

#ifndef USER_PROFILE_H_
#define USER_PROFILE_H_

#include "rwip_config.h"

#include "prf_types.h"
#include "prf.h"



#define USER_PROFILE_IDX_MAX        (1)


enum
{
    /// Idle state
    USER_PROFILE_IDLE,
    /// Busy state
    USER_PROFILE_BUSY,
    /// Number of defined states.
    USER_PROFILE_STATE_MAX
};

//Attributes database handle list
enum user_profile_att_db_handles
{
    USER_PROFILE_SVC_IDX_SVC,

    USER_PROFILE_SVC_IDX_RX_CHAR,
    USER_PROFILE_SVC_IDX_RX_VAL,
    USER_PROFILE_SVC_IDX_TX_CHAR,
    USER_PROFILE_SVC_IDX_TX_VAL,
    USER_PROFILE_SVC_IDX_TX_NTF_CFG,
    
    USER_PROFILE_SVC_ATT_NUM
};


struct user_profile_env_tag
{
    prf_env_t prf_env;
    uint16_t start_hdl;
    uint8_t  conidx;
    
    uint16_t value;
    
    ke_state_t state[USER_PROFILE_IDX_MAX];
};


const struct prf_task_cbs* user_profile_prf_itf_get(void);

extern const struct ke_state_handler user_profile_handler;

#endif //USER_PROFILE_H_

