/*
 ******************************************************************************
 * @file    sensor_hub_fifo_lis2mdl_passthrough_simple.c
 * @author  Sensors Software Solution Team
 * @brief   This file show the simplest way to read LIS2MDL mag
 *          connected to LSM6DSM I2C master interface (with FIFO support).
 *          Configure LIS2MDL using LSM6DSM pass-through feature
 *          (platform I2C only).
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

/* Private macro -------------------------------------------------------------*/
#if defined(NUCLEO_F411RE_X_NUCLEO_IKS01A2)
#define LSM6DSM_INT2_PIN GPIO_PIN_1
#define LSM6DSM_INT2_GPIO_PORT GPIOC
#define LSM6DSM_INT1_PIN GPIO_PIN_0
#define LSM6DSM_INT1_GPIO_PORT GPIOC
#else /* NUCLEO_F411RE_X_NUCLEO_IKS01A2 */
#define LSM6DSM_INT2_PIN GPIO_PIN_5
#define LSM6DSM_INT2_GPIO_PORT GPIOB
#define LSM6DSM_INT1_PIN GPIO_PIN_8
#define LSM6DSM_INT1_GPIO_PORT GPIOB
#endif /* NUCLEO_F411RE_X_NUCLEO_IKS01A2 */

/* Private variables ---------------------------------------------------------*/
axis3bit16_t data_raw_magnetic;
axis3bit16_t data_raw_acceleration;
axis3bit16_t data_raw_angular_rate;
float acceleration_mg[3];
float angular_rate_mdps[3];
float magnetic_mG[3];
uint8_t whoamI, rst;
static uint8_t tx_buffer[1000];
uint8_t slave_address = LSM6DSM_I2C_ADD_H;
stmdev_ctx_t dev_ctx;

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
static int32_t platform_read_int_pin(void);

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
  uint8_t saved_sa = slave_address;
  lis2mdl_reg_t reg;
  uint8_t whoamI;
  lsm6dsm_sh_cfg_read_t val =
  {
    .slv_add = LIS2MDL_I2C_ADD,
    .slv_subadd = LIS2MDL_OUTX_L_REG,
    .slv_len = 3 * sizeof(int16_t),
  };

  /*
   * Enable pass-through
   */
  lsm6dsm_sh_pass_through_set(ctx, PROPERTY_ENABLE);

  /*
   * Set new I2C address for LIS2MDL
   */
  slave_address = LIS2MDL_I2C_ADD;

  /*
   * Check if LIS2MDL connected to Sensor Hub
   */
  lsm6dsm_read_reg(ctx, LIS2MDL_WHO_AM_I, &whoamI, 1);
  if (whoamI != LIS2MDL_ID)
  {
    while(1)
    {
      /* manage here device not found */
    }
  }

  reg.byte = 0;
  reg.cfg_reg_a.md = LIS2MDL_CONTINUOUS_MODE;
  reg.cfg_reg_a.comp_temp_en = PROPERTY_ENABLE;
  reg.cfg_reg_a.odr = LIS2MDL_ODR_50Hz;
  lsm6dsm_write_reg(ctx, LIS2MDL_CFG_REG_A, &reg.byte, 1);

  reg.byte = 0;
  reg.cfg_reg_c.bdu = PROPERTY_ENABLE;
  lsm6dsm_write_reg(ctx, LIS2MDL_CFG_REG_C, &reg.byte, 1);

  /*
   * Restore LSM6DSM i2c address.
   */
  slave_address = saved_sa;

  lsm6dsm_sh_pass_through_set(ctx, PROPERTY_DISABLE);

  /*
   * Prepare sensor hub to read data from external Slave0.
   */
  lsm6dsm_sh_slv0_cfg_read(ctx, &val);
}

