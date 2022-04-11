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

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
volatile u32 sys_tick = 0;
/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

void SysTick_init( void )
{
    SysTick->LOAD  = ( u32 )( MAIN_CLOCK / 1000  - 1UL );                   /* set reload register */  //1us
    NVIC_SetPriority ( SysTick_IRQn, ( 1UL << __NVIC_PRIO_BITS ) - 1UL ); /* set Priority for Systick Interrupt */
    SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                     SysTick_CTRL_TICKINT_Msk   |
                     SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */

    NVIC_ClearPendingIRQ( SysTick_IRQn );
    NVIC_EnableIRQ( SysTick_IRQn );
    __enable_irq();
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void SysTick_Handler( void )
{
    sys_tick++;
	LOG_RAW("systick=%d\r\n\r\n",sys_tick);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u32 GetSysTick( void )
{
    return sys_tick;
}



/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    SysTick_init();
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



