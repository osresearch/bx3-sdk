/*
 ******************************************************************************
 * @file    lsm6dsrx_wake_up.c
 * @author  Sensors Software Solution Team
 * @brief   This file show the simplest way to detect wake-up events from
 *          sensor.
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
#include <lsm6dsrx_reg.h>
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
static uint8_t whoamI, rst;
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
static void tx_com( uint8_t *tx_buffer, uint16_t len );
static void platform_init(void);

/* Main Example --------------------------------------------------------------*/
void lsm6dsrx_wake_up(void)
{
  stmdev_ctx_t dev_ctx;

  /*
   * Uncomment to configure INT 1
   */
  //lsm6dsrx_pin_int1_route_t int1_route;

  /*
   * Uncomment to configure INT 2
   */
  lsm6dsrx_pin_int2_route_t int2_route;

  /*
   *  Initialize mems driver interface
   */
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &hi2c1;

  /*
   * Init test platform
   */
  platform_init();

  /*
   *  Check device ID
   */
  lsm6dsrx_device_id_get(&dev_ctx, &whoamI);
  if (whoamI != LSM6DSRX_ID)
    while(1);

  /*
   *  Restore default configuration
   */
  lsm6dsrx_reset_set(&dev_ctx, PROPERTY_ENABLE);
  do {
    lsm6dsrx_reset_get(&dev_ctx, &rst);
  } while (rst);

  /*
   * Disable I3C interface
   */
  lsm6dsrx_i3c_disable_set(&dev_ctx, LSM6DSRX_I3C_DISABLE);

  /*
   * Set XL Output Data Rate to 416 Hz
   */
  lsm6dsrx_xl_data_rate_set(&dev_ctx, LSM6DSRX_XL_ODR_417Hz);

  /*
   * Set 2g full XL scale
   */
  lsm6dsrx_xl_full_scale_set(&dev_ctx, LSM6DSRX_2g);

  /*
   * Apply high-pass digital filter on Wake-Up function
   */
  lsm6dsrx_xl_hp_path_internal_set(&dev_ctx, LSM6DSRX_USE_SLOPE);

  /*
   * Set Wake-Up threshold: 1 LSb corresponds to FS_XL/2^6
   */
  lsm6dsrx_wkup_threshold_set(&dev_ctx, 2);

  /*
   * Uncomment interrupt generation on Wake-Up INT1 pin
   */
  //lsm6dsrx_pin_int1_route_get(&dev_ctx, &int1_route);
  //int1_route.md1_cfg.int1_wu = PROPERTY_ENABLE;
  //lsm6dsrx_pin_int1_route_set(&dev_ctx, &int1_route);

  /*
   * Enable if interrupt generation on Wake-Up INT2 pin
   */
  lsm6dsrx_pin_int2_route_get(&dev_ctx, &int2_route);
  int2_route.md2_cfg.int2_wu = PROPERTY_ENABLE;
  lsm6dsrx_pin_int2_route_set(&dev_ctx, &int2_route);

  /*
   * Wait Events
   */
  while(1)
  {
    lsm6dsrx_all_sources_t all_source;

    /*
     * Check if Wake-Up events
     */
    lsm6dsrx_all_sources_get(&dev_ctx, &all_source);
    if (all_source.wake_up_src.wu_ia)
    {
      sprintf((char*)tx_buffer, "Wake-Up event on ");
      if (all_source.wake_up_src.x_wu)
        strcat((char*)tx_buffer, "X");
      if (all_source.wake_up_src.y_wu)
        strcat((char*)tx_buffer, "Y");
      if (all_source.wake_up_src.z_wu)
        strcat((char*)tx_buffer, "Z");

      strcat((char*)tx_buffer, " direction\r\n");
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
    HAL_I2C_Mem_Write(handle, LSM6DSRX_I2C_ADD_L, reg,
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
    HAL_I2C_Mem_Read(handle, LSM6DSRX_I2C_ADD_L, reg,
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
