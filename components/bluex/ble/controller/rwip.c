/**
****************************************************************************************
*
* @file rwip.c
*
* @brief RW IP SW main module
*
* Copyright (C) RivieraWaves 2009-2015
*
*
****************************************************************************************
*/

/**
 ****************************************************************************************
 * @addtogroup RW IP SW main module
 * @ingroup ROOT
 * @brief The RW IP SW main module.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#define __RAM_CODE__
#include "rwip_config.h"     // RW SW configuration
#include <string.h>          // for mem* functions
#include "rwip.h"            // RW definitions
#include "arch.h"            // Platform architecture definition
#include "plf.h"

#if (NVDS_SUPPORT)
#include "nvds.h"         // NVDS definitions
#endif // NVDS_SUPPORT

#if (BT_EMB_PRESENT)
#include "rwbt.h"            // rwbt definitions
#endif //BT_EMB_PRESENT

#if (BLE_EMB_PRESENT)
#include "rwble.h"           // rwble definitions
#endif //BLE_EMB_PRESENT

#if (BLE_HOST_PRESENT)
#include "rwble_hl.h"        // BLE HL definitions
#include "gapc.h"
#include "gattc.h"
#include "l2cc.h"
#endif //BLE_HOST_PRESENT

#if (BLE_APP_PRESENT)
//#include "app.h"             // Application definitions
#include "user_ble.h"             // Application definitions
#endif //BLE_APP_PRESENT

#if (DEEP_SLEEP)
#if (BLE_EMB_PRESENT)
#include "lld_sleep.h"       // definitions for sleep mode
#endif //BLE_EMB_PRESENT
#endif //DEEP_SLEEP

#if (BLE_EMB_PRESENT)
#include "llc.h"
#endif //BLE_EMB_PRESENT

#if (BLE_EMB_PRESENT)
#include "lld_wlcoex.h"
#endif //BLE_EMB_PRESENT
#if (BT_EMB_PRESENT)
#include "ld.h"
#endif //BT_EMB_PRESENT

#if (DISPLAY_SUPPORT)
#include "display.h"         // display definitions
#endif //DISPLAY_SUPPORT

#if (EA_PRESENT)
#include "ea.h"              // Event Arbiter definitions
#endif //EA_PRESENT

#if (BT_EMB_PRESENT || BLE_EMB_PRESENT)
#include "plf.h"             // platform definition
#include "rf.h"              // RF definitions
#endif //BT_EMB_PRESENT || BLE_EMB_PRESENT

#if (H4TL_SUPPORT)
#include "h4tl.h"
#endif //H4TL_SUPPORT

#if (AHI_TL_SUPPORT)
#include "ahi.h"
#endif //AHI_TL_SUPPORT

#if (HCI_PRESENT)
#include "hci.h"             // HCI definition
#endif //HCI_PRESENT

#if (KE_SUPPORT)
#include "ke.h"              // kernel definition
#include "ke_event.h"        // kernel event
#include "ke_timer.h"        // definitions for timer
#include "ke_mem.h"          // kernel memory manager
#endif //KE_SUPPORT

#if (SECURE_CONNECTIONS && (BT_EMB_PRESENT || BLE_EMB_PRESENT))
#include "ecc_p256.h"        // ECC P256 library
#endif // (SECURE_CONNECTIONS && (BT_EMB_PRESENT || BLE_EMB_PRESENT))

#include "dbg.h"             // debug definition
#include "log.h"
#include "bx_config.h"
#include "awo_apollo_00.h"
#include "sys_sleep.h"
#include "nvds_task.h"
#include "io_ctrl.h"
#include "rc_calib.h"
#include "compiler_flag.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// Time information
typedef struct
{
    /// Time in 625 us step.
    uint32_t time;
    /// number of us before getting next tick
    uint32_t next_tick;
} rwip_time_t;
 

#if (DEEP_SLEEP)
/// Sleep Duration Value in periodic wake-up mode
#define MAX_SLEEP_DURATION_PERIODIC_WAKEUP      0x0320  // 0.5s
/// Sleep Duration Value in external wake-up mode
#define MAX_SLEEP_DURATION_EXTERNAL_WAKEUP      0x3E80 //10s
#endif //DEEP_SLEEP

#if (DISPLAY_SUPPORT)
///Table of HW image names for display
static const char* ip_type[7] =
{
        "HW: Backup Image",
        "HW: BTDM Ripple",
        "HW: BT Ripple",
        "HW: BLE Atlas",
        "HW: Unknown",
        "HW: BLE Ripple",
        "HW: BLE Blim"
};

/// FW type display line
#if (BT_EMB_PRESENT && BLE_EMB_PRESENT)
#define FW_TYPE_DISPLAY   "FW: BTDM split emb"
#elif (BT_EMB_PRESENT)
#define FW_TYPE_DISPLAY   "FW: BT split emb"
#elif (BLE_EMB_PRESENT && BLE_HOST_PRESENT)
#define FW_TYPE_DISPLAY   "FW: BLE full"
#elif (BLE_EMB_PRESENT)
#define FW_TYPE_DISPLAY   "FW: BLE split emb"
#else
#define FW_TYPE_DISPLAY   "FW: ROM"
#endif // BT_EMB_PRESENT / BLE_EMB_PRESENT / BLE_HOST_PRESENT
#endif //DISPLAY_SUPPORT

 // Heap header size is 12 bytes
 #define RWIP_HEAP_HEADER             (12 / sizeof(uint32_t))
 // ceil(len/sizeof(uint32_t)) + RWIP_HEAP_HEADER
 #define RWIP_CALC_HEAP_LEN(len)      ((((len) + (sizeof(uint32_t) - 1)) / sizeof(uint32_t)) + RWIP_HEAP_HEADER)

/*
 * STRUCT DEFINITIONS
 ****************************************************************************************
 */
