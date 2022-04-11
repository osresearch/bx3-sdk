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
#include "bxd_tim.h"
#include "bxd_gpio.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/
void bx_it_init( void )
{
    bxd_timer_set_intr_callback(BX_TIM0, bx_tim0_intr_handler);
    bxd_timer_set_intr_callback(BX_TIM1, bx_tim1_intr_handler);
}

/*========================= end of private function ==========================*/

/*============================ interrupt function ============================*/
void bx_tim0_intr_handler(void)
{
    BX_READ_REG( BX_TIM0->EOI );
    bxd_gpio_toggle( BX_GPIOA, 2 );
}
void bx_tim1_intr_handler(void)
{
    BX_READ_REG( BX_TIM1->EOI );
    bxd_gpio_toggle( BX_GPIOA, 3 );
}

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



