/**
  ******************************************************************************
  * @file   :   main.c
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
#include "app.h"
#include "bxd_spis.h"
#include "bxd_spim.h"
#include "bx_pm.h"
#include "plf.h"
#include "bxd_gpio.h"
//0214
#include "bx_dbg.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
uint8_t s_tx_len = 0;					//spi tx 长度
uint8_t s_rx_len = 0;					//spi rx 长度
uint8_t * s_p_tx_buff = 0;		//spi tx buffer
uint8_t * s_p_rx_buff = 0;		//spi rx buffer

struct user_service us_svc = {0};

u8 w_data[5] = {0xAA, 0x22, 0x33, 0x44, 0x55};		//spi tx data
u8 w_data1[5] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
u8 r_data[5] = {0};																//spi rx buffer
static bool send_flag = false;
u32 tx_rx_count = 0;
/*============================= private function =============================*/


/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
//spi tx/rx fifo 深度
void spis_fifo_depth( void )
{
    BX_MODIFY_REG( BX_SPIS->TXFTL, SPIS_TXFTL_VAL, ( uint32_t ) ( SPI_FIFO_DEPTH / 2 ) );
    BX_MODIFY_REG( BX_SPIS->RXFTL, SPIS_RXFTL_VAL, ( uint32_t ) ( SPI_FIFO_DEPTH / 2 ) );
}


void spis_intr_mask( void )
{
    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_MMC );
    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_RFF );//Receive FIFO Full Interrupt Mask
    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_RFO );
    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_RFU );
    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_TFO );
    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_TFE );//Transmit FIFO Empty Interrupt Mask
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//slave spi 初始化
void spis_init( void )
{
    NVIC_DisableIRQ( SPIS_IRQn );       //disable interrupt

    bxd_spis_open( BX_SPIS );
    bxd_spis_set_data_bit( BX_SPIS, BX_SPI_DATA_BIT_8B );
    bxd_spis_set_cs_pin( BX_SPIS, 3 );	//3:cs0 2:cs1


    spis_fifo_depth();
    spis_intr_mask();

    /*the last step*/
    NVIC_ClearPendingIRQ( SPIS_IRQn );  //clear  interrupt
    NVIC_EnableIRQ( SPIS_IRQn );        //enable interrupt
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//master spi tx
bx_err_t spis_transmit_data( uint8_t * pbuff, uint32_t len )
{
    s_tx_len = len;
    s_p_tx_buff = pbuff;

    /*open clock gate*/
    BX_PER->CLKG0 |= PER_CLKG0_32M_SET_SPIS;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_SPIS;

    BX_MODIFY_REG( BX_SPIS->CTRL, SPIS_CTRL_TM, SPIS_CTRL_TM_T_TX );

    /*start transfer*/
    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_TFE  );

    /*set ssie enable*/
    BX_SET_BIT( BX_SPIS->SSIE, SPIS_SSIE_BIT );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//master spi rx
bx_err_t spis_receive_data( uint8_t * pbuff, uint32_t len )
{

    s_rx_len = len;
    s_p_rx_buff = pbuff;


    /*open clock gate*/
    BX_PER->CLKG0 |= PER_CLKG0_32M_SET_SPIS;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_SPIS;

    BX_MODIFY_REG( BX_SPIS->CTRL, SPIM_CTRL_TM, SPIS_CTRL_TM_T_RX );

    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_TFE  );
    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_RFF  );

    /*set ssie enable*/
    BX_SET_BIT( BX_SPIS->SSIE, SPIS_SSIE_BIT );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//master spi tx&rx
bx_err_t spis_transmit_receive_data( uint8_t * tx_pbuff, uint32_t tx_len, uint8_t * rx_pbuff, uint32_t rx_len )
{

    s_tx_len = tx_len;
    s_p_tx_buff = tx_pbuff;
    s_rx_len = rx_len;
    s_p_rx_buff = rx_pbuff;

    /*open clock gate*/
    BX_PER->CLKG0 |= PER_CLKG0_32M_SET_SPIS;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_SPIS;
	
    BX_MODIFY_REG( BX_SPIS->CTRL, SPIS_CTRL_TM, SPIS_CTRL_TM_T_TXRX );

    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_TFE  );//Transmit FIFO Empty Interrupt Mask
    BX_SET_BIT( BX_SPIS->IM, SPIS_IM_RFF  );//Receive FIFO Full Interrupt Mask

    /*set ssie enable*/
    BX_SET_BIT( BX_SPIS->SSIE, SPIS_SSIE_BIT );//SSI Enable

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
	  //注册user服务
    struct bx_service svc;
    svc.prop_set_func = NULL;
    svc.prop_get_func = NULL;
    svc.msg_handle_func = user_msg_handle_func;
    svc.name = "user service";
    us_svc.id = bx_register( &svc );
		//spi slave 初始化
    spis_init();
  
    bxd_gpio_open( BX_GPIOA );
    bxd_gpio_set_mode( BX_GPIOA, 22, BX_GPIO_MODE_OUTPUT );
    bxd_gpio_write( BX_GPIOA, 22, 1 );
	  
    bx_dwork( spis_write_read_data, NULL, 500, BX_FOREVER );
	
	  //订阅消息
    bx_subscibe( us_svc.id, BXM_USER_TRANSMIT_DATA, 0, 0 );
    bx_subscibe( us_svc.id, BXM_USER_RECEIVE_DATA_END, 0, 0 );
}



void spis_write_read_data( void * arg )
{

    //tx_rx_count++;
	  //generate GPIOA 22 falling edge signal to master
    bxd_gpio_write( BX_GPIOA, 22, 1 );
    BX_DELAY_US( 10000 );//high level delay 10ms
    bxd_gpio_write( BX_GPIOA, 22, 0 );//falling edge
	
	  //slave write data[1-4]
	  w_data[1] = 0xff; 
		w_data[2] = 0xee;
		w_data[3] = 0xdd;
		w_data[4] = 0xcc;
	
    //slave spi tx/rx
    spis_transmit_receive_data( w_data, 5, r_data, 5 );

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 )
{

    int intRegValue;

    s32 msg_src = bx_msg_source();
    if( msg_src == us_svc.id ) {
        switch( msg ) {
            case BXM_USER_TRANSMIT_DATA: {

            }
            break;


            case BXM_USER_RECEIVE_DATA_END: {
                for( u8 i = 0; i < 5; i++ ) {
                    LOG_I( "slave:%10u\tr_data[%d] = 0x%2x\t\tw_data[%d] = 0x%2x", tx_rx_count, i, r_data[i], i, w_data[i] );
                }
                LOG_I( "\n\n" );
            }
            break;

            default:
                break;
        }

    }
    return BX_OK;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



