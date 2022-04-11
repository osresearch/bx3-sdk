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
#include "app.h"
#include "ble.h"

#include "app_dis.h"
#include "bx_kernel.h"

#include "app_hid.h"
#include "app_sec.h"
#include "bxe_matrix_keyboard_wakeup.h"
#include "flexible_button.h"
#include "bx_apollo00_it.h"

/* private define ------------------------------------------------------------*/
#define POWER_ON_OFF        0x30
#define UP_CMD              0x42
#define MOUSE_CMD           0x00
#define RIGHT_CMD           0x45
#define MENU_CMD            0x223
#define SETTING_CMD         0x40
#define RETURN_CMD          0x224
#define VOLUME_DOWN_CMD     0xEA
#define VOLUME_UP_CMD       0xE9
#define OK_CMD              0x41
#define LEFT_CMD            0x44
#define DOWN_CMD            0x43
/* private typedef -----------------------------------------------------------*/
typedef void ( *appm_add_svc_func_t )( void );
uint16_t button_buf[] = {POWER_ON_OFF, MENU_CMD, LEFT_CMD, UP_CMD,
                         SETTING_CMD, OK_CMD, MOUSE_CMD, RETURN_CMD,
                         VOLUME_UP_CMD, RIGHT_CMD, VOLUME_DOWN_CMD, DOWN_CMD
                        };
/* private variables ---------------------------------------------------------*/
uint8_t user_scan_rsp_data[] = {
    0x07,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, //type of this data
    'B', 'X', '-', 'H', 'I', 'D'
};

// GAP - Advertisement data (max size = (28) bytes)
uint8_t user_adv_data[] = {
    //Appearance
    0x03,// length of this data
    GAP_AD_TYPE_APPEARANCE,//type of this data
    0xC1, 0x03, //0x80,0x01,


    0x07,// length of this data
    GAP_AD_TYPE_SHORTENED_NAME,//type of this data
    'B', 'X', '-', 'H', 'I', 'D',
};


static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    ( appm_add_svc_func_t )app_dis_add_dis,
    ( appm_add_svc_func_t )app_hid_add_hids,
};



/* exported variables --------------------------------------------------------*/
struct user_service us_svc = {0} ;
//struct app_env_tag app_env;

/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_set_dev_cfg( struct gapm_set_dev_config_cmd * cmd )
{
    cmd->operation = GAPM_SET_DEV_CONFIG;
    cmd->role      = GAP_ROLE_PERIPHERAL;
    cmd->pairing_mode = GAPM_PAIRING_LEGACY;
    cmd->sugg_max_tx_octets = BLE_MAX_OCTETS;
    cmd->sugg_max_tx_time   = BLE_MAX_TIME;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool app_add_svc( void )
{
    bool more_svc = false;
    if ( app_env.next_svc != sizeof( appm_add_svc_func_list ) / sizeof( appm_add_svc_func_t ) ) {
        appm_add_svc_func_list[app_env.next_svc]();
        app_env.next_svc++;
        more_svc = true;
    }
    return more_svc;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_init( void )
{
    app_dis_init();
  
    bx_it_init();

    app_sec_init();
    app_hid_init();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_ready( void )
{
    struct gapm_start_advertise_cmd adv_data;
    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160;//unit is 625 us
    adv_data.intv_min   = 160;//unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( user_adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( user_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, user_adv_data, sizeof( user_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );

    ble_advertising_start( &adv_data );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_disconnect( void )
{
    struct gapm_start_advertise_cmd adv_data;
    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160;//unit is 625 us
    adv_data.intv_min   = 160;//unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( user_adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( user_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, user_adv_data, sizeof( user_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );

    ble_advertising_start( &adv_data );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    struct bx_service svc;
    svc.prop_set_func = NULL;
    svc.prop_get_func = NULL;
    svc.msg_handle_func = user_msg_handle_func;
    svc.name = "user service";
    us_svc.id = bx_register( &svc );

    key_init();
    bx_subscibe( us_svc.id, USM_BTN_EVENT, 0, 0 );
}

bx_err_t hid_report_process( u32 btn_event, u32 btn_id )
{
    switch( btn_event ) {

        case FLEX_BTN_PRESS_SHORT_START:
        case FLEX_BTN_PRESS_LONG_START:
        case FLEX_BTN_PRESS_LONG_HOLD: {
            u8 temp[REPORT_LENGTH_ID0] = {0};
            temp[0] = button_buf[btn_id];
            temp[1] = button_buf[btn_id] >> 8;
            LOG_I( "temp[0] = %d\ttemp[1] = %d\ttemp[2] = %d", temp[0], temp[1], temp[2] );
            app_hid_send_keyboard_report( &temp[0] );
        }
        break;

        case FLEX_BTN_PRESS_SHORT_UP:
        case FLEX_BTN_PRESS_LONG_UP:
        case FLEX_BTN_PRESS_LONG_HOLD_UP: {
            u8 temp[REPORT_LENGTH_ID0] = {0};
            LOG_I( "temp[0] = %d\ttemp[1] = %d\ttemp[2] = %d", temp[0], temp[1], temp[2] );
            app_hid_send_keyboard_report( &temp[0] );
        }
        break;

    }
}

bx_err_t user_msg_handle_func( s32 id, u32 msg, u32 param0, u32 param1 )
{
    s32 msg_src = bx_msg_source();

    if( msg_src == us_svc.id ) {
        switch( msg ) {
            
            case USM_BTN_EVENT: {
                hid_report_process( param0, param1 );
            }
            break;

            default:
                break;
        }

    }
    return BX_OK;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