#if (BLE_EMB_PRESENT || BT_EMB_PRESENT)
/// Local supported commands
N_XIP_VARIABLE const struct rwip_prio rwip_priority[RWIP_PRIO_IDX_MAX]={
    #if (BT_EMB_PRESENT)
    {RWIP_PRIO_ACL_DFT,          RWIP_INCR_ACL_DFT},
    {RWIP_PRIO_ACL_ACT,          RWIP_INCR_ACL_ACT},
    {RWIP_PRIO_ACL_RSW,          RWIP_INCR_ACL_RSW},
    {RWIP_PRIO_ACL_SNIFF_DFT,    RWIP_INCR_ACL_SNIFF_DFT},
    {RWIP_PRIO_ACL_SNIFF_TRANS,  RWIP_INCR_ACL_SNIFF_TRANS},
    #if MAX_NB_SYNC
    {RWIP_PRIO_SCO_DFT,          RWIP_INCR_SCO_DFT},
    #endif //MAX_NB_SYNC
    {RWIP_PRIO_BCST_DFT,         RWIP_INCR_BCST_DFT},
    {RWIP_PRIO_BCST_ACT,         RWIP_INCR_BCST_ACT},
    {RWIP_PRIO_CSB_RX_DFT,       RWIP_INCR_CSB_RX_DFT},
    {RWIP_PRIO_CSB_TX_DFT,       RWIP_INCR_CSB_TX_DFT},
    {RWIP_PRIO_INQ_DFT,          RWIP_INCR_INQ_DFT},
    {RWIP_PRIO_ISCAN_DFT,        RWIP_INCR_ISCAN_DFT},
    {RWIP_PRIO_PAGE_DFT,         RWIP_INCR_PAGE_DFT},
	{RWIP_PRIO_PAGE_1ST_PKT,     RWIP_INCR_PAGE_1ST_PKT},
    {RWIP_PRIO_PCA_DFT,          RWIP_INCR_PCA_DFT},
    {RWIP_PRIO_PSCAN_DFT,        RWIP_INCR_PSCAN_DFT},
    {RWIP_PRIO_PSCAN_1ST_PKT,    RWIP_INCR_PSCAN_1ST_PKT},
    {RWIP_PRIO_SSCAN_DFT,        RWIP_INCR_SSCAN_DFT},
    {RWIP_PRIO_STRAIN_DFT,       RWIP_INCR_STRAIN_DFT},
    #endif // #if (BT_EMB_PRESENT)
    #if (BLE_EMB_PRESENT)
    {RWIP_PRIO_SCAN_DFT,         RWIP_INCR_SCAN_DFT},
    {RWIP_PRIO_INIT_DFT,         RWIP_INCR_INIT_DFT},
    {RWIP_PRIO_LE_ESTAB_DFT,     RWIP_INCR_LE_ESTAB_DFT},
    {RWIP_PRIO_LE_CON_IDLE_DFT,  RWIP_INCR_LE_CON_IDLE_DFT},
    {RWIP_PRIO_LE_CON_ACT_DFT,   RWIP_INCR_LE_CON_ACT_DFT},
    {RWIP_PRIO_ADV_DFT,          RWIP_INCR_ADV_DFT},
    {RWIP_PRIO_ADV_HDC_DFT,      RWIP_INCR_ADV_HDC_PRIO_DFT},
    #endif // #if (BLE_EMB_PRESENT)
};

N_XIP_VARIABLE const uint8_t rwip_coex_cfg[RWIP_COEX_CFG_MAX]={
    #if (BT_EMB_PRESENT)
    [RWIP_COEX_MSSWITCH_IDX]  = (RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS) \
            | (RWIP_MWS_TXEN << RWIP_MWSTXDSB_POS) | (RWIP_MWS_RXEN << RWIP_MWSRXDSB_POS),
    [RWIP_COEX_SNIFFATT_IDX]  = (RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS) \
            | (RWIP_MWS_TXEN << RWIP_MWSTXDSB_POS) | (RWIP_MWS_RXEN << RWIP_MWSRXDSB_POS),
    [RWIP_COEX_PAGE_IDX    ]  = (RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTEN << RWIP_DNABORT_POS) \
            | (RWIP_MWS_TXEN << RWIP_MWSTXDSB_POS) | (RWIP_MWS_RXEN << RWIP_MWSRXDSB_POS),
    [RWIP_COEX_PSCAN_IDX   ]  = (RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS) \
            | (RWIP_MWS_TXEN << RWIP_MWSTXDSB_POS) | (RWIP_MWS_RXEN << RWIP_MWSRXDSB_POS),
    [RWIP_COEX_INQ_IDX     ]  = (RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS) \
            | (RWIP_MWS_TXEN << RWIP_MWSTXDSB_POS) | (RWIP_MWS_RXEN << RWIP_MWSRXDSB_POS),
    [RWIP_COEX_INQRES_IDX  ]  = (RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS) \
            | (RWIP_MWS_TXEN << RWIP_MWSTXDSB_POS) | (RWIP_MWS_RXEN << RWIP_MWSRXDSB_POS),
    [RWIP_COEX_SCORSVD_IDX ]  = (RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS) \
            | (RWIP_MWS_TXEN << RWIP_MWSTXDSB_POS) | (RWIP_MWS_RXEN << RWIP_MWSRXDSB_POS),
    [RWIP_COEX_BCAST_IDX   ]  = (RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS) \
            | (RWIP_MWS_TXEN << RWIP_MWSTXDSB_POS) | (RWIP_MWS_RXEN << RWIP_MWSRXDSB_POS),
    [RWIP_COEX_CONNECT_IDX ]  = (RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS) \
            | (RWIP_MWS_TXEN << RWIP_MWSTXDSB_POS) | (RWIP_MWS_RXEN << RWIP_MWSRXDSB_POS),
    #endif // #if (BT_EMB_PRESENT)
    #if (BLE_EMB_PRESENT)
    [RWIP_COEX_CON_IDX]   	= (uint8_t)((RWIP_PTI_TXDIS << RWIP_TXBSY_POS)  | (RWIP_PTI_RXDIS << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS)),
	[RWIP_COEX_CON_DATA_IDX]= (uint8_t)((RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS)),
    [RWIP_COEX_ADV_IDX]   	= (uint8_t)((RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXDIS << RWIP_RXBSY_POS) | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS)),
    [RWIP_COEX_SCAN_IDX]  	= (uint8_t)((RWIP_PTI_TXDIS << RWIP_TXBSY_POS) | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS)),
    [RWIP_COEX_INIT_IDX]  	= (uint8_t)((RWIP_PTI_TXEN << RWIP_TXBSY_POS)  | (RWIP_PTI_RXEN << RWIP_RXBSY_POS)  | (RWIP_PTI_DNABORTDIS << RWIP_DNABORT_POS)),
    #endif // #if (BLE_EMB_PRESENT)
};
#endif//#if (BLE_EMB_PRESENT || BT_EMB_PRESENT)

/// RWBT Environment
#if (DEEP_SLEEP)
struct rwip_env_tag
{
    /// Power_up delay
    uint32_t lp_cycle_wakeup_delay;
    /// Contains sleep duration accumulated timing error
    uint32_t sleep_acc_error;
    /// Duration of sleep and wake-up algorithm (depends on CPU speed) expressed in us.
    uint16_t sleep_algo_dur;
    /// Prevent sleep bit field
    uint16_t prevent_sleep;
    /// Sleep algorithm enabled
    bool sleep_enable;
    /// External wake-up support
    bool     ext_wakeup_enable;
};
#endif //DEEP_SLEEP
/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
#if (DEEP_SLEEP)
/// RW SW environment
static struct rwip_env_tag rwip_env;
#endif //DEEP_SLEEP
/// RF API
struct rwip_rf_api rwip_rf;

