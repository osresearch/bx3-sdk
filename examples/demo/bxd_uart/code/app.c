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
#include "bxs_uart.h"
#include "bx_pm.h"
#include "plf.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

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
    bxd_uart_set_tx_pin( BX_UART1, 5 );
    bxd_uart_set_rx_pin( BX_UART1, 6 );
    bxd_uart_set_data_bit( BX_UART1, BX_UART_DB_8B );
    bxd_uart_set_speed( BX_UART1, BX_UART_BD_115200 );
    bxd_uart_set_stop_bit( BX_UART1, BX_UART_SB_ONE );
    bxd_uart_set_parity( BX_UART1, BX_UART_PARITY_NONE );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void uart_receive( u32 data_len )
{
    u8 recvbuff[5];

    bxd_uart_read( BX_UART1, recvbuff, 5 );
    bx_delay_asm( 10000 );
    bxd_uart_write( BX_UART1, recvbuff, 5 );

}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



