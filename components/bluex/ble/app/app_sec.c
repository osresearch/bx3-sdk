/**
 ****************************************************************************************
 *
 * @file app_sec.c
 *
 * @brief Application Security Entry Point
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APP
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"
#include <stdbool.h>


#include <string.h>
#include "co_math.h"
#include "gapc_task.h"      // GAP Controller Task API Definition
#include "gapm_task.h"      // GAPM task API definition
#include "gap.h"            // GAP Definition
#include "gapc.h"           // GAPC Definition
#include "gapm.h"
#include "prf_types.h"

//#include "user_ble.h"            // Application API Definition
#include "app_sec.h"        // Application Security API Definition
//#include "user_ble_task.h"       // Application Manager API Definition

#include "bx_kernel.h"
//#include "user_service_ble.h"

//#if (DISPLAY_SUPPORT)
//#include "app_display.h"    // Display Application Definitions
//#endif //(DISPLAY_SUPPORT)

#if (NVDS_SUPPORT)
#include "nvds.h"           // NVDS API Definitions
#endif //(NVDS_SUPPORT)

//#ifdef BLE_APP_AM0
//#include "am0_app.h"
//#endif // BLE_APP_AM0

#include "bx_pm.h"
//#include "bx_shell.h"
#include "flash_wrapper.h"
//#include "user_app.h"
#include "app.h"
//bool app_sec_get_bond_status( void );

#include "ble.h"
/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Application Security Environment Structure
struct app_sec_env_tag app_sec_env;




//#include "log.h"
//extern u32 sys_tick;
//#define bx_rtt_log(fmt,args...)                             \
//do                                                          \
//{                                                           \
//    LOG_RAW("%10u SEC-> ",sys_tick);                        \
//    LOG_RAW( fmt,##args);                                   \
//    LOG_RAW( "\n");                                         \
//}while(0)

#define bx_rtt_log(fmt,args...) ( ( void ) 0U )

/*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void app_sec_init(void)
{
    /*------------------------------------------------------
     * RETRIEVE BOND STATUS
     *------------------------------------------------------*/

    uint8_t length = NVDS_LEN_PERIPH_BONDED;


    uint8_t sec_buf[256] = {0};
    flash_std_read(  APP_SEC_OFFSET, FLASH_SIZE, sec_buf );


    if( sec_buf[APP_SEC_BOND_STATE_OFFSET] == 0xFF ) {
        app_sec_env.bonded = false;
    } else {
        app_sec_env.bonded = sec_buf[APP_SEC_BOND_STATE_OFFSET];
    }

    if ( ( app_sec_env.bonded != true ) && ( app_sec_env.bonded != false ) ) {
        app_sec_env.bonded = false;
    }

    bx_rtt_log( "app_sec_init\t\tapp_sec_env.bonded = %x", app_sec_env.bonded );



}


void app_sec_remove_bond( void )
{


    uint16_t ntf_cfg = PRF_CLI_STOP_NTFIND;

    // Check if we are well bonded
    if ( app_sec_env.bonded == true ) {

        bx_rtt_log( "!#########################app_sec_remove_bond" );

        // Update the environment variable
        app_sec_env.bonded = false;
        uint8_t sec_buf[256] = {0};

        flash_std_read(   APP_SEC_OFFSET, FLASH_SIZE, sec_buf );

        flash_erase( APP_SEC_OFFSET, Sector_Erase );

        sec_buf[APP_SEC_BOND_STATE_OFFSET] = app_sec_env.bonded;
        flash_program( APP_SEC_OFFSET, FLASH_SIZE,  sec_buf );

    }
}

void app_sec_bond_data_save( void * data )
{
    bx_rtt_log( "!#########################app_sec_bond_data_save" );
    uint8_t sec_buf[256] = {0};
//            bx_pm_lock( BX_PM_FLASH );
    flash_std_read(  APP_SEC_OFFSET, FLASH_SIZE, sec_buf );
    flash_erase( APP_SEC_OFFSET, Sector_Erase );

    sec_buf[APP_SEC_BOND_STATE_OFFSET] = app_sec_env.bonded;
    memcpy( &sec_buf[APP_SEC_LTK_OFFSET], app_sec_env.sec_ltk, NVDS_LEN_LTK );

    memcpy( &sec_buf[APP_SEC_PEER_IRK_OFFSET], app_sec_env.peer_irk, NVDS_LEN_PEER_IRK );
    memcpy( &sec_buf[APP_SEC_BD_ADDR_OFFSET], app_sec_env.bdaddr, NVDS_LEN_PEER_BD_ADDRESS );
    flash_program(  APP_SEC_OFFSET, FLASH_SIZE,  sec_buf );
//            bx_pm_unlock( BX_PM_FLASH );
}