/// Heap definitions - use uint32 to ensure that memory blocks are 32bits aligned.
#if (KE_MEM_RW)
/// Memory allocated for environment variables
uint32_t rwip_heap_env[RWIP_CALC_HEAP_LEN(RWIP_HEAP_ENV_SIZE)];
#if (BLE_HOST_PRESENT)
/// Memory allocated for Attribute database
uint32_t rwip_heap_db[RWIP_CALC_HEAP_LEN(RWIP_HEAP_DB_SIZE)];
#endif // (BLE_HOST_PRESENT)
/// Memory allocated for kernel messages
uint32_t rwip_heap_msg[RWIP_CALC_HEAP_LEN(RWIP_HEAP_MSG_SIZE)];
/// Non Retention memory block
uint32_t rwip_heap_non_ret[RWIP_CALC_HEAP_LEN(RWIP_HEAP_NON_RET_SIZE)];
#endif // (KE_MEM_RW)

/*
 * LOCAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */


#if (DEEP_SLEEP && BLE_EMB_PRESENT)
/**
 ****************************************************************************************
 * @brief  check If the fine counter is close the 3/4 of the slot boundary (624 >> 2) * 3 = 468
 *
 * @return when boundary wak-up is ok
 ****************************************************************************************
 */
bool rwip_check_wakeup_boundary(void)
{
    //Sample the base time count
    ble_samp_setf(1);
    while (ble_samp_getf());
    return  ((ble_finetimecnt_get() < 468) ? false : true);
}
#endif //DEEP_SLEEP && BLE_EMB_PRESENT


#if (DEEP_SLEEP)
/**
 ****************************************************************************************
 * @brief Converts a duration in slots into a number of low power clock cycles.
 * The function converts a duration in slots into a number of low power clock cycles.
 * Sleep clock runs at either 32768Hz or 32000Hz, so this function divides the value in
 * slots by 20.48 or 20 depending on the case.
 * To do this the following formulae are applied:
 *
 *   N = x * 20.48 = (2048 * x)/100 for a 32.768kHz clock or
 *   N = x * 20                     for a 32kHz clock
 *
 * @param[in] slot_cnt    The value in slot count
 *
 * @return The number of low power clock cycles corresponding to the slot count
 *
 ****************************************************************************************
 */
static uint32_t rwip_slot_2_lpcycles(uint32_t slot_cnt)
{
    uint32_t lpcycles;

    // Sanity check: The number of slots should not be too high to avoid overflow
    ASSERT_ERR(slot_cnt < 1000000);
    #if (RC32K_USED)
    lpcycles = (slot_cnt<<11)*625/get_rc32k_calib_val();
    #else
    #if HZ32000
    // Compute the low power clock cycles - case of a 32kHz clock
    lpcycles = slot_cnt * 20;
    #else //HZ32000
    // Compute the low power clock cycles - case of a 32.768kHz clock
    lpcycles = (slot_cnt << 11)/100;
    #endif //HZ32000
    #endif
    // Corner case, Sleep duration is exactly on slot boundary so slot interrupt will not
    // be generated on expected slot (but next one).

    // So reduce little bit sleep duration in order to allow fine time compensation
    // Note compensation will be in range of [1 , 2[ lp cycles

    lpcycles--;

    return(lpcycles);
}
#endif //(DEEP_SLEEP)


#if (DISPLAY_SUPPORT)
/**
 ****************************************************************************************
 * @brief Display device configuration
 *
 * This function adds graphical display
 ****************************************************************************************
 */
