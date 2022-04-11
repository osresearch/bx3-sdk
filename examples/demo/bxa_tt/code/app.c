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

#include "bxd_uart.h"
#include "bxd_spim.h"
#include "bxd_iic.h"
#include "bxd_tim.h"
#include "bxd_gpio.h"
#include "gattc.h"
#include "bx_apollo00_it.h"
#include "bx_pm.h"
/* private define ------------------------------------------------------------*/
//TT_UART 、TT_SPI 、TT_IIC choose one
#define TT_UART 1
#define TT_SPI  0
#define TT_IIC  0

#define RX_MAX_NOTIFY_LEN        240
#define TX_MAX_DEPTH        32

#if (TT_UART ==1)
#define UART_TX_PIN     12// 串口发送pin
#define UART_RX_PIN     13//串口接收pin



#define UART_BOND       256000
#define RX_IDLE_COUNT_MAX  (8*1000*RX_MAX_NOTIFY_LEN/UART_BOND+1)//1//uint:ms
#endif

#if (TT_SPI == 1)
#define SPIM_BOND   100000
#define RX_IDLE_COUNT_MAX  (8*1000*RX_MAX_NOTIFY_LEN/SPIM_BOND+1)//1//uint:ms
#endif

#if (TT_IIC == 1)
#define IIC_BOND   100000
#define RX_IDLE_COUNT_MAX  (8*1000*RX_MAX_NOTIFY_LEN/IIC_BOND+1)//1//uint:ms

#endif

#define CONN_INTERVAL_MIN   16//  // Unit:1.25ms
#define CONN_INTERVAL_MAX   16//   // Unit:1.25ms
#define SLAVE_LATENCY       0//
#define CONN_TIMEOUT        200// //unit:10ms

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)


/* private typedef -----------------------------------------------------------*/
typedef void ( *appm_add_svc_func_t )( void );
/* private variables ---------------------------------------------------------*/
uint8_t user_scan_rsp_data[] = {
    0x0D,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, //type of this data
    'B', 'X', '-', 'S', 'e', 'r', 'i', 'a', 'l', 'A', 'p', 'p'
};

// GAP - Advertisement data (max size = (28) bytes)
uint8_t user_adv_data[] = {
    0x11,
    GAP_AD_TYPE_COMPLETE_LIST_128_BIT_UUID,
    0xc7, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0x11, 0xe1, 0x02, 0xd1, 0xff, 0xff, 0x00, 0x00,
};


static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    ( appm_add_svc_func_t )app_dis_add_dis,
    ( appm_add_svc_func_t )add_user_profile,
};


static u8 rx_buff[RXFIFO_MAX_LEN];
static u8 tx_buff[TXFIFO_MAX_LEN];

