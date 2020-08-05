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

/* includes ------------------------------------------------------------------*/

#include "apollo_00_reg.h"
#include "timer_demo.h"
#include "bx_shell.h"
#include "string.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/


/* private macros ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported function prototypes ----------------------------------------------*/

/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_init( void )
{
    static bool s_is_init = false;
    if( !s_is_init ) {
        NVIC_ClearPendingIRQ( TIMER_IRQn );
        NVIC_EnableIRQ( TIMER_IRQn );

        BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM0;

        BX_CPU->CLKG0 |= CPU_CLKG0_CLR_TIM_DIV;
        uint8_t div = 31;/* PWM tick clock = 32MHz/(div+1) zero means divide by 2 */
        BX_MODIFY_REG(BX_CPU->TIMDP,CPU_TIMDP,( uint32_t )div << CPU_TIMDP_POS);
        BX_CPU->CLKG0 |= CPU_CLKG0_SET_TIM_DIV;

        BX_CPU->CLKG1 |= CPU_CLKG1_SET_TIM0 ;
        s_is_init = true;
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_tim_start(uint32_t period_ms)
{
    //bxsh_logln( "period_ms %d ",period_ms );
    
    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
    BX_GPIOA->DIR |=  GPIO_PIN_2 ;
    
    __disable_irq();
    
    BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM0;
    // Hz = 32M(31+1)/BX_TIM0->LCR
    BX_TIM0->LC = period_ms / 2 * 1000 ;

    BX_CPU->CLKG1 |= CPU_CLKG1_SET_TIM0;

    BX_MODIFY_REG(BX_TIM0->CTRL,TIM_CTRL_MODE,TIM_CTRL_MODE_T_USER_DEFINED);
    //BX_SET_BIT(BX_TIM0->CTRL,TIM_CTRL_MODE);
    BX_CLR_BIT(BX_TIM0->CTRL,TIM_CTRL_IM);
    BX_SET_BIT(BX_TIM0->CTRL,TIM_CTRL_EN);
    
    __enable_irq();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_tim_cmd_handler( char argc, char * argv )
{
   uint32_t period_ms = 0;
    char ch[1];
    prv_init();
    if ( argc == 2 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_logln( "useage: tim + period_ms (toggle D2) " );
            return;
        }
        if( sscanf( &argv[argv[1]], "%*[0]%*[x|X]%8X%1s", &period_ms, ch ) == 1 ) {
        } else if( sscanf( &argv[argv[1]], "%10u%1s", &period_ms, ch ) == 1 ) {
        } else {
            bxsh_logln( "period_ms err" );
            return;
        }
        if( period_ms == 0 ) {
            bxsh_arg_err( &argv[argv[0]] );
            return;
        }
        prv_tim_start( period_ms );
    }  else {
        bxsh_arg_err( &argv[argv[0]] );
    }
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void tim_add_shell_cmd( void )
{
    bxsh_add_cmd( "tim", prv_tim_cmd_handler, "timer0 test" );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void TIMER_IRQHandler( void )
{
    if( BX_TIM0->IS > 0 ) {
        uint32_t a = BX_TIM0->EOI & 0x01;
        BX_GPIOA->OD ^=  GPIO_PIN_2 ;
    }
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
