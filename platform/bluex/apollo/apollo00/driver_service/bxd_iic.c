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

#include "bxd_iic.h"
#include "bxd_io_mux.h"
#include "plf.h"
#include "bx_log.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct iic_speed_onfig {
    uint32_t lcnt;    // low level count
    uint32_t hcnt;    // high level count
    uint32_t rx_hold; // rx hold
    uint32_t tx_hold; // tx hold
};

/* private variables ---------------------------------------------------------*/
static struct iic_speed_onfig iic_speed_ary[BX_IIC_SPEED_MAX + 1] = {
    {0,   0,   0, 0 }, //speed mode is 1-3,array[0] is no use.
    {160, 145, 3, 10}, // STANDARD_100K_32M
    {40,  30,  3, 6 }, // FAST_400K_32M
    {16,  8,   3, 3 }, // HIGH_1M_32M
};

static bxd_iic_env_t bxd_iic_env[2];


/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/
#define CHECK_HANDLE(hdl)                                   \
do{                                                         \
    if( (hdl) != BX_IIC0 && (hdl) != BX_IIC1 ){             \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_PIN_NUM(pin_num)                              \
do{                                                         \
    if( (pin_num) < 2 || (pin_num) > 23 ){                  \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

#define CHECK_MODE(mode)                                    \
do{                                                         \
    if( (mode) >= BX_IIC_MODE_MAX ) {                       \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_SPEED(speed)                                  \
do{                                                         \
    if( (speed) >= BX_IIC_SPEED_MAX ) {                     \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_ADDR_BIT(ab)                                  \
do{                                                         \
    if( (ab) >= BX_IIC_ADDR_BIT_MAX ) {                     \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)


static void bxd_iic_clear_all_pending_irq( void * hdl )
{
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    volatile uint32_t irq_stat = BX_IICx->IS;
    volatile uint32_t temp_clear_irq_val;
    
    if(irq_stat & (1 << IIC_INTR_RX_UNDER   ))   temp_clear_irq_val = BX_IICx->CLRRUI;
    if(irq_stat & (1 << IIC_INTR_RX_OVER    ))   temp_clear_irq_val = BX_IICx->CLRROI  ;
    if(irq_stat & (1 << IIC_INTR_TX_OVER    ))   temp_clear_irq_val = BX_IICx->CLRTOI  ;
    if(irq_stat & (1 << IIC_INTR_RD_REQ     ))   temp_clear_irq_val = BX_IICx->CLRRRI   ;
    if(irq_stat & (1 << IIC_INTR_TX_ABORT   ))   temp_clear_irq_val = BX_IICx->CLRTAI  ;
    if(irq_stat & (1 << IIC_INTR_RX_DONE    ))   temp_clear_irq_val = BX_IICx->CLRRDI  ;
    if(irq_stat & (1 << IIC_INTR_ACTIVITY   ))   temp_clear_irq_val = BX_IICx->CLRAI ;
    if(irq_stat & (1 << IIC_INTR_STOP_DET   ))   temp_clear_irq_val = BX_IICx->CLRSPDI ;
    if(irq_stat & (1 << IIC_INTR_START_DET  ))   temp_clear_irq_val = BX_IICx->CLRSTDI;
    if(irq_stat & (1 << IIC_INTR_GEN_CALL   ))   temp_clear_irq_val = BX_IICx->CLRGCI ;
}


static u8 bxd_iic_get_index( void * hdl )
{
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    uint8_t idx;
    if( BX_IICx == BX_IIC0 )
    {
        idx = 0;
    }
    else
    {
        idx = 1;
    }
    
    return idx;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_open( void * hdl )
{
    CHECK_HANDLE( hdl );

    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    if( BX_IICx == BX_IIC0 ) {
        //选择时钟源 set clock src
        BX_MODIFY_REG( BX_PER->CS, PER_CS_IIC0, PER_CS_TYPE_16M_IIC0 );
        //打开时钟 set clock gate
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_SET_IIC0 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_SET_IIC0 );

        //复位
        BX_SET_BIT( BX_PER->SRST, PER_SRST_CLR_IIC0 );
        BX_SET_BIT( BX_PER->SRST, PER_SRST_SET_IIC0 );
//    //设置分频参数
//    BX_MODIFY_REG(BX_PER->CDP0, PER_CDP0_IIC1 ,0 << PER_CDP0_IIC1_POS );
    } else if ( BX_IICx == BX_IIC1 ) {
        //选择时钟源 set clock src
        BX_MODIFY_REG( BX_PER->CS, PER_CS_IIC1, PER_CS_TYPE_16M_IIC1 );
        //打开时钟 set clock gate
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_SET_IIC1 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_SET_IIC1 );

        //复位
        BX_SET_BIT( BX_PER->SRST, PER_SRST_CLR_IIC1 );
        BX_SET_BIT( BX_PER->SRST, PER_SRST_SET_IIC1 );

//    //设置分频参数
//    BX_MODIFY_REG(BX_PER->CDP0, PER_CDP0_IIC1 ,0 << PER_CDP0_IIC1_POS );

    } else {
        return BX_ERR_INVAL;
    }
    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IICx->TFTL, IIC_TFTL_TX_TL, 1 );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    if( BX_IICx == BX_IIC0 ) {
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_IIC0 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_IIC0 );
    } else if ( BX_IICx == BX_IIC1 ) {
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_32M_CLR_IIC1 );
        BX_SET_BIT( BX_PER->CLKG0, PER_CLKG0_PLL_CLR_IIC1 );
    } else {
        return BX_ERR_INVAL;
    }

    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_set_sda( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    //input pull up
    u32 pin_mask = 0x01 << pin_num;
    BX_AWO->GPIOIS |= pin_mask;
    BX_AWO->GPIOIE |= pin_mask;
    BX_AWO->GPIOPS |= pin_mask;
    BX_AWO->GPIOPE |= pin_mask;

    if( BX_IICx == BX_IIC0 ) {
        bxd_iomux_set_pin_type( pin_num, BX_PIN_TYPE_IIC0_SDA );
    } else if ( BX_IICx == BX_IIC1 ) {
        bxd_iomux_set_pin_type( pin_num, BX_PIN_TYPE_IIC1_SDA );
    } else {
        return BX_ERR_INVAL;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_set_scl( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    u32 pin_mask = 0x01 << pin_num;
    BX_AWO->GPIOIS |= pin_mask;
    BX_AWO->GPIOIE |= pin_mask;
    BX_AWO->GPIOPS |= pin_mask;
    BX_AWO->GPIOPE |= pin_mask;

    BX_SET_BIT( BX_CPU->FIOEN, pin_mask >> 2 );

    if( BX_IICx == BX_IIC0 ) {
        bxd_iomux_set_pin_type( pin_num, BX_PIN_TYPE_IIC0_SCL );
    } else if ( BX_IICx == BX_IIC1 ) {
        bxd_iomux_set_pin_type( pin_num, BX_PIN_TYPE_IIC1_SCL );
    } else {
        return BX_ERR_INVAL;
    }
    return BX_OK;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_set_mode( void * hdl, u8 mode )
{
    CHECK_HANDLE( hdl );
    CHECK_MODE( mode );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    switch( mode ) {
        case BX_IIC_MODE_MASTER:
            BX_SET_BIT( BX_IICx->CR, IIC_CR_MASTER_MODE );
            BX_SET_BIT( BX_IICx->CR, IIC_CR_SLAVE_DISABLE );
            break;

        case BX_IIC_MODE_SLAVE:
            BX_CLR_BIT( BX_IICx->CR, IIC_CR_MASTER_MODE );
            BX_CLR_BIT( BX_IICx->CR, IIC_CR_SLAVE_DISABLE );
            break;

        default:
            return BX_ERR_INVAL;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_set_speed( void * hdl, u8 speed )
{
    CHECK_HANDLE( hdl );
    CHECK_SPEED( speed );

    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    speed += 1;

    BX_FIELD_WR( BX_IICx->CR, IIC_CR_SPEED, speed );
    BX_FIELD_WR( BX_IICx->SSSH, IIC_SSSH, iic_speed_ary[speed].hcnt );
    BX_FIELD_WR( BX_IICx->SSSL, IIC_SSSL, iic_speed_ary[speed].lcnt );
    BX_FIELD_WR( BX_IICx->SDAHT, IIC_SDAHT_RX_HOLD, iic_speed_ary[speed].rx_hold );
    BX_FIELD_WR( BX_IICx->SDAHT, IIC_SDAHT_TX_HOLD, iic_speed_ary[speed].tx_hold );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_set_addr_bit( void * hdl, u8 addr_bit )
{
    CHECK_HANDLE( hdl );
    CHECK_SPEED( addr_bit );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    switch( addr_bit ) {
        case BX_IIC_ADDR_BIT_7B:
            BX_CLR_BIT( BX_IICx->CR, IIC_CR_10BITADDR_MASTER );
        BX_CLR_BIT( BX_IICx->CR, IIC_CR_10BITADDR_SLAVE );
            break;

        case BX_IIC_ADDR_BIT_10B:
            BX_SET_BIT( BX_IICx->CR, IIC_CR_10BITADDR_MASTER );
            BX_SET_BIT( BX_IICx->CR, IIC_CR_10BITADDR_SLAVE );
            break;
        default:
            return BX_ERR_INVAL;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_set_slave_addr( void * hdl, u16 slave_addr )
{
    CHECK_HANDLE( hdl );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    BX_FIELD_WR( BX_IICx->SA, IIC_SA_SAR, (slave_addr >> 1) );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//cmd 0->write
//cmd 1->read
void app_iic_set_data_cmd_pack( void * hdl, uint8_t restart, uint8_t stop, uint8_t cmd, uint8_t dat )
{
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    BX_IICx->DC = ( ( ( uint32_t )restart << 10 ) | ( ( uint32_t )stop << 9 ) | ( ( uint32_t )cmd << 8 ) | ( ( uint32_t )dat << 0 ) );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_read( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IICx->TA, IIC_TA_TAR, addr >> 1 );
    BX_SET_BIT( BX_IICx->EN, IIC_EN_ENABLE );

    uint8_t restart = 1;
    uint8_t stop = 0;
    //restart will send a byte of data
    do {
        if( len == 1 ) {
            stop = 1;
        }
        app_iic_set_data_cmd_pack( hdl, 0, 0, 0, reg++ );
        app_iic_set_data_cmd_pack( hdl, restart, stop, 1, 0 );
        restart = 0;
        //此处容易出BUG，后期修改
        while( BX_READ_BIT ( BX_IICx->STA, IIC_STA_RFNE ) == 0 );
        *buff = BX_FIELD_RD( BX_IICx->DC, IIC_DC_DAT );
        buff++;
        len--;
    } while( len > 0 );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_read_ex( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len, s32 timeout_ms )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IICx->TA, IIC_TA_TAR, addr >> 1 );
    BX_SET_BIT( BX_IICx->EN, IIC_EN_ENABLE );

    uint8_t restart = 1;
    uint8_t stop = 0;
    //restart will send a byte of data
    do {
        if( len == 1 ) {
            stop = 1;
        }
        app_iic_set_data_cmd_pack( hdl, 0, 0, 0, reg++ );
        app_iic_set_data_cmd_pack( hdl, restart, stop, 1, 0 );
        restart = 0;

        while( ( BX_READ_BIT ( BX_IICx->STA, IIC_STA_RFNE ) == 0 ) && ( timeout_ms -- > 0 ) ) {
            BX_DELAY_US( 1000 );
        }
        if( timeout_ms <= 0 ) {
            return BX_ERR_TIMEOUT;
        }
        *buff = BX_FIELD_RD( BX_IICx->DC, IIC_DC_DAT );
        buff++;
        len--;
    } while( len > 0 );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_write( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IICx->TA, IIC_TA_TAR, addr >> 1 );
    BX_SET_BIT( BX_IICx->EN, IIC_EN_ENABLE );

    uint8_t stop = 0;
    //restart will send a byte of data
    do {
        if( len == 1 ) {
            stop = 1;
        }
        app_iic_set_data_cmd_pack( hdl, 1, 0, 0, reg++ );
        app_iic_set_data_cmd_pack( hdl, 0, stop, 0, *buff );
        while( BX_READ_BIT ( BX_IICx->STA, IIC_STA_TFE ) == 0 );
        buff++;
        len--;
    } while( len > 0 );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_write_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IICx->TA, IIC_TA_TAR, addr >> 1 );
    BX_SET_BIT( BX_IICx->EN, IIC_EN_ENABLE );

    uint8_t stop = 0;
    //restart will send a byte of data
    app_iic_set_data_cmd_pack( hdl, 1, 0, 0, reg >> 8 );
    app_iic_set_data_cmd_pack( hdl, 0, 0, 0, reg & 0xFF );
    do {
        if( len == 1 ) {
            stop = 1;
        }

        app_iic_set_data_cmd_pack( hdl, 0, stop, 0, *buff );
        while( BX_READ_BIT ( BX_IICx->STA, IIC_STA_TFE ) == 0 );
        buff++;
        len--;
    } while( len > 0 );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_read_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    BX_CLR_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    BX_FIELD_WR( BX_IICx->TA, IIC_TA_TAR, addr >> 1 );
    BX_SET_BIT( BX_IICx->EN, IIC_EN_ENABLE );

    uint8_t restart = 1;
    uint8_t stop = 0;
    //restart will send a byte of data
    app_iic_set_data_cmd_pack( hdl, 0, 0, 0, reg >> 8 );
    app_iic_set_data_cmd_pack( hdl, 0, 0, 0, reg & 0xFF );
    do {
        if( len == 1 ) {
            stop = 1;
        }

        app_iic_set_data_cmd_pack( hdl, restart, stop, 1, 0 );
        restart = 0;
        while( BX_READ_BIT ( BX_IICx->STA, IIC_STA_RFNE ) == 0 );
        *buff = BX_FIELD_RD( BX_IICx->DC, IIC_DC_DAT );
        buff++;
        len--;
    } while( len > 0 );

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_iic_slave_intr_read( void * hdl, u8 * buff, u32 len, void (*callback) (void*) )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    u8 iic_index = bxd_iic_get_index( hdl );

    if(BX_IICx == BX_IIC0)
    {
        NVIC_ClearPendingIRQ( IIC0_IRQn );//clear  interrupt
        NVIC_EnableIRQ(IIC0_IRQn);//enable interrupt
    }
    else if (BX_IICx == BX_IIC1)
    {
        NVIC_ClearPendingIRQ( IIC1_IRQn );//clear  interrupt
        NVIC_EnableIRQ(IIC1_IRQn);//enable interrupt
    }
    
    BX_SET_REG( BX_IICx->IM, 0xef );//unmask all IRQ
    BX_SET_BIT( BX_IICx->EN, IIC_EN_ENABLE );
    bxd_iic_env[iic_index].rx_cplt_cb = callback;
    bxd_iic_env[iic_index].state = IIC_STATE_READ;
    bxd_iic_env[iic_index].error_detect = BX_OK;
    bxd_iic_env[iic_index].p_rx_buff = buff;
    bxd_iic_env[iic_index].rx_size = len;
    bxd_iic_env[iic_index].p_tx_buff = buff;
    bxd_iic_env[iic_index].tx_size = len;
    bxd_iic_clear_all_pending_irq(BX_IICx);
    u8 tl_value;
    if( bxd_iic_env[iic_index].tx_size >= 2 )
    {
        tl_value = (bxd_iic_env[iic_index].tx_size > IIC_RX_FIFO_LEN) ? IIC_RX_FIFO_LEN/2 : bxd_iic_env[iic_index].tx_size-1;
    }
    else
    {
        tl_value = 1;
    }
    BX_FIELD_WR(BX_IICx->RFTL, IIC_TFTL_TX_TL,tl_value);
    BX_FIELD_WR(BX_IICx->RFTL, IIC_TFTL_TX_TL,tl_value-1);

    BX_SET_BIT( BX_IICx->IM, IIC_IM_TX_EMPTY );/* Mask tx empty intr */
    BX_SET_BIT( BX_IICx->IM, IIC_IM_TX_ABRT );/* Mask TX abort isr */
    BX_SET_BIT( BX_IICx->IM, IIC_IM_STOP_DET );/* Mask stop detect intr */
    BX_SET_BIT( BX_IICx->IM, IIC_IM_RX_FULL );/* Mask RX full isr */

    return BX_OK;
}

static void bxd_iic_tx_abort_isr( void *hdl )
{
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    u8 iic_index = bxd_iic_get_index( hdl );
    //nack error
    bxd_iic_env[iic_index].error_detect = BX_ERR_TIMEOUT;
    BX_CLR_BIT( BX_IICx->IM, IIC_IM_TX_EMPTY );
}

static void bxd_iic_rx_full_isr( void * hdl )
{
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    u8 iic_index = bxd_iic_get_index( hdl );
    
    //read received data
    while( BX_READ_BIT(BX_IICx->RXFL, IIC_RXFL) )
    {
        //read current
        *bxd_iic_env[iic_index].p_rx_buff = BX_FIELD_RD( BX_IICx->DC, IIC_DC_DAT );
        bxd_iic_env[iic_index].p_rx_buff++;
        if( bxd_iic_env[iic_index].rx_size > 0)
        {
            bxd_iic_env[iic_index].rx_size--;
        }

        if( bxd_iic_env[iic_index].rx_size == 0 )
        {
            return;
        }
    }
    //tramsmit remain data, generate clocks
    uint8_t rx_fifo_depth = ( bxd_iic_env[iic_index].rx_size > IIC_RX_FIFO_LEN ) ? IIC_RX_FIFO_LEN / 2 : bxd_iic_env[iic_index].rx_size-1;
    BX_FIELD_WR(BX_IICx->RFTL, IIC_RFTL_RX_TL,rx_fifo_depth);
//    BX_SET_REG(BX_IICx->RFTL, rx_fifo_depth);
}

static void bxd_iic_tx_empty_isr( void * hdl )
{
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    u8 iic_index = bxd_iic_get_index( hdl );
    
    if( bxd_iic_env[iic_index].tx_size == 0 )
    {
        BX_CLR_BIT( BX_IICx->IM, IIC_IM_TX_EMPTY );/* Mask tx empty intr */
        return;
    }
    
    while( BX_READ_BIT(BX_IICx->STA, IIC_STA_TFNF) )/* tx FIFO not full */
    {
        uint8_t rw,stop_bit;
        rw = (bxd_iic_env[iic_index].state == IIC_STATE_READ) ? 1 : 0 ;
        stop_bit = (bxd_iic_env[iic_index].tx_size == 1) ? 1 : 0;
        //write one byte
        app_iic_set_data_cmd_pack(hdl, 0, stop_bit, rw, *bxd_iic_env[iic_index].p_tx_buff);
        //increase buffer ptr
        bxd_iic_env[iic_index].p_tx_buff++;
        bxd_iic_env[iic_index].tx_size--;
        if( bxd_iic_env[iic_index].tx_size == 0 )
        {
            BX_FIELD_WR(BX_IICx->TFTL, IIC_TFTL_TX_TL, 0);;/* Set txtl = 0 */ 
            return;
        }
    }
}

static void bxd_iic_rd_req_isr( void * hdl )
{
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    BX_SET_BIT( BX_IICx->IM, IIC_IM_TX_EMPTY );;/* Unmask tx empty intr */
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void bxd_iic_rx_done_isr( void * hdl )
{
    //no need
    //LOG(LOG_LVL_WARN , "iic_rx_done_isr\n");
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void bxd_iic_stop_det_isr( void * hdl )
{
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    u8 iic_index = bxd_iic_get_index( hdl );
    uint8_t valid_stop_det = 0;
    //to avoid glitch in scl
    //because of tx.remain later than data output , so add time delay 1 byte.
    if( ( BX_READ_BIT(BX_IICx->STA, IIC_STA_TFE) ) && ( bxd_iic_env[iic_index].tx_size <= 1 ) )
    {
        valid_stop_det = 1;
    }
    else
    {
        //stop because of nack , nack will mask tx empty.
        if( bxd_iic_env[iic_index].error_detect == BX_ERR_TIMEOUT )
        {
            valid_stop_det = 1;
        }
        else
        {
            LOG_RAW("invald iic stop bit\n");
        }
    }

    BX_CLR_BIT( BX_IICx->IM, IIC_IM_TX_EMPTY );/* Mask tx empty intr */
    BX_CLR_BIT( BX_IICx->IM, IIC_IM_TX_ABRT );/* Mask TX abort isr */
    BX_CLR_BIT( BX_IICx->IM, IIC_IM_STOP_DET );/* Mask stop detect intr */
    BX_CLR_BIT( BX_IICx->IM, IIC_IM_RX_FULL );/* Mask RX full isr */

    if( bxd_iic_env[iic_index].rx_size > 0 )
    {
        while( BX_READ_BIT(BX_IICx->RXFL, IIC_RXFL) )
        {
            //read current
            *bxd_iic_env[iic_index].p_rx_buff = BX_FIELD_RD( BX_IICx->DC, IIC_DC_DAT );
            bxd_iic_env[iic_index].p_rx_buff++;
            if( bxd_iic_env[iic_index].rx_size > 0)
            {
                bxd_iic_env[iic_index].rx_size--;
            }
            if( bxd_iic_env[iic_index].rx_size == 0 )
            {
                return;
            }
        }
    }
    
    if(valid_stop_det)
    {
        BX_CLR_REG(BX_IICx->IM);/* Mask all isr */
        
        if( bxd_iic_env[iic_index].state == IIC_STATE_WRITE )
        {
            if( bxd_iic_env[iic_index].tx_cplt_cb != NULL )
            {
                bxd_iic_env[iic_index].tx_cplt_cb( &bxd_iic_env[iic_index].error_detect );
            }
        }
        else/* I2C_STATE_READ */
        {
            if( bxd_iic_env[iic_index].rx_cplt_cb != NULL )
            {
                bxd_iic_env[iic_index].rx_cplt_cb( &bxd_iic_env[iic_index].error_detect );
            }
        }
        bxd_iic_env[iic_index].state = IIC_STATE_READY;
    }
}



static void bxd_iic_isr( void * hdl )
{
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;
    uint32_t irq_stat = BX_IICx->IS;
    
    if(irq_stat & (1<<IIC_INTR_TX_ABORT)) {bxd_iic_tx_abort_isr(hdl);  irq_stat &= ~(1<<IIC_INTR_TX_ABORT); irq_stat &= ~(1<<IIC_INTR_TX_EMPTY);}
    if(irq_stat & (1<<IIC_INTR_RX_FULL )) {bxd_iic_rx_full_isr (hdl);  irq_stat &= ~(1<<IIC_INTR_RX_FULL );}
    if(irq_stat & (1<<IIC_INTR_TX_EMPTY)) {bxd_iic_tx_empty_isr(hdl);  irq_stat &= ~(1<<IIC_INTR_TX_EMPTY);}
    if(irq_stat & (1<<IIC_INTR_RD_REQ  )) {bxd_iic_rd_req_isr  (hdl);  irq_stat &= ~(1<<IIC_INTR_RD_REQ  );}
    if(irq_stat & (1<<IIC_INTR_RX_DONE )) {bxd_iic_rx_done_isr (hdl);  irq_stat &= ~(1<<IIC_INTR_RX_DONE );}
    if(irq_stat & (1<<IIC_INTR_STOP_DET)) {bxd_iic_stop_det_isr(hdl); irq_stat &= ~(1<<IIC_INTR_STOP_DET);}
    //unexpected irq
    if(irq_stat)
    {
//        LOG_RAW("unexpected irq,stat=0x%x\n", irq_stat);
    }
    //clear all irq
    bxd_iic_clear_all_pending_irq( hdl );
}

void IIC0_IRQHandler(void)
{
    bxd_iic_isr( BX_IIC0 );
}

void IIC1_IRQHandler(void)
{
    bxd_iic_isr( BX_IIC1 );
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



