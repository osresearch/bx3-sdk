/**
  ******************************************************************************
  * @file   :   .h
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RF_REG_SETTINGS_H__
#define __RF_REG_SETTINGS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* exported define -----------------------------------------------------------*/
#define PLL_48M                                         0x3
#define PLL_64M                                         0x4
#define PLL_80M                                         0x5
#define PLL_96M                                         0x6
//define for DCDC_OUTPUT setting
#define DCDC_OUTPUT_1V4                                 0x0
#define DCDC_OUTPUT_1V2                                 0x1
#define DCDC_OUTPUT_1V0                                 0x2
#define DCDC_OUTPUT_1V1                                 0x3

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/
void reg_config_touch(void);
bool reg_pll_lock(void);
void reg_pll_enable(uint8_t en);

void reg_set_pll(uint32_t freq);
void reg_wait_pll_stable(void);
void reg_set_xtal_current(uint32_t iboost_current,uint32_t xtal_current,uint32_t vboost,uint32_t iboost);
void reg_set_xtal_current_startup(void);
void reg_set_xtal_current_normal(void);

void rf_setting_differential_mode_adc(void);
void rf_setting_single_mode_adc(void);
void rf_setting_battery_monitor_adc(void);
void rf_setting_temperature_adc(void);
void rf_setPA_0dbm(void);
void rf_setPA_8dbm(void);

void rf_low_battery_config(void);
void rf_reg_adjust_bat(uint16_t);
void rf_reg_adjust_temp(int16_t);
void rf_reg_settings_init_mp(void);

#ifdef __cplusplus
}
#endif

#endif /* __RF_REG_SETTINGS_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
