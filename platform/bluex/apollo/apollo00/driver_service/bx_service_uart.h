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
#ifndef __BX_SERVICE_UART_H__
#define __BX_SERVICE_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
#include "bx_uart_type_def.h"
/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

enum bx_property_uart {
    BXP_UART_FIRST = BXP_FIRST_USER_PROP,
    
    BXP_UART_TX_PIN,
    BXP_UART_RX_PIN,
    BXP_UART_CTS_PIN,
    BXP_UART_RTS_PIN,
    
    BXP_UART_PARITY,
    BXP_UART_STOP_BIT,
    BXP_UART_115200_8_1_N,

    BXP_UART_RXBUFF,
    BXP_UART_TXBUFF,
    
};

enum bx_msg_uart{
    BXM_UART_FIRST = BXM_FIRST_USER_MSG,
    
    
    BXM_UART_RECEIVED_DATA,
};
/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     bxs_uart_register( void );
s32      bxs_uart0_id( void );
s32      bxs_uart1_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __BX_SERVICE_UART_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
