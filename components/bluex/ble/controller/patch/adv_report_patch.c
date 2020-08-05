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
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "patch.h"
#include "bx_dbg.h"

#if (MESH_SCHED_PATCH == 1)
#include "hci.h"
#include "reg_ble_em_cs.h"
#include "rtc.h"
#include "mesh_ble_time.h"
#endif 

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

#if (MESH_SCHED_PATCH == 1)
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void adv_rx_time_get_patch_c( void * event, uint8_t rx_hdl )
{
    hci_send_2_host( event );
    uint32_t rtc_time = RTC_CURRENTCNT_GET();

    adv_rx_time_enqueue( rtc_time );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void LLM_ADV_REPORT_SEND_ADV_RX_TIME_GET( void );
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_llm_adv_report_send_patch( void )
{
    half_word_aligned_bl_patch( 0x1944e, LLM_ADV_REPORT_SEND_ADV_RX_TIME_GET );
}

#else
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void adv_rx_time_get_patch_c( void * event, uint8_t rx_hdl )
{

}
#endif

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
