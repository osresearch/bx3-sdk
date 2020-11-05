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

#include "bx_kernel.h"
#include "user_common_api.h"

#include "gapc_task.h"
#include "gapm_task.h"
#include "ke_timer.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

/*============================= private function =============================*/



/** ---------------------------------------------------------------------------
 * @brief   :Software reset or platform reset
 * @note    :
 * @param   :GAPM_RESET: Software reset;GAPM_PLF_RESET: Platform reset
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t Sys_Reset(uint8_t op_code)
{
	struct gapm_reset_cmd * reset_cmd = KE_MSG_ALLOC( GAPM_RESET_CMD,
													TASK_GAPM, TASK_APP,
													gapm_reset_cmd );
	
	CHECK_POINTER( reset_cmd );
	reset_cmd->operation=op_code;
	
	ke_msg_send( reset_cmd );

	return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :aes128 - bit encryption
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/

bx_err_t AES_128_Encryption(uint8_t *key,uint8_t *data)
{
	struct gapm_use_enc_block_cmd * aes_cmd = KE_MSG_ALLOC( GAPM_USE_ENC_BLOCK_CMD,
															TASK_GAPM, TASK_APP,
															gapm_use_enc_block_cmd );

	CHECK_POINTER( aes_cmd );
	aes_cmd->operation=GAPM_USE_ENC_BLOCK;
	memcpy(aes_cmd->operand_1,key,16);
	memcpy(aes_cmd->operand_2,data,16);
	
	ke_msg_send( aes_cmd );
	return BX_OK;
}











/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



