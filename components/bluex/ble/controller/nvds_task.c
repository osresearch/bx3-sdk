
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
#include "bx_config.h"
#include <stddef.h>
#include <string.h>
#include "nvds_task.h"
#include "ke_task.h"
#include "ke_msg.h"
#include "nvds_in_ram.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
#if ( LOCAL_NVDS == 0 )
static const struct ke_msg_handler nvds_default_state[]=
{
    {KE_MSG_DEFAULT_HANDLER,(ke_msg_func_t)nvds_default_msg_handler},
    {NVDS_SET_DATA_CMD,(ke_msg_func_t)nvds_set_data_cmd_handler},
};

static const struct ke_state_handler nvds_default_handler = KE_STATE_HANDLER(nvds_default_state);

static ke_state_t nvds_state[NVDS_IDX_MAX];

static const struct ke_task_desc TASK_DESC_NVDS = 
{NULL,&nvds_default_handler,nvds_state,NVDS_STATE_MAX,NVDS_IDX_MAX};

#endif /* ( LOCAL_NVDS == 0 ) */

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

#if ( LOCAL_NVDS == 0 )
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int nvds_default_msg_handler(ke_msg_id_t const msgid, void *event,
        ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    return (KE_MSG_CONSUMED);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int nvds_set_data_cmd_handler(ke_msg_id_t const msgid, struct nvds_set_data_cmd const *cmd,
        ke_task_id_t const dest_id, ke_task_id_t const src_id)
{
    nvds_ram_buf_init(cmd->nvds,cmd->length);
    ke_state_set(TASK_NVDS,NVDS_READY);
    return (KE_MSG_CONSUMED);
}
#endif /* ( LOCAL_NVDS == 0 ) */
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

#if ( LOCAL_NVDS == 0 )
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void nvds_ram_buf_init(uint8_t const *data,uint16_t length);
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void nvds_task_init()
{
    ke_task_create(TASK_NVDS,&TASK_DESC_NVDS);
    ke_state_set(TASK_NVDS,NVDS_EMPTY);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void nvds_data_put_ind_send(uint8_t name,uint8_t *data,uint16_t length)
{
    uint8_t state = ke_state_get(TASK_NVDS);
    if(state == NVDS_READY)
    {
        struct nvds_data_put_ind *ind = KE_MSG_ALLOC_DYN(NVDS_DATA_PUT_IND,TASK_AHI,TASK_NVDS,nvds_data_put_ind,length);
        ind->length = length;
        ind->tag_name = name;
        memcpy(ind->data,data,length);
        ke_msg_send(ind);        
    }

}
#endif /* ( LOCAL_NVDS == 0 ) */
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

