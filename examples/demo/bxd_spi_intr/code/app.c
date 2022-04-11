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

/* private define ------------------------------------------------------------*/
#define ADD_REG_WHO_AM_I                0x0F
#define ADD_REG_CTRL_4                  0x20
#define ADD_REG_OUT_X_L                 0x28
#define ADD_REG_OUT_X_H                 0x29
#define ADD_REG_OUT_Y_L                 0x2A
#define ADD_REG_OUT_Y_H                 0x2B
#define ADD_REG_OUT_Z_L                 0x2C
#define ADD_REG_OUT_Z_H                 0x2D

#define UC_WHO_AM_I_DEFAULT_VALUE       0x3F
#define UC_ADD_REG_CTRL_4_CFG_VALUE     0x77

#define SENS_2G_RANGE_MG_PER_DIGIT      ((float)0.06)
#define SET_READ_SINGLE_CMD(x)          (x | 0x80)

#define SET_WRITE_SINGLE_CMD(x)         (x & (~(0xC0)))

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
uint8_t m_tx_len = 0;
uint8_t m_rx_len = 0;
uint8_t * m_p_tx_buff = 0;
uint8_t * m_p_rx_buff = 0;

struct user_service us_svc = {0};

uint8_t lis3_data[2] = {0x8f, 0x00};

uint8_t lis3_rx_data[2] = {0x01, 0x02};

uint8_t device_id;
int intValueMgX, intValueMgY, intValueMgZ;

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



void spim_fifo_depth( void )
{
    BX_MODIFY_REG( BX_SPIM0->TXFTL, SPIM_TXFTL_VAL, ( uint32_t ) ( SPI_FIFO_DEPTH / 2 ) );
    BX_MODIFY_REG( BX_SPIM0->RXFTL, SPIM_RXFTL_VAL, ( uint32_t ) ( SPI_FIFO_DEPTH / 2 ) );
}

void spim_intr_mask( void )
{
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_MMC );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_RFF );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_RFO );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_RFU );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_TFO );
    BX_SET_BIT( BX_SPIM0->IM, SPIM_IM_TFE );
}


void spim_init( void )
{
    NVIC_DisableIRQ( SPIM0_IRQn );       //disable interrupt

    bxd_spim_open( BX_SPIM0 );
    bxd_spim_set_speed( BX_SPIM0, 100000 );
    bxd_spim_set_data_bit( BX_SPIM0, BX_SPI_DATA_BIT_8B );
    bxd_spim_use_cs( BX_SPIM0, 0x01 );
    bxd_spim_set_cs1_pin( BX_SPIM0, 2 );

    spim_fifo_depth();
    spim_intr_mask();

    /*the last step*/
    NVIC_ClearPendingIRQ( SPIM0_IRQn );  //clear  interrupt
    NVIC_EnableIRQ( SPIM0_IRQn );        //enable interrupt
}


