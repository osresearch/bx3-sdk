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
/* config -------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "patch.h"
#include "log.h"
#include "co_bt_defines.h"
#include "compiler_flag.h"

/* private define ------------------------------------------------------------*/
#define SLAVE_FINETIMECNT_PATCH_ADDR 0x17670

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

void SLAVE_FINETIMECNT_PATCH( void );

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint64_t finetimecnt_recalculate( uint32_t uncheck_val, uint32_t * origin )
{
    uint64_t rslt;
    if( uncheck_val > *origin ) {
        rslt = 0;
        rslt <<= 32;
        rslt |= 11; //12 slot 7.5ms
    } else {
        rslt = uncheck_val % SLOT_SIZE;
        rslt <<= 32;
        rslt |= uncheck_val / SLOT_SIZE;
    }
    return rslt;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_slave_finetimecnt_patch()
{
    uint32_t code = cal_patch_bl( SLAVE_FINETIMECNT_PATCH_ADDR, ( uint32_t )SLAVE_FINETIMECNT_PATCH - 1 );
    uint8_t patch_no;
    if( patch_alloc( &patch_no ) == false ) {
        BX_ASSERT( 0 );
    }
    patch_entrance_exit_addr( patch_no, SLAVE_FINETIMECNT_PATCH_ADDR, code );
    PATCH_ENABLE( patch_no );

}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

