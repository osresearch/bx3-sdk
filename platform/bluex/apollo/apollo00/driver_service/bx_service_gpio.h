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
#ifndef __BX_SERVICE_GPIO_H__
#define __BX_SERVICE_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
#include "bx_gpio_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/



enum bx_property_gpio {
    BXP_GPIO_FIRST = BXP_FIRST_USER_PROP,
    
    BXP_GPIO_PULL,
};

enum bx_msg_gpio {
    BXM_GPIO_FIRST = BXM_FIRST_USER_MSG,
    
    BXM_GPIO_INTR,
    BXM_GPIO_EXT_INTR,
    
};

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t bxs_gpio_register( void );
s32      bxs_gpio_a_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __BX_SERVICE_GPIO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
