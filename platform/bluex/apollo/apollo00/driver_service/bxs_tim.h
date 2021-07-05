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
#ifndef __BXS_TIM_H__
#define __BXS_TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
#include "bx_tim_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/



enum bx_property_tim {
    BXP_TIM_FIRST = BXP_FIRST_USER_PROP,
    
};

enum bx_msg_tim{
    BXM_TIM_FIRST = BXM_FIRST_USER_MSG,
    
    BXM_TIM0_INTR,
    BXM_TIM1_INTR,
};
/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     bxs_tim_register( void );
s32      bxs_tim0_id( void );
s32      bxs_tim1_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __BXS_TIM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
