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
#define __RAM_CODE__

/* includes ------------------------------------------------------------------*/

#include "rf.h"            // RF interface
#include "rwip.h"          // for RF API structure definition
#include "reg_blecore.h"   // ble core registers
#include <string.h>
#include "bx_config.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_awo_apollo_00.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

#if RF_PARAM == 0
#define RF_POWER_MAX 0x06

static const int8_t rf_rssi_map[128] ={
    [0]= -100,    [1]= -99,    [2]= -98,    [3]= -98,    [4]= -97,    [5]= -97,    [6]= -96,    [7]= -96,    [8]= -95,    [9]= -95,    [10]= -94,   [11]= -94,   [12]= -94,   [13]= -93,   [14]= -93,   [15]= -93,
    [16]=-92 ,   [17]= -92,   [18]= -92,   [19]= -91,   [20]= -91,   [21]= -91,   [22]=-90,   [23]= -90,   [24]= -90,   [25]= -89 ,   [26]= -89,   [27]=-88 ,   [28]= -88,   [29]= -87,   [30]=-87 ,   [31]=-86,
    [32]= -86,   [33]=-86 ,   [34]= -85,   [35]= -85,   [36]=-84,   [37]=-84 ,   [38]= -83,   [39]= -83,   [40]=-82 ,   [41]= -82,   [42]= -82,   [43]= -81,   [44]= -81,   [45]=-80 ,   [46]= -80,   [47]= -79,
    [48]= -79,   [49]= -79,   [50]=-78 ,   [51]= -78,   [52]=-77 ,   [53]= -77,   [54]= -76,   [55]=-76 ,   [56]= -76,   [57]=-75 ,   [58]=-75 ,   [59]= -75,   [60]=-74 ,   [61]= -74,   [62]=-73 ,   [63]= -73,
    [64]= -73,   [65]=-73 ,   [66]=-72 ,   [67]= -72,   [68]=-71 ,   [69]= -71,   [70]= -71,   [71]=-70 ,   [72]= -70,   [73]= -70,   [74]=-69 ,   [75]= -69,   [76]=-68 ,   [77]= -68,   [78]= -68,   [79]= -68,
    [80]= -67,   [81]= -67,   [82]= -66,   [83]= -66,   [84]= -66,   [85]=-65 ,   [86]= -65,   [87]= -65,   [88]= -65,   [89]= -64,   [90]=-64 ,   [91]= -64,   [92]= -63,   [93]=-63 ,   [94]= -63,   [95]= -63,
    [96]= -62,   [97]= -62,   [98]= -61,   [99]= -61,   [100]= -61,  [101]= -60,  [102]= -60,  [103]= -60,  [104]= -59,  [105]= -59,  [106]= -59,  [107]= -58,  [108]= -58,  [109]= -58,  [110]= -57,  [111]= -57,
    [112]=-57,  [113]= -57,  [114]=-56 ,  [115]= -56,  [116]= -56,  [117]= -55,  [118]= -55,  [119]=-55 ,  [120]=-54 ,  [121]=-54 ,  [122]= -53,  [123]= -53,  [124]= -52,  [125]= -51,   [126]= -50,  [127]=-49 ,
};
/* exported variables --------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_reset()
{

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_force_agc_enable(bool en)
{

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint8_t rf_txpwr_dbm_get(uint8_t txpwr_idx,uint8_t modulation)
{
   return 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint32_t rf_reg_rd(uint16_t addr)
{
    return 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_reg_wr(uint16_t addr,uint32_t value)
{

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int8_t rf_rssi_convert(uint8_t rssi_reg)
{
    if(rssi_reg > 0x7f)
    {
        rssi_reg = 0x7f;
    }
    return rf_rssi_map[rssi_reg];
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_sleep()
{
    #if defined(CFG_BLE)
    ble_deepslcntl_set(ble_deepslcntl_get() |
                      BLE_DEEP_SLEEP_ON_BIT |    // RW BLE Core sleep
                      BLE_RADIO_SLEEP_EN_BIT |   // Radio sleep
                      BLE_OSC_SLEEP_EN_BIT);     // Oscillator sleep
    #endif /* end of defined(CFG_BLE) */    
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_mac_low_battery_config(void)
{
    ble_rxpwrup0_setf(0x66);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_init(struct rwip_rf_api *api)
{
    api->reg_rd = rf_reg_rd;
    api->reg_wr = rf_reg_wr;
    api->txpwr_dbm_get = rf_txpwr_dbm_get;
    api->txpwr_max = RF_POWER_MAX;
    api->sleep = rf_sleep;
    api->reset = rf_reset;
    api->force_agc_enable = rf_force_agc_enable;
    api->rssi_convert = rf_rssi_convert;
    ble_radiocntl1_pack(0,0,0,0,0,0,2,0);
    ble_radiocntl2_set(0x40);
    // 1Mbps settings
    #if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
    ble_rxpwrup0_setf(0x74);
    ble_txpwrdn0_setf(0x9);
    uint32_t reg_ro_val = sysc_awo_rf_reg_rd_get();
    switch (reg_ro_val&0x1f)
    {
    case APOLLO_00_V4A_V4AMC: // V4am
        ble_txpwrup0_setf(0x74);
        break;
    case APOLLO_00_V4B_V4BMC: // V4bm
        ble_txpwrup0_setf(0x84);
        break;
    case APOLLO_00_A01:
    case APOLLO_00_A02:
    case APOLLO_00_A03:
    case APOLLO_00_A04:
    case APOLLO_00_A05:
    case APOLLO_00_A06:
    case APOLLO_00_A07:
    case APOLLO_00_A08:
    case APOLLO_00_A09:
    case APOLLO_00_A10:
    case APOLLO_00_A11:
    case APOLLO_00_A12:
    case APOLLO_00_B1:
    case APOLLO_00_B2:
    case APOLLO_00_B3:
        ble_txpwrup0_setf(0x76); // A1
        ble_rxpwrup0_setf(RX_PWRUP0_DEFAULT_VALUE);
        break;
    default:
        ble_txpwrup0_setf(0x76);
        ble_rxpwrup0_setf(0x80);
        break;
    }

//    ble_txpwrup0_setf(0x74); ///
    ble_txpathdly0_setf(2);
    ble_rxpathdly0_setf(5);
	ble_rfrxtmda0_setf(8);
    ble_sync_position0_setf(0);
    // 2Mbps settings
    ble_rxpwrup1_setf(0x74);
    ble_txpwrdn1_setf(0x9);
    ble_txpwrup1_setf(0x74);
    ble_txpathdly1_setf(4);
    ble_rxpathdly1_setf(0);
    ble_rfrxtmda1_setf(4);
    ble_sync_position1_setf(0);
	#else
	ble_rxpwrup0_setf(0x78);
    ble_txpwrdn0_setf(0xa);
    ble_txpwrup0_setf(0x78);
    ble_txpathdly0_setf(8);
    ble_rxpathdly0_setf(5);
	ble_rfrxtmda0_setf(8);
    ble_sync_position0_setf(0);
    // 2Mbps settings
    ble_rxpwrup1_setf(0x78);
    ble_txpwrdn1_setf(0xa);
    ble_txpwrup1_setf(0x78);
    ble_txpathdly1_setf(2);
    ble_rxpathdly1_setf(9);
    ble_rfrxtmda1_setf(4);
    ble_sync_position1_setf(0);
	#endif
    // freq table programming
    int8_t *freq_table_ptr = (int8_t *)(EM_BASE_ADDR+EM_FT_OFFSET);
    uint8_t ch;
    for(ch = 0 ; ch<EM_RF_FREQ_TABLE_LEN; ++ ch)
    {
        freq_table_ptr[ch] = ch * 2;
    }
}
#elif RF_PARAM == 1 || RF_PARAM == 2 || RF_PARAM == 3
#define RF_POWER_MAX 0x06

static const int8_t rf_rssi_map[128] ={
    [0]= -100,    [1]= -99,    [2]= -98,    [3]= -98,    [4]= -97,    [5]= -97,    [6]= -96,    [7]= -96,    [8]= -95,    [9]= -95,    [10]= -94,   [11]= -94,   [12]= -94,   [13]= -93,   [14]= -93,   [15]= -93,
    [16]=-92 ,   [17]= -92,   [18]= -92,   [19]= -91,   [20]= -91,   [21]= -91,   [22]=-90,   [23]= -90,   [24]= -90,   [25]= -89 ,   [26]= -89,   [27]=-88 ,   [28]= -88,   [29]= -87,   [30]=-87 ,   [31]=-86,
    [32]= -86,   [33]=-86 ,   [34]= -85,   [35]= -85,   [36]=-84,   [37]=-84 ,   [38]= -83,   [39]= -83,   [40]=-82 ,   [41]= -82,   [42]= -82,   [43]= -81,   [44]= -81,   [45]=-80 ,   [46]= -80,   [47]= -79,
    [48]= -79,   [49]= -79,   [50]=-78 ,   [51]= -78,   [52]=-77 ,   [53]= -77,   [54]= -76,   [55]=-76 ,   [56]= -76,   [57]=-75 ,   [58]=-75 ,   [59]= -75,   [60]=-74 ,   [61]= -74,   [62]=-73 ,   [63]= -73,
    [64]= -73,   [65]=-73 ,   [66]=-72 ,   [67]= -72,   [68]=-71 ,   [69]= -71,   [70]= -71,   [71]=-70 ,   [72]= -70,   [73]= -70,   [74]=-69 ,   [75]= -69,   [76]=-68 ,   [77]= -68,   [78]= -68,   [79]= -68,
    [80]= -67,   [81]= -67,   [82]= -66,   [83]= -66,   [84]= -66,   [85]=-65 ,   [86]= -65,   [87]= -65,   [88]= -65,   [89]= -64,   [90]=-64 ,   [91]= -64,   [92]= -63,   [93]=-63 ,   [94]= -63,   [95]= -63,
    [96]= -62,   [97]= -62,   [98]= -61,   [99]= -61,   [100]= -61,  [101]= -60,  [102]= -60,  [103]= -60,  [104]= -59,  [105]= -59,  [106]= -59,  [107]= -58,  [108]= -58,  [109]= -58,  [110]= -57,  [111]= -57,
    [112]=-57,  [113]= -57,  [114]=-56 ,  [115]= -56,  [116]= -56,  [117]= -55,  [118]= -55,  [119]=-55 ,  [120]=-54 ,  [121]=-54 ,  [122]= -53,  [123]= -53,  [124]= -52,  [125]= -51,   [126]= -50,  [127]=-49 ,
};
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_reset()
{

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_force_agc_enable(bool en)
{

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint8_t rf_txpwr_dbm_get(uint8_t txpwr_idx,uint8_t modulation)
{
   return 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int8_t rf_rssi_convert(uint8_t rssi_reg)
{
    if(rssi_reg > 0x7f)
    {
        rssi_reg = 0x7f;
    }
    return rf_rssi_map[rssi_reg];
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint32_t rf_reg_rd(uint16_t addr)
{
    return 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_reg_wr(uint16_t addr,uint32_t value)
{

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_sleep()
{
    #if defined(CFG_BLE)
    ble_deepslcntl_set(ble_deepslcntl_get() |
                      BLE_DEEP_SLEEP_ON_BIT |    // RW BLE Core sleep
                      BLE_RADIO_SLEEP_EN_BIT |   // Radio sleep
                      BLE_OSC_SLEEP_EN_BIT);     // Oscillator sleep
    #endif // CFG_BLE    
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_mac_low_battery_config(void)
{
    ble_rxpwrup0_setf(0x66);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_init(struct rwip_rf_api *api)
{
    api->reg_rd = rf_reg_rd;
    api->reg_wr = rf_reg_wr;
    api->txpwr_dbm_get = rf_txpwr_dbm_get;
    api->txpwr_max = RF_POWER_MAX;
    api->sleep = rf_sleep;
    api->reset = rf_reset;
    api->force_agc_enable = rf_force_agc_enable;
    api->rssi_convert = rf_rssi_convert;
    ble_radiocntl1_pack(0,0,0,0,0,0,2,0);
    ble_radiocntl2_set(0x40);
    // 1Mbps settings
    #if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
    ble_rxpwrup0_setf(0x74);
    ble_txpwrdn0_setf(0x9);
    uint32_t reg_ro_val = sysc_awo_rf_reg_rd_get();
    switch (reg_ro_val&0x1f)
    {
    case APOLLO_00_V4A_V4AMC: // V4am
        ble_txpwrup0_setf(0x74);
        break;
    case APOLLO_00_V4B_V4BMC: // V4bm
        ble_txpwrup0_setf(0x84);
        break;
    case APOLLO_00_A01:
    case APOLLO_00_A02:
    case APOLLO_00_A03:
    case APOLLO_00_A04:
    case APOLLO_00_A05:
    case APOLLO_00_A06:
    case APOLLO_00_A07:
    case APOLLO_00_A08:
    case APOLLO_00_A09:
    case APOLLO_00_A10:
    case APOLLO_00_A11:
    case APOLLO_00_A12:
    case APOLLO_00_B1:
    case APOLLO_00_B2:
    case APOLLO_00_B3:
        ble_txpwrup0_setf(0x78); // A1
        ble_rxpwrup0_setf(RX_PWRUP0_DEFAULT_VALUE);
        break;
    default:
        ble_txpwrup0_setf(0x89);
        ble_rxpwrup0_setf(0x80);
        break;
    }

//    ble_txpwrup0_setf(0x74); ///
    ble_txpathdly0_setf(2);
    ble_rxpathdly0_setf(5);
	ble_rfrxtmda0_setf(8);
    ble_sync_position0_setf(0);
    // 2Mbps settings
    ble_rxpwrup1_setf(0x82);
    ble_txpwrdn1_setf(0x9);
    ble_txpwrup1_setf(0x82);
    ble_txpathdly1_setf(4);
    ble_rxpathdly1_setf(0);
    ble_rfrxtmda1_setf(4);
    ble_sync_position1_setf(0);
	#else 
	ble_rxpwrup0_setf(0x78);
    ble_txpwrdn0_setf(0xa);
    ble_txpwrup0_setf(0x78);
    ble_txpathdly0_setf(8);
    ble_rxpathdly0_setf(5);
	ble_rfrxtmda0_setf(8);
    ble_sync_position0_setf(0);
    // 2Mbps settings
    ble_rxpwrup1_setf(0x78);
    ble_txpwrdn1_setf(0xa);
    ble_txpwrup1_setf(0x78);
    ble_txpathdly1_setf(2);
    ble_rxpathdly1_setf(9);
    ble_rfrxtmda1_setf(4);
    ble_sync_position1_setf(0);
	#endif
    // freq table programming
    int8_t *freq_table_ptr = (int8_t *)(EM_BASE_ADDR+EM_FT_OFFSET);
    uint8_t ch;
    for(ch = 0 ; ch<EM_RF_FREQ_TABLE_LEN; ++ ch)
    {
        freq_table_ptr[ch] = ch * 2;
    }
}
#endif

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

