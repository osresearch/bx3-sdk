#include "rwip_config.h"


#if (BLE_ANC_CLIENT)
#include <string.h>
#include "ancc_task.h"
#include "ancc.h"
#include "prf_utils.h"
#include "prf_types.h"

#include "log.h"


#define ATT_DESC_CLIENT_CHAR_CFG_ARRAY {0x02,0x29}

#define ANC_SVC_UUID_128 {0xd0,0x00,0x2d,0x12,0x1e,0x4b,0x0f,0xa4, 0x99,0x4e, 0xce,0xb5,0x31,0xf4,0x05,0x79}

const uint8_t anc_svc_uuid[] = ANC_SVC_UUID_128;

const struct prf_char_uuid128_def ancc_anc_char[ANC_CHAR_MAX] =
{
    [ANC_CHAR_NTF_SRC] = {
        .uuid_len = ATT_UUID_128_LEN,
        .uuid = {0xBD, 0x1D, 0xA2, 0x99, 0xE6, 0x25, 0x58, 0x8C, 0xD9, 0x42, 0x01, 0x63, 0x0D, 0x12, 0xBF, 0x9F},
        .req_flag = ATT_MANDATORY,
        .prop_mand = ATT_CHAR_PROP_NTF,
        },
    [ANC_CHAR_CTRL_PT] = {
        .uuid_len = ATT_UUID_128_LEN,
        .uuid = {0xD9, 0xD9, 0xAA, 0xFD, 0xBD, 0x9B, 0x21, 0x98, 0xA8, 0x49, 0xE1, 0x45, 0xF3, 0xD8, 0xD1, 0x69},
        .req_flag = ATT_OPTIONAL,
        .prop_mand = ATT_CHAR_PROP_WR,
        },
    [ANC_CHAR_DATA_SRC] = {
        .uuid_len = ATT_UUID_128_LEN,
        .uuid = {0xFB, 0x7B, 0x7C, 0xCE, 0x6A, 0xB3, 0x44, 0xBE, 0xB5, 0x4B, 0xD6, 0x24, 0xE9, 0xC6, 0xEA, 0x22},
        .req_flag = ATT_OPTIONAL,
        .prop_mand = ATT_CHAR_PROP_NTF,
        },
};

const struct prf_char_desc_uuid128_def ancc_anc_char_desc[ANC_DESC_MAX] = 
{
    [ANC_DESC_NTF_SRC_CL_CFG] = {ATT_UUID_16_LEN,ATT_DESC_CLIENT_CHAR_CFG_ARRAY,ATT_MANDATORY,ANC_CHAR_NTF_SRC},
    [ANC_DESC_DATA_SRC_CL_CFG] = {ATT_UUID_16_LEN,ATT_DESC_CLIENT_CHAR_CFG_ARRAY,ATT_OPTIONAL,ANC_CHAR_DATA_SRC},
};

static int ancc_enable_req_handler(ke_msg_id_t const msgid,
    struct ancc_enable_req const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
 
    uint8_t state = ke_state_get(dest_id);
    uint8_t conidx = KE_IDX_GET(dest_id);
    // Apple Notification Centre Client Role Task Environment
    struct ancc_env_tag *ancc_env = PRF_ENV_GET(ANCC,ancc);   
    ASSERT_INFO(ancc_env != NULL, dest_id, src_id);
    if(state == ANCC_IDLE)
    {
        if(ancc_env->env[conidx] == NULL)
        {
            // allocate environment variable for task instance
            ancc_env->env[conidx] = (struct ancc_cnx_env*) ke_malloc(sizeof(struct ancc_cnx_env),KE_MEM_ATT_DB);
            memset(ancc_env->env[conidx], 0, sizeof(struct ancc_cnx_env));
        }
        //Config connection, start discovering
        if(param->con_type == PRF_CON_DISCOVERY)
        {
            //start discovering ANC Server on peer
            prf_disc_svc_128_send(&ancc_env->prf_env, conidx, anc_svc_uuid);
            // Go to DISCOVERING state
            ke_state_set(dest_id, ANCC_DISCOVERING);
        }else
        {
            ancc_env->env[conidx]->anc = param->anc;
            
            ancc_enable_rsp_send(ancc_env,conidx,GAP_ERR_NO_ERROR,true);
        }
    }else if(state != ANCC_DISCOVERING && state != ANCC_NONE)
    {
        ancc_enable_rsp_send(ancc_env,conidx,PRF_ERR_REQ_DISALLOWED,false);
    }
    
    return (KE_MSG_CONSUMED);
}

