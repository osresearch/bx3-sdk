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
/* config --------------------------------------------------------------------*/
#define __RAM_CODE__

/* includes ------------------------------------------------------------------*/

#include "bx_config.h"
#include "jump_table.h"
#include "nvds_in_ram.h"
#include "ecc_p256.h"
#include "arch.h"
#include "rwip.h"
#include "prf.h"
#include "lld_sleep.h"
#include "compiler_flag.h"

/* private define ------------------------------------------------------------*/
#define JUMP_TABLE_SECTION __attribute__((section("jump_table_area")))

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
void * const jump_table[JUMP_TABLE_SIZE] JUMP_TABLE_SECTION USED_FLAG = {
#if (CFG_FREERTOS_SUPPORT == 1 || !defined(CFG_APP))
    [APP_INTERFACE] = ( void * )TASK_AHI,
#else
    [APP_INTERFACE] = ( void * )TASK_APP,
#endif
    [PLATFORM_RESET] = platform_reset,
    [NVDS_INIT] = nvds_init,
    [NVDS_GET] = nvds_get,
    [NVDS_DEL] = nvds_del,
    [NVDS_PUT] = nvds_put,
    [PRF_INIT] = prf_init,
    [PRF_CLEANUP] = prf_cleanup,
    [PRF_CREATE] = prf_create,
    [PRF_ADD_PROFILE] = prf_add_profile,
    [PRF_GET_ID_FROM_TASK] = prf_get_id_from_task,
    [PRF_GET_TASK_FROM_ID] = prf_get_task_from_id,
    [ECC_GENERATE_KEY256] = ecc_generate_key256,
    [ECC_GEN_NEW_SECRET_KEY] = ecc_gen_new_secret_key,
    [ECC_GEN_NEW_PUBLIC_KEY] = ecc_gen_new_public_key,
    [RWIP_WAKEUP] = rwip_wakeup,
    [RWIP_WAKEUP_END] = rwip_wakeup_end,
    [RWIP_PREVENT_SLEEP_SET] = rwip_prevent_sleep_set,
    [RWIP_PREVENT_SLEEP_CLEAR] = rwip_prevent_sleep_clear,
    [RWIP_RESET] = rwip_reset,
    [RWIP_RF] = ( void * ) & rwip_rf,
    [RWIP_PRIORITY] = ( void * ) & rwip_priority[0],
    [RWIP_COEX_CFG] = ( void * ) & rwip_coex_cfg[0],
    [LLD_SLEEP_INIT] = lld_sleep_init,
    [RWIP_ASSERT_DBG] = rwip_assert_asm,
    [HBEACON] = NULL,
    [DUMMY0] = NULL,
};
/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

