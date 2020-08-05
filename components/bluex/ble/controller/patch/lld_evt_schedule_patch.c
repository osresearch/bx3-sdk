/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author :
  * @brief  :   If in the scan only mode , the rx_en and sync_found_pulse will Intermittent sometimes,cause loss packet.
  *             This patch fix the scan mode loss packet.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "patch.h"
#include "log.h"
#include "ea.h"
#include "llm.h"
#include "lld.h"
#include "lld_pdu.h"
#include "lld_evt.h"
#include "reg_blecore.h"
#include "compiler_flag.h"

/* private define ------------------------------------------------------------*/
#define LLD_EVT_ELT_WAIT_GET                            ( ( lld_evt_elt_wait_get_fp ) ( 0x000162e8 + 1 ) )
#define LLD_EVT_SCHEDULE_SCAN_PATCH_ADDR                0x00017200
#define RX_PWRUP0_SCAN_PATCH_VALUE                      0x02

/* private typedef -----------------------------------------------------------*/
typedef struct lld_evt_wait_tag * ( *lld_evt_elt_wait_get_fp )( struct ea_elt_tag * elt );

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
extern struct llm_le_env_tag llm_le_env;

/* private macros ------------------------------------------------------------*/

N_XIP_SECTION void ble_rxpwrup0_setf( uint8_t rxpwrup0 );

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION struct lld_evt_wait_tag * lld_evt_schedule_scan_patch( struct ea_elt_tag * elt )
{
    // Get associated BLE event environment
    struct lld_evt_tag * evt = LLD_EVT_ENV_ADDR_GET( elt );
    if ( evt->mode == LLD_EVT_SCAN_MODE ) {
        if ( LLD_EVT_FLAG_GET( evt, WAITING_EOEVT_TO_DELETE ) ) {
            ;
        } else {
            if( ke_state_get( TASK_LLM ) == LLM_SCANNING && llm_le_env.scanning_params->type == SCAN_PASSIVE ) {
                ble_rxpwrup0_setf( RX_PWRUP0_SCAN_PATCH_VALUE );
            }
        }
    }
    return LLD_EVT_ELT_WAIT_GET( elt );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_lld_evt_schedule_scan_patch( void )
{
    uint8_t patch_no;
    if( patch_alloc( &patch_no ) == false ) {
        BX_ASSERT( 0 );
    }
    uint32_t code = cal_patch_bl( LLD_EVT_SCHEDULE_SCAN_PATCH_ADDR, ( uint32_t )lld_evt_schedule_scan_patch - 1 );
    patch_entrance_exit_addr( patch_no, LLD_EVT_SCHEDULE_SCAN_PATCH_ADDR, code );
    PATCH_ENABLE( patch_no );

}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

