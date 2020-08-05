/**
 ****************************************************************************************
 *
 * @file lld_sleep.c
 *
 * @brief Definition of the functions to manage RWBLE core sleep mode
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup LLDSLEEP
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#define __RAM_CODE__
#include "rwip_config.h" // stack configuration

#if (DEEP_SLEEP)
#include "lld_sleep.h"
#include "lld_evt.h"

#if (NVDS_SUPPORT)
#include "nvds.h"         // NVDS definitions
#endif // NVDS_SUPPORT
#include "awo_apollo_00.h"
#include "compiler_flag.h"
/*
 * STRUCTURE DEFINITIONS
 ****************************************************************************************
 */

#if (!BT_DUAL_MODE)
/// Environment structure for the LLD SLEEP module
struct lld_sleep_env_tag
{
    uint32_t irq_mask;
    uint16_t twext;
    uint16_t twosc;
    uint16_t twrm;
};
#endif //!BT_DUAL_MODE

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

#if (!BT_DUAL_MODE)
/// Environment of the LLD SLEEP module
static struct lld_sleep_env_tag lld_sleep_env;
#endif //!BT_DUAL_MODE



/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

#if (!BT_DUAL_MODE)


/**
 ****************************************************************************************
 * @brief Apply the correction to the base time counter and fine counter after deep-sleep,
 * according to the duration of the deep sleep.
 * The function first converts the number of low power clock cycles spent in deep sleep to
 * a time in us. Sleep clock runs at either 32768Hz or 32000Hz, so the function multiplies
 * the sleep duration by 30.517578125 or 31.25 depending on the case.
 * To do this we apply the following formulae:
 *
 *   Tsleep = x*30.517578125 = 30*x + x/2 + x/64 + x/512 for a 32.768kHz clock or
 *   Tsleep = x*31.25        = 31*x + x/4                for a 32kHz clock
 *
 * These formulae give an exact value.
 *
 * The function then converts the result into 2 parts:
 *   BTCORR = int(Tsleep / 625) to get the correction value for the base time counter
 *   FTCORR = 625 - (Tsleep mod 625) to get the correction value for the fine counter
 *
 * The computed values are then applied in the correction registers
 *
 ****************************************************************************************
 */
N_XIP_SECTION static void lld_sleep_compensate(void)
{
    uint32_t dur_us;
    uint32_t dur_slot;
    uint16_t fintetime_correction;
    // Get the number of low power sleep period
    uint32_t slp_period = ble_deepslstat_get();

    // Sanity check: The duration of a sleep is limited
    ASSERT_ERR(slp_period < LLD_EVT_MAX_SLEEP_DURATION);

    // Convert sleep duration into us. add also the sleep compensation due to HW issue when fine count duration equals zero
    dur_us   = rwip_sleep_lpcycles_2_us(slp_period) + lld_evt_env.hw_wa_sleep_compensation;
    dur_slot = dur_us / SLOT_SIZE;

    // If the sleep duration is a multiple of slot then fine timer correction is set to 0 else is set to the difference
    fintetime_correction = 624 - (dur_us - dur_slot*SLOT_SIZE);

    // fix in case of fine correction equals zero, we have an HW misalignment of 1 half slot
    if(fintetime_correction == 0)
    {
        fintetime_correction = 624;
        dur_slot += 1;
        // one us is not executed, keep this information to compensate it in a next wake-up
        lld_evt_env.hw_wa_sleep_compensation = 1;
    }
    else
    {
        // no need to compensate
        lld_evt_env.hw_wa_sleep_compensation = 0;
    }

    // The correction values are then deduced from the sleep duration in us
    ble_basetimecntcorr_set(dur_slot);
    ble_finecntcorr_set(fintetime_correction);
    
    #if HW_BX_VERSION == 00
    sysc_awo_awo_reset_signal_set(SRST_BLE_LP_CLR);
    #endif
    // Start the correction
    ble_deep_sleep_corr_en_setf(1);
}
#endif // !BT_DUAL_MODE

