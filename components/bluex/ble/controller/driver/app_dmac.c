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
#include <stddef.h>
#include "periph_common.h"
#include "periph_recovery.h"
#include "field_manipulate.h"
#include "dmac_typedef.h"
#include "app_dmac.h"
#include "co_utils.h"
#include "bx_dbg.h"
#include "ll.h"
#include "compiler_flag.h"
#include "rst_gen.h"
#include "clk_gate.h"

/* private define ------------------------------------------------------------*/
#define DMAC_MAX_BLOCK_TS       4095
#define INVALID_CHANNEL_NUM     0xff

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static app_dmac_inst_t * s_dmac_inst;


/* exported variables --------------------------------------------------------*/
dmac_ch_env_t g_dmac_ch_env[DMAC_CHANNEL_NUM];

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void dmac_sys_stat( app_dmac_inst_t * inst, uint32_t sys_stat )
{
    switch( sys_stat ) {
        case DMAC_INIT:
            recovery_list_add( cpu_domain_recovery_buf, CPU_DOMAIN_DMAC, &inst->inst );
            break;
        case DMAC_UNINIT:
            recovery_list_remove( cpu_domain_recovery_buf, CPU_DOMAIN_DMAC );
            break;
        case DMAC_TRANSFER_START:
            cpu_domain_stat.dmac = 1;
            break;
        case DMAC_TRANSFER_DONE:
            cpu_domain_stat.dmac = 0;
            break;
        default:
            //LOG( LOG_LVL_WARN, "unexpected sys_stat:%d\n", sys_stat );
            break;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint8_t dmac_ch_alloc( app_dmac_inst_t * inst )
{
    uint8_t i;
    for( i = 0; i < inst->env.ch_num; ++i ) {
        uint8_t ch_mask = 1 << i;
        bool ch_available;
        GLOBAL_INT_DISABLE();
        ch_available = ( inst->env.ch_stat & ch_mask ) == 0;
        if( ch_available ) {
            inst->env.ch_stat |= ch_mask;
        }
        GLOBAL_INT_RESTORE();
        if( ch_available ) {
            return i;
        }
    }
    return INVALID_CHANNEL_NUM;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION static void dmac_ch_free( app_dmac_inst_t * inst, uint8_t ch_idx )
{
    uint8_t free_ch_mask = ~( 1 << ch_idx );
    GLOBAL_INT_DISABLE();
    inst->env.ch_stat &= free_ch_mask;
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION static void dmac_block_ts_config( app_dmac_inst_t * inst, uint8_t ch_idx )
{
    ble_reg_dmac_t * reg = inst->reg;
    if( inst->env.ch[ch_idx].size > DMAC_MAX_BLOCK_TS ) {
        FIELD_WR( &reg->ch[ch_idx], ctl_h, DMAC_BLOCK_TS, DMAC_MAX_BLOCK_TS );
    } else {
        FIELD_WR( &reg->ch[ch_idx], ctl_h, DMAC_BLOCK_TS, inst->env.ch[ch_idx].size );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION static void dmac_stat_clean_if_all_transfer_done( app_dmac_inst_t * inst )
{
    GLOBAL_INT_DISABLE();
    if( inst->env.ch_stat == 0 && inst->reg->status_tfr_l == 0 && inst->reg->status_err_l == 0 ) {
        ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_DMAC );
        dmac_sys_stat( inst, DMAC_TRANSFER_DONE );
    }
    GLOBAL_INT_RESTORE();
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :   Initialize APP_DMAC module
 * @note    :
 * @param   :   hdl[in] the peripheral common instance handler(pointer) for the DMAC instance
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t app_dmac_init( periph_inst_handle_t hdl )
{
    app_dmac_inst_t * inst = CONTAINER_OF( hdl, app_dmac_inst_t, inst );
    srst_cpu( DMAC_SRST_CPU );

    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_DMAC );

    NVIC_ClearPendingIRQ( DMAC_IRQn );
    s_dmac_inst = inst;
    NVIC_EnableIRQ( DMAC_IRQn );

    ble_reg_dmac_t * reg = inst->reg;
    reg->dma_cfg_reg_l = FIELD_BUILD( DMAC_DMA_EN, DMAC_Enabled );
    uint8_t ch_mask = ( 1 << inst->env.ch_num ) - 1;
    reg->mask_err_l = FIELD_BUILD( DMAC_INT_MASK, ch_mask ) | FIELD_BUILD( DMAC_INT_MASK_WE, ch_mask );
    reg->mask_tfr_l = FIELD_BUILD( DMAC_INT_MASK, ch_mask ) | FIELD_BUILD( DMAC_INT_MASK_WE, ch_mask );
    dmac_sys_stat( inst, DMAC_INIT );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_DMAC );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :   De Initialize APP_DMAC module
 * @note    :
 * @param   :   hdl[in] the peripheral common instance handler(pointer) for the DMAC instance
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t app_dmac_uninit( periph_inst_handle_t hdl )
{
    app_dmac_inst_t * inst = CONTAINER_OF( hdl, app_dmac_inst_t, inst );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_DMAC );
    NVIC_DisableIRQ( DMAC_IRQn );
    dmac_sys_stat( inst, DMAC_UNINIT );
    return PERIPH_NO_ERROR;
}

/** ---------------------------------------------------------------------------
 * @brief   :   Start a dma transfer
 * @note    :
 * @param   :   [in]hdl             the peripheral common instance handler(pointer) for the DMAC instance
 *              [in]param           parameter for the transfer
 *              [out]channel_idx    used in this transfer
 * @retval  :   error code
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_dmac_start( periph_inst_handle_t hdl, app_dmac_transfer_param_t * param, uint8_t * channel_idx )
{
    app_dmac_inst_t * inst = CONTAINER_OF( hdl, app_dmac_inst_t, inst );
    uint8_t ch_idx = dmac_ch_alloc( inst );
    if( ch_idx == INVALID_CHANNEL_NUM ) {
        return PERIPH_DMAC_NO_AVAILABLE_CHANNEL;
    }
    inst->env.ch[ch_idx].callback = param->callback;
    inst->env.ch[ch_idx].callback_param = param->callback_param;
    inst->env.ch[ch_idx].size = param->length;
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_DMAC );
    dmac_sys_stat( inst, DMAC_TRANSFER_START );
    dmac_block_ts_config( inst, ch_idx );
    uint8_t sinc, dinc;

    if( param->tt_fc == Peripheral_to_Memory_DMAC_Flow_Controller ) {
        sinc = Address_No_Change;
        dinc = Address_Increment;
    } else if( param->tt_fc == Memory_to_Peripheral_DMAC_Flow_Controller ) {
        sinc = Address_Increment;
        dinc = Address_No_Change;
    } else if( param->tt_fc == Memory_to_Memory_DMAC_Flow_Controller ) {
        sinc = Address_Increment;
        dinc = Address_Increment;
    } else {
        BX_ASSERT( 0 );
    }

    ble_reg_dmac_t * reg = inst->reg;
    reg->ch[ch_idx].ctl_l = FIELD_BUILD( DMAC_TT_FC, param->tt_fc ) |
                            FIELD_BUILD( DMAC_SRC_MSIZE, param->src_msize ) | FIELD_BUILD( DMAC_DEST_MSIZE, param->dst_msize ) |
                            FIELD_BUILD( DMAC_SINC, sinc ) | FIELD_BUILD( DMAC_DINC, dinc ) |
                            FIELD_BUILD( DMAC_SRC_TR_WIDTH, param->src_tr_width ) | FIELD_BUILD( DMAC_DST_TR_WIDTH, param->dst_tr_width ) |
                            FIELD_BUILD( DMAC_INT_EN, param->int_en );
    reg->ch[ch_idx].cfg_l = FIELD_BUILD( DMAC_SRC_HS_POL, HS_Polarity_Active_High ) | FIELD_BUILD( DMAC_DST_HS_POL, HS_Polarity_Active_High ) |
                            FIELD_BUILD( DMAC_HS_SEL_SRC, Hardware_Handshaking ) | FIELD_BUILD( DMAC_HS_SEL_DST, Hardware_Handshaking );
    reg->ch[ch_idx].cfg_h = FIELD_BUILD( DMAC_DEST_PER, param->dst_per ) | FIELD_BUILD( DMAC_SRC_PER, param->src_per ) |
                            FIELD_BUILD( DMAC_FIFO_MODE, 1 );
    reg->ch[ch_idx].sar_l = ( uint32_t )param->src;
    reg->ch[ch_idx].dar_l = ( uint32_t )param->dst;
    reg->ch_en_reg_l = FIELD_BUILD( DMAC_CH_EN, 1 << ch_idx ) | FIELD_BUILD( DMAC_CH_EN_WE, 1 << ch_idx );
    if( channel_idx ) {
        *channel_idx = ch_idx;
    }
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :   [in]hdl                 the peripheral common instance handler(pointer) for the DMAC instance
 *              [in]ch_idx              channel index for which to wait
 *              [out]remaining_size     the dma hasn't transferred size
 * @retval  :   error code
-----------------------------------------------------------------------------*/
periph_err_t app_dmac_transfer_cancel( periph_inst_handle_t hdl, uint8_t ch_idx, uint32_t * remaining_size )
{
    app_dmac_inst_t * inst = CONTAINER_OF( hdl, app_dmac_inst_t, inst );
    periph_err_t error;
    ble_reg_dmac_t * reg = inst->reg;
    NVIC_DisableIRQ( DMAC_IRQn );
    if( inst->env.ch_stat & 1 << ch_idx ) {
        REG_FIELD_WR( reg->ch[ch_idx].cfg_l, DMAC_CH_SUSP, 1 );
        if( reg->status_tfr_l & 1 << ch_idx ) {
            reg->clear_tfr_l = 1 << ch_idx;
        }
        error = PERIPH_NO_ERROR;
    } else {
        error =  PERIPH_STATE_ERROR;
    }

    NVIC_ClearPendingIRQ( DMAC_IRQn );
    s_dmac_inst = inst;
    NVIC_EnableIRQ( DMAC_IRQn );

    if( error == PERIPH_NO_ERROR ) {
        while( REG_FIELD_RD( reg->ch[ch_idx].cfg_l, DMAC_FIFO_EMPTY ) == 0 );
        reg->ch_en_reg_l = FIELD_BUILD( DMAC_CH_EN, 0 ) | FIELD_BUILD( DMAC_CH_EN_WE, 1 << ch_idx );
        inst->env.ch[ch_idx].size -= REG_FIELD_RD( reg->ch[ch_idx].ctl_h, DMAC_BLOCK_TS );
        dmac_ch_free( inst, ch_idx );
        dmac_stat_clean_if_all_transfer_done( inst );
        if( remaining_size ) {
            *remaining_size = inst->env.ch[ch_idx].size;
        }
    }
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :   Wait for a dma transfer done (can only be applied to non-interrupt transfer)
 * @note    :
 * @param   :   hdl[in]     the peripheral common instance handler(pointer) for the DMAC instance
 *              ch_idx[in]  channel index for which to wait
 * @retval  :   error code
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_dmac_transfer_wait( periph_inst_handle_t hdl, uint8_t ch_idx )
{
    app_dmac_inst_t * inst = CONTAINER_OF( hdl, app_dmac_inst_t, inst );
    ble_reg_dmac_t * reg = inst->reg;
    if( ch_idx >= inst->env.ch_num ) {
        return PERIPH_INVALID_PARAM;
    }
    if( reg->ch_en_reg_l & 1 << ch_idx == 0 ) {
        return PERIPH_STATE_ERROR;
    }
    if( REG_FIELD_RD( reg->ch[ch_idx].ctl_l, DMAC_INT_EN ) != 0 ) {
        return PERIPH_INVALID_OPERATION;
    }
    while( 1 ) {
        while( ( reg->raw_tfr_l & 1 << ch_idx ) == 0 );
        reg->clear_tfr_l = 1 << ch_idx;
        inst->env.ch[ch_idx].size -= REG_FIELD_RD( reg->ch[ch_idx].ctl_h, DMAC_BLOCK_TS );
        if( inst->env.ch[ch_idx].size == 0 ) {
            break;
        }
        dmac_block_ts_config( inst, ch_idx );
        reg->ch_en_reg_l = FIELD_BUILD( DMAC_CH_EN, 1 << ch_idx ) | FIELD_BUILD( DMAC_CH_EN_WE, 1 << ch_idx );
    }
    dmac_ch_free( inst, ch_idx );
    dmac_stat_clean_if_all_transfer_done( inst );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint16_t dmac_get_max_block_transfer_size()
{
    return DMAC_MAX_BLOCK_TS;
}

/** ---------------------------------------------------------------------------
 * @brief   :   Get enumeration of burst transaction size
 * @note    :
 * @param   :   msize[in]   Burst Size in bytes
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t dmac_get_burst_transaction_size_enum( uint16_t msize )
{
    if( msize ==  1 ) {
        return Burst_Transaction_Length_1;
    }
    uint8_t val = 0;
    switch( msize ) {
        case 4:
            val = Burst_Transaction_Length_4;
            break;
        case 8:
            val = Burst_Transaction_Length_8;
            break;
        case 16:
            val = Burst_Transaction_Length_16;
            break;
        case 32:
            val = Burst_Transaction_Length_32;
            break;
        case 64:
            val = Burst_Transaction_Length_64;
            break;
        case 128:
            val = Burst_Transaction_Length_128;
            break;
        case 256:
            val = Burst_Transaction_Length_256;
            break;
        default:
            BX_ASSERT( 0 );
            break;
    }
    return val;
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
static void dmac_tfr_isr( app_dmac_inst_t * inst, uint8_t ch_idx )
{
    ble_reg_dmac_t * reg = inst->reg;
    inst->env.ch[ch_idx].size -= REG_FIELD_RD( reg->ch[ch_idx].ctl_h, DMAC_BLOCK_TS );
    if( inst->env.ch[ch_idx].size ) {
        dmac_block_ts_config( inst, ch_idx );
        reg->ch_en_reg_l = FIELD_BUILD( DMAC_CH_EN, 1 << ch_idx ) | FIELD_BUILD( DMAC_CH_EN_WE, 1 << ch_idx );
    } else {
        void ( *cb )( void * ) = inst->env.ch[ch_idx].callback;
        void * param = inst->env.ch[ch_idx].callback_param;
        dmac_ch_free( inst, ch_idx );
        cb( param );
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_dmac_isr( app_dmac_inst_t * inst )
{
    ble_reg_dmac_t * reg = inst->reg;
    BX_ASSERT( reg->status_err_l == 0 );
    while( reg->status_tfr_l ) {
        uint8_t i;
        for( i = 0; i < inst->env.ch_num; ++i ) {
            if( reg->status_tfr_l & 1 << i ) {
                reg->clear_tfr_l = 1 << i;
                dmac_tfr_isr( inst, i );
            }
        }
    }
    dmac_stat_clean_if_all_transfer_done( inst );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void DMAC_IRQHandler()
{
    app_dmac_isr( s_dmac_inst );
}

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
