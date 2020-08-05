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
#include "bx_service_tim.h"
#include "bx_drv_tim.h"

/* config --------------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bx_timer_service {
    s32 id;
    void * handle;
};
/* private variables ---------------------------------------------------------*/
static struct bx_timer_service tim0_svc = { 0 };
static struct bx_timer_service tim1_svc = { 0 };

/* exported variables --------------------------------------------------------*/

/* private define ------------------------------------------------------------*/
#define GET_TIM_SERVICE_BY_ID( p_svc, svc_id )          \
do{                                                     \
    if( ( svc_id ) == tim0_svc.id ) {                   \
        p_svc = &tim0_svc;                              \
    }else if( ( svc_id ) == tim1_svc.id ) {             \
        p_svc = &tim1_svc;                              \
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
static bx_err_t tim_msg_handle( s32 id, u32 msg, u32 param0, u32 param1 )
{
    struct bx_timer_service * p_svc;
    GET_TIM_SERVICE_BY_ID( p_svc, id );

    switch( msg ) {
        case BXM_OPEN :
            bx_drv_timer_open( p_svc->handle );
            break;

        case BXM_CLOSE :
            bx_drv_timer_close( p_svc->handle );
            break;

        case BXM_START :
            bx_drv_timer_start( p_svc->handle, param0 );
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
static bx_err_t tim_property_set( s32 id, u32 property, u32 param0, u32 param1 )
{
    return BX_ERR_NOTSUP;
//    switch( property ) {
//        case BXP_HANDLE:
//            tim_svc.handle = (reg_timer_t *)param0;
//            break;
//
//        default:
//            return BX_ERR_NOTSUP;
//    }
//    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t tim_property_get( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bx_timer_service * p_svc;
    GET_TIM_SERVICE_BY_ID( p_svc, id );

    switch( property ) {
        case BXP_HANDLE:
            *( u32 * )param0 = ( u32 )( p_svc->handle );
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
bool bxs_tim_init( void )
{
    struct bx_service svc;
    svc.name = "tim0 service";
    svc.msg_handle_func = tim_msg_handle;
    svc.prop_get_func = tim_property_get;
    svc.prop_set_func = tim_property_set;
    tim0_svc.id = bx_register( &svc );
    if( tim0_svc.id == -1 ) {
        return false;
    }
    tim0_svc.handle = BX_TIM0;

    svc.name = "tim1 service";
    svc.msg_handle_func = tim_msg_handle;
    svc.prop_get_func = tim_property_get;
    svc.prop_set_func = tim_property_set;
    tim1_svc.id = bx_register( &svc );
    if( tim1_svc.id == -1 ) {
        return false;
    }
    tim1_svc.handle = BX_TIM1;
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_tim0_id( void )
{
    return tim0_svc.id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_tim1_id( void )
{
    return tim1_svc.id;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


