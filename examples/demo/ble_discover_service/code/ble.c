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


#include "ble.h"

/* private define ------------------------------------------------------------*/

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static const struct ke_task_desc TASK_DESC_APP = {
    NULL,
    &appm_default_handler,
    app_state,
    APP_STATE_MAX,
    APP_IDX_MAX
};

/* exported variables --------------------------------------------------------*/
struct app_env_tag app_env;
ke_state_t app_state[APP_IDX_MAX];

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_ble_init( void )
{
    memset( &app_env, 0, sizeof( app_env ) );
    ke_task_create( TASK_APP, &TASK_DESC_APP );
    ke_state_set( TASK_APP, APP_INIT );
    app_on_ble_init();
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_scan_start( struct gapm_start_scan_cmd *scan_param )
{

    struct gapm_start_scan_cmd * cmd = KE_MSG_ALLOC( GAPM_START_SCAN_CMD,
                                       TASK_GAPM, TASK_APP,
                                       gapm_start_scan_cmd );

    cmd->op.code = scan_param->op.code;
    cmd->op.addr_src = scan_param->op.addr_src;
    cmd->op.state = 0;
    cmd->interval = scan_param->interval;
    cmd->window = scan_param->window;
    cmd->mode = scan_param->mode;
    cmd->filter_duplic = scan_param->filter_duplic;
    cmd->filt_policy = scan_param->filt_policy;

    ke_msg_send( cmd );
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_scan_stop( void )
{

    struct gapm_cancel_cmd * cmd = KE_MSG_ALLOC( GAPM_CANCEL_CMD,
                                   TASK_GAPM, TASK_APP,
                                   gapm_cancel_cmd );

    cmd->operation = GAPM_CANCEL;
    ke_msg_send( cmd );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_disconnect( void )
{
    struct gapc_disconnect_cmd * discon_cmd = KE_MSG_ALLOC( GAPC_DISCONNECT_CMD, TASK_GAPC, TASK_APP, gapc_disconnect_cmd );

    discon_cmd->operation = GAPC_DISCONNECT;
    discon_cmd->reason = CO_ERROR_REMOTE_USER_TERM_CON;

    ke_msg_send( discon_cmd );
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_connect_start( u8 * addr )
{
    struct gapm_start_connection_cmd * connect_cmd = KE_MSG_ALLOC_DYN( GAPM_START_CONNECTION_CMD, TASK_GAPM, TASK_APP, gapm_start_connection_cmd, sizeof( struct gap_bdaddr ) );

    connect_cmd->op.code = GAPM_CONNECTION_DIRECT;
    connect_cmd->op.addr_src = GAPM_STATIC_ADDR;
    connect_cmd->op.state = 0;
    connect_cmd->scan_interval = 160;
    connect_cmd->scan_window = 80;
    connect_cmd->con_intv_min = 400;
    connect_cmd->con_intv_max = 400;
    connect_cmd->con_latency = 0;
    connect_cmd->superv_to = 300;
    connect_cmd->ce_len_min = 0xffff;
    connect_cmd->ce_len_max = 0xffff;
    connect_cmd->nb_peers = 1;

    connect_cmd->peers[0].addr_type = 0;
    memcpy( connect_cmd->peers[0].addr.addr, addr, 6 );

    ke_msg_send( connect_cmd );
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_discover_service(u8 *uuid)
{
	struct gattc_sdp_svc_disc_cmd* disc_cmd  = KE_MSG_ALLOC( GATTC_SDP_SVC_DISC_CMD,TASK_GATTC, TASK_APP,gattc_sdp_svc_disc_cmd );
	
	static u16 dis_seq_num;
	disc_cmd->operation=GATTC_SDP_DISC_SVC;
	disc_cmd->uuid_len=16;
	disc_cmd->seq_num=dis_seq_num++;
	disc_cmd->start_hdl=0x01;
	disc_cmd->end_hdl=0xffff;
	memcpy(disc_cmd->uuid,uuid,16);
	ke_msg_send( disc_cmd );

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_update_con_param( struct gapc_conn_param * conn_param )
{
    // Prepare the GAPC_PARAM_UPDATE_CMD message
    struct gapc_param_update_cmd * cmd = KE_MSG_ALLOC( GAPC_PARAM_UPDATE_CMD,TASK_GAPC, TASK_APP,gapc_param_update_cmd );

    cmd->operation  = GAPC_UPDATE_PARAMS;
    cmd->intv_min   = conn_param->intv_min;
    cmd->intv_max   = conn_param->intv_max;
    cmd->latency    = conn_param->latency;
    cmd->time_out   = conn_param->time_out;

    // not used by a slave device
    cmd->ce_len_min = 0xFFFF;
    cmd->ce_len_max = 0xFFFF;

    // Send the message
    ke_msg_send( cmd );
}

/** ---------------------------------------------------------------------------
 * @brief   :Used for wtite data from the central to the peripheral
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_gatt_write(u8 operation,u8 length,u8 handle,u8 *pdata)
{
	static u16 write_seq_num = 0;
    struct gattc_write_cmd* write_cmd  = KE_MSG_ALLOC_DYN(GATTC_WRITE_CMD, TASK_GATTC,TASK_APP, gattc_write_cmd, length);
	
	write_cmd->operation=operation;
	write_cmd->auto_execute=1;
	write_cmd->seq_num=write_seq_num++;
	write_cmd->handle=handle;
	write_cmd->offset=0;
	write_cmd->length=length;
	memcpy(write_cmd->value, pdata, length);

	ke_msg_send(write_cmd);
}


/** ---------------------------------------------------------------------------
 * @brief   :Used to read data from the central to the peripheral
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_gatt_read(u8 operation,u8 length,u8 handle)
{
	static u16 read_seq_num = 0;
    struct gattc_read_cmd* read_cmd  = KE_MSG_ALLOC( GATTC_READ_CMD,TASK_GATTC, TASK_APP,gattc_read_cmd );
	
	read_cmd->operation=operation;
	read_cmd->nb=0;
	read_cmd->seq_num=read_seq_num++;
	read_cmd->req.simple.handle=handle;
	read_cmd->req.simple.offset=0;
	read_cmd->req.simple.length=length;
		
	ke_msg_send(read_cmd);
}

/* exported variables --------------------------------------------------------*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint8_t appm_get_handler( const struct ke_state_handler * handler_list,
                                 ke_msg_id_t msgid,
                                 void * param,
                                 ke_task_id_t src_id )
{
    uint8_t counter;

    for ( counter = handler_list->msg_cnt; 0 < counter; counter-- ) {
        struct ke_msg_handler * handler = ( struct ke_msg_handler * )( ( handler_list->msg_table + counter - 1 ) );

        if ( ( handler->id == msgid ) ||
             ( handler->id == KE_MSG_DEFAULT_HANDLER ) ) {
            ASSERT_ERR( handler->func );

            return ( uint8_t )( handler->func( msgid, param, TASK_APP, src_id ) );
        }
    }
    return ( KE_MSG_CONSUMED );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gapm_device_ready_ind_handler( ke_msg_id_t const msgid,
        void const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{
    ASSERT_ERR( ke_state_get( dest_id ) == APP_INIT );
    struct gapm_reset_cmd * cmd = KE_MSG_ALLOC( GAPM_RESET_CMD,
                                  TASK_GAPM, TASK_APP,
                                  gapm_reset_cmd );
    cmd->operation = GAPM_RESET;
    ke_msg_send( cmd );
    return ( KE_MSG_CONSUMED );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gapm_cmp_evt_handler( ke_msg_id_t const msgid,
                                 struct gapm_cmp_evt const * param,
                                 ke_task_id_t const dest_id,
                                 ke_task_id_t const src_id )
{
    switch( param->operation ) {
        case ( GAPM_RESET ): {
            if( param->status == GAP_ERR_NO_ERROR ) {
                struct gapm_set_dev_config_cmd * cmd = KE_MSG_ALLOC( GAPM_SET_DEV_CONFIG_CMD,
                                                       TASK_GAPM, TASK_APP,
                                                       gapm_set_dev_config_cmd );
                app_set_dev_cfg(cmd);
                ke_msg_send( cmd );
                ke_msg_send_basic( BKT_MSG_CREAT_TIMER, TASK_BX_KERNEL_TIMER, TASK_BX_KERNEL_TIMER );
            } else {
                ASSERT_ERR( 0 );
            }
        }
        break;
        case ( GAPM_PROFILE_TASK_ADD ): {
            struct gapm_gen_rand_nb_cmd * cmd = KE_MSG_ALLOC( GAPM_GEN_RAND_NB_CMD,
                                                TASK_GAPM, TASK_APP,
                                                gapm_gen_rand_nb_cmd );
            cmd->operation   = GAPM_GEN_RAND_NB;
            app_env.rand_cnt = 1;
            ke_msg_send( cmd );
        }
        break;

        case ( GAPM_GEN_RAND_NB ) : {
            if ( app_env.rand_cnt == 1 ) {
                app_env.rand_cnt++;
                struct gapm_gen_rand_nb_cmd * cmd = KE_MSG_ALLOC( GAPM_GEN_RAND_NB_CMD,
                                                    TASK_GAPM, TASK_APP,
                                                    gapm_gen_rand_nb_cmd );
                cmd->operation = GAPM_GEN_RAND_NB;
                ke_msg_send( cmd );
            } else {
                struct gapm_set_irk_cmd * cmd = KE_MSG_ALLOC( GAPM_SET_IRK_CMD,
                                                TASK_GAPM, TASK_APP,
                                                gapm_set_irk_cmd );

                app_env.rand_cnt = 0;
                cmd->operation = GAPM_SET_IRK;
                memcpy( &cmd->irk.key[0], &app_env.loc_irk[0], KEY_LEN );

                ke_msg_send( cmd );
            }
        }
        break;

        case ( GAPM_SET_IRK ): {
            app_env.rand_cnt = 0;

            if ( !app_add_svc() ) {
                ke_state_set(TASK_APP, APP_READY);
                
                app_on_ble_ready();
            }
        }
        break;

        case ( GAPM_SET_DEV_CONFIG ): {
            ASSERT_INFO( param->status == GAP_ERR_NO_ERROR, param->operation, param->status );

            ke_state_set( TASK_APP, APP_CREATE_DB );

            app_add_svc();
        }
        break;

        case ( GAPM_ADV_NON_CONN ):
        case ( GAPM_ADV_UNDIRECT ):
        case ( GAPM_ADV_DIRECT ):
        case ( GAPM_ADV_DIRECT_LDC ):
        case ( GAPM_UPDATE_ADVERTISE_DATA ): {
            ASSERT_INFO( param->status == GAP_ERR_NO_ERROR, param->operation, param->status );
        }
        break;


        default:

            break;
    }

    return ( KE_MSG_CONSUMED );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gapc_get_dev_info_req_ind_handler( ke_msg_id_t const msgid,
        struct gapc_get_dev_info_req_ind const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{
    switch( param->req ) {
        case GAPC_DEV_NAME: {
            struct gapc_get_dev_info_cfm * cfm = KE_MSG_ALLOC_DYN( GAPC_GET_DEV_INFO_CFM,
                                                 src_id, dest_id,
                                                 gapc_get_dev_info_cfm, APP_DEVICE_NAME_MAX_LEN );

            cfm->req = param->req;
            cfm->info.name.length = app_get_dev_name( cfm->info.name.value );
            ke_msg_send( cfm );
        }
        break;

        case GAPC_DEV_APPEARANCE: {
            struct gapc_get_dev_info_cfm * cfm = KE_MSG_ALLOC( GAPC_GET_DEV_INFO_CFM,
                                                 src_id, dest_id,
                                                 gapc_get_dev_info_cfm );
            cfm->req = param->req;
            cfm->info.appearance=0;
            ke_msg_send( cfm );
        }
        break;

        case GAPC_DEV_SLV_PREF_PARAMS: {
            struct gapc_get_dev_info_cfm * cfm = KE_MSG_ALLOC( GAPC_GET_DEV_INFO_CFM,
                                                 src_id, dest_id,
                                                 gapc_get_dev_info_cfm );
            cfm->req = param->req;            
            cfm->info.slv_params.con_intv_min = 8;
            cfm->info.slv_params.con_intv_max = 10;
            cfm->info.slv_params.slave_latency = 0;
            cfm->info.slv_params.conn_timeout = 200;
            ke_msg_send( cfm );
        }
        break;

        default:
            break;
    }


    return ( KE_MSG_CONSUMED );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gapc_set_dev_info_req_ind_handler( ke_msg_id_t const msgid,
        struct gapc_set_dev_info_req_ind const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{
    // Set Device configuration
    struct gapc_set_dev_info_cfm * cfm = KE_MSG_ALLOC( GAPC_SET_DEV_INFO_CFM, src_id, dest_id,
                                         gapc_set_dev_info_cfm );
    cfm->status = GAP_ERR_REJECTED;
    cfm->req = param->req;
    ke_msg_send( cfm );

    return ( KE_MSG_CONSUMED );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gapc_connection_req_ind_handler( ke_msg_id_t const msgid,
        struct gapc_connection_req_ind const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{
    app_env.conidx = KE_IDX_GET( src_id );

    if ( app_env.conidx != GAP_INVALID_CONIDX ) {
        app_env.conhdl = param->conhdl;


        struct gapc_connection_cfm * cfm = KE_MSG_ALLOC( GAPC_CONNECTION_CFM,
                                           KE_BUILD_ID( TASK_GAPC, app_env.conidx ), TASK_APP,
                                           gapc_connection_cfm );

        cfm->auth=GAP_AUTH_REQ_NO_MITM_NO_BOND;
        ke_msg_send( cfm );
		LOG_RAW("CONNECTED\r\n\r\n");
		
		static u8 uuid_buf[16]={0xC7,0xA5,0x00,0x5B,0x02,0x00,0x23,0x9B,0x11,0xE1,0x02,0xD1,0x66,0x66,0x00,0x00};
		bx_dwork( (void(*)(void *))ble_discover_service,uuid_buf,500, 1 );
    } else {
        app_on_ble_connect_fail();
    }

    return ( KE_MSG_CONSUMED );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gapc_cmp_evt_handler( ke_msg_id_t const msgid,
                                 struct gapc_cmp_evt const * param,
                                 ke_task_id_t const dest_id,
                                 ke_task_id_t const src_id )
{
    switch( param->operation ) {

        default: {
        } break;
    }

    return ( KE_MSG_CONSUMED );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gapc_disconnect_ind_handler( ke_msg_id_t const msgid,
                                        struct gapc_disconnect_ind const * param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id )
{
    app_on_ble_disconnect();

    return ( KE_MSG_CONSUMED );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gapm_profile_added_ind_handler( ke_msg_id_t const msgid,
        struct gapm_profile_added_ind * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{

    uint8_t state            = ke_state_get( dest_id );

    if ( state == APP_CREATE_DB ) {
    } else {
        ASSERT_INFO( 0, state, src_id );
    }
    return KE_MSG_CONSUMED;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int msg_default_handler( ke_msg_id_t const msgid,
                                void * param,
                                ke_task_id_t const dest_id,
                                ke_task_id_t const src_id )
{
    ke_task_id_t src_task_id = MSG_T( msgid );
    uint8_t msg_pol          = KE_MSG_CONSUMED;

    switch ( src_task_id ) {
        
        case TASK_ID_DISS:
            msg_pol = appm_get_handler(&app_dis_table_handler, msgid, param, src_id);
            break;
        default:
            break;
    }
    return ( msg_pol );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gapm_gen_rand_nb_ind_handler( ke_msg_id_t const msgid, struct gapm_gen_rand_nb_ind * param,
        ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    if ( app_env.rand_cnt == 1 ) {
        memcpy( &app_env.loc_irk[0], &param->randnb.nb[0], 8 );
    } else if ( app_env.rand_cnt == 2 ) {
        memcpy( &app_env.loc_irk[8], &param->randnb.nb[0], 8 );
    }

    return KE_MSG_CONSUMED;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void osapp_gapc_param_update_cfm( ke_msg_id_t const msgid, void const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    struct gapc_param_update_cfm * cfm = KE_MSG_ALLOC( GAPC_PARAM_UPDATE_CFM,
                                         src_id, dest_id,
                                         gapc_param_update_cfm );
    cfm->accept = 0x01;
    cfm->ce_len_max = 0xffff;
    cfm->ce_len_min = 0xffff;
    ke_msg_send( cfm );
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gattc_sdp_svc_ind_handler( ke_msg_id_t const msgid, struct gattc_sdp_svc_ind const * param,
                                  ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
	LOG_RAW("service uuid:\r\n\r\n");
	for(u8 i=0;i<param->uuid_len;i++)
	{
		LOG_RAW("%02x ",param->uuid[i]);
	}
	LOG_RAW("\r\n\r\n");
    LOG_RAW("start handle=%d\r\n",param->start_hdl);
    LOG_RAW("end handle=%d\r\n",param->end_hdl);
    
    LOG_RAW("att_type=%d\r\n",param->info[0].att_type);
    LOG_RAW("att_char.att_type=%d\r\n",param->info[0].att_char.att_type);
    LOG_RAW("att_char.prop=%d\r\n",param->info[0].att_char.prop);
    LOG_RAW("att_char.handle=%d\r\n\r\n",param->info[0].att_char.handle);
    
    
    
    LOG_RAW("att.att_type=%d\r\n",param->info[0].att.att_type);
    LOG_RAW("att.uuid_len=%d\r\n",param->info[0].att.uuid_len);
    for(u8 j=0;j<param->info[0].att.uuid_len;j++)
	{
		LOG_RAW("%02x ",param->info[0].att.uuid[j]);
	}
    LOG_RAW("\r\n\r\n");
    
     LOG_RAW("inc_svc.att_type=%d\r\n",param->info[0].inc_svc.att_type);
     LOG_RAW("inc_svc.start_hdl=%d\r\n",param->info[0].inc_svc.start_hdl);
    LOG_RAW("inc_svc.end_hdl=%d\r\n",param->info[0].inc_svc.end_hdl);
    LOG_RAW("inc_svc.uuid_len=%d\r\n",param->info[0].inc_svc.uuid_len);
    for(u8 k=0;k<param->info[0].inc_svc.uuid_len;k++)
	{
		LOG_RAW("%02x ",param->info[0].inc_svc.uuid[k]);
	}
    LOG_RAW("\r\n\r\n");
    
	
    return ( KE_MSG_CONSUMED );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int gattc_cmp_evt_handler( ke_msg_id_t const msgid, struct gattc_cmp_evt const * param,
                                  ke_task_id_t const dest_id, ke_task_id_t const src_id )
{

    return ( KE_MSG_CONSUMED );
}


const struct ke_msg_handler appm_default_state[] = {
    {KE_MSG_DEFAULT_HANDLER,    ( ke_msg_func_t )msg_default_handler},
    {GAPM_DEVICE_READY_IND,     ( ke_msg_func_t )gapm_device_ready_ind_handler},
    {GAPM_CMP_EVT,              ( ke_msg_func_t )gapm_cmp_evt_handler},
    {GAPC_GET_DEV_INFO_REQ_IND, ( ke_msg_func_t )gapc_get_dev_info_req_ind_handler},
    {GAPC_SET_DEV_INFO_REQ_IND, ( ke_msg_func_t )gapc_set_dev_info_req_ind_handler},
    {GAPC_CONNECTION_REQ_IND,   ( ke_msg_func_t )gapc_connection_req_ind_handler},
    {GAPC_CMP_EVT,              ( ke_msg_func_t )gapc_cmp_evt_handler},
    {GAPC_DISCONNECT_IND,       ( ke_msg_func_t )gapc_disconnect_ind_handler},
    {GAPM_PROFILE_ADDED_IND,    ( ke_msg_func_t )gapm_profile_added_ind_handler},
    {GAPM_GEN_RAND_NB_IND,      ( ke_msg_func_t )gapm_gen_rand_nb_ind_handler},
    {GAPC_PARAM_UPDATE_REQ_IND, ( ke_msg_func_t )osapp_gapc_param_update_cfm},
    {GATTC_CMP_EVT,             ( ke_msg_func_t )gattc_cmp_evt_handler},
	{GAPM_ADV_REPORT_IND,       ( ke_msg_func_t )app_on_scan_adv_report},
	{GATTC_SDP_SVC_IND,			( ke_msg_func_t )gattc_sdp_svc_ind_handler}
};

const struct ke_state_handler appm_default_handler = KE_STATE_HANDLER( appm_default_state );
ke_state_t appm_state[1];




__weak bool app_add_svc( void )
{
    return false;
}
__weak void app_set_dev_cfg( struct gapm_set_dev_config_cmd * cfg )
{
    
}
__weak u8 app_get_dev_name( uint8_t * name )
{
    return 0;
}
__weak void app_on_ble_ready( void )
{
    
}
__weak void app_on_ble_disconnect( void )
{

}
__weak void app_on_ble_connect_fail( void )
{

}
/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
