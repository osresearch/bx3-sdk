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
#ifndef __BXD_SPIS_H__
#define __BXD_SPIS_H__

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


bx_err_t    bxd_spis_set_cs_pin( void * hdl, u8 pin_num );

bx_err_t    bxd_spis_set_data_bit( void * hdl, u8 data_bit );


bx_err_t    bxd_spis_open( void * hdl );
bx_err_t    bxd_spis_close( void * hdl );

bx_err_t    bxd_spis_read( void * hdl,u8 * buff, u32 len );
bx_err_t    bxd_spis_write( void * hdl,u8 * buff, u32 len );

bx_err_t    bxd_spis_transmit_recieve(void * hdl, u8 * tx_data, u32 tx_len, u8 * rx_data, u32 rx_len );

bx_err_t    bxd_spis_write_dma( void * hdl, u8 * tx_data, u32 tx_len,void (*cb)(void *),void *cb_param );

#ifdef __cplusplus
}
#endif

#endif /* __BXD_SPIS_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

