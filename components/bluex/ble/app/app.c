/**
 ****************************************************************************************
 *
 * @file app.c
 *
 * @brief Application entry point
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup APP
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"             // SW configuration

#if (BLE_APP_PRESENT)
#include <string.h>

#include "app_task.h"                // Application task Definition
#include "app.h"                     // Application Definition
#include "gap.h"                     // GAP Definition
#include "gapm_task.h"               // GAP Manager Task API
#include "gapc_task.h"               // GAP Controller Task API

#include "co_bt.h"                   // Common BT Definition
#include "co_math.h"                 // Common Maths Definition

#if (BLE_APP_SEC)
#include "app_sec.h"                 // Application security Definition
#endif // (BLE_APP_SEC)

#if (BLE_APP_HT)
#include "app_ht.h"                  // Health Thermometer Application Definitions
#endif //(BLE_APP_HT)


#if (BLE_APP_DIS)
#include "app_dis.h"                 // Device Information Service Application Definitions
#endif //(BLE_APP_DIS)

#if (BLE_APP_BATT)
#include "app_batt.h"                // Battery Application Definitions
#endif //(BLE_APP_DIS)

#if (BLE_APP_HID)
#include "app_hid.h"                 // HID Application Definitions
#endif //(BLE_APP_HID)

#if (DISPLAY_SUPPORT)
#include "app_display.h"             // Application Display Definition
#endif //(DISPLAY_SUPPORT)

#ifdef BLE_APP_AM0
#include "am0_app.h"                 // Audio Mode 0 Application
#endif //defined(BLE_APP_AM0)

#if (NVDS_SUPPORT)
#include "nvds.h"                    // NVDS Definitions
#endif //(NVDS_SUPPORT)

#include "bx_kernel.h"
#include "ke_timer.h"
#include "bx_shell.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// Default Device Name if no value can be found in NVDS
#define APP_DFLT_DEVICE_NAME            ("RW-BLE-DEV")
#define APP_DFLT_DEVICE_NAME_LEN        (sizeof(APP_DFLT_DEVICE_NAME))


#if (BLE_APP_HID)
// HID Mouse
#define DEVICE_NAME        "Hid Mouse"
#else
#define DEVICE_NAME        "RW DEVICE"
#endif

#define DEVICE_NAME_SIZE    sizeof(DEVICE_NAME)

/**
 * UUID List part of ADV Data
 * --------------------------------------------------------------------------------------
 * x03 - Length
 * x03 - Complete list of 16-bit UUIDs available
 * x09\x18 - Health Thermometer Service UUID
 *   or
 * x12\x18 - HID Service UUID
 * --------------------------------------------------------------------------------------
 */

#if (BLE_APP_HT)
#define APP_HT_ADV_DATA_UUID        "\x03\x03\x09\x18"
#define APP_HT_ADV_DATA_UUID_LEN    (4)
#endif //(BLE_APP_HT)

#if (BLE_APP_HID)
#define APP_HID_ADV_DATA_UUID       "\x03\x03\x12\x18"
#define APP_HID_ADV_DATA_UUID_LEN   (4)
#endif //(BLE_APP_HID)

/**
 * Appearance part of ADV Data
 * --------------------------------------------------------------------------------------
 * x03 - Length
 * x19 - Appearance
 * x03\x00 - Generic Thermometer
 *   or
 * xC2\x04 - HID Mouse
 * --------------------------------------------------------------------------------------
 */

#if (BLE_APP_HT)
#define APP_HT_ADV_DATA_APPEARANCE    "\x03\x19\x00\x03"
#endif //(BLE_APP_HT)

#if (BLE_APP_HID)
#define APP_HID_ADV_DATA_APPEARANCE   "\x03\x19\xC2\x03"
#endif //(BLE_APP_HID)

#define APP_ADV_DATA_APPEARANCE_LEN  (4)

