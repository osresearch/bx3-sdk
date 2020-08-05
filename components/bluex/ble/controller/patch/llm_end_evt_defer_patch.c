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
#include "bx_config.h"
#include "patch.h"
#include "bx_dbg.h"
#include "co_bt.h"
#include "co_error.h"
#include "co_list.h"
#include "em_buf.h"
#include "co_utils.h"
#include "co_math.h"
#include "co_endian.h"
#include "ke_msg.h"
#include "ke_timer.h"
#include "ke_event.h"
#include "llm.h"
#include "llm_task.h"
#include "llm_util.h"
#include "co_version.h"
#include "llc.h"
#include "llc_task.h"
#include "llc_util.h"
#include "lld.h"
#include "lld_util.h"
#include "lld_pdu.h"
#include "lld_evt.h"
#include "rwip.h"
#include "dbg.h"
#include "gapm_int.h"
#include "gapm_util.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

void llm_util_chk_tst_mode_patch( void );
void llm_util_chk_tst_mode( void );

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void mesh_sched_adv_stop_patch()
{
    ke_state_t current_state = ke_state_get( TASK_LLM );
    if( current_state == LLM_ADVERTISING && ( llm_le_env.advertising_params->type == LL_ADV_NONCONN_UNDIR || llm_le_env.advertising_params->type == LL_ADV_CONN_UNDIR ) ) {
        struct gapm_start_advertise_cmd * adv = ( struct gapm_start_advertise_cmd * ) gapm_get_operation_ptr( GAPM_OP_AIR );
        GAPM_SET_OP_FIELD( adv->op, CANCELED );
        GAPM_SET_OP_STATE( adv->op, GAPM_OP_STOP );
        llm_le_env.state = LLM_ADVERTISING;
        ke_state_set( TASK_LLM, LLM_STOPPING );
        lld_evt_delete_elt_push( llm_le_env.elt, true, true );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void llm_end_evt_defer_patch()
{
#if(TX_TEST_PACKET_NUM_PATCH == 1)
    llm_util_chk_tst_mode_patch();
#else
    llm_util_chk_tst_mode();
#endif
#if(MESH_SCHED_PATCH == 1)
    mesh_sched_adv_stop_patch();
#endif
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_llm_end_evt_defer_patch()
{
    half_word_aligned_bl_patch( 0x19be6, llm_end_evt_defer_patch );
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
