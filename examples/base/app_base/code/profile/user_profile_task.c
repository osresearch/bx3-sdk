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

/* includes ------------------------------------------------------------------*/


#include "rwip_config.h"

#include "gap.h"
#include "gattc_task.h"
#include "user_profile.h"
#include "user_profile_task.h"
#include "prf_utils.h"

#include "ke_mem.h"
#include "co_utils.h"

#include "bx_dbg.h"
#include "bx_kernel.h"

/* private define ------------------------------------------------------------*/
/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
/* exported variables --------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int user_profile_write_req_ind_handler( ke_msg_id_t const msgid,
                                        struct gattc_write_req_ind * param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id )
{
    bx_logln("user_profile_write_req_ind_handler");
    uint8_t state  = ke_state_get( dest_id );
    if( state == USER_PROFILE_IDLE ) {
        uint8_t status = GAP_ERR_NO_ERROR;
        struct gattc_write_cfm * cfm;

        cfm = KE_MSG_ALLOC( GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm );
        cfm->handle = param->handle;
        cfm->status = status;
        for( u32 i=0;i<param->length;i++ ){
            bx_log("%02X ",param->value[i]);
        }
        bx_logln("");
        ke_msg_send( cfm );

    }
    return ( KE_MSG_CONSUMED );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int user_profile_read_req_ind_handler( ke_msg_id_t const msgid,
                                       struct gattc_read_req_ind const * param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id )
{
    bx_logln("user_profile_read_req_ind_handler");
    ke_state_t state = ke_state_get( dest_id );

    if( state == USER_PROFILE_IDLE ) {
        static u16 test_count = 0;
        struct gattc_read_cfm * cfm = KE_MSG_ALLOC_DYN( GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm, 2 );
        cfm->handle = param->handle;
        cfm->status = ATT_ERR_NO_ERROR;
        cfm->length = 2;
        cfm->value[0] = test_count>>8;
        cfm->value[1] = test_count;
        test_count++;
        ke_msg_send( cfm );
    }

    return ( KE_MSG_CONSUMED );
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int user_profile_cmp_evt_handler( ke_msg_id_t const msgid, struct gattc_cmp_evt const * param,
                                  ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    bx_logln( "user_profile_cmp_evt_handler" );

    return ( KE_MSG_CONSUMED );
}

/*============================= exported function ============================*/

/*========================= end of exported function =========================*/
const struct ke_msg_handler user_profile_state[] = {
    {GATTC_WRITE_REQ_IND,                 ( ke_msg_func_t ) user_profile_write_req_ind_handler},
    {GATTC_READ_REQ_IND,                  ( ke_msg_func_t ) user_profile_read_req_ind_handler},
    {GATTC_CMP_EVT,                       ( ke_msg_func_t ) user_profile_cmp_evt_handler},
};

/// Specifies the message handlers that are common to all states.
const struct ke_state_handler user_profile_handler = KE_STATE_HANDLER( user_profile_state );


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
