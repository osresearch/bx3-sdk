/**
 ****************************************************************************************
 *
 * @file appm_task.c
 *
 * @brief RW APP Task implementation
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APPTASK
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"          // SW configuration


#include "app_task.h"             // Application Manager Task API
#include "app.h"                  // Application Manager Definition
#include "gapc_task.h"            // GAP Controller Task API
#include "gapm_task.h"            // GAP Manager Task API
#include "arch.h"                 // Platform Definitions
#include <string.h>


#include "app_dis.h"              // Device Information Module Definition
#include "diss_task.h"



#include "bx_kernel_timer.h"

#include "user_profile.h"
#include "user_profile_task.h"

#include "bxotas.h"
#include "bxotas_task.h"

#include "bx_kernel.h"
#include "bx_shell.h"
#include "bx_service_ble.h"
/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

static uint8_t appm_get_handler( const struct ke_state_handler * handler_list,
                                 ke_msg_id_t msgid,
                                 void * param,
                                 ke_task_id_t src_id )
{
//    bxsh_logln("appm_get_handler");
    // Counter
    uint8_t counter;

    // Get the message handler function by parsing the message table
    for ( counter = handler_list->msg_cnt; 0 < counter; counter-- ) {
        struct ke_msg_handler * handler = ( struct ke_msg_handler * )( ( handler_list->msg_table + counter - 1 ) );

        if ( ( handler->id == msgid ) ||
             ( handler->id == KE_MSG_DEFAULT_HANDLER ) ) {
            // If handler is NULL, message should not have been received in this state
            ASSERT_ERR( handler->func );

            return ( uint8_t )( handler->func( msgid, param, TASK_APP, src_id ) );
        }
    }

    // If we are here no handler has been found, drop the message
    return ( KE_MSG_CONSUMED );
}

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Handles ready indication from the GAP. - Reset the stack
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapm_device_ready_ind_handler( ke_msg_id_t const msgid,
        void const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{
    // Application has not been initialized
    ASSERT_ERR( ke_state_get( dest_id ) == APPM_INIT );

    // Reset the stack
    struct gapm_reset_cmd * cmd = KE_MSG_ALLOC( GAPM_RESET_CMD,
                                  TASK_GAPM, TASK_APP,
                                  gapm_reset_cmd );

    cmd->operation = GAPM_RESET;

    ke_msg_send( cmd );

    return ( KE_MSG_CONSUMED );
}

/**
 ****************************************************************************************
 * @brief Handles GAP manager command complete events.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapm_cmp_evt_handler( ke_msg_id_t const msgid,
                                 struct gapm_cmp_evt const * param,
                                 ke_task_id_t const dest_id,
                                 ke_task_id_t const src_id )
{
    switch( param->operation ) {
        // Reset completed
        case ( GAPM_RESET ): {
            if( param->status == GAP_ERR_NO_ERROR ) {

                // Set Device configuration
                struct gapm_set_dev_config_cmd * cmd = KE_MSG_ALLOC( GAPM_SET_DEV_CONFIG_CMD,
                                                       TASK_GAPM, TASK_APP,
                                                       gapm_set_dev_config_cmd );
                // Set the operation
                cmd->operation = GAPM_SET_DEV_CONFIG;
                // Set the device role - Peripheral
                cmd->role      = GAP_ROLE_PERIPHERAL;
                // Set Data length parameters

                cmd->pairing_mode = GAPM_PAIRING_LEGACY;

                cmd->sugg_max_tx_octets = BLE_MIN_OCTETS;
                cmd->sugg_max_tx_time   = BLE_MIN_TIME;


                // load IRK
                memcpy( cmd->irk.key, app_env.loc_irk, KEY_LEN );

                // Send message
                ke_msg_send( cmd );
                //ke_msg_send_basic( SFTIM_MSG_CREAT_TIMER,TASK_ID_USER_TIMER,TASK_ID_USER_TIMER );
                ke_msg_send_basic( BKT_MSG_CREAT_TIMER, TASK_BX_KERNEL_TIMER, TASK_BX_KERNEL_TIMER );
                bx_post(0,BXM_SYS_READY,0,0);
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
                // Generate a second random number
                app_env.rand_cnt++;
                struct gapm_gen_rand_nb_cmd * cmd = KE_MSG_ALLOC( GAPM_GEN_RAND_NB_CMD,
                                                    TASK_GAPM, TASK_APP,
                                                    gapm_gen_rand_nb_cmd );

                cmd->operation = GAPM_GEN_RAND_NB;
                ke_msg_send( cmd );
            } else {
                // Prepare the GAPM_START_ADVERTISE_CMD message
                struct gapm_set_irk_cmd * cmd = KE_MSG_ALLOC( GAPM_SET_IRK_CMD,
                                                TASK_GAPM, TASK_APP,
                                                gapm_set_irk_cmd );

                app_env.rand_cnt = 0;
                /// GAPM requested operation:
                ///  - GAPM_SET_IRK: Set device configuration
                cmd->operation = GAPM_SET_IRK;

                memcpy( &cmd->irk.key[0], &app_env.loc_irk[0], KEY_LEN );

                ke_msg_send( cmd );
            }
        }
        break;

        case ( GAPM_SET_IRK ): {
            // ASSERT_INFO(param->status == GAP_ERR_NO_ERROR, param->operation, param->status);
            // Add the next requested service
            app_env.rand_cnt = 0;

            if ( !appm_add_svc() ) {
                // Go to the ready state
                ke_state_set( TASK_APP, APPM_READY );

                // No more service to add, start advertising
                appm_start_advertising();
            }
        }
        break;
        // Device Configuration updated
        case ( GAPM_SET_DEV_CONFIG ): {

            ke_state_set( TASK_APP, APPM_CREATE_DB );

            appm_add_svc();
        }
        break;

        default: 
        break;
    }

    return ( KE_MSG_CONSUMED );
}

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
            cfm->info.name.length = appm_get_dev_name( cfm->info.name.value );


            ke_msg_send( cfm );
        }
        break;

        case GAPC_DEV_APPEARANCE: {

            struct gapc_get_dev_info_cfm * cfm = KE_MSG_ALLOC( GAPC_GET_DEV_INFO_CFM,
                                                 src_id, dest_id,
                                                 gapc_get_dev_info_cfm );
            cfm->req = param->req;


            cfm->info.appearance = 0;

            ke_msg_send( cfm );
        }
        break;

        case GAPC_DEV_SLV_PREF_PARAMS: {

            struct gapc_get_dev_info_cfm * cfm = KE_MSG_ALLOC( GAPC_GET_DEV_INFO_CFM,
                                                 src_id, dest_id,
                                                 gapc_get_dev_info_cfm );
            cfm->req = param->req;
            // Slave preferred Connection interval Min
            cfm->info.slv_params.con_intv_min = 8;
            // Slave preferred Connection interval Max
            cfm->info.slv_params.con_intv_max = 10;
            // Slave preferred Connection latency
            cfm->info.slv_params.slave_latency  = 0;
            // Slave preferred Link supervision timeout
            cfm->info.slv_params.conn_timeout    = 200;  // 2s (500*10ms)

            // Send message
            ke_msg_send( cfm );
        }
        break;

        default:
            break;
    }


    return ( KE_MSG_CONSUMED );
}
/**
 ****************************************************************************************
 * @brief Handles GAPC_SET_DEV_INFO_REQ_IND message.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_set_dev_info_req_ind_handler( ke_msg_id_t const msgid,
        struct gapc_set_dev_info_req_ind const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{
    // Set Device configuration
    struct gapc_set_dev_info_cfm * cfm = KE_MSG_ALLOC( GAPC_SET_DEV_INFO_CFM, src_id, dest_id,
                                         gapc_set_dev_info_cfm );
    // Reject to change parameters
    cfm->status = GAP_ERR_REJECTED;
    cfm->req = param->req;

    ke_msg_send( cfm );

    return ( KE_MSG_CONSUMED );
}

/**
 ****************************************************************************************
 * @brief Handles connection complete event from the GAP. Enable all required profiles
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_connection_req_ind_handler( ke_msg_id_t const msgid,
        struct gapc_connection_req_ind const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{
    app_env.conidx = KE_IDX_GET( src_id );

    // Check if the received Connection Handle was valid
    if ( app_env.conidx != GAP_INVALID_CONIDX ) {
        // Retrieve the connection info from the parameters
        app_env.conhdl = param->conhdl;


        // Send connection confirmation
        struct gapc_connection_cfm * cfm = KE_MSG_ALLOC( GAPC_CONNECTION_CFM,
                                           KE_BUILD_ID( TASK_GAPC, app_env.conidx ), TASK_APP,
                                           gapc_connection_cfm );


        cfm->auth      = GAP_AUTH_REQ_NO_MITM_NO_BOND;

        ke_msg_send( cfm );

        bxsh_logln( "connected" );
        
        ke_state_set( dest_id, APPM_CONNECTED );
        
        bx_public( bxs_ble_id(),BXM_BLE_CONNECTED,0,0);

    } else {
        appm_start_advertising();
    }

    return ( KE_MSG_CONSUMED );
}

/**
 ****************************************************************************************
 * @brief Handles GAP controller command complete events.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_cmp_evt_handler( ke_msg_id_t const msgid,
                                 struct gapc_cmp_evt const * param,
                                 ke_task_id_t const dest_id,
                                 ke_task_id_t const src_id )
{
    switch( param->operation ) {
        case ( GAPC_UPDATE_PARAMS ): {
            if ( param->status != GAP_ERR_NO_ERROR ) {
                appm_disconnect();
            }
        } break;

        default: {
        } break;
    }

    return ( KE_MSG_CONSUMED );
}

/**
 ****************************************************************************************
 * @brief Handles disconnection complete event from the GAP.
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapc_disconnect_ind_handler( ke_msg_id_t const msgid,
                                        struct gapc_disconnect_ind const * param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id )
{
    // Go to the ready state
    ke_state_set( TASK_APP, APPM_READY );
    
    bx_public( bxs_ble_id(),BXM_BLE_DISCONNECT,0,0);
    
    appm_start_advertising();

    return ( KE_MSG_CONSUMED );
}


static int gapm_profile_added_ind_handler( ke_msg_id_t const msgid,
        struct gapm_profile_added_ind * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{
    // Current State
    uint8_t state            = ke_state_get( dest_id );

    if ( state == APPM_CREATE_DB ) {
        switch ( param->prf_task_id ) {
            default: /* Nothing to do */
                break;
        }
    } else {
        ASSERT_INFO( 0, state, src_id );
    }

    if( param->prf_task_id == TASK_ID_BXOTAS ) {
        osapp_bxotas_config();
    }
    return KE_MSG_CONSUMED;
}

