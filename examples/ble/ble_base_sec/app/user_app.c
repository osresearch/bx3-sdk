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

#include "bx_kernel.h"
#include "user_app.h"
#include "bx_shell.h"
#include "user_service_ble.h"
#include "bx_pm.h"
#include <easyflash.h>
#include "app_sec.h"
#include "user_ble.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

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
void user_init( void )
{
    us_ble_register();
    easyflash_init();

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void user_app( void )
{
    bx_subscibe( us_ble_id(), BXM_BLE_READY, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_ADVERTISING, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_CONNECTED, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_DISCONNECTED, 0, 0 );
    bx_subscibe( us_ble_id(), BXM_BLE_BOND_SUCCEED, 0, 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_ble_msg_handle_func( u32 src_id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {
        case BXM_BLE_READY:
            bxsh_logln( "BXM_BLE_READY" );
            bx_post( src_id, BXM_BLE_ADV_START, 0, 0 );
            break;
        case BXM_BLE_ADVERTISING:
            bxsh_logln( "BXM_BLE_ADVERTISING" );
            break;
        case BXM_BLE_CONNECTED:
            bxsh_logln( "BXM_BLE_CONNECTED" );
            break;
        case BXM_BLE_DISCONNECTED:
            bxsh_logln( "BXM_BLE_DISCONNECTED" );
            bx_post( src_id, BXM_BLE_ADV_START, 0, 0 );
            break;
        case BXM_BLE_BOND_SUCCEED:
            bxsh_logln( "BXM_BLE_BOND_SUCCEED" );
            break;

        default:
            break;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 )
{
    s32 msg_src = bx_msg_source();
    if(  msg_src == us_ble_id() ) {
        user_ble_msg_handle_func( msg_src, msg, param0, param1 );
    }
    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



