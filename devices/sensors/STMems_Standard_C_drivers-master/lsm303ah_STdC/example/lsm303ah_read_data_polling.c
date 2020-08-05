/*
 ******************************************************************************
 * @file    read_data_polling.c
 * @author  MEMS Software Solution Team
 * @brief   This file show the simplest way to get data from sensor.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include <lsm303ah_reg.h>
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

typedef union{
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;

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
#endif

#define TX_BUF_DIM          1000

/* Private variables ---------------------------------------------------------*/
static axis3bit16_t data_raw_acceleration;
static axis3bit16_t data_raw_magnetic;
static float acceleration_mg[3];
static float magnetic_mG[3];
static uint8_t whoamI, rst;
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
  uint32_t i2c_add = (uint32_t)handle;

  HAL_I2C_Mem_Write(&hi2c1, i2c_add, Reg,
                    I2C_MEMADD_SIZE_8BIT, Bufp, len, 1000);
  return 0;
}

static int32_t platform_read(void *handle, uint8_t Reg, uint8_t *Bufp,
                             uint16_t len)
{
  uint32_t i2c_add = (uint32_t)handle;

  HAL_I2C_Mem_Read(&hi2c1, (uint8_t) i2c_add, Reg,
                   I2C_MEMADD_SIZE_8BIT, Bufp, len, 1000);
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

/* Main Example --------------------------------------------------------------*/
void lsm303ah_read_data_polling(void)
{
  /*
   *  Initialize mems driver interface
   */
  stmdev_ctx_t dev_ctx_xl;
  dev_ctx_xl.write_reg = platform_write;
  dev_ctx_xl.read_reg = platform_read;
  dev_ctx_xl.handle = (void*)LSM303AH_I2C_ADD_XL; 
 
  stmdev_ctx_t dev_ctx_mg;
  dev_ctx_mg.write_reg = platform_write;
  dev_ctx_mg.read_reg = platform_read;
  dev_ctx_mg.handle = (void*)LSM303AH_I2C_ADD_MG;
 
  /*
   *  Check device ID
   */
  whoamI = 0;
  lsm303ah_xl_device_id_get(&dev_ctx_xl, &whoamI);
  if ( whoamI != LSM303AH_ID_XL )
    while(1); /*manage here device not found */
  whoamI = 0;
  lsm303ah_mg_device_id_get(&dev_ctx_mg, &whoamI);
  if ( whoamI != LSM303AH_ID_MG )
    while(1); /*manage here device not found */
 
  /*
   *  Restore default configuration
   */
  lsm303ah_xl_reset_set(&dev_ctx_xl, PROPERTY_ENABLE);
  do {
    lsm303ah_xl_reset_get(&dev_ctx_xl, &rst);
  } while (rst);
 
  lsm303ah_mg_reset_set(&dev_ctx_mg, PROPERTY_ENABLE);
  do {
    lsm303ah_mg_reset_get(&dev_ctx_mg, &rst);
  } while (rst);
 
  /*
   *  Enable Block Data Update
   */
  lsm303ah_xl_block_data_update_set(&dev_ctx_xl, PROPERTY_ENABLE);
  lsm303ah_mg_block_data_update_set(&dev_ctx_mg, PROPERTY_ENABLE);
 
  /*
   * Set full scale
   */ 
  lsm303ah_xl_full_scale_set(&dev_ctx_xl, LSM303AH_XL_2g);
  /*
   * Configure filtering chain
   */ 
  /* Accelerometer - High Pass / Slope path */
  //lsm303ah_xl_hp_path_set(&dev_ctx_xl, LSM303AH_HP_ON_OUTPUTS);
  /*
   * Set / Reset magnetic sensor mode
   */ 
  lsm303ah_mg_set_rst_mode_set(&dev_ctx_mg, LSM303AH_MG_SENS_OFF_CANC_EVERY_ODR); 
 
  /*
   * Enable temperature compensation on mag sensor
   */ 
  lsm303ah_mg_offset_temp_comp_set(&dev_ctx_mg, PROPERTY_ENABLE); 
 
  /*
   * Set Output Data Rate
   */
  lsm303ah_xl_data_rate_set(&dev_ctx_xl, LSM303AH_XL_ODR_100Hz_LP);
  lsm303ah_mg_data_rate_set(&dev_ctx_mg, LSM303AH_MG_ODR_10Hz);
 
  /*
   * Set magnetometer in continuos mode
   */  
  lsm303ah_mg_operating_mode_set(&dev_ctx_mg, LSM303AH_MG_CONTINUOUS_MODE); 
 
  /*
   * Read samples in polling mode (no int)
   */
  while(1)
  {
    /*
     * Read output only if new value is available
     */
    lsm303ah_reg_t reg;
    lsm303ah_xl_status_reg_get(&dev_ctx_xl, &reg.status_a);

    if (reg.status_a.drdy)
    {
      /* Read acceleration data */
      memset(data_raw_acceleration.u8bit, 0x00, 3*sizeof(int16_t));
      lsm303ah_acceleration_raw_get(&dev_ctx_xl, data_raw_acceleration.u8bit);
      acceleration_mg[0] = lsm303ah_from_fs2g_to_mg( data_raw_acceleration.i16bit[0]);
      acceleration_mg[1] = lsm303ah_from_fs2g_to_mg( data_raw_acceleration.i16bit[1]);
      acceleration_mg[2] = lsm303ah_from_fs2g_to_mg( data_raw_acceleration.i16bit[2]);
     
      sprintf((char*)tx_buffer, "Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
              acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
      tx_com( tx_buffer, strlen( (char const*)tx_buffer ) );
    }

    lsm303ah_mg_status_get(&dev_ctx_mg, &reg.status_reg_m);
    if (reg.status_reg_m.zyxda)
    {
      /* Read magnetic field data */
      memset(data_raw_magnetic.u8bit, 0x00, 3*sizeof(int16_t));
      lsm303ah_magnetic_raw_get(&dev_ctx_mg, data_raw_magnetic.u8bit);
      magnetic_mG[0] = lsm303ah_from_lsb_to_mgauss( data_raw_magnetic.i16bit[0]);
      magnetic_mG[1] = lsm303ah_from_lsb_to_mgauss( data_raw_magnetic.i16bit[1]);
      magnetic_mG[2] = lsm303ah_from_lsb_to_mgauss( data_raw_magnetic.i16bit[2]);
     
      sprintf((char*)tx_buffer, "Magnetic field [mG]:%4.2f\t%4.2f\t%4.2f\r\n",
              magnetic_mG[0], magnetic_mG[1], magnetic_mG[2]);
      tx_com( tx_buffer, strlen( (char const*)tx_buffer ) );
    }   
  }
}
