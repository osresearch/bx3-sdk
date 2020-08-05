#include "rwip_config.h"

#if (BLE_ANC_CLIENT)
#include "ancc.h"
#include "ancc_task.h"
#include "prf_utils.h"
#include "ke_mem.h"
static uint8_t ancc_init(struct prf_task_env* env, uint16_t* start_hdl, uint16_t app_task, uint8_t sec_lvl,  void* params)
{
    struct ancc_env_tag *ancc_env = (struct ancc_env_tag *)ke_malloc(sizeof(struct ancc_env_tag),KE_MEM_ATT_DB);
    
    env->env = &ancc_env->prf_env;
    ancc_env->prf_env.app_task = app_task
            | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
    ancc_env->prf_env.prf_task = env->task | PERM(PRF_MI, ENABLE);
    
    env->id = TASK_ID_ANCC;
    env->desc.idx_max = ANCC_IDX_MAX;
    env->desc.state = ancc_env->state;
    env->desc.default_handler = &ancc_default_handler;
    
    uint8_t idx;
    for(idx = 0; idx < ANCC_IDX_MAX ; ++idx)
    {
        ancc_env->env[idx] = NULL;
    }
    
    return GAP_ERR_NO_ERROR;
}

static void ancc_destroy(struct prf_task_env* env)
{

    struct ancc_env_tag* ancc_env = (struct ancc_env_tag*) env->env;
    uint8_t idx;
    // cleanup environment variable for each task instances
    for(idx = 0; idx < ANCC_IDX_MAX ; idx++)
    {
        if(ancc_env->env[idx] != NULL)
        {
            ke_free(ancc_env->env[idx]);
        }
    }

    // free profile environment variables
    env->env = NULL;
    ke_free(ancc_env);    
    
}

static void ancc_create(struct prf_task_env* env, uint8_t conidx)
{
    ke_state_set(KE_BUILD_ID(env->task,conidx),ANCC_IDLE);
    
}

static void ancc_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    struct ancc_env_tag *ancc_env = (struct ancc_env_tag*)env->env;
    if(ancc_env->env[conidx])
    {
        ke_free(ancc_env->env[conidx]);
        ancc_env->env[conidx] = NULL;
    }
    
    ke_state_set(KE_BUILD_ID(env->task,conidx),ANCC_NONE);
}

void ancc_enable_rsp_send(struct ancc_env_tag *ancc_env,uint8_t conidx,uint8_t status,bool env_free)
{
    ke_task_id_t dst = prf_dst_task_get(&(ancc_env->prf_env), conidx);
    ke_task_id_t src = prf_src_task_get(&(ancc_env->prf_env), conidx);
    struct ancc_enable_rsp *rsp = KE_MSG_ALLOC(ANCC_ENABLE_RSP,dst,src,ancc_enable_rsp);
    rsp->status = status;
    if(status == GAP_ERR_NO_ERROR)
    {
        rsp->anc = ancc_env->env[conidx]->anc;
        prf_unregister_atthdl2gatt(&ancc_env->prf_env,conidx,&ancc_env->env[conidx]->anc.svc);
        prf_register_atthdl2gatt(&ancc_env->prf_env,conidx,&ancc_env->env[conidx]->anc.svc);
    }else if(ancc_env->env[conidx]&&env_free)
    {
        ke_free(ancc_env->env[conidx]);
        ancc_env->env[conidx] = NULL;
    }
    ke_msg_send(rsp);
}

void ancc_ntf_src_ind_send(struct ancc_env_tag *ancc_env,uint8_t conidx,const uint8_t *data)
{
    struct anc_ntf_src *ind = KE_MSG_ALLOC(ANCC_NTF_SRC_IND,prf_dst_task_get(&(ancc_env->prf_env), conidx),
        prf_src_task_get(&(ancc_env->prf_env), conidx),anc_ntf_src);
    memcpy(ind,data,sizeof(struct anc_ntf_src));
    ke_msg_send(ind);
}

void ancc_cmp_evt_send(struct ancc_env_tag *ancc_env,uint8_t conidx,uint8_t operation,uint8_t status)
{
    ke_task_id_t src_id = prf_src_task_get(&(ancc_env->prf_env), conidx);
    struct ancc_cmp_evt *evt = KE_MSG_ALLOC(ANCC_CMP_EVT,prf_dst_task_get(&(ancc_env->prf_env), conidx),
        src_id,ancc_cmp_evt);
    evt->id = ancc_env->env[conidx]->data_src_rx_env.id;
    evt->operation = operation;
    evt->status = status;
    ke_msg_send(evt);    
    ke_state_set(src_id, ANCC_IDLE);
}

void ancc_att_ind_msg_prepare(struct ancc_env_tag *ancc_env,uint8_t conidx,ancc_data_src_rx_env_t *env)
{
    struct ancc_att_ind *ind = KE_MSG_ALLOC_DYN(env->cmd_id == CMD_ID_GET_NTF_ATTS ? ANCC_NTF_ATT_IND : ANCC_APP_ATT_IND,
        prf_dst_task_get(&(ancc_env->prf_env), conidx),prf_src_task_get(&(ancc_env->prf_env), conidx),
        ancc_att_ind,env->att_length);
    ind->length = env->att_length;
    ind->att_id = env->att_id;
    ind->id = env->id;
    env->ind = ind;
}

void ancc_att_ind_send(ancc_data_src_rx_env_t *env)
{
    ke_msg_send(env->ind);
    env->ind = NULL;
}

const struct prf_task_cbs ancc_itf =
{
    ancc_init,
    ancc_destroy,
    ancc_create,
    ancc_cleanup,
};

const struct prf_task_cbs *ancc_prf_itf_get()
{
    return &ancc_itf;
}


#endif
