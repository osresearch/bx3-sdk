#ifndef ANCC_H_
#define ANCC_H_
#include "rwip_config.h"
#if (BLE_ANC_CLIENT)
#include <stdint.h>
#include <stdbool.h>
#include "ke_task.h"
#include "prf_utils.h"
#include "ancc_task.h"

#define ANCC_IDX_MAX (BLE_CONNECTION_MAX)

enum ancc_data_src_rx_stage
{
    ATT_RSP_RX_CMD_ID,
    ATT_RSP_RX_NTF_UID,
    ATT_RSP_RX_APP_ID,
    ATT_RSP_RX_ATT_ID,
    ATT_RSP_RX_LENGTH_BYTE0,
    ATT_RSP_RX_LENGTH_BYTE1,
    ATT_RSP_RX_DATA,
};

typedef struct
{
    struct ancc_att_ind *ind;
    ancc_id_u id;
    uint16_t att_mask;
    uint16_t att_id;
    uint16_t att_length;
    uint16_t ind_offset;
    uint8_t cmd_id;
    uint8_t app_id_offset;
    enum ancc_data_src_rx_stage stage;    
}ancc_data_src_rx_env_t;

struct ancc_cnx_env
{
    struct ancc_anc_content anc;
    ancc_data_src_rx_env_t data_src_rx_env;
};

struct ancc_env_tag
{
    prf_env_t prf_env;
    struct ancc_cnx_env *env[ANCC_IDX_MAX];
    ke_state_t state[ANCC_IDX_MAX];
    
};
    


void ancc_enable_rsp_send(struct ancc_env_tag *ancc_env,uint8_t conidx,uint8_t status,bool env_free);

void ancc_ntf_src_ind_send(struct ancc_env_tag *ancc_env,uint8_t conidx,const uint8_t *data);

void ancc_cmp_evt_send(struct ancc_env_tag *ancc_env,uint8_t conidx,uint8_t operation,uint8_t status);

void ancc_att_ind_msg_prepare(struct ancc_env_tag *ancc_env,uint8_t conidx,ancc_data_src_rx_env_t *env);

void ancc_att_ind_send(ancc_data_src_rx_env_t *env);





#endif
#endif
