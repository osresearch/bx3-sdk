/*
 ******************************************************************************
 * @file    orientation_6d.c
 * @author  Sensors Software Solution Team
 * @brief   This file show the simplest way to detect 6D orientation from sensor.
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
#include "lis331dlh_reg.h"
#include "gpio.h"
#include "i2c.h"
#if defined(STEVAL_MKI109V3)
#include "usbd_cdc_if.h"
#include "spi.h"
#elif defined(NUCLEO_F411RE_X_NUCLEO_IKS01A2)
#include "usart.h"
#endif

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t whoamI;
static uint8_t tx_buffer[1000];

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
static void tx_com(uint8_t *tx_buffer, uint16_t len);
static void platform_init(void);

/* Main Example --------------------------------------------------------------*/
void example_main_orientation_6D_lis331dlh(void)
{
  /*
   * Initialize mems driver interface
   */
  stmdev_ctx_t dev_ctx;

  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &hi2c1;

  /*
   * Initialize platform specific hardware
   */
  platform_init();

  /*
   * Check device ID
   */
  lis331dlh_device_id_get(&dev_ctx, &whoamI);
  if (whoamI != LIS331DLH_ID)
  {
    while(1)
    {
      /* manage here device not found */
    }
  }

  /*
   * Set full scale
   */
  lis331dlh_full_scale_set(&dev_ctx, LIS331DLH_2g);

  /*
   * Disable HP filter
   */
  lis331dlh_hp_path_set(&dev_ctx, LIS331DLH_HP_DISABLE);

  /*
   * Set no duration
   */
  lis331dlh_int1_dur_set(&dev_ctx, 0);

  /*
   * Set 6D position detection
   */
  lis331dlh_int1_6d_mode_set(&dev_ctx, LIS331DLH_6D_INT1_POSITION);

  /*
   * Apply 6D Orientation axis threshold
   */
  lis331dlh_int1_treshold_set(&dev_ctx, 33);

  /*
   * Set Output Data Rate
   */
  lis331dlh_data_rate_set(&dev_ctx, LIS331DLH_ODR_100Hz);

  /*
   * Wait Events
   */
  while(1)
  {
    lis331dlh_reg_t all_source;

    lis331dlh_int1_src_get(&dev_ctx, &all_source.int1_src);

    /*
     * Check 6D Orientation
     */
    switch(all_source.byte & 0x3f)
    {
    case 0x01:
      sprintf((char*)tx_buffer, "6D Or. position XL\r\n");
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      break;
    case 0x02:
      sprintf((char*)tx_buffer, "6D Or. position XH\r\n");
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      break;
    case 0x04:
      sprintf((char*)tx_buffer, "6D Or. position YL\r\n");
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      break;
    case 0x08:
      sprintf((char*)tx_buffer, "6D Or. position YH\r\n");
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      break;
    case 0x10:
      sprintf((char*)tx_buffer, "6D Or. position ZL\r\n");
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      break;
    case 0x20:
      sprintf((char*)tx_buffer, "6D Or. position ZH\r\n");
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      break;
    default:
      break;
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
    /* Write multiple command */
    reg |= 0x80;
    HAL_I2C_Mem_Write(handle, LIS331DLH_I2C_ADD_L, reg,
                      I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  }
#ifdef STEVAL_MKI109V3
  else if (handle == &hspi2)
  {
    /* Write multiple command */
    reg |= 0x40;
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
    /* Read multiple command */
    reg |= 0x80;
    HAL_I2C_Mem_Read(handle, LIS331DLH_I2C_ADD_L, reg,
                     I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  }
#ifdef STEVAL_MKI109V3
  else if (handle == &hspi2)
  {
    /* Read multiple command */
    reg |= 0xC0;
    HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &reg, 1, 1000);
    HAL_SPI_Receive(handle, bufp, len, 1000);
    HAL_GPIO_WritePin(CS_up_GPIO_Port, CS_up_Pin, GPIO_PIN_SET);
  }
#endif
  return 0;
}

/*
 * @brief  Send buffer to console (platform dependent)
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
  CDC_Transmit_FS(tx_buffer, len);
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
