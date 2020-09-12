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
#include "user_service_button.h"
#include "bx_service_gpio.h"
#include "user_service_ble.h"

#include "bx_shell.h"

#include "gap.h"
#include "gapm_task.h"
#include "co_bt_defines.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
// GAP - SCAN RSP data (max size = 31 bytes)
static uint8_t user_scanRspData[] = {
    // complete name
    0x0A,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, ////type of this data
    0x42, //'B'
    0x6C, //'l'
    0x75, //'u'
    0x65, //'e'
    0x58, //'X'
    0x2d, //'-'
    0x53, //'S'
    0x44, //'D'
    0x4B, //'K'
};

// GAP - Advertisement data (max size = (31 - 3) bytes, though this is
// best kept short to conserve power while advertisting)
static uint8_t user_advertData[] = {

    // service UUID, to notify central devices what services are included
    // in this peripheral
    0x03,   // length of this data
    GAP_AD_TYPE_COMPLETE_LIST_16_BIT_UUID,// some of the UUID's, but not all
    0x12,
    0x18,

    //shortened name
    0x0A,// length of this data
    GAP_AD_TYPE_SHORTENED_NAME,//type of this data
    0x42, //'B'
    0x6C, //'l'
    0x75, //'u'
    0x65, //'e'
    0x58, //'X'
    0x2d, //'-'
    0x53, //'S'
    0x44, //'D'
    0x4B, //'K'

    //Manufacturer specific data
    0x04,// length of this data
    GAP_AD_TYPE_MANU_SPECIFIC_DATA,//type of this data
    0x11,
    0x12,
    0x13,

};


static struct bx_ble_adv user_ble_adv = {0};

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
    user_service_button_register();
    bxs_gpio_register();
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

    //订阅button事件
    bx_subscibe( id, USM_BTN_CLICK, 0, 0 );
    bx_subscibe( id, USM_BTN_DOUBLE_CLICK, 0, 0 );
    bx_subscibe( id, USM_BTN_CLICK_MORE, 0, 0 );
    bx_subscibe( id, USM_BTN_PRESS_SHORT_START, 0, 0 );
    bx_subscibe( id, USM_BTN_PRESS_LONG_START, 0, 0 );
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
                bx_post( us_ble_id(), BXM_BLE_ADV_STOP, 0, 0 );
                bxsh_logln( " ADV STOP" );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bx_post( us_ble_id(), BXM_BLE_ADV_START, 0, 0 );
                bxsh_logln( "ADV START" );
            }

            break;

        case USM_BTN_DOUBLE_CLICK:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                uint16_t adv_intv_max = 160;
                uint16_t adv_intv_min = 160;
                uint8_t op_code = GAPM_ADV_UNDIRECT;
                uint8_t adv_mode = GAP_GEN_DISCOVERABLE;
                uint8_t adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;

                bx_set( us_ble_id(), BXP_BLE_ADV_DATA, ( u32 )user_advertData, sizeof( user_advertData ) );
                bx_set( us_ble_id(), BXP_BLE_SCAN_RSP_DATA, ( u32 )user_scanRspData, sizeof( user_scanRspData ) );

                bx_set( us_ble_id(), BXP_BLE_ADV_INTV, adv_intv_max, adv_intv_min );

                bx_set( us_ble_id(), BXP_BLE_OP_CODE, op_code, 0 );
                bx_set( us_ble_id(), BXP_BLE_ADV_MODE, adv_mode, 0 );
                bx_set( us_ble_id(), BXP_BLE_ADV_FILT_POLICY, adv_filt_policy, 0 );
                bxsh_logln( "SET ADV " );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                user_ble_adv.host_adv_data_len = sizeof( user_advertData );
                user_ble_adv.host_scan_data_len = sizeof( user_scanRspData );
                memcpy( user_ble_adv.host_adv_data, user_advertData, user_ble_adv.host_adv_data_len );
                memcpy( user_ble_adv.host_scan_data, user_scanRspData, user_ble_adv.host_scan_data_len );

                bx_post( us_ble_id(), BXM_BLE_ADV_UPDATE, ( u32 )&user_ble_adv, 0 );
                bxsh_logln( "ADV UPDATE" );
            }
            break;

        case USM_BTN_CLICK_MORE:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                bx_post( us_ble_id(), BXM_BLE_ADV_CHANGE_DATA, ( u32 )user_advertData, sizeof( user_advertData ) );
                bxsh_logln( "CHANGE ADV DATA" );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                bx_post( us_ble_id(), BXM_BLE_ADV_CHANGE_SCAN_RSP_DATA, ( u32 )user_scanRspData, sizeof( user_scanRspData ) );
                bxsh_logln( "CHANGE ADV SCAN RSP DATA" );
            }
            break;

        case USM_BTN_PRESS_SHORT_START:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                uint16_t adv_intv_max = 1600;
                uint16_t adv_intv_min = 1600;
                bx_post( us_ble_id(), BXM_BLE_ADV_CHANGE_INTV, adv_intv_max, adv_intv_min );
                bxsh_logln( "CHANGE ADV INTV" );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                uint8_t op_code = GAPM_ADV_UNDIRECT;
                bx_post( us_ble_id(), BXM_BLE_ADV_CHANGE_OP_CODE, op_code, 0 );
                bxsh_logln( "CHANGE ADV OP CODE" );
            }

            break;

        case USM_BTN_PRESS_LONG_START:
            if( param0 == BUTTON_GPIO_PIN0 ) {
                uint8_t adv_mode = GAP_GEN_DISCOVERABLE;
                bx_post( us_ble_id(), BXM_BLE_ADV_CHANGE_MODE, adv_mode, 0 );
                bxsh_logln( "CHANGE ADV SCAN MODE" );
            } else if( param0 == BUTTON_GPIO_PIN1 ) {
                uint8_t adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
                bx_post( us_ble_id(), BXM_BLE_ADV_CHANGE_FILT_POLICY, adv_filt_policy, 0 );
                bxsh_logln( "CHANGE ADV FILT POLICY" );
            }

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
bx_err_t app_msg_handle( u32 msg, u32 param0, u32 param1 )
{
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
    s32 src_id = bx_msg_source();

    if( src_id == user_service_button_id() ) {
        app_button_msg_handle( msg, param0, param1 );
    } else if( src_id == user_service_id ) {
        app_msg_handle( msg, param0, param1 );
    }

    return BX_OK;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