/**
 * Default Scan response data
 * --------------------------------------------------------------------------------------
 * x09                             - Length
 * xFF                             - Vendor specific advertising type
 * x00\x60\x52\x57\x2D\x42\x4C\x45 - "RW-BLE"
 * --------------------------------------------------------------------------------------
 */
#define APP_SCNRSP_DATA         "\x09\xFF\x00\x60\x52\x57\x2D\x42\x4C\x45"
#define APP_SCNRSP_DATA_LEN     (10)

/**
 * Advertising Parameters
 */
#if (BLE_APP_HID)
/// Default Advertising duration - 30s (in multiple of 10ms)
#define APP_DFLT_ADV_DURATION   (3000)
#endif //(BLE_APP_HID)
/// Advertising channel map - 37, 38, 39
#define APP_ADV_CHMAP           (0x07)
/// Advertising minimum interval - 40ms (64*0.625ms)
#define APP_ADV_INT_MIN         (64)
/// Advertising maximum interval - 40ms (64*0.625ms)
#define APP_ADV_INT_MAX         (64)
/// Fast advertising interval
#define APP_ADV_FAST_INT        (32)

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef void (*appm_add_svc_func_t)(void);

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/// List of service to add in the database
enum appm_svc_list
{
    #if (BLE_APP_HT)
    APPM_SVC_HTS,
    #endif //(BLE_APP_HT)
    #if (BLE_APP_DIS)
    APPM_SVC_DIS,
    #endif //(BLE_APP_DIS)
    #if (BLE_APP_BATT)
    APPM_SVC_BATT,
    #endif //(BLE_APP_BATT)
    #if (BLE_APP_HID)
    APPM_SVC_HIDS,
    #endif //(BLE_APP_HID)
    #ifdef BLE_APP_AM0
    APPM_SVC_AM0_HAS,
    #endif //defined(BLE_APP_AM0)
    BXOTAS,
    USER_SVC,
    APPM_SVC_LIST_STOP,
};

/*
 * LOCAL VARIABLES DEFINITIONS
 ****************************************************************************************
 */

/// Application Task Descriptor
static const struct ke_task_desc TASK_DESC_APP = {NULL, &appm_default_handler,
                                                  appm_state, APPM_STATE_MAX, APP_IDX_MAX};

