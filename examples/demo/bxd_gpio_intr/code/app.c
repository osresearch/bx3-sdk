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
#include "bxd_gpio.h"
#include "bx_pm.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
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
void read_pin( void * data )
{
//	bxd_gpio_open( BX_GPIOA );
//	bxd_gpio_set_mode( BX_GPIOA, 2, BX_GPIO_MODE_OUTPUT );

    bxd_gpio_read( BX_GPIOA, &pin_value );
    if( !( pin_value >> 15 & 0x01 ) ) {
        bxd_gpio_write( BX_GPIOA, 2, 0 );
    } else {
        bxd_gpio_write( BX_GPIOA, 2, 1 );
    }
//	 bxd_gpio_close( BX_GPIOA );
}

void gpio_callback(void *hd,u8 pin_num,u8 reason)
{
	LOG_I("pin_num = %d\treason = %d",pin_num,reason);
	bxd_gpio_toggle( BX_GPIOA, 2 );
}


void app_init( void )
{
//    bx_pm_lock( BX_PM_GPIO );
    bxd_gpio_open( BX_GPIOA );
    bxd_gpio_set_mode( BX_GPIOA, 2, BX_GPIO_MODE_OUTPUT );
    bxd_gpio_write( BX_GPIOA, 2, 0 );
    bxd_gpio_set_mode( BX_GPIOA, 15, BX_GPIO_MODE_INPUT );
	bxd_gpio_set_pull(BX_GPIOA, 15, BX_GPIO_PULLUP);
    bxd_gpio_set_mode( BX_GPIOA, 15, BX_GPIO_MODE_EIT_FALLING );
	bxd_gpio_set_intr_callback( BX_GPIOA, gpio_callback);
    bxd_gpio_enable_intr( BX_GPIOA );
//    bx_dwork( read_pin, NULL, 10, -1 );

}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



