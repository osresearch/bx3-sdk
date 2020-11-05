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

#include "bx_kernel.h"
#include "user_app.h"
#include "bx_shell.h"
#include "user_service_ble.h"
#include "user_profile_task.h"

#include "nvds_typedef.h"
#include "nvds_in_ram.h"

#include "bx_service_uart.h"
#include "bx_service_tim.h"

#include "gattc.h"

#include "bx_drv_ble.h"
#include "bx_pm.h"
#include "user_service_button.h"
#include "bx_service_gpio.h"
/* private define ------------------------------------------------------------*/

#define UART_TX_PIN     12
#define UART_RX_PIN     13

#define RX_MAX_NOTIFY_LEN        240

#define TXRX_TIMR_OUT   10//uint:ms


static u8 rx_buff[2048];
static u8 tx_buff[2048];

static u8 rx_data[250];
static u8 tx_data[250];

static u8 notify_start = 0;
static u8 serialApp_start = 0;

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
void user_init( void )
{
    
    bxs_tim_register();

    bxs_uart_register();

    us_ble_register();

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void user_app( void )
{

    //¶©ÔÄTIM0ÖÐ¶ÏÏûÏ¢
    bx_subscibe( bxs_tim0_id(), BXM_TIM0_INTR, 0, 0 );

    bx_subscibe( us_ble_id(), BXM_BLE_READY, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_ADVERTISING, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_CONNECTED, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_DISCONNECTED, 0, 0 );

    bx_subscibe( us_ble_id(), BXM_BLE_NOTIFY_END, 0, 0 );
    bx_subscibe( bxs_uart1_id(), BXM_DATA_TX_END, 0, 0 );

    bx_subscibe( bxs_uart1_id(), BXM_DATA_RECEIVED_TIMEOUT, 0, 0 );
    bx_subscibe( bxs_uart1_id(), BXM_DATA_TRANSMIT_TIMEOUT, 0, 0 );

}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_ble_msg_handle_func( u32 src_id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {
        case BXM_BLE_READY:
            bxsh_logln( "BXM_BLE_READY" );
            bx_post( src_id, BXM_BLE_ADV_START, 0, 0 );
            break;

        case BXM_BLE_ADVERTISING:
            bxsh_logln( "BXM_BLE_ADVERTISING" );
            break;

        case BXM_BLE_CONNECTED:
            bx_call( bxs_uart1_id(), BXM_OPEN, 0, 0 );
            bx_set( bxs_uart1_id(), BXP_UART_TX_PIN, UART_TX_PIN, 0 );
            bx_set( bxs_uart1_id(), BXP_UART_RX_PIN, UART_RX_PIN, 0 );

            bx_set( bxs_uart1_id(), BXP_DATA_BIT, BX_UART_DB_8B, 0 );
            bx_set( bxs_uart1_id(), BXP_SPEED, BX_UART_BD_115200, 0 );
            bx_set( bxs_uart1_id(), BXP_UART_STOP_BIT, BX_UART_SB_ONE, 0 );
            bx_set( bxs_uart1_id(), BXP_UART_PARITY, BX_UART_PARITY_NONE, 0 );


            bx_set( us_ble_id(), BXP_BLE_NOTIFY_HANDLE, 36, 0 );

            bx_set( bxs_uart1_id(), BXP_UART_RXBUFF, ( u32 )rx_buff, 2048 );

            bx_set( bxs_uart1_id(), BXP_UART_TXBUFF, ( u32 )tx_buff, 2048 );
            bx_post( bxs_uart1_id(), BXM_READ_START, 0, 0 );
            bxsh_logln( "BXM_BLE_CONNECTED" );
            bx_pm_lock( BX_PM_ALL );
            break;

        case BXM_BLE_DISCONNECTED:
            bxsh_logln( "BXM_BLE_DISCONNECTED" );
            bx_post( src_id, BXM_BLE_ADV_START, 0, 0 );

            bx_call( bxs_uart1_id(), BXM_CLOSE, 0, 0 );
            bx_pm_unlock( BX_PM_ALL );
            break;
        case BXM_BLE_NOTIFY_END:
            notify_start = param0;
            break;

        default:
            break;
    }
    return BX_OK;
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_uart1_msg_handle_func( u32 src_id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {
        case BXM_DATA_RECEIVED_TIMEOUT: {
            uint16_t notify_len;
            notify_len = param0;
            if( notify_len > ( gattc_get_mtu( 0 ) - 3 ) ) {
                bx_set( bxs_uart1_id(), BXP_DATA_TXRX_TIMEOUT, 1000, 0 );
                uart_rx_time_1ms = 1;
                if( ( gattc_get_mtu( 0 ) - 3 ) > RX_MAX_NOTIFY_LEN ) {
                    notify_len = RX_MAX_NOTIFY_LEN;
                } else {
                    notify_len = ( gattc_get_mtu( 0 ) - 3 );
                }
            } else {
                if( notify_len > RX_MAX_NOTIFY_LEN ) {
                    bx_set( bxs_uart1_id(), BXP_DATA_TXRX_TIMEOUT, 1000, 0 );
                    uart_rx_time_1ms = 1;
                    notify_len = RX_MAX_NOTIFY_LEN;
                }
            }
            bx_get( bxs_uart1_id(), BXP_RECEIVED_DATA, &rx_data[0], notify_len );

            notify_start = 1;
            bx_call( us_ble_id(), BXM_BLE_NOTIFY, ( u32 )&rx_data[0], notify_len );
        }
        break;

        case BXM_DATA_TRANSMIT_TIMEOUT: {
            bx_get( bxs_uart1_id(), BXP_TRANSMIT_DATA, &tx_data[0], param0 );
            serialApp_start = 1;
            bx_call( bxs_uart1_id(), BXM_WRITE, ( u32 )&tx_data[0], param0 );
        }

        break;

        case BXM_DATA_TX_END:
            serialApp_start = 0;
            break;

        default:
            break;
    }
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_tim0_msg_handle_func( u32 src_id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {
        case BXM_TIM0_INTR: {
            if( uart_rx_time_1ms != 0 ) {
                uart_rx_time_1ms++;
            }

            if( uart_tx_time_1ms != 0 ) {
                uart_tx_time_1ms++;
            }

            if ( ( uart_rx_time_1ms > TXRX_TIMR_OUT ) && ( !notify_start ) ) {
                bx_call( bxs_tim0_id(), BXM_CLOSE, 0, 0 );
                uart_rx_time_1ms = 0;
                bx_call( bxs_uart1_id(), BXM_DATA_RECEIVED, 0, 0 );
            }

            if ( ( uart_tx_time_1ms > TXRX_TIMR_OUT ) && ( !serialApp_start ) ) {
                bx_call( bxs_tim0_id(), BXM_CLOSE, 0, 0 );
                uart_tx_time_1ms = 0;
                bx_call( bxs_uart1_id(), BXM_DATA_TRANSMIT, 0, 0 );
            }
        }
        break;

        default:
            break;
    }
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 )
{
    s32 msg_src = bx_msg_source();
    if(  msg_src == us_ble_id() ) {
        user_ble_msg_handle_func( msg_src, msg, param0, param1 );
    } else if ( msg_src == bxs_uart1_id() ) {
        user_uart1_msg_handle_func( msg_src, msg, param0, param1 );
    } else if ( msg_src == bxs_tim0_id() ) {
        user_tim0_msg_handle_func( msg_src, msg, param0, param1 );
    } 
    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



