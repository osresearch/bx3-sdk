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
#include "led_demo.h"
#include "bx_shell.h"
#include "string.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

static uint32_t s_led_hub[] = { GPIO_PIN_2, GPIO_PIN_3 };

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
        BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
        BX_GPIOA->DIR |=  GPIO_PIN_2 | GPIO_PIN_3;
        s_is_init = true;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_off( char * p_led_id )
{
    uint32_t led_id;
    if( sscanf( p_led_id, "%d", &led_id ) == 1 ) {
        if( led_id < sizeof( s_led_hub ) / sizeof( s_led_hub[0] ) ) {
            BX_GPIOA->OD |= s_led_hub[led_id];
        }
    } else {
        bxsh_arg_err( "led" );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_on( char * p_led_id )
{
    uint32_t led_id;
    if( sscanf( p_led_id, "%d", &led_id ) == 1 ) {
        if( led_id < sizeof( s_led_hub ) / sizeof( s_led_hub[0] ) ) {
            BX_GPIOA->OD &= ~s_led_hub[led_id];
        }
    } else {
        bxsh_arg_err( "led" );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_toggle( char * p_led_id )
{
    uint32_t led_id;
    if( sscanf( p_led_id, "%d", &led_id ) == 1 ) {
        if( led_id < sizeof( s_led_hub ) / sizeof( s_led_hub[0] ) ) {
            BX_GPIOA->OD ^= s_led_hub[led_id];
        }
    } else {
        bxsh_arg_err( "led" );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_led_cmd_handler( char argc, char * argv )
{

    if ( argc > 1 ) {
        prv_init();
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_logln( "useage: help [options]" );
            bxsh_logln( "options:" );
            bxsh_logln( "\t on + index" );
            bxsh_logln( "\t off + index" );
            bxsh_logln( "\t -t + index \t: toggle led" );
        } else if ( !strcmp( "on", &argv[argv[1]] ) ) {
            prv_on( &argv[argv[2]] );
        } else if ( !strcmp( "off", &argv[argv[1]] ) ) {
            prv_off( &argv[argv[2]] );
        } else if ( !strcmp( "-t", &argv[argv[1]] ) ) {
            prv_toggle( &argv[argv[2]] );
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
void led_add_shell_cmd( void )
{
    bxsh_add_cmd( "led", prv_led_cmd_handler, "led test" );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