/// List of functions used to create the database
static const appm_add_svc_func_t appm_add_svc_func_list[APPM_SVC_LIST_STOP] =
{
    #if (BLE_APP_HT)
    (appm_add_svc_func_t)app_ht_add_hts,
    #endif //(BLE_APP_HT)
    #if (BLE_APP_DIS)
    (appm_add_svc_func_t)app_dis_add_dis,
    #endif //(BLE_APP_DIS)
    #if (BLE_APP_BATT)
    (appm_add_svc_func_t)app_batt_add_bas,
    #endif //(BLE_APP_BATT)
    #if (BLE_APP_HID)
    (appm_add_svc_func_t)app_hid_add_hids,
    #endif //(BLE_APP_HID)
    #ifdef BLE_APP_AM0
    (appm_add_svc_func_t)am0_app_add_has,
    #endif //defined(BLE_APP_AM0)
    (appm_add_svc_func_t)app_bxotas,
    (appm_add_svc_func_t)app_user_add_profile,
};

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Application Environment Structure
struct app_env_tag app_env;

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void appm_init()
{
    #if (NVDS_SUPPORT)
    uint8_t key_len = KEY_LEN;
    #endif //(NVDS_SUPPORT)

    // Reset the application manager environment
    memset(&app_env, 0, sizeof(app_env));

    // Create APP task
    ke_task_create(TASK_APP, &TASK_DESC_APP);

    // Initialize Task state
    ke_state_set(TASK_APP, APPM_INIT);

    // Load the device name from NVDS

    // Get the Device Name to add in the Advertising Data (Default one or NVDS one)
    #if (NVDS_SUPPORT)
    app_env.dev_name_len = APP_DEVICE_NAME_MAX_LEN;
    if (nvds_get(NVDS_TAG_DEVICE_NAME, &(app_env.dev_name_len), app_env.dev_name) != NVDS_OK)
    #endif //(NVDS_SUPPORT)
    {
        // Get default Device Name (No name if not enough space)
        memcpy(app_env.dev_name, APP_DFLT_DEVICE_NAME, APP_DFLT_DEVICE_NAME_LEN);
        app_env.dev_name_len = APP_DFLT_DEVICE_NAME_LEN;

        // TODO update this value per profiles
    }
    
    #if (NVDS_SUPPORT)
    if ((nvds_get(NVDS_TAG_LOC_IRK, &key_len, app_env.loc_irk) != NVDS_OK) )
    #endif //(NVDS_SUPPORT)
    {
        uint8_t counter;

        // generate a new IRK
        for (counter = 0; counter < KEY_LEN; counter++)
        {
            app_env.loc_irk[counter]    = (uint8_t)co_rand_word();
        }

        // Store it in NVDS
        #if (NVDS_SUPPORT)
        // Store the generated value in NVDS
        if (nvds_put(NVDS_TAG_LOC_IRK, KEY_LEN, (uint8_t *)&app_env.loc_irk) != NVDS_OK)
        {
            ASSERT_INFO(0, NVDS_TAG_LOC_IRK, 0);
        }
        #endif // #if (NVDS_SUPPORT)
    }

    /*------------------------------------------------------
     * INITIALIZE ALL MODULES
     *------------------------------------------------------*/

    // load device information:

    #if (DISPLAY_SUPPORT)
    app_display_init();
    #endif //(DISPLAY_SUPPORT)

    #if (BLE_APP_SEC)
    // Security Module
    app_sec_init();
    #endif // (BLE_APP_SEC)

    #if (BLE_APP_HT)
    // Health Thermometer Module
    app_ht_init();
    #endif //(BLE_APP_HT)

    #if (BLE_APP_DIS)
    // Device Information Module
    app_dis_init();
    #endif //(BLE_APP_DIS)

    #if (BLE_APP_HID)
    // HID Module
    app_hid_init();
    #endif //(BLE_APP_HID)

    #if (BLE_APP_BATT)
    // Battery Module
    app_batt_init();
    #endif //(BLE_APP_BATT)

    #ifdef BLE_APP_AM0
    // Audio Mode 0 Module
    am0_app_init();
    #endif // defined(BLE_APP_AM0)
}

bool appm_add_svc(void)
{
    // Indicate if more services need to be added in the database
    bool more_svc = false;

    // Check if another should be added in the database
    if (app_env.next_svc != APPM_SVC_LIST_STOP)
    {
        ASSERT_INFO(appm_add_svc_func_list[app_env.next_svc] != NULL, app_env.next_svc, 1);

        // Call the function used to add the required service
        appm_add_svc_func_list[app_env.next_svc]();

        // Select following service to add
        app_env.next_svc++;
        more_svc = true;
    }

    return more_svc;
}

void appm_disconnect(void)
{
    struct gapc_disconnect_cmd *cmd = KE_MSG_ALLOC(GAPC_DISCONNECT_CMD,
                                                   KE_BUILD_ID(TASK_GAPC, app_env.conidx), TASK_APP,
                                                   gapc_disconnect_cmd);

    cmd->operation = GAPC_DISCONNECT;
    cmd->reason    = CO_ERROR_REMOTE_USER_TERM_CON;

    // Send the message
    ke_msg_send(cmd);
}

/**
 ****************************************************************************************
 * Advertising Functions
 ****************************************************************************************
 */

