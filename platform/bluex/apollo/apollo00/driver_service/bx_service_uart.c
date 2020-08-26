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
#include "bx_service_uart.h"
#include "bx_drv_uart.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bx_uart_service {
    s32 id;
    void * handle;
    
};
/* private variables ---------------------------------------------------------*/
static struct bx_uart_service uart0_svc = { 0 };
static struct bx_uart_service uart1_svc = { 0 };

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
static bx_err_t uart_msg_handle(s32 id, u32 msg, u32 param0, u32 param1 )
{
    struct bx_uart_service * p_svc;
    GET_UART_SERVICE_BY_ID( p_svc, id );
    
    switch( msg ) {
        case BXM_OPEN:
            return bx_drv_uart_open(p_svc->handle);
        
        case BXM_CLOSE:
            return bx_drv_uart_close(p_svc->handle);
        
        case BXM_READ:
            return bx_drv_uart_read(p_svc->handle,(u8 *)param0,param1);
        
        case BXM_WRITE:
            return bx_drv_uart_write(p_svc->handle,(u8 *)param0,param1);

        default:
            return BX_ERR_NOTSUP;
    }
//    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t uart_property_set(s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bx_uart_service * p_svc;
    GET_UART_SERVICE_BY_ID( p_svc, id );
    
    switch( property ) {
        case BXP_UART_TX_PIN:
            return bx_drv_uart_set_tx_pin( p_svc->handle,param0 );
            
        case BXP_UART_RX_PIN:
            return bx_drv_uart_set_rx_pin( p_svc->handle,param0 );
        
        case BXP_UART_CTS_PIN:
            return bx_drv_uart_set_cts_pin( p_svc->handle,param0 );
        
        case BXP_UART_RTS_PIN:
            return bx_drv_uart_set_rts_pin( p_svc->handle,param0 );
        
        case BXP_UART_PARITY:
            return bx_drv_uart_set_parity( p_svc->handle,param0 );
        
        case BXP_UART_STOP_BIT:
            return bx_drv_uart_set_stop_bit( p_svc->handle,param0 );
        
        case BXP_DATA_BIT:
            return bx_drv_uart_set_data_bit( p_svc->handle,param0 );
        
        case BXP_SPEED:
            return bx_drv_uart_set_speed( p_svc->handle,param0 );
        
        case BXP_UART_115200_8_1_N:
            bx_drv_uart_set_speed( p_svc->handle,BX_UART_BD_115200 );
            bx_drv_uart_set_data_bit( p_svc->handle,BX_UART_DB_8B );
            bx_drv_uart_set_stop_bit( p_svc->handle,BX_UART_SB_ONE );
            bx_drv_uart_set_parity( p_svc->handle,BX_UART_PARITY_NONE );
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
static bx_err_t uart_property_get(s32 id, u32 property, u32 param0, u32 param1 )
{
    return BX_ERR_NOTSUP;
    
//    struct bx_uart_service * p_svc;
//    GET_UART_SERVICE_BY_ID( p_svc, id );
//    
//    switch( property ) {
//        default:
//            return BX_ERR_NOTSUP;
//    }
//    return BX_OK;
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

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