void app_sec_update_param( void * data )
{
    struct gapc_conn_param conn_param;
    conn_param.intv_min = CONN_INTERVAL_MIN;//ble_svc.con_min_intv;
    conn_param.intv_max = CONN_INTERVAL_MAX;//ble_svc.con_max_intv;
    conn_param.latency = SLAVE_LATENCY;//ble_svc.latency;
    conn_param.time_out = CONN_TIMEOUT;//ble_svc.con_param_timeout;
    ble_update_con_param( &conn_param );

}

void app_sec_send_security_req( uint8_t conidx )
{
    bx_rtt_log( "!#########################app_sec_send_security_req" );

    // Send security request
    struct gapc_security_cmd * cmd = KE_MSG_ALLOC( GAPC_SECURITY_CMD,
                                     KE_BUILD_ID( TASK_GAPC, conidx ), TASK_APP,
                                     gapc_security_cmd );

    cmd->operation = GAPC_SECURITY_REQ;

    cmd->auth      = GAP_AUTH_REQ_NO_MITM_BOND;//GAP_AUTH_REQ_MITM_BOND;


    // Send the message
    ke_msg_send( cmd );
}



/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */

static int gapc_bond_req_ind_handler( ke_msg_id_t const msgid,
                                      struct gapc_bond_req_ind const * param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id )
{


    // Prepare the GAPC_BOND_CFM message
    struct gapc_bond_cfm * cfm = KE_MSG_ALLOC( GAPC_BOND_CFM,
                                 src_id, TASK_APP,
                                 gapc_bond_cfm );

    bx_rtt_log( "gapc_bond_req_ind_handler\tparam->request = %d", param->request );

    switch ( param->request ) {
        case ( GAPC_PAIRING_REQ ): {

            cfm->request = GAPC_PAIRING_RSP;
#ifndef BLE_APP_AM0
            cfm->accept  = false;
            app_sec_remove_bond();
            // Check if we are already bonded (Only one bonded connection is supported)
            if ( !app_sec_env.bonded )
#endif // !BLE_APP_AM0
            {
                bx_rtt_log( "already bonded\r\n" );
                cfm->accept  = true;
                // Pairing Features
                cfm->data.pairing_feat.auth      = GAP_AUTH_REQ_NO_MITM_BOND;

                cfm->data.pairing_feat.iocap     = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
                cfm->data.pairing_feat.key_size  = 16;
                cfm->data.pairing_feat.oob       = GAP_OOB_AUTH_DATA_NOT_PRESENT;

                cfm->data.pairing_feat.sec_req   = GAP_SEC1_NOAUTH_PAIR_ENC;
                cfm->data.pairing_feat.ikey_dist = GAP_KDIST_ENCKEY | GAP_KDIST_IDKEY;//GAP_KDIST_NONE;
                cfm->data.pairing_feat.rkey_dist = GAP_KDIST_ENCKEY | GAP_KDIST_IDKEY;//GAP_KDIST_ENCKEY;


            }
        }
        break;

        case ( GAPC_LTK_EXCH ): {
            bx_rtt_log( "GAPC_LTK_EXCH\r\n" );
            // Counter
            uint8_t counter;

            cfm->accept  = true;
            cfm->request = GAPC_LTK_EXCH;

            // Generate all the values
            cfm->data.ltk.ediv = ( uint16_t )co_rand_word();

            for ( counter = 0; counter < RAND_NB_LEN; counter++ ) {
                cfm->data.ltk.ltk.key[counter]    = ( uint8_t )co_rand_word();
                cfm->data.ltk.randnb.nb[counter] = ( uint8_t )co_rand_word();
            }

            for ( counter = RAND_NB_LEN; counter < KEY_LEN; counter++ ) {
                cfm->data.ltk.ltk.key[counter]    = ( uint8_t )co_rand_word();
            }


            // Store the generated value in NVDS
            memcpy( &app_sec_env.sec_ltk, &cfm->data.ltk, NVDS_LEN_LTK );
        }
        break;


        case ( GAPC_IRK_EXCH ): {
            bx_rtt_log( "GAPC_IRK_EXCH\r\n" );

            uint8_t addr_len = BD_ADDR_LEN;


            bx_rtt_log( "GAPC_IRK_EXCH2\r\n" );
            cfm->accept  = true;
            cfm->request = GAPC_IRK_EXCH;

            // Load IRK
            memcpy( cfm->data.irk.irk.key, app_env.loc_irk, KEY_LEN );
            // load device address
            cfm->data.irk.addr.addr_type = ADDR_PUBLIC;
            uint8_t sec_buf[256] = {0};
            flash_std_read(  APP_SEC_OFFSET, FLASH_SIZE, sec_buf );
            memcpy( cfm->data.irk.addr.addr.addr, &sec_buf[APP_SEC_BD_ADDR_OFFSET], addr_len );



//              ef_get_env_blob( bd_addr, cfm->data.irk.addr.addr.addr, addr_len ,NULL);

        }
        break;
        case ( GAPC_TK_EXCH ): {
            bx_rtt_log( "GAPC_TK_EXCH\r\n" );
            // Generate a PIN Code- (Between 100000 and 999999)
            uint32_t pin_code = ( 100000 + ( co_rand_word() % 900000 ) );


            cfm->accept  = true;
            cfm->request = GAPC_TK_EXCH;

            // Set the TK value
            memset( cfm->data.tk.key, 0, KEY_LEN );

            cfm->data.tk.key[0] = ( uint8_t )( ( pin_code & 0x000000FF ) >>  0 );
            cfm->data.tk.key[1] = ( uint8_t )( ( pin_code & 0x0000FF00 ) >>  8 );
            cfm->data.tk.key[2] = ( uint8_t )( ( pin_code & 0x00FF0000 ) >> 16 );
            cfm->data.tk.key[3] = ( uint8_t )( ( pin_code & 0xFF000000 ) >> 24 );
        }
        break;

        default: {
            ASSERT_ERR( 0 );
        }
        break;
    }

