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

#if (BLE_APP_SEC)

#include <string.h>
#include "co_math.h"
#include "gapc_task.h"      // GAP Controller Task API Definition
#include "gapm_task.h"      // GAPM task API definition
#include "gap.h"            // GAP Definition
#include "gapc.h"           // GAPC Definition
#include "gapm.h"
#include "prf_types.h"

#include "user_ble.h"            // Application API Definition
#include "app_sec.h"        // Application Security API Definition
#include "user_ble_task.h"       // Application Manager API Definition

#if (DISPLAY_SUPPORT)
#include "app_display.h"    // Display Application Definitions
#endif //(DISPLAY_SUPPORT)

#if (NVDS_SUPPORT)
#include "nvds.h"           // NVDS API Definitions
#endif //(NVDS_SUPPORT)

#ifdef BLE_APP_AM0
#include "am0_app.h"
#endif // BLE_APP_AM0

#include "user_service_ble.h"
#include "bx_kernel.h"

#include <easyflash.h>
#include "bx_shell.h"
/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */



char ltk_key[] = "ltk_key";
char status[] = "bond_status";
char BD_ADDR[] = "ADDRRR";
char IR_KEY[] = "ir_key";
/// Application Security Environment Structure
struct app_sec_env_tag app_sec_env;

/*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void app_sec_init()
{
    uint8_t bond_status;
    /*------------------------------------------------------
     * RETRIEVE BOND STATUS
     *------------------------------------------------------*/
    uint8_t length = NVDS_LEN_PERIPH_BONDED;

    ef_get_env_blob( status, &bond_status, 1, NULL );
    if( bond_status == 0xff ) {
        app_sec_env.bonded = false;
    } else {
        app_sec_env.bonded = bond_status;
    }

    if ( ( app_sec_env.bonded != true ) && ( app_sec_env.bonded != false ) ) {
        app_sec_env.bonded = false;
    }

}


void app_sec_remove_bond( void )
{
    // Check if we are well bonded
    if ( app_sec_env.bonded == true ) {
        // Update the environment variable
        app_sec_env.bonded = false;

        ef_set_env_blob( status, ( uint8_t * )&app_sec_env.bonded, 1 );

    }
}


void app_sec_send_security_req( uint8_t conidx )
{
    // Send security request
    struct gapc_security_cmd * cmd = KE_MSG_ALLOC( GAPC_SECURITY_CMD,
                                     TASK_GAPC, TASK_APP,
                                     gapc_security_cmd );

    cmd->operation = GAPC_SECURITY_REQ;

    cmd->auth      = GAP_AUTH_REQ_MITM_BOND;
    // Send the message
    ke_msg_send( cmd );
}

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */

