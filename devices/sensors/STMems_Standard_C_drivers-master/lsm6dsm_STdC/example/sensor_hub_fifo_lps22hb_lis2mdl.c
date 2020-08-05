/*
 ******************************************************************************
 * @file    sensor_hub_fifo_lps22hb_lis2mdl.c
 * @author  Sensors Software Solution Team
 * @brief   This file show the simplest way enable LPS22HB press. and
 *          LIS2MDL mag connected to LSM6DSM I2C master interface
 *          (with FIFO support).
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
#include <lis2mdl_reg.h>
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
#define LIS2MDL_ODR_LSB_TO_HZ(_odr)	(_odr == 0 ? 10 : _odr == 1 ? 20 : _odr == 2 ? 50 : 100)
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
static uint16_t pattern_len;
static float pressure_hPa;
static float temperature_degC;
static float acceleration_mg[3];
static float angular_rate_mdps[3];
static float magnetic_mG[3];
static axis3bit16_t data_raw_magnetic;
static axis1bit32_t data_raw_pressure;
static axis1bit16_t data_raw_temperature;
static axis3bit16_t data_raw_acceleration;
static axis3bit16_t data_raw_angular_rate;
static stmdev_ctx_t dev_ctx;
static stmdev_ctx_t press_ctx;
static stmdev_ctx_t mag_ctx;

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

/*
 * External lis2mdl Mag test parameters
 */
static sensor_lsm6dsl test_6dsl_mag = {
  .enable = PROPERTY_ENABLE,
  .odr = LIS2MDL_ODR_50Hz,
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
 * Following routine read a pattern from FIFO
 */
static void LSM6DSL_SH_Read_FIFO_Pattern(void)
{
  uint8_t gy_num = test_6dsl_gyro.samples_num_in_pattern;
  uint8_t xl_num = test_6dsl_xl.samples_num_in_pattern;
  uint8_t press_num = test_6dsl_press.samples_num_in_pattern;
  uint8_t mg_num = test_6dsl_mag.samples_num_in_pattern;
  uint8_t dummy[OUT_XYZ_SIZE];

  /*
   * FIFO pattern is composed by gy_num gyroscope triplets and
   * xl_num accelerometer triplets. The sequence has always following order:
   * gyro first, accelerometer second etc etc
   */
  while(gy_num > 0 || xl_num > 0 || press_num > 0 || mg_num > 0)
  {
    /*
     * Read gyro samples
     */
    if (test_6dsl_gyro.enable && gy_num > 0)
    {
      lsm6dsm_fifo_raw_data_get(&dev_ctx, data_raw_angular_rate.u8bit, OUT_XYZ_SIZE);
      angular_rate_mdps[0] = lsm6dsm_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[0]);
      angular_rate_mdps[1] = lsm6dsm_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[1]);
      angular_rate_mdps[2] = lsm6dsm_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[2]);

      sprintf((char*)tx_buffer, "Angular rate [mdps]:%4.2f\t%4.2f\t%4.2f\r\n",
              angular_rate_mdps[0], angular_rate_mdps[1], angular_rate_mdps[2]);
      tx_com( tx_buffer, strlen( (char const*)tx_buffer ) );
      gy_num--;
    }

    /*
     * Read XL samples
     */
    if (test_6dsl_xl.enable && xl_num > 0)
    {
      lsm6dsm_fifo_raw_data_get(&dev_ctx,
                                data_raw_acceleration.u8bit,
                                OUT_XYZ_SIZE);
      acceleration_mg[0] =
        lsm6dsm_from_fs2g_to_mg(data_raw_acceleration.i16bit[0]);
      acceleration_mg[1] =
        lsm6dsm_from_fs2g_to_mg(data_raw_acceleration.i16bit[1]);
      acceleration_mg[2] =
        lsm6dsm_from_fs2g_to_mg(data_raw_acceleration.i16bit[2]);

      sprintf((char*)tx_buffer, "Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
              acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      xl_num--;
    }

    /*
     * Read Mag samples
     */
    if (test_6dsl_mag.enable && mg_num > 0)
    {
      lsm6dsm_fifo_raw_data_get(&dev_ctx,
                                data_raw_magnetic.u8bit,
                                OUT_XYZ_SIZE);
      magnetic_mG[0] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic.i16bit[0]);
      magnetic_mG[1] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic.i16bit[1]);
      magnetic_mG[2] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic.i16bit[2]);

      sprintf((char*)tx_buffer, "Mag [mG]:%4.2f\t%4.2f\t%4.2f\r\n",
              magnetic_mG[0], magnetic_mG[1], magnetic_mG[2]);
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      mg_num--;
    }

    /*
     * Read press. and temperature samples
     */
    if (test_6dsl_press.enable && press_num > 0)
    {
      lsm6dsm_fifo_raw_data_get(&dev_ctx, dummy, OUT_XYZ_SIZE);
      memcpy(data_raw_pressure.u8bit, &dummy[0], PRESS_OUT_XYZ_SIZE);
      memcpy(data_raw_temperature.u8bit, &dummy[3], TEMP_OUT_XYZ_SIZE);
      pressure_hPa = lps22hb_from_lsb_to_hpa(data_raw_pressure.i32bit);
      temperature_degC = lps22hb_from_lsb_to_degc(data_raw_temperature.i16bit);

      sprintf((char*)tx_buffer, "Press [hPa]:%4.2f\t\r\n", pressure_hPa);
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      sprintf((char*)tx_buffer, "Temp [C]:%4.2f\t\r\n", temperature_degC);
      tx_com(tx_buffer, strlen((char const*)tx_buffer));
      press_num--;
    }
  }
}

