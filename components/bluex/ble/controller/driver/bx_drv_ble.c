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
#include "user_ble_task.h"
#include "user_ble.h"
#include "ke_timer.h"
#include "bx_sys_config.h"
#include "co_error.h"
#include "bx_shell.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* config --------------------------------------------------------------------*/

#define APP_ADV_CHMAP                                   0x07

#define DEFAULT_ADV_INT_MIN                             160 // ( 160 * 0.625 = 100ms )
#define DEFAULT_ADV_INT_MAX                             160 // ( 160 * 0.625 = 100ms )

#define DEFAULT_CNT_INTV_MIN                            400 // (400* 1.25 ms = 1000ms)
#define DEFAULT_CNT_INTV_MAX                            400 // (400* 1.25 ms = 1000ms)
#define DEFAULT_CON_LATENCY                             0
#define DEFAULT_TIME_OUT                                300
#define DEFAULT_CE_LEN_MIN                              0
#define DEFAULT_CE_LEN_MAX                              0
#define DEFAULT_NB_PEERS                                1
#define DEFAULT_ADDR_TYPE                               0


#define DEFAULT_SCAN_INTERVAL                           48
#define DEFAULT_SCAN_WINDOW                             48
#define DEFAULT_SCAN_MODE                               GAP_GEN_DISCOVERY
#define DEFAULT_SCAN_OPERATION                          GAPM_SCAN_ACTIVE
#define DEFAULT_GAPM_ADDR                               GAPM_STATIC_ADDR
#define DEFAULT_GATT_DISC                               GATTC_SDP_DISC_SVC_ALL

#define DEFAULT_GAPM_CONNECT                            GAPM_CONNECTION_DIRECT
#define DEFAULT_GAPM_ADDR                               GAPM_STATIC_ADDR

/* private variables ---------------------------------------------------------*/

