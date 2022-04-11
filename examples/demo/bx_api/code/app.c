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
#include "us_test.h"

#include <stdarg.h>
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
static u32 a = 1;


/*============================= private function =============================*/
void test( void * data )
{
    bx_logln("testing...");
}

void test2( void * data )
{
    u32 value = *(u32 *)data;
    bx_logln("testing2...%u",value);
    *(u32 *)data = value + 1;
}

void test3( void * data )
{
    u32 value = *(u32 *)data;
    bx_logln("testing3...%u",value);
    if( value % 10 == 0  ) {
        bx_dwork_cancel(test3);
        bx_logln("cancel ");
    }
    *(u32 *)data = value + 1;
    bx_dwork( test3,&a,1000,1);
}

 
/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
//    us_test_register();
//    
//    u16 wide;
//    u16 high;
//    char name[16];
//    
//    bx_set( us_test_id(),USP_TEST_WIDE,100,NULL );
//    bx_set( us_test_id(),USP_TEST_HIGH,200,NULL );
//    bx_set( us_test_id(),USP_TEST_NAME,(u32)"my_names",NULL );
//    
//    bx_get( us_test_id(),USP_TEST_WIDE,(u32)&wide,NULL );
//    bx_get( us_test_id(),USP_TEST_HIGH,(u32)&high,NULL );
//    bx_get( us_test_id(),USP_TEST_NAME,(u32)&name,NULL );
    
    
    bx_dwork( test3,&a,1000,1);

}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