static int gattc_sdp_svc_ind_handler(ke_msg_id_t const msgid,
    struct gattc_sdp_svc_ind const *ind,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);

    if(state == ANCC_DISCOVERING)
    {
        uint8_t conidx = KE_IDX_GET(dest_id);
        // Get the address of the environment
        struct ancc_env_tag *ancc_env = PRF_ENV_GET(ANCC, ancc);

        ASSERT_INFO(ancc_env != NULL, dest_id, src_id);
        ASSERT_INFO(ancc_env->env[conidx] != NULL, dest_id, src_id);

        // Retrieve ANC characteristics
        prf_extract_svc_uuid128_info(ind, ANC_CHAR_MAX, ancc_anc_char,ancc_env->env[conidx]->anc.chars,   ANC_DESC_MAX,ancc_anc_char_desc,ancc_env->env[conidx]->anc.descs);

        //Even if we get multiple responses we only store 1 range
        ancc_env->env[conidx]->anc.svc.shdl = ind->start_hdl;
        ancc_env->env[conidx]->anc.svc.ehdl = ind->end_hdl;

    }

    return (KE_MSG_CONSUMED);
}

static int gattc_cmp_evt_handler(ke_msg_id_t const msgid,
    struct gattc_cmp_evt const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);
    // Get the address of the environment
    struct ancc_env_tag *ancc_env = PRF_ENV_GET(ANCC, ancc);
    uint8_t conidx = KE_IDX_GET(dest_id);

    uint8_t status = param->status;
    switch(state)
    {
    case ANCC_DISCOVERING:
        if (param->status == ATT_ERR_NO_ERROR)
        {
            status = prf_check_svc_char_uuid128_validity(ANC_CHAR_MAX, ancc_env->env[conidx]->anc.chars,ancc_anc_char);
            
            // check descriptor validity
            if (status == GAP_ERR_NO_ERROR)
            {
                status = prf_check_svc_char_desc_uuid128_validity(ANC_DESC_MAX,ancc_env->env[conidx]->anc.descs,ancc_anc_char_desc,ancc_env->env[conidx]->anc.chars);
            }
        }
        
        ancc_enable_rsp_send(ancc_env, conidx, status,true);
        ke_state_set(dest_id, ANCC_IDLE);
    break;
    case ANCC_NTF_SRC_CL_CFG_NTF_DISABLING:
    case ANCC_DATA_SRC_CL_CFG_NTF_DISABLING:
    case ANCC_NTF_SRC_CL_CFG_NTF_ENABLING:
    case ANCC_DATA_SRC_CL_CFG_NTF_ENABLING:
    case ANCC_NTF_ACTION_REQUESTING:
        if(param->operation == GATTC_WRITE)
        {
            ancc_cmp_evt_send(ancc_env,conidx,state,status);
        }
    break;
    case ANCC_NTF_ATTS_REQUESTING:
    case ANCC_APP_ATTS_REQUESTING:
        if(param->operation == GATTC_WRITE && status!=GAP_ERR_NO_ERROR)
        {
            ancc_cmp_evt_send(ancc_env,conidx,state,status);
        }
    break;
    case ANCC_IDLE:
        BX_ASSERT(param->operation == GATTC_REGISTER && param->status == GAP_ERR_NO_ERROR 
                || param->operation == GATTC_UNREGISTER);
    break;
    default:
        LOG(LOG_LVL_WARN,"state:%d,gattc_cmp_evt,%d,%d\n",state,param->operation,param->status);
    break;
    }

    return (KE_MSG_CONSUMED);
}

static int ancc_cmd_return_status(uint8_t task_state)
{
    int status;
    switch(task_state)
    {
    case ANCC_NONE:
    case ANCC_IDLE:
    case ANCC_DISCOVERING:
        status = KE_MSG_CONSUMED;
    break;
    case ANCC_NTF_SRC_CL_CFG_NTF_ENABLING:
    case ANCC_NTF_SRC_CL_CFG_NTF_DISABLING:
    case ANCC_DATA_SRC_CL_CFG_NTF_DISABLING:
    case ANCC_DATA_SRC_CL_CFG_NTF_ENABLING:
    case ANCC_NTF_ATTS_REQUESTING:
    case ANCC_APP_ATTS_REQUESTING:
    case ANCC_NTF_ACTION_REQUESTING:
        status = KE_MSG_SAVED;
    break;
    }
    return status;
}

