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
#include "rtc_demo.h"
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
        
        BX_SET_BIT( BX_AWO->LCC, AWO_LCC_32K_XTAL_EN);
        BX_MODIFY_REG( BX_AWO->LCC, AWO_LCC_32K_SRC_SEL,AWO_LCC_32K_SRC_SEL_T_XTAL);
        
        BX_AWO->CLKG |= AWO_CLKG_SET_RTC;
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
static void prv_rtc_start(uint32_t count)
{
    //bxsh_logln( "count %d ",count );
    
    BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
    BX_GPIOA->DIR |=  GPIO_PIN_3 ;
    
    __disable_irq();
    
    BX_RTC->CM = count;
    BX_RTC->CL = 0;
    
    BX_SET_BIT(BX_RTC->CC,RTC_CC_IE);
    BX_CLR_BIT(BX_RTC->CC,RTC_CC_IM);
    BX_SET_BIT(BX_RTC->CC,RTC_CC_WRAP_EN);
    BX_SET_BIT(BX_RTC->CC,RTC_CC_EN);
    
    NVIC_EnableIRQ( RTC_IRQn );
    
    __enable_irq();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_rtc_cmd_handler( char argc, char * argv )
{
   uint32_t count = 0;
    char ch[1];
    prv_init();
    if ( argc == 2 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_logln( "useage: rtc + count(unit: clk)(toggle D3) " );
            return;
        }
        if( sscanf( &argv[argv[1]], "%*[0]%*[x|X]%8X%1s", &count, ch ) == 1 ) {
        } else if( sscanf( &argv[argv[1]], "%10u%1s", &count, ch ) == 1 ) {
        } else {
            bxsh_logln( "count err" );
            return;
        }
        if( count == 0 ) {
            bxsh_arg_err( &argv[argv[0]] );
            return;
        }
        prv_rtc_start( count );
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
void rtc_add_shell_cmd( void )
{
    bxsh_add_cmd( "rtc", prv_rtc_cmd_handler, "rtc test" );
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
void RTC_IRQHandler( void )
{
    if( BX_RTC->IS > 0 ) {
        uint32_t a = BX_RTC->EOI & 0x01;
        BX_GPIOA->OD ^=  GPIO_PIN_3 ;
        //bxsh_logln( "RTC_IRQHandler" );
    }
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
