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
#include "bx_drv_ble.h"
#include "stdint.h"
#include "gapc_task.h"
#include "gattc_task.h"
#include "nvds_typedef.h"
#include "app_task.h"
#include "app.h"
#include "ke_timer.h"
#include "bx_sys_config.h"
#include "co_error.h"

#include "bx_type_def.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* config --------------------------------------------------------------------*/

#define APP_ADV_CHMAP                                   0x07
#define SWAP(X,Y)                                       { (X)= (X)^(Y);(Y)= (X)^(Y);(X)= (X)^(Y);}


#define ADV_INTERVAL                                    160

#define min_interval                                    80
#define max_interval                                    800

#define APP_ADV_INT_MIN                                 64
#define APP_ADV_INT_MAX                                 64

#define DEFAULT_con_latency                             6
#define DEFAULT_TIME_OUT                                1000
#define DEFAUT_CE_LEN_MIN                               5
#define DEFAULT_CE_LEN_MAX                              10
#define DEFAULT_nb_peers                                1
#define DEFAULT_ADDR_TYPE                               0


#define DEFAULT_SCAN_INTERVAL                           48

#define DEFAULT_SCAN_WINDOW                             48

#define DEFAULT_SCAN_MODE                               GAP_GEN_DISCOVERY

#define DEFAULT_SCAN_OPERATION                          GAPM_SCAN_ACTIVE

#define DEFAULT_GAPM_ADDR                               GAPM_STATIC_ADDR

#define DEFAULT_GATT_DISC                               GATTC_SDP_DISC_SVC_ALL

#define DEFAULT_GAPM_CONNECT                            GAPM_CONNECTION_GENERAL
#define DEFAULT_GAPM_ADDR                               GAPM_STATIC_ADDR
/* private variables ---------------------------------------------------------*/

