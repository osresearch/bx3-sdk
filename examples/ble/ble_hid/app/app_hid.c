/**
 ****************************************************************************************
 *
 * @file app_hid.c
 *
 * @brief HID Application Module entry point
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

#include "rwip_config.h"            // SW configuration

#include <stdio.h>
#include <string.h>


/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "user_ble.h"                    // Application Definitions
#include "app_sec.h"                // Application Security Module API
#include "user_ble_task.h"               // Application task definitions
#include "app_hid.h"                // HID Application Module Definitions
#include "hogpd_task.h"             // HID Over GATT Profile Device Role Functions
#include "prf_types.h"              // Profile common types Definition
#include "arch.h"                    // Platform Definitions
#include "prf.h"

#include "bx_kernel.h"
#include "user_service_ble.h"

#if (NVDS_SUPPORT)
#include "nvds.h"                   // NVDS Definitions
#endif //(NVDS_SUPPORT)

#if (DISPLAY_SUPPORT)
#include "app_display.h"            // Application Display Module
#endif //(DISPLAY_SUPPORT)

#include "co_utils.h"               // Common functions

#if (KE_PROFILING)
#include "ke_mem.h"
#endif //(KE_PROFILING)

#include "bx_shell.h"

#include "easyflash.h"
#include "ke_timer.h"
/*
 * DEFINES
 ****************************************************************************************
 */

/// Length of the HID Mouse Report
#define APP_HID_MOUSE_REPORT_LEN       (6)
/// Length of the Report Descriptor for an HID Mouse
#define APP_HID_MOUSE_REPORT_MAP_LEN   (sizeof(keyboard_report_map))

/// Duration before connection update procedure if no report received (mouse is silent) - 20s
#define APP_HID_SILENCE_DURATION_1     (2000)
/// Duration before disconnection if no report is received after connection update - 60s
#define APP_HID_SILENCE_DURATION_2     (6000)

/// Number of reports that can be sent
#define APP_HID_NB_SEND_REPORT         (10)




/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/// States of the Application HID Module
enum app_hid_states {
    /// Module is disabled (Service not added in DB)
    APP_HID_DISABLED,
    /// Module is idle (Service added but profile not enabled)
    APP_HID_IDLE,
    /// Module is enabled (Device is connected and the profile is enabled)
    APP_HID_ENABLED,
    /// The application can send reports
    APP_HID_READY,
    /// Waiting for a report
    APP_HID_WAIT_REP,

    APP_HID_STATE_MAX,
};


typedef struct {
    uint8_t conidx;
    uint8_t state;
    uint8_t nb_report;
} hid_env_t;


static hid_env_t osapp_hid_env;

uint8_t botton_ctrl_buffer[REPORT_LENGTH_ID0];
uint8_t pos_ctrl_buffer[REPORT_LENGTH_ID1];


uint8_t key_borad_buf[REPORT_LENGTH_ID2];

int8_t report_lenght = 0;
int8_t report_id = 0;
uint8_t ios_or_android = 0;
char mouse_ene_save[32] = "energy_safe";//NVDS_TAG_MOUSE_ENERGY_SAFE
char mouse_timeout[32] = "ps_timeout";//NVDS_TAG_MOUSE_TIMEOUT

extern uint8_t notify_status;
/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// HID Application Module Environment Structure
static struct app_hid_env_tag app_hid_env;

