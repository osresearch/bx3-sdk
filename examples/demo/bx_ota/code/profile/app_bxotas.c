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

#include "rwip_config.h"     // SW configuration

#if (BLE_BXOTA_SERVER)

#include "app.h" 
#include "app_bxotas.h"                
#include "bxotas_task.h"              
#include "prf_types.h"             
#include "gapm_task.h"        
#include <string.h>
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void app_bxotas_start_req_ind_handler( ke_msg_id_t const msgid, struct bxotas_start_req_ind const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    struct bxotas_start_cfm * cfm = KE_MSG_ALLOC( BXOTAS_START_CFM,
                                    src_id, dest_id,
                                    bxotas_start_cfm );
    cfm->status = OTA_REQ_ACCEPTED;
    ke_msg_send( cfm );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void app_bxotas_finish_ind_handler( ke_msg_id_t const msgid, void const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    u32 time = 1000000;
    while( time-- > 0 ) {
        __asm( "nop" );
    }
    platform_reset( 0 );
}
/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_bxotas_init(void)
{
    // Nothing to do
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_bxotas_add_ota(void)
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
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_bxotas_config(void)
{
    struct bxotas_firmware_dest_cmd *cmd =KE_MSG_ALLOC(BXOTAS_FIRMWARE_DEST_CMD,TASK_ID_GATTC,TASK_APP,bxotas_firmware_dest_cmd);
    
    cmd->firmware_dest = LOCAL_FLASH;
    
    ke_msg_send(cmd);
}
/*========================= end of exported function =========================*/


const struct ke_msg_handler app_bxotas_msg_handler_list[] =
{
    {BXOTAS_START_REQ_IND,      ( ke_msg_func_t )app_bxotas_start_req_ind_handler},
    {BXOTAS_FINISH_IND,         ( ke_msg_func_t )app_bxotas_finish_ind_handler},
};

const struct ke_state_handler app_bxotas_table_handler =
    {&app_bxotas_msg_handler_list[0], (sizeof(app_bxotas_msg_handler_list)/sizeof(struct ke_msg_handler))};

#endif //BLE_APP_DIS

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