/**
 ****************************************************************************************
 * @brief Handles reception of all messages sent from the lower layers to the application
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int appm_msg_handler( ke_msg_id_t const msgid,
                             void * param,
                             ke_task_id_t const dest_id,
                             ke_task_id_t const src_id )
{

    ke_task_id_t src_task_id = MSG_T( msgid );

    uint8_t msg_pol          = KE_MSG_CONSUMED;


    switch ( src_task_id ) {

        case ( TASK_ID_DISS ):
            msg_pol = appm_get_handler( &app_dis_table_handler, msgid, param, src_id );
            break;

        default:
            break;
    }
//    bxsh_logln("appm_msg_handler return : %u",msg_pol);
    return ( msg_pol );
}
/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Handles reception of random number generated message
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gapm_gen_rand_nb_ind_handler( ke_msg_id_t const msgid, struct gapm_gen_rand_nb_ind * param,
        ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    if ( app_env.rand_cnt == 1 ) { // First part of IRK
        memcpy( &app_env.loc_irk[0], &param->randnb.nb[0], 8 );
    } else if ( app_env.rand_cnt == 2 ) { // Second part of IRK
        memcpy( &app_env.loc_irk[8], &param->randnb.nb[0], 8 );
    }

    return KE_MSG_CONSUMED;
}
/*
 * GLOBAL VARIABLES DEFINITION
 ****************************************************************************************
 */
