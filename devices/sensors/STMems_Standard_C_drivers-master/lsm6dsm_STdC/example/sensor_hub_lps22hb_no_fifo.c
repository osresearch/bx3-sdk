/*
 ******************************************************************************
 * @file    sensor_hub_lps22hb.c
 * @author  Sensors Software Solution Team
 * @brief   This file show the simplest way enable a LPS22HB press. and
 *          temperature sensor connected to LSM6DSM I2C master interface
 *          (no FIFO support).
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
#include <lsm6dsm_reg.h>
#include <lps22hb_reg.h>
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

typedef union{
  int16_t i16bit;
  uint8_t u8bit[2];
} axis1bit16_t;

typedef union{
  int32_t i32bit;
  uint8_t u8bit[4];
} axis1bit32_t;
  
/* Private macro -------------------------------------------------------------*/
#define OUT_XYZ_SIZE		6
#define PRESS_OUT_XYZ_SIZE	3
#define TEMP_OUT_XYZ_SIZE	2

#define MIN_ODR(x, y) 			(x < y ? x : y)
#define MAX_ODR(x, y) 			(x > y ? x : y)
#define MAX_PATTERN_NUM			FIFO_THRESHOLD / 6
#define LSM6DSM_ODR_LSB_TO_HZ(_odr)	(_odr ? (13 << (_odr - 1)) : 0)
#define LPS22HB_ODR_LSB_TO_HZ(_odr)	(_odr == 1 ? 1 : _odr == 2 ? 10 : 25 << (_odr - 3))

/* Private types ---------------------------------------------------------*/
typedef struct {
  uint8_t enable;
  uint32_t odr;
  uint16_t odr_hz_val;
  uint32_t fs;
  uint8_t decimation;
  uint8_t samples_num_in_pattern;
} sensor_lsm6dsl;

/* Private variables ---------------------------------------------------------*/
static uint8_t whoamI, rst;
static uint8_t tx_buffer[1000];
static float pressure_hPa;
static float temperature_degC;
static float acceleration_mg[3];
static float angular_rate_mdps[3];
static axis1bit32_t data_raw_pressure;
static axis1bit16_t data_raw_temperature;
static axis3bit16_t data_raw_acceleration;
static axis3bit16_t data_raw_angular_rate;
static stmdev_ctx_t dev_ctx;
static stmdev_ctx_t press_ctx;

/*
 * 6dsl Accelerometer test parameters
 */
static sensor_lsm6dsl test_6dsl_xl =
{
  .enable = PROPERTY_ENABLE,
  .odr = LSM6DSM_XL_ODR_52Hz,
  .odr_hz_val = 0,
  .fs = LSM6DSM_2g,
  .decimation = 0,
  .samples_num_in_pattern = 0,
};

/*
 * 6dsl Gyroscope test parameters
 */
static sensor_lsm6dsl test_6dsl_gyro =
{
  .enable = PROPERTY_ENABLE,
  .odr = LSM6DSM_GY_ODR_26Hz,
  .odr_hz_val = 0,
  .fs = LSM6DSM_2000dps,
  .decimation = 0,
  .samples_num_in_pattern = 0,
};

/*
 * External Pression test parameters
 */
static sensor_lsm6dsl test_6dsl_press =
{
  .enable = PROPERTY_ENABLE,
  .odr = LPS22HB_ODR_50_Hz,
  .odr_hz_val = 0,
  .fs = 0,
  .decimation = 0,
  .samples_num_in_pattern = 0,
};

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

/*
 * Read data byte from internal register of a slave device connected
 * to master I2C interface.
 * Address selected for sensor is lps22hb_address
 */
