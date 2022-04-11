/**
  ******************************************************************************
  * @file   :   .h
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) .
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_SVC_XXX_H__
#define __USER_SVC_XXX_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
/* config --------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

enum usm_xxx_def {
    USM_XXX_FIRST = BXM_FIRST_USER_MSG,
    
};

enum usp_xxx_def {
    USP_XXX_FIRST = BXP_FIRST_USER_PROP,
    
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool  us_xxx_register( void );

s32   us_xxx_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __USER_SVC_XXX_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
