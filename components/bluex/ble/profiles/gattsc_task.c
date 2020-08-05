#include "rwip_config.h"

#if (BLE_GATTS_CLIENT)
#include <string.h>
#include "gattsc_task.h"
#include "gattsc.h"
#include "prf_utils.h"
#include "prf_types.h"
#include "ke_msg.h"
#include "log.h"


const struct prf_char_def gatts_client_char[GATTS_CHAR_MAX] =
{
    [GATTS_CHAR_SVC_CHANGED] = {ATT_CHAR_SERVICE_CHANGED,ATT_MANDATORY,ATT_CHAR_PROP_IND},
};

const struct prf_char_desc_def gatts_client_char_desc[GATTS_DESC_MAX] = 
{
    [GATTS_DESC_SVC_CHANGED_CL_CFG] = {ATT_DESC_CLIENT_CHAR_CFG,ATT_MANDATORY,GATTS_CHAR_SVC_CHANGED}, 
};

static int gattsc_enable_req_handler(ke_msg_id_t const msgid,
    struct gattsc_enable_req const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
 
    uint8_t state = ke_state_get(dest_id);
    uint8_t conidx = KE_IDX_GET(dest_id);
    struct gattsc_env_tag *gattsc_env = PRF_ENV_GET(GATTSC,gattsc);   
    ASSERT_INFO(gattsc_env != NULL, dest_id, src_id);
    if(state == GATTSC_IDLE)
    {
        if(gattsc_env->env[conidx] == NULL)
        {
            // allocate environment variable for task instance
            gattsc_env->env[conidx] = (struct gattsc_cnx_env*) ke_malloc(sizeof(struct gattsc_cnx_env),KE_MEM_ATT_DB);
            memset(gattsc_env->env[conidx], 0, sizeof(struct gattsc_cnx_env));
        }

        //Config connection, start discovering
        if(param->con_type == PRF_CON_DISCOVERY)
        {

            prf_disc_svc_send(&gattsc_env->prf_env, conidx, ATT_SVC_GENERIC_ATTRIBUTE);
            // Go to DISCOVERING state
            ke_state_set(dest_id, GATTSC_DISCOVERING);
        }else
        {
            gattsc_env->env[conidx]->gatts = param->gatts;
            
            gattsc_enable_rsp_send(gattsc_env,conidx,GAP_ERR_NO_ERROR,true);
        }
    }else if(state != GATTSC_DISCOVERING && state != GATTSC_NONE)
    {
        gattsc_enable_rsp_send(gattsc_env,conidx,PRF_ERR_REQ_DISALLOWED,false);
    }
    
    return (KE_MSG_CONSUMED);
}

static int gattc_sdp_svc_ind_handler(ke_msg_id_t const msgid,
    struct gattc_sdp_svc_ind const *ind,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);

    if(state == GATTSC_DISCOVERING)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct gattsc_env_tag *gattsc_env = PRF_ENV_GET(GATTSC, gattsc);

        ASSERT_INFO(gattsc_env != NULL, dest_id, src_id);
        ASSERT_INFO(gattsc_env->env[conidx] != NULL, dest_id, src_id);

        if(gattsc_env->env[conidx]->nb_svc == 0)
        {
            prf_extract_svc_info(ind, GATTS_CHAR_MAX, gatts_client_char,gattsc_env->env[conidx]->gatts.chars,GATTS_DESC_MAX,gatts_client_char_desc,gattsc_env->env[conidx]->gatts.descs);

            //Even if we get multiple responses we only store 1 range
            gattsc_env->env[conidx]->gatts.svc.shdl = ind->start_hdl;
            gattsc_env->env[conidx]->gatts.svc.ehdl = ind->end_hdl;
        }

        gattsc_env->env[conidx]->nb_svc++;
    }

    return (KE_MSG_CONSUMED);
}

static uint8_t gattsc_svc_validity_check(struct gatts_client_content const*gatts)
{
    uint8_t status = prf_check_svc_char_validity(GATTS_CHAR_MAX,gatts->chars,gatts_client_char);
    if(status == ATT_ERR_NO_ERROR)
    {
        status = prf_check_svc_char_desc_validity(GATTS_DESC_MAX,gatts->descs,gatts_client_char_desc,gatts->chars);
    }
    return status;
}