/* exported variables --------------------------------------------------------*/
struct user_service us_svc = {0} ;


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


    cmd->sugg_max_tx_octets = BLE_MAX_OCTETS;
    cmd->sugg_max_tx_time   = BLE_MAX_TIME;

    cmd->max_mtu = 2048; //1024;
    cmd->max_mps = 256;

    cmd->tx_pref_rates = GAP_RATE_LE_2MBPS | GAP_RATE_LE_1MBPS;//GAP_RATE_LE_1MBPS;//
    cmd->rx_pref_rates = GAP_RATE_LE_2MBPS | GAP_RATE_LE_1MBPS;//GAP_RATE_LE_1MBPS;//
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

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void appm_update_param( void * data )
{
    // Prepare the GAPC_PARAM_UPDATE_CMD message
    struct gapc_param_update_cmd * cmd = KE_MSG_ALLOC( GAPC_PARAM_UPDATE_CMD,
                                         KE_BUILD_ID( TASK_GAPC, app_env.conidx ), TASK_APP,
                                         gapc_param_update_cmd );

    cmd->operation  = GAPC_UPDATE_PARAMS;
    cmd->intv_min   = CONN_INTERVAL_MIN;
    cmd->intv_max   = CONN_INTERVAL_MAX;
    cmd->latency    = SLAVE_LATENCY;
    cmd->time_out   = CONN_TIMEOUT;

    // not used by a slave device
    cmd->ce_len_min = 0xFFFF;
    cmd->ce_len_max = 0xFFFF;

    // Send the message
    ke_msg_send( cmd );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_exchange_mtu( void )
{
    static u16 mtu_seq_num = 0;
    struct gattc_exc_mtu_cmd * mtu_cmd = KE_MSG_ALLOC( GATTC_EXC_MTU_CMD, TASK_GATTC, TASK_APP, gattc_exc_mtu_cmd );
    CHECK_POINTER( mtu_cmd );

    mtu_cmd->operation = GATTC_MTU_EXCH;
    mtu_cmd->seq_num = mtu_seq_num++;

    ke_msg_send( mtu_cmd );
    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t ble_send_data_notify( u8 * data, u8 length, u16 handle )
{
    struct gattc_send_evt_cmd * notify_cmd = KE_MSG_ALLOC_DYN( GATTC_SEND_EVT_CMD,
            TASK_GATTC, TASK_APP,
            gattc_send_evt_cmd, length );
    CHECK_POINTER( notify_cmd );
    static u16 notify_seq_num = 0;
    notify_cmd->operation = GATTC_NOTIFY;
    notify_cmd->seq_num = notify_seq_num++;
    notify_cmd->length = length;
    notify_cmd->handle = handle;

    memcpy( notify_cmd->value, data, length );

    ke_msg_send( notify_cmd );
    return BX_OK;
}
#if (TT_UART ==1)
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void uart_uninit( void )
{
    bxd_uart_close( BX_UART1 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void uart_init( void )
{
    bxd_uart_open( BX_UART1 );
    bxd_uart_set_tx_pin( BX_UART1, UART_TX_PIN );
    bxd_uart_set_rx_pin( BX_UART1, UART_RX_PIN );

    bxd_uart_set_data_bit( BX_UART1, BX_UART_DB_8B );
    bxd_uart_set_speed( BX_UART1, BX_UART_BD_256000 );
    bxd_uart_set_stop_bit( BX_UART1, BX_UART_SB_ONE );
    bxd_uart_set_parity( BX_UART1, BX_UART_PARITY_NONE );

    bx_fifo_init( &us_svc.rx_fifo, rx_buff, RXFIFO_MAX_LEN );
    bx_fifo_init( &us_svc.tx_fifo, tx_buff, TXFIFO_MAX_LEN );

    bxd_uart_intr_read_start( BX_UART1 );
    bxd_uart_enable_intr( BX_UART1 );
}
#endif

#if (TT_SPI == 1)
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void spim_uninit( void )
{
    bxd_spim_close( BX_SPIM0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void spim_init( void )
{
    bxd_spim_open( BX_SPIM0 );
    bxd_spim_set_speed( BX_SPIM0, 100000 );
    bxd_spim_set_data_bit( BX_SPIM0, BX_SPI_DATA_BIT_8B );
    bxd_spim_use_cs( BX_SPIM0, 0x01 );
    bxd_spim_set_cs1_pin( BX_SPIM0, 3 );

    bx_fifo_init( &us_svc.rx_fifo, rx_buff, RXFIFO_MAX_LEN );
    bx_fifo_init( &us_svc.tx_fifo, tx_buff, TXFIFO_MAX_LEN );

}
#endif

#if (TT_IIC == 1)
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void iic_uninit( void )
{
    bxd_iic_close( BX_IIC0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void iic_init( void )
{
    bxd_iic_open( BX_IIC0 );
    bxd_iic_set_scl( BX_IIC0, 2 );
    bxd_iic_set_sda( BX_IIC0, 3 );
    bxd_iic_set_speed( BX_IIC0, BX_IIC_SPEED_STANDARD );
    bxd_iic_set_addr_bit( BX_IIC0, BX_IIC_ADDR_BIT_7B );
    bxd_iic_set_mode( BX_IIC0, BX_IIC_MODE_MASTER );

    bx_fifo_init( &us_svc.rx_fifo, rx_buff, RXFIFO_MAX_LEN );
    bx_fifo_init( &us_svc.tx_fifo, tx_buff, TXFIFO_MAX_LEN );

}

#endif
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void tim0_start( void )
{
    bxd_timer_open( BX_TIM0 );
    bxd_timer_start( BX_TIM0, 1100 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void tim0_close( void )
{
    bxd_timer_close( BX_TIM0 );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void gpio_init( void )
{
    bxd_gpio_open( BX_GPIOA );

    bxd_gpio_set_pull( BX_GPIOA, 15, BX_GPIO_PULLUP );
    bxd_gpio_set_mode( BX_GPIOA, 15, BX_GPIO_MODE_EIT_FALLING );

    bxd_gpio_set_pull( BX_GPIOA, 17, BX_GPIO_PULLUP );
    bxd_gpio_set_mode( BX_GPIOA, 17, BX_GPIO_MODE_EIT_FALLING );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void gpio_uninit( void )
{
    bxd_gpio_close( BX_GPIOA );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void notify_data( u32 data_len )
{

    u8 rx_data[250];
    bx_fifo_pop( &( us_svc.rx_fifo ), rx_data, data_len );


    us_svc.notify_start = 1;
    ble_send_data_notify( &rx_data[0], data_len, 30 );

//        LOG_I( "%10u ==================================notify_data %x\t%x\n", sys_tick, rx_data[11], rx_data[12] );

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void tx_data( u32 data_len )
{
    u8 tx_data[50] = {0};

    us_svc.tx_busy = 1;


    bx_fifo_pop( &( us_svc.tx_fifo ), tx_data, data_len );
#if (TT_UART == 1)

    bxd_uart_write( BX_UART1, tx_data, data_len );
#endif

#if (TT_SPI == 1)
    bxd_spim_write( BX_SPIM0, tx_data, data_len );

#endif

#if (TT_IIC == 1)
    bxd_iic_write( BX_IIC0, 0xA0, 0x20, tx_data, data_len );

#endif
    us_svc.tx_busy = 0;
//    LOG_I( "%10u ==================================tx_data\n", sys_tick );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    bx_it_init();

    struct bx_service svc;
    svc.prop_set_func = NULL;
    svc.prop_get_func = NULL;
    svc.msg_handle_func = user_msg_handle_func;
    svc.name = "user service";
    us_svc.id = bx_register( &svc );

    bx_subscibe( us_svc.id, BXM_USER_BLE_CONNECTED, 0, 0 );
    bx_subscibe( us_svc.id, BXM_USER_BLE_DISCONNECTED, 0, 0 );
    bx_subscibe( us_svc.id, BXM_USER_BLE_NOTIFY_END, 0, 0 );
    bx_subscibe( us_svc.id, BXM_USER_TIM0_INTR, 0, 0 );
    bx_subscibe( us_svc.id, BXM_USER_GPIO_INTR, 0, 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 )
{

    s32 msg_src = bx_msg_source();
    if( msg_src == us_svc.id ) {
        switch( msg ) {
            case BXM_USER_BLE_CONNECTED:
                bx_pm_lock( BX_PM_ALL );
                LOG_RAW( "BXM_BLE_CONNECTED\r\n" );

                tim0_start();
                gpio_init();
#if (TT_UART == 1)
                uart_init();
#endif

#if (TT_SPI == 1)
                spim_init();
#endif

#if (TT_IIC == 1)
                iic_init();
#endif
                ble_exchange_mtu();

                bx_dwork( appm_update_param, NULL, 4000, 1 );

                break;

            case BXM_USER_BLE_DISCONNECTED:
                LOG_RAW( "BXM_BLE_DISCONNECTED\r\n" );
#if (TT_UART == 1)
                uart_uninit();
#endif

#if (TT_SPI == 1)
                spim_uninit();
#endif

#if (TT_IIC == 1)
                iic_uninit();
#endif
                tim0_close();
                gpio_uninit();

                bx_pm_unlock( BX_PM_ALL );
                break;

            case BXM_USER_BLE_NOTIFY_END:
                us_svc.notify_start = 0;
                break;

            case BXM_USER_TIM0_INTR: {
                bool send_now = false;

                //check if there is data for one full packet
                if( ( gattc_get_mtu( 0 ) - 3 ) > RX_MAX_NOTIFY_LEN ) {
                    us_svc.max_notify_len = RX_MAX_NOTIFY_LEN;
                } else {
                    us_svc.max_notify_len = ( gattc_get_mtu( 0 ) - 3 );
                }

                //check if idle for long time
                us_svc.notify_idle_count++;

                us_svc.rx_len = bx_fifo_get_len( &( us_svc.rx_fifo ) );
                if(  us_svc.rx_len >= us_svc.max_notify_len ) {
                    us_svc.notify_len = us_svc.max_notify_len;
                    send_now = true;
                    us_svc.notify_idle_count = 0;
                }

                if( !send_now ) {
                    //check if idle for long time

                    if( us_svc.rx_len == 0 ) {
                        us_svc.notify_idle_count = 0;
                    } else if( ( us_svc.notify_idle_count > RX_IDLE_COUNT_MAX ) ) {
                        us_svc.notify_len = us_svc.rx_len;
                        us_svc.notify_idle_count = 0;
                        send_now = true;
                    }
                }

                if( ( send_now ) && ( !us_svc.notify_start ) ) {
                    notify_data( us_svc.notify_len );
                }

                uint16_t tx_len = 0;
                bool tx_now = false;
#if (TT_UART == 1)
                if(  ( !us_svc.tx_busy ) && ( BX_READ_BIT( BX_UART1->US, UART_US_TX_FIFO_NOT_FULL ) >> UART_US_TX_FIFO_NOT_FULL_POS != 0 )   ) {
                    us_svc.tx_len = bx_fifo_get_len( &( us_svc.tx_fifo ) );
                    if( us_svc.tx_len > TX_MAX_DEPTH ) {
                        tx_len = TX_MAX_DEPTH;
                        tx_now = true;
                    } else if( us_svc.tx_len > 0 ) {
                        tx_len = us_svc.tx_len;
                        tx_now = true;
                    }

                    if( tx_now ) {
                        tx_data( tx_len );
                    }
                }
#endif

#if ((TT_SPI == 1) || (TT_IIC == 1))
                if(  ( !us_svc.tx_busy ) ) {
                    us_svc.tx_len = bx_fifo_get_len( &( us_svc.tx_fifo ) );

                    if( us_svc.tx_len > TX_MAX_DEPTH ) {
                        tx_len = TX_MAX_DEPTH;
                        tx_now = true;
                    } else if( us_svc.tx_len > 0 ) {
                        tx_len = us_svc.tx_len;
                        tx_now = true;
                    }

                    if( tx_now ) {
                        tx_data( tx_len );
                    }
                }

#endif
            }
            break;

            case BXM_USER_GPIO_INTR:
                if( param0 == 0x8000 ) {
                    LOG_RAW( "BXM_GPIO15_EXT_INTR\r\n" );
#if (TT_SPI == 1)
                    u8 rx_len = 0;
                    bxd_spim_read( BX_SPIM0, &rx_len, 1 );
                    u8 rx_buf[255] = {0};
                    rx_buf[0] = rx_len;
                    bxd_spim_read( BX_SPIM0, &rx_buf[1], rx_len );
                    bx_fifo_push( &us_svc.rx_fifo, rx_buf, ( rx_len + 1 ) );
#endif

#if (TT_IIC == 1)
                    u8 rx_len = 0;
                    bxd_iic_read( BX_IIC0, 0xA0, 0xA0, &rx_len, 1 );
                    u8 rx_buf[255] = {0};
                    rx_buf[0] = rx_len;
                    bxd_iic_read( BX_IIC0, 0xA0, 0xA0, rx_buf, rx_len ); //
                    bx_fifo_push( &us_svc.rx_fifo, rx_buf, ( rx_len + 1 ) );

#endif
//                    bx_post( us_ble_id(), BXM_BLE_ADV_START, 0, 0 );
                } else if( param0 == 0x20000 ) {
                    LOG_RAW( "BXM_GPIO17_EXT_INTR\r\n" );
                    static u8 test_data[5] = {1, 2, 3, 4, 5};
                    us_svc.notify_start = 1;
                    ble_send_data_notify( test_data, 5, 30 );
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



