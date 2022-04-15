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
#ifndef __BXD_PWM_H__
#define __BXD_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_pwm_type_def.h"
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


bx_err_t    bxd_pwm_set_pin( void * hdl, u8 pin_num );

bx_err_t    bxd_pwm_open( void * hdl );
bx_err_t    bxd_pwm_set_clock_div( u8 div );
bx_err_t    bxd_pwm_close( void * hdl );

bx_err_t    bxd_pwm_start( void * hdl, u32 freq, u8 duty );
bx_err_t    bxd_pwm_start2( void * hdl, u16 high, u16 low );

bx_err_t    bxd_pwm_stop( void * hdl );

#ifdef __cplusplus
}
#endif

#endif /* __BXD_PWM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