//keyboard map
static const uint8_t keyboard_report_map[] =
{
    //first Id
    0x05, 0x0C, /*Usage Page(Consumer)*/
    0x09, 0x01, /*Usage(Consumer Control)*/
    0xA1, 0x01, /*Collection(Application)*/
    0x85, 0x01, /*report id(1)*/
    0x19, 0x00, /*Usage Minimum(Unassigned)*/
    0x2A, 0x9C, 0x02, /*Usage Maximum(AC Distribute Vertically)*/
    0x15, 0x00, /*Logical minimum(0)*/
    0x26, 0x9C, 0x02, /*Usage maximum(668)*/
    0x95, 0x01, /*report count(1)*/
    0x75, 0x10, /*report size(16)*/
    0x81, 0x00, /*Input(Data,Array,Absolute,Bit Field)*/
    0x09, 0x02, /*Usage(Numeric Key Pad)*/
    0xA1, 0x02, /*Collection(Logical)*/
    0x05, 0x09, /*Usage Page(Button)*/
    0x19, 0x01, /*Usage Minimum(Button1)*/
    0x29, 0x0A, /*Usage Maximum(Button10)*/
    0x15, 0x01, /*Logical minimum(1)*/
    0x25, 0x0A, /*Logical maximum(10)*/
    0x95, 0x01, /*report count(1)*/
    0x75, 0x08, /*report size(8)*/
    0x81, 0x40, /*Input(Data,Array,Absolute,Bit Field)*/
    0xC0,/*End Collection*/
    0xC0,/*End Collection*/

    0x05, 0x01, /*Usage Page(Deneric Desktop)*/
    0x09, 0x02, /*Usage(Mouse)*/
    0xA1, 0x01, /*Collection(Application)*/
    0x09, 0x01, /*Usage(Pointer)*/
    0xA1, 0x00, /*Collection(Physical)*/
    0x85, 0x03, /*report id(3)*/
    0x05, 0x01, /*Usage Page(Generic Desktop)*/
    0x09, 0x30, /*Usage(X)*/
    0x09, 0x31, /*Usage(Y)*/
    0x15, 0x80, /*Logical minimum(-128)*/
    0x25, 0x7F, /*Logical maximum(127)*/
    0x75, 0x08, /*report size(8)*/
    0x95, 0x02, /*report count(2)*/
    0x81, 0x06, /*Input(Data,Value,Relative,Bit Field)*/
    0x05, 0x09, /*Usage Page(Button)*/
    0x19, 0x01, /*Usage Minimum(Button 1)*/
    0x29, 0x05, /*Usage Maximum(Button 5)*/
    0x15, 0x00, /*Logical minimum(0)*/
    0x25, 0x01, /*Logical maximum(1)*/
    0x95, 0x05, /*report count(5)*/
    0x75, 0x01, /*report size(1)*/
    0x81, 0x02, /*Input(Data,Value,Absolute,Bit Field)*/
    0x95, 0x01, /*Report Count(1)*/
    0x75, 0x03, /*Report Size(3)*/
    0x81, 0x03, /*Input(Constant,Value,Absolute,Bit Field)*/
    0xC0,/*End Collection*/
    0xC0,/*End Collection*/
    0x06, 0x01, 0xFF, /*Usage Page(Vendor-defined 0xFF01)*/
    0x09, 0x01, /*Usage(Vendor-defined 0x0001)*/
    0xA1, 0x02, /*Collection(Logical)*/
    0x85, 0x05, /*report id(5)*/
    0x09, 0x14, /*Usage(Vendor-defined 0x0014)*/
    0x75, 0x08, /*report size(8)*/
    0x95, 0x14, /*report count(20)*/
    0x15, 0x80, /*Logical minimum(-128)*/
    0x25, 0x7F, /*Logical maximum(127)*/
    0x81, 0x22, /*Input(Data,Value,Absolute,Bit Field)*/
    0x85, 0x04, /*report id(4)*/
    0x09, 0x04, /*Usage(Vendor-defined 0x0004)*/
    0x75, 0x08, /*report size(8)*/
    0x95, 0x01, /*report count(1)*/
    0x91, 0x02, /*Output(Data,Value,Absolute,Non-volatile,Bit Field)*/
    0xC0,/*End Collection*/

    0x05, 0x01, /*Usage Page(Generic Desktop)*/
    0x09, 0x06, /*Usage(Keyboard)*/
    0xA1, 0x01, /*Collection(Aplication)*/
    0x85, 0x0A, /*report id(10)*/
    0x75, 0x01, /*report size(1)*/
    0x95, 0x08, /*report count(8)*/
    0x05, 0x07, /*Usage Page(keyboard)*/
    0x19, 0xE0, /*Usage Minimum(Keyboard Left Control)*/
    0x29, 0xE7, /*Usage Maximum(Keyboard Right GUI)*/
    0x15, 0x00, /*Logical minimum(0)*/
    0x25, 0x01, /*Logical maximum(1)*/
    0x81, 0x02, /*Input(Data,Value,Absolute,Bit Field)*/
    0x95, 0x01, /*report count(1)*/
    0x75, 0x08, /*report size(8)*/
    0x81, 0x01, /*Input(Constant,Array,Absolute,Bit Field)*/
    0x95, 0x05, /*report count(5)*/
    0x75, 0x01, /*report size(1)*/
    0x05, 0x08, /*Usage Page(LEDs)*/
    0x19, 0x01, /*Usage Minimum(Num Lock)*/
    0x29, 0x05, /*Usage Maximum(Kana)*/
    0x91, 0x02, /*Output(Data,Value,Absolute,Non-volatile,Bit Field)*/
    0x95, 0x01, /*report count(1)*/
    0x75, 0x03, /*report size(3)*/
    0x91, 0x01, /*Output(Constant,Array,Absolute,Non-volatile,Bit Field)*/
    0x95, 0x06, /*report count(6)*/
    0x75, 0x08, /*report size(8)*/
    0x15, 0x00, /*Logical minimum(0)*/
    0x26, 0xE7, 0x00, /*Logical maximum(231)*/
    0x05, 0x07, /*Usage Page(Keyboard)*/
    0x19, 0x00, /*Usage minimum(No event indicated)*/
    0x29, 0xE7, /*Usage maximum(Keyboard Right GUI)*/
    0x81, 0x00, /*Input(Data,Array,Absolute,Bit Field)*/
    0xC0,/*End Collection*/
};



