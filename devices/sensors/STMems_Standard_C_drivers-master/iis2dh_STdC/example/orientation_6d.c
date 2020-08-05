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
#include "iis2dh_reg.h"
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
void example_main_orientation_6d_iis2dh(void)
{
  /*
   *  Initialize mems driver interface.
   */
  stmdev_ctx_t dev_ctx;
  iis2dh_int1_cfg_t _6d_cfg;
  iis2dh_ctrl_reg3_t ctrl_reg3;

  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &hi2c1;

  /*
   * Initialize platform specific hardware
   */
  platform_init();

  /*
   *  Check device ID
   */
  iis2dh_device_id_get(&dev_ctx, &whoamI);
  if (whoamI != IIS2DH_ID)
  {
    while(1)
    {
    	/* manage here device not found */
    }
  }

  /*
   * Set Output Data Rate to 25 Hz
   */
  iis2dh_data_rate_set(&dev_ctx, IIS2DH_ODR_25Hz);

  /*
   * Set full scale to 2 g
   */
  iis2dh_full_scale_set(&dev_ctx, IIS2DH_2g);

  /*
   * Set interrupt threshold to 0x12 -> 288 mg
   */
  iis2dh_int1_gen_threshold_set(&dev_ctx, 0x12);

  /*
   * Enable AOI1 on int1 pin
   */
  iis2dh_pin_int1_config_get(&dev_ctx, &ctrl_reg3);
  ctrl_reg3.i1_aoi1 = PROPERTY_ENABLE;
  iis2dh_pin_int1_config_set(&dev_ctx, &ctrl_reg3);

  /*
   * Set no time duration.
   */
  iis2dh_int1_gen_duration_set(&dev_ctx, 0);

  /*
   * Configure for movement recognition on all axis
   *
   * Follow a short definition of movement recognition
   * and direction recognition supported by device:
   *
   * AOI-6D = ‘01’ is movement recognition:
   *     An interrupt is generated when the orientation
   *     moves from an unknown zone to a known zone.
   *     The interrupt signal remains for a duration ODR.
   *
   * AOI-6D = ‘11’ is direction recognition:
   *     An interrupt is generated when the orientation is
   *     inside a known zone.
   *     The interrupt signal remains while the orientation
   *     is inside the zone.
   */
  iis2dh_int1_gen_conf_get(&dev_ctx, &_6d_cfg);
  _6d_cfg._6d = PROPERTY_ENABLE;
  _6d_cfg.aoi = PROPERTY_DISABLE;
  _6d_cfg.xlie = PROPERTY_ENABLE;
  _6d_cfg.xhie = PROPERTY_ENABLE;
  _6d_cfg.ylie = PROPERTY_ENABLE;
  _6d_cfg.yhie = PROPERTY_ENABLE;
  _6d_cfg.zlie = PROPERTY_ENABLE;
  _6d_cfg.zhie = PROPERTY_ENABLE;
  iis2dh_int1_gen_conf_set(&dev_ctx, &_6d_cfg);

  /*
   * Set device in HR mode
   */
  iis2dh_operating_mode_set(&dev_ctx, IIS2DH_HR_12bit);

  while(1)
  {
    iis2dh_reg_t all_source;

    /*
     * Read INT pin 1 in polling mode
     */
    iis2dh_int1_gen_source_get(&dev_ctx, &all_source.int1_src);

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
    HAL_I2C_Mem_Write(handle, IIS2DH_I2C_ADD_L, reg,
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
    HAL_I2C_Mem_Read(handle, IIS2DH_I2C_ADD_L, reg,
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
