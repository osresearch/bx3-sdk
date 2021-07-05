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
#ifndef __BX_POWER_MANAGER_H__
#define __BX_POWER_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/
#define BX_PM_ADC                                       ( ( ( u32 ) 0x01UL ) << 0 )
#define BX_PM_GPIO                                      ( ( ( u32 ) 0x01UL ) << 1 )
#define BX_PM_IIC                                       ( ( ( u32 ) 0x01UL ) << 2 )
#define BX_PM_PWM                                       ( ( ( u32 ) 0x01UL ) << 3 )
#define BX_PM_SPIM                                      ( ( ( u32 ) 0x01UL ) << 4 )
#define BX_PM_TIM                                       ( ( ( u32 ) 0x01UL ) << 5 )
#define BX_PM_UART                                      ( ( ( u32 ) 0x01UL ) << 6 )
#define BX_PM_WDT                                       ( ( ( u32 ) 0x01UL ) << 7 )
#define BX_PM_FLASH                                     ( ( ( u32 ) 0x01UL ) << 8 )
#define BX_PM_ALL                                       ( 0xFFFFFFFF )

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void     bx_pm_lock( u32 flag );
void     bx_pm_unlock( u32 flag );
bool     bx_pm_check( u32 flag );

#ifdef __cplusplus
}
#endif

#endif /* __BX_POWER_MANAGER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