static void display_add_config(void)
{
    uint8_t i;
    #if (NVDS_SUPPORT)
    uint8_t dev_name_length = NVDS_LEN_DEVICE_NAME;
    uint8_t dev_name_data[NVDS_LEN_DEVICE_NAME];
    uint8_t bd_ad_length = NVDS_LEN_BD_ADDRESS;
    uint8_t bd_ad_data[NVDS_LEN_BD_ADDRESS];
    #if (PLF_UART)
    uint8_t uart_length = NVDS_LEN_UART_BAUDRATE;
    uint32_t baudrate = 921600;
    #endif //PLF_UART
    #endif // NVDS_SUPPORT
    uint32_t fw_version;
    struct plf_version plfversion;
    struct plf_version plfversion_unkn;
    uint32_t hw_version;
    uint8_t digit;
    uint8_t value;
    char* ptr;
    #if defined(CFG_RF_RIPPLE)
    uint16_t rf_id;
    char scr_rf[DISPLAY_LINE_SIZE+1];
    #endif //CFG_RF_RIPPLE
    char scr_fw_time[DISPLAY_LINE_SIZE+1];
    char scr_bd_ad[DISPLAY_LINE_SIZE+1];
    char scr_fw_version[DISPLAY_LINE_SIZE+1];
    char scr_fpga_time[DISPLAY_LINE_SIZE+1];
    char scr_fpga_version[DISPLAY_LINE_SIZE+1];
    char scr_hw_version[DISPLAY_LINE_SIZE+1];
    #if (PLF_UART && NVDS_SUPPORT)
    char scr_uart[DISPLAY_LINE_SIZE+1];
    #endif //PLF_UART

    uint8_t s_type = display_screen_alloc();
    uint8_t s_fw = display_screen_alloc();
    uint8_t s_fw_time = display_screen_alloc();
    uint8_t s_fpga_version = display_screen_alloc();
    uint8_t s_fpga_time = display_screen_alloc();
    #if (BT_EMB_PRESENT)
    uint8_t s_bthw = display_screen_alloc();
    #endif //BT_EMB_PRESENT
    #if (BLE_EMB_PRESENT)
    uint8_t s_blehw = display_screen_alloc();
    #endif //BLE_EMB_PRESENT
    uint8_t s_name = display_screen_alloc();
    uint8_t s_bd = display_screen_alloc();
    #if (PLF_UART)
    uint8_t s_uart = display_screen_alloc();
    #endif //PLF_UART
    uint8_t s_rf = display_screen_alloc();

    // List all screens
    display_screen_insert(s_fpga_version, s_type);
    display_screen_insert(s_fpga_time, s_type);
    display_screen_insert(s_fw, s_type);
    display_screen_insert(s_fw_time, s_type);
    #if (BT_EMB_PRESENT)
    display_screen_insert(s_bthw, s_type);
    #endif //BT_EMB_PRESENT
    #if (BLE_EMB_PRESENT)
    display_screen_insert(s_blehw, s_type);
    #endif //BLE_EMB_PRESENT
    display_screen_insert(s_name, s_type);
    display_screen_insert(s_bd, s_type);
    #if (PLF_UART)
    display_screen_insert(s_uart, s_type);
    #endif //PLF_UART
    display_screen_insert(s_rf, s_type);

    // Get platform version, date, time ...
    plf_read_version(&plfversion);

    /************************************************************************/
    /*                              FW TYPE                                 */
    /************************************************************************/
    memset(&plfversion_unkn, 0, sizeof(plfversion_unkn));
    if(plfversion.ip_type > 6 || (memcmp(&plfversion, &plfversion_unkn, sizeof(plfversion_unkn)) == 0))
        display_screen_set(s_type, NULL, "HW: Unknown" ,FW_TYPE_DISPLAY);
    else
        display_screen_set(s_type, NULL, ip_type[plfversion.ip_type] ,FW_TYPE_DISPLAY);

    /************************************************************************/
    /*                             FW VERSION                               */
    /************************************************************************/
    rwip_version((uint8_t*)&fw_version, (uint8_t*)&hw_version);
    i = 11;
    *(scr_fw_version+i) = '\0';
    while(i-- > 0)
    {
        digit = fw_version&0xF;
        digit += (digit < 10) ? 48:55;
        *(scr_fw_version+i) = (char)digit;
        fw_version >>= 4;
        if(i == 3 || i==6 || i==9)
        {
            *(scr_fw_version+(--i)) = '.';
        }
    }
    display_screen_set(s_fw, NULL, "FW version:", scr_fw_version);

    /************************************************************************/
    /*                              FW TIME                                 */
    /************************************************************************/
    /* Build the FW type screen with:
     *  - type
     *  - build date "Mmm dd yyyy"
     *  - build time "hh:mm:ss"
     */
    strncpy(scr_fw_time, __DATE__, 7);
    strncpy(scr_fw_time+7, __TIME__, 8);
    scr_fw_time[DISPLAY_LINE_SIZE] = '0';
    display_screen_set(s_fw_time, NULL, "FW date:", scr_fw_time);

    /************************************************************************/
    /*                            FPGA VERSION                              */
    /************************************************************************/
    // Plf type
    scr_fpga_version[0] = plfversion.plf_type + ((plfversion.plf_type < 10) ? 48:55);
    scr_fpga_version[1] = '.';
    // Ip type
    scr_fpga_version[2] = plfversion.ip_type + ((plfversion.ip_type < 10) ? 48:55);
    scr_fpga_version[3] = '.';
    // Version
    i = 10;
    while(i-- > 4)
    {
        digit = plfversion.version &0xF;
        digit += (digit < 10) ? 48:55;
        *(scr_fpga_version+i) = (char)digit;
        plfversion.version >>= 4;
    }
    scr_fpga_version[10] = '\0';
    display_screen_set(s_fpga_version, NULL, "FPGA version:", scr_fpga_version);

    /************************************************************************/
    /*                           FPGA DATE/TIME                             */
    /************************************************************************/
    ptr = scr_fpga_time;
    // Month
    value = plfversion.month;
    digit = (value/10) + 48;
    *(ptr++) = (char)digit;
    digit = (value - 10*(value/10)) + 48;
    *(ptr++) = (char)digit;
    *(ptr++) = '_';
    // Day
    value = plfversion.day;
    digit = (value/10) + 48;
    *(ptr++) = (char)digit;
    digit = (value - 10*(value/10)) + 48;
    *(ptr++) = (char)digit;
    *(ptr++) = ' ';
    // Hours
    value = plfversion.hour;
    digit = (value/10) + 48;
    *(ptr++) = (char)digit;
    digit = (value - 10*(value/10)) + 48;
    *(ptr++) = (char)digit;
    *(ptr++) = ':';
    // Minutes
    value = plfversion.minute;
    digit = (value/10) + 48;
    *(ptr++) = (char)digit;
    digit = (value - 10*(value/10)) + 48;
    *(ptr++) = (char)digit;
    *(ptr++) = ':';
    // Seconds
    value = plfversion.second;
    digit = (value/10) + 48;
    *(ptr++) = (char)digit;
    digit = (value - 10*(value/10)) + 48;
    *(ptr++) = (char)digit;
    *(ptr++) = '\0';
    display_screen_set(s_fpga_time, NULL, "FPGA Date:", scr_fpga_time);

    #if BT_EMB_PRESENT
    /************************************************************************/
    /*                           BT HW VERSION                              */
    /************************************************************************/
    i = 11;
    *(scr_hw_version+i) = '\0';
    while(i-- > 0)
    {
        digit = hw_version&0xF;
        digit += (digit < 10) ? 48:55;
        *(scr_hw_version+i) = (char)digit;
        hw_version >>= 4;
        if(i == 3 || i==6 || i==9)
        {
            *(scr_hw_version+(--i)) = '.';
        }
    }
    display_screen_set(s_bthw, NULL, "BT HW version:", scr_hw_version);
    #endif //BT_EMB_PRESENT

    #if (BLE_EMB_PRESENT)
    /************************************************************************/
    /*                           BLE HW VERSION                             */
    /************************************************************************/
    rwip_version((uint8_t*)&fw_version, (uint8_t*)&hw_version);
    i = 11;
    *(scr_hw_version+i) = '\0';
    while(i-- > 0)
    {
        digit = hw_version&0xF;
        digit += (digit < 10) ? 48:55;
        *(scr_hw_version+i) = (char)digit;
        hw_version >>= 4;
        if(i == 3 || i==6 || i==9)
        {
            *(scr_hw_version+(--i)) = '.';
        }
    }
    display_screen_set(s_blehw, NULL, "BLE HW version:", scr_hw_version);
    #endif //BLE_EMB_PRESENT

    /************************************************************************/
    /*                            DEVICE NAME                               */
    /************************************************************************/
    #if (NVDS_SUPPORT)
    if(nvds_get(NVDS_TAG_DEVICE_NAME, &dev_name_length, dev_name_data) == NVDS_OK)
    {
        // Put end of line
        if(dev_name_length > 16)
        {
            dev_name_length = 16;
        }
        dev_name_data[dev_name_length] = '\0';
    }
    else
    {
        dev_name_data[0] = '\0';
    }
    display_screen_set(s_name, NULL, "Device name:", (char*)dev_name_data);
    #else // NVDS_SUPPORT
    display_screen_set(s_name, NULL, "Device name:", "");
    #endif // NVDS_SUPPORT

    /************************************************************************/
    /*                              BD ADDRESS                              */
    /************************************************************************/
    strcpy(scr_bd_ad, "0x");
    #if (NVDS_SUPPORT)
    if(nvds_get(NVDS_TAG_BD_ADDRESS, &bd_ad_length, bd_ad_data) == NVDS_OK)
    {
        // Encode to ASCII
        for(i = 0; i < NVDS_LEN_BD_ADDRESS; i++)
        {
            digit = bd_ad_data[NVDS_LEN_BD_ADDRESS-1-i]>>4;
            digit += (digit < 10) ? 48:55;
            *(scr_bd_ad+2+2*i) = (char)digit;
            digit = bd_ad_data[NVDS_LEN_BD_ADDRESS-1-i]&0xF;
            digit += (digit < 10) ? 48:55;
            *(scr_bd_ad+2+2*i+1) = (char)digit;
        }
    }
    scr_bd_ad[14] = '\0';
    display_screen_set(s_bd, NULL, "BD Address:", scr_bd_ad);
    #else // NVDS_SUPPORT
    display_screen_set(s_bd, NULL, "BD Address:", "");
    #endif // NVDS_SUPPORT


    #if (PLF_UART)
    /************************************************************************/
    /*                            UART BAUDRATE                             */
    /************************************************************************/

    #if (NVDS_SUPPORT)
    // Get UART baudrate from NVDS
    if(nvds_get(NVDS_TAG_UART_BAUDRATE, &uart_length, (uint8_t*) &baudrate) == NVDS_OK)
    {
        if(baudrate > 3500000 || baudrate < 9600)
        {
            baudrate = 921600;
        }
    }
    else
    {
        baudrate = 921600;
    }

    // Display UART baudrate on screen
    strcpy(scr_uart, "        bps");
    i = 0;
    while (baudrate > 0)
    {
        scr_uart[6-i++] = (baudrate - (10*(baudrate / 10))) + 48;
        baudrate = baudrate / 10;
    }
    display_screen_set(s_uart, NULL, "UART baudrate:", scr_uart);
    #else // NVDS_SUPPORT
    display_screen_set(s_uart, NULL, "UART baudrate:", "");
    #endif // NVDS_SUPPORT
    #endif //PLF_UART


    /************************************************************************/
    /*                               RF BOARD                               */
    /************************************************************************/

    #if defined(CFG_RF_RIPPLE)
    // Read board ID in platform
    rf_id = plf_read_rf_board_id();
    // Add screen to display RF board type
    strcpy(scr_rf, "Ripple #");
    scr_rf[8] = (rf_id/10) + 48;
    scr_rf[9] = (rf_id - (10*(rf_id/10))) + 48;
    scr_rf[10] = '\0';
    display_screen_set(s_rf, NULL, "RF board:", scr_rf);
    #elif defined (CFG_RF_BLUEJAY)
    display_screen_set(s_rf, NULL, "RF board:", "Bluejay");
    #elif defined(CFG_RF_ATLAS)
    display_screen_set(s_rf, NULL, "RF board:", "Atlas");
    #elif defined(CFG_RF_BLIM)
    display_screen_set(s_rf, NULL, "RF board:", "Blim");
    #endif //CFG_RF


    // Start with FW type screen
    display_start(s_type);
}
#endif //DISPLAY_SUPPORT

