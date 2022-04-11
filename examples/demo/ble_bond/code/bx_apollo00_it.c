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
#include "bx_apollo00_it.h"

#include "bxd_gpio.h"

#include "bxe_matrix_keyboard_wakeup.h"
#include "bx_kernel.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================ interrupt function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
u32 ext_int_stat_2_pin_state( u32 ext_int_stat )
{
    u32 ret = 0;
    u32 temp = 0;

    for( u32 i = 0; i < 5; i++ ) {
        if( ext_int_stat & ( 0x01 << i ) ) {
            switch( i ) {
                case 0: {
                    bx_dwork( key_scan_process, NULL, 10, BX_FOREVER );
                    temp = 0x01 << 15;
                }
                break;

                case 1: {
                    bx_dwork( key_scan_process, NULL, 10, BX_FOREVER );

                    temp = 0x01 << 16;
                }
                break;

                case 2: {
                    bx_dwork( key_scan_process, NULL, 10, BX_FOREVER );

                    temp = 0x01 << 17;
                }
                break;

                case 3: {
                    bx_dwork( key_scan_process, NULL, 10, BX_FOREVER );

                    temp = 0x01 << 22;
                }
                break;

                case 4: {
                    bx_dwork( key_scan_process, NULL, 10, BX_FOREVER );

                    temp = 0x01 << 23;
                }
                break;

                default:
                    break;
            }
        }
        ret |= temp;
    }
    return ret;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/

void EXT_INTR_IRQHandler( void )
{
    uint8_t ext_int_stat = BX_FIELD_RD( BX_AWO->EIVAL, AWO_EIVAL_VAL ) ;
    BX_AWO->EICLR |= ext_int_stat;
    u32 pin_state = ext_int_stat_2_pin_state( ext_int_stat );

//    LOG_I( "EXT_INTR_IRQHandler = %d,ext_int_stat=%d", pin_state ,ext_int_stat);
}


/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