/*
 * GLOBAL FUNCTION DEFINITIONS
 ****************************************************************************************
 */

void app_hid_init( void )
{
    // Length of the mouse timeout value
    uint8_t length = NVDS_LEN_MOUSE_TIMEOUT;

    // Reset the environment
    memset( &app_hid_env, 0, sizeof( app_hid_env ) );

    app_hid_env.nb_report = APP_HID_NB_SEND_REPORT;

    /*
     * Get the timeout value from the NVDS - This value is used each time a report is received
     * from the PS2 driver, store it in the environment.
     */

    ef_get_env_blob( mouse_timeout, ( uint8_t * )&app_hid_env.timeout, length, NULL );
//    if ( nvds_get( NVDS_TAG_MOUSE_TIMEOUT, &length, ( uint8_t * )&app_hid_env.timeout ) != NVDS_OK )
    if( app_hid_env.timeout == 0xFF ) {
        app_hid_env.timeout = APP_HID_SILENCE_DURATION_1;
    }
}


/*
 ****************************************************************************************
 * @brief Function called when get GAP manager command complete events.
 *
 ****************************************************************************************
 */
#if 0
void app_hid_start_mouse( void )
{
    /*-----------------------------------------------------------------------------------
     * CONFIGURE THE MOUSE
     *----------------------------------------------------------------------------------*/
#if (PS2_SUPPORT)
    // Default mouse rate (200 report/s)
    uint8_t rate = 200;

#if (NVDS_SUPPORT)
    uint8_t length = NVDS_LEN_MOUSE_SAMPLE_RATE;

    // Get sample rate from NVDS
    if ( nvds_get( NVDS_TAG_MOUSE_SAMPLE_RATE, &length, &rate ) == NVDS_OK ) {
        // Check if value is among supported set
        if ( ( rate != 10 ) && ( rate != 20 ) && ( rate != 40 ) && ( rate != 60 ) &&
             ( rate != 80 ) && ( rate != 100 ) && ( rate != 200 ) ) {
            // Default value
            rate = 200;
        }
    }
#endif //(NVDS_SUPPORT)

    // Start PS2_mouse
    ps2_mouse_start( rate, &app_hid_send_mouse_report );
#endif //(PS2_SUPPORT)
}

#endif

void app_hid_start_keyboard( void )
{

}