static char gapc_bond_info_str[][30] = {
    "GAPC_PAIRING_REQ",
    "GAPC_PAIRING_RSP",
    "GAPC_PAIRING_SUCCEED",
    "GAPC_PAIRING_FAILED",
    "GAPC_TK_EXCH",
    "GAPC_IRK_EXCH",
    "GAPC_CSRK_EXCH",
    "GAPC_LTK_EXCH",
    "GAPC_REPEATED_ATTEMPT",
    "GAPC_OOB_EXCH",
    "GAPC_NC_EXCH",
};
static int gapc_bond_req_ind_handler( ke_msg_id_t const msgid,
                                      struct gapc_bond_req_ind const * param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id )
{
    // Prepare the GAPC_BOND_CFM message
    struct gapc_bond_cfm * cfm = KE_MSG_ALLOC( GAPC_BOND_CFM,
                                 src_id, TASK_APP,
                                 gapc_bond_cfm );
    bxsh_logln( "gapc_bond_req_ind_handler:%s", gapc_bond_info_str[param->request] );
    switch ( param->request ) {
        case ( GAPC_PAIRING_REQ ): {
            cfm->request = GAPC_PAIRING_RSP;
            // Check if we are already bonded (Only one bonded connection is supported)
            if ( !app_sec_env.bonded ) {
                cfm->accept  = true;
                cfm->data.pairing_feat.auth      = GAP_AUTH_REQ_NO_MITM_BOND;//GAP_AUTH_REQ_MITM_BOND;

                cfm->data.pairing_feat.auth      = GAP_AUTH_REQ_NO_MITM_BOND;//GAP_AUTH_REQ_MITM_BOND;
//                app_env.sec_con_enabled = true;
                cfm->data.pairing_feat.iocap     = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
                cfm->data.pairing_feat.key_size  = 16;
                cfm->data.pairing_feat.oob       = GAP_OOB_AUTH_DATA_NOT_PRESENT;
                cfm->data.pairing_feat.sec_req   = GAP_SEC1_NOAUTH_PAIR_ENC;//GAP_NO_SEC;//

                cfm->data.pairing_feat.ikey_dist = GAP_KDIST_ENCKEY | GAP_KDIST_IDKEY;//GAP_KDIST_NONE;GAP_KDIST_IDKEY
                cfm->data.pairing_feat.rkey_dist = GAP_KDIST_ENCKEY | GAP_KDIST_IDKEY;//GAP_KDIST_ENCKEY;

            }
        }
        break;

        case ( GAPC_LTK_EXCH ): {
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

            ef_set_env_blob( ltk_key, ( uint8_t * )&cfm->data.ltk, NVDS_LEN_LTK );

        }
        break;

        case ( GAPC_IRK_EXCH ): {

            uint8_t addr_len = BD_ADDR_LEN;
            cfm->accept  = true;
            cfm->request = GAPC_IRK_EXCH;
            // Load IRK
            memcpy( cfm->data.irk.irk.key, app_env.loc_irk, KEY_LEN );
            // load device address
            cfm->data.irk.addr.addr_type = ADDR_PUBLIC;

            ef_get_env_blob( BD_ADDR, cfm->data.irk.addr.addr.addr, addr_len, NULL );

        }
        break;

        case ( GAPC_TK_EXCH ): {
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

void appm_disconnect( void )
{
    struct gapc_disconnect_cmd * cmd = KE_MSG_ALLOC( GAPC_DISCONNECT_CMD,
                                       KE_BUILD_ID( TASK_GAPC, app_env.conidx ), TASK_APP,
                                       gapc_disconnect_cmd );

    cmd->operation = GAPC_DISCONNECT;
    cmd->reason    = CO_ERROR_REMOTE_USER_TERM_CON;

    // Send the message
    ke_msg_send( cmd );
}

static int gapc_bond_ind_handler( ke_msg_id_t const msgid,
                                  struct gapc_bond_ind const * param,
                                  ke_task_id_t const dest_id,
                                  ke_task_id_t const src_id )
{
    bxsh_logln( "gapc_bond_ind_handler:%s", gapc_bond_info_str[param->info] );
    switch ( param->info ) {

        case ( GAPC_PAIRING_SUCCEED ): {
            bx_public( us_ble_id(), BXM_BLE_BOND_SUCCEED, 0, 0 );
            // Update the bonding status in the environment
            app_sec_env.bonded = true;

            // Update the bonding status in the environment

            ef_set_env_blob( status, ( uint8_t * )&app_sec_env.bonded, 1 );
            // Set the BD Address of the peer device in NVDS

            ef_set_env_blob( BD_ADDR, ( uint8_t * )gapc_get_bdaddr( 0, SMPC_INFO_PEER ), NVDS_LEN_PEER_BD_ADDRESS );

        }
        break;

        case ( GAPC_REPEATED_ATTEMPT ): {
//            appm_disconnect();
        } break;

        case ( GAPC_IRK_EXCH ): {
            // Store peer identity in NVDS


            ef_set_env_blob( IR_KEY, ( uint8_t * )&param->data.irk, NVDS_LEN_PEER_IRK );

        }
        break;

        case ( GAPC_PAIRING_FAILED ): {
            app_sec_send_security_req( 0 );
        }
        break;

        // In Secure Connections we get BOND_IND with SMPC calculated LTK
        case ( GAPC_LTK_EXCH ) : {

            if ( app_env.sec_con_enabled == true ) {
                // Store LTK in NVDS

                ef_set_env_blob( ltk_key, ( uint8_t * )&param->data.ltk.ltk.key[0], NVDS_LEN_LTK );

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

    // LTK value
    struct gapc_ltk ltk;
    // Length
    uint8_t length = NVDS_LEN_LTK;
    // Prepare the GAPC_ENCRYPT_CFM message
    struct gapc_encrypt_cfm * cfm = KE_MSG_ALLOC( GAPC_ENCRYPT_CFM,
                                    src_id, TASK_APP,
                                    gapc_encrypt_cfm );

    cfm->found    = false;

    if ( app_sec_env.bonded ) {

        // Retrieve the required informations from NVDS

        ef_get_env_blob( ltk_key, ( uint8_t * )&ltk, length, NULL );

        // Check if the provided EDIV and Rand Nb values match with the stored values
        if ( ( param->ediv == ltk.ediv ) &&
             !memcmp( &param->rand_nb.nb[0], &ltk.randnb.nb[0], sizeof( struct rand_nb ) ) ) {
            cfm->found    = true;
            cfm->key_size = 16;
            memcpy( &cfm->ltk, &ltk.ltk, sizeof( struct gap_sec_key ) );
        }
        /*
         * else we are bonded with another device, disconnect the link
         */


    }
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

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler app_sec_msg_handler_list[] = {
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,  ( ke_msg_func_t )app_sec_msg_dflt_handler},

    {GAPC_BOND_REQ_IND,       ( ke_msg_func_t )gapc_bond_req_ind_handler},
    {GAPC_BOND_IND,           ( ke_msg_func_t )gapc_bond_ind_handler},

    {GAPC_ENCRYPT_REQ_IND,    ( ke_msg_func_t )gapc_encrypt_req_ind_handler},
    {GAPC_ENCRYPT_IND,        ( ke_msg_func_t )gapc_encrypt_ind_handler},
};

const struct ke_state_handler app_sec_table_handler =
{&app_sec_msg_handler_list[0], ( sizeof( app_sec_msg_handler_list ) / sizeof( struct ke_msg_handler ) )};

#endif //(BLE_APP_SEC)


bool app_sec_get_bond_status( void )
{
#if (BLE_APP_SEC)
    return app_sec_env.bonded;
#else
    return false;
#endif //(BLE_APP_SEC)
}

/// @} APP
