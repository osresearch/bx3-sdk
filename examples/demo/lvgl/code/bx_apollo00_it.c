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
#define LOG_LVL 5
#define LOG_TAG "[IRQ]"

/* includes ------------------------------------------------------------------*/
#include "bx_apollo00_it.h"
#include "bxd_gpio.h"
#include "bx_kernel.h"
#include "bx_log.h"

#include "us_tp.h"
#include "arch_init.h"
/* private define ------------------------------------------------------------*/
#define FILE_ID 1000000
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
    
    MARK();
    //LOG_V( "ext_intr:%u %u", pin_num, reason );
    switch(  pin_num ) {
        case TP_INT_PIN: {
            MARK();
            bx_post( tp_svc.id, USM_TP_EVT_INTR, 0, 0 );
        }
        break;

        default:
            break;
    }
    MARK();
}

//void TIMER_IRQHandler( void )
//{
//    uint32_t timer_isr_status0, timer_isr_status1;

//    timer_isr_status0 = BX_TIM0->IS & 0x01;
//    timer_isr_status1 = BX_TIM1->IS & 0x01;

//    if( timer_isr_status0 ) {
//        BX_READ_REG( BX_TIM0->EOI );
//        bx_post(0,1234,0,0);
//    }

//    if( timer_isr_status1 ) {
//        BX_READ_REG( BX_TIM1->EOI );
//    }
//}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



