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
#include "bx_apollo00_it.h"
#include "bxd_gpio.h"
#include "bx_kernel.h"
#include "bx_log.h"
#include "us_tp.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/
void bx_it_init( void )
{
    bxd_gpio_set_intr_callback( BX_GPIOA, bx_ext_intr_handler );
}
/*========================= end of private function ==========================*/

/*============================ interrupt function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void bx_ext_intr_handler( void * hdl, u8 pin_num, u8 reason )
{
    LOG_V( "ext_intr:%u %u", pin_num, reason );
    switch(  pin_num ) {
        case TP_INT_PIN: {
            bx_logln("TP");
            bx_post( tp_svc.id, USM_TP_EVT_INTR, 0, 0 );
        }
        break;



        default:
            break;
    }

}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



