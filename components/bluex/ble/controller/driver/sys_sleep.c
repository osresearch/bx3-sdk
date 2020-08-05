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
#include "apollo_00_ble_reg.h"
#include "plf.h"
#include "sys_sleep.h"
#include "clk_gate.h"
#include "awo_apollo_00.h"
#include "pshare.h"
#include "rwip.h"
#include "log.h"
#include "reg_blecore.h"
#include "reg_sysc_awo.h"
#include "modem.h"
#include "reg_gpio.h"
#include "patch.h"
#include "sysctrl.h"
#include "rf_reg_settings.h"
#include "swint.h"
#include "rf.h"
#include "periph_recovery.h"
#include "ke_event.h"
#include "ke.h"
#include "rc_calib.h"
#include "compiler_flag.h"

#include "bx_shell.h"
#include "bx_pm.h"
#include "rf_temp_adjust.h"


/* private define ------------------------------------------------------------*/
#define SECONDS_TO_RTC( a )                             ( 30 * 1000 * ( a ) )

/* private typedef -----------------------------------------------------------*/

#if (defined(CFG_DYNAMIC_UPDATE)&&(CFG_DYNAMIC_UPDATE==1))
struct dynamic_update_handler {
    uint8_t index;
    dynamic_update_cb cb;
};
#endif

/* private variables ---------------------------------------------------------*/
blemac_stat_t mac_status = active_clk;
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
N_XIP_SECTION void ble_lp_intr_clr()
{
#if HW_BX_VERSION == 00
    hwp_sysc_awo->blelp_inrp_clr.val = 0x3;
#else
#error ERROR: ERROR to define HW_BX_VERSION
#endif
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void ble_lp_irq_enable()
{
#if HW_BX_VERSION == 00
    hwp_sysc_awo->reg_misc_1.bit_field.blelp_inrp_en = 0x3;
#else
#error ERROR: ERROR to define HW_BX_VERSION
#endif
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void ble_lp_irq_disable()
{
#if HW_BX_VERSION == 00
    hwp_sysc_awo->reg_misc_1.bit_field.blelp_inrp_en = 0;
#else
#error ERROR: ERROR to define HW_BX_VERSION
#endif
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__attribute__( ( weak ) ) bool deep_sleep_check()
{
    return true;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint8_t sleep_prepare_and_check()
{
#if(RC32K_USED == 1)
    rc_test_end();
#endif
    uint8_t sleep_type = 0;
    if( mac_status == active_clk ) {
        sleep_type = rwip_sleep();
        if( sleep_type & BLE_DEEP_SLEEP ) {
            mac_status = sleep_low_power_clk;
			try_to_update_rf_param_with_temp();
        }
    } else if( mac_status == sleep_low_power_clk ) {
        sleep_type = ke_sleep_check() ? PROCESSOR_SLEEP | BLE_DEEP_SLEEP : 0 ;
    } else {
        sleep_type = PROCESSOR_SLEEP;
    }
    bool busy = periph_domain_busy() || cpu_domain_busy() || !deep_sleep_check();
    if( busy ) {
        sleep_type &= ~SYS_DEEP_SLEEP;
    } else {
        sleep_type |= SYS_DEEP_SLEEP;
    }
    return sleep_type;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void sleep_check(void)
{
    if( bx_pm_check( BX_PM_ALL ) ) {
        bxsh_logln("not sleep");
        return ;
    }
    uint8_t sleep_type;
    GLOBAL_INT_DISABLE();
    sleep_type = sleep_prepare_and_check();
    if( sleep_type == ( SYS_DEEP_SLEEP | BLE_DEEP_SLEEP | PROCESSOR_SLEEP ) ) {
        pre_deepsleep_processing_mp();
        WFI();
        post_deepsleep_processing_mp();
    } else if( sleep_type & PROCESSOR_SLEEP ) {
        WFI();
    }
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void ble_soft_wakeup()
{
    LOG( LOG_LVL_INFO, "soft wakeup\n" );
    ble_clk_gate_awo( BLE_AWO_CLKG_SET_BLE );
    ble_soft_wakeup_req_setf( 1 );
    while( mac_status != active_clk ) {
        __WFI();
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint32_t enable_32m_rc()
{
    sysc_awo_dr_16m_rcosc_en_setf( 1 );
    sysc_awo_reg_16m_rcosc_en_setf( 1 );
    return get_real_rtc();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void system_recovery()
{
    SWINT_SYS_INT_EN();
    patch_init();
    periph_recovery( periph_domain_recovery_buf, PERIPH_DOMAIN_MAX );
    periph_recovery( cpu_domain_recovery_buf, CPU_DOMAIN_MAX );
#if (defined(CFG_DYNAMIC_UPDATE)&&(CFG_DYNAMIC_UPDATE==1))
//    sys_param_periodic_update();
#endif
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void switch_to_32m_xtal( uint32_t current_time )
{
    wait_rtc_until( current_time + XTAL_STARTUP_TIME );
    reg_set_xtal_current_normal();
    wait_rtc_until( current_time + XTAL_STARTUP_TIME + 1 );
    sysc_awo_o_ana_16m_selrc_setf( 0 );
}

#ifdef CFG_LOWEST_CURRENT
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION static void first_deep_sleep( void )
{
    SCB->SCR |= ( 1 << 2 );
    awo_pd_onoff_sw( PD_PER | PD_BLE_MAC, PD_POWER_DOWN );
    awo_pd_onoff_sw( PD_PER | PD_BLE_RF | PD_BLE_MAC | PD_SRAM0 | PD_SRAM1 | PD_SRAM2 | PD_SRAM3 | PD_SRAM4 | PD_SRAM5 | PD_SRAM6, PD_POWER_ON );

    app_rtc_init_wrapper();
    rtc_SetConfig( 320, 0 ); // sleep 10ms
    rtc_Run( NULL );

    uint32_t i;

    for( i = 0; i < 1000; i++ ) {                    //
        __NOP();
    }

    __asm( "cpsid i" );

    __asm( "wfi" );

    SCB->SCR &= ~( 1 << 2 );
    rtc_DisableIrq();
    rtc_ClearIrq();
    awo_reset_signal( SRST_RTC_CLR );
    awo_reset_signal( SRST_RTC_SET ); // reset RTC
    rtc_rtc_cmr_set( 1 );
    WAIT_RTC_RST( 1 ); // wait RTC reset completed
    rtc_rtc_cmr_set( 0 ); // restore matchcounter with 0
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void set_vdd_in_systeminit( void )
{
    extern void intc_init( void );
    intc_init();
    GLOBAL_INT_START();
    awo_vdd_value_set( 0 );
    first_deep_sleep();
    GLOBAL_INT_STOP();
}
#endif

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void BLE_LP_IRQHandler( void )
{
    ble_clk_gate_awo( BLE_AWO_CLKG_SET_BLE );
    modem_init();
    ble_lp_irq_disable();
    mac_status = wakeup_requested;
    NVIC_EnableIRQ( BLE_MAC_IRQn );
    BX_ASSERT( NVIC_GetPendingIRQ( BLE_MAC_IRQn ) == 0 );
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

