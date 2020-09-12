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
#ifndef __USER_APP_H__
#define __USER_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"

/* config --------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
extern s32 user_service_id;

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void user_init(void);
void user_app(void);

bx_err_t user_msg_handle_func(s32 svc, u32 msg,u32 param0,u32 param1 );

#ifdef __cplusplus
}
#endif

#endif /* __USER_APP_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
