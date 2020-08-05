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

#include <string.h>
#include "arch.h"
#include "co_bt.h"
#include "co_endian.h"
#include "co_list.h"
#include "rwble_config.h"
#include "rwble.h"
#include "ke_event.h"
#include "ke_timer.h"
#include "ke_mem.h"
#include "ea.h"
#include "lld.h"
#include "lld_pdu.h"
#include "lld_evt.h"
#include "lld_util.h"
#include "reg_common_em_et.h"
#include "reg_ble_em_cs.h"
#include "reg_ble_em_rx_desc.h"
#include "reg_access.h"
#include "llm.h"
#include "rwip.h"
#include "llc.h"
#include "llc_util.h"
#include "llc_task.h"
#include "llm_util.h"

#if (NVDS_SUPPORT)
#include "nvds.h"
#endif

#if ((BLE_CENTRAL || BLE_PERIPHERAL) && (BLE_AUDIO))
#include "audio.h"
#endif

#include "dbg.h"

#include "patch.h"
#include "compiler_flag.h"

/* private define ------------------------------------------------------------*/
#define LLD_SLAVE_INSTANT_PATCH_ADDR                    0x16f6c
#define LLD_SLAVE_INSTANT_EVT_REMOVE_PATCH_ADDR         0x16fd8
#define LLD_SLAVE_INSTANT_EVT_REMOVE_PATCH_CODE         0xe03c

/* private typedef -----------------------------------------------------------*/
/// defer event type
enum lld_evt_defer_type {
    /// RX interrupt defer
    LLD_DEFER_RX                 = 0,
    /// End of event interrupt defer
    LLD_DEFER_END,
    /// Test End defer
    LLD_DEFER_TEST_END,
#if (BLE_CENTRAL || BLE_PERIPHERAL)
    /// Connection parameter update instant defer
    LLD_DEFER_CON_UP_INSTANT,
    /// Channel Map update instant defer
    LLD_DEFER_MAP_UP_INSTANT,
    /// Phys update instant defer
    LLD_DEFER_PHY_UP_INSTANT,
#endif // (BLE_CENTRAL || BLE_PERIPHERAL)

    LLD_DEFER_MAX
};

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
#define lld_evt_deferred_elt_push                       ( ( void( * ) ( struct ea_elt_tag * elt, uint8_t type, uint8_t rx_desc_cnt ) ) 0x15f75 )


void SLAVE_EVT_COUNT_JUST_BEFORE_INSTANT( void );

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void lld_evt_slave_instant_evt_patch( struct ea_elt_tag * elt )
{
    // Get BLE event environment
    struct lld_evt_tag * evt = LLD_EVT_ENV_ADDR_GET( elt );
    switch ( evt->evt.conn.instant_action ) {
        // A parameter update has to be performed
        case LLD_UTIL_PARAM_UPDATE: {
            // When the switch instant has passed, update the time of the last sync with the offset
            evt->evt.conn.update_offset = 0;

            lld_evt_deferred_elt_push( elt, LLD_DEFER_CON_UP_INSTANT, 0 );
        }
        break;

        // A channel map update has to be performed
        case LLD_UTIL_CHMAP_UPDATE: {
            lld_evt_deferred_elt_push( elt, LLD_DEFER_MAP_UP_INSTANT, 0 );
        }
        break;
#if(BLE_2MBPS)
        // A phys update has to be performed
        case LLD_UTIL_PHY_UPDATE: {
            lld_evt_deferred_elt_push( elt, LLD_DEFER_PHY_UP_INSTANT, 0 );
        }
        break;
#endif
        default: {
            // Nothing is done
        } break;
    }

    // Reset waiting instant flag
    LLD_EVT_FLAG_RESET( evt, WAITING_INSTANT );

    // Clear the action
    evt->evt.conn.instant_action = LLD_UTIL_NO_ACTION;
    // Clear the instant
    evt->evt.conn.instant = 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint32_t slave_event_count_just_before_instant_c( bool rx_sync_win_update, struct ea_elt_tag * elt )
{
    lld_evt_slave_instant_evt_patch( elt );
    if( rx_sync_win_update ) {
        return 0x16f71;
    } else {
        return 0x17055;
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_lld_slave_instant_patch()
{
    uint32_t code = cal_patch_bl( LLD_SLAVE_INSTANT_PATCH_ADDR, ( uint32_t )SLAVE_EVT_COUNT_JUST_BEFORE_INSTANT - 1 );
    uint8_t patch_no[2];
    if( patch_alloc( &patch_no[0] ) == false ) {
        BX_ASSERT( 0 );
    }
    patch_entrance_exit_addr( patch_no[0], LLD_SLAVE_INSTANT_PATCH_ADDR, code );
    PATCH_ENABLE( patch_no[0] );
    if( patch_alloc( &patch_no[1] ) == false ) {
        BX_ASSERT( 0 );
    }
    patch_entrance_exit_addr( patch_no[1], LLD_SLAVE_INSTANT_EVT_REMOVE_PATCH_ADDR, LLD_SLAVE_INSTANT_EVT_REMOVE_PATCH_CODE );
    PATCH_ENABLE( patch_no[1] );
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

