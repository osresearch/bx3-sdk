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
#ifndef __USER_SERVICE_XXX_H__
#define __USER_SERVICE_XXX_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
enum user_property_XXX {
    USP_XXX_FIRST = BXP_FIRST_USER_PROP,
    
};

enum user_msg_XXX{
    USM_XXX_FIRST = BXM_FIRST_USER_MSG,
    
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     us_xxx_register( void );
s32      us_xxx_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __USER_SERVICE_XXX_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