static int32_t lsm6dsm_read_cx(void* ctx, uint8_t reg, uint8_t* data,
                               uint16_t len)
{
  int32_t mm_error;
  uint8_t drdy;
  uint8_t i;
  lsm6dsm_reg_t reg_endop;
  uint8_t sh_reg[18];
  lsm6dsm_sh_cfg_read_t val = {
    .slv_add = LPS22HB_I2C_ADD_H,
    .slv_subadd = reg,
    .slv_len = len,
  };

  (void)ctx;

  /*
   * Configure Sensor Hub to read LPS22HB
   */
  mm_error = lsm6dsm_sh_slv0_cfg_read(&dev_ctx, &val);
  lsm6dsm_sh_num_of_dev_connected_set(&dev_ctx, LSM6DSM_SLV_0_1);

  /*
   * Enable I2C Master and I2C master Pull Up
   */
  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_ENABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_ENABLE);

  /*
   * Enable accelerometer to trigger Sensor Hub operation
   */
  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_104Hz);

  /*
   * Wait Sensor Hub operation flag set
   */
  lsm6dsm_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
  do
  {
    lsm6dsm_xl_flag_data_ready_get(&dev_ctx, &drdy);
  } while (!drdy);

  do
  {
    lsm6dsm_read_reg(&dev_ctx, LSM6DSM_FUNC_SRC1, &reg_endop.byte, 1);
  } while (!reg_endop.func_src1.sensorhub_end_op);

  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_OFF);
  lsm6dsm_sh_read_data_raw_get(&dev_ctx, (lsm6dsm_emb_sh_read_t*)&sh_reg);

  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_DISABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_DISABLE);

  for(i = 0; i < len; i++)
    data[i] = sh_reg[i];

  return mm_error;
}

/*
 * Write data byte to internal register of a slave device connected
 * to master I2C interface
 * Address selected for sensor is lps22hb_address
 */
static int32_t lsm6dsm_write_cx(void* ctx, uint8_t reg, uint8_t* data,
        uint16_t len)
{
  int32_t mm_error;
  uint8_t drdy;
  lsm6dsm_reg_t reg_endop;
  lsm6dsm_sh_cfg_write_t val = {
    .slv0_add = LPS22HB_I2C_ADD_H,
    .slv0_subadd = reg,
    .slv0_data = *data,
  };

  (void)ctx;
  (void)len;

  /*
   * Disable accelerometer
   */
  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_OFF);

  /*
   * Configure Sensor Hub to write
   */
  mm_error = lsm6dsm_sh_cfg_write(&dev_ctx, &val);

  /*
   * Enable I2C Master and I2C master Pull Up
   */
  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_ENABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_ENABLE);

  /*
   * Enable accelerometer to trigger Sensor Hub operation
   */
  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_104Hz);

  /*
   * Wait Sensor Hub operation flag set
   */
  lsm6dsm_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
  do
  {
    lsm6dsm_xl_flag_data_ready_get(&dev_ctx, &drdy);
  } while (!drdy);

  do
  {
    lsm6dsm_read_reg(&dev_ctx, LSM6DSM_FUNC_SRC1, &reg_endop.byte, 1);
  } while (!reg_endop.func_src1.sensorhub_end_op);

  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_OFF);

  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_DISABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_DISABLE);

  return mm_error;
}

/*
 * Configure LPS22HB sensor over I2C master line
 *
 * Enable LPS22HB Press. and Temp. reading
 * Address selected for sensor is lps22hb_address
 */
static void configure_lps22hb(stmdev_ctx_t* ctx)
{
  lsm6dsm_sh_cfg_read_t val = {
    .slv_add = LPS22HB_I2C_ADD_H,
    .slv_subadd = LPS22HB_PRESS_OUT_XL,
    .slv_len = PRESS_OUT_XYZ_SIZE + TEMP_OUT_XYZ_SIZE,
  };

  lps22hb_data_rate_set(ctx, test_6dsl_press.odr);

  /*
   * Prepare sensor hub to read data from external sensor
   */
  lsm6dsm_sh_slv0_cfg_read(&dev_ctx, &val);
}

