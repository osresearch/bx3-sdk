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
#ifndef __APP_USER_PROFILE_H__
#define __APP_USER_PROFILE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "rwip_config.h"     // SW Configuration

#include <stdint.h>
/* config --------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
/// Table of message handlers
extern const struct ke_state_handler app_user_profile_table_handler;
/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/
void app_user_profile_init(void);
void app_user_profile_add_profile(void);


#ifdef __cplusplus
}
#endif

#endif /* __APP_USER_PROFILE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