static uint16_t w_seqnum = 0;
/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
bx_err_t ble_advtising_start( struct ble_adv_data * p_new_advdata_buf, bool default_adv_flag )
{
    ke_state_set( TASK_APP, APPM_ADVERTISING );
    // Prepare the GAPM_START_ADVERTISE_CMD message
    struct gapm_start_advertise_cmd * adv_cmd = KE_MSG_ALLOC( GAPM_START_ADVERTISE_CMD,
            TASK_GAPM, TASK_APP,
            gapm_start_advertise_cmd );
	
	CHECK_POINTER(adv_cmd);

    adv_cmd->op.addr_src    = GAPM_STATIC_ADDR;
    adv_cmd->channel_map    = APP_ADV_CHMAP;

    adv_cmd->intv_max   = APP_ADV_INT_MIN;
    adv_cmd->intv_min   = APP_ADV_INT_MIN;
    adv_cmd->op.code    = GAPM_ADV_UNDIRECT;
    adv_cmd->info.host.mode = DEFAULT_SCAN_MODE;
    adv_cmd->info.host.adv_data_len       = ADV_DATA_LEN - 3;
    adv_cmd->info.host.scan_rsp_data_len  = SCAN_RSP_DATA_LEN;

    adv_cmd->info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_WLST;

    if( default_adv_flag ) {
        uint8_t avail_space;
        avail_space = ( ADV_DATA_LEN - 3 ) - adv_cmd->info.host.adv_data_len - 2;
        if ( avail_space > 2 ) {
            avail_space = co_min( avail_space, app_env.dev_name_len );
            adv_cmd->info.host.adv_data[0] = avail_space + 1;
            adv_cmd->info.host.adv_data[1] = ( avail_space == app_env.dev_name_len ) ? '\x08' : '\x09';
            memcpy( &adv_cmd->info.host.adv_data[2], app_env.dev_name, avail_space );
        }
    } else {
        memcpy( adv_cmd->info.host.adv_data, p_new_advdata_buf->adv_data, ( ADV_DATA_LEN - 3 ) );
        memcpy( adv_cmd->info.host.scan_rsp_data, p_new_advdata_buf->scan_rsp_data, SCAN_RSP_DATA_LEN );
    }

    ke_msg_send( adv_cmd );
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_advtining_advdata_update( struct ble_adv_data * p_new_advdata_buf, bool adv_update, bool scan_rsp_update )
{
    struct gapm_update_advertise_data_cmd * update_cmd = KE_MSG_ALLOC( GAPM_UPDATE_ADVERTISE_DATA_CMD,
            TASK_GAPM, TASK_APP,
            gapm_update_advertise_data_cmd );
	
	CHECK_POINTER(update_cmd);
    if( adv_update ) {
        for( uint8_t i = 0; i < 28; i++ ) {
            update_cmd->adv_data[i] = 0x00;
        }
        memcpy( update_cmd->adv_data, p_new_advdata_buf->adv_data, p_new_advdata_buf->adv_data_len );
    }
    if( scan_rsp_update ) {
        for( uint8_t i = 0; i < 30; i++ ) {
            update_cmd->scan_rsp_data[i] = 0x00;
        }
        memcpy( update_cmd->scan_rsp_data, p_new_advdata_buf->scan_rsp_data, p_new_advdata_buf->scan_rsp_data_len );
    }
    update_cmd->operation = GAPM_UPDATE_ADVERTISE_DATA;
    update_cmd->adv_data_len = p_new_advdata_buf->adv_data_len;

    update_cmd->scan_rsp_data_len = p_new_advdata_buf->scan_rsp_data_len;

    ke_msg_send( update_cmd );
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_bonding_pair( void )
{
    struct gapc_bond_cmd * pair_cmd = KE_MSG_ALLOC( GAPC_BOND_CMD,
                                      TASK_GAPC, TASK_APP,
                                      gapc_bond_cmd );

	CHECK_POINTER(pair_cmd);
    pair_cmd->operation = GAPC_BOND;
    pair_cmd->pairing.iocap = GAP_IO_CAP_DISPLAY_ONLY;
    pair_cmd->pairing.oob = GAP_OOB_AUTH_DATA_PRESENT;
    pair_cmd->pairing.auth = GAP_AUTH_REQ_MITM_BOND;
    pair_cmd->pairing.key_size = 16;
    pair_cmd->pairing.ikey_dist = GAP_KDIST_ENCKEY;
    pair_cmd->pairing.rkey_dist = GAP_KDIST_ENCKEY;
    pair_cmd->pairing.sec_req = GAP_NO_SEC;
    ke_msg_send( pair_cmd );
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_bonding_pair_request( void )
{
    struct gapc_security_cmd * request = KE_MSG_ALLOC( GAPC_SECURITY_CMD,
                                         TASK_GAPC, TASK_APP,
                                         gapc_security_cmd );

	CHECK_POINTER(request);
    request->operation = GAPC_SECURITY_REQ;
    request->auth = GAP_AUTH_REQ_SEC_CON_BOND;


    ke_msg_send( request );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_advtising_stop( void )
{
    if ( ke_state_get( TASK_APP ) == APPM_ADVERTISING ) {
        ke_state_set( TASK_APP, APPM_READY );
        struct gapm_cancel_cmd * cmd = KE_MSG_ALLOC( GAPM_CANCEL_CMD,
                                       TASK_GAPM, TASK_APP,
                                       gapm_cancel_cmd );
		CHECK_POINTER(cmd);
        cmd->operation = GAPM_CANCEL;
        ke_msg_send( cmd );
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_scan_start( uint8_t filter_duplic, uint8_t filt_policy, uint8_t scan_mode )
{

    struct gapm_start_scan_cmd * cmd = KE_MSG_ALLOC( GAPM_START_SCAN_CMD,
                                       TASK_GAPM, TASK_APP,
                                       gapm_start_scan_cmd );
	
	CHECK_POINTER(cmd);
    cmd->op.code = scan_mode;
    cmd->op.addr_src = DEFAULT_GAPM_ADDR;
    cmd->op.state = 0;
    cmd->interval = DEFAULT_SCAN_INTERVAL;
    cmd->window = DEFAULT_SCAN_WINDOW;
    cmd->mode = DEFAULT_SCAN_MODE;
    cmd->filter_duplic = filter_duplic;
    cmd->filt_policy = filt_policy;

    ke_msg_send( cmd );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_scan_stop( void )
{

    struct gapm_cancel_cmd * cmd = KE_MSG_ALLOC( GAPM_CANCEL_CMD,
                                   TASK_GAPM, TASK_APP,
                                   gapm_cancel_cmd );
	CHECK_POINTER(cmd);
    cmd->operation = GAPM_CANCEL;
    ke_msg_send( cmd );
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_advertising_whitelist_set( struct whitelist_data *white_list, uint8_t addr_cnt )
{

	struct gapm_white_list_mgt_cmd * whitelist_cmd = KE_MSG_ALLOC_DYN(GAPM_WHITE_LIST_MGT_CMD,TASK_GAPM,TASK_APP,gapm_white_list_mgt_cmd,6);
	

	
	CHECK_POINTER(whitelist_cmd);
    whitelist_cmd->operation = GAPM_ADD_DEV_IN_WLIST;
    whitelist_cmd->nb = 1;
	
	whitelist_cmd->devices[addr_cnt].addr_type=white_list->addr_type;
	whitelist_cmd->devices[addr_cnt].addr.addr[0]=white_list->addr[0];
	whitelist_cmd->devices[addr_cnt].addr.addr[1]=white_list->addr[1];
	whitelist_cmd->devices[addr_cnt].addr.addr[2]=white_list->addr[2];
	whitelist_cmd->devices[addr_cnt].addr.addr[3]=white_list->addr[3];
	whitelist_cmd->devices[addr_cnt].addr.addr[4]=white_list->addr[4];
	whitelist_cmd->devices[addr_cnt].addr.addr[5]=white_list->addr[5];
	
	
    ke_msg_send( whitelist_cmd );
	return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_connect_stop( void )
{
    struct gapc_disconnect_cmd * discon_cmd = KE_MSG_ALLOC( GAPC_DISCONNECT_CMD,
            TASK_GAPC, TASK_APP,
            gapc_disconnect_cmd );

	CHECK_POINTER(discon_cmd);
    discon_cmd->operation = GAPC_DISCONNECT;
    discon_cmd->reason = CO_ERROR_REMOTE_USER_TERM_CON;

    ke_msg_send( discon_cmd );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_connect_start( uint8_t * addr )
{
    struct gapm_start_connection_cmd * connect_cmd = KE_MSG_ALLOC( GAPM_START_CONNECTION_CMD,
            TASK_GAPM, TASK_APP,
            gapm_start_connection_cmd );

	CHECK_POINTER(connect_cmd);
    connect_cmd->op.code = DEFAULT_GAPM_CONNECT;
    connect_cmd->op.addr_src = DEFAULT_GAPM_ADDR;
    connect_cmd->op.state = 0;
    connect_cmd->scan_interval = DEFAULT_SCAN_INTERVAL;
    connect_cmd->scan_window = DEFAULT_SCAN_WINDOW;
    connect_cmd->con_intv_min = min_interval;
    connect_cmd->con_intv_max = max_interval;
    connect_cmd->con_latency = DEFAULT_con_latency;
    connect_cmd->superv_to = DEFAULT_TIME_OUT;
    connect_cmd->ce_len_min = DEFAUT_CE_LEN_MIN;
    connect_cmd->ce_len_max = DEFAULT_CE_LEN_MAX;

    connect_cmd->peers->addr_type = DEFAULT_ADDR_TYPE;
    memcpy( connect_cmd->peers->addr.addr, addr, 6 );

    ke_msg_send( connect_cmd );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t update_conn_params( struct gapc_conn_param * conn_param )
{
    struct gapc_param_update_cmd * param_cmd = KE_MSG_ALLOC( GAPC_PARAM_UPDATE_CMD,
            KE_BUILD_ID( TASK_GAPC, app_env.conidx ), TASK_APP,
            gapc_param_update_cmd );
	
	CHECK_POINTER(param_cmd);
    param_cmd->operation  = GAPC_UPDATE_PARAMS;
    param_cmd->intv_min   = conn_param->intv_min;
    param_cmd->intv_max   = conn_param->intv_max;
    param_cmd->latency    = conn_param->latency;
    param_cmd->time_out   = conn_param->time_out;

    param_cmd->ce_len_min = 0xFFFF;
    param_cmd->ce_len_max = 0xFFFF;

    ke_msg_send( param_cmd );
    return BX_OK;
}

///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//bx_err_t ble_discover_start( struct ble_discover * discover, uint8_t uuid_len )
//{
//    static uint8_t dis_seq_num;
//    struct gattc_disc_cmd * cover_cmd = KE_MSG_ALLOC( GATTC_DISC_CMD,
//                                        TASK_GATTC, TASK_APP,
//                                        gattc_disc_cmd );

//    cover_cmd->operation = DEFAULT_GATT_DISC;
//    cover_cmd->seq_num = dis_seq_num++;
//    cover_cmd->start_hdl = discover->start_hdl;
//    cover_cmd->end_hdl = discover->end_hdl;
//    cover_cmd->uuid_len = uuid_len;
//    if( uuid_len == 4 ) {
//        memcpy( cover_cmd->uuid, discover->uuid, uuid_len );
//    } else {
//        memcpy( cover_cmd->uuid, discover->uuid, uuid_len );
//    }

//    ke_msg_send( cover_cmd );
//    return BX_OK;
//}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_notifaction_enabled( uint16_t handle )
{
    struct gattc_write_cmd * notify_cmd = KE_MSG_ALLOC_DYN(GATTC_WRITE_CMD,TASK_GATTC,TASK_APP,gattc_write_cmd,2);

	CHECK_POINTER(notify_cmd);
    notify_cmd->operation = GATTC_WRITE_NO_RESPONSE;
    notify_cmd->auto_execute = true;
    notify_cmd->seq_num = w_seqnum++;
    notify_cmd->handle = handle;
    notify_cmd->offset = 0;
    notify_cmd->length = 2;
    notify_cmd->cursor = 0;
    notify_cmd->value[0] = 0x01;
    notify_cmd->value[1] = 0x00;

    ke_msg_send( notify_cmd );
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_indication_enabled( uint16_t handle )
{
    struct gattc_write_cmd * indic_cmd = KE_MSG_ALLOC_DYN(GATTC_WRITE_CMD,TASK_GATTC,TASK_APP,gattc_write_cmd,2);

	
	CHECK_POINTER(indic_cmd);
    indic_cmd->operation = GATTC_WRITE_NO_RESPONSE;
    indic_cmd->auto_execute = true;
    indic_cmd->seq_num = w_seqnum++;
    indic_cmd->handle = handle;
    indic_cmd->offset = 0;
    indic_cmd->length = 2;
    indic_cmd->cursor = 0;
    indic_cmd->value[0] = 0x02;
    indic_cmd->value[1] = 0x00;

	
    ke_msg_send( indic_cmd );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_notify( struct ble_notify_data * p_data )
{
    struct gattc_send_evt_cmd * notify_cmd = KE_MSG_ALLOC_DYN( GATTC_SEND_EVT_CMD,
            TASK_GATTC, TASK_APP,
            gattc_send_evt_cmd,p_data->len);

    static uint16_t notify_seq_num = 0;
    notify_cmd->operation = GATTC_NOTIFY;
    notify_cmd->seq_num = notify_seq_num++;
    notify_cmd->length = p_data->len;
    notify_cmd->handle = p_data->hdl;

    memcpy( notify_cmd->value, p_data->data, p_data->len );
		
    ke_msg_send( notify_cmd );
    return BX_OK;
}



bx_err_t send_data_notify(uint8_t *data,uint8_t length,uint16_t handle)
{
    struct gattc_send_evt_cmd * notify_cmd = KE_MSG_ALLOC_DYN( GATTC_SEND_EVT_CMD,
											TASK_GATTC, TASK_APP,
											gattc_send_evt_cmd,length);

    static uint16_t notify_seq_num = 0;
    notify_cmd->operation = GATTC_NOTIFY;
    notify_cmd->seq_num = notify_seq_num++;
    notify_cmd->length = length;
    notify_cmd->handle = handle;

    memcpy( notify_cmd->value,data, length );
		
    ke_msg_send( notify_cmd );
    return BX_OK;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