static int ancc_cl_cfg_ntf_en_cmd_handler(ke_msg_id_t const msgid,
    struct ancc_cl_cfg_ntf_en_cmd const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);
    struct ancc_env_tag *ancc_env = PRF_ENV_GET(ANCC, ancc);
    uint8_t conidx = KE_IDX_GET(dest_id);
    if(state == ANCC_IDLE)
    {
        prf_gatt_write_ntf_ind(&ancc_env->prf_env,conidx,ancc_env->env[conidx]->anc.descs[param->cfg].desc_hdl,param->enable ? PRF_CLI_START_NTF : PRF_CLI_STOP_NTFIND);
        uint8_t next_state;
        if(param->cfg == ANC_DESC_NTF_SRC_CL_CFG)
        {
            if(param->enable)
            {
                next_state = ANCC_NTF_SRC_CL_CFG_NTF_ENABLING;
            }else
            {
                next_state = ANCC_NTF_SRC_CL_CFG_NTF_DISABLING;
            }
        }else
        {
            if(param->enable)
            {
                next_state = ANCC_DATA_SRC_CL_CFG_NTF_ENABLING;
            }else
            {
                next_state = ANCC_DATA_SRC_CL_CFG_NTF_DISABLING;
            }
        }
        ke_state_set(dest_id, next_state);
    }
    return ancc_cmd_return_status(state);
}

static void ancc_data_rx_stage_set(ancc_data_src_rx_env_t *env,enum ancc_data_src_rx_stage stage)
{
    env->stage = stage;
    if(stage == ATT_RSP_RX_APP_ID)
    {
        env->app_id_offset = 0;
    }
    if(stage == ATT_RSP_RX_ATT_ID)
    {
        env->att_id = 0;
    }
    if(stage == ATT_RSP_RX_LENGTH_BYTE0)
    {
        env->att_length = 0;
    }
    if(stage == ATT_RSP_RX_DATA)
    {
        env->ind_offset = 0;
    }
}

static bool pending_att(ancc_data_src_rx_env_t *env)
{
    uint8_t max = env->cmd_id == CMD_ID_GET_NTF_ATTS? NTF_ATT_ID_NB : APP_ATT_ID_NB;
    uint8_t i;
    for(i=env->att_id+1;i<max;++i)
    {
        if(env->att_mask&1<<i)
        {
            return true;
        }
    }
    return false;
}

static void att_ind_and_new_stage(struct ancc_env_tag *ancc_env,uint8_t conidx,uint8_t state)
{
    ancc_data_src_rx_env_t *env = &ancc_env->env[conidx]->data_src_rx_env;
    ancc_att_ind_send(env);
    if(pending_att(env)==false)
    {
        ancc_data_rx_stage_set(env,ATT_RSP_RX_CMD_ID);
        ancc_cmp_evt_send(ancc_env,conidx,state,GAP_ERR_NO_ERROR);
    }else
    {
        ancc_data_rx_stage_set(env,ATT_RSP_RX_ATT_ID);
    }    
    
}

