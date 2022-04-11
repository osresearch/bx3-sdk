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
#include "ble.h"

#include "app_dis.h"

#include "bxd_spim.h"
#include "bxd_gpio.h"
/* private define ------------------------------------------------------------*/


/* private typedef -----------------------------------------------------------*/
typedef void ( *appm_add_svc_func_t )( void );
/* private variables ---------------------------------------------------------*/

uint8_t user_scan_rsp_data[] = {
    0x08,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, //type of this data
    'B', 'X', '-', 'S', 'D', 'K', '3'
};

// GAP - Advertisement data (max size = (28) bytes)
uint8_t user_adv_data[] = {
    0x08,// length of this data
    GAP_AD_TYPE_SHORTENED_NAME,//type of this data
    'B', 'X', '-', 'S', 'D', 'K', '3'
};


static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    ( appm_add_svc_func_t )app_dis_add_dis
};

/* exported variables --------------------------------------------------------*/
uint8_t m_tx_len = 0;					//spi tx 长度
uint8_t m_rx_len = 0;					//spi rx 长度
uint8_t * m_p_tx_buff = 0;		//spi tx buffer
uint8_t * m_p_rx_buff = 0;		//spi rx buffer

struct user_service us_svc = {0};

u8 w_data[5] = {0xCC, 0x22, 0x33, 0x44, 0x55};    //spi master tx data
u8 w_data1[5] = {0xFF, 0xBB, 0xCC, 0xDD, 0xEE};   //spi master tx data
u8 r_data[5] = {0};																//spi master rx data , feedback from slave
static bool send_flag = false;

u32 tx_rx_count = 0;
/*============================= private function =============================*/

/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_set_dev_cfg( struct gapm_set_dev_config_cmd * cmd )
{
    cmd->operation = GAPM_SET_DEV_CONFIG;
    cmd->role      = GAP_ROLE_PERIPHERAL;
    cmd->pairing_mode = GAPM_PAIRING_LEGACY;
    cmd->sugg_max_tx_octets = BLE_MAX_OCTETS;
    cmd->sugg_max_tx_time   = BLE_MAX_TIME;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool app_add_svc( void )
{
    bool more_svc = false;
    if ( app_env.next_svc != sizeof( appm_add_svc_func_list ) / sizeof( appm_add_svc_func_t ) ) {
        appm_add_svc_func_list[app_env.next_svc]();
        app_env.next_svc++;
        more_svc = true;
    }
    return more_svc;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_init( void )
{
    app_dis_init();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_ready( void )
{
    struct gapm_start_advertise_cmd adv_data;
    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160;//unit is 625 us
    adv_data.intv_min   = 160;//unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( user_adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( user_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, user_adv_data, sizeof( user_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );

    ble_advertising_start( &adv_data );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_on_ble_disconnect( void )
{
    struct gapm_start_advertise_cmd adv_data;
    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160;//unit is 625 us
    adv_data.intv_min   = 160;//unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( user_adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( user_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, user_adv_data, sizeof( user_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );

    ble_advertising_start( &adv_data );
}

//master spi tx/rx fifo 深度
void spim_fifo_depth( void )
{
    BX_MODIFY_REG( BX_SPIM0->TXFTL, SPIM_TXFTL_VAL, ( uint32_t ) ( SPI_FIFO_DEPTH / 2 ) );
    BX_MODIFY_REG( BX_SPIM0->RXFTL, SPIM_RXFTL_VAL, ( uint32_t ) ( SPI_FIFO_DEPTH / 2 ) );
}

//master spi 中断mask
void spim_intr_mask( void )
{
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_MMC );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_RFF );		//Receive FIFO Full Interrupt Mask
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_RFO );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_RFU );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_TFO );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_TFE );		//Transmit FIFO Empty Interrupt Mask
}

