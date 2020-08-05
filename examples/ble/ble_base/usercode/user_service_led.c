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
#include "bx_service_gpio.h"

#include "user_service_led.h"

/* config --------------------------------------------------------------------*/
#define LED0_PIN_NUM            2
#define LED1_PIN_NUM            5
#define LED2_PIN_NUM            6

#define LED_COUNT_MAX           3

#define LIGHT_LEVEL             1

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/


/* private variables ---------------------------------------------------------*/
static u8 led_hub[LED_COUNT_MAX] = {
    LED0_PIN_NUM,
    LED1_PIN_NUM,
    LED2_PIN_NUM
};

static s32  led_service_id;
/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/
static void led_open( void )
{
    s32 id = bxs_gpio_a_id();
    bx_call( id, BXM_OPEN, 0, 0 );
    for( u32 i = 0; i < LED_COUNT_MAX; i++ ) {
        bx_set( id, BXP_MODE, led_hub[i], BX_GPIO_MODE_OUTPUT );
    }
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
static int32_t led_write( u8 led_num, bool is_light )
{
    s32 id = bxs_gpio_a_id();
    if( is_light ) {
#if ( LIGHT_LEVEL == 1 )
        bx_call( id, BXM_WRITE, led_hub[led_num], 1 );
#else
        bx_call( id, BXM_WRITE, led_hub[led_num], 0 );
#endif
    } else {
#if ( LIGHT_LEVEL == 1 )
        bx_call( id, BXM_WRITE, led_hub[led_num], 0 );
#else
        bx_call( id, BXM_WRITE, led_hub[led_num], 1 );
#endif
    }
    return 0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int32_t led_toggle( u8 len_num )
{
    s32 id = bxs_gpio_a_id();
    bx_call( id, BXM_TOGGLE, led_hub[len_num], 0 );
    return 0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t led_msg_handle(s32 id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {

        case BXM_OPEN:
            led_open();
            break;

        case BXM_CLOSE:
            led_close();
            break;

        case BXM_WRITE:
            led_write( param0, param1 );
            break;

        case BXM_TOGGLE:
            led_toggle( param0 );
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
static bx_err_t led_property_set(s32 id, u32 property, u32 param0, u32 param1 )
{
    return BX_ERR_NOTSUP;
//    switch( property ) {
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
static bx_err_t led_property_get(s32 id, u32 property, u32 param0, u32 param1 )
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
bool user_service_led_init( void )
{
    struct bx_service svc;
    svc.name = "led service";
    svc.msg_handle_func = led_msg_handle;
    svc.prop_get_func = led_property_get;
    svc.prop_set_func = led_property_set;
    led_service_id = bx_register( &svc );
    if( led_service_id == -1 ) {
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
s32 user_service_led_id( void )
{
    return led_service_id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