void appm_start_advertising(void)
{
    // Check if the advertising procedure is already is progress
    if (ke_state_get(TASK_APP) == APPM_READY)
    {
        #if defined(BLE_APP_AM0)
        am0_app_start_advertising();
        #else
        // Prepare the GAPM_START_ADVERTISE_CMD message
        struct gapm_start_advertise_cmd *cmd = KE_MSG_ALLOC(GAPM_START_ADVERTISE_CMD,
                                                            TASK_GAPM, TASK_APP,
                                                            gapm_start_advertise_cmd);

        cmd->op.addr_src    = GAPM_STATIC_ADDR;
        cmd->channel_map    = APP_ADV_CHMAP;

        #if (BLE_APP_HID)
        /*
         * If the peripheral is already bonded with a central device, use the direct advertising
         * procedure (BD Address of the peer device is stored in NVDS.
         */
        if (app_sec_get_bond_status())
        {
//            // BD Address of the peer device
//            struct gap_bdaddr peer_bd_addr;
//            // Length
//            uint8_t length = NVDS_LEN_PEER_BD_ADDRESS;
//
//            // Get the BD Address of the peer device in NVDS
//            if (nvds_get(NVDS_TAG_PEER_BD_ADDRESS, &length, (uint8_t *)&peer_bd_addr) != NVDS_OK)
//            {
//                // The address of the bonded peer device should be present in the database
//                ASSERT_ERR(0);
//            }
//
//            // Set the DIRECT ADVERTISING mode
//            cmd->op.code = GAPM_ADV_DIRECT;
//            // Copy the BD address of the peer device and the type of address
//            memcpy(&cmd->info.direct, &peer_bd_addr, NVDS_LEN_PEER_BD_ADDRESS);

            cmd->intv_min = APP_ADV_FAST_INT;
            cmd->intv_max = APP_ADV_FAST_INT;
        }
        else
        {
            cmd->intv_min = APP_ADV_INT_MIN;
            cmd->intv_max = APP_ADV_INT_MAX;
        }

        #else //(BLE_APP_HID)
        cmd->intv_min = APP_ADV_INT_MIN;
        cmd->intv_max = APP_ADV_INT_MAX;
        #endif //(BLE_APP_HID)
        {

            cmd->op.code        = GAPM_ADV_UNDIRECT;
        #if (BLE_APP_HID)
            cmd->info.host.mode = GAP_LIM_DISCOVERABLE;
        #else //(BLE_APP_HID)
            cmd->info.host.mode = GAP_GEN_DISCOVERABLE;
        #endif //(BLE_APP_HID)

            /*-----------------------------------------------------------------------------------
             * Set the Advertising Data and the Scan Response Data
             *---------------------------------------------------------------------------------*/
            // Flag value is set by the GAP
            cmd->info.host.adv_data_len       = ADV_DATA_LEN - 3;
            cmd->info.host.scan_rsp_data_len  = SCAN_RSP_DATA_LEN;

            // Advertising Data
            #if (NVDS_SUPPORT)
            if(nvds_get(NVDS_TAG_APP_BLE_ADV_DATA, &cmd->info.host.adv_data_len,
                        &cmd->info.host.adv_data[0]) != NVDS_OK)
            #endif //(NVDS_SUPPORT)
            {
                cmd->info.host.adv_data_len = 0;

                //Add list of UUID and appearance
                #if (BLE_APP_HT)
                memcpy(&cmd->info.host.adv_data[cmd->info.host.adv_data_len],
                       APP_HT_ADV_DATA_UUID, APP_HT_ADV_DATA_UUID_LEN);
                cmd->info.host.adv_data_len += APP_HT_ADV_DATA_UUID_LEN;
                memcpy(&cmd->info.host.adv_data[cmd->info.host.adv_data_len],
                       APP_HT_ADV_DATA_APPEARANCE, APP_ADV_DATA_APPEARANCE_LEN);
                cmd->info.host.adv_data_len += APP_ADV_DATA_APPEARANCE_LEN;
                #endif //(BLE_APP_HT)

                #if (BLE_APP_HID)
                memcpy(&cmd->info.host.adv_data[cmd->info.host.adv_data_len],
                       APP_HID_ADV_DATA_UUID, APP_HID_ADV_DATA_UUID_LEN);
                cmd->info.host.adv_data_len += APP_HID_ADV_DATA_UUID_LEN;
                memcpy(&cmd->info.host.adv_data[cmd->info.host.adv_data_len],
                       APP_HID_ADV_DATA_APPEARANCE, APP_ADV_DATA_APPEARANCE_LEN);
                cmd->info.host.adv_data_len += APP_ADV_DATA_APPEARANCE_LEN;
                #endif //(BLE_APP_HID)
            }

            // Scan Response Data
            #if (NVDS_SUPPORT)
            if(nvds_get(NVDS_TAG_APP_BLE_SCAN_RESP_DATA, &cmd->info.host.scan_rsp_data_len,
                        &cmd->info.host.scan_rsp_data[0]) != NVDS_OK)
            #endif //(NVDS_SUPPORT)
            {
                cmd->info.host.scan_rsp_data_len = 0;
                
                // factory id 
                #define FACTORY_ID      "BX"
                #define FACTORY_ID_LEN  2
                
                #define MAC_BASE_ADDR   0x802000
                #define MAX_ADDR_LEN    6
                
                #define LINK_NAME       "BXL"
                #define LINK_NAME_LEN   3
                
                #define DEVICE_TYPE     "\x00"
                #define DEVICE_TYPE_LEN 1
                
                #define DEVICE_ADDR     "\x00\x01"
                #define DEVICE_ADDR_LEN 2
                
                uint8_t mac_addr[6];
                for( uint32_t i=0;i<6;i++ ){
                    mac_addr[i] = *(uint8_t *)(MAC_BASE_ADDR+5-i);
                    //bxsh_log("%02x ",mac_addr[5-i]);
                }
                //bxsh_log("\r\n");
                
                memcpy(&cmd->info.host.scan_rsp_data[cmd->info.host.scan_rsp_data_len],
                       FACTORY_ID, FACTORY_ID_LEN);
                cmd->info.host.scan_rsp_data_len += FACTORY_ID_LEN;
                
                memcpy(&cmd->info.host.scan_rsp_data[cmd->info.host.scan_rsp_data_len],
                       mac_addr, 6);
                cmd->info.host.scan_rsp_data_len += 6;
                
                memcpy(&cmd->info.host.scan_rsp_data[cmd->info.host.scan_rsp_data_len],
                       LINK_NAME, LINK_NAME_LEN);
                cmd->info.host.scan_rsp_data_len += LINK_NAME_LEN;
                
                memcpy(&cmd->info.host.scan_rsp_data[cmd->info.host.scan_rsp_data_len],
                       DEVICE_TYPE, DEVICE_TYPE_LEN);
                cmd->info.host.scan_rsp_data_len += DEVICE_TYPE_LEN;
                
                memcpy(&cmd->info.host.scan_rsp_data[cmd->info.host.scan_rsp_data_len],
                       DEVICE_ADDR, DEVICE_ADDR_LEN);
                cmd->info.host.scan_rsp_data_len += DEVICE_ADDR_LEN;
                
//                for( uint32_t i=0;i<cmd->info.host.scan_rsp_data_len;i++ ){
//                    bxsh_log("%02x ",cmd->info.host.scan_rsp_data[i]);
//                }
//                bxsh_log("\r\n");
                
                memmove(&cmd->info.host.scan_rsp_data[2],&cmd->info.host.scan_rsp_data[0],cmd->info.host.scan_rsp_data_len);
                cmd->info.host.scan_rsp_data[0] = cmd->info.host.scan_rsp_data_len+1;
                cmd->info.host.scan_rsp_data[1] = 0xFF;
                cmd->info.host.scan_rsp_data_len +=2;
                
//                for( uint32_t i=0;i<cmd->info.host.scan_rsp_data_len;i++ ){
//                    bxsh_log("%02x ",cmd->info.host.scan_rsp_data[i]);
//                }
//                bxsh_log("\r\n");
            }


            //  Device Name Length
            uint8_t avail_space;

            // Get remaining space in the Advertising Data - 2 bytes are used for name length/flag
            avail_space = (ADV_DATA_LEN - 3) - cmd->info.host.adv_data_len - 2;

            // Check if data can be added to the Advertising data
            if (avail_space > 2)
            {
                avail_space = co_min(avail_space, app_env.dev_name_len);

                cmd->info.host.adv_data[cmd->info.host.adv_data_len]     = avail_space + 1;
                // Fill Device Name Flag
                cmd->info.host.adv_data[cmd->info.host.adv_data_len + 1] = (avail_space == app_env.dev_name_len) ? '\x08' : '\x09';
                // Copy device name
                memcpy(&cmd->info.host.adv_data[cmd->info.host.adv_data_len + 2], app_env.dev_name, avail_space);

                // Update Advertising Data Length
                cmd->info.host.adv_data_len += (avail_space + 2);
            }
        }

        // Send the message
        ke_msg_send(cmd);

        #if (BLE_APP_HID)
        // At this point, timeout timer is not active
        ASSERT_INFO(!ke_timer_active(APP_ADV_TIMEOUT_TIMER, TASK_APP), APP_ADV_TIMEOUT_TIMER, 2);

        // Start the advertising timer
        ke_timer_set(APP_ADV_TIMEOUT_TIMER, TASK_APP, (uint16_t)APP_DFLT_ADV_DURATION);
        #endif //(BLE_APP_HID)
        #endif // defined(BLE_APP_AM0)
        #if (DISPLAY_SUPPORT)
        // Update advertising state screen
        app_display_set_adv(true);
        #endif //(DISPLAY_SUPPORT)

        // Set the state of the task to APPM_ADVERTISING
        ke_state_set(TASK_APP, APPM_ADVERTISING);
    }
    // else ignore the request
}

