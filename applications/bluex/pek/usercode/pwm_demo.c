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
        s_is_init = true;
    }
}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//static void prv_start( uint32_t pin_num,uint32_t duty,uint32_t period)
//{
//
//}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_pin2_start( uint16_t high, uint16_t low )
{
    /* close clock gate */
    BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM0;

    /* clk div config */
    BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM_DIV;
    uint8_t div = 31;/* PWM tick clock = 32MHz/(div+1) zero means divide by 2 */
    BX_PER->CDP0 |= ( uint32_t )div << PER_CDP0_PWM_POS;
    BX_PER->CLKG1 |= PER_CLKG1_SET_PWM_DIV;

    /* open clock gate */
    BX_PER->CLKG1 |= PER_CLKG1_SET_PWM0;

    /* pin config */
    BX_MODIFY_REG( BX_CPU->FIOS0, CPU_FIOS0_IO01, CPU_FIO_TYPE_PWM0 << ( 0 * 4 ) );
    BX_SET_BIT( BX_CPU->FIOEN, GPIO_PIN_2 >> 2 );

    BX_PWM0->PS = ( ( uint32_t )high << 16 ) | low;
    BX_PWM0->EN = 1;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_pwm_cmd_handler( char argc, char * argv )
{
    uint32_t high = 0;
    uint32_t low = 0;
    char ch[1];
    prv_init();
    if ( argc == 2 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_logln( "useage: pwm + high + low" );
        }  else {
            bxsh_option_unsupport( &argv[argv[0]] );
        }
    } else if ( argc == 3 ) {
        if( sscanf( &argv[argv[1]], "%*[0]%*[x|X]%8X%1s", &high, ch ) == 1 ) {
        } else if( sscanf( &argv[argv[1]], "%10u%1s", &high, ch ) == 1 ) {
        } else {
            bxsh_logln( "duty err" );
            return;
        }

        if( sscanf( &argv[argv[2]], "%*[0]%*[x|X]%8X%1s", &low, ch ) == 1 ) {
        } else if( sscanf( &argv[argv[2]], "%10u%1s", &low, ch ) == 1 ) {
        } else {
            bxsh_logln( "low err" );
            return;
        }

        prv_pin2_start( high, low );
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
void pwm_add_shell_cmd( void )
{
    bxsh_add_cmd( "pwm", prv_pwm_cmd_handler, "pwm test" );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
