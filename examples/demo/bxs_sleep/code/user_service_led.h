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
#ifndef __USER_SERVICE_LED_H__
#define __USER_SERVICE_LED_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
enum user_property_led {
    USP_LED_FIRST = BXP_FIRST_USER_PROP,
    
};

enum user_msg_led{
    USM_LED_FIRST = BXM_FIRST_USER_MSG,
    
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     us_led_register( void );
s32      us_led_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __USER_SERVICE_LED_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
