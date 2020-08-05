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
#include "rwip_config.h"
#include "rwble_config.h"
#include "em_buf.h"
#include "bx_dbg.h"
#include "patch.h"

/* private define ------------------------------------------------------------*/
#define LLD_PDU_TX_FLUSH_LIST_PATCH_ADDR 0x1862c
/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

void LLD_PDU_TX_FLUSH_LIST_PATCH( void );

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t lld_pdu_tx_flush_patch_c( struct em_desc_node * txnode, uint8_t tx_cnt )
{
    bool buffer_flushed;
    // Free the buffer
    GLOBAL_INT_DISABLE();
    buffer_flushed = em_buf_tx_free( txnode );
    GLOBAL_INT_RESTORE();
    if( buffer_flushed ) {
        tx_cnt++;
    }
    return tx_cnt;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void set_lld_pdu_tx_flush_patch()
{
    uint32_t code = cal_patch_bl( LLD_PDU_TX_FLUSH_LIST_PATCH_ADDR, ( uint32_t )LLD_PDU_TX_FLUSH_LIST_PATCH - 1 );
    uint8_t patch_no;
    if( patch_alloc( &patch_no ) == false ) {
        BX_ASSERT( 0 );
    }
    patch_entrance_exit_addr( patch_no, LLD_PDU_TX_FLUSH_LIST_PATCH_ADDR, code );
    PATCH_ENABLE( patch_no );
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
