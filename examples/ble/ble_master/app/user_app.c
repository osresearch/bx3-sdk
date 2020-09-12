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
#include "bx_service_gpio.h"
#include "user_service_ble.h"
#include "bx_shell.h"
#include "gapm_task.h"
#include "gattc_task.h"
#include "co_bt_defines.h"
#include "bx_drv_ble.h"
#include "user_service_button.h"
/* private define ------------------------------------------------------------*/

uint8_t button_value = 1;
/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void user_init( void )
{
	bxs_gpio_register();
	user_service_button_register();
	us_ble_register();
	
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

	bx_post( bxs_gpio_a_id(), BXM_OPEN, 0, 0 );

    //¶©ÔÄbuttonÐÅÏ¢
    bx_subscibe( id, USM_BTN_CLICK, 0, 0 );
    bx_subscibe( id, USM_BTN_DOUBLE_CLICK, 0, 0 );
    bx_subscibe( id, USM_BTN_CLICK_MORE, 0, 0 );
    bx_subscibe( id, USM_BTN_PRESS_SHORT_START, 0, 0 );
    bx_subscibe( id, USM_BTN_PRESS_SHORT_UP, 0, 0 );
    bx_subscibe( id, USM_BTN_PRESS_LONG_START, 0, 0 );
    bx_subscibe( id, USM_BTN_PRESS_LONG_UP, 0, 0 );
    bx_subscibe( id, USM_BTN_PRESS_LONG_HOLD, 0, 0 );
    bx_subscibe( id, USM_BTN_PRESS_LONG_HOLD_UP, 0, 0 );
	
	
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
				bxsh_logln( "start scan\r\n" );
				bx_set(us_ble_id(),BXP_BLE_SCAN_POLICY,SCAN_ALLOW_ADV_ALL,0);
				bx_set(us_ble_id(),BXP_BLE_SCAN_DUPLIC,SCAN_FILT_DUPLIC_DIS,0);
				bx_set(us_ble_id(),BXP_BLE_SCAN_MODE,GAPM_SCAN_ACTIVE,0);
				bx_call(us_ble_id(),BXM_BLE_SCAN_START,0,0);
				bx_cancel( user_service_button_id(), USM_BTN_DOWN );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bxsh_logln( "BUTTON_GPIO_PIN1 CLICK" );
				bx_post(us_ble_id(),BXM_BLE_DIS_LINK,0,0);
            }
            button_value++;

            break;

        case USM_BTN_DOUBLE_CLICK:
            if( param0 == BUTTON_GPIO_PIN0 ) {
				static uint8_t write_data[4]={0x01,0x02,0x03,0x04};
                bxsh_logln( "BUTTON_GPIO_PIN0 DOUBLE CLICK" );
				bx_set(us_ble_id(),BXP_BLE_WRITE_TYPE,GATTC_WRITE_NO_RESPONSE,0);
				bx_set(us_ble_id(),BXP_BLE_WRITE_HANDLE,34,0);
				bx_post(us_ble_id(),BXM_BLE_GATTC_WRITE,4,(u32)write_data);
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bxsh_logln( "BUTTON_GPIO_PIN1 DOUBLE CLICK" );
				bx_set(us_ble_id(),BXP_BLE_READ_TYPE,GATTC_READ,0);
				bx_set(us_ble_id(),BXP_BLE_READ_HANDLE,34,0);
				bx_post(us_ble_id(),BXM_BLE_GATTC_READ,1,0);
            }
            button_value += 2;

            break;

        case USM_BTN_CLICK_MORE:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                bxsh_logln( "BUTTON_GPIO_PIN0 CLICK MORE" );
				bx_post(us_ble_id(),BXM_BLE_EXCHANGE_MTU,0,0);
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bxsh_logln( "BUTTON_GPIO_PIN1 CLICK MORE" );
				bx_post(us_ble_id(),BXM_BLE_SET_PHY,GAP_RATE_LE_1MBPS,GAP_RATE_LE_2MBPS);
            }
            button_value += 3;

            break;

        case USM_BTN_PRESS_SHORT_START:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                bxsh_logln( "BUTTON_GPIO_PIN0 SHORT START" );
//				bx_set(us_ble_id(),BXP_BLE_CON_PARAM_MININTV,96,0);
				bx_set(us_ble_id(),BXP_BLE_CON_PARAM_MAXINTV,96,0);
				bx_set(us_ble_id(),BXP_BLE_CON_PARAM_MININTV,96,0);
				bx_set(us_ble_id(),BXP_BLE_CON_PARAM_LATENCY,0,0);
				bx_set(us_ble_id(),BXP_BLE_CON_PARAM_TIMEOUT,200,0);
				bx_post(us_ble_id(),BXM_BLE_UPDATE_PARAM,0,0);
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bxsh_logln( "BUTTON_GPIO_PIN1 SHORT START" );
            }

            button_value += 1;
            break;

        case USM_BTN_PRESS_SHORT_UP:
            if( param0 == BUTTON_GPIO_PIN0 ) {
//                bxsh_logln( "BUTTON_GPIO_PIN0 SHORT UP" );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
//                bxsh_logln( "BUTTON_GPIO_PIN1 SHORT UP" );
            }
            button_value -= 1;
            break;

        case USM_BTN_PRESS_LONG_START:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                bxsh_logln( "BUTTON_GPIO_PIN0 LONG START" );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bxsh_logln( "BUTTON_GPIO_PIN1 LONG START" );
            }
            button_value += 5;
            break;

        case USM_BTN_PRESS_LONG_UP:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                bxsh_logln( "BUTTON_GPIO_PIN0 LONG UP" );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bxsh_logln( "BUTTON_GPIO_PIN1 LONG UP" );
            }
            button_value -= 5;
            break;
        case USM_BTN_PRESS_LONG_HOLD:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                bxsh_logln( "BUTTON_GPIO_PIN0 LONG HOLD" );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bxsh_logln( "BUTTON_GPIO_PIN1 LONG HOLD" );
            }
            button_value += 10;
            break;
        case USM_BTN_PRESS_LONG_HOLD_UP:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                bxsh_logln( "BUTTON_GPIO_PIN0 LONG HOLD UP" );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bxsh_logln( "BUTTON_GPIO_PIN1 LONG HOLD UP" );
            }
            button_value -= 10;
            break;

        default:
            break;

    }

#if ( BX_DEEP_SLEEP > 0 )
    bx_defer( user_service_button_id(), USM_BTN_UP, 0, 0, BUTTON_MAX_DELAY_MS );
#endif
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func(s32 svc, u32 msg,u32 param0,u32 param1 )
{
	
	if( bx_msg_source() == user_service_button_id() ) 
	{
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