void app_hid_add_hids( void )
{
    struct hogpd_db_cfg * db_cfg;
    // Prepare the HOGPD_CREATE_DB_REQ message
    struct gapm_profile_task_add_cmd * req = KE_MSG_ALLOC_DYN( GAPM_PROFILE_TASK_ADD_CMD,
            TASK_GAPM, TASK_APP,
            gapm_profile_task_add_cmd, sizeof( struct hogpd_db_cfg ) );

    // Fill message
    req->operation   = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl     = PERM( SVC_AUTH, ENABLE );
    req->prf_task_id = TASK_ID_HOGPD;
    req->app_task    = TASK_APP;
    req->start_hdl   = 0;

    // Set parameters
    db_cfg = ( struct hogpd_db_cfg * ) req->param;

    // Only one HIDS instance is useful

    db_cfg->hids_nb = 1;//2;//

    // The device is a mouse
    db_cfg->cfg[0].svc_features = HOGPD_CFG_KEYBOARD;
    //

    // Only one Report Characteristic is requested
    db_cfg->cfg[0].report_nb    = 5;//1;//3;//2;//


    db_cfg->cfg[0].report_id[0] = 1;
    db_cfg->cfg[0].report_id[1] = 3;
    db_cfg->cfg[0].report_id[2] = 5;
    db_cfg->cfg[0].report_id[3] = 10;
    db_cfg->cfg[0].report_id[4] = 4;



    // The report is an input report
    db_cfg->cfg[0].report_char_cfg[0] = HOGPD_CFG_REPORT_IN;
    db_cfg->cfg[0].report_char_cfg[1] = HOGPD_CFG_REPORT_IN;
    db_cfg->cfg[0].report_char_cfg[2] = HOGPD_CFG_REPORT_IN;
    db_cfg->cfg[0].report_char_cfg[3] = HOGPD_CFG_REPORT_IN;
    db_cfg->cfg[0].report_char_cfg[4] = HOGPD_CFG_REPORT_OUT;


    // HID Information
    db_cfg->cfg[0].hid_info.bcdHID       = 0x0111;         // HID Version 1.11
    db_cfg->cfg[0].hid_info.bCountryCode = 0x00;
    db_cfg->cfg[0].hid_info.flags        = HIDS_REMOTE_WAKE_CAPABLE | HIDS_NORM_CONNECTABLE;


    // Send the message
    ke_msg_send( req );
}




/*
 ****************************************************************************************
 * @brief Function called when get connection complete event from the GAP
 *
 ****************************************************************************************
 */
void app_hid_enable_prf( uint8_t conidx )
{
    // Requested connection parameters
//    struct gapc_conn_param conn_param;

    uint16_t ntf_cfg;

    // Store the connection handle
    app_hid_env.conidx = conidx;

    // Allocate the message
    struct hogpd_enable_req * req = KE_MSG_ALLOC( HOGPD_ENABLE_REQ,
                                    prf_get_task_from_id( TASK_ID_HOGPD ),
                                    TASK_APP,
                                    hogpd_enable_req );

    // Fill in the parameter structure
    req->conidx     = conidx;
    // Notifications are disabled
    ntf_cfg         = 0;

    // Go to Enabled state
    app_hid_env.state = APP_HID_ENABLED;


    bxsh_logln( "=========app_sec_get_bond_status() = %d========", app_sec_get_bond_status() );
#if (NVDS_SUPPORT)
    // If first connection with the peer device
    if ( app_sec_get_bond_status() ) {
        // Length of the value read in NVDS
        uint8_t length   = NVDS_LEN_MOUSE_NTF_CFG;
        // Notification configuration

//        if ( nvds_get( NVDS_TAG_MOUSE_NTF_CFG, &length, ( uint8_t * )&ntf_cfg ) != NVDS_OK ) {
//            // If we are bonded this information should be present in the NVDS
//            ASSERT_ERR( 0 );
//        }
//        ef_get_env_blob( mouse_ntf, &ntf_cfg, length, NULL );

        // CCC enable notification
        if ( ( ntf_cfg & HOGPD_CFG_REPORT_NTF_EN ) != 0 ) {
            // The device is ready to send reports to the peer device
            app_hid_env.state = APP_HID_READY;
            app_hid_env.nb_report = APP_HID_NB_SEND_REPORT;

            // Restart the mouse timeout timer if needed
            if ( app_hid_env.timeout != 0 ) {
                ke_timer_set( APP_HID_MOUSE_TIMEOUT_TIMER, TASK_APP, ( uint32_t )( app_hid_env.timeout ) );
                app_hid_env.timer_enabled = true;
            }
        }
    }
#endif //(NVDS_SUPPORT)

    req->ntf_cfg[conidx] = ntf_cfg;

    /*
     * Requested connection interval: 10ms
     * Latency: 25
     * Supervision Timeout: 2s
     */
//    conn_param.intv_min = 8;
//    conn_param.intv_max = 8;
//    conn_param.latency  = 25;
//    conn_param.time_out = 200;

//    appm_update_param();

    // Send the message
    ke_msg_send( req );
}







/*
 ****************************************************************************************
 * @brief Function called from PS2 driver
 *
 ****************************************************************************************
 */