/**
 * @brief Get current time info
 *
 * @return current time info sampled in active baseband core
 */
static rwip_time_t rwip_time_get(void)
{
    rwip_time_t res;

    #if (BT_EMB_PRESENT)
    //Sample the base time count
    bt_slotclk_samp_setf(1);
    while (bt_slotclk_samp_getf());

    // Read current time in HW
    res.time      = (bt_slotclk_sclk_getf() >> 1)& MAX_SLOT_CLOCK;
    res.next_tick = bt_finetimecnt_get();

    #elif (BLE_EMB_PRESENT)
    //Sample the base time count
    ble_samp_setf(1);
    while (ble_samp_getf());

    // Read current time in HW
    res.time      =  ble_basetimecnt_get() & MAX_SLOT_CLOCK;
    res.next_tick =  ble_finetimecnt_get();
    #endif

    return res;
}
/*
 * EXPORTED FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void rwip_init(uint32_t error)
{
    #if (DEEP_SLEEP)
    // Reset RW environment
    memset(&rwip_env, 0, sizeof(rwip_env));
    #endif //DEEPSLEEP

    #if (KE_SUPPORT)
    // Initialize kernel
    ke_init();

    // Initialize memory heap used by kernel.
    #if (KE_MEM_RW)
    // Memory allocated for environment variables
    ke_mem_init(KE_MEM_ENV,           (uint8_t*)rwip_heap_env,     RWIP_HEAP_ENV_SIZE);
    #if (BLE_HOST_PRESENT)
    // Memory allocated for Attribute database
    ke_mem_init(KE_MEM_ATT_DB,        (uint8_t*)rwip_heap_db,      RWIP_HEAP_DB_SIZE);
    #endif // (BLE_HOST_PRESENT)
    // Memory allocated for kernel messages
    ke_mem_init(KE_MEM_KE_MSG,        (uint8_t*)rwip_heap_msg,     RWIP_HEAP_MSG_SIZE);
    // Non Retention memory block
    ke_mem_init(KE_MEM_NON_RETENTION, (uint8_t*)rwip_heap_non_ret, RWIP_HEAP_NON_RET_SIZE);
    #endif // (KE_MEM_RW)
    #endif //KE_SUPPORT

    // Initialize RF
    #if (BT_EMB_PRESENT || BLE_EMB_PRESENT)
    rf_init(&rwip_rf);
    #endif //BT_EMB_PRESENT || BLE_EMB_PRESENT

    #if (DISPLAY_SUPPORT)
    // Initialize display module
    display_init();

    // Add some configuration information to display
    display_add_config();
    #endif //DISPLAY_SUPPORT

    #if (SECURE_CONNECTIONS && (BT_EMB_PRESENT || BLE_EMB_PRESENT))
    // Initialize Diffie Hellman Elliptic Curve Algorithm
    ecc_init(false);
    #endif // (SECURE_CONNECTIONS && (BT_EMB_PRESENT || BLE_EMB_PRESENT))

    // Initialize H4 TL
    #if (H4TL_SUPPORT)
    #if (BLE_HOST_PRESENT)
    #if (BLE_EMB_PRESENT) // FULL HOST
    h4tl_init(H4TL_TYPE_AHI, rwip_eif_get(RWIP_EIF_AHI));
    #else // !(BLE_EMB_PRESENT)  // SPLIT HOST
    #if(AHI_TL_SUPPORT)
    h4tl_init(H4TL_TYPE_AHI, rwip_eif_get(RWIP_EIF_AHI));
    #endif // AHI_TL_SUPPORT
    h4tl_init(H4TL_TYPE_HCI, rwip_eif_get(RWIP_EIF_HCIH));
    #endif // (BLE_EMB_PRESENT)
    #else // !(BLE_HOST_PRESENT) // SPLIT EMB
    h4tl_init(H4TL_TYPE_HCI, rwip_eif_get(RWIP_EIF_HCIC));
    #endif // (BLE_HOST_PRESENT)
    #endif //(H4TL_SUPPORT)

    #if (HCI_PRESENT)
    // Initialize the HCI
    hci_init();
    #endif //HCI_PRESENT

    #if (AHI_TL_SUPPORT)
    // Initialize the Application Host Interface
    ahi_init();
    #endif //AHI_TL_SUPPORT

    #if (BLE_HOST_PRESENT)
    // Initialize BLE Host stack
    rwble_hl_init();
    #endif //BLE_HOST_PRESENT

    #if (BT_EMB_PRESENT)
    // Initialize BT
    rwbt_init();
    #endif //BT_EMB_PRESENT

    #if (BLE_EMB_PRESENT)
    // Initialize BLE
    rwble_init();
    #endif //BLE_EMB_PRESENT

    #if (BT_EMB_PRESENT || BLE_EMB_PRESENT)
    #if (RW_DEBUG)
    // Initialize the debug process
    dbg_init();
    #endif //(RW_DEBUG)
    #endif //(BT_EMB_PRESENT || BLE_EMB_PRESENT)

    #if (EA_PRESENT)
    //Initialize Event arbiter
    ea_init(false);
    #endif //(EA_PRESENT)

    #if (DEEP_SLEEP)
    // at device initialization, disable deep sleep, enable it at reset only
    rwip_env.sleep_enable = false;
    #endif // (DEEP_SLEEP)

    #if (BT_EMB_PRESENT || (BLE_EMB_PRESENT && !BLE_HOST_PRESENT))
    // If FW initializes due to FW reset, send the message to Host
    if(error != RESET_NO_ERROR)
    {
        if(error == RESET_TO_ROM || error == RESET_AND_LOAD_FW)
        {
            // Send platform reset command complete if requested by user
            dbg_platform_reset_complete(error);
        }
        else
        {
            // Allocate a message structure for hardware error event
            struct hci_hw_err_evt *evt = KE_MSG_ALLOC(HCI_EVENT, 0, HCI_HW_ERR_EVT_CODE, hci_hw_err_evt);

            // Fill the HW error code
            switch(error)
            {
                case RESET_MEM_ALLOC_FAIL: evt->hw_code = CO_ERROR_HW_MEM_ALLOC_FAIL; break;
                default: ASSERT_INFO(0, error, 0); break;
            }

            // Send the message
            hci_send_2_host(evt);
        }
    }
    #endif //(BT_EMB_PRESENT || (BLE_EMB_PRESENT && !BLE_HOST_PRESENT))

    /*
     ************************************************************************************
     * Application initialization
     ************************************************************************************
     */
    #if (!(defined(CFG_FREERTOS_SUPPORT)&&(CFG_FREERTOS_SUPPORT==1)))
    #if (BLE_APP_PRESENT)
    // Initialize APP
    user_ble_init();
    #endif //BLE_APP_PRESENT
    #endif/*(defined(CFG_FREERTOS_SUPPORT)&&(CFG_FREERTOS_SUPPORT==1))*/
    #if LOCAL_NVDS == 0
    nvds_task_init();
    #endif
}

