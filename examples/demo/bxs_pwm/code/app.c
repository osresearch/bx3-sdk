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
#include "bxs_pwm.h"
#include "bxs_gpio.h"
#include "plf.h"

#include "app_dis.h"
/* private define ------------------------------------------------------------*/
#define    PWM0_PIN         2
#define    PWM1_PIN         3
#define    PWM2_PIN         4
#define    PWM3_PIN         5
#define    PWM4_PIN         6
#define    BUTTON_0         15
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

s32 us_svc;

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
    us_svc = bx_register( &svc );

    bxs_pwm_register();
    bxs_gpio_register();

    static u8 duty_value = 0;
    u32 pin_value;
    s32 id_gpio = bxs_gpio_a_id();

    s32 id0 = bxs_pwm0_id();
    s32 id1 = bxs_pwm1_id();
    s32 id2 = bxs_pwm2_id();
    s32 id3 = bxs_pwm3_id();
    s32 id4 = bxs_pwm4_id();

    bx_call( id_gpio, BXM_OPEN, 0, 0 );
    bx_set( id_gpio, BXP_MODE, 15, BX_GPIO_MODE_INPUT );
    bx_set( id_gpio, BXP_GPIO_PULL, 15, BX_GPIO_PULLUP );

    bx_call( id0, BXM_OPEN, 0, 0 );
    bx_call( id1, BXM_OPEN, 0, 0 );
    bx_call( id2, BXM_OPEN, 0, 0 );
    bx_call( id3, BXM_OPEN, 0, 0 );
    bx_call( id4, BXM_OPEN, 0, 0 );

    bx_set( id0, BXP_PIN, PWM0_PIN, 0 );
    bx_set( id1, BXP_PIN, PWM1_PIN, 0 );
    bx_set( id2, BXP_PIN, PWM2_PIN, 0 );
    bx_set( id3, BXP_PIN, PWM3_PIN, 0 );
    bx_set( id4, BXP_PIN, PWM4_PIN, 0 );

    bx_call( id0, BXM_START, 1000, 0 );
    bx_call( id1, BXM_START, 50000, 20 );
    bx_call( id2, BXM_START, 160000, 50 );
    bx_call( id3, BXM_START, 10000, 40 );
    bx_call( id4, BXM_START, 1000, 100 );


    while( 1 ) {
        bx_call( id_gpio, BXM_READ, ( u32 )&pin_value, 0 );

        if( !( pin_value >> 15 ) ) {
            if( duty_value >= 100 ) {
                duty_value = 0;
            } else {
                duty_value += 10;
            }



            bx_call( id0, BXM_START, 1000, duty_value );

            BX_DELAY_US( 1000 * 1000 );
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 )
{

    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



