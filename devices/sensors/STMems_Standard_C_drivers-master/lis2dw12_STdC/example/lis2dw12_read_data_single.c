/*
 ******************************************************************************
 * @file    read_data_simple.c
 * @author  Sensors Software Solution Team
 * @brief   This file show the simplest way to get data from sensor.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/*
 * This example was developed using the following STMicroelectronics
 * evaluation boards:
 *
 * - STEVAL_MKI109V3
 * - NUCLEO_F411RE + X_NUCLEO_IKS01A2
 *
 * and STM32CubeMX tool with STM32CubeF4 MCU Package
 *
 * Used interfaces:
 *
 * STEVAL_MKI109V3    - Host side:   USB (Virtual COM)
 *                    - Sensor side: SPI(Default) / I2C(supported)
 *
 * NUCLEO_STM32F411RE + X_NUCLEO_IKS01A2 - Host side: UART(COM) to USB bridge
 *                                       - I2C(Default) / SPI(N/A)
 *
 * If you need to run this example on a different hardware platform a
 * modification of the functions: `platform_write`, `platform_read`,
 * `tx_com` and 'platform_init' is required.
 *
 */

/* STMicroelectronics evaluation boards definition
 *
 * Please uncomment ONLY the evaluation boards in use.
 * If a different hardware is used please comment all
 * following target board and redefine yours.
 */
//#define STEVAL_MKI109V3
#define NUCLEO_F411RE_X_NUCLEO_IKS01A2

#if defined(STEVAL_MKI109V3)
/* MKI109V3: Define communication interface */
#define SENSOR_BUS hspi2

/* MKI109V3: Vdd and Vddio power supply values */
#define PWM_3V3 915

#elif defined(NUCLEO_F411RE_X_NUCLEO_IKS01A2)
/* NUCLEO_F411RE_X_NUCLEO_IKS01A2: Define communication interface */
#define SENSOR_BUS hi2c1

#endif

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "lis2dw12_reg.h"
#include "gpio.h"
#include "i2c.h"
#if defined(STEVAL_MKI109V3)
#include "usbd_cdc_if.h"
#include "spi.h"
#elif defined(NUCLEO_F411RE_X_NUCLEO_IKS01A2)
#include "usart.h"
#endif

typedef union{
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static axis3bit16_t data_raw_acceleration;
static float acceleration_mg[3];
static uint8_t whoamI, rst;
static uint8_t tx_buffer[1000];
static lis2dw12_ctrl4_int1_pad_ctrl_t  ctrl4_int1_pad;

/* Extern variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
static void tx_com( uint8_t *tx_buffer, uint16_t len );
static void platform_init(void);

/* Main Example --------------------------------------------------------------*/
void lis2dw12_read_data_single(void)
{
  /* Initialize mems driver interface */
  stmdev_ctx_t dev_ctx;
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &SENSOR_BUS;

  /* Initialize platform specific hardware */
  platform_init();

  /* Check device ID */
  lis2dw12_device_id_get(&dev_ctx, &whoamI);
  if (whoamI != LIS2DW12_ID)
    while(1){
      /* manage here device not found */
    }

  /* Restore default configuration */
  lis2dw12_reset_set(&dev_ctx, PROPERTY_ENABLE);
  do {
    lis2dw12_reset_get(&dev_ctx, &rst);
  } while (rst);

  /* Enable Block Data Update */
  lis2dw12_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
  //lis2dw12_cs_mode_set(&dev_ctx, LIS2DW12_PULL_UP_DISCONNECT);
  //lis2dw12_i2c_interface_set(&dev_ctx, LIS2DW12_I2C_DISABLE);
  //lis2dw12_spi_mode_set(&dev_ctx, LIS2DW12_SPI_3_WIRE);
 
  lis2dw12_int_notification_set(&dev_ctx, LIS2DW12_INT_LATCHED);
  lis2dw12_pin_polarity_set(&dev_ctx, LIS2DW12_ACTIVE_LOW);
 
  lis2dw12_pin_int1_route_get(&dev_ctx, &ctrl4_int1_pad);
  ctrl4_int1_pad.int1_drdy = PROPERTY_ENABLE;
  lis2dw12_pin_int1_route_set(&dev_ctx, &ctrl4_int1_pad);
 
  /* Set full scale */ 
  lis2dw12_full_scale_set(&dev_ctx, LIS2DW12_2g);

  /* Configure filtering chain accelerometer */ 
  lis2dw12_filter_path_set(&dev_ctx, LIS2DW12_LPF_ON_OUT);
  lis2dw12_filter_bandwidth_set(&dev_ctx, LIS2DW12_ODR_DIV_10);

  /* Configure power mode and Output Data Rate */
  lis2dw12_power_mode_set(&dev_ctx, LIS2DW12_CONT_LOW_PWR_12bit);
  lis2dw12_data_rate_set(&dev_ctx, LIS2DW12_XL_SET_SW_TRIG);

  /* Read samples in polling mode (no int) */
  while(1)
  {
    /* polling on DRDY signal */
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))
    {
      /* Read acceleration data */
      memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
      lis2dw12_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
      acceleration_mg[0] = lis2dw12_from_fs2_lp1_to_mg(data_raw_acceleration.i16bit[0]);
      acceleration_mg[1] = lis2dw12_from_fs2_lp1_to_mg(data_raw_acceleration.i16bit[1]);
      acceleration_mg[2] = lis2dw12_from_fs2_lp1_to_mg(data_raw_acceleration.i16bit[2]);
      for (int i=0; i<0x3FF; i++);
      lis2dw12_data_rate_set(&dev_ctx, LIS2DW12_XL_SET_SW_TRIG);
     
      sprintf((char*)tx_buffer, "Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
              acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
    }
  }
}

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
                              uint16_t len)
{
  if (handle == &hi2c1)
  {
    HAL_I2C_Mem_Write(handle, LIS2DW12_I2C_ADD_L, reg,
                      I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  }
#ifdef STEVAL_MKI109V3
  else if (handle == &hspi2)
  {
    HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &reg, 1, 1000);
    HAL_SPI_Transmit(handle, bufp, len, 1000);
    HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_SET);
  }
#endif
  return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
  if (handle == &hi2c1)
  {
    HAL_I2C_Mem_Read(handle, LIS2DW12_I2C_ADD_L, reg,
                     I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  }
#ifdef STEVAL_MKI109V3
  else if (handle == &hspi2)
  {
	/* Read command */
	reg |= 0x80;
    HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &reg, 1, 1000);
    HAL_SPI_Receive(handle, bufp, len, 1000);
    HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_SET);
  }
#endif
  return 0;
}

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  tx_buffer     buffer to trasmit
 * @param  len           number of byte to send
 *
 */
static void tx_com(uint8_t *tx_buffer, uint16_t len)
{
  #ifdef NUCLEO_F411RE_X_NUCLEO_IKS01A2
  HAL_UART_Transmit(&huart2, tx_buffer, len, 1000);
  #endif
  #ifdef STEVAL_MKI109V3
  //CDC_Transmit_FS(tx_buffer, len);
  #endif
}

/*
 * @brief  platform specific initialization (platform dependent)
 */
static void platform_init(void)
{
#ifdef STEVAL_MKI109V3
  TIM3->CCR1 = PWM_3V3;
  TIM3->CCR2 = PWM_3V3;
  HAL_Delay(1000);
#endif
}
