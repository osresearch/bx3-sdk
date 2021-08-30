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

/* includes ------------------------------------------------------------------*/
#include "bxd_spis.h"
#include "bxd_io_mux.h"
#include "bx_sys_config.h"

#include "app_dmac_wrapper.h"

/* includes ------------------------------------------------------------------*/

/* config --------------------------------------------------------------------*/
#define SPIS_TX_FIFO_MAX_LEN 16
#define SPIS_RX_FIFO_MAX_LEN 16

/* private define ------------------------------------------------------------*/
#define CHECK_HANDLE(hdl)                                   \
do{                                                         \
    if( (hdl) != BX_SPIS ) {                               \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

#define CHECK_SPEED(speed)                                  \
do{                                                         \
    if( (speed) > 16000000 ) {                              \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_DATA_BIT(db)                                  \
do{                                                         \
    if( (db) >= BX_SPI_DATA_BIT_MAX ) {                     \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_CS_NUM(num)                                   \
do{                                                         \
    if( (num) > 2 || (num) <= 0 ) {                         \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

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
bx_err_t bxd_spis_open( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_spis_t * BX_SPISx = ( reg_spis_t * )hdl;
	BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_SET_SPIS );
	BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_SET_SPIS);
		   //澶嶄綅
	BX_SET_BIT( BX_PER->SRST, PER_SRST_CLR_SPIS );
	BX_SET_BIT( BX_PER->SRST, PER_SRST_SET_SPIS );


    //引脚配置
    BX_SET_BIT( BX_CPU->PSEN, CPU_PSEN_SPIS );
    BX_AWO->GPIOIS |= ( GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 );
    BX_AWO->GPIOIE |= ( GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 );
    //上拉
    BX_AWO->GPIOPS |= ( GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_5 );
    BX_AWO->GPIOPE |= ( GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_5 );


    //先关闭
    BX_CLR_BIT( BX_SPISx->SSIE, SPIS_SSIE_BIT );

    BX_MODIFY_REG( BX_SPISx->CTRL, SPIS_CTRL_SCPH, SPIS_CTRL_SCPH_T_MIDDLE );
    BX_MODIFY_REG( BX_SPISx->CTRL, SPIS_CTRL_SCPOL, SPIS_CTRL_SCPOL_T_LOW );
    BX_MODIFY_REG( BX_SPISx->CTRL, SPIS_CTRL_FF, SPIS_CTRL_FF_T_MOTOROLA_SPI );



    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_spis_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_spis_t * BX_SPISx = ( reg_spis_t * )hdl;

    BX_CLR_BIT( BX_PER->CLKG0, PER_CLKG0_32M_SET_SPIS );
    BX_CLR_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_SET_SPIS );
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_SPIS );
    BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_SPIS );


    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :需要把CS引脚一直有效才可使用此函数
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_spis_read( void * hdl, u8 * rx_data, u32 rx_len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( rx_data );
    reg_spis_t * BX_SPISx = ( reg_spis_t * )hdl;

    //清空当前存在的数据
    while( BX_READ_REG( BX_SPISx->RXFL ) > 0 ) {
        BX_READ_REG( BX_SPISx->DATA );
    }

    while( 1 ) {
        uint32_t rd_len = rx_len > SPIS_RX_FIFO_MAX_LEN ? SPIS_RX_FIFO_MAX_LEN : rx_len;
        for( uint32_t i = 0; i < rd_len; i++ ) {
            BX_SPISx->DATA = 0xAA;
        }
        while( rd_len > 0 && BX_READ_REG( BX_SPISx->TXFL ) != 0 );
        while( rd_len > 0 && BX_READ_REG( BX_SPISx->RXFL ) == 0 );
        while( rd_len > 0 && BX_READ_REG( BX_SPISx->RXFL ) > 0 ) {
            *rx_data = BX_READ_REG( BX_SPISx->DATA );
            rx_data++;
        }
        rx_len -= rd_len;
        if( rx_len == 0 ) {
            break;
        }
    }

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_spis_write( void * hdl, u8 * tx_data, u32 tx_len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( tx_data );
    reg_spis_t * BX_SPISx = ( reg_spis_t * )hdl;

    BX_MODIFY_REG( BX_SPISx->CTRL, SPIS_CTRL_TM, SPIS_CTRL_TM_T_TX );

    uint32_t wr_len;
    while( 1 ) {
        wr_len = tx_len > SPIS_TX_FIFO_MAX_LEN ? SPIS_TX_FIFO_MAX_LEN : tx_len;
        for( uint32_t i = 0; i < wr_len; i++ ) {
            BX_SPISx->DATA = *tx_data;
            tx_data++;
        }
        while( wr_len > 0 &&  BX_READ_REG( BX_SPISx->TXFL ) > SPIS_TX_FIFO_MAX_LEN/2 );

        tx_len -= wr_len;
        if( tx_len == 0 ) {
            break;
        }
    }
    while( wr_len > 0 &&  BX_READ_REG( BX_SPISx->TXFL ) != 0 );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_spis_set_cs_pin( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );
    reg_spim_t * BX_SPISx = ( reg_spim_t * )hdl;


    bxd_iomux_af_enable( SPIS_EN );


    u32 pin_mask = 0x01 << pin_num;
    BX_AWO->GPIOPS |= pin_mask;
    BX_AWO->GPIOPE |= pin_mask;

	BX_SET_BIT( BX_SPISx->SSIE, SPIS_SSIE_BIT );

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :   data_bit[in]    a value of @ref enum bx_spi_data_bit
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_spis_set_data_bit( void * hdl, u8 data_bit )
{
    CHECK_HANDLE( hdl );
    CHECK_DATA_BIT( data_bit );

    reg_spis_t * BX_SPISx = ( reg_spis_t * )hdl;

    u32 val = ( u32 )( data_bit + 3 )<<SPIS_CTRL_DFS32_POS;
 
    BX_MODIFY_REG( BX_SPISx->CTRL, SPIS_CTRL_DFS32, val );

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_spis_transmit_recieve( void * hdl, u8 * tx_data, u32 tx_len, u8 * rx_data, u32 rx_len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( tx_data );
    CHECK_POINTER( rx_data );
    reg_spis_t * BX_SPISx = ( reg_spis_t * )hdl;

    BX_MODIFY_REG( BX_SPISx->CTRL, SPIS_CTRL_TM, SPIS_CTRL_TM_T_TXRX );

    uint32_t tx_len_bk = tx_len;

    uint32_t wr_len = 0;
    while( 1 ) {
        wr_len = tx_len > SPIS_TX_FIFO_MAX_LEN ? SPIS_TX_FIFO_MAX_LEN : tx_len;
        for( uint32_t i = 0; i < wr_len; i++ ) {
            BX_SPISx->DATA = *tx_data;
            tx_data++;
        }
        while( wr_len > 0 &&  BX_READ_REG( BX_SPISx->TXFL ) != 0 );

        tx_len -= wr_len;
        if( tx_len == 0 ) {
            break;
        }
    }

    //清空由于TX而产生的数据
    tx_len = tx_len_bk;
    while( BX_READ_REG( BX_SPISx->RXFL ) > 0 ) {
        BX_READ_REG( BX_SPISx->DATA );
    }
    while( 1 ) {
        uint32_t rd_len = tx_len > SPIS_RX_FIFO_MAX_LEN ? SPIS_RX_FIFO_MAX_LEN : tx_len;
        for( uint32_t i = 0; i < rd_len; i++ ) {
            BX_SPISx->DATA = 0xAA;
        }
        while( rd_len > 0 && BX_READ_REG( BX_SPISx->TXFL ) != 0 );
        while( rd_len > 0 && BX_READ_REG( BX_SPISx->RXFL ) == 0 );
        while( rd_len > 0 && BX_READ_REG( BX_SPISx->RXFL ) > 0 ) {
            u8 a = BX_READ_REG( BX_SPISx->DATA );
        }
        tx_len -= rd_len;
        if( tx_len == 0 ) {
            break;
        }
    }

    //清空当前存在的数据
    while( BX_READ_REG( BX_SPISx->RXFL ) > 0 ) {
        BX_READ_REG( BX_SPISx->DATA );
    }
    //接收数据
    while( 1 ) {
        uint32_t rd_len = rx_len > SPIS_RX_FIFO_MAX_LEN ? SPIS_RX_FIFO_MAX_LEN : rx_len;
        for( uint32_t i = 0; i < rd_len; i++ ) {
            BX_SPISx->DATA = 0xAA;
        }
        while( rd_len > 0 && BX_READ_REG( BX_SPISx->TXFL ) != 0 );
        while( rd_len > 0 && BX_READ_REG( BX_SPISx->RXFL ) == 0 );
        while( rd_len > 0 && BX_READ_REG( BX_SPISx->RXFL ) > 0 ) {
            *rx_data = BX_READ_REG( BX_SPISx->DATA );
            rx_data++;
        }
        rx_len -= rd_len;
        if( rx_len == 0 ) {
            break;
        }
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_spis_write_dma( void * hdl, u8 * tx_data, u32 tx_len,void (*cb)(void *),void *cb_param )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( tx_data );
    CHECK_POINTER( cb );
    
    reg_spis_t * BX_SPISx = ( reg_spis_t * )hdl;
    u8 index = 0;

    BX_MODIFY_REG( BX_SPISx->CTRL, SPIS_CTRL_TM, SPIS_CTRL_TM_T_TX );
    
    BX_SPISx->DMATDL = SPIS_TX_FIFO_MAX_LEN/2;
    
    BX_SPISx->DMAC |= SPIS_DMAC_TX_EN;
    BX_SPISx->IM &= ~SPIS_IM_TFE;
    
    app_dmac_transfer_param_t dma_param;
    dma_param.src = tx_data;
    dma_param.dst = ( uint8_t * )&BX_SPISx->DATA;
    dma_param.length = tx_len;
    dma_param.src_tr_width = Transfer_Width_8_bits;
    dma_param.dst_tr_width = Transfer_Width_8_bits;
    dma_param.src_msize = Burst_Transaction_Length_4;
    dma_param.dst_msize = Burst_Transaction_Length_4;
    dma_param.tt_fc = Memory_to_Peripheral_DMAC_Flow_Controller;
    dma_param.src_per = dmac_spi_slave_rx_handshake_enum( index );
    dma_param.dst_per = dmac_spi_slave_tx_handshake_enum( index );
    dma_param.int_en = Interrupt_Enabled;
    dma_param.callback = cb;
    dma_param.callback_param = cb_param;
    
    uint8_t ch_idx;
    app_dmac_start_wrapper( &dma_param, &ch_idx );
    
    return BX_OK;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



