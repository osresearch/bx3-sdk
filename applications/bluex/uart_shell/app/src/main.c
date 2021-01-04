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
/* config ------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include <stdio.h>

/* include platform config  exp:apollo00 apollo01 */
//#include "apolloxx_cfg.h"


/* include board config  exp:EVK DVK */
//#include "board_cfg.h"


/* include component config exp:os fs ble */
//#include "component_cfg.h"


/* include device config exp: sensor module */
//#include "device_cfg.h"


/* include user.h */

#include "apollo_00_reg.h"

#include "printf_demo.h"
#include "uart_shell_demo.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
int main( void )
{
    /* peripheral init */

    /* board */

    /* component */

    /* device */

    /* user */

    __DMB();
    SCB->VTOR = APOLLO_00_VTOR_BASE;
    __DSB();
    
    uart_shell_test();
    
    while( 1 );
}


/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



