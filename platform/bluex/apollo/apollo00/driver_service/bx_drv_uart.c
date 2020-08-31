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

#include "bx_shell.h"
#include "plf.h"
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

	 	NVIC_ClearPendingIRQ( UART0_IRQn );
        BX_PER->CLKG0 |= PER_CLKG0_32M_SET_UART0;
        BX_PER->SRST |= PER_SRST_SET_UART0;
        BX_PER->SRST |= PER_SRST_CLR_UART0;
        BX_MODIFY_REG( BX_PER->CS, PER_CS_UART0, PER_CS_TYPE_16M_DIV_UART0 );
    } else if( BX_UARTx == BX_UART1 ) {
		NVIC_ClearPendingIRQ( UART1_IRQn );
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
bx_err_t bx_drv_uart_intr_enable( void * hdl )
{
	CHECK_HANDLE( hdl );
	reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    BX_UARTx->DI = ( ( ( uint32_t )0/*ptime*/ << 7 ) \
                       | ( ( uint32_t )0/*edssi, 0: Modem_Status_Interrupt_Disabled, 1: Modem_Status_Interrupt_Enabled*/ << 3 ) \
                       | ( ( uint32_t )1/*elsi, 0: Receiver_Line_Status_Interrupt_Disabled, 1: Receiver_Line_Status_Interrupt_Enabled*/ << 2 ) \
                       | ( ( uint32_t )0/*etbei, 0: Transmit_Holding_Register_Empty_Interrupt_Disabled, 1: Transmit_Holding_Register_Empty_Interrupt_Enabled*/ << 1 ) \
                       | ( ( uint32_t )0/*erbfi, 0: Received_Data_Available_Interrupt_Disabled, 1: Received_Data_Available_Interrupt_Enabled*/ << 0 ) );

    BX_UARTx->IF = ( ( ( uint32_t )0/*rcvr, 0: RCVR_Trigger_One_Character, 1: RCVR_Trigger_FIFO_One_Quarter_Full, 2: RCVR_Trigger_FIFO_Half_Full, 3: RCVR_Trigger_FIFO_Two_Less_Than_Full*/ << 6 ) \
                       | ( ( uint32_t )0/*tet, 0: TX_Empty_Trigger_FIFO_Empty, 1: TX_Empty_Trigger_Two_Characters_In_FIFO, 2: TX_Empty_Trigger_One_Quarter_Full, 3: Tx_Empty_Trigger_Half_Full*/ << 4 ) \
                       | ( ( uint32_t )0/*dmam*/ << 3 ) \
                       | ( ( uint32_t )0/*xfifor*/ << 2 ) \
                       | ( ( uint32_t )0/*rfifor*/ << 1 ) \
                       | ( ( uint32_t )1/*fifoe, 0: FIFO_Disabled, 1: FIFO_Enabled*/ << 0 ) );
	if(BX_UARTx == BX_UART0){
		NVIC_EnableIRQ( UART0_IRQn );
	} else if(BX_UARTx == BX_UART1){
		NVIC_EnableIRQ( UART1_IRQn );
	}else{
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
bx_err_t bx_drv_uart_intr_read_start( void * hdl)
{
    CHECK_HANDLE( hdl );
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    bx_drv_uart_intr_enable(BX_UARTx);
	BX_SET_BIT(BX_UARTx->DI,UART_DI_IE_RDA_AND_IDLE);

    return BX_OK;
}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//bx_err_t bx_drv_uart_intr_write_start( void * hdl )
//{
//    CHECK_HANDLE( hdl );
//    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;


//    bx_drv_uart_intr_enable(BX_UARTx);
//	BX_SET_BIT(BX_UARTx->DI,UART_DI_IE_TX_EMPTY);


//    return BX_OK;
//}
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
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;
    
    switch(stop_bit){
        case BX_UART_SB_ONE:
            BX_CLR_BIT( BX_UARTx->LC, UART_LC_STOP_BIT );
            break;
        case BX_UART_SB_ONE_POINT_FIVE://only when databit = 5B
        case BX_UART_SB_TWO:
            BX_SET_BIT( BX_UARTx->LC, UART_LC_STOP_BIT );
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
    reg_uart_t * BX_UARTx = ( reg_uart_t * )hdl;

    switch( parity ) {
        case BX_UART_PARITY_NONE:
            BX_CLR_BIT( BX_UARTx->LC, UART_LC_PARITY_EN );
            break;
        
        case BX_UART_PARITY_ODD:
            BX_SET_BIT( BX_UARTx->LC, UART_LC_PARITY_EN );
            BX_CLR_BIT( BX_UARTx->LC, UART_LC_EVEN_PARITY_EN );
            break;
        
        case BX_UART_PARITY_EVEN:
            BX_SET_BIT( BX_UARTx->LC, UART_LC_PARITY_EN );
            BX_SET_BIT( BX_UARTx->LC, UART_LC_EVEN_PARITY_EN );
            break;
        
//        case BX_UART_PARITY_MARK:
//            BX_SET_BIT( BX_UARTx->LC, UART_LC_PARITY_EN );
//            break;
//        
//        case BX_UART_PARITY_SPACE:
//            BX_SET_BIT( BX_UARTx->LC, UART_LC_PARITY_EN );
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
    
    BX_GPIOA->DIR &= ~( 0x01 << pin_num );
    BX_AWO->GPIOIS |= ( 0x01 << pin_num );
    BX_AWO->GPIOIE |= ( 0x01 << pin_num );
    
    if( BX_UARTx == BX_UART0 ) {
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
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//void UART0_IRQHandler( void )
//{
//	uint32_t tempw;

//	u8 irq_status = BX_READ_REG(BX_UART0->IF)&0x0F;

//	switch(irq_status)
//	{
//		case BX_UART_IRQ_TE:
//			break;

//		case BX_UART_IRQ_RDA:
//		case BX_UART_IRQ_CT:
//			while(1 == BX_READ_BIT(BX_UART0->LS,UART_LS_DATA_READY))	//0: No_Data_Ready, 1: Data_Ready
//			{
//				bx_fifo_push( BX_UART0->RTD;
//			}
//			return;

//		case BX_UART_IRQ_RLS:
//			if(BX_READ_BIT(BX_UART0->LS,UART_LS_OVERRUN_ERR)==1)	//0: No_Overrun_Error, 1: Overrun_Error
//			{
//				bxsh_logln("uart overrun\n");
//				while(BX_READ_BIT(BX_UART0->LS,UART_LS_DATA_READY) == 1)	//0: No_Data_Ready, 1: Data_Ready
//				{
//					tempw = BX_UART0->RTD;	//drop
//				}
//			}			
//			if(BX_READ_BIT(BX_UART0->LS,UART_LS_FRAME_ERR)==1)	//0: No_Framing_Error, 1: Framing_Error
//			{
//				bxsh_logln("uart framing error\n");
//			}
//			return;

//		case BX_UART_IRQ_MS:
//		default:
//			break;
//	}
//}


///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//void UART1_IRQHandler( void )
//{
//	uint32_t tempw;

//	u8 irq_status = BX_READ_REG(BX_UART1->IF)&0x0F;

//	switch(irq_status)
//	{
//		case BX_UART_ID_TE:
//			if (0 == tx_length)
//			{
//				while(0 == BX_READ_BIT(BX_UART1->LS, UART_LS_TH_EMPTY)>>UART_LS_TH_EMPTY_POS);	//0: Transmitter_Not_Empty, 1: Transmitter_Empty
//				
//				tx_buf_ptr = 0;
//				/*Disable TX interrupt*/
//				BX_SET_BIT(BX_UART1->DI, UART_DI_IE_TX_EMPTY);
//				return;
//			}
//			/*Fill TX FIFO until full*/
//			read_data = BX_READ_BIT(BX_UART1->US, UART_US_TX_FIFO_NOT_FULL)>>UART_US_TX_FIFO_NOT_FULL_POS;
//			while(1 == BX_READ_BIT(BX_UART1->US, UART_US_TX_FIFO_NOT_FULL)>>UART_US_TX_FIFO_NOT_FULL_POS)	//0: Transmit_FIFO_Full, 1: Transmit_FIFO_Not_Full
//			{
//				BX_UART1->RTD = *tx_buf_ptr;
//				--tx_length;
//				++tx_buf_ptr;
//				
//				if (0 == tx_length)
//				{
//					break;
//				}
//			}
//			break;

//		case BX_UART_ID_RDA:
//		case BX_UART_ID_CT:
//			while(1 == BX_READ_BIT(BX_UART1->LS,UART_LS_DATA_READY)>>UART_LS_DATA_READY_POS)	//0: No_Data_Ready, 1: Data_Ready
//			{
//				*rx_buf_ptr = BX_UART1->RTD;	// Read data received in the FIFO
//				
//				--rx_length;
//				++rx_buf_ptr;
//				
//				if (0 == rx_length)
//				{
//					rx_buf_ptr = 0;
//					/*Disable Rx interrupt*/
//					BX_SET_BIT(BX_UART1->DI, UART_DI_IE_TX_EMPTY);
//				}
//			}
//			return;

//		case BX_UART_ID_RLS:
//			if(BX_READ_BIT(BX_UART1->LS,UART_LS_OVERRUN_ERR)>>UART_LS_OVERRUN_ERR_POS == 1)	//0: No_Overrun_Error, 1: Overrun_Error
//			{
//				bxsh_logln("uart overrun\n");
//				while(BX_READ_BIT(BX_UART1->LS,UART_LS_DATA_READY)>>UART_LS_DATA_READY_POS == 1)	//0: No_Data_Ready, 1: Data_Ready
//				{
//					tempw = BX_UART1->RTD;	//drop
//				}
//			}			
//			if(BX_READ_BIT(BX_UART1->LS,UART_LS_FRAME_ERR)>>UART_LS_FRAME_ERR_POS == 1)	//0: No_Framing_Error, 1: Framing_Error
//			{
//				bxsh_logln("uart framing error\n");
//			}
//			return;

//		case BX_UART_ID_MS:
//		default:
//			break;
//	}
//}


/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



