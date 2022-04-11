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
#include "app.h"
#include "bxs_gpio.h"
#include "bxd_gpio.h"
#include "bx_dbg.h"
#include "plf.h"
#include "bx_apollo00_it.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
s32 user_service_id;
u32 pin_value;
/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    struct bx_service svc;
    svc.prop_set_func = NULL;
    svc.prop_get_func = NULL;
    svc.msg_handle_func = user_msg_handle_func;
    svc.name = "user service";
    user_service_id = bx_register( &svc );

    bxs_gpio_register();
    bx_it_init();
    s32 id = bxs_gpio_a_id();


    bx_call( id, BXM_OPEN, 0, 0 );
    bx_set( id, BXP_MODE, 2, BX_GPIO_MODE_OUTPUT );
    bx_call( id, BXM_WRITE, 2, 1 );
    bx_set( id, BXP_MODE, 15, BX_GPIO_MODE_INPUT );
    bx_repeat( user_service_id, USER_GPIO_INPUT, 0, 0, 10 );
    bx_set( id, BXP_MODE, 15, BX_GPIO_MODE_EIT_FALLING );
    bx_subscibe( id, BXM_GPIO_INTR, 0, 0 );

}
s32 us_id( void )
{
    return user_service_id;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( s32 id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {
        case BXM_GPIO_INTR:
            bx_logln( "BXM_GPIO_INTR" );
            break;
        case USER_GPIO_INPUT: {
            bx_call( bxs_gpio_a_id(), BXM_READ, ( u32 )&pin_value, 0 );
            if( !( pin_value >> 15 & 0x01 ) ) {
                bx_call( bxs_gpio_a_id(), BXM_TOGGLE, 2, 0 );
            } 
        }
        break;
        default:
            break;
    }
    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



