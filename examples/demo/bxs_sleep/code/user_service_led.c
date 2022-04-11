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
#include "user_service_led.h"

#include "bxs_gpio.h"

/* config --------------------------------------------------------------------*/
#define LED_PIN 2
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct us_led_service {
    s32 id;

};

/* private variables ---------------------------------------------------------*/
static struct us_led_service led_svc = {0};

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
#define GET_LED_SERVICE_BY_ID( p_svc, svc_id )                  \
do{                                                             \
    if( ( svc_id ) == led_svc.id ) {                            \
        p_svc = &led_svc;                                       \
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
static void led_open( void )
{
    s32 id = bxs_gpio_a_id();
    bx_call( id, BXM_OPEN, 0, 0 );
    bx_set( id, BXP_MODE, LED_PIN, BX_GPIO_MODE_OUTPUT );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void led_close( void )
{
    s32 id = bxs_gpio_a_id();
    bx_call( id, BXM_CLOSE, 0, 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int32_t led_write( bool is_light )
{
    s32 id = bxs_gpio_a_id();
    if( is_light ) {
        bx_call( id, BXM_WRITE, LED_PIN, 0 );
    } else {
        bx_call( id, BXM_WRITE, LED_PIN, 1 );
    }
    return 0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int32_t led_toggle( )
{
    s32 id = bxs_gpio_a_id();
    bx_call( id, BXM_TOGGLE, LED_PIN, 0 );
    return 0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t led_msg_handle(s32 svc_id, u32 msg, u32 param0, u32 param1 )
{
//    struct us_led_service * p_svc;
//    GET_LED_SERVICE_BY_ID( p_svc, svc_id );
    
    switch( msg ) {

        case BXM_OPEN:
            led_open();
            break;

        case BXM_CLOSE:
            led_close();
            break;

        case BXM_WRITE:
            led_write( param0 );
            break;

        case BXM_TOGGLE:
            led_toggle( );
            break;

        default:
            return BX_ERROR;
    }
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t led_property_set(s32 svc_id, u32 property, u32 param0, u32 param1 )
{
//    struct us_led_service * p_svc;
//    GET_LED_SERVICE_BY_ID( p_svc, svc_id );
    
    switch( property ) {
        default:
            return BX_ERR_NOTSUP;
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t led_property_get(s32 svc_id, u32 property, u32 param0, u32 param1 )
{
//    struct us_led_service * p_svc;
//    GET_LED_SERVICE_BY_ID( p_svc, svc_id );
    
    switch( property ) {
        default:
            return BX_ERR_NOTSUP;
    }
}


/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool us_led_register( void )
{
    struct bx_service svc;
    svc.name = "led service";
    svc.msg_handle_func = led_msg_handle;
    svc.prop_get_func = led_property_get;
    svc.prop_set_func = led_property_set;
    led_svc.id = bx_register( &svc );
    if( led_svc.id == -1 ) {
        return false;
    }
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 us_led_id( void )
{
    return led_svc.id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

