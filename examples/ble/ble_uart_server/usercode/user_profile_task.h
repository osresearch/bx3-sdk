/**
 ****************************************************************************************
 *
 * @file diss_task.h
 *
 * @brief Header file - USERTASK.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef USER_PROFILE_TASK_H_
#define USER_PROFILE_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup USERTASK Task
 * @ingroup USER
 * @brief Device Information Service Server Task
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "rwip_task.h" // Task definitions
#include "prf_types.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// Messages for Glucose Profile Sensor
enum user_msg_id
{
    /// Start the Glucose Profile Sensor - at connection
    USER_ENABLE_REQ = TASK_FIRST_MSG(TASK_ID_USER),
    /// Confirm that Glucose Profile Sensor is started.
    USER_ENABLE_RSP,

    ///Inform APP of new configuration value
    USER_CFG_INDNTF_IND,

    /// Record Access Control Point Request
    USER_RACP_REQ_RCV_IND,

    /// Record Access Control Point Resp
    USER_SEND_RACP_RSP_CMD,

    /// Send Glucose measurement with context information
    USER_SEND_MEAS_WITH_CTX_CMD,
    /// Send Glucose measurement without context information
    USER_SEND_MEAS_WITHOUT_CTX_CMD,

    ///Inform that requested action has been performed
    USER_CMP_EVT,
};
///Attribute Table Indexes
enum user_info
{
    /// Manufacturer Name
    USER_MANUFACTURER_NAME_CHAR,
    /// Model Number
    USER_MODEL_NB_STR_CHAR,

    USER_CHAR_MAX,
};

///Database Configuration Flags
enum user_features
{
    ///Indicate if Manufacturer Name String Char. is supported
    USER_MANUFACTURER_NAME_CHAR_SUP       = 0x0001,
    ///Indicate if Model Number String Char. is supported
    USER_MODEL_NB_STR_CHAR_SUP            = 0x0002,
    
    
    USER_ALL_SUP = 0X3,
};
/*
 * API MESSAGES STRUCTURES
 ****************************************************************************************
 */

/// Parameters for the database creation
struct user_db_cfg
{
    /// Database configuration @see enum diss_features
    uint16_t features;
};
/// Parameters of the @ref USER_ENABLE_REQ message
struct user_enable_req
{
    /// Glucose indication/notification configuration
    uint16_t evt_cfg;
};

///Parameters of the @ref USER_ENABLE_RSP message
struct user_enable_rsp
{
    ///Status
    uint8_t status;
};

///Parameters of the @ref USER_CFG_INDNTF_IND message
struct user_cfg_indntf_ind
{
    /// Glucose indication/notification configuration
    uint8_t evt_cfg;
};

///Parameters of the @ref USER_SEND_MEAS_WITH_CTX_CMD message
struct user_send_meas_with_ctx_cmd
{
    /// Sequence Number
    uint16_t seq_num;
};


///Parameters of the @ref USER_SEND_MEAS_WITHOUT_CTX_CMD message
struct user_send_meas_without_ctx_cmd
{
    /// Sequence Number
    uint16_t seq_num;
};


///Parameters of the @ref USER_RACP_REQ_RCV_IND message
struct user_racp_req_rcv_ind
{
    uint8_t a;
};

///Parameters of the @ref USER_SEND_RACP_RSP_CMD message
struct user_send_racp_rsp_cmd
{
    ///Number of records.
    uint16_t num_of_record;
    /// operation code
    uint8_t op_code;
    ///Command status
    uint8_t status;
};

///Parameters of the @ref USER_CMP_EVT message
struct user_cmp_evt
{
    /// completed request
    uint8_t request;
    ///Command status
    uint8_t status;
};
/// @} USERTASK
#endif // USER_TASK_H_
