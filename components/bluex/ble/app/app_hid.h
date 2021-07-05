/**
 ****************************************************************************************
 *
 * @file app_hid.h
 *
 * @brief HID Application Module entry point
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef APP_HID_H_
#define APP_HID_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup RICOW
 *
 * @brief HID Application Module entry point
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"     // SW configuration



#include <stdint.h>          // Standard Integer Definition
#include "ke_task.h"         // Kernel Task Definition

#if (PS2_SUPPORT)
#include "ps2.h"             // PS2 Mouse Driver
#endif //(PS2_SUPPORT)


#include "hogpd_task.h"


/*
 * STRUCTURES DEFINITION
 ****************************************************************************************
 */

/// HID Application Module Environment Structure
struct app_hid_env_tag
{
    /// Connection handle
    uint8_t conidx;
    /// Mouse timeout value
    uint16_t timeout;
    /// Internal state of the module
    uint8_t state;
    /// Timer enabled
    bool timer_enabled;
    /// Number of report that can be sent
    uint8_t nb_report;
};

/*
 * GLOBAL VARIABLES DECLARATIONS
 ****************************************************************************************
 */

#define REPORT_LENGTH_ID0		3
#define REPORT_LENGTH_ID1		6

#define REPORT_KEYBOARD     0 //keyboard
#define REPORT_MOUSE        2 //mouse

extern uint8_t botton_ctrl_buffer[REPORT_LENGTH_ID0];
extern uint8_t pos_ctrl_buffer[REPORT_LENGTH_ID1];

extern int8_t report_lenght;
extern int8_t report_id ;
extern uint8_t ios_or_android;

/// Table of message handlers
extern const struct ke_state_handler app_hid_table_handler;

/*
 * GLOBAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 *
 * Health Thermometer Application Functions
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Initialize HID Application Module
 ****************************************************************************************
 */
void app_hid_init(void);

/**
 ****************************************************************************************
 * @brief Initialize the PS2 mouse driver so that it can be used by the application
 ****************************************************************************************
 */
void app_hid_start_mouse(void);



void app_hid_start_keyboard(void);
void app_hid_send_keyboard_report(uint8_t *array);

/**
 ****************************************************************************************
 * @brief Add a HID Service instance in the DB
 ****************************************************************************************
 */
void app_hid_add_hids(void);

/**
 ****************************************************************************************
 * @brief Enable the HID Over GATT Profile device role
 *
 * @param[in]:  conhdl - Connection handle for the connection
 ****************************************************************************************
 */
void app_hid_enable_prf(uint8_t conidx);

/**
 ****************************************************************************************
 * @brief Send a mouse report to the peer device
 *
 * @param[in]:  report - Mouse report sent by the PS2 driver
 ****************************************************************************************
 */
//void app_hid_send_mouse_report(struct ps2_mouse_msg report);

//void app_hid_send_keyboard_report_ex( struct hogpd_report_upd_req * p_upd );
void app_hid_send_keyboard_report_ex( struct hogpd_report_upd_req * p_upd,uint8_t key_type,uint8_t key );
void app_hid_send_mouse_report_ex( struct hogpd_report_upd_req * p_upd,uint8_t key_type,uint8_t key );

/// @} APP

#endif // APP_HID_H_