bx_err_t spim_transmit_data( uint8_t * pbuff, uint32_t len )
{
    if( us_svc.m_lock == true ) {
        return -1;
    }

    us_svc.m_lock = true;

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

bx_err_t spim_receive_data( uint8_t * pbuff, uint32_t len )
{
    if( us_svc.m_lock == true ) {
        return -1;
    }

    us_svc.m_lock = true;

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

bx_err_t spim_transmit_receive_data( uint8_t * tx_pbuff, uint32_t tx_len, uint8_t * rx_pbuff, uint32_t rx_len )
{
    if( us_svc.m_lock == true ) {
        return -1;
    }
//    LOG_RAW( "spim_transmit_receive_data\n" );

    us_svc.m_lock = true;
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


void LIS3DSH_write_reg( int reg, int data )
{
    lis3_data[0] = SET_WRITE_SINGLE_CMD( reg );
    lis3_data[1] = data;

    spim_transmit_data( lis3_data, 2 );

}

int LIS3DSH_read_reg( int reg )
{
    lis3_data[0] = SET_READ_SINGLE_CMD( reg );
    lis3_data[1] = 0xff;

    spim_transmit_receive_data( lis3_data, 2, lis3_rx_data, 2 );

    return lis3_rx_data[1];
}



int twoComplToInt16( int twoComplValue )
{
    int int16Value = 0;
    /* conversion */
    if( twoComplValue > 32768 ) {
        int16Value = -( ( ( ~twoComplValue ) & 0xFFFF ) + 1 );
    } else {
        int16Value = twoComplValue;
    }

    return int16Value;
}



/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    struct bx_service svc;
    svc.prop_set_func = NULL;
    svc.prop_get_func = NULL;
    svc.msg_handle_func = user_msg_handle_func;
    svc.name = "user service";
    us_svc.id = bx_register( &svc );

    spim_init();

    bx_repeat( us_svc.id, BXM_USER_TRANSMIT_DATA, 0, 0, 1000 );

    bx_subscibe( us_svc.id, BXM_USER_TRANSMIT_DATA, 0, 0 );
    bx_subscibe( us_svc.id, BXM_USER_RECEIVE_DATA_END, 0, 0 );

    LIS3DSH_read_reg( ADD_REG_WHO_AM_I );
    us_svc.spi_state = SPI_STA_DEVICE_ID;
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
            case BXM_USER_TRANSMIT_DATA:
                if( ( us_svc.spi_state == SPI_STA_DEVICE_ID ) && ( lis3_rx_data[1] == UC_WHO_AM_I_DEFAULT_VALUE ) ) {
                    LOG_RAW( "device get success device id = %d\r\n", lis3_rx_data[1] );
                    us_svc.spi_state = SPI_STA_REG;
                    LIS3DSH_write_reg( ADD_REG_CTRL_4, UC_ADD_REG_CTRL_4_CFG_VALUE );
                    LIS3DSH_read_reg( ADD_REG_CTRL_4 );

                } else if( us_svc.spi_state == SPI_STA_REG ) {
                    us_svc.spi_state = SPI_STA_XYZ_R;
                    if( lis3_rx_data[1] != UC_ADD_REG_CTRL_4_CFG_VALUE ) {
                        LOG_RAW( "intRegValue is %d\r\n", lis3_rx_data[1] );
                    }
                } else if( us_svc.spi_state == SPI_STA_XYZ_R ) {
                    if( us_svc.xyz_state == XYZ_STA_NONE ) {
                        intValueMgX = 0;  
                        intValueMgY = 0;
                        intValueMgZ = 0;
                        us_svc.xyz_state = XYZ_STA_X_R_H;
                        LIS3DSH_read_reg( ADD_REG_OUT_X_H );
                        bx_cancel( us_svc.id, BXM_USER_TRANSMIT_DATA );
                    }
                } else {
                    LOG_RAW( "device get failed	read data %x\t%x\r\n", lis3_rx_data[0], lis3_rx_data[1] );
                    us_svc.spi_state = SPI_STA_NONE;
                    LIS3DSH_read_reg( ADD_REG_WHO_AM_I );
                }
                break;


            case BXM_USER_RECEIVE_DATA_END:
                if( us_svc.spi_state == SPI_STA_XYZ_R ) {
                    if( us_svc.xyz_state == XYZ_STA_X_R_H ) {
                        intValueMgX = lis3_rx_data[1] << 8;
                        us_svc.xyz_state = XYZ_STA_X_R_L;
                        LIS3DSH_read_reg( ADD_REG_OUT_X_L );

                    }
                    if( us_svc.xyz_state == XYZ_STA_X_R_L ) {
                        intValueMgX += lis3_rx_data[1];
                        us_svc.xyz_state = XYZ_STA_Y_R_H;
                        LIS3DSH_read_reg( ADD_REG_OUT_Y_H );

                    } else if( us_svc.xyz_state == XYZ_STA_Y_R_H ) {
                        intValueMgY = lis3_rx_data[1] << 8;
                        us_svc.xyz_state = XYZ_STA_Y_R_L;
                        LIS3DSH_read_reg( ADD_REG_OUT_Y_L );

                    } else if( us_svc.xyz_state == XYZ_STA_Y_R_L ) {
                        intValueMgY += lis3_rx_data[1];
                        us_svc.xyz_state = XYZ_STA_Z_R_H;
                        LIS3DSH_read_reg( ADD_REG_OUT_Z_H );

                    } else if( us_svc.xyz_state == XYZ_STA_Z_R_H ) {
                        intValueMgZ = lis3_rx_data[1] << 8;
                        us_svc.xyz_state = XYZ_STA_Z_R_L;
                        LIS3DSH_read_reg( ADD_REG_OUT_Z_L );


                    } else if( us_svc.xyz_state == XYZ_STA_Z_R_L ) {
                        intValueMgZ += lis3_rx_data[1];
                        us_svc.xyz_state = XYZ_STA_NONE;

                        intValueMgX = twoComplToInt16( intValueMgX );
                        intValueMgX = intValueMgX * SENS_2G_RANGE_MG_PER_DIGIT;

                        intValueMgY = twoComplToInt16( intValueMgY );
                        intValueMgY = intValueMgY * SENS_2G_RANGE_MG_PER_DIGIT;

                        intValueMgZ = twoComplToInt16( intValueMgZ );
                        intValueMgZ = intValueMgZ * SENS_2G_RANGE_MG_PER_DIGIT;

                        bx_defer( us_svc.id, BXM_USER_TRANSMIT_DATA, 0, 0, 2000 );
                        LOG_RAW( "X=%6d Y=%6d Z=%6d \r\n", intValueMgX, intValueMgY, intValueMgZ );;
                    }
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



