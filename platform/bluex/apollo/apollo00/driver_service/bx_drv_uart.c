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
#include "bx_drv_uart.h"
#include "bx_drv_io_mux.h"

/* includes ------------------------------------------------------------------*/

/* private define ------------------------------------------------------------*/
#define CHECK_HANDLE(hdl)                                   \
do{                                                         \
    if( (hdl) != BX_UART0 && (hdl) != BX_UART1 ) {          \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_BAUDRATE(rate)                                \
do{                                                         \
    if( (rate) >= BX_UART_BD_MAX ) {                        \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_STOP_BIT(sb)                                  \
do{                                                         \
    if( (sb) >= BX_UART_SB_MAX ) {                          \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)


#define CHECK_DATA_BIT(db)                                  \
do{                                                         \
    if( (db) >= BX_UART_DB_MAX ) {                          \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)


#define CHECK_PARITY(parity)                                \
do{                                                         \
    if( (parity) >= BX_UART_PARITY_MAX ) {                  \
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
/* private typedef -----------------------------------------------------------*/
struct uart_baudrate_cfg {
    u8  num1;
    u8  num0;
    u8  len1;
    u8  len0;
    u32 div;
};
/* private variables ---------------------------------------------------------*/
static struct uart_baudrate_cfg bd_cfg_hub[] = {
    {2, 12, 2, 1, 8},
    {12, 2, 1, 2, 1},
    {0, 0, 0, 0, 1},
};
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
bx_err_t bx_drv_uart_open( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {
        BX_PER->CLKG0 |= PER_CLKG0_32M_SET_UART0;
        BX_PER->SRST |= PER_SRST_SET_UART0;
        BX_PER->SRST |= PER_SRST_CLR_UART0;
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_DIV_UART0 );
    } else if( BX_UARTx == BX_UART1 ) {
        BX_PER->CLKG0 |= PER_CLKG0_32M_SET_UART1;
        BX_PER->SRST |= PER_SRST_SET_UART1;
        BX_PER->SRST |= PER_SRST_CLR_UART1;
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART1, PER_CS_TYPE_16M_DIV_UART1 );
    } else {
        return BX_ERR_INVAL;
    }
    
    BX_UARTx->IF |= UART_IF_FIFO_EN;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {
        BX_PER->CLKG0 |= PER_CLKG0_32M_CLR_UART0;
        BX_PER->CLKG0 |= PER_CLKG0_PLL_CLR_UART0;
        
    } else if( BX_UARTx == BX_UART1 ) {
        BX_PER->CLKG0 |= PER_CLKG0_32M_CLR_UART1;
        BX_PER->CLKG0 |= PER_CLKG0_PLL_CLR_UART1;
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
bx_err_t bx_drv_uart_read( void * hdl, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;
    
    while( len ){
        while( BX_READ_BIT( BX_UARTx->LS, UART_LS_DATA_READY ) == 0 );
        *buff = BX_UARTx->RTD;
        buff++;
        len--;
    }
    
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_write( void * hdl, u8 * buff, u32 len )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( buff );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    while( len ){
        BX_UARTx->RTD = *buff;
        while( BX_READ_BIT( BX_UARTx->LS, UART_LS_TX_EMPTY ) == 0 );
        buff++;
        len--;
    }
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_set_speed( void * hdl, u8 baudrate )
{
    CHECK_HANDLE( hdl );
    CHECK_BAUDRATE( baudrate );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    struct uart_baudrate_cfg * p_cfg = &bd_cfg_hub[baudrate];
    if( BX_UARTx == BX_UART0 ) {
        BX_PER->CDP1  = ( ( ( uint32_t )p_cfg->num1 << 24 )     \
                           | ( ( uint32_t )p_cfg->num0 << 16 )  \
                           | ( ( uint32_t )p_cfg->len1 << 8 )   \
                           | ( ( uint32_t )p_cfg->len0 << 0 ) );
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_DIV_UART0 );            
    } else if( BX_UARTx == BX_UART1 ) {
        BX_PER->CDP2  = ( ( ( uint32_t )p_cfg->num1 << 24 )     \
                           | ( ( uint32_t )p_cfg->num0 << 16 )  \
                           | ( ( uint32_t )p_cfg->len1 << 8 )   \
                           | ( ( uint32_t )p_cfg->len0 << 0 ) );
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART1, PER_CS_TYPE_16M_DIV_UART1 );
    } else {
        return BX_ERR_INVAL;
    }
    BX_UARTx->LC |= 0x80;
    BX_UARTx->RTD = ( uint8_t )p_cfg->div;
    BX_UARTx->DI = ( uint8_t )( p_cfg->div >> 8 );
    BX_UARTx->LC &= ~( ( uint32_t )0x80 );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_set_stop_bit( void * hdl, u8 stop_bit )
{
    CHECK_HANDLE( hdl );
    CHECK_STOP_BIT( stop_bit );
//    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;
    
    switch(stop_bit){
        case BX_UART_SB_ONE:
            BX_CLR_BIT( BX_UART0->LC, UART_LC_STOP_BIT );
            break;
        case BX_UART_SB_ONE_POINT_FIVE://only when databit = 5B
        case BX_UART_SB_TWO:
            BX_SET_BIT( BX_UART0->LC, UART_LC_STOP_BIT );
            break;
        default:
            return BX_ERR_NOTSUP;
    }
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_set_data_bit( void * hdl, u8 data_bit )
{
    CHECK_HANDLE( hdl );
    CHECK_DATA_BIT( data_bit );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;
    
    BX_FIELD_WR(BX_UARTx->LC, UART_LC_DATA_WIDTH,data_bit);
    
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_set_parity( void * hdl, u8 parity )
{
    CHECK_HANDLE( hdl );
    CHECK_PARITY( parity );
//    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    switch( parity ) {
        case BX_UART_PARITY_NONE:
            BX_CLR_BIT( BX_UART0->LC, UART_LC_PARITY_EN );
            break;
        
        case BX_UART_PARITY_ODD:
            BX_SET_BIT( BX_UART0->LC, UART_LC_PARITY_EN );
            BX_CLR_BIT( BX_UART0->LC, UART_LC_EVEN_PARITY_EN );
            break;
        
        case BX_UART_PARITY_EVEN:
            BX_SET_BIT( BX_UART0->LC, UART_LC_PARITY_EN );
            BX_SET_BIT( BX_UART0->LC, UART_LC_EVEN_PARITY_EN );
            break;
        
//        case BX_UART_PARITY_MARK:
//            BX_SET_BIT( BX_UART0->LC, UART_LC_PARITY_EN );
//            break;
//        
//        case BX_UART_PARITY_SPACE:
//            BX_SET_BIT( BX_UART0->LC, UART_LC_PARITY_EN );
//            break;
        
        default:
            return BX_ERR_NOTSUP;
    }

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_set_tx_pin( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {
        return bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_UART0_TX );
    } else if( BX_UARTx == BX_UART1 ) {
        return bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_UART1_TX );
    } else {
        return BX_ERR_INVAL;
    }

//    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_set_rx_pin( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {
        BX_GPIOA->DIR &= ~( 0x01 << pin_num );
        BX_AWO->GPIOIS |= ( 0x01 << pin_num );
        BX_AWO->GPIOIE |= ( 0x01 << pin_num );
        return bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_UART0_RX );
    } else if( BX_UARTx == BX_UART1 ) {
        return bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_UART1_RX );
    } else {
        return BX_ERR_INVAL;
    }

//    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_set_cts_pin( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {
        return bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_UART0_CTS );
    } else if( BX_UARTx == BX_UART1 ) {
        return BX_ERR_NOTSUP;
    } else {
        return BX_ERR_INVAL;
    }

//    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_uart_set_rts_pin( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    if( BX_UARTx == BX_UART0 ) {
        return bx_drv_iomux_set_pin_type( pin_num, BX_PIN_TYPE_UART0_RTS );
    } else if( BX_UARTx == BX_UART1 ) {
        return BX_ERR_NOTSUP;
    } else {
        return BX_ERR_INVAL;
    }

//    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



