#ifndef NVDS_TYPEDEF_H_
#define NVDS_TYPEDEF_H_
#include <stdbool.h>   
#include <stdint.h>


/*
 * DEFINES
 ****************************************************************************************
 */

/// NVDS is defined as read-write
#define NVDS_READ_WRITE          1

/// NVDS is defined as packed
#define NVDS_PACKED              1

/// NVDS has 8-bit length tags
#define NVDS_8BIT_TAGLENGTH      1

/// Type of the tag length (8 or 16 bits)
#if (NVDS_8BIT_TAGLENGTH)
typedef uint8_t  nvds_tag_len_t;
#else
typedef uint16_t nvds_tag_len_t;
#endif // NVDS_8BIT_TAGLENGTH


/*
 * ENUMERATION DEFINITIONS
 ****************************************************************************************
 */

/// Possible Returned Status
enum NVDS_STATUS
{
    /// NVDS status OK
    NVDS_OK,
    /// generic NVDS status KO
    NVDS_FAIL,
    /// NVDS TAG unrecognized
    NVDS_TAG_NOT_DEFINED,
    /// No space for NVDS
    NVDS_NO_SPACE_AVAILABLE,
    /// Length violation
    NVDS_LENGTH_OUT_OF_RANGE,
    /// NVDS parameter locked
    NVDS_PARAM_LOCKED,
    /// NVDS corrupted
    NVDS_CORRUPT
};

/// List of NVDS TAG identifiers
enum NVDS_TAG
{
    /// Definition of the tag associated to each parameters
    /// Local Bd Address
    NVDS_TAG_BD_ADDRESS                 = 0x01,
    /// Device Name
    NVDS_TAG_DEVICE_NAME                = 0x02,
    /// Enable sleep mode
    NVDS_TAG_SLEEP_ENABLE               = 0x03,
    /// External wake-up time
    NVDS_TAG_EXT_WAKEUP_TIME            = 0x04,
    /// Oscillator wake-up time
    NVDS_TAG_OSC_WAKEUP_TIME            = 0x05,
    /// Radio wake-up time
    NVDS_TAG_RM_WAKEUP_TIME             = 0x06,
    /// Radio Drift
    NVDS_TAG_LPCLK_DRIFT                = 0x07,

    /// Enable External Wakeup
    NVDS_TAG_EXT_WAKEUP_ENABLE          = 0x08,
    /// Sleep algorithm duration
    NVDS_TAG_SLEEP_ALGO_DUR             = 0x09,

    /// Static Device Address
    NVDS_TAG_STATIC_DEV_ADDR            = 0x0a,

    NVDS_TAG_LOCAL_IRK                  = 0x0b,

    NVDS_TAG_BOND_DEV_INFO_START        = 0x10,
    NVDS_TAG_BOND_DEV_INFO_END          = 0x3f,

    /// BLE Channel Assessment tags
    NVDS_TAG_BLE_CA_TIMER_DUR           = 0x40,
    NVDS_TAG_BLE_CRA_TIMER_CNT          = 0x41,
    NVDS_TAG_BLE_CA_MIN_THR             = 0x42,
    NVDS_TAG_BLE_CA_MAX_THR             = 0x43,
    NVDS_TAG_BLE_CA_NOISE_THR           = 0x44,

    NVDS_TAG_BOND_GATT_DB_START         = 0x50,
    NVDS_TAG_BOND_GATT_DB_END           = 0x7f,

    /// SP Private Key (Low Energy)
    NVDS_TAG_LE_PRIVATE_KEY_P256        = 0x80,
    /// SP Public Key (Low Energy)
    NVDS_TAG_LE_PUBLIC_KEY_P256         = 0x81,
    /// SP Debug: Used Fixed Private Key from NVDS (Low Energy)
    NVDS_TAG_LE_DBG_FIXED_P256_KEY_EN   = 0x82,

    ///Bond save age buff to remove oldest item in central role
    NVDS_TAG_BOND_SAVE_AGE              = 0x90,
    ///Bond save database usage summary
    NVDS_TAG_BOND_SAVE_DB_TAG_USED      = 0x91,

    NVDS_TAG_DIAG_BLE_HW                = 0x9f,
    
    /// Application specific
    NVDS_TAG_APP_SPECIFIC_FIRST         = 0xa0,
    NVDS_TAG_SAVE_AUTH_VAL          = 0xa0,
    NVDS_TAG_SAVE_BEACON_UUID       = 0xa1,
    NVDS_TAG_APP_SPECIFIC_LAST          = 0xef,
};

