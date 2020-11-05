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


#include "rwip_config.h"          // SW configuration

#include "user_ble_task.h"
#include "user_ble.h"
#include "gapc_task.h"
#include "gapm_task.h"
#include "arch.h"
#include <string.h>
#include "ke_timer.h"
#include "user_profile.h"
#include "user_profile_task.h"
#include "bxotas.h"
#include "bxotas_task.h"
#include "user_ble_profile.h"
#include "diss_task.h"
#include "bx_kernel_timer.h"
#include "bx_kernel.h"
#include "bx_shell.h"
#include "user_service_ble.h"

#include "app_sec.h"
#include "app_hid.h"

#include "bx_pm.h"
//#include "bond_manage.h"
//#include "osapp_utils.h"

/* private define ------------------------------------------------------------*/

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

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
    ASSERT_ERR( ke_state_get( dest_id ) == APPM_INIT );
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

//                app_hid_start_keyboard();

                struct gapm_set_dev_config_cmd * cmd = KE_MSG_ALLOC( GAPM_SET_DEV_CONFIG_CMD,
                                                       TASK_GAPM, TASK_APP,
                                                       gapm_set_dev_config_cmd );


                cmd->operation = GAPM_SET_DEV_CONFIG;

                cmd->role      = GAP_ROLE_PERIPHERAL;


                cmd->max_mtu = 160;
                cmd->pairing_mode = GAPM_PAIRING_LEGACY;
                cmd->sugg_max_tx_octets = BLE_MIN_OCTETS;
                cmd->sugg_max_tx_time   = BLE_MIN_TIME;
                // Enable Slave Preferred Connection Parameters present
                cmd->att_cfg = GAPM_MASK_ATT_SLV_PREF_CON_PAR_EN;

                memcpy( cmd->irk.key, app_env.loc_irk, KEY_LEN );
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

            if ( !user_ble_add_svc() ) {
                ke_state_set( TASK_APP, APPM_READY );
                bx_public( us_ble_id(), BXM_BLE_READY, 0, 0 );

            }
        }
        break;

        case ( GAPM_SET_DEV_CONFIG ): {
            ASSERT_INFO( param->status == GAP_ERR_NO_ERROR, param->operation, param->status );

            ke_state_set( TASK_APP, APPM_CREATE_DB );

            user_ble_add_svc();
        }
        break;

        case ( GAPM_ADV_NON_CONN ):
        case ( GAPM_ADV_UNDIRECT ):
//        case ( GAPM_ADV_DIRECT ):
        case ( GAPM_ADV_DIRECT_LDC ):
        case ( GAPM_UPDATE_ADVERTISE_DATA ): {
            ASSERT_INFO( param->status == GAP_ERR_NO_ERROR, param->operation, param->status );
        }
        break;