void rwip_reset(void)
{
    #if (NVDS_SUPPORT && DEEP_SLEEP)
    uint8_t length = 1;
    uint8_t sleep_enable;
    uint8_t ext_wakeup_enable;
    #endif //NVDS_SUPPORT && DEEP_SLEEP

    // Disable interrupts until reset procedure is completed
    GLOBAL_INT_DISABLE();

    #if (KE_SUPPORT)
    //Clear all message and timer pending
    ke_flush();
    #endif //KE_SUPPORT

    #if (SECURE_CONNECTIONS && (BT_EMB_PRESENT || BLE_EMB_PRESENT))
    // Reset Diffie Hellman Elliptic Curve Algorithm
    ecc_init(true);
    #endif // (SECURE_CONNECTIONS && (BT_EMB_PRESENT || BLE_EMB_PRESENT))

    #if (HCI_PRESENT)
    // Reset the HCI
    hci_reset();
    #endif //HCI_PRESENT

    #if (BT_EMB_PRESENT)
    // Reset BT
    rwbt_reset();
    #endif //BT_EMB_PRESENT

    #if (BLE_EMB_PRESENT)
    // Reset BLE
    rwble_reset();
    #endif //BLE_EMB_PRESENT


    #if (NVDS_SUPPORT && DEEP_SLEEP)
    // Activate deep sleep feature if enabled in NVDS
    if(nvds_get(NVDS_TAG_SLEEP_ENABLE, &length, &sleep_enable) == NVDS_OK)
    {
        if(sleep_enable != 0)
        {
            rwip_env.sleep_enable    = true;
            rwip_env.sleep_acc_error = 0;

            // Set max sleep duration depending on wake-up mode
            if(nvds_get(NVDS_TAG_EXT_WAKEUP_ENABLE, &length, &ext_wakeup_enable) == NVDS_OK)
            {
                if(ext_wakeup_enable != 0)
                {
                    rwip_env.ext_wakeup_enable = true;
                }
            }

            // Set max sleep duration depending on wake-up mode
            length = NVDS_LEN_SLEEP_ALGO_DUR;
            if(nvds_get(NVDS_TAG_SLEEP_ALGO_DUR, &length,  (uint8_t*) &rwip_env.sleep_algo_dur) != NVDS_OK)
            {
                // set a default duration: 200 us
                rwip_env.sleep_algo_dur = 200;
            }
        }
    }
    #endif //NVDS_SUPPORT && DEEP_SLEEP

	rwip_env.sleep_enable    = true;
    rwip_env.sleep_acc_error = 0;
	rwip_env.ext_wakeup_enable = true;
	rwip_env.sleep_algo_dur = 200;

    #if (EA_PRESENT)
    ea_init(true);
    #endif //(EA_PRESENT)

    // Reset the RF
    rwip_rf.reset();

    #if (DISPLAY_SUPPORT)
    // Restart display module
    display_resume();
    #endif //DISPLAY_SUPPORT

    // Restore interrupts once reset procedure is completed
    GLOBAL_INT_RESTORE();
}

void rwip_version(uint8_t* fw_version, uint8_t* hw_version)
{
    #if (BT_EMB_PRESENT)
    rwbt_version(fw_version , hw_version);
    #elif (BLE_EMB_PRESENT)
    rwble_version(fw_version , hw_version);
    #endif //BT_EMB_PRESENT / BLE_EMB_PRESENT
}

void rwip_schedule(void)
{
    #if (KE_SUPPORT)
    #if (DEEP_SLEEP)
    // If system is waking up, delay the handling
    if ((rwip_env.prevent_sleep & RW_WAKE_UP_ONGOING) == 0)
    #endif // DEEP_SLEEP
    {
        // schedule all pending events
        ke_event_schedule();
    }
    #endif //KE_SUPPORT
}

#if(RC32K_USED)
static void ble_wakeup_time_update()
{
    bx_lld_wakeup_time_set();
}
#else
static void ble_wakeup_time_update(){}
#endif

