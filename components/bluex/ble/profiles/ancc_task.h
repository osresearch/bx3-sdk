#ifndef ANCC_TASK_H_
#define ANCC_TASK_H_

#include "rwip_task.h"
#include "prf_types.h"
#include "anc_common.h"
#include "ke.h"
#include "ke_mem.h"

#define ANC_APP_ID_MAX_LENGTH 32

enum
{
    ANCC_NONE,
    ANCC_IDLE,
    ANCC_DISCOVERING,
    ANCC_NTF_SRC_CL_CFG_NTF_ENABLING,
    ANCC_NTF_SRC_CL_CFG_NTF_DISABLING,
    ANCC_DATA_SRC_CL_CFG_NTF_ENABLING,
    ANCC_DATA_SRC_CL_CFG_NTF_DISABLING,
    ANCC_NTF_ATTS_REQUESTING,
    ANCC_APP_ATTS_REQUESTING,
    ANCC_NTF_ACTION_REQUESTING,
    ANCC_STATE_MAX,
};

/// Message IDs
enum
{
    /// Enable the ANCS Client task - at connection
    ANCC_ENABLE_REQ = TASK_FIRST_MSG(TASK_ID_ANCC),

    ANCC_ENABLE_RSP,
    
    ANCC_CL_CFG_NTF_EN_CMD,
    
    /// Indicate that a notification of the Notification Source characteristic has been received
    ANCC_NTF_SRC_IND,
    
    /// Write a "Get Notification Attributes" command in Control Point 
    ANCC_GET_NTF_ATTS_CMD,
    
    /// Indicate that the value of a notification attribute is available
    ANCC_NTF_ATT_IND,
    
    /// Write a "Get App Attributes" command in Control Point 
    ANCC_GET_APP_ATTS_CMD,

    /// Indicate that the value of a notification attribute is available
    ANCC_APP_ATT_IND,
    
    ANCC_PERFORM_NTF_ACTION_CMD,

    ANCC_CMP_EVT,
};

/// ANCS Characteristics
enum ancc_anc_chars
{
    /// Notification Source
    ANC_CHAR_NTF_SRC,
    /// Control Point
    ANC_CHAR_CTRL_PT,
    /// Data Source
    ANC_CHAR_DATA_SRC,

    ANC_CHAR_MAX,    
};

/// ANCS Characteristic Descriptors
enum ancc_anc_descs
{
    /// Notification Source - Client Characteristic Configuration
    ANC_DESC_NTF_SRC_CL_CFG,
    /// Data Source - Client Characteristic Configuration
    ANC_DESC_DATA_SRC_CL_CFG,

    ANC_DESC_MAX,

};

struct ancc_anc_content
{
    struct prf_svc svc;
    struct prf_char_inf chars[ANC_CHAR_MAX];
    struct prf_char_desc_inf descs[ANC_DESC_MAX];
};

struct ancc_enable_req
{
    uint8_t con_type;
    struct ancc_anc_content anc;    
};

struct ancc_enable_rsp
{
    uint8_t status;
    struct ancc_anc_content anc;
};

struct ancc_cl_cfg_ntf_en_cmd
{
    enum ancc_anc_descs cfg;
    bool enable;
};

typedef struct
{
    uint8_t str[ANC_APP_ID_MAX_LENGTH];
}ancc_app_id_t;

typedef union
{
    ancc_app_id_t app_id;
    uint32_t ntf_uid;
}ancc_id_u;

struct ancc_att_ind
{
    ancc_id_u id;
    uint16_t length;
    uint8_t att_id;
    uint8_t val[];
};

struct ancc_get_ntf_atts_cmd
{
    uint32_t ntf_uid;
    uint16_t att_mask;
    uint16_t title_length;
    uint16_t subtitle_length;
    uint16_t message_length;
};

struct ancc_get_app_atts_cmd
{
    ancc_app_id_t app_id;
    uint8_t att_mask;
};

struct ancc_perform_ntf_action_cmd
{
    uint32_t ntf_uid;
    uint8_t action_id;
};

struct ancc_cmp_evt
{
   ancc_id_u id;
   uint8_t operation;
   uint8_t status;
};

extern const struct ke_state_handler ancc_default_handler;

#endif
