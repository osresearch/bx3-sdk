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

#include "user_service_button.h"

/* config --------------------------------------------------------------------*/
#define BUTTON_COUNT_MAX            3

//当按键按下时GPIO的值 1->high 0->low
#define IO_LEVEL_WHEN_BTN_DOWN      0

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct button {
    u8  pin_num;
    u32 sample;
};

/* private variables ---------------------------------------------------------*/
static struct button button_hub[] = {
    {15},
    {17},
};

static s32  button_service_id;
/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void button_open( void )
{
    s32 id = bxs_gpio_a_id();
    bx_call( id, BXM_OPEN, 0, 0 );

    for( u32 i = 0; i < BUTTON_COUNT_MAX; i++ ) {
#if ( IO_LEVEL_WHEN_BTN_DOWN == 0 )
        bx_set( id, BXP_MODE, button_hub[i].pin_num, BX_GPIO_MODE_IT_FALLING );
#else
        bx_set( id, BXP_MODE, button_hub[i].pin_num, BX_GPIO_MODE_IT_RISING );
#endif
    }
    
    //订阅消息
    bx_subscibe(id,BXM_GPIO_EXT_INTR,0,0);
    bx_subscibe(id,BXM_GPIO_INTR,0,0);

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void button_close( void )
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
static bx_err_t button_msg_handle( s32 id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {

        case BXM_OPEN:
            button_open();
            break;

        case BXM_CLOSE:
            button_close();
            break;
        
        case BXM_GPIO_EXT_INTR:
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
static bx_err_t led_property_set( s32 id, u32 property, u32 param0, u32 param1 )
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
static bx_err_t led_property_get( s32 id, u32 property, u32 param0, u32 param1 )
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
    svc.name = "button service";
    svc.msg_handle_func = led_msg_handle;
    svc.prop_get_func = led_property_get;
    svc.prop_set_func = led_property_set;
    button_service_id = bx_register( &svc );
    if( button_service_id == -1 ) {
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
s32 user_service_button_id( void )
{
    return button_service_id;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