/*
 * Samples acquisition is triggered by FIFO threshold event
 */
static void LSM6DSL_SH_ACC_GYRO_MAG_PRESS_sample_Callback_fifo(void)
{
  uint16_t num = 0;
  uint16_t num_pattern = 0;
  lsm6dsm_reg_t reg;

  /*
   * Get FIFO status
   */
  lsm6dsm_read_reg(&dev_ctx, LSM6DSM_FIFO_STATUS2, &reg.byte, 1);

  /*
   * In case of overrun remove at least minimal pattern from FIFO
   * in order to recovery status
   */
  if (reg.fifo_status2.over_run)
  {
    num_pattern = 10;
  }
  else
  {
    /*
     * Read number of word in FIFO
     */
    lsm6dsm_fifo_data_level_get(&dev_ctx, &num);
    num_pattern = num / pattern_len;
  }

  while (num_pattern-- > 0)
    LSM6DSL_SH_Read_FIFO_Pattern();
}

/*
 * Normalize external sensor ODR to a LSM6DSM compatible
 */
static uint16_t lsm6dsm_normalize_odr(uint16_t odr)
{
    uint16_t ret = 104;

    if (odr < 26)
      ret = 26;
    else if (odr < 52)
      ret = 52;

    return ret;
}

/*
 * Following routine calculate the FIFO pattern composition based
 * on gyro, acc,  mag. and press. enable state and ODR freq
 */
