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
#include "app.h"
#include "elog.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/



/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
int fputc( int ch, FILE * f )
{
    while( BX_READ_BIT( BX_UART0->LS, UART_LS_TX_EMPTY ) == 0 );
    BX_UART0->RTD = ch;
    return ch;
}

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

void my_log_test(void * data)
{
    log_a("Hello EasyLogger assert!");
    log_e("Hello EasyLogger error!");
    log_w("Hello EasyLogger warning!");
    log_i("Hello EasyLogger info!");
    log_d("Hello EasyLogger debug!");
    log_v("Hello EasyLogger verbose!");
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    elog_init();
    elog_set_text_color_enabled(true);
    elog_start();
    
    bx_dwork(my_log_test,NULL,1000,BX_FOREVER);
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



