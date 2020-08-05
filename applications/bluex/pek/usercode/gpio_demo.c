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
#include "gpio_demo.h"
#include "bx_shell.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_output_test( void )
{
    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;

    /* output config */
    BX_GPIOA->DIR |=  GPIO_PIN_2 ;

    /* toggle pin */
    BX_GPIOA->OD ^=  GPIO_PIN_2 ;
    
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_intput_test()
{
    /* set clock */
    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;

    /* output config */
    BX_GPIOA->DIR |=  GPIO_PIN_2 ;

    /* input config */
    BX_GPIOA->DIR &= ~( GPIO_PIN_15 );
    BX_AWO->GPIOIS |= ( GPIO_PIN_15 );
    BX_AWO->GPIOIE |= ( GPIO_PIN_15 );

    /* pull down */
    BX_AWO->GPIOPS &= ~( GPIO_PIN_15 );
    BX_AWO->GPIOPE |= ( GPIO_PIN_15 );
    
    bxsh_logln("input test start: ( press KEY_PAD )");
    uint32_t intput_count = 0x2FFFFF;
    while( intput_count > 0 ) {
        if( ( BX_GPIOA->ID & GPIO_PIN_15 ) > 0 ) {
            BX_GPIOA->OD |=  GPIO_PIN_2 ;
        } else {
            intput_count--;
            BX_GPIOA->OD &=  ~GPIO_PIN_2 ;
        }
    }
    BX_GPIOA->OD |=  GPIO_PIN_2 ;
    bxsh_logln("input test done");
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_irq_test()
{
    __disable_irq();

    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;

    BX_GPIOA->DIR |= GPIO_PIN_2;

    uint32_t pin_mark =  GPIO_PIN_15;
    /* config input */
    BX_GPIOA->DIR &= ~( pin_mark );
    if( GPIO_PAD_MASK & ( pin_mark ) ) {
        BX_AWO-> GPIOIE |= ( pin_mark );
        BX_AWO-> GPIOIS |= ( pin_mark );
    }
    /* LOW LEVEL */
//    BX_GPIOA->IT &= ~pin_mark;
//    BX_GPIOA->IP &= ~pin_mark;
//    BX_GPIOA->INT_BOTHEDGE &= ~pin_mark;

    /* HIGH LEVEL */
//    BX_GPIOA->IT &= ~pin_mark;
//    BX_GPIOA->IP |= pin_mark;
//    BX_GPIOA->INT_BOTHEDGE &= ~pin_mark;

    /* FALLING */
//    BX_GPIOA->IT |= pin_mark;
//    BX_GPIOA->IP &= ~pin_mark;
//    BX_GPIOA->INT_BOTHEDGE &= ~pin_mark;

    /* RISING */
    BX_GPIOA->IT |= pin_mark;
    BX_GPIOA->IP |= pin_mark;
    BX_GPIOA->IBE &= ~pin_mark;

    /* BOTHEDG */
//    BX_GPIOA->INT_BOTHEDGE |= pin_mark;

    BX_GPIOA->IE |= pin_mark;
    BX_GPIOA->IM &= ~pin_mark;

    NVIC_ClearPendingIRQ( GPIO_IRQn );
    NVIC_EnableIRQ( GPIO_IRQn );

    __enable_irq();

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_gpio_cmd_handler( char argc, char * argv )
{
    if ( argc > 1 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_logln( "useage: help [options]" );
            bxsh_logln( "options:" );
            bxsh_logln( "\t -o \t: output test (toggle led D2) " );
            bxsh_logln( "\t -i \t: input test " );
            bxsh_logln( "\t -irq \t: irq test toggle D2 by key_pad" );
        } else if ( !strcmp( "-o", &argv[argv[1]] ) ) {
            prv_output_test();
        } else if ( !strcmp( "-i", &argv[argv[1]] ) ) {
            prv_intput_test();
        } else if ( !strcmp( "-irq", &argv[argv[1]] ) ) {
            prv_irq_test();
        } else {
            bxsh_option_unsupport( &argv[argv[0]] );
        }
    } else {
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
void gpio_test( void )
{
    //prv_output_test();

    //prv_intput_test();

    //prv_irq_test();
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void gpio_add_shell_cmd( void )
{
    bxsh_add_cmd( "gpio", prv_gpio_cmd_handler, "gpio test" );
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
void GPIO_IRQHandler( void )
{
    uint32_t pin_mark = BX_GPIOA->IS;
    BX_GPIOA->EOI |= pin_mark;
    if( ( pin_mark & GPIO_PIN_15 ) > 0 ) {
        BX_GPIOA->OD ^= GPIO_PIN_2;
    }
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
