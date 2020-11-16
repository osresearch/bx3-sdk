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
#include "field_manipulate.h"
#include "app_qspi.h"
#include "dw_apb_ssi_typedef.h"
#include "app_dmac_wrapper.h"
#include "log.h"
#include "compiler_flag.h"
#include "clk_gate.h"
#include "rst_gen.h"
#include "sysctrl.h"
#include "reg_sysc_cpu_apollo_00.h"

/* private define ------------------------------------------------------------*/
#define SUPPORT_XMC_FLASH_VERDOR            0
#define QSPI_FIFO_DEPTH                     64


/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
#define ADDR_EXTEND( addr, lsb )                        ( ( addr ) << 8 | ( lsb ) )

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void qspi_sys_stat( app_qspi_inst_t * inst, uint32_t sys_stat )
{
    switch( sys_stat ) {
        case QSPI_INIT:
            break;
        case QSPI_UNINIT:
            break;
        case QSPI_OP_START:
            break;
        case QSPI_OP_DONE:
            break;
        default:
            LOG( LOG_LVL_WARN, "unexpected sys stat: %d\n", sys_stat );
            break;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void qspi_pin_cfg( app_qspi_inst_t * inst, uint8_t pin_num, uint32_t pin_role, bool enable )
{
    switch( pin_role ) {
        case QSPI_CLK_PIN:
            hwp_sysc_cpu->pin_share_en.bit_field.qspi_en = 3;
            sysctrl_io_config( 25, QSPI_CLK );
            break;
        case QSPI_D0_PIN:
            sysctrl_io_config( 26, QSPI_D0 );
            break;
        case QSPI_D1_PIN:
            sysctrl_io_config( 27, QSPI_D1 );
            break;
        case QSPI_D2_PIN:
            hwp_sysc_cpu->pin_share_en.bit_field.qspi_en = 0xf;
            sysctrl_io_config( 28, QSPI_D2 );
            break;
        case QSPI_D3_PIN:
            sysctrl_io_config( 29, QSPI_D3 );
            break;
        case QSPI_CS0_PIN:
            sysctrl_io_config( 24, QSPI_CS );
            break;
        default:
            BX_ASSERT( 0 );
            break;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION static void qspi_std_byte_write_dma_start( ble_reg_ssi_t * reg, uint8_t cs_sel_mask, uint8_t * data, uint32_t length )
{
    app_dmac_transfer_param_t dma_param;
    dma_param.src = data;
    dma_param.dst = ( uint8_t * )&reg->DR;
    dma_param.length = length;
    dma_param.src_tr_width = Transfer_Width_8_bits;
    dma_param.dst_tr_width = Transfer_Width_8_bits;
    dma_param.src_msize = Burst_Transaction_Length_4;
    dma_param.dst_msize = Burst_Transaction_Length_4;
    dma_param.tt_fc = Memory_to_Peripheral_DMAC_Flow_Controller;
    dma_param.src_per = dmac_qspi_rx_handshake_enum( 0 );
    dma_param.dst_per = dmac_qspi_tx_handshake_enum( 0 );
    dma_param.int_en = Interrupt_Disabled;
    uint8_t ch_idx;
    periph_err_t error = app_dmac_start_wrapper( &dma_param, &ch_idx );
    BX_ASSERT( error == PERIPH_NO_ERROR );
    reg->SER = cs_sel_mask;
    error = app_dmac_transfer_wait_wrapper( ch_idx );
    BX_ASSERT( error == PERIPH_NO_ERROR );
    while( FIELD_RD( reg, SR, SSI_TFE ) == Transmit_FIFO_Not_Empty );
    while( FIELD_RD( reg, SR, SSI_BUSY ) == SSI_Busy );
    reg->SSIENR = SSI_Disabled;
    reg->SER = 0;
#if SUPPORT_XMC_FLASH_VERDOR
    qspi_flush_fifo_data( reg, 64 );
#endif
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_init( periph_inst_handle_t hdl )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    srst_cpu( QSPI_SRST_CPU );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_QSPI );
    qspi_pin_cfg( inst, inst->param.clk_pin_no, QSPI_CLK_PIN, true );
    if( inst->param.multi_read.dual_quad == Quad_SPI_Format ) {
        qspi_pin_cfg( inst, inst->param.data_pin_no[3], QSPI_D3_PIN, true );
        qspi_pin_cfg( inst, inst->param.data_pin_no[2], QSPI_D2_PIN, true );
    }
    qspi_pin_cfg( inst, inst->param.data_pin_no[0], QSPI_D0_PIN, true );
    qspi_pin_cfg( inst, inst->param.data_pin_no[1], QSPI_D1_PIN, true );
    uint8_t i;
    uint8_t pin_role;
    for( i = 0, pin_role = QSPI_CS0_PIN; i < QSPI_CS_NUM; ++i, ++pin_role ) {
        qspi_pin_cfg( inst, inst->param.cs_pin_no[i], pin_role, true );
    }
    inst->reg->SSIENR = SSI_Disabled;
    inst->reg->BAUDR = inst->param.clk_div;
    inst->reg->RXSAMPLE_DLY = inst->param.rxsample_dly;
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_QSPI );
    qspi_sys_stat( inst, QSPI_INIT );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_uninit( periph_inst_handle_t hdl )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    if( periph_lock_state_get( &inst->qspi_lock ) ) {
        return PERIPH_BUSY;
    }
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_QSPI );
    qspi_sys_stat( inst, QSPI_UNINIT );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION static void qspi_std_byte_write_dma_config( ble_reg_ssi_t * reg, uint16_t fifo_depth )
{
    reg->CTRLR0 = FIELD_BUILD( SSI_SPI_FRF, Standard_SPI_Format ) | FIELD_BUILD( SSI_DFS, DFS_32_8_bits ) | FIELD_BUILD( SSI_TMOD, Transmit_Only ) |
                  FIELD_BUILD( SSI_SCPOL, Inactive_Low ) | FIELD_BUILD( SSI_SCPH, SCLK_Toggle_In_Middle ) | FIELD_BUILD( SSI_FRF, Motorola_SPI );
    reg->DMATDLR = fifo_depth - 4;
    reg->DMACR = 0;
    reg->DMACR = FIELD_BUILD( SSI_TDMAE, Transmit_DMA_Enabled );
    reg->SSIENR = SSI_Enabled;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
#if SUPPORT_XMC_FLASH_VERDOR
N_XIP_SECTION static void qspi_flush_fifo_data( ble_reg_ssi_t * reg, uint8_t depth )
{
    reg->SSIENR = SSI_Enabled;
    uint8_t i;
    for( i = 0; i < depth; ++i ) {
        reg->DR = 0;
    }
    reg->SSIENR = SSI_Disabled;

}
#endif /* SUPPORT_XMC_FLASH_VERDOR */

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_std_write( periph_inst_handle_t hdl, uint8_t cs_sel_mask, uint8_t * data, uint32_t length )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    uint16_t fifo_depth = QSPI_FIFO_DEPTH;
    ble_reg_ssi_t * reg = inst->reg;
    if( periph_lock( &inst->qspi_lock ) == false ) {
        return PERIPH_BUSY;
    }
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_QSPI );
    qspi_sys_stat( inst, QSPI_OP_START );
    qspi_std_byte_write_dma_config( reg, fifo_depth );
    qspi_std_byte_write_dma_start( reg, cs_sel_mask, data, length );
    qspi_sys_stat( inst, QSPI_OP_DONE );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_QSPI );
    periph_unlock( &inst->qspi_lock );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_std_write_no_dma( periph_inst_handle_t hdl, uint8_t cs_sel_mask, uint8_t * data, uint16_t length )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    uint16_t fifo_depth = QSPI_FIFO_DEPTH;
    BX_ASSERT( length <= fifo_depth );
    ble_reg_ssi_t * reg = inst->reg;
    if( periph_lock( &inst->qspi_lock ) == false ) {
        return PERIPH_BUSY;
    }
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_QSPI );
    qspi_sys_stat( inst, QSPI_OP_START );
    reg->CTRLR0 = FIELD_BUILD( SSI_SPI_FRF, Standard_SPI_Format ) | FIELD_BUILD( SSI_DFS, DFS_32_8_bits ) | FIELD_BUILD( SSI_TMOD, Transmit_Only ) |
                  FIELD_BUILD( SSI_SCPOL, Inactive_Low ) | FIELD_BUILD( SSI_SCPH, SCLK_Toggle_In_Middle ) | FIELD_BUILD( SSI_FRF, Motorola_SPI );
    reg->SSIENR = SSI_Enabled;
    uint16_t i;
    for( i = 0; i < length; ++i ) {
        reg->DR = data[i];
    }
    reg->SER = cs_sel_mask;
    while( FIELD_RD( reg, SR, SSI_TFE ) == Transmit_FIFO_Not_Empty );
    while( FIELD_RD( reg, SR, SSI_BUSY ) == SSI_Busy );
    reg->SSIENR = SSI_Disabled;
    reg->SER = 0;
    qspi_sys_stat( inst, QSPI_OP_DONE );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_QSPI );
    periph_unlock( &inst->qspi_lock );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_flash_program( periph_inst_handle_t hdl, uint8_t cs_sel_mask, uint8_t cmd, uint32_t addr, uint8_t * data, uint32_t length )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    uint16_t fifo_depth = QSPI_FIFO_DEPTH;
    if( periph_lock( &inst->qspi_lock ) == false ) {
        return PERIPH_BUSY;
    }
    ble_reg_ssi_t * reg = inst->reg;
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_QSPI );
    qspi_sys_stat( inst, QSPI_OP_START );
    qspi_std_byte_write_dma_config( reg, fifo_depth );
    reg->DR = cmd;
    reg->DR = addr >> 16 & 0xff;
    reg->DR = addr >> 8 & 0xff;
    reg->DR = addr & 0xff;
    qspi_std_byte_write_dma_start( reg, cs_sel_mask, data, length );
    qspi_sys_stat( inst, QSPI_OP_DONE );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_QSPI );
    periph_unlock( &inst->qspi_lock );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_std_read( periph_inst_handle_t hdl, uint8_t cs_sel_mask, uint8_t * cmd_buf, uint8_t cmd_len, uint8_t * data_buf, uint16_t data_len )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    if( periph_lock( &inst->qspi_lock ) == false ) {
        return PERIPH_BUSY;
    }
    ble_reg_ssi_t * reg = inst->reg;
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_QSPI );
    qspi_sys_stat( inst, QSPI_OP_START );
    reg->CTRLR0 = FIELD_BUILD( SSI_SPI_FRF, Standard_SPI_Format ) | FIELD_BUILD( SSI_DFS, DFS_32_8_bits ) | FIELD_BUILD( SSI_TMOD, EEPROM_Read ) |
                  FIELD_BUILD( SSI_SCPOL, Inactive_Low ) | FIELD_BUILD( SSI_SCPH, SCLK_Toggle_In_Middle ) | FIELD_BUILD( SSI_FRF, Motorola_SPI );
    reg->CTRLR1 = data_len - 1;
    reg->DMARDLR = 7;
    reg->DMACR = 0;
    reg->DMACR = FIELD_BUILD( SSI_RDMAE, Receive_DMA_Enabled );
    reg->SSIENR = SSI_Enabled;
    uint8_t i;
    for( i = 0; i < cmd_len; ++i ) {
        reg->DR = cmd_buf[i];
    }
    app_dmac_transfer_param_t dma_param;
    dma_param.src = ( uint8_t * )&reg->DR;
    dma_param.dst = data_buf;
    dma_param.length = data_len;
    dma_param.src_tr_width = Transfer_Width_8_bits;
    dma_param.dst_tr_width = Transfer_Width_8_bits;
    dma_param.src_msize = Burst_Transaction_Length_8;
    dma_param.dst_msize = Burst_Transaction_Length_8;
    dma_param.tt_fc = Peripheral_to_Memory_DMAC_Flow_Controller;
    dma_param.src_per = dmac_qspi_rx_handshake_enum( 0 );
    dma_param.dst_per = dmac_qspi_tx_handshake_enum( 0 );
    dma_param.int_en = Interrupt_Disabled;
    uint8_t ch_idx;
    periph_err_t error = app_dmac_start_wrapper( &dma_param, &ch_idx );
    BX_ASSERT( error == PERIPH_NO_ERROR );
    reg->SER = cs_sel_mask;
    error = app_dmac_transfer_wait_wrapper( ch_idx );
    BX_ASSERT( error == PERIPH_NO_ERROR );
    reg->SSIENR = SSI_Disabled;
    reg->SER = 0;
    qspi_sys_stat( inst, QSPI_OP_DONE );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_QSPI );
    periph_unlock( &inst->qspi_lock );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_multi_read_32bits( periph_inst_handle_t hdl, uint8_t cs_sel_mask, uint32_t * data, uint16_t length, qspi_addr_data_t addr )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    if( periph_lock( &inst->qspi_lock ) == false ) {
        return PERIPH_BUSY;
    }
    qspi_sys_stat( inst, QSPI_OP_START );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_QSPI );
    ble_reg_ssi_t * reg = inst->reg;
    uint8_t wait_cycles;
    if( inst->param.multi_read.trans_type == Both_Standard_SPI_Mode ) {
        wait_cycles = inst->param.multi_read.wait_cycles - 8;
    } else {
        if( inst->param.multi_read.dual_quad == Quad_SPI_Format ) {
            wait_cycles = inst->param.multi_read.wait_cycles - 2;
        } else {
            wait_cycles = inst->param.multi_read.wait_cycles - 4;
        }
    }
    reg->SPI_CTRLR0 = FIELD_BUILD( SSI_WAIT_CYCLES, wait_cycles ) | FIELD_BUILD( SSI_INST_L, Instruction_Length_8_bits ) |
                      FIELD_BUILD( SSI_ADDR_L, Addr_Width_32_bits ) | FIELD_BUILD( SSI_TRANS_TYPE, inst->param.multi_read.trans_type );
    reg->CTRLR0 = FIELD_BUILD( SSI_SPI_FRF, inst->param.multi_read.dual_quad ) | FIELD_BUILD( SSI_DFS, DFS_32_32_bits ) | FIELD_BUILD( SSI_TMOD, Receive_Only ) |
                  FIELD_BUILD( SSI_SCPOL, Inactive_Low ) | FIELD_BUILD( SSI_SCPH, SCLK_Toggle_In_Middle ) | FIELD_BUILD( SSI_FRF, Motorola_SPI );
    reg->CTRLR1 = length - 1;
    reg->DMACR = 0;
    reg->SSIENR = SSI_Enabled;
    reg->DR = inst->param.multi_read.cmd;
    reg->DR = ADDR_EXTEND( addr.addr, addr.extend_byte );
    uint16_t fifo_depth = QSPI_FIFO_DEPTH;
    if( length > fifo_depth ) {
        reg->DMARDLR = 7;
        reg->DMACR = FIELD_BUILD( SSI_RDMAE, Receive_DMA_Enabled );
        app_dmac_transfer_param_t dma_param;
        dma_param.src = ( uint8_t * )&reg->DR_REVERSED;
        dma_param.dst = ( uint8_t * )data;
        dma_param.length = length;
        dma_param.src_tr_width = Transfer_Width_32_bits;
        dma_param.dst_tr_width = Transfer_Width_32_bits;
        dma_param.src_msize = Burst_Transaction_Length_8;
        dma_param.dst_msize = Burst_Transaction_Length_8;
        dma_param.tt_fc = Peripheral_to_Memory_DMAC_Flow_Controller;
        dma_param.src_per = dmac_qspi_rx_handshake_enum( 0 );
        dma_param.dst_per = dmac_qspi_tx_handshake_enum( 0 ),
        dma_param.int_en = Interrupt_Disabled;
        uint8_t ch_idx;
        periph_err_t error = app_dmac_start_wrapper( &dma_param, &ch_idx );
        BX_ASSERT( error == PERIPH_NO_ERROR );
        reg->SER = cs_sel_mask;
        error = app_dmac_transfer_wait_wrapper( ch_idx );
        BX_ASSERT( error == PERIPH_NO_ERROR );
    } else {
        reg->SER = cs_sel_mask;
        while( FIELD_RD( reg, SR, SSI_TFE ) != Transmit_FIFO_Empty );
        while( FIELD_RD( reg, SR, SSI_BUSY ) == SSI_Busy );
        uint8_t i;
        for( i = 0; i < length; i++ ) {
            data[i] = reg->DR_REVERSED;
        }
    }
    reg->SSIENR = SSI_Disabled;
    reg->SER = 0;
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_QSPI );
    qspi_sys_stat( inst, QSPI_OP_DONE );
    periph_unlock( &inst->qspi_lock );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_config_for_cache( periph_inst_handle_t hdl, uint8_t cs_sel_mask, uint16_t cache_line_size )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    if( periph_lock( &inst->qspi_lock ) == false ) {
        return PERIPH_BUSY;
    }
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_QSPI );
    ble_reg_ssi_t * reg = inst->reg;
    reg->SPI_CTRLR0 = FIELD_BUILD( SSI_WAIT_CYCLES, inst->param.multi_read.wait_cycles ) | FIELD_BUILD( SSI_INST_L, Instruction_Length_8_bits ) |
                      FIELD_BUILD( SSI_ADDR_L, Addr_Width_24_bits ) | FIELD_BUILD( SSI_TRANS_TYPE, inst->param.multi_read.trans_type );
    reg->CTRLR0 = FIELD_BUILD( SSI_SPI_FRF, inst->param.multi_read.dual_quad ) | FIELD_BUILD( SSI_DFS, DFS_32_32_bits ) | FIELD_BUILD( SSI_TMOD, Receive_Only ) |
                  FIELD_BUILD( SSI_SCPOL, Inactive_Low ) | FIELD_BUILD( SSI_SCPH, SCLK_Toggle_In_Middle ) | FIELD_BUILD( SSI_FRF, Motorola_SPI );
    reg->CTRLR1 = cache_line_size / sizeof( uint32_t ) - 1;
    reg->SER = cs_sel_mask;
    reg->SSIENR = SSI_Enabled;
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint32_t app_qspi_dr_reg_addr_for_cache( periph_inst_handle_t hdl )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    return ( uint32_t )&inst->reg->DR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint8_t app_qspi_multi_read_cmd_get( periph_inst_handle_t hdl )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
    return inst->param.multi_read.cmd;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_disable_for_cache( periph_inst_handle_t hdl )
{
    app_qspi_inst_t * inst = CONTAINER_OF( hdl, app_qspi_inst_t, inst );
//    if( periph_lock_state_get( &inst->qspi_lock ) == false ) {
//        return PERIPH_STATE_ERROR;
//    }
    ble_reg_ssi_t * reg = inst->reg;
    while( FIELD_RD( reg, SR, SSI_BUSY ) );
    reg->SSIENR = SSI_Disabled;
    reg->SER = 0;
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_QSPI );
    periph_unlock( &inst->qspi_lock );
    return PERIPH_NO_ERROR;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


