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
#ifndef __SYSCTRL_H__
#define __SYSCTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
typedef struct
{
    uint32_t active_ie;
    uint32_t deep_sleep_ie;
    uint32_t util_io_mask;
    uint32_t util_io_ret_dir;
    uint32_t util_io_ret_val;
}io_mngt_t;

/* exported variables --------------------------------------------------------*/
extern io_mngt_t io_mngt;

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void sysctrl_pwr_3v2_drv_capability_maintain(bool enable);
bool sysctrl_pwr_pwm_2_sleep_en_get(void);
void sysctrl_io_config_mask(uint32_t mask,uint32_t config);
void sysctrl_io_config(uint8_t num,uint32_t config);
void sysctrl_io_init(void);
void sysctrl_awo_init(void);
void sysctrl_32k_clk_init(void);
void sysctrl_set_ahb_apb_blemac_clk(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSCTRL_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
