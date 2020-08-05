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
#ifndef __BXSH_UART_H__
#define __BXSH_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* config --------------------------------------------------------------------*/
#include "bx_sdk3_config.h"

#if ( BX_UART_SHELL_ENABLE > 0 )
/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define uart_data_ready()   BX_READ_BIT( BX_UART0->LS, UART_LS_DATA_READY )
/* exported functions --------------------------------------------------------*/

void bxsh_uart_init( void );

void bxsh_uart_send_byte( uint8_t data);

uint8_t bxsh_uart_read_byte( void );

#else /* ( BX_UART_SHELL_ENABLE > 0 ) */

#define bxsh_uart_data_ready()                   ( ( void ) 0U )
#define bxsh_uart_init( )                        ( ( void ) 0U )
#define bxsh_uart_send_byte( data)               ( ( void ) 0U )
#define bxsh_uart_read_byte( )                   ( ( void ) 0U )

#endif /* ( BX_UART_SHELL_ENABLE > 0 ) */

#ifdef __cplusplus
}
#endif

#endif /* __BXSH_UART_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

