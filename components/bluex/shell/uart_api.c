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
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/

#include "uart_api.h"

#if ( BX_UART_SHELL_ENABLE > 0 )

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported function prototypes ----------------------------------------------*/

/*============================= private function =============================*/
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void uart_init( void )
{

    NVIC_ClearPendingIRQ( UART0_IRQn );

    /* close clock */
    BX_PER->CLKG0 |= PER_CLKG0_32M_CLR_UART0;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_CLR_UART0;


    /*config uart0 baudrate begin*/
#define BAUDRATE_115200

#ifdef BAUDRATE_115200
#define NUM1_M1 2   //clk_diparam1.val.num1_m1 = 9
#define NUM0_M1 12  //clk_diparam1.val.num0_m1 = 5
#define LEN1_M1 2   //clk_diparam1.val.len1_m1 = 17
#define LEN0_M1 1   //clk_diparam1.val.len0_m1 = 16
#define UART_CLK_SEL    PER_CS_TYPE_16M_DIV_UART0
#define DIVISOR 8
#endif
#ifdef BAUDRATE_921600
#define NUM1_M1 12  //clk_diparam1.val.num1_m1 = 12
#define NUM0_M1 2   //clk_diparam1.val.num0_m1 = 2
#define LEN1_M1 1   //clk_diparam1.val.len1_m1 = 1
#define LEN0_M1 2   //clk_diparam1.val.len0_m1 = 2
#define UART_CLK_SEL    PER_CS_TYPE_16M_DIV_UART0
#define DIVISOR 1
#endif
#ifdef BAUDRATE_2000000
#define NUM1_M1 0   //clk_diparam1.val.num1_m1 = 0
#define NUM0_M1 0   //clk_diparam1.val.num0_m1 = 0
#define LEN1_M1 0   //clk_diparam1.val.len1_m1 = 0
#define LEN0_M1 0   //clk_diparam1.val.len0_m1 = 0
#define UART_CLK_SEL    PER_CS_TYPE_16M_UART0
#define DIVISOR 1
#endif
    BX_PER->CDP1  = ( ( ( uint32_t )NUM1_M1 << 24 ) \
                           | ( ( uint32_t )NUM0_M1 << 16 ) \
                           | ( ( uint32_t )LEN1_M1 << 8 ) \
                           | ( ( uint32_t )LEN0_M1 << 0 ) );
    BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, UART_CLK_SEL );

    /* open clock */
    BX_PER->CLKG0 |= PER_CLKG0_32M_SET_UART0;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_UART0;

    BX_SET_BIT( BX_CPU->FIOEN, GPIO_PIN_13 >> 2 );
    BX_SET_BIT( BX_CPU->FIOEN, GPIO_PIN_12 >> 2 );

    /* rx pin n  input config */
    BX_GPIOA->DIR &= ~( GPIO_PIN_13 );
    BX_AWO->GPIOIS |= ( GPIO_PIN_13 );
    BX_AWO->GPIOIE |= ( GPIO_PIN_13 );


    //gpio_mux[12] = funcio 10 , gpio_mux[13]=funcio 11
    BX_MODIFY_REG( BX_CPU->FIOS1, CPU_FIOS1_IO10, CPU_FIO_TYPE_UART0_TX << ( ( 10 - 8 ) * 4 ) );
    BX_MODIFY_REG( BX_CPU->FIOS1, CPU_FIOS1_IO11, CPU_FIO_TYPE_UART0_RX << ( ( 11 - 8 ) * 4 ) );

    BX_MODIFY_REG( BX_UART0->LC, UART_LC_DATA_WIDTH, UART_LC_DATA_WIDTH_T_8B );


    BX_SET_BIT( BX_UART0->LC, UART_LC_STOP_BIT );
    BX_CLR_BIT( BX_UART0->LC, UART_LC_PARITY_EN );

    //UART0->LCR |= UART_PARITY_EVEN;//even
    //UART0->LCR &= ~UART_PARITY_EVEN;//odd

    /* before set divisor must open clk */
    uint16_t divisor = DIVISOR;
    BX_UART0->LC |= 0x80; //open dlab
    /* baud rate = (serial clock freq) / (16 * divisor). */
    /* divisor low 8bit */
    BX_UART0->RTD = ( uint8_t )divisor;
    /* divisor high 8bit */
    BX_UART0->DI = ( uint8_t )( divisor >> 8 );
    BX_UART0->LC &= ~( ( uint32_t )0x80 ); //close dlab

    BX_UART0->IF |= UART_IF_FIFO_EN;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void uart_send_byte( uint8_t data )
{
    BX_UART0->RTD = data;
    while( BX_READ_BIT( BX_UART0->LS, UART_LS_TX_EMPTY ) == 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :   need fifo enable
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t uart_read_byte( void )
{
    //while( BX_READ_BIT( BX_UART0->LS, UART_LS_DATA_READY ) == 0 );
    return ( uint8_t )( BX_UART0->RTD );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/
/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/
/*========================= end of interrupt function ========================*/

#endif /* BX_UART_SHELL_ENABLE > 0 */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