void appm_stop_advertising(void)
{
    if (ke_state_get(TASK_APP) == APPM_ADVERTISING)
    {
        #if (BLE_APP_HID)
        // Stop the advertising timer if needed
        if (ke_timer_active(APP_ADV_TIMEOUT_TIMER, TASK_APP))
        {
            ke_timer_clear(APP_ADV_TIMEOUT_TIMER, TASK_APP);
        }
        #endif //(BLE_APP_HID)


        // Go in ready state
        ke_state_set(TASK_APP, APPM_READY);

        // Prepare the GAPM_CANCEL_CMD message
        struct gapm_cancel_cmd *cmd = KE_MSG_ALLOC(GAPM_CANCEL_CMD,
                                                   TASK_GAPM, TASK_APP,
                                                   gapm_cancel_cmd);

        cmd->operation = GAPM_CANCEL;

        // Send the message
        ke_msg_send(cmd);

        #if (DISPLAY_SUPPORT)
        // Update advertising state screen
        app_display_set_adv(false);
        #endif //(DISPLAY_SUPPORT)
    }
    // else ignore the request
}

void appm_update_param(struct gapc_conn_param *conn_param)
{
    // Prepare the GAPC_PARAM_UPDATE_CMD message
    struct gapc_param_update_cmd *cmd = KE_MSG_ALLOC(GAPC_PARAM_UPDATE_CMD,
                                                     KE_BUILD_ID(TASK_GAPC, app_env.conidx), TASK_APP,
                                                     gapc_param_update_cmd);

    cmd->operation  = GAPC_UPDATE_PARAMS;
    cmd->intv_min   = conn_param->intv_min;
    cmd->intv_max   = conn_param->intv_max;
    cmd->latency    = conn_param->latency;
    cmd->time_out   = conn_param->time_out;

    // not used by a slave device
    cmd->ce_len_min = 0xFFFF;
    cmd->ce_len_max = 0xFFFF;

    // Send the message
    ke_msg_send(cmd);
}

uint8_t appm_get_dev_name(uint8_t* name)
{
    // copy name to provided pointer
    memcpy(name, app_env.dev_name, app_env.dev_name_len);
    // return name length
    return app_env.dev_name_len;
}
#endif //(BLE_APP_PRESENT)

/// @} APP
