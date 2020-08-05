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
#define BX_PM_GPIO                                      ( ( ( u32 ) 0x01UL ) << 0 )
#define BX_PM_PWM                                       ( ( ( u32 ) 0x01UL ) << 1 )
#define BX_PM_UART                                      ( ( ( u32 ) 0x01UL ) << 2 )
#define BX_PM_TIM                                       ( ( ( u32 ) 0x01UL ) << 3 )
#define BX_PM_ALL                                       ( 0xFFFFFFFF )


#define BX_PM_MSG_LOCK                                  (BX_MSG_GENERATE(BX_SERVICE_T_POWER_MANAGER,0x0000))
#define BX_PM_MSG_UNLOCK                                (BX_MSG_GENERATE(BX_SERVICE_T_POWER_MANAGER,0x0001))

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     bxs_pm_init( void );
s32      bxs_pm_id( void );
bx_err_t bxs_pm_msg_handle(u32 msg, u32 param0, u32 param1);

void     bx_pm_init( void );
void     bx_pm_lock( u32 flag );
void     bx_pm_unlock( u32 flag );
bool     bx_pm_check( u32 flag );
#ifdef __cplusplus
}
#endif

#endif /* __BX_POWER_MANAGER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/