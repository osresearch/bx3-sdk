/**
  ******************************************************************************
  * @file   :   main.c
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
#include "rwip_config.h"             // SW configuration

#include "user_ble_task.h"
#include "user_ble.h"
#include "gap.h"
#include "gapm_task.h"
#include "gapc_task.h"
#include "user_ble_profile.h"
#include "bx_kernel.h"
#include "ke_timer.h"
#include "bx_shell.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
typedef void ( *appm_add_svc_func_t )( void );

/* private variables ---------------------------------------------------------*/
static const struct ke_task_desc TASK_DESC_APP = {
    NULL,
    &appm_default_handler,
    appm_state,
    APPM_STATE_MAX,
    1
};
struct app_env_tag app_env;

static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    ( appm_add_svc_func_t )add_dis_profile,
    ( appm_add_svc_func_t )add_bxota_profile,
    ( appm_add_svc_func_t )add_user_profile,
};

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void user_ble_init()
{
    memset( &app_env, 0, sizeof( app_env ) );
    ke_task_create( TASK_APP, &TASK_DESC_APP );
    ke_state_set( TASK_APP, APPM_INIT );
    memcpy( app_env.dev_name, BX_DEV_NAME, sizeof( BX_DEV_NAME ) );
    app_env.dev_name_len = strlen( BX_DEV_NAME );
    app_dis_init();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool user_ble_add_svc( void )
{
    bool more_svc = false;
    if ( app_env.next_svc != sizeof( appm_add_svc_func_list ) / sizeof( appm_add_svc_func_t ) ) {
        appm_add_svc_func_list[app_env.next_svc]();
        app_env.next_svc++;
        more_svc = true;
    }
    return more_svc;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

