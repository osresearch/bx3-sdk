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
#include "flash_wrapper.h"
#include "log.h"
/* private define ------------------------------------------------------------*/
#define user_flash_adress   0x20000
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
void app_init( void )
{
    u8 w_value = 0xef;
    u8 r_value = 0x00;
    flash_erase( user_flash_adress, Sector_Erase );

    flash_program( user_flash_adress, 1, &w_value );

    flash_multi_read( user_flash_adress, 1, &r_value );
    LOG_RAW( "r_vaule=%02x\r\n\r\n", r_value );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


