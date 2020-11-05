/**
  ******************************************************************************
  * @file   :   main.c
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
#include "user_app.h"
#include "bx_shell.h"
#include "user_service_ble.h"
#include "bx_pm.h"
#include <easyflash.h>
#include "app_sec.h"
#include "user_ble.h"
#include "bx_service_gpio.h"
#include "user_service_button.h"

#include "app_hid.h"
#include "hogpd_task.h"
#include "prf.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
/*============================= private function =============================*/

/*========================= end of private function ==========================*/
uint8_t notify_status = 0;

/*============================= exported function ============================*/


/** ---------------------------------------------------------------------------
 * @brief   :The keyboard to report
 * @note    :
 * @param   :key value
 * @retval  :
-----------------------------------------------------------------------------*/						
void hid_keyboard_sendreport( uint8_t keycode )
{
    uint8_t buf[8];

    buf[0] = 0;         // Modifier keys
    buf[1] = 0;         // Reserved
    buf[2] = keycode;   // Keycode 1
    buf[3] = 0;         // Keycode 2
    buf[4] = 0;         // Keycode 3
    buf[5] = 0;         // Keycode 4
    buf[6] = 0;         // Keycode 5
    buf[7] = 0;         // Keycode 6

    report_lenght = REPORT_LENGTH_ID2;
    report_id = REPORT_ID3;

    app_hid_send_keyboard_report( buf );

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void hid_mouse_sendreport( uint8_t buttons )
{
    uint8_t buf[8];

    buf[0] = buttons;   // Buttons
    buf[1] = 0;         // X
    buf[2] = 0;         // Y
    buf[3] = 0;         // Wheel
    buf[4] = 0;         // AC Pan

    report_lenght = 5;
    report_id = REPORT_ID2;

    app_hid_send_keyboard_report( buf );
}




/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void user_init( void )
{
    us_ble_register();

    bxs_gpio_register();
    user_service_button_register();

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void user_app( void )
{
    s32 id = user_service_button_id();
    bx_post( id, BXM_OPEN, 0, 0 );

    //订阅ble状态信息
    bx_subscibe( us_ble_id(), BXM_BLE_READY, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_ADVERTISING, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_CONNECTED, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_DISCONNECTED, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_BOND_SUCCEED, 0, 0 );

    //订阅button信息
    bx_subscibe( id, USM_BTN_CLICK, 0, 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_ble_msg_handle_func( u32 src_id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {
        case BXM_BLE_READY:
            bxsh_logln( "BXM_BLE_READY" );
            bx_post( src_id, BXM_BLE_ADV_START, 0, 0 );
            break;
        case BXM_BLE_ADVERTISING:
            bxsh_logln( "BXM_BLE_ADVERTISING" );
            break;
        case BXM_BLE_CONNECTED:
            bxsh_logln( "BXM_BLE_CONNECTED" );
            break;
        case BXM_BLE_DISCONNECTED:
			bx_pm_unlock( BX_PM_ALL );
            bxsh_logln( "BXM_BLE_DISCONNECTED" );
            bx_post( src_id, BXM_BLE_ADV_START, 0, 0 );
            break;
        case BXM_BLE_BOND_SUCCEED:
            bxsh_logln( "BXM_BLE_BOND_SUCCEED" );
            break;

        default:
            break;
    }
    return BX_OK;
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t app_button_msg_handle( u32 msg, u32 param0, u32 param1 )
{

    switch( msg ) {

        case USM_BTN_CLICK:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                bxsh_logln( "BUTTON_GPIO_PIN0 CLICK" );

                hid_mouse_sendreport(1);
                hid_mouse_sendreport( HID_RELEASE ); //释放hid
				
                bx_cancel( user_service_button_id(), USM_BTN_DOWN );  //释放按键

            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bxsh_logln( "BUTTON_GPIO_PIN1 CLICK" );

                hid_keyboard_sendreport(HID_KEYBOARD_2);   //report 键值
                hid_keyboard_sendreport( HID_RELEASE );
                bx_cancel( user_service_button_id(), USM_BTN_DOWN );
            }

            break;

        default:
            break;

    }

//#if ( BX_DEEP_SLEEP > 0 )
//    bx_defer( user_service_button_id(), USM_BTN_UP, 0, 0, BUTTON_MAX_DELAY_MS );
//#endif
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 )
{
    s32 msg_src = bx_msg_source();
    if(  msg_src == us_ble_id() ) {
        user_ble_msg_handle_func( msg_src, msg, param0, param1 );
    } else if( msg_src == user_service_button_id() ) {
        app_button_msg_handle( msg, param0, param1 );
    }
    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



