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
#ifndef __BX_DRV_TIM_H__
#define __BX_DRV_TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_tim_type_def.h"
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t    bx_drv_timer_open(void * hdl );
bx_err_t    bx_drv_timer_close(void * hdl );

bx_err_t    bx_drv_timer_start( void * hdl, u32 periode_us );

#ifdef __cplusplus
}
#endif

#endif /* __BX_DRV_TIM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