static uint16_t LSM6DSL_SH_Calculate_FIFO_Pattern(uint16_t *min_odr, uint16_t *max_odr)
{
  uint16_t fifo_samples_tot_num = 0;

  /*
   * Calculate min_odr and max_odr for current configuration
   */
  if (test_6dsl_gyro.enable)
  {
    test_6dsl_gyro.odr_hz_val = LSM6DSM_ODR_LSB_TO_HZ(test_6dsl_gyro.odr);
    *max_odr = MAX_ODR(*max_odr, test_6dsl_gyro.odr_hz_val);
    *min_odr = MIN_ODR(*min_odr, test_6dsl_gyro.odr_hz_val);
  }

  if (test_6dsl_xl.enable)
  {
    test_6dsl_xl.odr_hz_val = LSM6DSM_ODR_LSB_TO_HZ(test_6dsl_xl.odr);
    *max_odr = MAX_ODR(*max_odr, test_6dsl_xl.odr_hz_val);
    *min_odr = MIN_ODR(*min_odr, test_6dsl_xl.odr_hz_val);
  }

  if (test_6dsl_mag.enable)
  {
    /*
     * LIS2MDL odr are 10, 20, 50 and 100 must be remapped to LSM6DSM ODR
     */
    test_6dsl_mag.odr_hz_val = LIS2MDL_ODR_LSB_TO_HZ(test_6dsl_mag.odr);
    test_6dsl_mag.odr_hz_val = lsm6dsm_normalize_odr(test_6dsl_mag.odr_hz_val);

    *max_odr = MAX_ODR(*max_odr, test_6dsl_mag.odr_hz_val);
    *min_odr = MIN_ODR(*min_odr, test_6dsl_mag.odr_hz_val);
  }

  if (test_6dsl_press.enable)
  {
    /*
     * LPS22HB odr are 10, 25, 50 and 75 must be remapped to LSM6DSM ODR
     */
    test_6dsl_press.odr_hz_val = LPS22HB_ODR_LSB_TO_HZ(test_6dsl_press.odr);
    test_6dsl_press.odr_hz_val = lsm6dsm_normalize_odr(test_6dsl_press.odr_hz_val);

    *max_odr = MAX_ODR(*max_odr, test_6dsl_press.odr_hz_val);
    *min_odr = MIN_ODR(*min_odr, test_6dsl_press.odr_hz_val);
  }

  /*
   * Calculate how many samples for each sensor are in current FIFO pattern
   */
  if (test_6dsl_gyro.enable)
  {
    test_6dsl_gyro.samples_num_in_pattern = test_6dsl_gyro.odr_hz_val / *min_odr;
    test_6dsl_gyro.decimation =  *max_odr / test_6dsl_gyro.odr_hz_val;
    fifo_samples_tot_num += (OUT_XYZ_SIZE * test_6dsl_gyro.samples_num_in_pattern);
  }

  if (test_6dsl_xl.enable)
  {
    test_6dsl_xl.samples_num_in_pattern = test_6dsl_xl.odr_hz_val / *min_odr;
    test_6dsl_xl.decimation =  *max_odr / test_6dsl_xl.odr_hz_val;
    fifo_samples_tot_num += (OUT_XYZ_SIZE * test_6dsl_xl.samples_num_in_pattern);
  }

  if (test_6dsl_mag.enable)
  {
    test_6dsl_mag.samples_num_in_pattern = test_6dsl_mag.odr_hz_val / *min_odr;
    test_6dsl_mag.decimation =  *max_odr / test_6dsl_mag.odr_hz_val;
    fifo_samples_tot_num += (OUT_XYZ_SIZE * test_6dsl_mag.samples_num_in_pattern);
  }

  if (test_6dsl_press.enable)
  {
    test_6dsl_press.samples_num_in_pattern = test_6dsl_press.odr_hz_val / *min_odr;
    test_6dsl_press.decimation =  *max_odr / test_6dsl_press.odr_hz_val;
    fifo_samples_tot_num += (OUT_XYZ_SIZE * test_6dsl_press.samples_num_in_pattern);
  }

  return fifo_samples_tot_num;
}

/*
 * Read data byte from internal register of a slave device connected
 * to master I2C interface
 */
static int32_t lsm6dsm_read_lps22hb_cx(void* ctx, uint8_t reg, uint8_t* data,
        uint16_t len)
{
  int32_t mm_error;
  uint8_t drdy;
  lsm6dsm_func_src1_t func_src1;
  lsm6dsm_sh_cfg_read_t val =
  {
    .slv_add = LPS22HB_I2C_ADD_H,
    .slv_subadd = reg,
    .slv_len = len,
  };

  (void)ctx;

  /*
   * Configure Sensor Hub to read LIS2MDL
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
    lsm6dsm_read_reg(&dev_ctx, LSM6DSM_FUNC_SRC1, (uint8_t *)&func_src1, 1);
  } while (!func_src1.sensorhub_end_op);

  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_OFF);
  lsm6dsm_sh_read_data_raw_get(&dev_ctx, (lsm6dsm_emb_sh_read_t*)&data);

  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_DISABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_DISABLE);

  return mm_error;
}

/*
 * Write data byte to internal register of a slave device connected
 * to master I2C interface
 */
static int32_t lsm6dsm_write_lps22hb_cx(void* ctx, uint8_t reg, uint8_t* data,
        uint16_t len)
{
  int32_t mm_error;
  uint8_t drdy;
  lsm6dsm_func_src1_t func_src1;
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
    lsm6dsm_read_reg(&dev_ctx, LSM6DSM_FUNC_SRC1, (uint8_t *)&func_src1, 1);
  } while (!func_src1.sensorhub_end_op);

  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_OFF);

  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_DISABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_DISABLE);

  return mm_error;
}

