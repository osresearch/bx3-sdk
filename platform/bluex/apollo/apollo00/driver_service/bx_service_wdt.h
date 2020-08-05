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
#ifndef __BX_SERVICE_WDT_H__
#define __BX_SERVICE_WDT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
#include "bx_wdt_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/



enum bx_property_wdt {
    BXP_WDT_FIRST = BXP_FIRST_USER_PROP,
    
};

enum bx_msg_wdt{
    BXM_WDT_FIRST = BXM_FIRST_USER_MSG,
    
    BXM_WDT_FEED,
};
/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t bxs_wdt_init( void );
s32      bxs_wdt_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __BX_SERVICE_WDT_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