static u16 w_seqnum = 0;
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
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_advertising_start( struct ble_adv_data * p_new_advdata_buf )
{

    ke_state_set( TASK_APP, APPM_ADVERTISING );
    // Prepare the GAPM_START_ADVERTISE_CMD message
    struct gapm_start_advertise_cmd * adv_cmd = KE_MSG_ALLOC( GAPM_START_ADVERTISE_CMD,
            TASK_GAPM, TASK_APP,
            gapm_start_advertise_cmd );

    CHECK_POINTER( adv_cmd );

    adv_cmd->op.addr_src    = GAPM_STATIC_ADDR;
    adv_cmd->channel_map    = APP_ADV_CHMAP;

    adv_cmd->intv_max   = p_new_advdata_buf->adv_intv_max;
    adv_cmd->intv_min   = p_new_advdata_buf->adv_intv_min;
    adv_cmd->op.code    = p_new_advdata_buf->op_code;
    adv_cmd->info.host.mode = p_new_advdata_buf->adv_mode;
    adv_cmd->info.host.adv_data_len       = p_new_advdata_buf->adv_data_len;
    adv_cmd->info.host.scan_rsp_data_len  = p_new_advdata_buf->scan_rsp_data_len;

    adv_cmd->info.host.adv_filt_policy = p_new_advdata_buf->adv_filt_policy;


    memcpy( adv_cmd->info.host.adv_data, p_new_advdata_buf->adv_data, p_new_advdata_buf->adv_data_len );
    memcpy( adv_cmd->info.host.scan_rsp_data, p_new_advdata_buf->scan_rsp_data, p_new_advdata_buf->scan_rsp_data_len );

    ke_msg_send( adv_cmd );
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_advertising_advdata_update( struct ble_adv_data * p_new_advdata_buf )
{
    struct gapm_update_advertise_data_cmd * update_cmd = KE_MSG_ALLOC( GAPM_UPDATE_ADVERTISE_DATA_CMD,
            TASK_GAPM, TASK_APP,
            gapm_update_advertise_data_cmd );

    CHECK_POINTER( update_cmd );

    memcpy( update_cmd->adv_data, p_new_advdata_buf->adv_data, p_new_advdata_buf->adv_data_len );
    memcpy( update_cmd->scan_rsp_data, p_new_advdata_buf->scan_rsp_data, p_new_advdata_buf->scan_rsp_data_len );

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
bx_err_t ble_advertising_stop( void )
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
bx_err_t ble_scan_start( u8 filter_duplic, u8 filt_policy, u8 scan_mode )
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
bx_err_t ble_whitelist_set( struct whitelist_data *white_list, u8 addr_cnt )
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
bx_err_t ble_connect_start( u8 * addr )
{
	struct gapm_start_connection_cmd * connect_cmd=KE_MSG_ALLOC_DYN(GAPM_START_CONNECTION_CMD,TASK_GAPM,TASK_APP,gapm_start_connection_cmd,1);

	CHECK_POINTER(connect_cmd);
    connect_cmd->op.code = DEFAULT_GAPM_CONNECT;
    connect_cmd->op.addr_src = DEFAULT_GAPM_ADDR;
    connect_cmd->op.state = 0;
    connect_cmd->scan_interval = DEFAULT_SCAN_INTERVAL;
    connect_cmd->scan_window = DEFAULT_SCAN_WINDOW;
    connect_cmd->con_intv_min = DEFAULT_CNT_INTV_MIN;
    connect_cmd->con_intv_max = DEFAULT_CNT_INTV_MAX;
    connect_cmd->con_latency = DEFAULT_CON_LATENCY;
    connect_cmd->superv_to = DEFAULT_TIME_OUT;
    connect_cmd->ce_len_min = DEFAULT_CE_LEN_MIN;
    connect_cmd->ce_len_max = DEFAULT_CE_LEN_MAX;
	connect_cmd->nb_peers=1;
	
	connect_cmd->peers[0].addr_type=DEFAULT_ADDR_TYPE;
	memcpy(connect_cmd->peers[0].addr.addr, addr, 6);
	
    ke_msg_send( connect_cmd );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t update_conn_params( struct ble_gapc_conn_param * conn_param )
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
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_notifaction_enabled( u16 handle )
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
bx_err_t ble_indication_enabled( u16 handle )
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
bx_err_t ble_send_data_notify(u8 *data,u8 length,u16 handle)
{
    struct gattc_send_evt_cmd * notify_cmd = KE_MSG_ALLOC_DYN( GATTC_SEND_EVT_CMD,
											TASK_GATTC, TASK_APP,
											gattc_send_evt_cmd,length);
	CHECK_POINTER(notify_cmd);
    static u16 notify_seq_num = 0;
    notify_cmd->operation = GATTC_NOTIFY;
    notify_cmd->seq_num = notify_seq_num++;
    notify_cmd->length = length;
    notify_cmd->handle = handle;

    memcpy( notify_cmd->value,data, length );
		
    ke_msg_send( notify_cmd );
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_get_dev_rssi(void)
{
	
	struct gapc_get_info_cmd * rssi_cmd = KE_MSG_ALLOC( GAPC_GET_INFO_CMD,
														TASK_GAPC, TASK_APP,
														gapc_get_info_cmd );
	CHECK_POINTER(rssi_cmd);
	rssi_cmd->operation=GAPC_GET_CON_RSSI;
	ke_msg_send( rssi_cmd );
    
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_gatt_write(u8 operation,u8 length,u8 handle,u8 *pdata)
{
	static u16 write_seq_num = 0;
    struct gattc_write_cmd* write_cmd  = KE_MSG_ALLOC_DYN(GATTC_WRITE_CMD, TASK_GATTC,TASK_APP, gattc_write_cmd, length);
	
	CHECK_POINTER(write_cmd);
	write_cmd->operation=operation;
	write_cmd->auto_execute=1;
	write_cmd->seq_num=write_seq_num++;
	write_cmd->handle=handle;
	write_cmd->offset=0;
	write_cmd->length=length;
	memcpy(write_cmd->value, pdata, length);

	ke_msg_send(write_cmd);
	return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_gatt_read(u8 operation,u8 length,u8 handle)
{
	static u16 read_seq_num = 0;
    struct gattc_read_cmd* read_cmd  = KE_MSG_ALLOC( GATTC_READ_CMD,TASK_GATTC, TASK_APP,gattc_read_cmd );
	
	CHECK_POINTER(read_cmd);
	read_cmd->operation=operation;
	read_cmd->nb=0;
	read_cmd->seq_num=read_seq_num++;
	read_cmd->req.simple.handle=handle;
	read_cmd->req.simple.offset=0;
	read_cmd->req.simple.length=length;
		
	ke_msg_send(read_cmd);
	return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_exchange_mtu(void)
{
	static u16 mtu_seq_num = 0;
	struct gattc_exc_mtu_cmd *mtu_cmd = KE_MSG_ALLOC(GATTC_EXC_MTU_CMD, TASK_GATTC,TASK_APP, gattc_exc_mtu_cmd);
	CHECK_POINTER(mtu_cmd);
	
	mtu_cmd->operation=GATTC_MTU_EXCH;
	mtu_cmd->seq_num=mtu_seq_num++;
	
	ke_msg_send(mtu_cmd);
	return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_set_phy(u8 rx_rate,u8 tx_rate)
{
	struct gapc_set_phy_cmd *phy_cmd = KE_MSG_ALLOC(GAPC_SET_PHY_CMD, TASK_GAPC,TASK_APP, gapc_set_phy_cmd);

	CHECK_POINTER(phy_cmd);
	phy_cmd->operation=GAPC_SET_PHY;
	phy_cmd->rx_rates=rx_rate;
	phy_cmd->tx_rates=tx_rate;
	
	ke_msg_send(phy_cmd);
	return BX_OK;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