    // Send the message
    ke_msg_send( cfm );

    return ( KE_MSG_CONSUMED );
}


static int gapc_bond_ind_handler( ke_msg_id_t const msgid,
                                  struct gapc_bond_ind const * param,
                                  ke_task_id_t const dest_id,
                                  ke_task_id_t const src_id )
{

    bx_rtt_log( "gapc_bond_ind_handler\tparam->info = %d", param->info );

    switch ( param->info ) {
        case ( GAPC_PAIRING_SUCCEED ): {
            bx_rtt_log( "bond succees\r\n" );

            // Update the bonding status in the environment
            app_sec_env.bonded = true;



            // Set the BD Address of the peer device in NVDS
            memcpy( &app_sec_env.bdaddr, ( uint8_t * )gapc_get_bdaddr( app_env.conidx, SMPC_INFO_PEER ), NVDS_LEN_PEER_BD_ADDRESS );


            bx_dwork( app_sec_update_param, NULL, 3000, 1 );
            bx_dwork( app_sec_bond_data_save, NULL, 4000, 1 );
        }
        break;

        case ( GAPC_REPEATED_ATTEMPT ): {
            bx_rtt_log( "bond disconnect\r\n" );
        }
        break;

        case ( GAPC_IRK_EXCH ): {

            bx_rtt_log( "GAPC_IRK_EXCH3\r\n" );
            // Store peer identity in NVDS
            memcpy( &app_sec_env.peer_irk, ( uint8_t * )&param->data.irk, NVDS_LEN_PEER_IRK );
        }
        break;

        case ( GAPC_PAIRING_FAILED ): {
            bx_rtt_log( "bond FAILED\r\n" );
            app_sec_send_security_req( 0 );
        }
        break;

        // In Secure Connections we get BOND_IND with SMPC calculated LTK
        case ( GAPC_LTK_EXCH ) : {
            bx_rtt_log( "GAPC_LTK_EXCH2\r\n" );
            if ( app_env.sec_con_enabled == true ) {

                bx_rtt_log( "GAPC_LTK_EXCH3" );
                // Store LTK in NVDS
                memcpy( &app_sec_env.sec_ltk, &param->data.ltk.ltk.key[0], NVDS_LEN_LTK );
            }
        }
        break;

        default: {
            ASSERT_ERR( 0 );
        }
        break;
    }

    return ( KE_MSG_CONSUMED );
}