/*
 * Read data byte from internal register of a slave device connected
 * to master I2C interface
 */
static int32_t lsm6dsm_read_lis2mdl_cx(void* ctx, uint8_t reg, uint8_t* data,
        uint16_t len)
{
  int32_t mm_error;
  uint8_t drdy;
  lsm6dsm_func_src1_t func_src1;
  lsm6dsm_sh_cfg_read_t val = {
    .slv_add = LIS2MDL_I2C_ADD,
    .slv_subadd = reg,
    .slv_len = len,
  };

  (void)ctx;

  /*
   * Configure Sensor Hub to read LIS2MDL
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
    lsm6dsm_read_reg(&dev_ctx, LSM6DSM_FUNC_SRC1, (uint8_t *)&func_src1, 1);
  } while (!func_src1.sensorhub_end_op);

  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_OFF);
  lsm6dsm_sh_read_data_raw_get(&dev_ctx, (lsm6dsm_emb_sh_read_t*)&data);

  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_DISABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_DISABLE);

  return mm_error;
}

/*
 * Write data byte to internal register of a slave device connected
 * to master I2C interface
 */
static int32_t lsm6dsm_write_lis2mdl_cx(void* ctx, uint8_t reg, uint8_t* data,
        uint16_t len)
{
  int32_t mm_error;
  uint8_t drdy;
  lsm6dsm_func_src1_t func_src1;
  lsm6dsm_sh_cfg_write_t val = {
    .slv0_add = LIS2MDL_I2C_ADD,
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
    lsm6dsm_read_reg(&dev_ctx, LSM6DSM_FUNC_SRC1, (uint8_t *)&func_src1, 1);
  } while (!func_src1.sensorhub_end_op);

  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_OFF);

  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_DISABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_DISABLE);

  return mm_error;
}

/*
 * Configure LIS2MDL magnetometer sensor over I2C master line (Slave0)
 *
 * Enable LIS2MDL Magnetometer:
 * set continuous mode
 * set temperature compensation
 * enable BDU
 * set ODR to 50 Hz
 */
static void configure_lis2mdl(stmdev_ctx_t* ctx)
{
  lsm6dsm_sh_cfg_read_t val =
  {
    .slv_add = LIS2MDL_I2C_ADD,
    .slv_subadd = LIS2MDL_OUTX_L_REG,
    .slv_len = OUT_XYZ_SIZE,
  };

  lis2mdl_operating_mode_set(ctx, LIS2MDL_CONTINUOUS_MODE);
  lis2mdl_offset_temp_comp_set(ctx, PROPERTY_ENABLE);
  lis2mdl_block_data_update_set(ctx, PROPERTY_ENABLE);
  lis2mdl_data_rate_set(ctx, LIS2MDL_ODR_50Hz);

  /*
   * Prepare sensor hub to read data from external Slave0
   */
  lsm6dsm_sh_slv0_cfg_read(&dev_ctx, &val);
}

/*
 * Configure LPS22HB barometer sensor over I2C master line (Slave1)
 *
 * Enable LPS22HB barometer:
 * set ODR to 50 Hz
 * enable BDU
 */
static void configure_lps22hb(stmdev_ctx_t* ctx)
{
  lsm6dsm_sh_cfg_read_t val =
  {
    .slv_add = LPS22HB_I2C_ADD_H,
    .slv_subadd = LPS22HB_PRESS_OUT_XL,
    .slv_len = OUT_XYZ_SIZE,
  };

  lps22hb_data_rate_set(ctx, LPS22HB_ODR_50_Hz);
  lps22hb_block_data_update_set(ctx, PROPERTY_ENABLE);

  /*
   * Prepare sensor hub to read data from external Slave1
   */
  lsm6dsm_sh_slv1_cfg_read(&dev_ctx, &val);
}

