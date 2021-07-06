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

#include "bxd_tim.h"

static timer_intr_cb timer_intr_cb_0 = NULL;
static timer_intr_cb timer_intr_cb_1 = NULL;


/* private define ------------------------------------------------------------*/
#define CHECK_HANDLE(hdl)                                   \
do{                                                         \
    if( (hdl) != BX_TIM0 && (hdl) != BX_TIM1 ) {            \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)


#define CHECK_PERIOD(period)                                \
do{                                                         \
    if( (period) >= BX_GPIO_MODE_MAX ) {                    \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

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
bx_err_t bxd_timer_open( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_timer_t * BX_TIMx = ( reg_timer_t * )hdl;

    if( BX_TIMx == BX_TIM0 ) {
        BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM0;
    } else if ( BX_TIMx == BX_TIM1 ) {
        BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM1;
    } else {
        return BX_ERR_INVAL;
    }

    BX_CPU->CLKG0 |= CPU_CLKG0_CLR_TIM_DIV;
    uint8_t div = 1;/* PWM tick clock = 32MHz/(div+1) zero means divide by 2 */
    BX_MODIFY_REG( BX_CPU->TIMDP, CPU_TIMDP, ( uint32_t )div << CPU_TIMDP_POS );
    BX_CPU->CLKG0 |= CPU_CLKG0_SET_TIM_DIV;

    if( BX_TIMx == BX_TIM0 ) {
        BX_CPU->CLKG1 |= CPU_CLKG1_SET_TIM0;
    } else if ( BX_TIMx == BX_TIM1 ) {
        BX_CPU->CLKG1 |= CPU_CLKG1_SET_TIM1;
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_timer_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_timer_t * BX_TIMx = ( reg_timer_t * )hdl;

    if( BX_TIMx == BX_TIM0 ) {
        BX_CPU->CLKG1 &= ~CPU_CLKG1_SET_TIM0;
        BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM0;
    } else if ( BX_TIMx == BX_TIM1 ) {
        BX_CPU->CLKG1 &= ~CPU_CLKG1_SET_TIM1;
        BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM1;
    } else {
        return BX_ERR_INVAL;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_timer_start( void * hdl, u32 periode_us )
{
    CHECK_HANDLE( hdl );
    reg_timer_t * BX_TIMx = ( reg_timer_t * )hdl;

    BX_CLR_BIT( BX_TIMx->CTRL, TIM_CTRL_EN );

    if( BX_TIMx == BX_TIM0 ) {
        BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM0;
        BX_CPU->CLKG1 |= CPU_CLKG1_SET_TIM0;
    } else if ( BX_TIMx == BX_TIM1 ) {
        BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM1;
        BX_CPU->CLKG1 |= CPU_CLKG1_SET_TIM1;
    } else {
        return BX_ERR_INVAL;
    }

    // Hz = 32M(31+1)/BX_TIM0->LCR
    BX_TIMx->LC = periode_us * 16 - 1;

    BX_MODIFY_REG( BX_TIMx->CTRL, TIM_CTRL_MODE, TIM_CTRL_MODE_T_USER_DEFINED );
    //BX_SET_BIT(BX_TIM0->CTRL,TIM_CTRL_MODE);
    BX_CLR_BIT( BX_TIMx->CTRL, TIM_CTRL_IM );
    BX_SET_BIT( BX_TIMx->CTRL, TIM_CTRL_EN );

    NVIC_ClearPendingIRQ( TIMER_IRQn );
    NVIC_EnableIRQ( TIMER_IRQn );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_timer_set_intr_callback( void * hdl, timer_intr_cb cb )
{
    CHECK_HANDLE( hdl );
	if(hdl == BX_TIM0)
	{
		timer_intr_cb_0 =  cb;
	}
	else if(hdl == BX_TIM1)
	{
		timer_intr_cb_1 =  cb;
	}
	else
	{
		return BX_ERR_INVAL;
	}
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void TIMER_IRQHandler( void )
{
    uint32_t timer_isr_status0, timer_isr_status1;
    timer_isr_status0 = BX_TIM0->IS & 0x01;
    timer_isr_status1 = BX_TIM1->IS & 0x01;
    if( timer_isr_status0 ) {
        BX_READ_REG( BX_TIM0->EOI );
		timer_intr_cb_0();
    }
    if( timer_isr_status1 ) {
        BX_READ_REG( BX_TIM1->EOI );
		timer_intr_cb_1();
    }
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



