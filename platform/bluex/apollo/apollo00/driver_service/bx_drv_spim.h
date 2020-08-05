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
#ifndef __BX_DRV_SPIM_H__
#define __BX_DRV_SPIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_spi_type_def.h"
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


bx_err_t    bx_drv_spim_set_cs1_pin( void * hdl, u8 pin_num );
bx_err_t    bx_drv_spim_use_cs( void * hdl, u8 cs_num );

bx_err_t    bx_drv_spim_set_speed( void * hdl, u32 speed_hz );
bx_err_t    bx_drv_spim_set_data_bit( void * hdl, u8 data_bit );


bx_err_t    bx_drv_spim_open( void * hdl );
bx_err_t    bx_drv_spim_close( void * hdl );

bx_err_t    bx_drv_spim_read( void * hdl,u8 * buff, u32 len );
bx_err_t    bx_drv_spim_write( void * hdl,u8 * buff, u32 len );

bx_err_t    bx_drv_spim_transmit_recieve(void * hdl, u8 * tx_data, u32 tx_len, u8 * rx_data, u32 rx_len );


#ifdef __cplusplus
}
#endif

#endif /* __BX_DRV_SPIM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