uint8_t rwip_sleep()
{
    uint8_t sleep_type = 0;
    #if (DEEP_SLEEP)
    int32_t sleep_duration;
    rwip_time_t current_time;

    // 10 ms target timer
    uint32_t timer_10ms_target;
    // Slot target timer
    uint32_t timer_slot_target;
    #endif //  DEEP_SLEEP

    ble_wakeup_time_update();

    DBG_SWDIAG(SLEEP, ALGO, 0);

    do
    {
        /************************************************************************
         **************            CHECK KERNEL EVENTS             **************
         ************************************************************************/
        #if (!DEEP_SLEEP)
        // Check if some kernel processing is ongoing
        if (!ke_sleep_check())
            break;
        // Processor sleep can be enabled
        proc_sleep = true;

        #else // (DEEP_SLEEP)
        // Check if some kernel processing is ongoing
        if (((rwip_env.prevent_sleep & RW_WAKE_UP_ONGOING) == 0) && !ke_sleep_check())
            break;
        // Processor sleep can be enabled
        sleep_type = PROCESSOR_SLEEP;

        DBG_SWDIAG(SLEEP, ALGO, 1);

        /************************************************************************
         **************             CHECK ENABLE FLAG              **************
         ************************************************************************/
        // Check sleep enable flag
        if(!rwip_env.sleep_enable)
            break;
        /************************************************************************
         **************              CHECK RW FLAGS                **************
         ************************************************************************/
        // First check if no pending procedure prevent from going to sleep
        if (rwip_env.prevent_sleep != 0)
            break;
        DBG_SWDIAG(SLEEP, ALGO, 2);


        #if (BT_EMB_PRESENT)
        /************************************************************************
         **************                 CHECK BT                   **************
         ************************************************************************/
        if (!rwbt_sleep_check())
            break;
        #endif //BT_EMB_PRESENT

        #if (BLE_EMB_PRESENT)
        /************************************************************************
         **************                 CHECK BLE                   **************
         ************************************************************************/
        if (!rwble_sleep_check())
            break;
        #endif //(BLE_EMB_PRESENT)
        DBG_SWDIAG(SLEEP, ALGO, 3);


        /************************************************************************
         **************            RETRIEVE CURRENT TIME           **************
         ************************************************************************/

        current_time = rwip_time_get();
        // remove the on-going slot for clock correction
        current_time.time += 1;
        // Remove 1 more solt because next slot will be started at end of function
        if(current_time.next_tick < rwip_env.sleep_algo_dur)
        {
            current_time.time += 1;
        }

        // Be sure that we don't exceed the clock wrapping time
        current_time.time &= MAX_SLOT_CLOCK;


        /************************************************************************
         **************     Get 10ms timer or slot timer target    **************
         ************************************************************************/
        timer_10ms_target = ke_timer_target_get();

        timer_slot_target = ea_timer_target_get(current_time.time);


        /************************************************************************
         **************           COMPUTE SLEEP DURATION           **************
         ************************************************************************/
        // no timer set
        if((timer_10ms_target == RWIP_INVALID_TARGET_TIME)
                && (timer_slot_target == RWIP_INVALID_TARGET_TIME))
        {
            sleep_duration = MAX_SLEEP_DURATION_EXTERNAL_WAKEUP;
        }
        // only half slot timer programmed
        else if (timer_10ms_target == RWIP_INVALID_TARGET_TIME)
        {
            sleep_duration = CLK_DIFF(current_time.time, timer_slot_target);
        }
        // only 10 ms timer programmed
        else if (timer_slot_target == RWIP_INVALID_TARGET_TIME)
        {
            sleep_duration = CLK_DIFF(current_time.time, timer_10ms_target);
        }
        // 10 ms timer target is greater than Half slot timer target
        else if (CLK_DIFF(timer_slot_target, timer_10ms_target) > 0)
        {
            // use half slot timer target
            sleep_duration = CLK_DIFF(current_time.time, timer_slot_target);
        }
        // Half slot timer target is greater than 10 ms timer target
        else
        {
            // use 10ms timer target
            sleep_duration = CLK_DIFF(current_time.time, timer_10ms_target);
        }

        DBG_SWDIAG(SLEEP, ALGO, 4);

        /************************************************************************
         **************           CHECK EXT WAKEUP FLAG            **************
         ************************************************************************/
        /* If external wakeup enable, sleep duration can be set to maximum, otherwise
         *  system should be woken-up periodically to poll incoming packets from HCI */
        if(!rwip_env.ext_wakeup_enable && (sleep_duration > MAX_SLEEP_DURATION_PERIODIC_WAKEUP))
        {
            sleep_duration = MAX_SLEEP_DURATION_PERIODIC_WAKEUP;
        }
        else if(sleep_duration > MAX_SLEEP_DURATION_EXTERNAL_WAKEUP)
        {
            sleep_duration = MAX_SLEEP_DURATION_EXTERNAL_WAKEUP;
        }

        // check if sleep duration is sufficient to allow clock to be ready
        if(sleep_duration <= RWIP_MINIMUM_SLEEP_TIME)
        {
            break;
        }

        sleep_duration = rwip_slot_2_lpcycles(sleep_duration);

        // check if sleep duration is sufficient according to wake-up delay
        // HW issue, if sleep duration = max(twosc,twext) + 1 the HW never wakes up, so we have to ensure that at least
        // sleep duration > max(twosc,twext) + 1 (all in lp clk cycle)
        if(sleep_duration < rwip_env.lp_cycle_wakeup_delay + 1)
        {
            break;
        }


        DBG_SWDIAG(SLEEP, ALGO, 5);

        #if (H4TL_SUPPORT)
        /************************************************************************
         **************                 CHECK TL                   **************
         ************************************************************************/
        // Try to switch off TL
        /*
        if (!h4tl_stop())
        {
            sleep_type &= ~PROCESSOR_SLEEP;
            break;
        }
        */
        #endif //H4TL_SUPPORT

        DBG_SWDIAG(SLEEP, ALGO, 6);

        /************************************************************************
         **************          PROGRAM CORE DEEP SLEEP           **************
         ************************************************************************/
        #if (BT_EMB_PRESENT)
        // Put BT core into deep sleep
        rwbt_sleep_enter(sleep_duration, rwip_env.ext_wakeup_enable);
        #elif (BLE_EMB_PRESENT)
        // Put BT core into deep sleep
        lld_sleep_enter(sleep_duration, rwip_env.ext_wakeup_enable);
        #endif //BT_EMB_PRESENT / BT_EMB_PRESENT

//        led_set(2);

        DBG_SWDIAG(SLEEP, SLEEP, 1);

        /************************************************************************
         **************               SWITCH OFF RF                **************
         ************************************************************************/
        rwip_rf.sleep();
        
        sleep_type |= BLE_DEEP_SLEEP;

        #endif // DEEP_SLEEP
    } while(0);
    return sleep_type;
}

#if (DEEP_SLEEP)
N_XIP_SECTION void rwip_wakeup(void)
{
    DBG_SWDIAG(SLEEP, SLEEP, 0);

//    led_set(6);
//    led_reset(2);

    // Prevent going to deep sleep until a slot interrupt is received
    rwip_prevent_sleep_set(RW_WAKE_UP_ONGOING);

    #if (BT_EMB_PRESENT)
    // Wake-up BT core
    rwbt_sleep_wakeup();
    #elif (BLE_EMB_PRESENT)
    // Wake-up BLE core
    lld_sleep_wakeup();
    #endif //BT_EMB_PRESENT / BLE_EMB_PRESENT

    #if (H4TL_SUPPORT)
    // Restart the flow on the TL
    //h4tl_start();
    #endif //H4TL_SUPPORT
    mac_status = active_clk;

}

N_XIP_SECTION void rwip_wakeup_end(void)
{
    #if HW_BX_VERSION == 00
    hwp_sysc_awo->awo_reset_signal.val = SRST_BLE_LP_SET;
    #endif
    ble_lp_intr_clr();
    ble_lp_irq_enable();
    if(rwip_env.prevent_sleep & RW_WAKE_UP_ONGOING)
    {
        #if (BT_EMB_PRESENT)
        rwbt_sleep_wakeup_end();
        #elif (BLE_EMB_PRESENT)
        // Wake-up BLE core
        lld_sleep_wakeup_end();
        #endif //BT_EMB_PRESENT / BLE_EMB_PRESENT

        // Schedule the kernel timers
        ke_event_set(KE_EVENT_KE_TIMER);

        // Wake up is complete now, so we allow the deep sleep again
        rwip_prevent_sleep_clear(RW_WAKE_UP_ONGOING);

//        led_reset(6);
    }
}

