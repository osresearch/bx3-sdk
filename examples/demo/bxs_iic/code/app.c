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
#include "bxs_iic.h"
#include "app_dis.h"
#include "lis3dsh_bxs_iic.h"

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

s32 user_service_id;

uint8_t iic_data[3] = {0x77, 0x02, 0x04};
uint8_t iic_readbuf[3] = {0x01, 0x02, 0x03};
uint8_t lis3_data[2] = {0x8f, 0x00};


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
    user_service_id = bx_register( &svc );



    bxs_iic_register();

    /*-----------iic----------------*/
    bx_call( bxs_iic0_id(), BXM_OPEN, 0, 0 );
    bx_set( bxs_iic0_id(), BXP_IIC_PIN_SCL, 2, 0 );
    bx_set( bxs_iic0_id(), BXP_IIC_PIN_SDA, 3, 0 );

    bx_set( bxs_iic0_id(), BXP_ADDR, 0x3d, 0 );
    bx_set( bxs_iic0_id(), BXP_SUB_ADDR, 0x20, 0 );
    bx_set( bxs_iic0_id(), BXP_SPEED, BX_IIC_SPEED_HIGHEST, 0 );
    bx_set( bxs_iic0_id(), BXP_ADDR_BIT, BX_IIC_ADDR_BIT_7B, 0 );
    bx_set( bxs_iic0_id(), BXP_MODE, BX_IIC_MODE_MASTER, 0 );
    iic_read_lis3dsh( 0x0f, iic_readbuf, 3 );
    if( iic_readbuf[0] == UC_WHO_AM_I_DEFAULT_VALUE ) {
        bx_log( "device ID=%02x\r\n", iic_readbuf[0] );
        iic_write_lis3dsh( ADD_REG_CTRL_4, iic_data, 3 );
        iic_read_lis3dsh( ADD_REG_CTRL_4, iic_readbuf, 3 );
        if( iic_readbuf[0] == 0x77 ) {
            bx_log( "set success\r\n" );
            bx_repeat( user_service_id, BXM_IIC_TEST, 0, 0, 1000 );

        }

    } else {
        bx_log( "device get failed\r\n" );
    }

}

bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 )
{


    switch( msg ) {
        case BXM_IIC_TEST:
            iic_read_lis3dsh( 0x28, iic_test_buf, 1 );
            bx_log( "XL=%d", iic_test_buf[0] );
            iic_read_lis3dsh( 0x29, iic_test_buf, 1 );
            bx_log( " XH=%d\r\n", iic_test_buf[0] );
            iic_read_lis3dsh( 0x2a, iic_test_buf, 1 );
            bx_log( "YL=%d", iic_test_buf[0] );
            iic_read_lis3dsh( 0x2b, iic_test_buf, 1 );
            bx_log( " YH=%d\r\n", iic_test_buf[0] );
            iic_read_lis3dsh( 0x2c, iic_test_buf, 1 );
            bx_log( "ZL=%d", iic_test_buf[0] );
            iic_read_lis3dsh( 0x2d, iic_test_buf, 1 );
            bx_log( " ZH=%d\r\n", iic_test_buf[0] );
            break;
        default:
            break;
    }


    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



