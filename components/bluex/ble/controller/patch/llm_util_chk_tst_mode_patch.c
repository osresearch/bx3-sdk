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
#include "compiler.h"
#include "co_endian.h"
#include "co_error.h"
#include "ke_mem.h"
#include "reg_ble_em_rx_desc.h"
#include "reg_ble_em_tx_desc.h"
#include "reg_ble_em_cs.h"
#include "reg_blecore.h"
#include "llm.h"
#include "lld.h"

#if (HCI_PRESENT)
#include "hci.h"
#endif

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void llm_util_chk_tst_mode_patch( void )
{
    //if the current state is not IDLE
    if( ( llm_le_env.test_mode.directtesttype != TEST_END ) && ( llm_le_env.test_mode.end_of_tst == true ) ) {
        // structure type for the complete command event
        struct hci_test_end_cmd_cmp_evt * event;

        // allocate the complete event message
        event = KE_MSG_ALLOC( HCI_CMD_CMP_EVENT, 0, HCI_LE_TEST_END_CMD_OPCODE, hci_test_end_cmd_cmp_evt );

        llm_le_env.test_mode.end_of_tst = false;
        // enable the whitening
        ble_whit_dsb_setf( 0 );

        // Number_Of_Packets for a transmitter test is reported as NULL.
        if ( llm_le_env.test_mode.directtesttype == TEST_TX ) {
            event->nb_packet_received = ble_rftesttxstat_get();
        } else {
            event->nb_packet_received = ble_rxccmpktcnt0_get( LLD_ADV_HDL );
        }
        // set the env variable,
        llm_le_env.test_mode.directtesttype = TEST_END;
        // update the status
        event->status = CO_ERROR_NO_ERROR;
        // send the message
        hci_send_2_host( event );
        ke_msg_send_basic( LLM_STOP_IND, TASK_LLM, TASK_LLM );
    }
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