/* Main Example --------------------------------------------------------------*/
void example_sensorhub_lps22hb(void)
{
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &hi2c1;

  /*
   * Configure low level function to access to external device
   */
  press_ctx.read_reg = lsm6dsm_read_cx;
  press_ctx.write_reg = lsm6dsm_write_cx;
  press_ctx.handle = &hi2c1;

  /*
   * Initialize platform specific hardware
   */
  platform_init();

  /*
   * Check device ID
   */
  lsm6dsm_device_id_get(&dev_ctx, &whoamI);
  if (whoamI != LSM6DSM_ID)
    while(1)
    {
      /* manage here device not found */
    }

  /*
   * Restore default configuration
   */
  lsm6dsm_reset_set(&dev_ctx, PROPERTY_ENABLE);
  do {
	  lsm6dsm_reset_get(&dev_ctx, &rst);
  } while (rst);

  /*
   * Some hardware require to enable pull up on master I2C interface
   */
  //lsm6dsm_sh_pin_mode_set(&dev_ctx, LSM6DSM_INTERNAL_PULL_UP);

  /*
   * Check if LPS22HB connected to Sensor Hub
   */
  lps22hb_device_id_get(&press_ctx, &whoamI);
  if (whoamI != LPS22HB_ID)
  {
    while(1)
    {
      /* manage here device not found */
    }
  }

  /*
   * Configure LPS22HB on the I2C master line
   */
  configure_lps22hb(&press_ctx);

  /*
   * Configure Sensor Hub to read one slaves
   */
  lsm6dsm_sh_num_of_dev_connected_set(&dev_ctx, LSM6DSM_SLV_0);

  /*
   * Enable master and XL trigger.
   */
  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_ENABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_ENABLE);

  /*
   * Set XL and Gyro Output Data Rate
   */
  lsm6dsm_xl_data_rate_set(&dev_ctx, test_6dsl_xl.odr);
  lsm6dsm_gy_data_rate_set(&dev_ctx, test_6dsl_gyro.odr);

  /*
   * Set XL full scale and Gyro full scale
   */
  lsm6dsm_xl_full_scale_set(&dev_ctx, test_6dsl_xl.fs);
  lsm6dsm_gy_full_scale_set(&dev_ctx, test_6dsl_gyro.fs);

  while(1)
  {
    lsm6dsm_reg_t reg;
    uint8_t emb_sh[18];

    /*
     * Read output only if new value is available
     */
    lsm6dsm_status_reg_get(&dev_ctx, &reg.status_reg);
    if (reg.status_reg.xlda)
    {
      /*
       * Read acceleration field data
       */
      memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
      lsm6dsm_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
      acceleration_mg[0] =
        lsm6dsm_from_fs2g_to_mg(data_raw_acceleration.i16bit[0]);
      acceleration_mg[1] =
        lsm6dsm_from_fs2g_to_mg(data_raw_acceleration.i16bit[1]);
      acceleration_mg[2] =
        lsm6dsm_from_fs2g_to_mg(data_raw_acceleration.i16bit[2]);

      sprintf((char*)tx_buffer, "Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
              acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
      tx_com(tx_buffer, strlen((char const*)tx_buffer));

      /*
       * Read pressure and temperature data from sensor hub register:
       * XL trigger a new read to sensor hub sensors
       */
      lsm6dsm_sh_read_data_raw_get(&dev_ctx, (lsm6dsm_emb_sh_read_t*) &emb_sh);
      memcpy(data_raw_pressure.u8bit,
             (uint8_t *)&emb_sh[0],
             PRESS_OUT_XYZ_SIZE);
      pressure_hPa = lps22hb_from_lsb_to_hpa(data_raw_pressure.i32bit);
      memcpy(data_raw_temperature.u8bit,
             (uint8_t *)&emb_sh[3],
             TEMP_OUT_XYZ_SIZE);
      temperature_degC = lps22hb_from_lsb_to_degc(data_raw_temperature.i16bit);

      sprintf((char*)tx_buffer, "Press [hpa]:%4.2f\r\n", pressure_hPa);
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      sprintf((char*)tx_buffer, "Temp [C]:%4.2f\r\n", temperature_degC);
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
    }

    if (reg.status_reg.gda)
    {
      /*
       * Read angular rate field data
       */
      memset(data_raw_angular_rate.u8bit, 0x00, 3 * sizeof(int16_t));
      lsm6dsm_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate.u8bit);
      angular_rate_mdps[0] =
        lsm6dsm_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[0]);
      angular_rate_mdps[1] =
        lsm6dsm_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[1]);
      angular_rate_mdps[2] =
        lsm6dsm_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[2]);

      sprintf((char*)tx_buffer,
              "Angular rate [mdps]:%4.2f\t%4.2f\t%4.2f\r\n",
              angular_rate_mdps[0],
              angular_rate_mdps[1],
              angular_rate_mdps[2]);
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
    HAL_I2C_Mem_Write(handle, LSM6DSM_I2C_ADD_H, reg,
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
    HAL_I2C_Mem_Read(handle, LSM6DSM_I2C_ADD_H, reg,
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