static int gattc_event_ind_handler(ke_msg_id_t const msgid,
    struct gattc_event_ind const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    struct ancc_env_tag *ancc_env = PRF_ENV_GET(ANCC, ancc);
    uint8_t conidx = KE_IDX_GET(dest_id);
    if(param->handle == ancc_env->env[conidx]->anc.chars[ANC_CHAR_NTF_SRC].val_hdl)
    {
        ancc_ntf_src_ind_send(ancc_env,conidx,param->value);
    }else if(param->handle == ancc_env->env[conidx]->anc.chars[ANC_CHAR_DATA_SRC].val_hdl)
    {
        uint8_t state = ke_state_get(dest_id);
        uint16_t i=0;
        ancc_data_src_rx_env_t *env = &ancc_env->env[conidx]->data_src_rx_env;
        while(i<param->length)
        {
            switch(env->stage)
            {
            case ATT_RSP_RX_CMD_ID:
            {
                env->cmd_id = param->value[i++];
                if(env->cmd_id == CMD_ID_GET_NTF_ATTS)
                {
                    BX_ASSERT(state == ANCC_NTF_ATTS_REQUESTING);
                    ancc_data_rx_stage_set(env,ATT_RSP_RX_NTF_UID);
                }else if(env->cmd_id == CMD_ID_GET_APP_ATTS)
                {
                    BX_ASSERT(state == ANCC_APP_ATTS_REQUESTING);
                    ancc_data_rx_stage_set(env,ATT_RSP_RX_APP_ID);
                }else{
                    BX_ASSERT(0);
                }
            }
            break;
            case ATT_RSP_RX_NTF_UID:
            {
                memcpy(&env->id.ntf_uid,&param->value[i],sizeof(uint32_t));
                i+= sizeof(uint32_t);
                ancc_data_rx_stage_set(env,ATT_RSP_RX_ATT_ID);
            }
            break;
            case ATT_RSP_RX_APP_ID:
            {
                if(param->value[i]=='\0')
                {
                    ancc_data_rx_stage_set(env,ATT_RSP_RX_ATT_ID);
                }
                env->id.app_id.str[env->app_id_offset++]=param->value[i++];
            }
            break;
            case ATT_RSP_RX_ATT_ID:
            {
                env->att_id = param->value[i++];
                BX_ASSERT(env->att_mask&1<<env->att_id);
                ancc_data_rx_stage_set(env,ATT_RSP_RX_LENGTH_BYTE0);
            }
            break;
            case ATT_RSP_RX_LENGTH_BYTE0:
            {
                env->att_length = param->value[i++];
                ancc_data_rx_stage_set(env,ATT_RSP_RX_LENGTH_BYTE1);
            }
            break;
            case ATT_RSP_RX_LENGTH_BYTE1:
            {
                env->att_length |= param->value[i++]<<8;
                ancc_att_ind_msg_prepare(ancc_env,conidx,env);
                if(env->att_length)
                {
                    ancc_data_rx_stage_set(env,ATT_RSP_RX_DATA);
                }else
                {
                    att_ind_and_new_stage(ancc_env,conidx,state);
                }
            }
            break;
            case ATT_RSP_RX_DATA:
            {
                env->ind->val[env->ind_offset++] = param->value[i++];
                if(env->ind_offset == env->att_length)
                {
                    att_ind_and_new_stage(ancc_env,conidx,state);
                }
            }
            break;
            default:
                BX_ASSERT(0);
            break;
            }
        }
        
    }else
    {
        BX_ASSERT(0);
    }

    return (KE_MSG_CONSUMED);
}

static uint8_t get_length_for_ntf_att_id(uint8_t i)
{
    if(i==NTF_ATT_ID_TITLE||i==NTF_ATT_ID_SUBTITLE||i==NTF_ATT_ID_MSG)
    {
        return 3;
    }else
    {
        return 1;
    }
    
}

static int ancc_get_ntf_atts_cmd_handler(ke_msg_id_t const msgid,
    struct ancc_get_ntf_atts_cmd const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);
    if(state == ANCC_IDLE)
    {
        struct ancc_env_tag *ancc_env = PRF_ENV_GET(ANCC, ancc);
        uint8_t conidx = KE_IDX_GET(dest_id);
        uint8_t length = 0;
        uint8_t i;
        for(i=0;i<NTF_ATT_ID_NB;++i)
        {
            if(param->att_mask&1<<i)
            {
                length += get_length_for_ntf_att_id(i);
            }
        }
        uint8_t buf[sizeof(anc_get_ntf_att_pkt_t)+length];
        anc_get_ntf_att_pkt_t *pkt = (anc_get_ntf_att_pkt_t *)buf;
        pkt->cmd_id = CMD_ID_GET_NTF_ATTS;
        pkt->ntf_uid = param->ntf_uid;
        uint8_t *ptr = pkt->att_ids;
        for(i=0;i<NTF_ATT_ID_NB;++i)
        {
            if(param->att_mask&1<<i)
            {   
                *ptr++ = i;
                switch(i)
                {
                case NTF_ATT_ID_TITLE:
                    memcpy(ptr,&param->title_length,sizeof(uint16_t));
                    ptr += 2;
                break;
                case NTF_ATT_ID_SUBTITLE:
                    memcpy(ptr,&param->subtitle_length,sizeof(uint16_t));
                    ptr += 2;
                break;
                case NTF_ATT_ID_MSG:
                    memcpy(ptr,&param->message_length,sizeof(uint16_t));
                    ptr += 2;
                break;
                default:
                
                break;
                }
            }
        }
        ancc_env->env[conidx]->data_src_rx_env.att_mask = param->att_mask;
        prf_gatt_write(&ancc_env->prf_env,conidx,ancc_env->env[conidx]->anc.chars[ANC_CHAR_CTRL_PT].val_hdl,buf,sizeof(buf),GATTC_WRITE);
        ke_state_set(dest_id,ANCC_NTF_ATTS_REQUESTING);
    }
    return ancc_cmd_return_status(state);
}

