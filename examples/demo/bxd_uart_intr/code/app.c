/**
  ******************************************************************************
  * @file   :   main.c
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

/* includes ------------------------------------------------------------------*/
#include "app.h"
#include "bxd_uart.h"

#include "bx_pm.h"

/* private define ------------------------------------------------------------*/
#define RXFIFO_MAX_LEN      20480
#define TXFIFO_MAX_LEN      20480
/* private typedef -----------------------------------------------------------*/
static u8 rx_buff[RXFIFO_MAX_LEN];
static u8 tx_buff[TXFIFO_MAX_LEN];
/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
struct user_service us_svc = {0} ;

/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
void uart_callback( void * hd, u8 data )
{
    bx_fifo_push( &( us_svc.rx_fifo ), &data, 1 ) ;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    bx_pm_lock( BX_PM_UART );
    bxd_uart_open( BX_UART1 );
    bxd_uart_set_tx_pin( BX_UART1, 12 );
    bxd_uart_set_rx_pin( BX_UART1, 13 );
    bxd_uart_set_data_bit( BX_UART1, BX_UART_DB_8B );
    bxd_uart_set_speed( BX_UART1, BX_UART_BD_115200 );
    bxd_uart_set_stop_bit( BX_UART1, BX_UART_SB_ONE );
    bxd_uart_set_parity( BX_UART1, BX_UART_PARITY_NONE );

    bxd_uart_set_intr_callback( BX_UART1, uart_callback );
    bxd_uart_enable_intr( BX_UART1 );
    bxd_uart_intr_read_start( BX_UART1 );

    bx_fifo_init( &us_svc.rx_fifo, rx_buff, RXFIFO_MAX_LEN );
    bx_fifo_init( &us_svc.tx_fifo, tx_buff, TXFIFO_MAX_LEN );

    bx_dwork( uart_receive, NULL, 1000, BX_FOREVER );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void uart_receive( void * data )
{
    u8 rx_data[11520];

    us_svc.rx_len = bx_fifo_get_len( &( us_svc.rx_fifo ) );
    if( us_svc.rx_len > 0 ) {

        bx_fifo_pop( &( us_svc.rx_fifo ), rx_data, us_svc.rx_len );
        bxd_uart_write( BX_UART1, rx_data, us_svc.rx_len );
    }

}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