/* Main Example --------------------------------------------------------------*/
void example_fifo_sensorhub_lps22hb_lis2mdl(void)
{
  //lsm6dsm_int1_route_t int_1_reg;
  //lsm6dsm_int2_route_t int_2_reg;
  uint16_t max_odr = 0, min_odr = 0xffff;

  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &hi2c1;

  /*
   * Configure low level function to access to external device
   */
  press_ctx.read_reg = lsm6dsm_read_lps22hb_cx;
  press_ctx.write_reg = lsm6dsm_write_lps22hb_cx;
  press_ctx.handle = &hi2c1;
  mag_ctx.read_reg = lsm6dsm_read_lis2mdl_cx;
  mag_ctx.write_reg = lsm6dsm_write_lis2mdl_cx;
  mag_ctx.handle = &hi2c1;

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
   * Check if LIS2MDL connected to Sensor Hub
   */
  lis2mdl_device_id_get(&mag_ctx, &whoamI);
  if (whoamI != LIS2MDL_ID)
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
   * Configure LIS2MDL on the I2C master line
   */
  configure_lis2mdl(&mag_ctx);

  /*
   * Configure Sensor Hub to read two slaves
   */
  lsm6dsm_sh_num_of_dev_connected_set(&dev_ctx, LSM6DSM_SLV_0_1);

  /*
   * Set XL full scale and Gyro full scale
   */
  lsm6dsm_xl_full_scale_set(&dev_ctx, test_6dsl_xl.fs);
  lsm6dsm_gy_full_scale_set(&dev_ctx, test_6dsl_gyro.fs);

  /*
   * Calculate number of sensors samples in each FIFO pattern
   */
  pattern_len = LSM6DSL_SH_Calculate_FIFO_Pattern(&min_odr, &max_odr);

  /*
   * Set FIFO watermark to a multiple of a pattern
   * in this example we set watermark to 10 pattern
   * which means ten sequence of:
   * (GYRO + XL + MAG + BARO_TEMP + XL + MAG + BARO_TEMP) = 42 bytes
   */
  lsm6dsm_fifo_watermark_set(&dev_ctx, 10 * pattern_len);

  /*
   * Set FIFO mode to Stream mode (aka Continuous Mode)
   */
  lsm6dsm_fifo_mode_set(&dev_ctx, LSM6DSM_STREAM_MODE);

  /*
   * Uncomment to enable FIFO watermark interrupt generation
   * on INT1 pin
   */
  //lsm6dsm_pin_int1_route_get(&dev_ctx, &int_1_reg);
  //int_1_reg.int1_fth = PROPERTY_ENABLE;
  //lsm6dsm_pin_int1_route_set(&dev_ctx, int_1_reg);

  /*
   * Uncomment to enable FIFO watermark interrupt generation
   * on INT2 pin
   */
  //lsm6dsm_pin_int2_route_get(&dev_ctx, &int_2_reg);
  //int_2_reg.int2_fth = PROPERTY_ENABLE;
  //lsm6dsm_pin_int2_route_set(&dev_ctx, int_2_reg);

  /*
   * Set FIFO sensor decimator
   */
  lsm6dsm_fifo_xl_batch_set(&dev_ctx, test_6dsl_xl.decimation);
  lsm6dsm_fifo_gy_batch_set(&dev_ctx, test_6dsl_gyro.decimation);
  lsm6dsm_fifo_dataset_3_batch_set(&dev_ctx, test_6dsl_mag.decimation);
  lsm6dsm_fifo_dataset_4_batch_set(&dev_ctx, test_6dsl_press.decimation);

  /*
   * Enable master and XL trigger
   */
  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_ENABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_ENABLE);

  /*
   * Set ODR FIFO
   */
  lsm6dsm_fifo_data_rate_set(&dev_ctx, LSM6DSM_FIFO_416Hz);

  /*
   * Set XL and Gyro Output Data Rate
   */
  lsm6dsm_xl_data_rate_set(&dev_ctx, test_6dsl_xl.odr);
  lsm6dsm_gy_data_rate_set(&dev_ctx, test_6dsl_gyro.odr);

  while(1)
  {
    uint8_t wt;

    /*
     * Read FIFO watermark flag in polling mode
     */
    lsm6dsm_fifo_wtm_flag_get(&dev_ctx, &wt);
    if (wt)
    {
      LSM6DSL_SH_ACC_GYRO_MAG_PRESS_sample_Callback_fifo();
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
