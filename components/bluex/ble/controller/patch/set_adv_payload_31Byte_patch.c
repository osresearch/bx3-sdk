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
/* config -------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "rwip_config.h"
#include "rwble_hl.h"
#include <string.h>
#include "co_error.h"
#include "co_bt.h"
#include "co_math.h"
#include "co_version.h"
#include "gap.h"
#include "gattm_task.h"
#include "gapm_task.h"
#include "gapm_util.h"
#include "gapm_int.h"
#include "gapc.h"
#include "gattm.h"
#include "gattc_task.h"
#include "attm.h"
#include "smpm_api.h"
#include "ke_mem.h"
#include "hci.h"

#if (BLE_PROFILES)
#include "prf.h"
#endif

#if (NVDS_SUPPORT)
#include "nvds.h"
#endif

#include "ke_timer.h"
#include "set_adv_payload_31Byte_patch.h"
#include "patch.h"

/* private define ------------------------------------------------------------*/
#if defined(V4_ROM)
#define SET_ADV_PAYLOAD_PATCH_ADDR                      0x1ea84
#elif defined(MP_ROM)
#define SET_ADV_PAYLOAD_PATCH_ADDR                      0x1f484
#else
#error patch version not defined
#endif

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/
#if (BLE_PERIPHERAL || BLE_BROADCASTER)

/**
 ****************************************************************************************
 * @brief Perform an advertising data sanity check
 *
 * @param[in] adv_data           Advertising data
 * @param[in] adv_data_len       Advertising data length
 * @param[in] scan_rsp_data      Scan response data
 * @param[in] scan_rsp_data_len  Scan response data length
 *
 * @return GAP_ERR_NO_ERROR if valid, GAP_ERR_ADV_DATA_INVALID if not valid
 ****************************************************************************************
 */
static uint8_t gapm_adv_sanity_patch( uint8_t * adv_data, uint8_t adv_data_len,
                                      uint8_t * scan_rsp_data, uint8_t scan_rsp_data_len,
                                      uint8_t adv_opcode )
{
    uint8_t status = GAP_ERR_NO_ERROR;
    uint8_t data_type_cursor = 0;


    while( ( data_type_cursor < 2 ) && ( status == GAP_ERR_NO_ERROR ) ) {
        data_type_cursor++;
    }
    return ( status );
}
/**
 ****************************************************************************************
 * @brief Set a random address operation.
 *
 * This function is used by air operations to modify random address in lower layer before
 * starting any air operations.
 *
 *  - If a public address is configured, operation state is set to @ref GAPM_OP_WAIT.
 *
 *  - If a random address should be generated, @ref GAPM_GEN_RAND_ADDR_CMD will be sent to
 *    @ref TASK_GAPM to request random address generation.
 *
 *  - When random address is generated, or provided by operation parameters, address is
 *    set to lower layers.
 *
 * @param op Operation parameters
 *
 ****************************************************************************************
 */
