#ifndef CTSC_H_
#define CTSC_H_

#include "rwip_config.h"
#if (BLE_CTS_CLIENT)
#include <stdint.h>
#include <stdbool.h>
#include "ke_task.h"
#include "prf_utils.h"
#include "ctsc_task.h"
#include "gattc_task.h"
#define CTSC_IDX_MAX (BLE_USER_CONN_NUM)

struct ctsc_cnx_env
{
    struct ctsc_cts_content cts;
};

struct ctsc_env_tag
{
    prf_env_t prf_env;
    struct ctsc_cnx_env *env[CTSC_IDX_MAX];
    ke_state_t state[CTSC_IDX_MAX];
};

void ctsc_enable_rsp_send(struct ctsc_env_tag *ctsc_env,uint8_t conidx,uint8_t status,bool env_free);

void ctsc_current_time_ind_send(struct ctsc_env_tag *ctsc_env,uint8_t conidx,struct gattc_read_ind const*ind);

void ctsc_cmp_evt_send(struct ctsc_env_tag *ctsc_env,uint8_t conidx,uint8_t operation,uint8_t status);

#endif
#endif
