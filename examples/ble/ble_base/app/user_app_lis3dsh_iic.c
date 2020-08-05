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
#include "bx_service_lis3dsh.h"
#include "shell_api.h"

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
    user_service_lis3dsh_init();
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void user_app( void )
{
    s32 id = user_service_get_lis3dsh_id();
    
    bx_post(id,BXM_OPEN,0,0);
    bx_repeat( id,BXM_READ,0,0,1000 );
    
    //¶©ÔÄÏûÏ¢
    bx_subscibe(id,BXM_DATA_UPDATE,0,0);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( u32 msg,u32 param0,u32 param1 )
{
    struct lis3dsh_data * data = ( struct lis3dsh_data * )param0;
    
    switch(msg){
        case BXM_DATA_UPDATE:
            bxsh_logln( "Acceleration [mg]:\t%4.2f\t%4.2f\t%4.2f",
                data->mg[0], data->mg[1], data->mg[2] );
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



