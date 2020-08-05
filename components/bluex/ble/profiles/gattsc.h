#ifndef GATTSC_H_
#define GATTSC_H_
#include "rwip_config.h"
#if (BLE_GATTS_CLIENT)
#include <stdint.h>
#include <stdbool.h>
#include "ke_task.h"
#include "prf_utils.h"
#include "gattsc_task.h"

#define GATTSC_IDX_MAX (BLE_USER_CONN_NUM)

struct gattsc_cnx_env
{
    struct gatts_client_content gatts;
    uint8_t nb_svc;
};

struct gattsc_env_tag
{
    prf_env_t prf_env;
    struct gattsc_cnx_env *env[GATTSC_IDX_MAX];
    ke_state_t state[GATTSC_IDX_MAX];
    
};

void gattsc_enable_rsp_send(struct gattsc_env_tag *gattsc_env,uint8_t conidx,uint8_t status,bool env_free);

void gattsc_cmp_evt_send(struct gattsc_env_tag *gattsc_env,uint8_t conidx,uint8_t operation,uint8_t status);

#endif
#endif
