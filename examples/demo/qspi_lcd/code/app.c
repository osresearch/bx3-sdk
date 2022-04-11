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
#include "user_service_display.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
typedef void ( *appm_add_svc_func_t )( void );
/* private variables ---------------------------------------------------------*/
uint8_t user_scan_rsp_data[] = {
    0x08,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, //type of this data
    'B','X', '-', 'S', 'D', 'K', '3'
};

// GAP - Advertisement data (max size = (28) bytes)
uint8_t user_adv_data[] = {
    0x08,// length of this data
    GAP_AD_TYPE_SHORTENED_NAME,//type of this data
    'B','X', '-', 'S', 'D', 'K', '3'
};


static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    (appm_add_svc_func_t)app_dis_add_dis
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

static u32 a = 1;
void test3( void * data )
{
    u32 value = *(u32 *)data;
    bx_logln("testing3...%u",value);
    switch( value % 8 ){
        case 0:
            bx_post( us_display_id(), USM_DISPLAY_SHOWEX_COLOR, 0xF800, 0 );
            break;
        case 1:
            bx_post( us_display_id(), USM_DISPLAY_SHOWEX_COLOR, 0x07E0, 0 );
            break;
        case 2:
            bx_post( us_display_id(), USM_DISPLAY_SHOWEX_COLOR, 0x1F, 0 );
            break;
        
        case 3:
            bx_post( us_display_id(), USM_DISPLAY_SHOWEX_PICTURE, 0X840000, 0 );
            break;

        case 4:
            bx_post( us_display_id(), USM_DISPLAY_SHOWEX_PICTURE, 0X880000, 0 );
            break;
        
        case 5:
            bx_post( us_display_id(), USM_DISPLAY_SHOWEX_COLOR, 0xF800, 0 );
        bx_post( us_display_id(), USM_DISPLAY_SHOWEX_COLOR, 0x07E0, 0 );
        bx_post( us_display_id(), USM_DISPLAY_SHOWEX_COLOR, 0x1F, 0 );
        bx_post( us_display_id(), USM_DISPLAY_SHOWEX_PICTURE, 0X840000, 0 );
        bx_post( us_display_id(), USM_DISPLAY_SHOWEX_PICTURE, 0X880000, 0 );
            break;
        
        default:
            break;
                
    }   
    *(u32 *)data = value + 1;
    bx_dwork( test3,&a,1000,1);
}
u32 lcd_data[360*10];
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_init( void )
{
    s32 id;
    us_display_register();
    id = us_display_id();
    bx_set( id, USP_PIC_BUFF, ( u32 )lcd_data, sizeof( lcd_data ) );
    bx_set( id, USP_PIC_START_PONIT, 0, 0 );
    bx_set( id, USP_PIC_SIZE, 360, 360 );
    
    bx_defer( us_display_id(), BXM_OPEN, 0, 0,1000 );
    //bx_defer( us_display_id(), USM_DISPLAY_SHOWEX_COLOR, 0xF800F800, 0,2000 );
    bx_dwork( test3,&a,1000,1);
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


