/**
  ******************************************************************************
  * @file   :   .c
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
#include "bxs_uart.h"
#include "bxd_uart.h"
#include "bx_pm.h"

#include "bx_fifo.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bxs_uart {
    s32 id;
    void * handle;

    struct bx_fifo rx_fifo;
    struct bx_fifo tx_fifo;
};
/* private variables ---------------------------------------------------------*/
static struct bxs_uart uart0_svc = { 0 };
static struct bxs_uart uart1_svc = { 0 };

/* exported variables --------------------------------------------------------*/

/* private define ------------------------------------------------------------*/
#define GET_UART_SERVICE_BY_ID( p_svc, svc_id )                 \
do{                                                             \
    if( ( svc_id ) == uart0_svc.id ) {                          \
        p_svc = &uart0_svc;                                     \
    } else if( ( svc_id ) == uart1_svc.id ) {                   \
        p_svc = &uart1_svc;                                     \
    } else {                                                    \
        return BX_ERR_NOTSUP;                                   \
    }                                                           \
}while(0)


/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t uart_msg_handle( s32 id, u32 msg, u32 param0, u32 param1 )
{
    struct bxs_uart * p_svc;
    GET_UART_SERVICE_BY_ID( p_svc, id );

    switch( msg ) {
        case BXM_OPEN: {
            bx_pm_lock( BX_PM_UART );
            return bxd_uart_open( p_svc->handle );
        }
        case BXM_CLOSE: {
            bx_pm_unlock( BX_PM_UART );
            return bxd_uart_close( p_svc->handle );
        }
        case BXM_READ:
            return bxd_uart_read( p_svc->handle, ( u8 * )param0, param1 );

        case BXM_WRITE: {
            if( p_svc->tx_fifo.data != 0 ) {
                bx_post( p_svc->id, BXM_WRITE_START, 0, 0 );
                return bx_fifo_push( &( p_svc->tx_fifo ), ( u8 * )param0, param1 ) ? BX_OK : BX_ERR_NOMEM;
            } else {
                return bxd_uart_write( p_svc->handle, ( u8 * )param0, param1 );
            }
        }

        case BXM_READ_START:
            bxd_uart_intr_read_start( p_svc->handle );
            break;

        case BXM_WRITE_START:
            while( bx_fifo_get_len( &p_svc->tx_fifo ) > 0 ) {
                u8 data;
                bx_fifo_pop( &( p_svc->tx_fifo ), &data, 1 );
                bxd_uart_write( p_svc->handle, &data, 1 );
            }
            break;

        case BXM_DATA_RECEIVED: {
            uint32_t len = bx_fifo_get_len( &p_svc->rx_fifo );
            if(  bx_fifo_get_len( &p_svc->rx_fifo ) > 0 ) {
                bx_public( id, BXM_DATA_RECEIVED, len, 0 );
            }
        }
        break;

        default:
            return BX_ERR_NOTSUP;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t uart_property_set( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bxs_uart * p_svc;
    GET_UART_SERVICE_BY_ID( p_svc, id );

    switch( property ) {
        case BXP_UART_TX_PIN:
            return bxd_uart_set_tx_pin( p_svc->handle, param0 );

        case BXP_UART_RX_PIN:
            return bxd_uart_set_rx_pin( p_svc->handle, param0 );

        case BXP_UART_CTS_PIN:
            return bxd_uart_set_cts_pin( p_svc->handle, param0 );

        case BXP_UART_RTS_PIN:
            return bxd_uart_set_rts_pin( p_svc->handle, param0 );

        case BXP_UART_PARITY:
            return bxd_uart_set_parity( p_svc->handle, param0 );

        case BXP_UART_STOP_BIT:
            return bxd_uart_set_stop_bit( p_svc->handle, param0 );

        case BXP_DATA_BIT:
            return bxd_uart_set_data_bit( p_svc->handle, param0 );

        case BXP_SPEED:
            return bxd_uart_set_speed( p_svc->handle, param0 );

        case BXP_UART_115200_8_1_N:
            bxd_uart_set_speed( p_svc->handle, BX_UART_BD_115200 );
            bxd_uart_set_data_bit( p_svc->handle, BX_UART_DB_8B );
            bxd_uart_set_stop_bit( p_svc->handle, BX_UART_SB_ONE );
            bxd_uart_set_parity( p_svc->handle, BX_UART_PARITY_NONE );
            break;

        case BXP_UART_RXBUFF:
            bx_fifo_init( &( p_svc->rx_fifo ), ( u8 * )param0, param1 );
            break;

        case BXP_UART_TXBUFF:
            bx_fifo_init( &( p_svc->tx_fifo ), ( u8 * )param0, param1 );
            break;

        default:
            return BX_ERR_NOTSUP;
    }
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t uart_property_get( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bxs_uart * p_svc;
    GET_UART_SERVICE_BY_ID( p_svc, id );

    switch( property ) {
        case BXP_RECEIVED_DATA:
            if( !bx_fifo_pop( &( p_svc->rx_fifo ), ( u8 * )param0, param1 ) ) {
                return BX_ERR_NOMEM;
            }
            bx_public( id, property, ( u32 )&param0, param1 );
            break;

        default:
            return BX_ERR_NOTSUP;
    }
    return BX_OK;
}


/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool bxs_uart_register( void )
{
    struct bx_service svc;
    svc.name = "uart0 service";
    svc.msg_handle_func = uart_msg_handle;
    svc.prop_get_func = uart_property_get;
    svc.prop_set_func = uart_property_set;
    uart0_svc.id = bx_register( &svc );
    if( uart0_svc.id == -1 ) {
        return false;
    }
    uart0_svc.handle = BX_UART0;
    svc.name = "uart1 service";
    svc.msg_handle_func = uart_msg_handle;
    svc.prop_get_func = uart_property_get;
    svc.prop_set_func = uart_property_set;
    uart1_svc.id = bx_register( &svc );
    if( uart1_svc.id == -1 ) {
        return false;
    }
    uart1_svc.handle = BX_UART1;
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_uart0_id( void )
{
    return uart0_svc.id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_uart1_id( void )
{
    return uart1_svc.id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//void UART0_IRQHandler( void )
//{
//    u8 irq_status = BX_READ_REG( BX_UART0->IF ) & 0x0F;

//    switch( irq_status ) {
//        case BX_UART_IRQ_RLS:
//        case BX_UART_IRQ_CT:
//        case BX_UART_IRQ_RDA: {
//            while( 1 == BX_READ_BIT( BX_UART0->LS, UART_LS_DATA_READY ) ) {
//                u8 data = BX_UART0->RTD;
//                bx_fifo_push( &( uart0_svc.rx_fifo ), &data, 1 );
//            }
//        }
//        break;

//        default:
//            break;
//    }
//}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//void UART1_IRQHandler( void )
//{
//    u8 irq_status = BX_READ_REG( BX_UART1->IF ) & 0x0F;

//    switch( irq_status ) {
//        case BX_UART_IRQ_RLS:
//        case BX_UART_IRQ_CT:
//        case BX_UART_IRQ_RDA: {
//            while( 1 == BX_READ_BIT( BX_UART1->LS, UART_LS_DATA_READY ) ) {
//                u8 data = BX_UART1->RTD;
//                bx_fifo_push( &( uart1_svc.rx_fifo ), &data, 1 );
//            }
//        }
//        break;

//        default:
//            break;
//    }
//}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