//        case (GAPM_ADV_DIRECT):
//        {
//            if (param->status == GAP_ERR_TIMEOUT)
//            {
//                ke_state_set(TASK_APP, APPM_READY);
//                bx_public( us_ble_id(), BXM_BLE_ADVERTISING, 0, 0 );
//            }
//        } break;

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
            memcpy( cfm->info.name.value, app_env.dev_name, app_env.dev_name_len );
            cfm->info.name.length = app_env.dev_name_len;
            ke_msg_send( cfm );
        }
        break;

        case GAPC_DEV_APPEARANCE: {
            struct gapc_get_dev_info_cfm * cfm = KE_MSG_ALLOC( GAPC_GET_DEV_INFO_CFM,
                                                 src_id, dest_id,
                                                 gapc_get_dev_info_cfm );
            cfm->req = param->req;
            //cfm->info.appearance = 0;
            // HID Mouse
            cfm->info.appearance = 962;

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
            cfm->info.slv_params.slave_latency  = 25;
            cfm->info.slv_params.conn_timeout    = 200;
//            cfm->info.slv_params.con_intv_min = 40;
//            cfm->info.slv_params.con_intv_max = 40;
//            cfm->info.slv_params.slave_latency  = 0;
//            cfm->info.slv_params.conn_timeout    = 500;

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

        bx_pm_lock( BX_PM_ALL );
        struct gapc_connection_cfm * cfm = KE_MSG_ALLOC( GAPC_CONNECTION_CFM,
                                           KE_BUILD_ID( TASK_GAPC, app_env.conidx ), TASK_APP,
                                           gapc_connection_cfm );


        cfm->auth      = app_sec_get_bond_status() ? GAP_AUTH_REQ_NO_MITM_BOND : GAP_AUTH_REQ_NO_MITM_NO_BOND;

//        app_hid_enable_prf( app_env.conhdl );

        ke_msg_send( cfm );
        ke_state_set( dest_id, APPM_CONNECTED );
        bx_public( us_ble_id(), BXM_BLE_CONNECTED, 0, 0 );

		bx_pm_lock( BX_PM_ALL );  //开启全速运行
        if ( app_sec_get_bond_status() == false ) {
            //Ask for the peer device to either start encryption
            app_sec_send_security_req( app_env.conidx );
        }

    } else {
        bx_public( us_ble_id(), BXM_BLE_DISCONNECTED, 0, 0 );
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
    ke_state_set( TASK_APP, APPM_READY );
    bx_public( us_ble_id(), BXM_BLE_DISCONNECTED, 0, 0 );
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

    if ( state == APPM_CREATE_DB ) {
        if( param->prf_task_id == TASK_ID_BXOTAS ) {
            osapp_bxotas_config();
        }
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
    static uint8_t utils_flag = 0;

    switch ( src_task_id ) {

        case ( TASK_ID_GAPC ): {

            if ( ( msgid >= GAPC_BOND_CMD ) &&
                 ( msgid <= GAPC_SECURITY_IND ) ) {
                msg_pol = appm_get_handler( &app_sec_table_handler, msgid, param, src_id );
            }

            // else drop the message
        }
        break;

        case ( TASK_ID_HOGPD ): {
            msg_pol = appm_get_handler( &app_hid_table_handler, msgid, param, src_id );
        }
        break;


        case ( TASK_ID_DISS ): {
            msg_pol = appm_get_handler( &app_dis_table_handler, msgid, param, src_id );

        }
        break;



        default:
//            if (msgid == APP_HID_MOUSE_TIMEOUT_TIMER)
//            {
//                msg_pol = appm_get_handler(&app_hid_table_handler, msgid, param, src_id);
//            }
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

//    struct gapc_param_update_cfm * cfm = KE_MSG_ALLOC( GAPC_PARAM_UPDATE_CFM,
//                                                     TASK_GAPC, TASK_APP,
//                                                     gapc_param_update_cfm );


    bxsh_logln( "param_update_cfm" );
//    cfm->accept = 0x01;
    cfm->accept = true;
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
static void osapp_bxotas_start_req_ind_handler( ke_msg_id_t const msgid, struct bxotas_start_req_ind const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    struct bxotas_start_cfm * cfm = KE_MSG_ALLOC( BXOTAS_START_CFM,
                                    src_id, dest_id,
                                    bxotas_start_cfm );
    cfm->status = OTA_REQ_ACCEPTED;
    ke_msg_send( cfm );

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void osapp_bxotas_finish_ind_handler( ke_msg_id_t const msgid, void const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    bxsh_logln( "osapp_bxotas_finish_ind_handler" );
    u32 time = 1000000;
    while( time-- > 0 ) {
        __asm( "nop" );
    }
    platform_reset( 0 );
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int osapp_gapc_param_update_ind( ke_msg_id_t const msgid,
                                        struct gapc_param_updated_ind * param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id )
{

    bxsh_logln( "param->con_interval:%f", param->con_interval * 1.25 );
    bxsh_logln( "param->con_latency:%u", param->con_latency );
    bxsh_logln( "param->sup_to:%u", param->sup_to * 10 );
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
    {BXOTAS_START_REQ_IND,      ( ke_msg_func_t )osapp_bxotas_start_req_ind_handler},
    {BXOTAS_FINISH_IND,         ( ke_msg_func_t )osapp_bxotas_finish_ind_handler},
    {GATTC_CMP_EVT,             ( ke_msg_func_t )gattc_cmp_evt_handler},
    {GAPC_PARAM_UPDATED_IND,    ( ke_msg_func_t )osapp_gapc_param_update_ind},
};

const struct ke_state_handler appm_default_handler = KE_STATE_HANDLER( appm_default_state );
ke_state_t appm_state[1];

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