void rwip_wakeup_delay_set(uint16_t wakeup_delay)
{
    rwip_env.lp_cycle_wakeup_delay = rwip_us_2_lpcycles(wakeup_delay);
}

N_XIP_SECTION void rwip_prevent_sleep_set(uint16_t prv_slp_bit)
{
    GLOBAL_INT_DISABLE();
    rwip_env.prevent_sleep |= prv_slp_bit;
    DBG_SWDIAG(SLEEP, PREVENT, rwip_env.prevent_sleep);
    GLOBAL_INT_RESTORE();
}

N_XIP_SECTION void rwip_prevent_sleep_clear(uint16_t prv_slp_bit)
{
    GLOBAL_INT_DISABLE();
    rwip_env.prevent_sleep &= ~prv_slp_bit;
    DBG_SWDIAG(SLEEP, PREVENT, rwip_env.prevent_sleep);
    GLOBAL_INT_RESTORE();
}

bool rwip_sleep_enable(void)
{
    return rwip_env.sleep_enable;
}

void rwip_sleep_enable_set(bool val)
{
    rwip_env.sleep_enable = val;
}

bool rwip_ext_wakeup_enable(void)
{
    return rwip_env.ext_wakeup_enable;
}

/**
 ****************************************************************************************
 * @brief Converts a duration in lp cycles into a duration is us.
 *
 * The function converts a duration in lp cycles into a duration is us, according to the
 * low power clock frequency (32768Hz or 32000Hz).
 *
 * To do this the following formulae are applied:
 *
 *   Tus = x*30.517578125 = 30*x + x/2 + x/64 + x/512 for a 32.768kHz clock or
 *   Tus = x*31.25        = 31*x + x/4                for a 32kHz clock
 *
 *
 * @param[in] lpcycles    duration in lp cycles
 *
 * @return duration in us
 ****************************************************************************************
 */
N_XIP_SECTION uint32_t rwip_sleep_lpcycles_2_us(uint32_t lpcycles)
{
    uint32_t res;

    // Sanity check: The number of lp cycles should not be too high to avoid overflow
    ASSERT_ERR(lpcycles < 1000000);
    #if (RC32K_USED)
    rwip_env.sleep_acc_error = lpcycles*get_rc32k_calib_val() + rwip_env.sleep_acc_error;
    res = rwip_env.sleep_acc_error >> 11;
    rwip_env.sleep_acc_error = rwip_env.sleep_acc_error - (res<<11);
    #else
    #if (HZ32000)
    // Compute the sleep duration in us - case of a 32kHz clock and insert previous computed error
    rwip_env.sleep_acc_error = lpcycles + rwip_env.sleep_acc_error;
    // get the truncated value
    res = rwip_env.sleep_acc_error >> 2;
    // retrieve new inserted error
    rwip_env.sleep_acc_error = rwip_env.sleep_acc_error - (res << 2);
    // finish computation
    res = (31 * lpcycles) + res;
    #else //HZ32000
    // Compute the sleep duration in half us - case of a 32.768kHz clock and insert previous computed error
    rwip_env.sleep_acc_error = ((lpcycles << 8) + (lpcycles << 3) + lpcycles) + rwip_env.sleep_acc_error;
    // get the truncated value
    res = rwip_env.sleep_acc_error >> 9;
    // retrieve new inserted error
    rwip_env.sleep_acc_error = rwip_env.sleep_acc_error - (res << 9);
    // finish computation
    res = (30 * lpcycles) + res;
    #endif //HZ32000
    #endif
    return res;
}


/**
 ****************************************************************************************
 * @brief Converts a duration in us into a duration in lp cycles.
 *
 * The function converts a duration in us into a duration is lp cycles, according to the
 * low power clock frequency (32768Hz or 32000Hz).
 *
 * @param[in] us    duration in us
 *
 * @return duration in lpcycles
 ****************************************************************************************
 */
uint32_t rwip_us_2_lpcycles(uint32_t us)
{
    uint32_t lpcycles;
    #if (RC32K_USED)
    lpcycles = (us<<11)/get_rc32k_calib_val() ;
    #else
    #if (HZ32000)
    // Compute the low power clock cycles - case of a 32kHz clock
    lpcycles = (us * 32) / 1000;
    #else //HZ32000
    // Compute the low power clock cycles - case of a 32.768kHz clock
    lpcycles = (us * 32768) / 1000000;
    #endif //HZ32000
    #endif

    return(lpcycles);
}

#endif// DEEP_SLEEP

#if (BT_EMB_PRESENT)

#if PCA_SUPPORT
bool rwip_pca_clock_dragging_only(void)
{
#if (BLE_EMB_PRESENT)
    return rwble_activity_ongoing_check();
#else
    return false;
#endif // BLE_EMB_PRESENT
}
#endif // PCA_SUPPORT
#endif // BT_EMB_PRESENT

#if (BT_EMB_PRESENT || BLE_EMB_PRESENT)
#if (RW_MWS_COEX)
void rwip_mwscoex_set(bool state)
{
#if (BLE_EMB_PRESENT)
    lld_mwscoex_set(state);
#endif // BLE_EMB_PRESENT
#if (BT_EMB_PRESENT)
    ld_mwscoex_set(state);
#endif // BT_EMB_PRESENT
}
#endif // RW_MWS_COEX
#if (RW_WLAN_COEX)
void rwip_wlcoex_set(bool state)
{
#if (BLE_EMB_PRESENT)
    lld_wlcoex_set(state);
#endif // BLE_EMB_PRESENT
#if (BT_EMB_PRESENT)
    ld_wlcoex_set(state);
#endif // BT_EMB_PRESENT
}
#endif // RW_WLAN_COEX
#endif // (BT_EMB_PRESENT || BLE_EMB_PRESENT)

#if RW_DEBUG
void rwip_assert_err(const char * file, int line, int param0, int param1)
{
    #if (BT_EMB_PRESENT || (BLE_EMB_PRESENT && !BLE_HOST_PRESENT))
    struct hci_dbg_assert_err_evt *evt = KE_MSG_ALLOC_DYN(HCI_DBG_EVT, 0, 0, hci_dbg_assert_err_evt, sizeof(struct hci_dbg_assert_err_evt) + strlen(file));
    evt->subcode = HCI_DBG_ASSERT_ERR_EVT_SUBCODE;
    evt->line = line;
    evt->param0 = param0;
    evt->param1 = param1;
    strcpy((char *) evt->file, file);
    hci_send_2_host(evt);
    #endif //(BT_EMB_PRESENT || (BLE_EMB_PRESENT && !BLE_HOST_PRESENT))
}
#endif //RW_DEBUG

///@} RW
