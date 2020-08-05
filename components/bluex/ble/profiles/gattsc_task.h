#ifndef GATTSC_TASK_H_
#define GATTSC_TASK_H_

#include "rwip_task.h"
#include "prf_types.h"
#include "ke.h"
#include "ke_mem.h"


enum
{
    GATTSC_NONE,
    GATTSC_DISCOVERING,
    GATTSC_IDLE,
    GATTSC_SVC_CHANGED_IND_ENABLING,
    GATTSC_SVC_CHANGED_IND_DISABLING,
    GATTSC_STATE_MAX,
};

/// Message IDs
enum
{
    GATTSC_ENABLE_REQ = TASK_FIRST_MSG(TASK_ID_GATTSC),

    GATTSC_ENABLE_RSP,
    
    GATTSC_SVC_CHANGED_IND_CFG_CMD,

    GATTSC_SVC_CHANGED_IND,

    GATTSC_CMP_EVT,
};

/// GATTS Characteristics
enum gatts_chars
{
    GATTS_CHAR_SVC_CHANGED,

    GATTS_CHAR_MAX,    
};

/// GATTS Characteristic Descriptors
enum gatts_descs
{
    GATTS_DESC_SVC_CHANGED_CL_CFG,

    GATTS_DESC_MAX,
};

struct gatts_client_content
{
    struct prf_svc svc;
    struct prf_char_inf chars[GATTS_CHAR_MAX];
    struct prf_char_desc_inf descs[GATTS_DESC_MAX];
};

struct gattsc_enable_req
{
    uint8_t con_type;
    struct gatts_client_content gatts;    
};

struct gattsc_enable_rsp
{
    uint8_t status;
    struct gatts_client_content gatts;
};

struct gattsc_svc_changed_ind_cfg_cmd
{
    bool enable;
};

struct gattsc_svc_changed_ind
{
    uint16_t start_hdl;
    uint16_t end_hdl;
};

struct gattsc_cmp_evt
{
    uint8_t operation;
    uint8_t status;
};

extern const struct ke_state_handler gattsc_default_handler;

#endif
