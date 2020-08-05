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
#ifndef __BX_DRV_WDT_H__
#define __BX_DRV_WDT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_wdt_type_def.h"
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


bx_err_t    bx_drv_wdt_set_mode(void * hdl ,u8 mode);

bx_err_t    bx_drv_wdt_open(void * hdl );
bx_err_t    bx_drv_wdt_close(void * hdl );

bx_err_t    bx_drv_wdt_start( void * hdl, u32 time);
bx_err_t    bx_drv_wdt_stop( void * hdl );
bx_err_t    bx_drv_wdt_feed( void * hdl );

#ifdef __cplusplus
}
#endif

#endif /* __BX_DRV_WDT_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

