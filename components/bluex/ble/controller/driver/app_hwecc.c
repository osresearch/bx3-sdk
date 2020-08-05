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
#include "app_hwecc.h"
#include "hwecc_typedef.h"
#include "bx_ring_queue.h"
#include "ll.h"
#include "co_utils.h"
#include "field_manipulate.h"
#include "log.h"

#include "rst_gen.h"
#include "clk_gate.h"
#include "periph_recovery.h"
#include "periph_mngt.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static app_hwecc_inst_t * hwecc_inst_env;

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
#define ECC_RAM(reg)            ((ecc_ram_t *)(reg)->ECC_RAM)


/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void hwecc_sys_stat( app_hwecc_inst_t * inst, uint32_t sys_stat )
{
    switch( sys_stat ) {
        case HWECC_INIT:
            recovery_list_add( cpu_domain_recovery_buf, CPU_DOMAIN_HWECC, &inst->inst );
            break;
        case HWECC_UNINIT:
            recovery_list_remove( cpu_domain_recovery_buf, CPU_DOMAIN_HWECC );
            break;
        case HWECC_START:
            cpu_domain_stat.hwecc = 1;
            break;
        case HWECC_DONE:
            cpu_domain_stat.hwecc = 0;
            break;
        default:
            LOG( LOG_LVL_WARN, "unexpected sys_stat:%d\n", sys_stat );
            break;
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void mem_to_reg( void * dst_addr, const void * src_addr, uint32_t length )
{
    BX_ASSERT( length % sizeof( uint32_t ) == 0 );
    uint32_t val;
    uint32_t i;
    uint32_t * dst = ( uint32_t * )dst_addr;
    uint8_t * src = ( uint8_t * )src_addr;
    for( i = 0; i < length / sizeof( uint32_t ); ++i ) {
        val = src[3] << 24 | src[2] << 16 | src[1] << 8 | src[0];
        *dst ++ = val;
        src += sizeof( uint32_t );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void reg_set( void * src_addr, uint32_t val, uint32_t length )
{
    uint32_t i;
    uint32_t * src = ( uint32_t * )src_addr;
    for( i = 0; i < length; ++i ) {
        *src = val;
        src ++;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void hwecc_calculate_start( app_hwecc_inst_t * inst, ecc_in_t * in )
{
    hwecc_sys_stat( inst, HWECC_START );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_ECC );
    mem_to_reg( &ECC_RAM( inst->reg )->block[15], in->secret_key, ECC_BLOCK_SIZE );
    mem_to_reg( &ECC_RAM( inst->reg )->block[5], in->public_key[0], ECC_BLOCK_SIZE );
    mem_to_reg( &ECC_RAM( inst->reg )->block[6], in->public_key[1], ECC_BLOCK_SIZE );
    reg_set   ( &ECC_RAM( inst->reg )->block[2], 0, ECC_BLOCK_SIZE / sizeof( uint32_t ) );
    reg_set   ( &ECC_RAM( inst->reg )->block[3], 0, ECC_BLOCK_SIZE / sizeof( uint32_t ) );
    reg_set   ( &ECC_RAM( inst->reg )->block[4], 0, ECC_BLOCK_SIZE / sizeof( uint32_t ) );
    reg_set   ( &ECC_RAM( inst->reg )->block[7], 0, ECC_BLOCK_SIZE / sizeof( uint32_t ) );
    reg_set   ( &ECC_RAM( inst->reg )->block[3], 1, 1 );
    reg_set   ( &ECC_RAM( inst->reg )->block[7], 1, 1 );
    inst->reg->START_BUSY = 1;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t app_hwecc_init( periph_inst_handle_t hdl )
{
    app_hwecc_inst_t * inst = CONTAINER_OF( hdl, app_hwecc_inst_t, inst );
    srst_cpu( ECC_SRST_CPU );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_ECC );
    NVIC_ClearPendingIRQ( ECC_IRQn );
    hwecc_inst_env = inst;
    NVIC_EnableIRQ( ECC_IRQn );
    
    ble_reg_ecc_t * reg = inst->reg;
    reg->START_SEL = FIELD_BUILD( ECC_ECC_WO_INV, With_Inversion ) | FIELD_BUILD( ECC_START_SEL_R, Full_ECC_Calc );
    reg->INTR_MASK = 1;
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_ECC );
    hwecc_sys_stat( inst, HWECC_INIT );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t app_hwecc_uninit( periph_inst_handle_t hdl )
{
    app_hwecc_inst_t * inst = CONTAINER_OF( hdl, app_hwecc_inst_t, inst );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_ECC );
    NVIC_DisableIRQ( ECC_IRQn );
    hwecc_sys_stat( inst, HWECC_UNINIT );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t app_hwecc_calculate( periph_inst_handle_t hdl, ecc_in_t * in, ecc_rslt_t * rslt )
{
    app_hwecc_inst_t * inst = CONTAINER_OF( hdl, app_hwecc_inst_t, inst );
    if( periph_lock( &inst->ecc_lock ) == false ) {
        return PERIPH_BUSY;
    }
    inst->rslt = *rslt;
    hwecc_calculate_start( inst, in );
    return PERIPH_NO_ERROR;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_hwecc_isr( app_hwecc_inst_t * inst )
{
    inst->reg->INTR_CLR = 1;
    ecc_rslt_t * ptr = &inst->rslt;
    void ( *callback )( void * ) = ptr->callback;
    void * cb_param = ptr->dummy;
    memcpy( ptr->out.key[0], &ECC_RAM( inst->reg )->block[12], ECC_BLOCK_SIZE );
    memcpy( ptr->out.key[1], &ECC_RAM( inst->reg )->block[13], ECC_BLOCK_SIZE );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_ECC );
    hwecc_sys_stat( inst, HWECC_DONE );
    periph_unlock( &inst->ecc_lock );
    callback( cb_param );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ECC_IRQHandler( void )
{
    app_hwecc_isr( hwecc_inst_env );
}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