/// List of NVDS Tag lengths
enum NVDS_LEN
{
     // Definition of length associated to each parameters
     /// Local Bd Address
     NVDS_LEN_BD_ADDRESS                 = 6,
     /// Device Name
     NVDS_LEN_DEVICE_NAME                = 248,
     /// Low power clock drift
     NVDS_LEN_LPCLK_DRIFT                = 2,
     /// Low power clock jitter
     NVDS_LEN_LPCLK_JITTER               = 1,
     /// Radio Class
     NVDS_LEN_RADIO_CLASS                = 1,
     /// Bluejay specific Settings
     NVDS_LEN_BJ_TXCNTL1                 = 4,


     /// External wake-up time
     NVDS_LEN_EXT_WAKEUP_TIME            = 2,
     /// Oscillator wake-up time
     NVDS_LEN_OSC_WAKEUP_TIME            = 2,
     /// Radio wake-up time
     NVDS_LEN_RM_WAKEUP_TIME             = 2,
     /// UART baudrate
     NVDS_LEN_UART_BAUDRATE              = 4,
     /// Enable sleep mode
     NVDS_LEN_SLEEP_ENABLE               = 1,
     /// Enable External Wakeup
     NVDS_LEN_EXT_WAKEUP_ENABLE          = 1,
     /// SP Private Key 192
     NVDS_LEN_SP_PRIVATE_KEY_P192        = 24,
     /// SP Public Key 192
     NVDS_LEN_SP_PUBLIC_KEY_P192         = 48,
     /// Errata adopted check
     NVDS_LEN_ERRATA_ADOPTED             = 1,
     /// CQDDR Tags
     NVDS_LEN_BASIC_THRESHOLD            = 70,
     NVDS_LEN_EDR_THRESHOLD              = 70,
     NVDS_LEN_BASIC_ALGORITHM            = 21,
     NVDS_LEN_EDR_ALGORITHM              = 21,
     NVDS_LEN_BASIC_PACKET_LUT           = 16,
     NVDS_LEN_EDR_PACKET_LUT             = 16,
     NVDS_LEN_AUTH_VAL                   = 16,
     NVDS_LEN_BEACON_UUID                = 16,
     /// Synchronous links configuration
     NVDS_LEN_SYNC_CONFIG                = 2,
     /// PCM Settings
     NVDS_LEN_PCM_SETTINGS               = 8,
     /// Sleep algorithm duration
     NVDS_LEN_SLEEP_ALGO_DUR             = 2,
     /// Diagport configuration
     NVDS_LEN_DIAG_BT_HW                 = 4,
     NVDS_LEN_DIAG_BLE_HW                = 4,
     NVDS_LEN_DIAG_SW                    = 4,
     NVDS_LEN_DIAG_PLF                   = 4,
	 /// RSSI thresholds
	 NVDS_LEN_RSSI_THR                   = 1,


     NVDS_LEN_BLE_CA_TIMER_DUR           = 2,
     NVDS_LEN_BLE_CRA_TIMER_CNT          = 1,
     NVDS_LEN_BLE_CA_MIN_THR             = 1,
     NVDS_LEN_BLE_CA_MAX_THR             = 1,
     NVDS_LEN_BLE_CA_NOISE_THR           = 1,

     /// AFH algorithm tags
     NVDS_LEN_AFH_REASS_NBCH             = 1,
     NVDS_LEN_AFH_WINLGTH                = 1,
     NVDS_LEN_AFH_RSSIMIN                = 1,
     NVDS_LEN_AFH_PERTHRESBAD            = 1,
     NVDS_LEN_AFH_REASS_INT              = 1,
     NVDS_LEN_AFH_NMIN                   = 1,
     NVDS_LEN_AFH_MAXADAPT               = 1,
     NVDS_LEN_AFH_THSMIN                 = 1,
     /// Link keys
     NVDS_LEN_BT_LINK_KEY                = 22,
     NVDS_LEN_BLE_LINK_KEY               = 48,

     /// P256
     NVDS_LEN_LE_PRIVATE_KEY_P256        = 32,
     NVDS_LEN_LE_PUBLIC_KEY_P256         = 64,
     NVDS_LEN_LE_DBG_FIXED_P256_KEY_EN   = 1,
     NVDS_LEN_SP_PRIVATE_KEY_P256        = 32,
     NVDS_LEN_SP_PUBLIC_KEY_P256         = 64,
     
};

#endif

