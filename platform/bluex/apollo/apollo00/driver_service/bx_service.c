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

#include "bx_service.h"
#include "bx_kernel.h"

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
bx_err_t bxs_register( void )
{
    if( bxs_gpio_register() != BX_OK ) {
        return BX_ERROR;
    }

    if( bxs_tim_register() != BX_OK ) {
        return BX_ERROR;
    }

    if( bxs_pwm_register() != BX_OK ) {
        return BX_ERROR;
    }

    if( bxs_iic_register() != BX_OK ) {
        return BX_ERROR;
    }
    
    if( bxs_uart_register() != BX_OK ) {
        return BX_ERROR;
    }
        
    if( bxs_adc_register() != BX_OK ) {
        return BX_ERROR;
    }
    
    if( bxs_spim_register() != BX_OK ) {
        return BX_ERROR;
    }

    return BX_OK;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



