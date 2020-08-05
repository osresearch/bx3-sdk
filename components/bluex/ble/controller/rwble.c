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
#include <stdint.h>
#include "co_version.h"
#include "reg_blecore.h"
#include "apollo_00_ble_reg.h"
#include "rwble.h"
#include "compiler_flag.h"
#include "reg_blecore.h"
#include "rf.h"

#if (defined(CFG_FREERTOS_SUPPORT)&&(CFG_FREERTOS_SUPPORT==1))
#include "ble_task.h"
#endif


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
void rwble_version(uint8_t* fw_version, uint8_t* hw_version)
{
    // FW version
    *(fw_version+3) = RWBT_SW_VERSION_MAJOR;
    *(fw_version+2) = RWBT_SW_VERSION_MINOR;
    *(fw_version+1) = RWBT_SW_VERSION_BUILD;
    *(fw_version)   = RWBT_SW_VERSION_SUB_BUILD;

    // HW version 
    *(hw_version+3) = ble_typ_getf();
    *(hw_version+2) = ble_rel_getf();
    *(hw_version+1) = ble_upg_getf();
    *(hw_version)   = ble_build_getf();
}


/*========================= end of exported function =========================*/


/*============================= import function ==============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint32_t ble_intstat_get(void);
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void ble_rxpwrup0_setf(uint8_t rxpwrup0);

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void BLE_MAC_IRQHandler(void)
{
    uint32_t irq_stat = ble_intstat_get();
    rwble_isr();
    // End of event interrupt
    if (irq_stat & BLE_EVENTINTSTAT_BIT)
    {
        ble_rxpwrup0_setf(RX_PWRUP0_DEFAULT_VALUE);
    }
    // AFPM interrupt
    if (irq_stat & BLE_EVENTAPFAINTSTAT_BIT)
    {
        ble_rxpwrup0_setf(RX_PWRUP0_DEFAULT_VALUE);
    }
    NVIC_ClearPendingIRQ(BLE_MAC_IRQn);
    #if (defined(CFG_FREERTOS_SUPPORT)&&(CFG_FREERTOS_SUPPORT==1))
    msg2blestack_from_ISR();
    #endif
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