static int gattc_cmp_evt_handler(ke_msg_id_t const msgid,
    struct gattc_cmp_evt const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);
    // Get the address of the environment
    struct gattsc_env_tag *gattsc_env = PRF_ENV_GET(GATTSC, gattsc);
    uint8_t conidx = KE_IDX_GET(dest_id);

    uint8_t status = param->status;
    switch(state)
    {
    case GATTSC_DISCOVERING:
        if (param->status == ATT_ERR_NO_ERROR)
        {
            if(gattsc_env->env[conidx]->nb_svc ==  1)
            {
                status = gattsc_svc_validity_check(&gattsc_env->env[conidx]->gatts);
            }
            // too much services
            else if (gattsc_env->env[conidx]->nb_svc > 1)
            {
                status = PRF_ERR_MULTIPLE_SVC;
            }
            // no services found
            else
            {
                status = PRF_ERR_STOP_DISC_CHAR_MISSING;
            }
        }
        gattsc_enable_rsp_send(gattsc_env, conidx, status,true);
        ke_state_set(dest_id,GATTSC_IDLE);
    break;
    case GATTSC_SVC_CHANGED_IND_ENABLING:
    case GATTSC_SVC_CHANGED_IND_DISABLING:
        if(param->operation == GATTC_WRITE)
        {
            gattsc_cmp_evt_send(gattsc_env,conidx,state,status);
            ke_state_set(dest_id,GATTSC_IDLE);
        }
    break;
    case GATTSC_IDLE:
        BX_ASSERT(param->operation == GATTC_REGISTER && param->status == GAP_ERR_NO_ERROR || param->operation == GATTC_UNREGISTER);
    break;
    default:
        LOG(LOG_LVL_WARN,"state:%d,gattc_cmp_evt,%d,%d\n",state,param->operation,param->status);
    break;
    }
    return (KE_MSG_CONSUMED);
}

static int gattsc_cmd_return_status(uint8_t task_state)
{
    int status;
    switch(task_state)
    {
    case GATTSC_NONE:
    case GATTSC_IDLE:
    case GATTSC_DISCOVERING:
        status = KE_MSG_CONSUMED;
    break;
    case GATTSC_SVC_CHANGED_IND_ENABLING:
    case GATTSC_SVC_CHANGED_IND_DISABLING:
        status = KE_MSG_SAVED;
    break;
    }
    return status;
}

static int gattsc_svc_changed_ind_cfg_cmd_handler(ke_msg_id_t const msgid,
    struct gattsc_svc_changed_ind_cfg_cmd const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);
    struct gattsc_env_tag *gattsc_env = PRF_ENV_GET(GATTSC, gattsc);
    uint8_t conidx = KE_IDX_GET(dest_id);
    if(state == GATTSC_IDLE)
    {
        prf_gatt_write_ntf_ind(&gattsc_env->prf_env,conidx,gattsc_env->env[conidx]->gatts.descs[GATTS_DESC_SVC_CHANGED_CL_CFG].desc_hdl,param->enable ? PRF_CLI_START_IND : PRF_CLI_STOP_NTFIND);
        uint8_t next_state;
        if(param->enable)
        {
            next_state = GATTSC_SVC_CHANGED_IND_ENABLING;
        }else
        {
            next_state = GATTSC_SVC_CHANGED_IND_DISABLING;
        }
        ke_state_set(dest_id, next_state);
    }
    return gattsc_cmd_return_status(state);
}

static int gattc_event_req_ind_handler(ke_msg_id_t const msgid,
    struct gattc_event_req_ind const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    struct gattsc_env_tag *gattsc_env = PRF_ENV_GET(GATTSC, gattsc);
    uint8_t conidx = KE_IDX_GET(dest_id);
    BX_ASSERT(param->handle == gattsc_env->env[conidx]->gatts.chars[GATTS_CHAR_SVC_CHANGED].val_hdl);
    struct gattc_event_cfm *cfm = KE_MSG_ALLOC(GATTC_EVENT_CFM,src_id, dest_id,gattc_event_cfm);
    cfm->handle = param->handle;
    ke_msg_send(cfm);
    BX_ASSERT(param->length == sizeof(struct gattsc_svc_changed_ind));
    struct gattsc_svc_changed_ind *ind = KE_MSG_ALLOC(GATTSC_SVC_CHANGED_IND,APP_MAIN_TASK,dest_id,gattsc_svc_changed_ind);
    memcpy(ind,param->value,sizeof(struct gattsc_svc_changed_ind));
    ke_msg_send(ind);

    return (KE_MSG_CONSUMED);
}


const struct ke_msg_handler gattsc_default_state[] =
{
    {GATTC_CMP_EVT,(ke_msg_func_t)gattc_cmp_evt_handler},
    {GATTC_SDP_SVC_IND,(ke_msg_func_t)gattc_sdp_svc_ind_handler},
    {GATTSC_ENABLE_REQ,(ke_msg_func_t)gattsc_enable_req_handler},
    {GATTSC_SVC_CHANGED_IND_CFG_CMD,(ke_msg_func_t)gattsc_svc_changed_ind_cfg_cmd_handler},
    {GATTC_EVENT_REQ_IND,(ke_msg_func_t)gattc_event_req_ind_handler},
};

const struct ke_state_handler gattsc_default_handler = KE_STATE_HANDLER(gattsc_default_state);

#endif