/*
 * EXPORTED FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

#if (!BT_DUAL_MODE)


void bx_lld_wakeup_time_set()
{
    // Program register
    ble_enbpreset_pack((uint16_t)rwip_us_2_lpcycles(lld_sleep_env.twext),
                      (uint16_t) rwip_us_2_lpcycles(lld_sleep_env.twosc),
                      (uint16_t) rwip_us_2_lpcycles(lld_sleep_env.twrm) );

    uint16_t twmax;
    // Configure wake up delay to the highest parameter
    twmax = co_max(lld_sleep_env.twext,lld_sleep_env.twrm);
    twmax = co_max(twmax,lld_sleep_env.twosc);
    rwip_wakeup_delay_set((uint16_t)twmax);

}

void lld_sleep_init(void)
{
    // Clear the environment
    memset(&lld_sleep_env, 0, sizeof(lld_sleep_env));

    #if (NVDS_SUPPORT)
    // Get TWrm from NVDS
    uint8_t length = sizeof(uint16_t);
    if (nvds_get(NVDS_TAG_RM_WAKEUP_TIME, &length, (uint8_t*)&lld_sleep_env.twrm) != NVDS_OK)
    #endif // NVDS_SUPPORT
    {
        // Set default values : 625 us
        lld_sleep_env.twrm = SLOT_SIZE;
    }

    #if (NVDS_SUPPORT)
    // Get TWosc from NVDS
    length = sizeof(uint16_t);
    if (nvds_get(NVDS_TAG_OSC_WAKEUP_TIME, &length, (uint8_t*)&lld_sleep_env.twosc) != NVDS_OK)
    #endif // NVDS_SUPPORT
    {
        // Set default values : 5 ms
        lld_sleep_env.twosc = 5000;
    }

    #if (NVDS_SUPPORT)
    // Get TWext from NVDS
    length = sizeof(uint16_t);
    if (nvds_get(NVDS_TAG_EXT_WAKEUP_TIME, &length, (uint8_t*)&lld_sleep_env.twext) != NVDS_OK)
    #endif // NVDS_SUPPORT
    {
        // Set default values : 5 ms
        lld_sleep_env.twext = 5000;
    }

    bx_lld_wakeup_time_set();

    // Enable external wake-up by default
    ble_extwkupdsb_setf(0);
}

void lld_sleep_enter(uint32_t sleep_duration, bool ext_wakeup)
{

    // Save IRQ mask
    lld_sleep_env.irq_mask = ble_intcntl_get();

    // Program wake-up time
    ble_deepslwkup_set(sleep_duration);

    // Clear possible pending IRQs
    ble_intack_clear(BLE_EVENTINTACK_BIT | BLE_RXINTACK_BIT | BLE_SLPINTACK_BIT | BLE_EVENTAPFAINTMSK_BIT);

    // Mask all interrupts except sleep IRQ
    ble_intcntl_set(BLE_SLPINTMSK_BIT);

    // Disable Fine timer irq
    if (ble_finetgtimintmsk_getf())
    {
        /*
         * If timer is enabled, it is possible that the irq is raised
         * due to a spurious value, so ack it before
         */
        ble_intack_clear(BLE_FINETGTIMINTACK_BIT);
        ble_finetgtimintmsk_setf(0);
    }

    if(!ext_wakeup)
    {
        ble_extwkupdsb_setf(1);
    }
}

N_XIP_SECTION void lld_sleep_wakeup(void)
{
    // Re-enable external wake-up by default
    ble_extwkupdsb_setf(0);

    // Compensate the base time counter and fine time counter
    lld_sleep_compensate();
    
    // Clear slot interrupt
    ble_intack_clear(BLE_CSCNTINTACK_BIT);

    // Enable slot interrupt only
    ble_intcntl_set(BLE_CSCNTINTMSK_BIT);
}

N_XIP_SECTION void lld_sleep_wakeup_end(void)
{
    // Re-enable interrupts
    ble_intcntl_set(lld_sleep_env.irq_mask);
}

#endif //!BT_DUAL_MODE
#endif // DEEP_SLEEP

/// @} LLD

