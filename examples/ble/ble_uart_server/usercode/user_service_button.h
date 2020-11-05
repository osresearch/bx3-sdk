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
#ifndef __USER_SERVICE_BUTTON_H__
#define __USER_SERVICE_BUTTON_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"

/* exported paras ------------------------------------------------------------*/
#define    SCAN_TIME_MS			        50
#define    BUTTON_MAX_DELAY_MS			( 4500 + SCAN_TIME_MS )


#define BUTTON_GPIO_PIN0    15
#define BUTTON_GPIO_PIN1    17

/* exported types ------------------------------------------------------------*/
enum user_property_button {
    USP_BTN_FIRST = BXP_FIRST_USER_PROP,


};

enum user_msg_button{
    USM_BTN_FIRST = BXM_FIRST_USER_MSG,
    
    USM_BTN_CLICK,
    USM_BTN_DOUBLE_CLICK,
    USM_BTN_CLICK_MORE,
    USM_BTN_PRESS_SHORT_START,
    USM_BTN_PRESS_SHORT_UP,
    USM_BTN_PRESS_LONG_START,
    USM_BTN_PRESS_LONG_UP,
    USM_BTN_PRESS_LONG_HOLD,
    USM_BTN_PRESS_LONG_HOLD_UP,
    USM_BTN_PRESS_MAX,
    
    USM_BTN_DOWN,
    USM_BTN_UP,
};

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     user_service_button_register( void );
s32      user_service_button_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __USER_SERVICE_BUTTON_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
