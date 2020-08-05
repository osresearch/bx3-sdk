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
#include "spim_demo.h"
#include "shell_api.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
volatile uint32_t local_time_us = 0;
/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_tim_init( void )
{
    static bool s_is_init = false;
    if( !s_is_init ) {
        NVIC_ClearPendingIRQ( TIMER_IRQn );
        NVIC_EnableIRQ( TIMER_IRQn );

        BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM0;

        BX_CPU->CLKG0 |= CPU_CLKG0_CLR_TIM_DIV;
        uint8_t div = 1;/* PWM tick clock = 32MHz/(div+1) zero means divide by 2 */
        BX_MODIFY_REG( BX_CPU->TIMDP, CPU_TIMDP, ( uint32_t )div << CPU_TIMDP_POS );
        BX_CPU->CLKG0 |= CPU_CLKG0_SET_TIM_DIV;

        BX_CPU->CLKG1 |= CPU_CLKG1_SET_TIM0 ;


        BX_CPU->CLKG1 |= CPU_CLKG1_CLR_TIM0;
        // Hz = 32M(1+1)/(BX_TIM0->LCR + 1)
        BX_TIM0->LC = 15;

        BX_CPU->CLKG1 |= CPU_CLKG1_SET_TIM0;

        BX_MODIFY_REG( BX_TIM0->CTRL, TIM_CTRL_MODE, TIM_CTRL_MODE_T_USER_DEFINED );
        //BX_SET_BIT(BX_TIM0->CTRL,TIM_CTRL_MODE);
        BX_CLR_BIT( BX_TIM0->CTRL, TIM_CTRL_IM );


        s_is_init = true;
        local_time_us = 0;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void delay_us( uint32_t time_us )
{
    local_time_us = time_us;
    BX_SET_BIT( BX_TIM0->CTRL, TIM_CTRL_EN );
    while(local_time_us>0);
//    while( local_time_us < time_5us ) {
//        ;
//    }
//    BX_CLR_BIT( BX_TIM0->CTRL, TIM_CTRL_EN );
}
#define SPIM_CS_PIN         GPIO_PIN_3
#define SPIM_CLK_PIN        GPIO_PIN_4
#define SPIM_MISO_PIN       GPIO_PIN_5
#define SPIM_MOSI_PIN       GPIO_PIN_6

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void prv_spim_init( void )
{
    __disable_irq();

    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;

    /* output config */
    BX_GPIOA->DIR |=  SPIM_CLK_PIN | SPIM_MOSI_PIN ;
    BX_GPIOA->OD &=  ~(SPIM_CLK_PIN | SPIM_MOSI_PIN);
    
    /* input config */
    BX_GPIOA->DIR &= ~( SPIM_MISO_PIN );
    BX_AWO->GPIOIS |= ( SPIM_MISO_PIN );
    BX_AWO->GPIOIE |= ( SPIM_MISO_PIN );

    /* pull down */
    BX_AWO->GPIOPS |= ( SPIM_MISO_PIN );
    BX_AWO->GPIOPE |= ( SPIM_MISO_PIN );

    prv_tim_init();

    BX_GPIOA->DIR |=  GPIO_PIN_2 ;

    __enable_irq();
}
#define SCK_H (BX_GPIOA->OD |=  SPIM_CLK_PIN)
#define SCK_L (BX_GPIOA->OD &=  ~SPIM_CLK_PIN)

#define MOSI_H (BX_GPIOA->OD |=  SPIM_MOSI_PIN)
#define MOSI_L (BX_GPIOA->OD &=  ~SPIM_MOSI_PIN)

#define MISO    ((BX_GPIOA->ID & SPIM_MISO_PIN) > 0 )

#define AHB_CLK                         MAIN_CLOCK
extern void bx_delay_asm(unsigned int loop);
#define bx_delay_us(a) bx_delay_asm((a)*(32000000/32000000))

void Soft_SPI_Write( uint8_t data )
{
    for( uint8_t i = 0; i < 8; i++ ) {

        if( data & 0x80 ) {
            MOSI_H;          /*若最高位为高，则输出高*/
        } else {
            MOSI_L;          /*若最高位为低，则输出低*/
        }  
        SCK_H;
        delay_us(1);             /*读取第一bit数据 等待数据稳定 根据实际时钟调整*/
        SCK_L;
        delay_us(1);
    }
}

////软件模拟SPI写(发送)
//void Soft_SPI_Write( uint8_t a )
//{
//    uint8_t cnt;
//    BX_GPIOA->OD &= ~( SPIM_CLK_PIN ); //拉高CLK

//    for( cnt = 0; cnt < 8; cnt++ ) {
//        BX_GPIOA->OD &= ~( SPIM_CLK_PIN ); //拉低CLK
//        delay_10us( 1 ); //这个延时时间任意，但要大于芯片数据手册上的(纳秒级的)
//        if( a & 0x80 ) {
//            BX_GPIOA->OD |= ( SPIM_MOSI_PIN );
//        } else {
//            BX_GPIOA->OD &= ~( SPIM_MOSI_PIN );
//        }
//        a <<= 1;
//        BX_GPIOA->OD |= ( SPIM_CLK_PIN ); //拉高CLK
//        delay_10us( 1 );
//    }
//}

//软件模拟SPI读(接收)
uint8_t Soft_SPI_Read( void )
{
    uint8_t cnt;
    uint8_t Rxdata = 0;

    for( cnt = 0; cnt < 8; cnt++ ) {
        BX_GPIOA->OD &= ~( SPIM_CLK_PIN ); //拉低CLK
        delay_us( 1 );
        Rxdata <<= 1;
        if( ( BX_GPIOA->ID & SPIM_MISO_PIN ) > 0 ) {
            Rxdata |= 0x01;
        }
        BX_GPIOA->OD |= ( SPIM_CLK_PIN ); //拉高CLK
        delay_us( 1 );
    }
    return Rxdata;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_spim_cmd_handler( char argc, char * argv )
{
    char ch[1];
    if ( argc > 1 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxs_printfln( "useage: help [options]" );
            bxs_printfln( "options:" );
            bxs_printfln( "\t init \t: spim init" );
            bxs_printfln( "\t -r + addr \t: read 1 byte " );
            bxs_printfln( "\t -w + addr + data\t: write 1 byte " );
        } else if ( !strcmp( "init", &argv[argv[1]] ) ) {
            prv_spim_init();
        } else if ( !strcmp( "-r", &argv[argv[1]] ) ) {
            uint8_t data = Soft_SPI_Read();
            bxs_printfln( "data :%u", data );
        } else if ( !strcmp( "-w", &argv[argv[1]] ) ) {
            uint32_t value;
            uint8_t data;
            if( sscanf( &argv[argv[2]], "%10u%1s", &value, ch ) == 1 ) {
            } else if( sscanf( &argv[argv[2]], "%*[0]%*[x|X]%8X%1s", &value, ch ) == 1 ) {
            } else if( sscanf( &argv[argv[2]], "%10u%1s", &value, ch ) == 1 ) {
            } else {
                shell_printf( "addr err\r\n" );
                return;
            }
            data = value;
            bxs_printfln( "data : %02x", data );
            
            Soft_SPI_Write( data );

        } else {
            bxs_option_unsupport( &argv[argv[0]] );
        }
    } else {
        bxs_arg_err( &argv[argv[0]] );
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
void spim_add_shell_cmd( void )
{
    bxs_add_cmd( "spim", prv_spim_cmd_handler, "spim test" );
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
        if( local_time_us > 0 ){
            local_time_us--;
            if( local_time_us == 0 ){
                BX_CLR_BIT( BX_TIM0->CTRL, TIM_CTRL_EN );
            }
        }
        //BX_GPIOA->OD ^= GPIO_PIN_2;
    }
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
