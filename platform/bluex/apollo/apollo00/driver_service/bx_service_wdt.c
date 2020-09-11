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
#include "bx_service_wdt.h"
#include "bx_drv_wdt.h"
#include "bx_pm.h"
/* config --------------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bx_wdt_service {
    s32 id;
    void * handle;
    u32 open_count;
};

/* private variables ---------------------------------------------------------*/
static struct bx_wdt_service wdt_svc = { 0 };

/* exported variables --------------------------------------------------------*/

/* private define ------------------------------------------------------------*/

#define GET_WDT_SERVICE_BY_ID( p_svc, svc_id )          \
do{                                                     \
    if( ( svc_id ) == wdt_svc.id ) {                    \
        p_svc = &wdt_svc;                               \
    }else{                                              \
        return BX_ERR_NOTSUP;                           \
    }                                                   \
}while(0)

/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t wdt_msg_handle( s32 id, u32 msg, u32 param0, u32 param1 )
{
    struct bx_wdt_service * p_svc;
    GET_WDT_SERVICE_BY_ID( p_svc, id );

    switch( msg ) {
        case BXM_OPEN : {
            p_svc->open_count++;
            if( p_svc->open_count == 1 ) {
                bx_pm_lock( BX_PM_WDT );
                return bx_drv_wdt_open( p_svc->handle );
            }
            break;
        }

        case BXM_CLOSE : {
            p_svc->open_count--;
            if( p_svc->open_count == 0 ) {
                bx_pm_unlock( BX_PM_WDT );
                bx_drv_wdt_close( p_svc->handle );
            }
            break;
        }

        case BXM_START :
            bx_drv_wdt_start( p_svc->handle, param0 );
            break;

        case BXM_STOP :
            bx_drv_wdt_stop( p_svc->handle );
            break;

        case BXM_WDT_FEED :
            bx_drv_wdt_feed( p_svc->handle );
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
static bx_err_t wdt_property_set( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bx_wdt_service * p_svc;
    GET_WDT_SERVICE_BY_ID( p_svc, id );

    switch( property ) {
        case BXP_MODE:
            return bx_drv_wdt_set_mode( p_svc->handle, param0 );

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
static bx_err_t wdt_property_get( s32 id, u32 property, u32 param0, u32 param1 )
{
    return BX_ERR_NOTSUP;
//    struct bx_wdt_service * p_svc;
//    GET_WDT_SERVICE_BY_ID( p_svc, id );

//    switch( property ) {

//
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
bx_err_t bxs_wdt_register( void )
{
    struct bx_service svc;
    svc.name = "wdt service";
    svc.msg_handle_func = wdt_msg_handle;
    svc.prop_get_func = wdt_property_get;
    svc.prop_set_func = wdt_property_set;
    wdt_svc.id = bx_register( &svc );
    if( wdt_svc.id == -1 ) {
        return BX_ERR_NOMEM;
    }
    wdt_svc.handle = BX_WDT;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_wdt_id( void )
{
    return wdt_svc.id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



