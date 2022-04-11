/**
 ****************************************************************************************
 *
 * @file diss.h
 *
 * @brief Header file - Device Information Service Server.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef USER_PROFILE_H_
#define USER_PROFILE_H_

/**
 ****************************************************************************************
 * @addtogroup DISS Device Information Service Server
 * @ingroup DIS
 * @brief Device Information Service Server
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#include "prf_types.h"
#include "prf.h"

/*
 * DEFINES
 ****************************************************************************************
 */

#define USER_PROFILE_IDX_MAX        (1)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/// Possible states of the DISS task
enum
{
    /// Idle state
    USER_PROFILE_IDLE,
    /// Busy state
    USER_PROFILE_BUSY,
    /// Number of defined states.
    USER_PROFILE_STATE_MAX
};

/// DISS Attributes database handle list
enum user_profile_att_db_handles
{
    PTS_SVC_IDX_SVC,

    PTS_SVC_IDX_RX_CHAR,
    PTS_SVC_IDX_RX_VAL,
    PTS_SVC_IDX_TX_CHAR,
    PTS_SVC_IDX_TX_VAL,
    PTS_SVC_IDX_TX_NTF_CFG,
    
    PTS_SVC_ATT_NUM
};

/// Value element
struct user_profile_val_elmt
{
    /// list element header
    struct co_list_hdr hdr;
    /// value identifier
    uint8_t value;
    /// value length
    uint8_t length;
    /// value data
    uint8_t data[__ARRAY_EMPTY];
};

///Device Information Service Server Environment Variable
struct user_profile_env_tag
{
    /// profile environment
    prf_env_t prf_env;
    /// List of values set by application
    struct co_list values;
    /// Service Attribute Start Handle
    uint16_t start_hdl;
    /// Services features
    uint16_t features;
    /// Last requested value
    uint8_t  req_val;
    /// Last connection index which request value
    uint8_t  req_conidx;

    /// DISS task state
    ke_state_t state[USER_PROFILE_IDX_MAX];
};

/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Retrieve DIS service profile interface
 *
 * @return DIS service profile interface
 ****************************************************************************************
 */
const struct prf_task_cbs* user_profile_prf_itf_get(void);


/**
 ****************************************************************************************
 * @brief Check if the provided value length matches characteristic requirements
 * @param char_code Characteristic Code
 * @param val_len   Length of the Characteristic value
 *
 * @return status if value length is ok or not
 ****************************************************************************************
 */
uint8_t user_profile_check_val_len(uint8_t char_code, uint8_t val_len);

/**
 ****************************************************************************************
 * @brief Retrieve handle attribute from value
 *
 * @param[in] env   Service environment variable
 * @param[in] value Value to search
 *
 * @return Handle attribute from value
 ****************************************************************************************
 */
uint16_t user_profile_value_to_handle(struct user_profile_env_tag* env, uint8_t value);

/**
 ****************************************************************************************
 * @brief Retrieve value from attribute handle
 *
 * @param[in] env    Service environment variable
 * @param[in] handle Attribute handle to search
 *
 * @return  Value from attribute handle
 ****************************************************************************************
 */
uint8_t user_profile_handle_to_value(struct user_profile_env_tag* env, uint16_t handle);

/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler userp_default_handler;

void add_user_profile(void);


#endif //BLE_USER_PROFILE_SERVER

