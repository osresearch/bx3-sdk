/*
 ******************************************************************************
 * @file    double_click_detection.c
 * @author  Sensors Software Solution Team
 * @brief   LIS3DE driver file
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

/* Includes ------------------------------------------------------------------*/
#include "lis3de_reg.h"
#include <string.h>
#include <stdio.h>

//#define MKI109V2
#define NUCLEO_STM32F411RE

#ifdef MKI109V2
#include "stm32f1xx_hal.h"
#include "usbd_cdc_if.h"
#include "spi.h"
#include "i2c.h"
#endif

#ifdef NUCLEO_STM32F411RE
#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#endif

/* Private macro -------------------------------------------------------------*/
#ifdef MKI109V2
#define CS_SPI2_GPIO_Port   CS_DEV_GPIO_Port
#define CS_SPI2_Pin         CS_DEV_Pin
#define CS_SPI1_GPIO_Port   CS_RF_GPIO_Port
#define CS_SPI1_Pin         CS_RF_Pin
#endif

#ifdef NUCLEO_STM32F411RE
/* N/A on NUCLEO_STM32F411RE + IKS01A1 */
/* N/A on NUCLEO_STM32F411RE + IKS01A2 */
#define CS_SPI2_GPIO_Port   0
#define CS_SPI2_Pin         0
#define CS_SPI1_GPIO_Port   0
#define CS_SPI1_Pin         0

/* Pin configured as platform interrupt from LIS3DE INT1. */
#define LIS3DE_INT1_PIN GPIO_PIN_4
#define LIS3DE_INT1_GPIO_PORT GPIOA

#endif

#define TX_BUF_DIM          1000

/* Private variables ---------------------------------------------------------*/
static uint8_t tx_buffer[TX_BUF_DIM];

/* Extern variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*
 *   Replace the functions "platform_write" and "platform_read" with your
 *   platform specific read and write function.
 *   This example use an STM32 evaluation board and CubeMX tool.
 *   In this case the "*handle" variable is useful in order to select the
 *   correct interface but the usage of "*handle" is not mandatory.
 */

static int32_t platform_write(void *handle, uint8_t Reg, uint8_t *Bufp,
                              uint16_t len)
{
  if (handle == &hi2c1)
  {
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0x80;
    HAL_I2C_Mem_Write(handle, LIS3DE_I2C_ADD_H, Reg,
                      I2C_MEMADD_SIZE_8BIT, Bufp, len, 1000);
  }
#ifdef MKI109V2
  else if (handle == &hspi2)
  {
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0x40;
    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &Reg, 1, 1000);
    HAL_SPI_Transmit(handle, Bufp, len, 1000);
    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
  }
  else if (handle == &hspi1)
  {
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0x40;
    HAL_GPIO_WritePin(CS_SPI1_GPIO_Port, CS_SPI1_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &Reg, 1, 1000);
    HAL_SPI_Transmit(handle, Bufp, len, 1000);
    HAL_GPIO_WritePin(CS_SPI1_GPIO_Port, CS_SPI1_Pin, GPIO_PIN_SET);
  }
#endif
  return 0;
}

static int32_t platform_read(void *handle, uint8_t Reg, uint8_t *Bufp,
                             uint16_t len)
{
  if (handle == &hi2c1)
  {
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0x80;
    HAL_I2C_Mem_Read(handle, LIS3DE_I2C_ADD_H, Reg,
                     I2C_MEMADD_SIZE_8BIT, Bufp, len, 1000);
  }
#ifdef MKI109V2
  else if (handle == &hspi2)
  {
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0xC0;
    HAL_GPIO_WritePin(CS_DEV_GPIO_Port, CS_DEV_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &Reg, 1, 1000);
    HAL_SPI_Receive(handle, Bufp, len, 1000);
    HAL_GPIO_WritePin(CS_DEV_GPIO_Port, CS_DEV_Pin, GPIO_PIN_SET);
  }
  else
  {
    /* enable auto incremented in multiple read/write commands */
    Reg |= 0xC0;
    HAL_GPIO_WritePin(CS_RF_GPIO_Port, CS_RF_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &Reg, 1, 1000);
    HAL_SPI_Receive(handle, Bufp, len, 1000);
    HAL_GPIO_WritePin(CS_RF_GPIO_Port, CS_RF_Pin, GPIO_PIN_SET);
  }
#endif
  return 0;
}

