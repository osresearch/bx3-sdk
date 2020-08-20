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

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void sysctrl_pwr_3v2_drv_capability_maintain(bool enable);
bool sysctrl_pwr_pwm_2_sleep_en_get(void);
void sysctrl_io_init(void);
void sysctrl_awo_init(void);
void sysctrl_32k_clk_init(void);
void sysctrl_set_ahb_apb_blemac_clk(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSCTRL_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
