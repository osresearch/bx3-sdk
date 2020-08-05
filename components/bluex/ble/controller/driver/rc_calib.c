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
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "reg_sysc_cpu.h"
#include "reg_sysc_cpu_apollo_00.h"
#include "log.h"
#include "rc_calib.h"
#include "rtc.h"

/* private define ------------------------------------------------------------*/
#define portMAX_32_BIT_NUMBER       (0xffffffff)
/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
uint32_t calib32k;
uint8_t rc_calib_10s = 0;
/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rc_calib_start()
{
    sysc_cpu_calb32k_start_setf( 1 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rc_calib_end( bool wait )
{
    uint32_t i = 0;
    while( !( sysc_cpu_calb32k_start_getf() == 0 ) ) {
        if( wait == false ) {
            return;
        }
        i++;
    }
    if( wait ) {
        //LOG( LOG_LVL_INFO, "rc_calib loop count i=%d\n", i );
    }
    calib32k = sysc_cpu_calb32k_rslt_getf();
    BX_ASSERT( calib32k );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint32_t get_rc32k_calib_val()
{
    return calib32k;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rc_test_start( void )
{
    static uint32_t tick_count_last = 0;
    uint32_t tick_count_current = RTC_CURRENTCNT_GET();
    uint32_t tick_temp;
    if( tick_count_current > tick_count_last ) {
        tick_temp = tick_count_current - tick_count_last;
    } else if( tick_count_current < tick_count_last ) {
        tick_temp = ( portMAX_32_BIT_NUMBER - tick_count_last ) + tick_count_current;
    }

    if( ( tick_temp >= 0x40000 ) && ( 0 == rc_calib_10s ) ) {
        tick_count_last = tick_count_current;
        rc_calib_start(); //开始校准
        rc_calib_10s = 1;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rc_test_end( void )
{
    if( 1 == rc_calib_10s ) {
        rc_calib_end( true );
        rc_calib_10s = 0;
    }
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

