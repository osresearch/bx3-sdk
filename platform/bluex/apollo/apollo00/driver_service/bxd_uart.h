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
#ifndef __BXD_UART_H__
#define __BXD_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_uart_type_def.h"
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/
enum bx_intr_id_uart{
	BX_UART_IRQ_MS = 0,     // modem status
	BX_UART_IRQ_NIP = 1,    // no interrupt pending
	BX_UART_IRQ_TE = 2,     // THR empty
	BX_UART_IRQ_RDA = 4,    // received data available
	BX_UART_IRQ_RLS = 6,    // receiver line status    
	BX_UART_IRQ_BD = 7,     // busy detect
	BX_UART_IRQ_CT = 12,    // character timeout
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t    bxd_uart_set_speed( void * hdl, u8 baudrate );
bx_err_t    bxd_uart_set_stop_bit( void * hdl, u8 stop_bit );
bx_err_t    bxd_uart_set_data_bit( void * hdl, u8 data_bit );
bx_err_t    bxd_uart_set_parity( void * hdl, u8 parity );
bx_err_t    bxd_uart_set_tx_pin( void * hdl, u8 pin_num );
bx_err_t    bxd_uart_set_rx_pin( void * hdl, u8 pin_num );
bx_err_t    bxd_uart_set_cts_pin( void * hdl, u8 pin_num );
bx_err_t    bxd_uart_set_rts_pin( void * hdl, u8 pin_num );

bx_err_t    bxd_uart_open( void * hdl );
bx_err_t    bxd_uart_close( void * hdl );

bx_err_t    bxd_uart_read( void * hdl, u8 * buff, u32 len );
bx_err_t    bxd_uart_write( void * hdl, u8 * buff, u32 len );

bx_err_t    bxd_uart_enable_intr( void * hdl );
bx_err_t    bxd_uart_disable_intr( void * hdl );

bx_err_t    bxd_uart_intr_write_start( void * hdl );
bx_err_t    bxd_uart_intr_read_start( void * hdl );
bx_err_t    bxd_uart_intr_read_stop( void * hdl );

#ifdef __cplusplus
}
#endif

#endif /* __BXD_UART_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

