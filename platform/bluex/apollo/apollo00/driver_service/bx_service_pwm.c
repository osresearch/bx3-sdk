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
#include "bx_service_pwm.h"
#include "bx_drv_pwm.h"
#include "bx_pm.h"
/* config --------------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bx_pwm_service {
    s32 id;
    void * handle;

    u8 pin_num;
};

/* private variables ---------------------------------------------------------*/
static struct bx_pwm_service pwm0_svc = { 0 };
static struct bx_pwm_service pwm1_svc = { 0 };
static struct bx_pwm_service pwm2_svc = { 0 };
static struct bx_pwm_service pwm3_svc = { 0 };
static struct bx_pwm_service pwm4_svc = { 0 };

/* exported variables --------------------------------------------------------*/

/* private define ------------------------------------------------------------*/

#define GET_PWM_SERVICE_BY_ID( p_svc, svc_id )          \
do{                                                     \
    if( ( svc_id ) == pwm0_svc.id ) {                   \
        p_svc = &pwm0_svc;                              \
    }else if( ( svc_id ) == pwm1_svc.id ) {             \
        p_svc = &pwm1_svc;                              \
    }else if( ( svc_id ) == pwm2_svc.id ) {             \
        p_svc = &pwm2_svc;                              \
    }else if( ( svc_id ) == pwm3_svc.id ) {             \
        p_svc = &pwm3_svc;                              \
    }else if( ( svc_id ) == pwm4_svc.id ) {             \
        p_svc = &pwm4_svc;                              \
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
static bx_err_t pwm_msg_handle( s32 id, u32 msg, u32 param0, u32 param1 )
{
    struct bx_pwm_service * p_svc;
    GET_PWM_SERVICE_BY_ID( p_svc, id );

    switch( msg ) {
        case BXM_OPEN : {
            bx_pm_lock( BX_PM_PWM );
            return bx_drv_pwm_open( p_svc->handle );
        }

        case BXM_CLOSE : {
            bx_pm_unlock( BX_PM_PWM );
            return bx_drv_pwm_close( p_svc->handle );
        }

        case BXM_START :
            bx_drv_pwm_start( p_svc->handle, param0, param1 );
            break;

        case BXM_STOP :
            bx_drv_pwm_stop( p_svc->handle );
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
static bx_err_t pwm_property_set( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bx_pwm_service * p_svc;
    GET_PWM_SERVICE_BY_ID( p_svc, id );
    bx_err_t err = BX_OK;
    switch( property ) {
        case BXP_PIN:
            err = bx_drv_pwm_set_pin( p_svc->handle, param0 );
            if( err == BX_OK ) {
                p_svc->pin_num = param0;
            }
            break;

        default:
            return BX_ERR_NOTSUP;
    }
    return err;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t pwm_property_get( s32 id, u32 property, u32 param0, u32 param1 )
{
    struct bx_pwm_service * p_svc;
    GET_PWM_SERVICE_BY_ID( p_svc, id );

    switch( property ) {
        case BXP_PIN:
            *( u8 * )param0 = p_svc->pin_num;
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
bool bxs_pwm_register( void )
{
    struct bx_service svc;
    svc.name = "pwm0 service";
    svc.msg_handle_func = pwm_msg_handle;
    svc.prop_get_func = pwm_property_get;
    svc.prop_set_func = pwm_property_set;
    pwm0_svc.id = bx_register( &svc );
    if( pwm0_svc.id == -1 ) {
        return false;
    }
    pwm0_svc.handle = BX_PWM0;

    svc.name = "pwm1 service";
    svc.msg_handle_func = pwm_msg_handle;
    svc.prop_get_func = pwm_property_get;
    svc.prop_set_func = pwm_property_set;
    pwm1_svc.id = bx_register( &svc );
    if( pwm1_svc.id == -1 ) {
        return false;
    }
    pwm1_svc.handle = BX_PWM1;

    svc.name = "pwm2 service";
    svc.msg_handle_func = pwm_msg_handle;
    svc.prop_get_func = pwm_property_get;
    svc.prop_set_func = pwm_property_set;
    pwm2_svc.id = bx_register( &svc );
    if( pwm2_svc.id == -1 ) {
        return false;
    }
    pwm2_svc.handle = BX_PWM2;

    svc.name = "pwm3 service";
    svc.msg_handle_func = pwm_msg_handle;
    svc.prop_get_func = pwm_property_get;
    svc.prop_set_func = pwm_property_set;
    pwm3_svc.id = bx_register( &svc );
    if( pwm3_svc.id == -1 ) {
        return false;
    }
    pwm3_svc.handle = BX_PWM3;

    svc.name = "pwm3 service";
    svc.msg_handle_func = pwm_msg_handle;
    svc.prop_get_func = pwm_property_get;
    svc.prop_set_func = pwm_property_set;
    pwm4_svc.id = bx_register( &svc );
    if( pwm4_svc.id == -1 ) {
        return false;
    }
    pwm4_svc.handle = BX_PWM4;

    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_pwm0_id( void )
{
    return pwm0_svc.id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_pwm1_id( void )
{
    return pwm1_svc.id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_pwm2_id( void )
{
    return pwm2_svc.id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_pwm3_id( void )
{
    return pwm3_svc.id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_pwm4_id( void )
{
    return pwm4_svc.id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



