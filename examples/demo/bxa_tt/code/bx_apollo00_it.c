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

#include "app.h"
#include "bxd_uart.h"
#include "bxd_gpio.h"
#include "bxd_tim.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/
void bx_it_init( void )
{
    bxd_gpio_set_intr_callback( BX_GPIOA, bx_ext_intr_handler );
    bxd_timer_set_intr_callback(BX_TIM0, bx_tim0_intr_handler);
    bxd_timer_set_intr_callback(BX_TIM1, bx_tim1_intr_handler);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//u32 ext_int_stat_2_pin_state( u32 ext_int_stat )
//{
//    u32 ret = 0;
//    u32 temp = 0;


//    for( u32 i = 0; i < 5; i++ ) {
//        if( ext_int_stat & ( 0x01 << i ) ) {
//            switch( i ) {
//                case 0:{
//                    temp = 0x01 << 15;
//                }
//                    break;

//                case 1:
//                    temp = 0x01 << 16;
//                    break;

//                case 2:
//                    temp = 0x01 << 17;
//                    break;

//                case 3:
//                    temp = 0x01 << 22;
//                    break;

//                case 4:
//                    temp = 0x01 << 23;
//                    break;

//                default:
//                    break;
//            }
//        }
//        ret |= temp;
//    }
//    return ret;
//}
/*========================= end of private function ==========================*/

/*============================ interrupt function ============================*/

void bx_ext_intr_handler( void * hdl, u8 pin_num, u8 reason )
{
    //LOG_V( "ext_intr:%u %u", pin_num, reason );
    switch(  pin_num ) {
       

        case 15: {
            bxd_gpio_disable_ext_intr( hdl, pin_num );
            bx_public( us_svc.id, BXM_USER_GPIO_INTR, 0x01<<pin_num, 0);
        }
        break;
        
        case 17: {
            bxd_gpio_disable_ext_intr( hdl, pin_num );
            bx_public( us_svc.id, BXM_USER_GPIO_INTR, 0x01<<pin_num, 0);
        }
        break;
        
        
        default:
            break;
    }

}
void bx_tim0_intr_handler(void)
{
    bx_public( us_svc.id, BXM_USER_TIM0_INTR, 0, 0 );
}
void bx_tim1_intr_handler(void)
{
//        bx_public( us_svc.id, BXM_USER_TIM1_INTR, 0, 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/

//void EXT_INTR_IRQHandler( void )
//{
//    uint8_t ext_int_stat = BX_FIELD_RD( BX_AWO->EIVAL, AWO_EIVAL_VAL ) ;
//    BX_AWO->EICLR |= ext_int_stat;
//    u32 pin_state = ext_int_stat_2_pin_state( ext_int_stat );
//    bx_public( us_svc.id, BXM_USER_GPIO_INTR, pin_state, 0);
////    LOG_I( "EXT_INTR_IRQHandler = %d,ext_int_stat=%d", pin_state ,ext_int_stat);
//}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//void TIMER_IRQHandler( void )
//{
//    uint32_t timer_isr_status0, timer_isr_status1;

//    timer_isr_status0 = BX_TIM0->IS & 0x01;
//    timer_isr_status1 = BX_TIM1->IS & 0x01;

//    if( timer_isr_status0 ) {
//        BX_READ_REG( BX_TIM0->EOI );
//        bx_public( us_svc.id, BXM_USER_TIM0_INTR, 0, 0 );
//    }

//    if( timer_isr_status1 ) {
//        BX_READ_REG( BX_TIM1->EOI );
////        bx_public( us_svc.id, BXM_USER_TIM1_INTR, 0, 0 );
//    }
//}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void UART1_IRQHandler( void )
{

    u8 irq_status = BX_READ_REG( BX_UART1->IF ) & 0x0F;

    switch( irq_status ) {
        case BX_UART_IRQ_RLS:
        case BX_UART_IRQ_CT:
        case BX_UART_IRQ_RDA: {
            while( 1 == BX_READ_BIT( BX_UART1->LS, UART_LS_DATA_READY ) ) {
                u8 data = BX_UART1->RTD;
                bx_fifo_push( &( us_svc.rx_fifo ), &data, 1 ) ;

            }
 
        }
        break;

        default:
            break;
    }
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



