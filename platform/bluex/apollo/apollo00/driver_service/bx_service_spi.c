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
#include "bx_service_spi.h"
#include "bx_drv_spim.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bx_spim_service {
    s32 id;
    void * handle;
    
};

/* private variables ---------------------------------------------------------*/
static struct bx_spim_service spim0_svc = { 0 };
static struct bx_spim_service spim1_svc = { 0 };

/* exported variables --------------------------------------------------------*/

/* private define ------------------------------------------------------------*/
#define GET_SPIM_SERVICE_BY_ID( p_svc, svc_id )                 \
do{                                                             \
    if( ( svc_id ) == spim0_svc.id ) {                          \
        p_svc = &spim0_svc;                                     \
    } else if( ( svc_id ) == spim1_svc.id ) {                   \
        p_svc = &spim1_svc;                                     \
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
static bx_err_t spim_msg_handle(s32 id, u32 msg, u32 param0, u32 param1 )
{
    struct bx_spim_service * p_svc;
    GET_SPIM_SERVICE_BY_ID( p_svc, id );
    
    struct bx_spim_txrx_config * p_cfg = (struct bx_spim_txrx_config *)param0;
    
    switch( msg ) {
        case BXM_OPEN:
            return bx_drv_spim_open(p_svc->handle);
        
        case BXM_CLOSE:
            return bx_drv_spim_close(p_svc->handle);
        
        case BXM_READ:
            return bx_drv_spim_read(p_svc->handle,(u8 *)param0,param1);
        
        case BXM_WRITE:
            return bx_drv_spim_write(p_svc->handle,(u8 *)param0,param1);
        
        case BXM_SPIM_TXRX_START:
            bx_drv_spim_transmit_recieve(   p_svc->handle,  \
                                            p_cfg->tx_buff, \
                                            p_cfg->tx_len,  \
                                            p_cfg->rx_buff, \
                                            p_cfg->rx_len );
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
static bx_err_t spim_property_set(s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bx_spim_service * p_svc;
    GET_SPIM_SERVICE_BY_ID( p_svc, id );
    
    switch( property ) {
        case BXP_SPIM_CS1_PIN:
            return bx_drv_spim_set_cs1_pin(p_svc->handle,param0);
        
        case BXP_SPIM_USE_CS_NUM:
            return bx_drv_spim_use_cs(p_svc->handle,param0);
        
        case BXP_DATA_BIT:
            return bx_drv_spim_set_data_bit(p_svc->handle,param0);
        
        case BXP_SPEED:
            return bx_drv_spim_set_speed(p_svc->handle,param0);
        
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
static bx_err_t spim_property_get(s32 id, u32 property, u32 param0, u32 param1 )
{
    return BX_ERR_NOTSUP;
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
bx_err_t bxs_spim_register( void )
{
    struct bx_service svc;
    svc.name = "spim0 service";
    svc.msg_handle_func = spim_msg_handle;
    svc.prop_get_func = spim_property_get;
    svc.prop_set_func = spim_property_set;
    spim0_svc.id = bx_register( &svc );
    if( spim0_svc.id == -1 ) {
        return BX_ERR_NOMEM;
    }
    spim0_svc.handle = BX_SPIM0;
    
    svc.name = "spim1 service";
    svc.msg_handle_func = spim_msg_handle;
    svc.prop_get_func = spim_property_get;
    svc.prop_set_func = spim_property_set;
    spim1_svc.id = bx_register( &svc );
    if( spim1_svc.id == -1 ) {
        return BX_ERR_NOMEM;
    }
    spim1_svc.handle = BX_SPIM1;
    
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_spim0_id( void )
{
    return spim0_svc.id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_spim1_id( void )
{
    return spim1_svc.id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