/* Main Example --------------------------------------------------------------*/
void example_sensor_hub_fifo_lis2mdl_passthrough_lsm6dsm(void)
{
  lsm6dsm_int1_route_t int_1_reg;
  uint16_t pattern_len;

  /*
   * Uncomment if interrupt generation on 6D INT2 pin
   */
  //lsm6dsm_int2_route_t int_2_reg;

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
   * Some hardware require to enable pull up on master I2C interface.
   */
  //lsm6dsm_sh_pin_mode_set(&dev_ctx, LSM6DSM_INTERNAL_PULL_UP);

  /*
   * Configure LIS2MDL on the I2C master line.
   */
  configure_lis2mdl(&dev_ctx);

  /*
   * Configure Sensor Hub to read one slave
   */
  lsm6dsm_sh_num_of_dev_connected_set(&dev_ctx, LSM6DSM_SLV_0);

  /*
   * Set XL full scale and Gyro full scale
   */
  lsm6dsm_xl_full_scale_set(&dev_ctx, LSM6DSM_2g);
  lsm6dsm_gy_full_scale_set(&dev_ctx, LSM6DSM_2000dps);

  /*
   * Enable Block Data Update (BDU) when FIFO support selected
   */
  lsm6dsm_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

  /*
   * Set FIFO watermark to a multiple of a pattern
   * in this example we set watermark to 10 pattern
   * which means ten sequence of:
   * (GYRO + XL + MAG) = 18 bytes.
   */
  pattern_len = 18;
  lsm6dsm_fifo_watermark_set(&dev_ctx, 10 * pattern_len);

  /*
   * Set FIFO mode to Stream mode (aka Continuous Mode)
   */
  lsm6dsm_fifo_mode_set(&dev_ctx, LSM6DSM_STREAM_MODE);

  /*
   * Enable FIFO watermark interrupt generation on INT1 pin
   */
  lsm6dsm_pin_int1_route_get(&dev_ctx, &int_1_reg);
  int_1_reg.int1_fth = PROPERTY_ENABLE;
  lsm6dsm_pin_int1_route_set(&dev_ctx, int_1_reg);

  /*
   * FIFO watermark interrupt on INT2 pin
   */
  //lsm6dsm_pin_int2_route_get(&dev_ctx, &int_2_reg);
  //int_2_reg.int2_fth = PROPERTY_ENABLE;
  //lsm6dsm_pin_int2_route_set(&dev_ctx, int_2_reg);

  /*
   * Set FIFO sensor decimator
   */
  lsm6dsm_fifo_xl_batch_set(&dev_ctx, LSM6DSM_FIFO_XL_NO_DEC);
  lsm6dsm_fifo_gy_batch_set(&dev_ctx, LSM6DSM_FIFO_GY_NO_DEC);
  lsm6dsm_fifo_dataset_3_batch_set(&dev_ctx, LSM6DSM_FIFO_DS3_NO_DEC);

  /*
   * Enable master and XL trigger
   */
  lsm6dsm_func_en_set(&dev_ctx, PROPERTY_ENABLE);
  lsm6dsm_sh_master_set(&dev_ctx, PROPERTY_ENABLE);

  /*
   * Set ODR FIFO
   */
  lsm6dsm_fifo_data_rate_set(&dev_ctx, LSM6DSM_FIFO_52Hz);

  /*
   * Set XL and Gyro Output Data Rate:
   * in this example we set 52 Hz for Accelerometer and
   * 52 Hz for Gyroscope
   */
  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_52Hz);
  lsm6dsm_gy_data_rate_set(&dev_ctx, LSM6DSM_GY_ODR_52Hz);

  while(1)
  {
    uint16_t num = 0;
    uint16_t num_pattern = 0;

    /*
     * Read LSM6DSM INT pin value
     */
    if (platform_read_int_pin())
    {
      /*
       * Read number of word in FIFO
       */
      lsm6dsm_fifo_data_level_get(&dev_ctx, &num);
      num_pattern = num / pattern_len;

      while (num_pattern-- > 0)
      {
        /*
         * Following the sensors ODR configuration, FIFO pattern is composed by
         * this sequence of samples: GYRO, XL, MAG
         */
        lsm6dsm_fifo_raw_data_get(&dev_ctx,
                                  data_raw_angular_rate.u8bit,
                                  3 * sizeof(int16_t));
        angular_rate_mdps[0] =
          lsm6dsm_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[0]);
        angular_rate_mdps[1] =
          lsm6dsm_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[1]);
        angular_rate_mdps[2] =
          lsm6dsm_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[2]);

        sprintf((char*)tx_buffer, "Angular rate [mdps]:%4.2f\t%4.2f\t%4.2f\r\n",
                angular_rate_mdps[0], angular_rate_mdps[1], angular_rate_mdps[2]);
        tx_com(tx_buffer, strlen((char const*)tx_buffer));

        lsm6dsm_fifo_raw_data_get(&dev_ctx,
                                  data_raw_acceleration.u8bit,
                                  3 * sizeof(int16_t));
        acceleration_mg[0] =
          lsm6dsm_from_fs2g_to_mg(data_raw_acceleration.i16bit[0]);
        acceleration_mg[1] =
          lsm6dsm_from_fs2g_to_mg(data_raw_acceleration.i16bit[1]);
        acceleration_mg[2] =
          lsm6dsm_from_fs2g_to_mg(data_raw_acceleration.i16bit[2]);

        sprintf((char*)tx_buffer, "Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
                acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
        tx_com(tx_buffer, strlen((char const*)tx_buffer));

        lsm6dsm_fifo_raw_data_get(&dev_ctx,
                                  data_raw_magnetic.u8bit,
                                  3 * sizeof(int16_t));
        magnetic_mG[0] =
          lis2mdl_from_lsb_to_mgauss(data_raw_magnetic.i16bit[0]);
        magnetic_mG[1] =
          lis2mdl_from_lsb_to_mgauss(data_raw_magnetic.i16bit[1]);
        magnetic_mG[2] =
          lis2mdl_from_lsb_to_mgauss(data_raw_magnetic.i16bit[2]);

        sprintf((char*)tx_buffer, "Mag [mG]:%4.2f\t%4.2f\t%4.2f\r\n",
                magnetic_mG[0], magnetic_mG[1], magnetic_mG[2]);
        tx_com(tx_buffer, strlen((char const*)tx_buffer));
      }
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
    HAL_I2C_Mem_Write(handle, slave_address, reg,
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
    HAL_I2C_Mem_Read(handle, slave_address, reg,
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

/*
 * Function to read external interrupt pin connected to LSM6DSM
 */
static int32_t platform_read_int_pin(void)
{
  return HAL_GPIO_ReadPin(LSM6DSM_INT1_GPIO_PORT, LSM6DSM_INT1_PIN);
  /*
   * Please uncomment next line if interrupt configured on INT2 pin
   */
  //return HAL_GPIO_ReadPin(LSM6DSM_INT2_GPIO_PORT, LSM6DSM_INT2_PIN);
}

