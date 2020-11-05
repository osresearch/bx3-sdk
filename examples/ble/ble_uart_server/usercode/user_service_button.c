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
#include "bx_drv_gpio.h"
#include "bx_shell.h"
#include "io_ctrl.h"

#include "bx_pm.h"
#include "flexible_button.h"

/* config --------------------------------------------------------------------*/
#define BUTTON_COUNT_MAX            3

//当按键按下时GPIO的值 1->high 0->low
#define IO_LEVEL_WHEN_BTN_DOWN      0

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
enum button_t {
    BTN_ID0,
    BTN_ID1,

    BTN_ID_MAX,
};
/* private variables ---------------------------------------------------------*/
static flex_button_t button_hub[BTN_ID_MAX] = {
    [BTN_ID0] = {.id = BUTTON_GPIO_PIN0},
    [BTN_ID1] = {.id = BUTTON_GPIO_PIN1},
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
static uint8_t common_btn_read( void * arg )
{
    uint8_t value = 0;

    flex_button_t * btn = ( flex_button_t * )arg;

    uint32_t pin_value;
    bx_drv_gpio_open( BX_GPIOA );
    bx_drv_gpio_read( BX_GPIOA, &pin_value );

    value = ( uint8_t )( ( pin_value >> btn->id ) & 0x01 );

    return value;
}

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

    io_ext_int_en( button_hub[0].id, 1 );
    io_ext_int_en( button_hub[1].id, 1 );

    bx_set( id, BXP_MODE, button_hub[0].id, BX_GPIO_MODE_INPUT );
    bx_set( id, BXP_MODE, button_hub[0].id, BX_GPIO_MODE_EIT_FALLING );
    bx_set( id, BXP_GPIO_PULL, button_hub[0].id, BX_GPIO_PULLUP );

    bx_set( id, BXP_MODE, button_hub[1].id, BX_GPIO_MODE_INPUT );
    bx_set( id, BXP_MODE, button_hub[1].id, BX_GPIO_MODE_EIT_FALLING );
    bx_set( id, BXP_GPIO_PULL, button_hub[1].id, BX_GPIO_PULLUP );


    for( u32 i = 0; i < BTN_ID_MAX; i++ ) {
        button_hub[i].usr_button_read = common_btn_read;
        //button_hub[0].cb = common_btn_evt_cb;
        button_hub[i].pressed_logic_level = 0;
        button_hub[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT( 1000 );
        button_hub[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT( 2500 );
        button_hub[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT( 4500 );
        flex_button_register( &button_hub[i] );
    }
    bx_subscibe( id, BXM_GPIO_EXT_INTR, 0, 0 );
    bx_subscibe( id, BXM_GPIO_INTR, 0, 0 );
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
        case BXM_GPIO_INTR:
            bx_repeat( id, USM_BTN_DOWN, 3, 0, SCAN_TIME_MS );
            bx_pm_lock( BX_PM_ALL );
            break;

        case USM_BTN_DOWN:
            flex_button_scan();
            break;


        case USM_BTN_UP:
            bx_cancel( id, USM_BTN_DOWN );
            bx_pm_unlock( BX_PM_ALL );
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
static bx_err_t button_property_set( s32 id, u32 property, u32 param0, u32 param1 )
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
static bx_err_t button_property_get( s32 id, u32 property, u32 param0, u32 param1 )
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
bool user_service_button_register( void )
{
    struct bx_service svc;
    svc.name = "button service";
    svc.msg_handle_func = button_msg_handle;
    svc.prop_get_func = button_property_get;
    svc.prop_set_func = button_property_set;
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



