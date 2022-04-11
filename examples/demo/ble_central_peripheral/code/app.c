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
#include "flash_wrapper.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
typedef void ( *appm_add_svc_func_t )( void );
/* private variables ---------------------------------------------------------*/
uint8_t user_scan_rsp_data[] = {
    0x08,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, //type of this data
    'B', 'X', '-', 'S', 'D', 'K', '3'
};

// GAP - Advertisement data (max size = (28) bytes)
uint8_t user_adv_data[] = {
    0x08,// length of this data
    GAP_AD_TYPE_SHORTENED_NAME,//type of this data
    'B', 'X', '-', 'S', 'D', 'K', '3'
};


static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    ( appm_add_svc_func_t )app_dis_add_dis
};

/* exported variables --------------------------------------------------------*/
/*============================= private function =============================*/

s32 user_service_id;

bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 );

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
    cmd->role      = GAP_ROLE_ALL;
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
 * @brief   :Scan callback function
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
int app_on_scan_adv_report( ke_msg_id_t const msgid, adv_report_t const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{

    LOG_RAW( "adv or rsp data:" );
    for( u8 i = 0; i < param->data_len; i++ ) {
        LOG_RAW( "%02x ", param->data[i] );

    }
    LOG_RAW( "\r\nRSSI=%u\r\n", param->rssi );
    LOG_RAW( "\r\n\r\n" );

    return ( KE_MSG_CONSUMED );
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


void app_ble_scan( void )
{
    struct gapm_start_scan_cmd * cmd = KE_MSG_ALLOC( GAPM_START_SCAN_CMD,
                                       TASK_GAPM, TASK_APP,
                                       gapm_start_scan_cmd );

    cmd->op.code = GAPM_SCAN_ACTIVE;
    cmd->op.addr_src = GAPM_STATIC_ADDR;
    cmd->op.state = 0;
    cmd->interval = 160;
    cmd->window = 160;
    cmd->mode = GAP_OBSERVER_MODE;
    cmd->filter_duplic = SCAN_ALLOW_ADV_ALL;
    cmd->filt_policy = SCAN_FILT_DUPLIC_DIS;

    ke_msg_send( cmd );
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
    user_service_id = bx_register( &svc );


    bx_defer( user_service_id, USM_APP_STOP_ADV, 0, 0, 10000 );

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
    if( msg_src == user_service_id ) {
        switch( msg ) {
            case USM_APP_STOP_ADV:
                
                LOG_RAW( "stop adv\r\n" );
                ble_advertising_stop();
                bx_defer( user_service_id, USM_APP_START_SCAN, 0, 0, 1000 );
                break;
            case USM_APP_START_SCAN:
                 LOG_RAW( "start scan\r\n" );
                app_ble_scan();
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



