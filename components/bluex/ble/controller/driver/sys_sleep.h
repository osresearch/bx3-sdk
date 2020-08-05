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
#ifndef __SYS_SLEEP_H__
#define __SYS_SLEEP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
typedef enum
{
    sleep_low_power_clk,    /* !< sleep_low_power_clk   */
    wakeup_requested,       /* !< wakeup_requested      */
    active_clk              /* !< active_clk            */
}blemac_stat_t;

#if (defined(CFG_DYNAMIC_UPDATE)&&(CFG_DYNAMIC_UPDATE==1))
enum
{
    bat_update_io_level = 0,
    bat_update_low_volt,
    bat_update_max,
    temp_update_deri_calib = bat_update_max,
    temp_update_max
};

enum
{
    temp_neg_40,
    temp_neg_30,
    temp_neg_20,
    temp_neg_10,
    temp_0,
    temp_pos_10,
    temp_pos_20,
    temp_pos_30,
    temp_pos_40,
    temp_pos_50,
    temp_pos_60,
    temp_pos_70,
    temp_pos_80,
    temp_highest
};

typedef void (*dynamic_update_cb)(uint16_t);
#endif /* (defined(CFG_DYNAMIC_UPDATE)&&(CFG_DYNAMIC_UPDATE==1)) */

/* exported variables --------------------------------------------------------*/
extern blemac_stat_t mac_status;

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#if (defined(CFG_DYNAMIC_UPDATE)&&(CFG_DYNAMIC_UPDATE==1))
void sys_param_periodic_update_init(void);
void sys_param_periodic_update(void);
#endif /* (defined(CFG_DYNAMIC_UPDATE)&&(CFG_DYNAMIC_UPDATE==1)) */


void ble_lp_intr_clr(void);
void ble_lp_irq_disable(void);
void ble_lp_irq_enable(void);
void ble_soft_wakeup(void);
void ble_schedule(void);

uint8_t sleep_prepare_and_check(void);
void pre_deepsleep_processing_mp(void);
void post_deepsleep_processing_mp(void);

void wait_rtc_until(uint32_t target);
uint32_t get_real_rtc(void);

void sysctrl_close_32m_rc(void);
uint32_t enable_32m_rc(void);

void system_recovery(void);
void flash_recovery(void);

void switch_to_32m_xtal(uint32_t current_time);

void sleep_check(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYS_SLEEP_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

