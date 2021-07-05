

#ifndef USER_PROFILE_TASK_H_
#define USER_PROFILE_TASK_H_


#include <stdint.h>
#include "rwip_task.h"
#include "prf_types.h"


enum user_profile_msg_id
{
    USER_PROFILE_MSG1 = TASK_FIRST_MSG(TASK_ID_USER),
    USER_PROFILE_MSG2,
    USER_PROFILE_MSG3,
};


enum user_data_value
{
    USER_DATA_VALUE1,
    USER_DATA_VALUE2,
    USER_DATA_VALUE3,
};


struct user_proflie_data
{
    uint16_t value;
};


#endif // USER_PROFILE_TASK_H_
