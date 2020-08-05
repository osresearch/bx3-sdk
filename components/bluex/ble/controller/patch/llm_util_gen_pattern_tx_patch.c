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

#include <string.h>
#include <stdbool.h>
#include "bx_sys_config.h"
#include "apollo_00_ble_reg.h"
#include "co_bt_defines.h"
#include "bx_dbg.h"
#include "patch.h"
#include "modem.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
#if ((RF_PARAM == 1) || (RF_PARAM == 2) || (RF_PARAM == 3))
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void llm_util_gen_pattern_tx_patch( uint8_t pattern_type, uint8_t payload_len, uint8_t * payload )
{
    set_deriv_calib_0( 2 );
    uint8_t pattern = 0;
    // get the pattern
    switch( pattern_type ) {
        case PAYL_11110000:
            pattern = 0xF0;
            break;
        case PAYL_10101010:
            pattern = 0xAA;
            set_deriv_calib_0( 3 );
            break;
        case PAYL_ALL_1:
            pattern = 0xFF;
            break;
        case PAYL_ALL_0:
            pattern = 0x00;
            break;
        case PAYL_00001111:
            pattern = 0x0F;
            break;
        case PAYL_01010101:
            pattern = 0x55;
            set_deriv_calib_0( 3 );
            break;
        default:
//            ASSERT_ERR(pattern_type < PAYL_END);
            break;
    }
    memset( payload, pattern, payload_len );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_llm_util_gen_pattern_tx_patch( void )
{
    uint32_t code = cal_patch_bl( 0x1a7ba, ( uint32_t )llm_util_gen_pattern_tx_patch - 1 );
    uint32_t * src_low = ( uint32_t * )0x1a7b8;
    uint32_t * src_high = ( uint32_t * )0x1a7bc;
    uint8_t patch_no[2];
    if( patch_alloc( &patch_no[0] ) == false ) {
        BX_ASSERT( 0 );
    }
    patch_entrance_exit_addr( patch_no[0], ( uint32_t )src_low, ( code & 0xffff ) << 16 | *src_low & 0xffff );
    PATCH_ENABLE( patch_no[0] );
    if( patch_alloc( &patch_no[1] ) == false ) {
        BX_ASSERT( 0 );
    }
    patch_entrance_exit_addr( patch_no[1], ( uint32_t )src_high, ( code & 0xffff0000 ) >> 16 | *src_high & 0xffff0000 );
    PATCH_ENABLE( patch_no[1] );
}
#endif

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


