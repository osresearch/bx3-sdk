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
/* private define ------------------------------------------------------------*/
#define DEFAULT_SCAN_OPCODE     GAPM_SCAN_ACTIVE
#define DEFAULT_SCAN_ADDR       GAPM_STATIC_ADDR
#define DEFAULT_SCAN_INTV       160 //unit is 0.625ms  48*0.625=30(ms)
#define DEFAULT_SCAN_WINDOW     80  //unit is 0.625ms

#define DEFAULT_SCAN_MODE       GAP_OBSERVER_MODE

#define DEFAULT_SCAN_FILTER_DUPLIC     SCAN_FILT_DUPLIC_DIS
#define DEFAULT_SCAN_FILT_POLICY       SCAN_ALLOW_ADV_ALL
/* private typedef -----------------------------------------------------------*/
typedef void ( *appm_add_svc_func_t )( void );
/* private variables ---------------------------------------------------------*/

static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    ( appm_add_svc_func_t )app_dis_add_dis
};

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
void app_set_dev_cfg( struct gapm_set_dev_config_cmd * cmd )
{
    cmd->operation = GAPM_SET_DEV_CONFIG;
    cmd->role      = GAP_ROLE_CENTRAL;
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
}

u8 con_mac_buf[6];
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


    if( param->data[0] == 0x0b && param->data[1] == GAP_AD_TYPE_COMPLETE_NAME ) {
        if( param->data[2] == 'D' && param->data[3] == 'L' && param->data[4] == 'U' && param->data[5] == 'E' && param->data[6] == 'X' ) {
            LOG_RAW( "MAC ADDR:%02x:%02x:%02x:%02x:%02x:%02x\r\n\r\n", param->adv_addr.addr[0], param->adv_addr.addr[1], param->adv_addr.addr[2], param->adv_addr.addr[3], param->adv_addr.addr[4], param->adv_addr.addr[5] );
            con_mac_buf[0] = param->adv_addr.addr[0];
            con_mac_buf[1] = param->adv_addr.addr[1];
            con_mac_buf[2] = param->adv_addr.addr[2];
            con_mac_buf[3] = param->adv_addr.addr[3];
            con_mac_buf[4] = param->adv_addr.addr[4];
            con_mac_buf[5] = param->adv_addr.addr[5];
            ble_scan_stop();

            bx_dwork( ( void ( * )( void * ) )ble_connect_start, con_mac_buf, 500, 1 );   //Execute the function ble_connect_start after 500ms


        }
    }

    return ( KE_MSG_CONSUMED );
}
/** ----------------------"vco restore to modem\n"-----------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_ready( void )
{
    struct gapm_start_scan_cmd app_scan_param;
    app_scan_param.op.code = DEFAULT_SCAN_OPCODE;
    app_scan_param.op.addr_src = DEFAULT_SCAN_ADDR;
    app_scan_param.interval = DEFAULT_SCAN_INTV;
    app_scan_param.window = DEFAULT_SCAN_WINDOW;
    app_scan_param.mode = DEFAULT_SCAN_MODE;
    app_scan_param.filter_duplic = DEFAULT_SCAN_FILTER_DUPLIC; //filtering rule
    app_scan_param.filt_policy = DEFAULT_SCAN_FILT_POLICY;

    ble_scan_start( &app_scan_param );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_disconnect( void )
{
    struct gapm_start_scan_cmd app_scan_param;
    app_scan_param.op.code = DEFAULT_SCAN_OPCODE;
    app_scan_param.op.addr_src = DEFAULT_SCAN_ADDR;
    app_scan_param.interval = DEFAULT_SCAN_INTV;
    app_scan_param.window = DEFAULT_SCAN_WINDOW;
    app_scan_param.mode = DEFAULT_SCAN_MODE;
    app_scan_param.filter_duplic = DEFAULT_SCAN_FILTER_DUPLIC;
    app_scan_param.filt_policy = DEFAULT_SCAN_FILT_POLICY;

    ble_scan_start( &app_scan_param );
}



/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{

}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