#if 1
void app_hid_send_keyboard_report( uint8_t * array )
{
    if ( app_hid_env.nb_report ) {

        // Allocate the HOGPD_REPORT_UPD_REQ message
        struct hogpd_report_upd_req * req = KE_MSG_ALLOC_DYN( HOGPD_REPORT_UPD_REQ,
                                            prf_get_task_from_id( TASK_ID_HOGPD ),
                                            TASK_APP,
                                            hogpd_report_upd_req,
                                            report_lenght );

//        req->conidx = osapp_hid_env.conidx;
//        req->report.hid_idx = osapp_hid_env.conidx;
		req->conidx = app_env.conidx;
        req->report.hid_idx = app_env.conidx;
        req->report.idx = report_id;//1;// 0;
        req->report.length = report_lenght;//MUSIC_CTRL_REPORT_LENGTH;
        req->report.type = HOGPD_REPORT;
        memset( req->report.value, 0, report_lenght );
        memcpy( req->report.value, array, report_lenght );

        //  bxsh_logln("======req->conidx = %d\treq->report.hid_idx = %d\treq->report.idx = %d========", req->conidx,req->report.hid_idx,req->report.idx);

        ke_msg_send( req );

        // app_hid_env.nb_report--;
        notify_status = 1;
        // Restart the mouse timeout timer if needed
        if ( app_hid_env.timeout != 0 ) {
            ke_timer_set( APP_HID_MOUSE_TIMEOUT_TIMER, TASK_APP, ( uint32_t )( app_hid_env.timeout ) );
            app_hid_env.timer_enabled = true;
        }
    }

}
#endif

/*
 * MESSAGE HANDLERS
 ****************************************************************************************
 */


static int hogpd_ctnl_pt_ind_handler( ke_msg_id_t const msgid,
                                      struct hogpd_ctnl_pt_ind const * param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id )
{


    if ( param->conidx == app_hid_env.conidx ) {
        //make use of param->hid_ctnl_pt
        struct hogpd_report_cfm * req = KE_MSG_ALLOC_DYN( HOGPD_REPORT_CFM,
                                        prf_get_task_from_id( TASK_ID_HOGPD ), /* src_id */
                                        TASK_APP,
                                        hogpd_report_cfm,
                                        0 );

        req->conidx = param->conidx; ///app_hid_env.conidx; ///???
        /// Operation requested (read/write @see enum hogpd_op)
        req->operation = HOGPD_OP_REPORT_WRITE;
        /// Status of the request
        req->status = GAP_ERR_NO_ERROR;  ///???
        /// Report Info
        //req->report;
        /// HIDS Instance
        req->report.hid_idx = app_hid_env.conidx; ///???
        /// type of report (@see enum hogpd_report_type)
        req->report.type = -1;//outside
        /// Report Length (uint8_t)
        req->report.length = 0;
        /// Report Instance - 0 for boot reports and report map
        req->report.idx = 0;
        /// Report data


        // Send the message
        ke_msg_send( req );
    }
    return ( KE_MSG_CONSUMED );
}




static int hogpd_ntf_cfg_ind_handler( ke_msg_id_t const msgid,
                                      struct hogpd_ntf_cfg_ind const * param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id )
{

    bxsh_logln( "hogpd_ntf_cfg_ind_handler\tapp_hid_env.conidx = %d\tparam->ntf_cfg[param->conidx] = %d\tapp_hid_env.state = %d", app_hid_env.conidx, param->ntf_cfg[param->conidx], app_hid_env.state );
    if ( app_hid_env.conidx == param->conidx ) {
        if ( ( param->ntf_cfg[param->conidx] & HOGPD_CFG_REPORT_NTF_EN ) != 0 ) {
            // The device is ready to send reports to the peer device
            app_hid_env.state = APP_HID_READY;
        } else {
            // Come back to the Enabled state
            if ( app_hid_env.state == APP_HID_READY ) {
                app_hid_env.state = APP_HID_ENABLED;
            }
        }

        // Store the notification configuration in the database
//        if ( nvds_put( NVDS_TAG_MOUSE_NTF_CFG, NVDS_LEN_MOUSE_NTF_CFG,
//                       ( uint8_t * )&param->ntf_cfg[param->conidx] ) != NVDS_OK ) {
//            // Should not happen
//            ASSERT_ERR( 0 );
//        }
        //ef_set_env_blob( mouse_ntf, &param->ntf_cfg[param->conidx], NVDS_LEN_MOUSE_NTF_CFG );
    }

    return ( KE_MSG_CONSUMED );
}