//master spi 初始化
void spim_init( void )
{
    NVIC_DisableIRQ( SPIM0_IRQn );       //disable interrupt

    bxd_spim_open( BX_SPIM0 );	//初始化spim0			
    bxd_spim_set_speed( BX_SPIM0, 100000 );//设置spi传输速度，单位：hz，此处设为100khz
    bxd_spim_set_data_bit( BX_SPIM0, BX_SPI_DATA_BIT_8B );//spi数据位，此处为8bit
    bxd_spim_use_cs( BX_SPIM0, 0x01 );//设置片选引脚( 0x01->cs0 0x02->cs1)
    bxd_spim_set_cs1_pin( BX_SPIM0, 3 );//设置设备上与片选引脚与之对应的引脚( 3->cs0 2->cs1 )

    spim_fifo_depth();
    spim_intr_mask();

    /*the last step*/
    NVIC_ClearPendingIRQ( SPIM0_IRQn );  //clear  interrupt
    NVIC_EnableIRQ( SPIM0_IRQn );        //enable interrupt
}

//master spi tx
bx_err_t spim_transmit_data( uint8_t * pbuff, uint32_t len )
{

    m_tx_len = len;
    m_p_tx_buff = pbuff;

    /*open clock gate*/
    BX_PER->CLKG0 |= PER_CLKG0_32M_SET_SPIM0;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_SPIM0;

    BX_MODIFY_REG( BX_SPIM0->CTRL, SPIM_CTRL_TM, SPIM_CTRL_TM_T_TX );

    /*start transfer*/
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_TFE  );

    /*set ssie enable*/
    BX_SET_BIT( BX_SPIM0->SSIE, SPIM_SSIE_BIT );

    return BX_OK;
}
//master spi rx
bx_err_t spim_receive_data( uint8_t * pbuff, uint32_t len )
{

    m_rx_len = len;
    m_p_rx_buff = pbuff;


    /*open clock gate*/
    BX_PER->CLKG0 |= PER_CLKG0_32M_SET_SPIM0;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_SPIM0;

    BX_MODIFY_REG( BX_SPIM0->CTRL, SPIM_CTRL_TM, SPIM_CTRL_TM_T_RX );

    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_TFE  );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_RFF  );

    /*set ssie enable*/
    BX_SET_BIT( BX_SPIM0->SSIE, SPIM_SSIE_BIT );

    return BX_OK;
}
//master spi tx&rx
bx_err_t spim_transmit_receive_data( uint8_t * tx_pbuff, uint32_t tx_len, uint8_t * rx_pbuff, uint32_t rx_len )
{

    m_tx_len = tx_len;
    m_p_tx_buff = tx_pbuff;
    m_rx_len = rx_len;
    m_p_rx_buff = rx_pbuff;

    /*open clock gate*/
    BX_PER->CLKG0 |= PER_CLKG0_32M_SET_SPIM0;
    BX_PER->CLKG0 |= PER_CLKG0_PLL_SET_SPIM0;

    BX_MODIFY_REG( BX_SPIM0->CTRL, SPIM_CTRL_TM, SPIM_CTRL_TM_T_TXRX );


    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_TFE  );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_RFF  );

    /*set ssie enable*/
    BX_SET_BIT( BX_SPIM0->SSIE, SPIM_SSIE_BIT );


    return BX_OK;
}



/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//GPIO callback function , do master spi tx/rx
void gpio_callback( void * hdl, u8 pin_num, u8 reason )
{
	  //tx_rx_count++;
	  //set spi tx data[1-4]
    w_data[1] = 0x01; 
    w_data[2] = 0x02;
    w_data[3] = 0x03;
    w_data[4] = 0x04;
    //master spi tx/rx
    spim_transmit_receive_data( w_data, 5, r_data, 5 );
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
    //master spi初始化
    spim_init();
	  //setup GPIO P22 
    bxd_gpio_open( BX_GPIOA );
    bxd_gpio_set_mode( BX_GPIOA, 22, BX_GPIO_MODE_INPUT );
    bxd_gpio_set_pull( BX_GPIOA, 22, BX_GPIO_PULLUP );
    bxd_gpio_set_mode( BX_GPIOA, 22, BX_GPIO_MODE_EIT_FALLING ); //set external falling trigger interrupt
    bxd_gpio_set_intr_callback( BX_GPIOA, gpio_callback ); //set interrupt callback function

		//订阅消息
    bx_subscibe( us_svc.id, BXM_USER_TRANSMIT_DATA, 0, 0 );
    bx_subscibe( us_svc.id, BXM_USER_RECEIVE_DATA_END, 0, 0 );

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
                    LOG_I( "master:%10u\tr_data[%d] = 0x%2x\t\tw_data[%d] = 0x%2x", tx_rx_count, i, r_data[i], i, w_data[i] );
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



