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
#include "cmd.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/



/*============================= private function =============================*/
void test1_cmd(void)
{
    bx_logln("test1_cmd");
}

void test2_cmd(void)
{
    bx_logln("test2_cmd");
}

void test3_cmd(void)
{
    bx_logln("test3_cmd");
}
REGISTER_CMD(test1, test1_cmd,test1 demo);
REGISTER_CMD(test2, test2_cmd,test2 demo);
REGISTER_CMD(test3, test3_cmd,test3 demo);


/*========================= end of private function ==========================*/

/*============================= exported function ============================*/

void my_parsing(void * data )
{
    static u8 uart_buff[128];
    static u32 rx_count=0;
    static u32 time_out = 10;
    while( BX_READ_BIT( BX_UART0->LS, UART_LS_DATA_READY ) ){
        uart_buff[rx_count++] = ( uint8_t )( BX_UART0->RTD );
        if( uart_buff[rx_count-1] == '\n'  ){
            uart_buff[rx_count-1] = 0;
            cmd_parsing((char *)uart_buff);
            rx_count = 0;
        }
        time_out = 10;
    }
    time_out--;
    if( time_out == 0 ){
        time_out = 10;
        rx_count = 0;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    cmd_init();
    bx_dwork(my_parsing,NULL,100,BX_FOREVER);
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