static int hogpd_report_req_ind_handler( ke_msg_id_t const msgid,
        struct hogpd_report_req_ind const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{

    if ( ( param->operation == HOGPD_OP_REPORT_READ ) && ( param->report.type == HOGPD_REPORT_MAP ) ) {

        uint16_t report_length = sizeof( keyboard_report_map );
        struct hogpd_report_cfm * req = KE_MSG_ALLOC_DYN( HOGPD_REPORT_CFM, src_id, dest_id, hogpd_report_cfm, report_length );
        req->conidx = osapp_hid_env.conidx;
        req->operation = HOGPD_OP_REPORT_READ;
        req->status = GAP_ERR_NO_ERROR;
        req->report.hid_idx = param->report.hid_idx;
        req->report.type = HOGPD_REPORT_MAP;
        req->report.length = report_length;
        req->report.idx = param->report.hid_idx;//0; // for report map
        memcpy( req->report.value, keyboard_report_map, report_length );
        ke_msg_send( req );


    } else {
        struct hogpd_report_cfm * req = KE_MSG_ALLOC_DYN( HOGPD_REPORT_CFM,
                                        src_id,
                                        TASK_APP,
                                        hogpd_report_cfm,
                                        param->report.length );

        req->conidx = param->conidx;
        req->operation = HOGPD_OP_REPORT_READ;
        req->status = GAP_ERR_NO_ERROR;
        req->report.type = param->report.type;
        req->report.length = param->report.length;
        req->report.idx = param->report.idx;
        memset( req->report.value, 0, param->report.length );

        // Send the message
        ke_msg_send( req );
    }

    return ( KE_MSG_CONSUMED );
}

static int hogpd_proto_mode_req_ind_handler( ke_msg_id_t const msgid,
        struct hogpd_proto_mode_req_ind const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{

    if ( ( param->conidx == app_hid_env.conidx ) && ( param->operation == HOGPD_OP_PROT_UPDATE ) ) {

        //make use of param->proto_mode
        struct hogpd_proto_mode_cfm * req = KE_MSG_ALLOC_DYN( HOGPD_PROTO_MODE_CFM,
                                            prf_get_task_from_id( TASK_ID_HOGPD ), /* src_id */
                                            TASK_APP,
                                            hogpd_proto_mode_cfm,
                                            0 );
        /// Connection Index
        req->conidx = app_hid_env.conidx;
        /// Status of the request
        req->status = GAP_ERR_NO_ERROR;
        /// HIDS Instance
        req->hid_idx = app_hid_env.conidx;
        /// New Protocol Mode Characteristic Value
        req->proto_mode = param->proto_mode;


        // Send the message
        ke_msg_send( req );
    } else {
        struct hogpd_proto_mode_cfm * req = KE_MSG_ALLOC_DYN( HOGPD_PROTO_MODE_CFM,
                                            prf_get_task_from_id( TASK_ID_HOGPD ), /* src_id */
                                            TASK_APP,
                                            hogpd_proto_mode_cfm,
                                            0 );
        /// Status of the request
        req->status = ATT_ERR_APP_ERROR;

        /// Connection Index
        req->conidx = app_hid_env.conidx;
        /// HIDS Instance
        req->hid_idx = app_hid_env.conidx;
        /// New Protocol Mode Characteristic Value
        req->proto_mode = param->proto_mode;

        // Send the message
        ke_msg_send( req );
    }
    return ( KE_MSG_CONSUMED );
}


static int hogpd_report_upd_handler( ke_msg_id_t const msgid,
                                     struct hogpd_report_upd_rsp const * param,
                                     ke_task_id_t const dest_id,
                                     ke_task_id_t const src_id )
{
#if 0
    if ( app_hid_env.conidx == param->conidx ) {
        if ( GAP_ERR_NO_ERROR == param->status ) {
            if ( app_hid_env.nb_report < APP_HID_NB_SEND_REPORT ) {
                app_hid_env.nb_report++;
            }
        } else {
            // we get this message if error occur while sending report
            // most likely - disconnect
            // Go back to the ready state
            app_hid_env.state = APP_HID_IDLE;
            // change mode
            // restart adv
            // Try to restart advertising if needed
            bx_call( us_ble_id(), BXM_BLE_ADV_START, 0, 0 );
            //report was not success - need to restart???
        }
    }
#endif
    return ( KE_MSG_CONSUMED );
}

static int hogpd_enable_rsp_handler( ke_msg_id_t const msgid,
                                     struct hogpd_enable_rsp const * param,
                                     ke_task_id_t const dest_id,
                                     ke_task_id_t const src_id )
{

    return ( KE_MSG_CONSUMED );
}

///**
// ****************************************************************************************
// * @brief Function called when the APP_HID_MOUSE_TIMEOUT_TIMER expires.
// *
// * @param[in] msgid     Id of the message received.
// * @param[in] param     Pointer to the parameters of the message.
// * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
// * @param[in] src_id    ID of the sending task instance.
// *
// * @return If the message was consumed or not.
// ****************************************************************************************
// */
//static int app_hid_mouse_timeout_timer_handler( ke_msg_id_t const msgid,
//        void const * param,
//        ke_task_id_t const dest_id,
//        ke_task_id_t const src_id )
//{
//    app_hid_env.timer_enabled = false;

//    if ( app_hid_env.state == APP_HID_READY ) {
//        // Requested connection parameters
////        struct gapc_conn_param conn_param;
//        // Length
//        uint8_t length = NVDS_LEN_MOUSE_TIMEOUT;
//        // Timer value
//        uint16_t timer_val;

//        /*
//         * Request an update of the connection parameters
//         * Requested connection interval: 10ms
//         * Latency: 200
//         * Supervision Timeout: 5s
//         */
////        conn_param.intv_min = 8;
////        conn_param.intv_max = 8;
////        conn_param.latency  = 200;
////        conn_param.time_out = 500;

//        appm_update_param(  );

//        // Go to the Wait for Report state
//        app_hid_env.state = APP_HID_WAIT_REP;

//        // Get the timer value from the NVDS
////        if ( nvds_get( NVDS_TAG_MOUSE_ENERGY_SAFE, &length, ( uint8_t * )&timer_val ) != NVDS_OK ) {
////            timer_val = APP_HID_SILENCE_DURATION_2;
////        }
//        ef_get_env_blob( mouse_ene_save, &timer_val, length, NULL );
//        if( timer_val == 0xFF ) {
//            timer_val = APP_HID_SILENCE_DURATION_2;
//        }

//        // Relaunch the timer
//        ke_timer_set( APP_HID_MOUSE_TIMEOUT_TIMER, TASK_APP, timer_val );
//        app_hid_env.timer_enabled = true;
//    } else if ( app_hid_env.state == APP_HID_WAIT_REP ) {
//        // Disconnect the link with the device
//        bx_call( us_ble_id(), BXM_BLE_DIS_LINK, 0, 0 );


//        // Go back to the ready state
//        app_hid_env.state = APP_HID_IDLE;
//    }

//    return ( KE_MSG_CONSUMED );
//}

/**
 ****************************************************************************************
 * @brief
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance (TASK_GAP).
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int app_hid_msg_dflt_handler( ke_msg_id_t const msgid,
                                     void const * param,
                                     ke_task_id_t const dest_id,
                                     ke_task_id_t const src_id )
{
    // Drop the message

    return ( KE_MSG_CONSUMED );
}

/**
 ****************************************************************************************
 * @brief Set the value of the Report Map Characteristic in the database
 ****************************************************************************************
 */
void app_hid_set_report_map( void );

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler app_hid_msg_handler_list[] = {
    // Note: first message is latest message checked by kernel so default is put on top.
    {KE_MSG_DEFAULT_HANDLER,        ( ke_msg_func_t )app_hid_msg_dflt_handler},

    {HOGPD_ENABLE_RSP,              ( ke_msg_func_t )hogpd_enable_rsp_handler},
///  notification configuration changed
    {HOGPD_NTF_CFG_IND,             ( ke_msg_func_t )hogpd_ntf_cfg_ind_handler},
    {HOGPD_REPORT_REQ_IND,          ( ke_msg_func_t )hogpd_report_req_ind_handler},
    {HOGPD_PROTO_MODE_REQ_IND,      ( ke_msg_func_t )hogpd_proto_mode_req_ind_handler},

    {HOGPD_CTNL_PT_IND,             ( ke_msg_func_t )hogpd_ctnl_pt_ind_handler},

    {HOGPD_REPORT_UPD_RSP,          ( ke_msg_func_t )hogpd_report_upd_handler},
//    {APP_HID_MOUSE_TIMEOUT_TIMER,   ( ke_msg_func_t )app_hid_mouse_timeout_timer_handler},
};

const struct ke_state_handler app_hid_table_handler =
{&app_hid_msg_handler_list[0], ( sizeof( app_hid_msg_handler_list ) / sizeof( struct ke_msg_handler ) )};



/// @} APP
