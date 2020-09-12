/**
 ****************************************************************************************
 *
 * @file app_dis.h
 *
 * @brief Device Information Application Module Entry point
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef APP_DIS_H_
#define APP_DIS_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 *
 * @brief Device Information Application Module Entry point.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW Configuration

#if (BLE_APP_DIS)

#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/// Manufacturer Name Value
//#define APP_DIS_MANUFACTURER_NAME       ("Homeylab.us")
//#define APP_DIS_MANUFACTURER_NAME_LEN   (11)

#define APP_DIS_MANUFACTURER_NAME       ("BLUEX-SDK3")
#define APP_DIS_MANUFACTURER_NAME_LEN   (sizeof(APP_DIS_MANUFACTURER_NAME) - 1)
    
/// Model Number String Value
#define APP_DIS_MODEL_NB_STR            ("RW-BLE-1.0")
#define APP_DIS_MODEL_NB_STR_LEN        (10)

/// Serial Number
#define APP_DIS_SERIAL_NB_STR           ("BLE-NEW-1001")
#define APP_DIS_SERIAL_NB_STR_LEN       (11)

/// Firmware Revision
#define APP_DIS_FIRM_REV_STR            ("CKF")
#define APP_DIS_FIRM_REV_STR_LEN        (3)

/// System ID Value - LSB -> MSB
#define APP_DIS_SYSTEM_ID               ("\x12\x34\x56\xFF\xFE\x9A\xBC\xDE")
#define APP_DIS_SYSTEM_ID_LEN           (8)

/// Hardware Revision String
#define APP_DIS_HARD_REV_STR            ("CKF10")
#define APP_DIS_HARD_REV_STR_LEN        (5)

/// Software Revision String
#define APP_DIS_SW_REV_STR              ("FWV 2.0.0.2")
#define APP_DIS_SW_REV_STR_LEN          (11)

/// IEEE
#define APP_DIS_IEEE                    ("\xFF\xEE\xDD\xCC\xBB\xAA")
#define APP_DIS_IEEE_LEN                (6)

/**
 * PNP ID Value - LSB -> MSB
 *      Vendor ID Source : 0x02 (USB Implementer’s Forum assigned Vendor ID value)
 *      Vendor ID : 0x045E      (Microsoft Corp)
 *      Product ID : 0x0040
 *      Product Version : 0x0300
 */
#define APP_DIS_PNP_ID               ("\x02\x5E\x04\x40\x00\x00\x03")
#define APP_DIS_PNP_ID_LEN           (7)

#if (BLE_APP_HID)
#define APP_DIS_FEATURES             (DIS_MANUFACTURER_NAME_CHAR_SUP |\
                                      DIS_MODEL_NB_STR_CHAR_SUP      |\
                                      DIS_SYSTEM_ID_CHAR_SUP         |\
                                      DIS_PNP_ID_CHAR_SUP)
#else
#define APP_DIS_FEATURES             (DIS_ALL_FEAT_SUP)
#endif //(BLE_APP_HID)


/*
 * GLOBAL VARIABLES DECLARATION
 ****************************************************************************************
 */

/// Table of message handlers
extern const struct ke_state_handler app_dis_table_handler;
/*
 * GLOBAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize Device Information Service Application
 ****************************************************************************************
 */
void app_dis_init(void);

/**
 ****************************************************************************************
 * @brief Add a Device Information Service instance in the DB
 ****************************************************************************************
 */
void add_dis_profile(void);
void add_user_profile(void);
void add_bxota_profile(void);
void app_bxotas(void);
void osapp_bxotas_config(void);
void app_user_add_glps(void);

void app_user_add_bass(void);
void app_user_batt_send_lvl(uint8_t lvl);

/**
 ****************************************************************************************
 * @brief Enable the Device Information Service
 ****************************************************************************************
 */
void app_dis_enable_prf(uint16_t conhdl);

#endif //BLE_APP_DIS

/// @} APP

#endif //APP_DIS_H_
