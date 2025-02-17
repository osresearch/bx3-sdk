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
#include "bx_sdk3_config.h"

/* includes ------------------------------------------------------------------*/

#include "apollo_00_ble_reg.h"
#include "arch_init.h"
#include "compiler_flag.h"
#include "sys_sleep.h"
#include "ke_event.h"
#include "rtc.h"
#include "ll.h"
#include "app_adc_utils.h"
#include "rf_temp_adjust.h"
#include "bx_dbg.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_init()
{
    soc_init();
    
    log_init();
    
    RTC_EN_WITHOUT_INT();
    rwip_init( 0 );
    GLOBAL_INT_START();
    
#if (DEFAULT_HCI  == 1)
    gapm_set_embedded_host( false );
#endif 
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void ble_schedule()
{
#if ( BX_USE_WDT > 0 )
    BX_MODIFY_REG( BX_WDT->CR, WDT_CR_VAL, 0X76 );
#endif
    if( mac_status == sleep_low_power_clk && ke_event_get_all() ) {
        ble_soft_wakeup();
    }
    if( mac_status == active_clk ) {
        rwip_schedule();
    }
    #if ( BX_DEEP_SLEEP > 0 )
    sleep_check();
    #endif
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



