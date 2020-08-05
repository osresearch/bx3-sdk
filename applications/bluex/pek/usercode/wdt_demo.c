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
#include "wdt_demo.h"
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
void prv_wdt_init(void)
{
    
    BX_CPU->SRST |= CPU_SRST_CLR_WDT_N;
    BX_CPU->SRST |= CPU_SRST_SET_WDT_N;
    
    BX_CPU->CLKG1 |= CPU_CLKG1_SET_WDT;
     
    BX_CLR_BIT(BX_WDT->CTRL,WDT_CTRL_EN); 
    
    BX_MODIFY_REG(BX_WDT->CTRL,WDT_CTRL_RMOD,WDT_CTRL_RMOD_T_SYSTEM_RESET);
    //BX_MODIFY_REG(BX_WDT->CTRL,WDT_CTRL_RMOD,WDT_CTRL_RMOD_T_INTERRUPT_FIRST);
    //复位时的脉冲宽度
    BX_MODIFY_REG(BX_WDT->CTRL,WDT_CTRL_RST_PULSE_LEN,WDT_CTRL_RST_PULSE_LEN_T_4_PCLK_CYCLES);

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void prv_wdt_set_reset_time( void )
{   
//    bxsh_logln("BX_WDT->TR:%08X",BX_WDT->TR);
    BX_CPU->CLKG1 |= CPU_CLKG1_CLR_WDT;
    //BX_MODIFY_REG(BX_WDT->TR,WDT_TR_PERIOD,15);
    //BX_MODIFY_REG(BX_WDT->CR,WDT_CR_VAL,0X76);
    BX_CPU->CLKG1 |= CPU_CLKG1_SET_WDT;
//    bxsh_logln("BX_WDT->TR:%08X",BX_WDT->TR);
//    
//    bxsh_logln("BX_WDT->CCV:%d",BX_WDT->CCV);
    BX_SET_BIT(BX_WDT->CTRL,WDT_CTRL_EN); 
//    while(1){
//    uint32_t i = 0;
//        while(i++<0xFFFFF);
//        bxsh_logln("BX_WDT->CCV:%d",BX_WDT->CCV);
//    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void prv_wdt_stop( void )
{
    BX_CLR_BIT(BX_WDT->CTRL,WDT_CTRL_EN); 
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void prv_wdt_feed( void )
{
    __asm("nop");
    BX_MODIFY_REG(BX_WDT->CR,WDT_CR_VAL,0X76);
    bxsh_logln("BX_WDT->CCV:%d",BX_WDT->CCV);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_wdt_cmd_handler( char argc, char * argv )
{
    if ( argc > 1 ) {
        if ( !strcmp( "-h", &argv[argv[1]] ) ) {
            bxsh_logln( "useage: help [options]" );
            bxsh_logln( "options:" );
            bxsh_logln( "\t init \t: wdt init" );
            bxsh_logln( "\t start \t: reset later " );
            bxsh_logln( "\t stop \t: stop wdt " );
            bxsh_logln( "\t feed \t: feed dog " );
        } else if ( !strcmp( "init", &argv[argv[1]] ) ) {
            prv_wdt_init();
        } else if ( !strcmp( "start", &argv[argv[1]] ) ) {
            prv_wdt_set_reset_time();
        } else if ( !strcmp( "stop", &argv[argv[1]] ) ) {
            prv_wdt_stop();
        } else if ( !strcmp( "feed", &argv[argv[1]] ) ) {
            prv_wdt_feed();
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
void wdt_add_shell_cmd( void )
{
    bxsh_add_cmd( "wdt", prv_wdt_cmd_handler, "wdt test" );
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
void WDT_IRQHandler( void )
{
    BX_READ_BIT( BX_WDT->EOI,WDT_EOI_VAL);
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
