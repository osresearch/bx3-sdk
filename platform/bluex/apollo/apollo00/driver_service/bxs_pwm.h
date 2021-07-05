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
#ifndef __BXS_PWM_H__
#define __BXS_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
#include "bx_pwm_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/



enum bx_property_pwm {
    BXP_PWM_FIRST = BXP_FIRST_USER_PROP,
    
};

enum bx_msg_pwm{
    BXM_PWM_FIRST = BXM_FIRST_USER_MSG,
    
};
/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     bxs_pwm_register( void );
s32      bxs_pwm0_id( void );
s32      bxs_pwm1_id( void );
s32      bxs_pwm2_id( void );
s32      bxs_pwm3_id( void );
s32      bxs_pwm4_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __BXS_PWM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
