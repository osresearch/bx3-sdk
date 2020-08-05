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

#include "bx_drv_iic.h"
#include "bx_drv_io_mux.h"

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
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_iic_open( void * hdl )
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
bx_err_t bx_drv_iic_close( void * hdl )
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
bx_err_t bx_drv_iic_set_sda( void * hdl, u8 pin_num )
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
        bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_IIC0_SDA );
    } else if ( BX_IICx == BX_IIC1 ) {
        bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_IIC1_SDA );
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
bx_err_t bx_drv_iic_set_scl( void * hdl, u8 pin_num )
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
        bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_IIC0_SCL );
    } else if ( BX_IICx == BX_IIC1 ) {
        bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_IIC1_SCL );
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
bx_err_t bx_drv_iic_set_mode( void * hdl, u8 mode )
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
bx_err_t bx_drv_iic_set_speed( void * hdl, u8 speed )
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
bx_err_t bx_drv_iic_set_addr_bit( void * hdl, u8 addr_bit )
{
    CHECK_HANDLE( hdl );
    CHECK_SPEED( addr_bit );
    reg_iic_t * BX_IICx = ( reg_iic_t * )hdl;

    switch( addr_bit ) {
        case BX_IIC_ADDR_BIT_7B:
            BX_CLR_BIT( BX_IICx->CR, IIC_CR_10BITADDR_MASTER );
            break;

        case BX_IIC_ADDR_BIT_10B:
            BX_SET_BIT( BX_IICx->CR, IIC_CR_10BITADDR_MASTER );
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
bx_err_t bx_drv_iic_read( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len )
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
bx_err_t bx_drv_iic_write( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len )
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
        //此处容易出BUG，后期修改
        while( BX_READ_BIT ( BX_IICx->STA, IIC_STA_TFE ) == 0 );
        buff++;
        len--;
    } while( len > 0 );
    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



