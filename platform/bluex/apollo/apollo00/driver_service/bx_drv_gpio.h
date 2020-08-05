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
#ifndef __BX_DRV_GPIO_H__
#define __BX_DRV_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_gpio_type_def.h"
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t    bx_drv_gpio_set_mode(void * hdl, u8 pin_num,u8 mode );
bx_err_t    bx_drv_gpio_set_pull(void * hdl, u8 pin_num,u8 pull );

bx_err_t    bx_drv_gpio_open(void * hdl );
bx_err_t    bx_drv_gpio_close(void * hdl );
bx_err_t    bx_drv_gpio_read(void * hdl,u32 * pin_value );
bx_err_t    bx_drv_gpio_write(void * hdl,u8 pin_num , u8 is_high);
bx_err_t    bx_drv_gpio_toggle(void * hdl,u8 pin_num );

#ifdef __cplusplus
}
#endif

#endif /* __BX_DRV_GPIO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

