/**
  ******************************************************************************
  * @file   :   main.c
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
#include "rwip_config.h"

#include "diss_task.h"               
#include "prf_types.h"            
#include "gapm_task.h"              
#include <string.h>

#include "user_profile.h"
#include "user_profile_task.h"

#include "bxotas.h"
#include "bxotas_task.h"
#include "user_ble.h"                   
#include "user_ble_profile.h"               
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int diss_value_req_ind_handler(ke_msg_id_t const msgid,
                                          struct diss_value_req_ind const *param,
                                          ke_task_id_t const dest_id,
                                          ke_task_id_t const src_id)
{
    uint8_t len = 0;
    uint8_t *data = NULL;
    
    switch (param->value)
    {
        case DIS_MANUFACTURER_NAME_CHAR:
        {
            len = APP_DIS_MANUFACTURER_NAME_LEN;
            data = (uint8_t *)APP_DIS_MANUFACTURER_NAME;
        } break;

        case DIS_MODEL_NB_STR_CHAR:
        {
            len = APP_DIS_MODEL_NB_STR_LEN;
            data = (uint8_t *)APP_DIS_MODEL_NB_STR;
        } break;

        case DIS_SYSTEM_ID_CHAR:
        {
            len = APP_DIS_SYSTEM_ID_LEN;
            data = (uint8_t *)APP_DIS_SYSTEM_ID;
        } break;

        case DIS_PNP_ID_CHAR:
        {
            len = APP_DIS_PNP_ID_LEN;
            data = (uint8_t *)APP_DIS_PNP_ID;
        } break;

        case DIS_SERIAL_NB_STR_CHAR:
        {
            len = APP_DIS_SERIAL_NB_STR_LEN;
            data = (uint8_t *)APP_DIS_SERIAL_NB_STR;
        } break;

        case DIS_HARD_REV_STR_CHAR:
        {
            len = APP_DIS_HARD_REV_STR_LEN;
            data = (uint8_t *)APP_DIS_HARD_REV_STR;
        } break;

        case DIS_FIRM_REV_STR_CHAR:
        {
            len = APP_DIS_FIRM_REV_STR_LEN;
            data = (uint8_t *)APP_DIS_FIRM_REV_STR;
        } break;

        case DIS_SW_REV_STR_CHAR:
        {
            len = APP_DIS_SW_REV_STR_LEN;
            data = (uint8_t *)APP_DIS_SW_REV_STR;
        } break;

        case DIS_IEEE_CHAR:
        {
            len = APP_DIS_IEEE_LEN;
            data = (uint8_t *)APP_DIS_IEEE;
        } break;

        default:
            ASSERT_ERR(0);
            break;
    }

    struct diss_value_cfm *cfm_value = KE_MSG_ALLOC_DYN(DISS_VALUE_CFM,
            src_id, dest_id,
            diss_value_cfm,
            len);

    cfm_value->value = param->value;
    cfm_value->length = len;
    if (len)
    {
        memcpy(&cfm_value->data[0], data, len);
    }
    ke_msg_send(cfm_value);

    return (KE_MSG_CONSUMED);
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_dis_init(void)
{
    // Nothing to do
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void add_dis_profile(void)
{
    struct diss_db_cfg* db_cfg;

    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,
                                                  TASK_GAPM, TASK_APP,
                                                  gapm_profile_task_add_cmd, sizeof(struct diss_db_cfg));

    req->operation = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl = PERM(SVC_AUTH, NO_AUTH);
    req->prf_task_id = TASK_ID_DISS;
    req->app_task = TASK_APP;
    req->start_hdl = 0;


    db_cfg = (struct diss_db_cfg* ) req->param;
    db_cfg->features = APP_DIS_FEATURES;

    ke_msg_send(req);
}

    
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
const struct ke_msg_handler app_dis_msg_handler_list[] =
{
    {DISS_VALUE_REQ_IND,     (ke_msg_func_t)diss_value_req_ind_handler},
};

const struct ke_state_handler app_dis_table_handler =
    {&app_dis_msg_handler_list[0], (sizeof(app_dis_msg_handler_list)/sizeof(struct ke_msg_handler))};


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void add_user_profile(void)
{
    struct user_db_cfg* db_cfg;

    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC_DYN(GAPM_PROFILE_TASK_ADD_CMD,
                                                  TASK_GAPM, TASK_APP,
                                                  gapm_profile_task_add_cmd, sizeof(struct user_db_cfg));

    req->operation = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl = PERM(SVC_AUTH, NO_AUTH);
    req->prf_task_id = TASK_ID_USER;
    req->app_task = TASK_APP;
    req->start_hdl = 0;

    db_cfg = (struct user_db_cfg* ) req->param;
    db_cfg->features = USER_ALL_SUP;

    ke_msg_send(req);
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void osapp_bxotas_config()
{
    struct bxotas_firmware_dest_cmd *cmd =KE_MSG_ALLOC(BXOTAS_FIRMWARE_DEST_CMD,TASK_ID_GATTC,TASK_APP,bxotas_firmware_dest_cmd);
    
    cmd->firmware_dest = LOCAL_FLASH;
    
    ke_msg_send(cmd);
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void add_bxota_profile(void)
{
    struct gapm_profile_task_add_cmd *req = KE_MSG_ALLOC(GAPM_PROFILE_TASK_ADD_CMD,
                                                  TASK_GAPM, TASK_APP,
                                                  gapm_profile_task_add_cmd);
    req->operation = GAPM_PROFILE_TASK_ADD;
    req->sec_lvl = PERM(SVC_AUTH,NO_AUTH);
    req->prf_task_id = TASK_ID_BXOTAS;
    req->app_task = TASK_APP;
    req->start_hdl = 0;
    
    ke_msg_send(req);
}

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


