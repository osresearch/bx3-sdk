/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* includes ------------------------------------------------------------------*/

#include "rwip_config.h"     // SW configuration

#if (BLE_BXOTA_SERVER)

#include "app.h" 
#include "app_user_profile.h"                
#include "user_profile_task.h"      
#include "user_profile.h"      
#include "prf_types.h"             
#include "gapm_task.h"        
#include <string.h>

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void user_profile_msg1_handler(ke_msg_id_t const msgid,
                                      void const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    bx_logln("user_profile_msg1_handler");
}

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_user_profile_init(void)
{
    
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_user_profile_add_profile(void)
{
    struct user_proflie_data* data;

    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,
                                                  TASK_GAPM, TASK_APP,
                                                  gapm_profile_task_add_cmd, sizeof(struct user_proflie_data));

    req->operation = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl = PERM(SVC_AUTH, NO_AUTH);
    req->prf_task_id = TASK_ID_USER;
    req->app_task = TASK_APP;
    req->start_hdl = 0;

    data = (struct user_proflie_data* ) req->param;
    data->value = USER_DATA_VALUE3;

    ke_msg_send(req);
}

/*========================= end of exported function =========================*/


const struct ke_msg_handler app_user_profile_msg_handler_list[] =
{
    {USER_PROFILE_MSG1,                 (ke_msg_func_t) user_profile_msg1_handler},
};

const struct ke_state_handler app_user_profile_table_handler =
    {&app_user_profile_msg_handler_list[0], (sizeof(app_user_profile_msg_handler_list)/sizeof(struct ke_msg_handler))};

#endif //BLE_APP_DIS

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