static int ancc_get_app_atts_cmd_handler(ke_msg_id_t const msgid,
    struct ancc_get_app_atts_cmd const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);
    if(state == ANCC_IDLE)
    { 
        struct ancc_env_tag *ancc_env = PRF_ENV_GET(ANCC, ancc);
        uint8_t conidx = KE_IDX_GET(dest_id);
        uint8_t str_total_size = strlen((char const *)param->app_id.str) + 1;
        uint8_t length = str_total_size;
        uint8_t i;
        for(i=0;i<APP_ATT_ID_NB;++i)
        {
            if(param->att_mask&1<<i)
            {
                length += 1;
            }
        }
        uint8_t buf[sizeof(anc_get_app_att_pkt_t)+length];
        anc_get_app_att_pkt_t *pkt = (anc_get_app_att_pkt_t *)buf;
        pkt->cmd_id = CMD_ID_GET_APP_ATTS;
        strcpy((void*)pkt->app_id_att_id,(void*)param->app_id.str);
        uint8_t *ptr = &pkt->app_id_att_id[str_total_size];
        for(i=0;i<APP_ATT_ID_NB;++i)
        {
            if(param->att_mask&1<<i)
            {
                *ptr++=i;
            }
        }
        ancc_env->env[conidx]->data_src_rx_env.att_mask = param->att_mask;
        prf_gatt_write(&ancc_env->prf_env,conidx,ancc_env->env[conidx]->anc.chars[ANC_CHAR_CTRL_PT].val_hdl,buf,sizeof(buf),GATTC_WRITE);
        ke_state_set(dest_id,ANCC_APP_ATTS_REQUESTING);        
    }
    return ancc_cmd_return_status(state);
}

static int ancc_perform_ntf_action_cmd_handler(ke_msg_id_t const msgid,
    struct ancc_perform_ntf_action_cmd const *param,
    ke_task_id_t const dest_id,
    ke_task_id_t const src_id)
{
    uint8_t state = ke_state_get(dest_id);
    if(state == ANCC_IDLE)
    {
        struct ancc_env_tag *ancc_env = PRF_ENV_GET(ANCC, ancc);
        uint8_t conidx = KE_IDX_GET(dest_id);
        ancc_env->env[conidx]->data_src_rx_env.id.ntf_uid = param->ntf_uid;
        anc_perform_ntf_action_pkt_t pkt = 
        {
            .cmd_id = CMD_ID_PERFORM_NTF_ACTION,
            .ntf_uid = param->ntf_uid,
            .action_id = param->action_id,
        };
        prf_gatt_write(&ancc_env->prf_env,conidx,ancc_env->env[conidx]->anc.chars[ANC_CHAR_CTRL_PT].val_hdl,(uint8_t *)&pkt,sizeof(pkt),GATTC_WRITE);
        ke_state_set(dest_id,ANCC_NTF_ACTION_REQUESTING);
    }
    return ancc_cmd_return_status(state);
}

const struct ke_msg_handler ancc_default_state[] =
{
    {GATTC_CMP_EVT,(ke_msg_func_t)gattc_cmp_evt_handler},
    {GATTC_SDP_SVC_IND,(ke_msg_func_t)gattc_sdp_svc_ind_handler},
    {ANCC_ENABLE_REQ,(ke_msg_func_t)ancc_enable_req_handler},
    {ANCC_CL_CFG_NTF_EN_CMD,(ke_msg_func_t)ancc_cl_cfg_ntf_en_cmd_handler},
    {GATTC_EVENT_IND,(ke_msg_func_t)gattc_event_ind_handler},
    {ANCC_GET_NTF_ATTS_CMD,(ke_msg_func_t)ancc_get_ntf_atts_cmd_handler},
    {ANCC_GET_APP_ATTS_CMD,(ke_msg_func_t)ancc_get_app_atts_cmd_handler},
    {ANCC_PERFORM_NTF_ACTION_CMD,(ke_msg_func_t)ancc_perform_ntf_action_cmd_handler},
};

const struct ke_state_handler ancc_default_handler = KE_STATE_HANDLER(ancc_default_state);

#endif
