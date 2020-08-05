#include "rwip_config.h"

#if (BLE_GATTS_CLIENT)
#include "gattsc.h"
#include "gattsc_task.h"
#include "prf_utils.h"
#include "ke_mem.h"
static uint8_t gattsc_init(struct prf_task_env* env, uint16_t* start_hdl, uint16_t app_task, uint8_t sec_lvl,  void* params)
{
    struct gattsc_env_tag *gattsc_env = (struct gattsc_env_tag *)ke_malloc(sizeof(struct gattsc_env_tag),KE_MEM_ATT_DB);
    
    env->env = &gattsc_env->prf_env;
    gattsc_env->prf_env.app_task = app_task
            | (PERM_GET(sec_lvl, SVC_MI) ? PERM(PRF_MI, ENABLE) : PERM(PRF_MI, DISABLE));
    gattsc_env->prf_env.prf_task = env->task | PERM(PRF_MI, ENABLE);
    
    env->id = TASK_ID_GATTSC;
    env->desc.idx_max = GATTSC_IDX_MAX;
    env->desc.state = gattsc_env->state;
    env->desc.default_handler = &gattsc_default_handler;
    
    uint8_t idx;
    for(idx = 0; idx < GATTSC_IDX_MAX ; ++idx)
    {
        gattsc_env->env[idx] = NULL;
    }
    
    return GAP_ERR_NO_ERROR;
}

static void gattsc_destroy(struct prf_task_env* env)
{

    struct gattsc_env_tag* gattsc_env = (struct gattsc_env_tag*) env->env;
    uint8_t idx;
    // cleanup environment variable for each task instances
    for(idx = 0; idx < GATTSC_IDX_MAX ; idx++)
    {
        if(gattsc_env->env[idx] != NULL)
        {
            ke_free(gattsc_env->env[idx]);
        }
    }

    // free profile environment variables
    env->env = NULL;
    ke_free(gattsc_env);    
    
}

static void gattsc_create(struct prf_task_env* env, uint8_t conidx)
{
    ke_state_set(KE_BUILD_ID(env->task,conidx),GATTSC_IDLE);
    
}

static void gattsc_cleanup(struct prf_task_env* env, uint8_t conidx, uint8_t reason)
{
    struct gattsc_env_tag *gattsc_env = (struct gattsc_env_tag*)env->env;
    if(gattsc_env->env[conidx])
    {
        ke_free(gattsc_env->env[conidx]);
        gattsc_env->env[conidx] = NULL;
    }
    
    ke_state_set(KE_BUILD_ID(env->task,conidx),GATTSC_NONE);
}

void gattsc_enable_rsp_send(struct gattsc_env_tag *gattsc_env,uint8_t conidx,uint8_t status,bool env_free)
{
    ke_task_id_t src_id = prf_src_task_get(&(gattsc_env->prf_env), conidx);
    struct gattsc_enable_rsp *rsp = KE_MSG_ALLOC(GATTSC_ENABLE_RSP,   
        prf_dst_task_get(&(gattsc_env->prf_env), conidx),src_id,
        gattsc_enable_rsp);
    rsp->status = status;
    if(status == GAP_ERR_NO_ERROR)
    {
        rsp->gatts = gattsc_env->env[conidx]->gatts;
        prf_unregister_atthdl2gatt(&gattsc_env->prf_env,conidx,&gattsc_env->env[conidx]->gatts.svc);
        prf_register_atthdl2gatt(&gattsc_env->prf_env,conidx,&gattsc_env->env[conidx]->gatts.svc);
    }else if(gattsc_env->env[conidx]&&env_free)
    {
        ke_free(gattsc_env->env[conidx]);
        gattsc_env->env[conidx] = NULL;
    }
    ke_msg_send(rsp);

}

void gattsc_cmp_evt_send(struct gattsc_env_tag *gattsc_env,uint8_t conidx,uint8_t operation,uint8_t status)
{
    ke_task_id_t src_id = prf_src_task_get(&(gattsc_env->prf_env), conidx);
    ke_task_id_t dst_id = prf_dst_task_get(&(gattsc_env->prf_env), conidx);
    struct gattsc_cmp_evt *evt = KE_MSG_ALLOC(GATTSC_CMP_EVT, dst_id, src_id, gattsc_cmp_evt);
    evt->operation = operation;
    evt->status = status;
    ke_msg_send(evt);
}



const struct prf_task_cbs gattsc_itf =
{
    gattsc_init,
    gattsc_destroy,
    gattsc_create,
    gattsc_cleanup,
};

const struct prf_task_cbs *gattsc_prf_itf_get()
{
    return &gattsc_itf;
}


#endif
