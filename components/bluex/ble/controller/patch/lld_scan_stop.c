/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author :
  * @brief  :
//If stop_scan_cmd send at scan channel_chaned_time window,(abort 1.7ms window)
//This command will delay a long time. We will receive the gapm_cmp_evt until a scan window time delay passed .
//this patch to avoid this issue in mesh low_power / mesh friend case.
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
#include "rwip_config.h"
#include "rwip.h"
#include "patch.h"
#include "h4tl_custom.h"
#include "log.h"
#include "h4tl.h"
#include "io_ctrl.h"
#include <stdbool.h>
#include "co_utils.h"
#include "co_endian.h"
#include "ke_event.h"
#include "ea.h"
#include "llm.h"
#include "llm_util.h"
#include "llc_llcp.h"
#include "llc.h"
#include "lld.h"
#include "lld_evt.h"
#include "lld_pdu.h"
#include "lld_util.h"
#include "reg_blecore.h"
#include "reg_ble_em_wpb.h"
#include "reg_ble_em_wpv.h"
#include "reg_ble_em_ral.h"
#include "reg_ble_em_cs.h"
#include "reg_common_em_et.h"
#include "rwip.h"
#include "rwble.h"

/* private define ------------------------------------------------------------*/
#define LLD_SCAN_STOP_ADDR      0x00018b54

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

void LLD_SCAN_STOP_PATCH( void );

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_scan_stop_ble_reg( void )
{
    *( volatile uint32_t * )BLE_DIAGCNTL_ADDR |= 0x8300;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool get_rx_en_reg( void )
{
    set_scan_stop_ble_reg();
    uint32_t tmp = *( volatile uint32_t * )BLE_DIAGSTAT_ADDR;
    tmp = tmp & 0x00000200;
    return tmp ? true : false;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void wait_until_rx_en_high( void )
{
    if( get_rx_en_reg() == 0 ) {
        //io_pin_set(11);
        while( get_rx_en_reg() == 0 );
        //io_pin_clear(11);
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void lld_scan_stop_patch( struct ea_elt_tag * elt )
{
    //Check if the elt will be programmed soon or already programmed
    if( !lld_evt_elt_delete( elt, true, true ) ) {
        // Get the associated BLE specific event environment
        struct lld_evt_tag * evt = LLD_EVT_ENV_ADDR_GET( elt );

        LLD_EVT_FLAG_SET( evt, WAITING_EOEVT_TO_DELETE );

        uint32_t current = lld_evt_time_get();
        if( CLK_DIFF( current, elt->timestamp ) >= 0 ) {
            wait_until_rx_en_high();
        }

        // Abort the event
        ble_rwblecntl_set( ble_rwblecntl_get() | BLE_SCAN_ABORT_BIT );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_lld_scan_stop_patch( void )
{
    uint8_t patch_no;
    if( patch_alloc( &patch_no ) == false ) {
        BX_ASSERT( 0 );
    }
    uint32_t code = cal_patch_bl( LLD_SCAN_STOP_ADDR, ( uint32_t )LLD_SCAN_STOP_PATCH - 1 );
    patch_entrance_exit_addr( patch_no, LLD_SCAN_STOP_ADDR, code );
    PATCH_ENABLE( patch_no );
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
