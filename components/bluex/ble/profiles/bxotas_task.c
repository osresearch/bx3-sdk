/**
 ****************************************************************************************
 *
 * @file bxotas_task.c
 *
 * @brief Apollo BLE OTA Service Task implementation.
 *
 * Copyright (C) Apollo 2015-2016
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup BXOTASTASK
 * @{
 ****************************************************************************************
 */
 /*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#if (BLE_BXOTA_SERVER)
#include <string.h>
#include "bxotas.h"
#include "gattc_task.h"
#include "bx_dbg.h"
#include "bxotas.h"
#include "bxotas_task.h"
#include "prf.h"
#include "prf_utils.h"
#include "log.h"
#include "ota_image.h"

#include "bx_shell.h"

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

static uint8_t bxotas_get_att_db_idx_from_handle(struct bxotas_env_tag *bxotas_env,uint16_t handle)
{
    return handle -bxotas_env->start_hdl;
}

static int gattc_read_req_ind_handler(ke_msg_id_t const msgid,
                                      struct gattc_read_req_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    uint8_t att_db_idx = bxotas_get_att_db_idx_from_handle(bxotas_env,param->handle);
    //LOG(LOG_LVL_INFO,"read ota hdl:%d\n",att_db_idx);
//    bxsh_logln("read ota hdl:%d",att_db_idx);
    switch(att_db_idx)
    {
    case BXOTAS_IDX_DATA_VAL:
    {
        struct gattc_read_cfm *cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM,src_id,dest_id,gattc_read_cfm,sizeof(bxota_data_att_read_t));
        cfm->handle = param->handle;
        cfm->length = sizeof(bxota_data_att_read_t);
        cfm->status = ATT_ERR_NO_ERROR;
        memcpy(cfm->value,&bxotas_env->ack,sizeof(bxota_data_att_read_t));
        ke_msg_send(cfm);
    }
    case BXOTAS_IDX_CTRL_IND_CFG:
    {
        struct gattc_read_cfm *cfm = KE_MSG_ALLOC_DYN(GATTC_READ_CFM,src_id,dest_id,gattc_read_cfm,sizeof(bxota_data_att_read_t));
        cfm->handle = param->handle;
        cfm->status = ATT_ERR_NO_ERROR;
        ke_msg_send(cfm);

    }
    break;
    default:
    break;
    }

    return KE_MSG_CONSUMED;
}

static bool request_validity_check(uint8_t task_state,struct bxotas_env_tag *bxotas_env,uint8_t conidx)
{
    return task_state == BXOTAS_BUSY && bxotas_env->conidx == conidx;
}

static void bxotas_start_req_ind_send(struct bxotas_env_tag *bxotas_env,ke_task_id_t src_id)
{
    ke_task_id_t dest_id = prf_dst_task_get(&bxotas_env->prf_env,bxotas_env->conidx);
    struct bxotas_start_req_ind *ind = KE_MSG_ALLOC(BXOTAS_START_REQ_IND,dest_id,src_id, bxotas_start_req_ind);
    ind->conidx = bxotas_env->conidx;
    ind->segment_data_max_length = bxotas_env->segment_data_length;
    ke_msg_send(ind);
}

static void bxotas_finish_ind_send(struct bxotas_env_tag *bxotas_env,ke_task_id_t src_id)
{
    ke_task_id_t dest_id = prf_dst_task_get(&bxotas_env->prf_env,bxotas_env->conidx);
    ke_msg_send_basic(BXOTAS_FINISH_IND,dest_id,src_id);
}

static void bxtoas_new_block_ind_send(struct bxotas_env_tag *bxotas_env,uint16_t block_id,ke_task_id_t src_id)
{
    ke_task_id_t dest_id = prf_dst_task_get(&bxotas_env->prf_env,bxotas_env->conidx);
    struct bxotas_new_block_ind *ind = KE_MSG_ALLOC(BXOTAS_NEW_BLOCK_IND,dest_id,src_id,bxotas_new_block_ind);
    ind->block_id = block_id;
    ke_msg_send(ind);
}

static uint8_t ctrl_pkt_dispatch(bxota_ctrl_t *ctrl,ke_task_id_t task_id,uint8_t state,uint8_t conidx)
{
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    uint8_t status;
    switch(ctrl->type)
    {
    case OTA_START_REQ:
    {
        if(state == BXOTAS_IDLE)
        {
            ke_state_set(task_id,BXOTAS_REQ);
            bxotas_env->conidx = conidx;
            bxotas_env->segment_data_length     = ctrl->u.start_req.segment_data_max_length;
            bxotas_env->ota_image_content_crc32 = ctrl->u.start_req.image_content_crc32;
            bxotas_env->ota_image_content_size  = ctrl->u.start_req.image_content_legnth;
            bxotas_env->ota_image_full_size     = bxotas_env->ota_image_content_size + sizeof(ota_image_header_t);
            bxotas_start_req_ind_send(bxotas_env,task_id);
            status = ATT_ERR_NO_ERROR;
        }else
        {
            status = PRF_PROC_IN_PROGRESS;
        }
    }
    break;
    case OTA_NEW_BLOCK_CMD:
    {
        bxotas_env->current_block = ctrl->u.new_block.block_id;
        memset(&bxotas_env->ack,0,sizeof(bxotas_env->ack));
        if(bxotas_env->firmware_dest != LOCAL_FLASH)
        {
            bxtoas_new_block_ind_send(bxotas_env,bxotas_env->current_block,task_id);
        }
        status = ATT_ERR_NO_ERROR;
    }
    break;
    case OTA_IMAGE_TRANSFER_FINISH_CMD:
    {
        if(request_validity_check(state,bxotas_env, conidx)==false)
        {
            status = PRF_APP_ERROR;
        }else
        {
            bxotas_image_validation(bxotas_env);
            bxotas_finish_ind_send(bxotas_env,task_id);
            status = ATT_ERR_NO_ERROR;
        }
    }
    break;
    default:
        //LOG(LOG_LVL_WARN,"unknown ctrl pkt type\n");
//        bxsh_logln("unknown ctrl pkt type");
        status = ATT_ERR_INVALID_HANDLE;
    break;
    }
    return status;
}

static void bxotas_gattc_send_evt_cmd(struct bxotas_env_tag *bxotas_env,uint8_t operation,uint16_t *seq_num,uint8_t att_idx,uint8_t *data,uint16_t length)
{
    ke_task_id_t dest_id = KE_BUILD_ID(TASK_GATTC,bxotas_env->conidx);
    ke_task_id_t src_id = prf_src_task_get(&bxotas_env->prf_env,bxotas_env->conidx);
    struct gattc_send_evt_cmd *cmd = KE_MSG_ALLOC_DYN(GATTC_SEND_EVT_CMD,dest_id,src_id,gattc_send_evt_cmd,length);
    cmd->operation = operation;
    cmd->seq_num = (*seq_num)++;
    cmd->handle = bxotas_env->start_hdl + att_idx;
    cmd->length = length;
    memcpy(cmd->value,data,length);
    ke_msg_send(cmd);
}

static void bxotas_start_rsp_indicate(struct bxotas_env_tag *bxotas_env,uint8_t status)
{
    static uint16_t indicate_num = 0;
    bxota_ctrl_t start_rsp = {
        .type = OTA_START_RSP,
        .u.start_rsp = {
            .status = status,
            .ack_map_size = BXOTA_ACK_MAP_SIZE,
        },
    };
    bxotas_gattc_send_evt_cmd(bxotas_env,GATTC_INDICATE,&indicate_num,BXOTAS_IDX_CTRL_VAL,(uint8_t *)&start_rsp,sizeof(start_rsp));
}

static void bxotas_data_rx_ind_send(struct bxotas_env_tag *bxotas_env,uint8_t segment_id,uint8_t const *data,uint8_t data_length,ke_task_id_t const src_id)
{
    ke_task_id_t dest_id = prf_dst_task_get(&bxotas_env->prf_env,bxotas_env->conidx);
    struct bxotas_data_rx_ind *ind = KE_MSG_ALLOC_DYN(BXOTAS_DATA_RX_IND,dest_id,src_id,bxotas_data_rx_ind,data_length);
    ind->segment_id = segment_id;
    ind->data_length = data_length;
    memcpy(ind->data,data,data_length);
    ke_msg_send(ind);
}

static void bxotas_data_ack_bit_set(struct bxotas_env_tag *bxotas_env,uint8_t segment_id)
{
    bxotas_env->ack.ack_map[segment_id / 8] |= 1<< segment_id % 8;
}

static int gattc_write_req_ind_handler(ke_msg_id_t const msgid,
                                       struct gattc_write_req_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    //bxsh_logln("gattc_write_req_ind_handler:%d %d %d",dest_id,src_id,TASK_ID_BXOTAS);
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    uint8_t att_db_idx = bxotas_get_att_db_idx_from_handle(bxotas_env,param->handle);
    uint8_t prf_state = ke_state_get(dest_id);
    uint8_t conidx = KE_IDX_GET(src_id);
    struct gattc_write_cfm *cfm = KE_MSG_ALLOC(GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm);
    cfm->handle = param->handle;
    BX_ASSERT(param->offset == 0);
    switch(att_db_idx)
    {
    case BXOTAS_IDX_CTRL_VAL:
        {
            bxota_ctrl_t ctrl;
            memcpy(&ctrl,param->value,param->length);
            cfm->status = ctrl_pkt_dispatch(&ctrl,dest_id,prf_state,conidx);
       }
       break;
    case BXOTAS_IDX_DATA_VAL:
        {
            if(request_validity_check(prf_state,bxotas_env,conidx))
            {
                uint8_t segment_id = param->value[0];
                //bxsh_logln("segment_id:%d",segment_id);
                //LOG(LOG_LVL_INFO,"%d\n",segment_id);
                uint8_t const *data = &param->value[offsetof(bxota_data_att_rx_t,data)];
                uint8_t length = param->length - sizeof(segment_id);
                if(bxotas_env->firmware_dest == LOCAL_FLASH)
                {
                    bxotas_program_flash(bxotas_env,segment_id,data,length);
                }else
                {
                    bxotas_data_rx_ind_send(bxotas_env,segment_id,data,length,dest_id);
                }
                bxotas_data_ack_bit_set(bxotas_env,segment_id);
                cfm->status = ATT_ERR_NO_ERROR;
            }else
            {
                cfm->status = ATT_ERR_APP_ERROR;
            }
        }
        break;
       case BXOTAS_IDX_CTRL_IND_CFG:
//        bxsh_logln("desc_cfg:%d,%d,%d",att_db_idx,param->length,*param->value);
        //LOG(LOG_LVL_INFO,"desc_cfg:%d,%d,%d\n",att_db_idx,param->length,*param->value);
        cfm->status = ATT_ERR_NO_ERROR;
        break;
    default:
        //LOG(LOG_LVL_WARN,"invalid,%d\n",att_db_idx);
//        bxsh_logln("invalid,%d",att_db_idx);
        cfm->status = ATT_ERR_INVALID_HANDLE;
        break;
    }
    ke_msg_send(cfm);
    return KE_MSG_CONSUMED;
}

static int bxotas_firmware_dest_cmd_handler(ke_msg_id_t const msgid,
                                       struct bxotas_firmware_dest_cmd const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
//    bxsh_logln("bxotas_firmware_dest_cmd_handler");
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    uint8_t state = ke_state_get(dest_id);
    if(state == BXOTAS_IDLE)
    {
        bxotas_env->firmware_dest = param->firmware_dest;
    }
    return KE_MSG_CONSUMED;
}

static int bxotas_start_cfm_handler(ke_msg_id_t const msgid,
                                       struct bxotas_start_cfm const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    bxsh_logln("bxotas_start_cfm_handler");
    struct bxotas_env_tag *bxotas_env = PRF_ENV_GET(BXOTAS,bxotas);
    uint8_t state = ke_state_get(dest_id);
    if(state == BXOTAS_REQ)
    {
        if(param->status == OTA_REQ_ACCEPTED)
        {
            if(bxotas_env->firmware_dest == LOCAL_FLASH)
            {
                bxotas_flash_cleanup_for_ota(bxotas_env);
            }
            ke_state_set(dest_id,BXOTAS_BUSY);
        }else
        {
            ke_state_set(dest_id,BXOTAS_IDLE);
        }
        bxotas_start_rsp_indicate(bxotas_env,param->status);
    }
    return KE_MSG_CONSUMED;
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler bxotas_default_state[] =
{
    {GATTC_WRITE_REQ_IND,      (ke_msg_func_t)gattc_write_req_ind_handler},
    {GATTC_READ_REQ_IND,      (ke_msg_func_t)gattc_read_req_ind_handler},
    {BXOTAS_FIRMWARE_DEST_CMD, (ke_msg_func_t)bxotas_firmware_dest_cmd_handler},
    {BXOTAS_START_CFM,    (ke_msg_func_t)bxotas_start_cfm_handler},

};

///Specifies the message handlers that are common to all states.
const struct ke_state_handler bxotas_default_handler = KE_STATE_HANDLER(bxotas_default_state);


#endif // BLE_BXOTA_SERVER
/// }@ BXOTASTASK