static void gapm_set_address_op( struct gapm_air_operation * op )
{
    // execute current operation state.
    switch( GAPM_GET_OP_STATE( *op ) ) {
        case GAPM_OP_ADDR_GEN: { // Address generation state
            struct gapm_gen_rand_addr_cmd * req = KE_MSG_ALLOC( GAPM_GEN_RAND_ADDR_CMD,
                                                  TASK_GAPM, TASK_GAPM, gapm_gen_rand_addr_cmd );

            req->operation = GAPM_GEN_RAND_ADDR;

            // address type to generate
            switch( op->addr_src ) {
                // Private resolvable address
                case GAPM_GEN_RSLV_ADDR:
                    req->rnd_type = GAP_RSLV_ADDR;
                    break;
                // Private non resolvable address
                case GAPM_GEN_NON_RSLV_ADDR:
                    req->rnd_type = GAP_NON_RSLV_ADDR;
                    break;
                // cannot append
                default:
                    break;
            }

            // send request
            ke_msg_send( req );
        }
        break;

        case GAPM_OP_ADDR_SET: { // Set device random address
            // update lower layer random address.
            struct hci_le_set_rand_addr_cmd * rand_addr = KE_MSG_ALLOC( HCI_COMMAND, 0, HCI_LE_SET_RAND_ADDR_CMD_OPCODE, hci_le_set_rand_addr_cmd );

            /* random address is in operation address (put during address generation
             * or provided by host application
             */
            memcpy( &( rand_addr->rand_addr ), &( gapm_env.addr ), sizeof( bd_addr_t ) );

            // send command
            hci_send_2_controller( rand_addr );

            // start resolvable/ non resolvable address timer to regenerate address if timeout occurs.
            // minimum duration: GAP_TMR_PRIV_ADDR_INT
            ke_timer_set( GAPM_ADDR_RENEW_TO_IND, TASK_GAPM, co_max( gapm_env.renew_dur, GAP_TMR_PRIV_ADDR_INT ) );
            // clear address renew flag
            GAPM_F_SET( gapm_env.cfg_flags, ADDR_RENEW, 0 );
        }
        break;
        default: {
            // should never happen
            ASSERT_ERR( 0 );
        }
        break;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void gapm_set_adv_data_patch( uint8_t length,  uint8_t * data )
{
    struct gapm_start_advertise_cmd_patch * adv = ( struct gapm_start_advertise_cmd_patch * ) gapm_get_operation_ptr( GAPM_OP_AIR );
    struct hci_le_set_adv_data_cmd * adv_data = KE_MSG_ALLOC( HCI_COMMAND, 0, HCI_LE_SET_ADV_DATA_CMD_OPCODE, hci_le_set_adv_data_cmd );
    adv_data->adv_data_len = length;
    memcpy( &( adv_data->data.data[0] ), data, GAP_ADV_DATA_LEN );
    hci_send_2_controller( adv_data );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t gapm_adv_op_sanity_patch( void )
{
    uint8_t status = GAP_ERR_NO_ERROR;

    struct gapm_start_advertise_cmd_patch * adv =
        ( struct gapm_start_advertise_cmd_patch * ) gapm_get_operation_ptr( GAPM_OP_AIR );

    do {
        uint8_t supp_role = ( ( adv->op.code != GAPM_ADV_NON_CONN )
                              ? GAP_ROLE_PERIPHERAL : GAP_ROLE_BROADCASTER );

        if(
#if (BLE_PERIPHERAL)
            ( gapm_env.connections >= BLE_CONNECTION_MAX ) &&
#endif
            ( adv->op.code != GAPM_ADV_NON_CONN )
            && ( adv->info.host.mode != GAP_BROADCASTER_MODE ) ) {
            status = GAP_ERR_COMMAND_DISALLOWED;
            break;
        }

        if( !GAPM_IS_ROLE_SUPPORTED( supp_role ) ) {
            // role not supported
            status = GAP_ERR_NOT_SUPPORTED;
            break;
        }

        switch( adv->op.code ) {
#if (BLE_PERIPHERAL)
            case GAPM_ADV_UNDIRECT: {
                if( adv->info.host.mode >= GAP_BROADCASTER_MODE ) {
                    status = GAP_ERR_INVALID_PARAM;
                    break;
                }
            }
#endif 
            case GAPM_ADV_NON_CONN: {
                if( adv->info.host.mode > GAP_BROADCASTER_MODE ) {
                    status = GAP_ERR_INVALID_PARAM;
                    break;
                }

                if( adv->info.host.adv_filt_policy >= ADV_ALLOW_SCAN_END ) {
                    status = GAP_ERR_INVALID_PARAM;
                    break;
                }

                if( ( adv->info.host.adv_filt_policy  != ADV_ALLOW_SCAN_ANY_CON_ANY )
                    && ( ( adv->info.host.mode == GAP_GEN_DISCOVERABLE )
                         || ( adv->info.host.mode == GAP_LIM_DISCOVERABLE ) ) ) {
                    status = GAP_ERR_INVALID_PARAM;
                    break;
                }

#if (BLE_PERIPHERAL)
                if( !GAPM_IS_ROLE_SUPPORTED( GAP_ROLE_PERIPHERAL ) )
#endif
                {
                    if( ( adv->info.host.mode == GAP_GEN_DISCOVERABLE )
                        || ( adv->info.host.mode == GAP_LIM_DISCOVERABLE ) ) {
                        status = GAP_ERR_NOT_SUPPORTED;
                        break;
                    }
                }

                status = gapm_adv_sanity_patch( adv->info.host.adv_data,
                                                adv->info.host.adv_data_len,
                                                adv->info.host.scan_rsp_data,
                                                adv->info.host.scan_rsp_data_len,
                                                adv->op.code );
            }

#if (BLE_PERIPHERAL)
            case GAPM_ADV_DIRECT:
            case GAPM_ADV_DIRECT_LDC:
#endif
            {
                if( GAPM_F_GET( gapm_env.cfg_flags, ADDR_TYPE ) == GAPM_CFG_ADDR_HOST_PRIVACY ) {
                    if( ( ( adv->op.code != GAPM_ADV_NON_CONN ) && ( adv->op.addr_src == GAPM_GEN_NON_RSLV_ADDR ) )
                        ||  ( adv->op.addr_src == GAPM_STATIC_ADDR ) ) {
                        status = GAP_ERR_PRIVACY_CFG_PB;
                    }
                } else if( adv->op.addr_src != GAPM_STATIC_ADDR ) {
                    status = GAP_ERR_PRIVACY_CFG_PB;
                }
            }
            break;

            default: {
                status = GAP_ERR_INVALID_PARAM;
            }
            break;
        };
    } while( 0 );

    return ( status );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void gapm_execute_adv_op_patch( void )
{
    struct gapm_start_advertise_cmd_patch * adv =
        ( struct gapm_start_advertise_cmd_patch * ) gapm_get_operation_ptr( GAPM_OP_AIR );

    // clear message in kernel queue
    GAPM_CLEAR_OP_FIELD( adv->op, QUEUED );

    // execute current operation state.
    switch( GAPM_GET_OP_STATE( adv->op ) ) {
        // entry point of advertising operation execution.
        case GAPM_OP_SET_PARAMS: {
            // First, Advertising parameters shall be set in lower layers.
            struct hci_le_set_adv_param_cmd * adv_par = KE_MSG_ALLOC( HCI_COMMAND, 0, HCI_LE_SET_ADV_PARAM_CMD_OPCODE, hci_le_set_adv_param_cmd );

            // Get own address type
            uint8_t addr_type = gapm_get_local_addrtype();

            // set provided parameters
            adv_par->own_addr_type = addr_type;
            adv_par->adv_chnl_map  = adv->channel_map;
            adv_par->adv_intv_max  = adv->intv_max;
            adv_par->adv_intv_min  = adv->intv_min;

            switch( adv->op.code ) {
                case GAPM_ADV_NON_CONN: {
                    if( adv->info.host.scan_rsp_data_len == 0 ) {
                        // Advertising without scan response data (ADV_NON_CONN_IND)
                        adv_par->adv_type = ADV_NONCONN_UNDIR;
                    } else {
                        // Advertising with scan response (ADV_SCAN_IND)
                        adv_par->adv_type = ADV_DISC_UNDIR;
                    }
                    // set filter policy
                    adv_par->adv_filt_policy = adv->info.host.adv_filt_policy;
                    // Copy address
                    if( addr_type >= ADDR_RPA_OR_PUBLIC ) {
                        // set direct address to value
                        adv_par->peer_addr_type = adv->info.host.peer_addr.addr_type;
                        memcpy( &adv_par->peer_addr, &adv->info.host.peer_addr.addr, BD_ADDR_LEN );
                    } else {
                        // set direct address to default value
                        adv_par->peer_addr_type = ADDR_RAND;
                        memset( &adv_par->peer_addr, 0, BD_ADDR_LEN );
                    }
                }
                break;
                case GAPM_ADV_UNDIRECT: {
                    // Advertising connectable (ADV_IND)
                    adv_par->adv_type = ADV_CONN_UNDIR;
                    // set filter policy
                    adv_par->adv_filt_policy = adv->info.host.adv_filt_policy;
                    // Copy address
                    if( addr_type >= ADDR_RPA_OR_PUBLIC ) {
                        // set direct address to value
                        adv_par->peer_addr_type = adv->info.host.peer_addr.addr_type;
                        memcpy( &adv_par->peer_addr, &adv->info.host.peer_addr.addr, BD_ADDR_LEN );
                    } else {
                        // set direct address to default value
                        adv_par->peer_addr_type = ADDR_RAND;
                        memset( &adv_par->peer_addr, 0, BD_ADDR_LEN );
                    }
                }
                break;
                case GAPM_ADV_DIRECT:
                case GAPM_ADV_DIRECT_LDC: {
                    // Direct connectable advertising (ADV_DIRECT_IND)
                    adv_par->adv_type = ( ( adv->op.code == GAPM_ADV_DIRECT_LDC )
                                          ? ADV_CONN_DIR_LDC : ADV_CONN_DIR );

                    // Set advertising policy
                    adv_par->adv_filt_policy  = ADV_ALLOW_SCAN_ANY_CON_ANY;

                    // set initiator address
                    adv_par->peer_addr_type = adv->info.direct.addr_type;
                    memcpy( &adv_par->peer_addr, &adv->info.direct.addr, BD_ADDR_LEN );
                }
                break;
                default:
                    ASSERT_ERR( 0 );
                    break; // not allowed
            }

            /* send the message */
            hci_send_2_controller( adv_par );
        }
        break;
        case GAPM_OP_SET_ADV_DATA: {
            // Set advertising data
            gapm_set_adv_data_patch( adv->info.host.adv_data_len,  adv->info.host.adv_data );
        }
        break;
        case GAPM_OP_SET_SCAN_RSP_DATA: {
            struct hci_le_set_scan_rsp_data_cmd * scan_resp = KE_MSG_ALLOC( HCI_COMMAND, 0, HCI_LE_SET_SCAN_RSP_DATA_CMD_OPCODE, hci_le_set_scan_rsp_data_cmd );
            // retrieve scan response data length
            scan_resp->scan_rsp_data_len = adv->info.host.scan_rsp_data_len;
            // copy provided scan response data
            memcpy( &( scan_resp->data ), adv->info.host.scan_rsp_data, GAP_SCAN_RSP_DATA_LEN );

            hci_send_2_controller( scan_resp );
        }
        break;
        // address management
        case GAPM_OP_ADDR_GEN:
        case GAPM_OP_ADDR_SET: {
            // Use address management toolbox to set address
            gapm_set_address_op( &adv->op );
        }
        break;
        case GAPM_OP_START: { // Start advertising
            // start a timer in limited discoverable mode
            if( adv->info.host.mode == GAP_LIM_DISCOVERABLE ) {
                ke_timer_set( GAPM_LIM_DISC_TO_IND, TASK_GAPM, GAP_TMR_LIM_ADV_TIMEOUT );
            }

            // start advertising mode
            gapm_set_adv_mode( true );
        }
        break;

        case GAPM_OP_STOP: { // Stop
            gapm_set_adv_mode( false );
        }
        break;

        default: {
            // error state, trigger an error message.
            GAPM_SET_OP_STATE( adv->op, GAPM_OP_ERROR );
        }
        break;
    }

}

/**
 ****************************************************************************************
 * @brief Check if current operation can be processed or not.
 * if it can be proceed, initialize an operation request.
 * If a command complete event with error code can be triggered.
 *
 * Function returns how the message should be handled by message handler.
 *
 * @param[in] op_type       Operation type.
 * @param[in] op_msg        Requested operation message (note op_msg cannot be null)
 * @param[in] supp_ops      Supported operations array.
 *                          Latest array value shall be GAPM_NO_OP.
 *
 * @return operation can be executed if message status equals KE_MSG_NO_FREE,
 * else nothing to do, just exit from the handler.
 ****************************************************************************************
 */
static int gapm_process_op( uint8_t op_type, void * op_msg, enum gapm_operation * supp_ops )
{
    ASSERT_ERR( op_type < GAPM_OP_MAX );
    // Returned message status
    int msg_status = KE_MSG_CONSUMED; // Reset State
    // Current process state
    uint8_t state = ke_state_get( TASK_GAPM );
    uint8_t operation = *( ( uint8_t * )op_msg );

    /* no operation on going or requested operation is current on going operation. */
    if( state != GAPM_DEVICE_SETUP ) {
        if( gapm_get_operation_ptr( op_type ) != op_msg ) {
            uint8_t status = GAP_ERR_NO_ERROR;

            // check what to do with command if an operation is ongoing.
            if( ( state & ( 1 << op_type ) ) != GAPM_IDLE ) {
                // only one air operation accepted
                if( op_type == GAPM_OP_AIR ) {
                    // request disallowed
                    status = GAP_ERR_COMMAND_DISALLOWED;
                } else {
                    // operation are queued by default
                    // save it for later.
                    msg_status = KE_MSG_SAVED;
                }
            } else {
                // check if operation is suported
                while( *supp_ops != GAPM_NO_OP ) {
                    // operation supported by command
                    if( operation == *supp_ops ) {
                        break;
                    }
                    // check next operation
                    else {
                        supp_ops++;
                    }
                }

                // operation not supported
                if( *supp_ops == GAPM_NO_OP ) {
                    status = GAP_ERR_INVALID_PARAM;
                } else {
                    // message memory will be managed by GAPM
                    msg_status = KE_MSG_NO_FREE;

                    // store operation
                    gapm_set_operation_ptr( op_type, op_msg );
                    // set state to busy
                    gapm_update_state( op_type, true );
                }
            }

            // if an error detected, send command completed with error status
            if( status != GAP_ERR_NO_ERROR ) {
                gapm_send_error_evt( operation, ke_msg_src_id_get( op_msg ), status );
            }
        } else {
            // message memory managed by GAPM
            msg_status = KE_MSG_NO_FREE;
        }
    }

    return msg_status;
}
/**
 ****************************************************************************************
 * @brief Handles request of starting advertising command:
 *
 *  - GAPM_ADV_NON_CONN: Start non connectable advertising
 *  - GAPM_ADV_UNDIRECT: Start undirected connectable advertising
 *  - GAPM_ADV_DIRECT: Start directed connectable advertising
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance.
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 *
 ****************************************************************************************
 */
static int gapm_start_advertise_cmd_handler_patch( ke_msg_id_t const msgid, struct gapm_start_advertise_cmd_patch * param,
        ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    // list of handler supported operations
    enum gapm_operation supp_ops[] = { GAPM_ADV_NON_CONN, GAPM_ADV_UNDIRECT,
                                       GAPM_ADV_DIRECT, GAPM_ADV_DIRECT_LDC, GAPM_NO_OP
                                     };
    // use to know if it's first operation loop
    bool first_loop = ( gapm_get_operation_ptr( GAPM_OP_AIR ) == NULL );
    // check if operation can be executed
    int msg_status = gapm_process_op( GAPM_OP_AIR, param, supp_ops );

    // Operation can be handled
    if( msg_status == KE_MSG_NO_FREE ) {
        // execution status
        uint8_t status = GAP_ERR_NO_ERROR;

        /* if destination and source id are different it means that operation
         * execution starts
         */
        if( first_loop ) {
            // operation initial state
            param->op.state = 0;

            // perform a sanity check
            status = gapm_adv_op_sanity_patch();

            if( status == GAP_ERR_NO_ERROR ) {
                // initialize state machine
                gapm_update_air_op_state( GAPM_OP_AIR, GAPM_OP_INIT, GAP_ERR_NO_ERROR );
            } else {
                // stop operation execution
                gapm_send_complete_evt( GAPM_OP_AIR, status );
            }
        }

        if( status == GAP_ERR_NO_ERROR ) {
            // Execute the operation
            gapm_execute_adv_op_patch();
        }
    }

    return msg_status;
}
#endif /* (BLE_PERIPHERAL || BLE_BROADCASTER) */

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_adv_payload_31Byte_patch( void )
{
    uint8_t patch_no[1];
    if( patch_alloc( &patch_no[0] ) == false ) {
        BX_ASSERT( 0 );
    }
    patch_entrance_exit_addr( patch_no[0], SET_ADV_PAYLOAD_PATCH_ADDR, ( uint32_t )gapm_start_advertise_cmd_handler_patch );
    PATCH_ENABLE( patch_no[0] );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
