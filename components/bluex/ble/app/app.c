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


#include <string.h>
#include "app_task.h"                // Application task Definition
#include "app.h"                     // Application Definition
#include "gap.h"                     // GAP Definition
#include "gapm_task.h"               // GAP Manager Task API
#include "gapc_task.h"               // GAP Controller Task API
#include "co_bt.h"                   // Common BT Definition
#include "co_math.h"                 // Common Maths Definition

#include "app_dis.h"                 // Device Information Service Application Definitions

#include "nvds.h"                    // NVDS Definitions

#include "bx_kernel.h"
#include "ke_timer.h"
#include "bx_shell.h"

#include "bx_service_ble.h"
/*
 * DEFINES
 ****************************************************************************************
 */
#define APP_ADV_CHMAP           (0x07)
/// Advertising minimum interval - 40ms (64*0.625ms)
#define APP_ADV_INT_MIN         (64)
/// Advertising maximum interval - 40ms (64*0.625ms)
#define APP_ADV_INT_MAX         (64)

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
    APPM_SVC_DIS,
    BXOTAS,
    USER_SVC,
    APPM_SVC_LIST_STOP,
};

/*
 * LOCAL VARIABLES DEFINITIONS
 ****************************************************************************************
 */

static const struct ke_task_desc TASK_DESC_APP = {NULL, &appm_default_handler,appm_state, APPM_STATE_MAX, APP_IDX_MAX};

static const appm_add_svc_func_t appm_add_svc_func_list[APPM_SVC_LIST_STOP] =
{
    (appm_add_svc_func_t)app_dis_add_dis,
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

    // Reset the application manager environment
    memset(&app_env, 0, sizeof(app_env));

    ke_task_create(TASK_APP, &TASK_DESC_APP);
    ke_state_set(TASK_APP, APPM_INIT);

    app_env.dev_name_len = APP_DEVICE_NAME_MAX_LEN;
    
    memcpy(app_env.dev_name,"SDK3",4);
    app_env.dev_name_len= strlen("SDK3");
    
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
    if (ke_state_get(TASK_APP) != APPM_READY) {
        return;
    }

    // Prepare the GAPM_START_ADVERTISE_CMD message
    struct gapm_start_advertise_cmd *cmd = KE_MSG_ALLOC(GAPM_START_ADVERTISE_CMD,
                                                        TASK_GAPM, TASK_APP,
                                                        gapm_start_advertise_cmd);

    cmd->op.addr_src    = GAPM_STATIC_ADDR;
    cmd->channel_map    = APP_ADV_CHMAP;

    cmd->intv_min = APP_ADV_INT_MIN;
    cmd->intv_max = APP_ADV_INT_MAX;

    cmd->op.code        = GAPM_ADV_UNDIRECT;
    cmd->info.host.mode = GAP_GEN_DISCOVERABLE;


    /*-----------------------------------------------------------------------------------
     * Set the Advertising Data and the Scan Response Data
     *---------------------------------------------------------------------------------*/
    // Flag value is set by the GAP
    cmd->info.host.adv_data_len       = 0;
    cmd->info.host.scan_rsp_data_len  = 0;

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
        
        for( uint32_t i=0;i<cmd->info.host.adv_data_len;i++ ){
            bxsh_log("%02x ",cmd->info.host.adv_data[i]);
        }
        bxsh_log("\r\n");
    }
    
    ke_msg_send(cmd);
    
    ke_state_set(TASK_APP, APPM_ADVERTISING);
    
    bx_public( bxs_ble_id(),BXM_BLE_ADVERTISING,0,0 );
}

void appm_stop_advertising(void)
{
    if (ke_state_get(TASK_APP) == APPM_ADVERTISING)
    {
        ke_state_set(TASK_APP, APPM_READY);
        struct gapm_cancel_cmd *cmd = KE_MSG_ALLOC(GAPM_CANCEL_CMD,
                                                   TASK_GAPM, TASK_APP,
                                                   gapm_cancel_cmd);
        cmd->operation = GAPM_CANCEL;
        ke_msg_send(cmd);
    }
}


uint8_t appm_get_dev_name(uint8_t* name)
{
    // copy name to provided pointer
    memcpy(name, app_env.dev_name, app_env.dev_name_len);
    // return name length
    return app_env.dev_name_len;
}