static int gapc_encrypt_req_ind_handler( ke_msg_id_t const msgid,
        struct gapc_encrypt_req_ind const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{

    bx_rtt_log( "encrypt msgid\r\n" );
    // LTK value
    struct gapc_ltk ltk;
    // Length
    uint8_t length = NVDS_LEN_LTK;

    // Prepare the GAPC_ENCRYPT_CFM message
    struct gapc_encrypt_cfm * cfm = KE_MSG_ALLOC( GAPC_ENCRYPT_CFM,
                                    src_id, TASK_APP,
                                    gapc_encrypt_cfm );

    cfm->found    = true;

//    if ( app_sec_env.bonded ) {
    // Retrieve the required informations from NVDS
//    ef_get_env_blob( sec_ltk, &ltk, length, NULL );

    uint8_t sec_buf[256] = {0};
    flash_std_read(  APP_SEC_OFFSET, FLASH_SIZE, sec_buf );
    memcpy( &ltk, &sec_buf[APP_SEC_LTK_OFFSET], length );

    {
        // Check if the provided EDIV and Rand Nb values match with the stored values
        if ( ( param->ediv == ltk.ediv ) &&
             !memcmp( &param->rand_nb.nb[0], &ltk.randnb.nb[0], sizeof( struct rand_nb ) ) ) {
            bx_rtt_log( "else encrypt msgid is :%d\r\n", msgid );
            bx_rtt_log( "else encrypt src_id is :%d\r\n", src_id );
            cfm->found    = true;
            cfm->key_size = 16;
            memcpy( &cfm->ltk, &ltk.ltk, sizeof( struct gap_sec_key ) );
        }
        /*
         * else we are bonded with another device, disconnect the link
         */
    }
//      else {
//            ASSERT_ERR( 0 );
//        }
//    }

    /*
     * else the peer device is not known, an error should trigger a new pairing procedure.
     */

    // Send the message
    ke_msg_send( cfm );

    return ( KE_MSG_CONSUMED );
}


static int gapc_encrypt_ind_handler( ke_msg_id_t const msgid,
                                     struct gapc_encrypt_ind const * param,
                                     ke_task_id_t const dest_id,
                                     ke_task_id_t const src_id )
{
    // encryption/ re-encryption succeeded

    bx_rtt_log( "auth is :%d\r\n", param->auth );


    return ( KE_MSG_CONSUMED );
}

static int app_sec_msg_dflt_handler( ke_msg_id_t const msgid,
                                     void * param,
                                     ke_task_id_t const dest_id,
                                     ke_task_id_t const src_id )
{
    // Drop the message

    return ( KE_MSG_CONSUMED );
}

static void app_gapm_cmp_evt_handler( ke_msg_id_t const msgid, struct gapm_cmp_evt const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    struct gapm_cmp_evt const * cmp_evt = param;

    bx_rtt_log( "app_sec\tapp_gapm_cmp_evt_handler\tcmp_evt->operation = %d\n", cmp_evt->operation );
    switch( cmp_evt->operation ) {
        case GAPM_RESOLV_ADDR:
            if( cmp_evt->status == GAP_ERR_NOT_FOUND ) {
                bx_rtt_log( "bond manage  IRK matched fail!!!\n" );
            }
            break;
        case GAPM_ADV_UNDIRECT:
        case GAPM_ADV_DIRECT:
        case GAPM_ADV_DIRECT_LDC:
            if( cmp_evt->status == GAP_ERR_NO_ERROR ) {
                bx_rtt_log( "===slave===" );

            }
            break;
        case GAPM_CONNECTION_DIRECT:
        case GAPM_CONNECTION_AUTO:
        case GAPM_CONNECTION_SELECTIVE:
            if( cmp_evt->status == GAP_ERR_NO_ERROR ) {
                bx_rtt_log( "===master===" );

            }
            break;
        default:
            break;
    }
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
    // ke_state_set( TASK_APP, APPM_READY );
    bx_rtt_log( "=== app_sec ===== gapc_disconnect_ind_handler ========dest_id = %d\t src_id = %d\tgapc_disconnect_ind.reason = %d=========", dest_id, src_id, param->reason );
//    bx_public( us_ble_id(), BXM_BLE_DISCONNECTED, 0, 0x02 );

    /*  if(app_sec_env.bonded == true)
          {
          app_sec_remove_bond();
    platform_reset(RESET_MEM_ALLOC_FAIL);
          }*/
    return ( KE_MSG_CONSUMED );
}

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler app_sec_msg_handler_list[] = {
    // Note: first message is latest message checked by kernel so default is put on top.
    ///GAPM event complete
    {GAPM_CMP_EVT, ( ke_msg_func_t )app_gapm_cmp_evt_handler},

    {KE_MSG_DEFAULT_HANDLER,  ( ke_msg_func_t )app_sec_msg_dflt_handler},

    {GAPC_BOND_REQ_IND,       ( ke_msg_func_t )gapc_bond_req_ind_handler},
    {GAPC_BOND_IND,           ( ke_msg_func_t )gapc_bond_ind_handler},

    {GAPC_ENCRYPT_REQ_IND,    ( ke_msg_func_t )gapc_encrypt_req_ind_handler},
    {GAPC_ENCRYPT_IND,        ( ke_msg_func_t )gapc_encrypt_ind_handler},

    {GAPC_DISCONNECT_IND,       ( ke_msg_func_t )gapc_disconnect_ind_handler},
};

const struct ke_state_handler app_sec_table_handler =
{&app_sec_msg_handler_list[0], ( sizeof( app_sec_msg_handler_list ) / sizeof( struct ke_msg_handler ) )};



bool app_sec_get_bond_status( void )
{
    return app_sec_env.bonded;
}

/// @} APP