/****************************************************************************************
 * @function name : osapp_gapc_param_update_cfm
 * @brief   : this funciton used to replay param update request
 * @param[in] none
 * @param[out] none
 * @return none
 *****************************************************************************************/
void osapp_gapc_param_update_cfm( ke_msg_id_t const msgid, void const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    //bxsh_logln("osapp_gapc_param_update_cfm");
    struct gapc_param_update_cfm * cfm = KE_MSG_ALLOC( GAPC_PARAM_UPDATE_CFM,
                                         src_id, dest_id,
                                         gapc_param_update_cfm );
    cfm->accept = 0x01;
    cfm->ce_len_max = 0xffff;
    cfm->ce_len_min = 0xffff;
    ke_msg_send( cfm );
}

/****************************************************************************************
 * @function name : osapp_bxotas_start_req_ind_handler
 * @brief   :
 * @param[in] none
 * @param[out] none
 * @return none
 *****************************************************************************************/

void osapp_bxotas_start_req_ind_handler( ke_msg_id_t const msgid, struct bxotas_start_req_ind const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    bxsh_logln( "osapp_bxotas_start_req_ind_handler:%d %d", dest_id, src_id );
    struct bxotas_start_cfm * cfm = KE_MSG_ALLOC( BXOTAS_START_CFM,
                                    src_id, dest_id,
                                    bxotas_start_cfm );
    cfm->status = OTA_REQ_ACCEPTED;
    ke_msg_send( cfm );

}

/****************************************************************************************
 * @function name : osapp_bxotas_finish_ind_handler
 * @brief   :
 * @param[in] none
 * @param[out] none
 * @return none
 *****************************************************************************************/
void osapp_bxotas_finish_ind_handler( ke_msg_id_t const msgid, void const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    bxsh_logln( "osapp_bxotas_finish_ind_handler" );
    /* do not reset chip immediately */
    u32 time = 1000000;
    while( time-- > 0 ) {
        __asm( "nop" );
    }
    platform_reset( 0 );
}

/* Default State handlers definition. */
const struct ke_msg_handler appm_default_state[] = {
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,    ( ke_msg_func_t )appm_msg_handler},


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
    //{GAPC_CON_RSSI_IND,(ke_msg_func_t)osapp_conn_rssi_handler},

};

/* Specifies the message handlers that are common to all states. */
const struct ke_state_handler appm_default_handler = KE_STATE_HANDLER( appm_default_state );

/* Defines the place holder for the states of all the task instances. */
ke_state_t appm_state[APP_IDX_MAX];