/*
 *  Function to print messages
 */
static void tx_com( uint8_t *tx_buffer, uint16_t len )
{
  #ifdef NUCLEO_STM32F411RE
  HAL_UART_Transmit( &huart2, tx_buffer, len, 1000 );
  #endif
  #ifdef MKI109V2
  CDC_Transmit_FS( tx_buffer, len );
  #endif
}

/*
 * Function to read external interrupt pin.
 */
static int32_t platform_reap_int_pin(void)
{
#ifdef NUCLEO_STM32F411RE
    return HAL_GPIO_ReadPin(LIS3DE_INT1_GPIO_PORT, LIS3DE_INT1_PIN);
#else /* NUCLEO_STM32F411RE */
    return 0;
#endif /* NUCLEO_STM32F411RE */
}

/* Main Example --------------------------------------------------------------*/

/*
 * Set click threshold to 12h  -> 0.281 g
 * Set TIME_LIMIT to 33h -> 127 ms
 * Enable double click detection on all axis
 * Poll on platform INT pin 1 waiting for event detection
 */
void example_double_click_lis3de(void)
{
  /* Initialize mems driver interface. */
  stmdev_ctx_t dev_ctx;
  lis3de_ctrl_reg3_t ctrl_reg3;
  lis3de_click_cfg_t click_cfg;
  uint8_t whoamI;

  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &hi2c1;

  /* Check device ID. */
  whoamI = 0;
  lis3de_device_id_get(&dev_ctx, &whoamI);
  if (whoamI != LIS3DE_ID)
    while(1); /* manage here device not found */

  /*
   * Set Output Data Rate.
   * The recommended accelerometer ODR for single and
   * double-click recognition is 400 Hz or higher.
   */
  lis3de_data_rate_set(&dev_ctx, LIS3DE_ODR_400Hz);

  /* Set full scale to 2 g. */
  lis3de_full_scale_set(&dev_ctx, LIS3DE_2g);

  /*
   * Set click threshold to 12h  -> 0.281 g.
   * 1 LSB = full scale/128
   * Set TIME_LIMIT to 20h -> 80 ms.
   * Set TIME_LATENCY to 20h -> 80 ms.
   * Set TIME_WINDOW to 30h -> 120 ms.
   * 1 LSB = 1/ODR
   */
  lis3de_tap_threshold_set(&dev_ctx, 0x12);
  lis3de_shock_dur_set(&dev_ctx, 0x20);
  lis3de_quiet_dur_set(&dev_ctx, 0x20);
  lis3de_double_tap_timeout_set(&dev_ctx, 0x30);

  /* Enable Click interrupt on INT pin 1. */
  memset((uint8_t *)&ctrl_reg3, 0, sizeof(ctrl_reg3));
  ctrl_reg3.int1_click = PROPERTY_ENABLE;
  lis3de_pin_int1_config_set(&dev_ctx, &ctrl_reg3);
  lis3de_int1_gen_duration_set(&dev_ctx, 0);

  /* Enable double click on all axis. */
  memset((uint8_t *)&click_cfg, 0, sizeof(click_cfg));
  click_cfg.xd = PROPERTY_ENABLE;
  click_cfg.yd = PROPERTY_ENABLE;
  click_cfg.zd = PROPERTY_ENABLE;
  lis3de_tap_conf_set(&dev_ctx, &click_cfg);

  /* Set device in HR mode. */
  lis3de_operating_mode_set(&dev_ctx, LIS3DE_LP);

  while(1)
  {
    /* Read INT pin 1 in polling mode. */
	lis3de_click_src_t src;

    if (platform_reap_int_pin())
    {
      lis3de_tap_source_get(&dev_ctx, &src);
      sprintf((char*)tx_buffer, "d-click detected : "
    		  "x %d, y %d, z %d, sign %d\r\n",
    		  src.x, src.y, src.z, src.sign);
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
    }
  }
}
