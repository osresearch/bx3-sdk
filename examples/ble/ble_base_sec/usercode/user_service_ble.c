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

#include "user_service_ble.h"
#include "bx_kernel.h"
#include "bx_drv_ble.h"

#include "user_ble.h"
#include "bx_shell.h"

#include "app_sec.h"
/* private define ------------------------------------------------------------*/
#define APP_ADV_INT_MIN                                 160 //40ms (64*0.625ms)  unit:0.625ms
#define APP_ADV_INT_MAX                                 160 //40ms (64*0.625ms)  unit:0.625ms

#define DEFAULT_OP_CODE                                 GAPM_ADV_UNDIRECT
#define DEFAULT_ADV_MODE                                GAP_GEN_DISCOVERABLE

#define DEFAULT_SCAN_OPERATION                          GAPM_SCAN_ACTIVE
#define DEFAULT_ADV_FILT_POLICY                         ADV_ALLOW_SCAN_ANY_CON_ANY
/* private typedef -----------------------------------------------------------*/
struct bx_ble_service {
    s32 id;
    u8 scan_filt_policy;
    u8 scan_filter_duplic;
    u8 scan_mode;
    u8 connect_addr[6];
    u8 write_type;
    u8 write_handle;
    u8 read_trpe;
    u8 read_handle;
    u8 con_min_intv;
    u8 con_max_intv;
    u8 latency;
    u8 con_param_timeout;

    u8 notify_handle;
};
/* private variables ---------------------------------------------------------*/
static struct bx_ble_service ble_svc = { 0 };
static struct ble_adv_data ble_adv = {0};


// GAP - SCAN RSP data (max size = 31 bytes)
static uint8_t scanRspData[] = {
    // complete name
    0x0B,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, //type of this data
    0x42, //'B'
    0x4C, //'L'
    0x55, //'U'
    0x45, //'E'
    0x58, //'X'
    0x2d, //'-'
    0x53, //'S'
    0x44, //'D'
    0x4B, //'K'
    0x33, //'3'
};

// GAP - Advertisement data (max size = (28) bytes, though this is
static uint8_t advData[] = {

    // service UUID, to notify central devices what services are included
    // in this peripheral
    0x03,   // length of this data
    GAP_AD_TYPE_COMPLETE_LIST_16_BIT_UUID,// some of the UUID's, but not all
    0x12,
    0x18,

    0x03,
    0x19,
    0xC1,
    0x03,

    //shortened name
    0x0B,// length of this data
    GAP_AD_TYPE_SHORTENED_NAME,//type of this data
    0x42, //'B'
    0x4C, //'L'
    0x55, //'U'
    0x45, //'E'
    0x58, //'X'
    0x2d, //'-'
    0x53, //'S'
    0x44, //'D'
    0x4B, //'K'
    0x33, //'3'
};

/* exported variables --------------------------------------------------------*/

/* private micro -------------------------------------------------------------*/
#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

#define CHECK_ADV_DATA_LEN(len)                             \
do{                                                         \
    if( (len) > GAP_ADV_DATA_LEN-3 ) {                      \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

#define CHECK_SCAN_RSP_DATA_LEN(len)                        \
do{                                                         \
    if( (len) > GAP_SCAN_RSP_DATA_LEN ) {                   \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)



/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t ble_msg_handle( s32 id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {
        case BXM_BLE_ADV_START: {
            bx_err_t err = ble_advertising_start( &ble_adv );
            if( err == BX_OK ) {
                bx_public( us_ble_id(), BXM_BLE_ADVERTISING, ble_adv.adv_intv_min, ble_adv.adv_intv_max );
            } else {
                return err;
            }
        }
        break;

        case BXM_BLE_ADV_STOP:
            ble_advertising_stop();
            break;
        case BXM_BLE_DIS_LINK:

            ble_connect_stop();
            break;
        case BXM_BLE_SCAN_STOP:
            ble_scan_stop();
            break;
        case BXM_BLE_NOTIFY:
            ble_send_data_notify( ( u8 * )param0, param1, ble_svc.notify_handle );
            break;
        case BXM_BLE_NOTIFY_ENABLED:
            ble_notifaction_enabled( param0 );
            break;
        case BXM_BLE_ADV_CHANGE_DATA:
            ble_advertising_stop();

            ble_adv.adv_data_len = param1;
            memcpy( ble_adv.adv_data, ( u8 * )param0, param1 );

            bx_defer( id, BXM_BLE_ADV_START, 0, 0, 100 );
            break;
        case BXM_BLE_ADV_CHANGE_SCAN_RSP_DATA:
            ble_advertising_stop();

            ble_adv.scan_rsp_data_len = param1;
            memcpy( ble_adv.scan_rsp_data, ( u8 * )param0, param1 );

            bx_defer( id, BXM_BLE_ADV_START, 0, 0, 100 );
            break;
        case BXM_BLE_ADV_CHANGE_INTV:
            ble_advertising_stop();

            ble_adv.adv_intv_max = param0;
            ble_adv.adv_intv_min = param1;

            bx_defer( id, BXM_BLE_ADV_START, 0, 0, 100 );
            break;
        case BXM_BLE_ADV_CHANGE_OP_CODE:
            ble_advertising_stop();

            ble_adv.op_code = param0;

            bx_defer( id, BXM_BLE_ADV_START, 0, 0, 100 );
            break;
        case BXM_BLE_ADV_CHANGE_MODE:
            ble_advertising_stop();

            ble_adv.adv_mode = param0;

            bx_defer( id, BXM_BLE_ADV_START, 0, 0, 100 );
            break;

        case BXM_BLE_ADV_CHANGE_FILT_POLICY:
            ble_advertising_stop();

            ble_adv.adv_filt_policy = param0;

            bx_defer( id, BXM_BLE_ADV_START, 0, 0, 100 );
            break;

        case BXM_BLE_ADV_UPDATE: {
            struct ble_adv_data * ble_adv_update = ( struct ble_adv_data * )param0;

            ble_adv.adv_data_len = ble_adv_update->adv_data_len;
            ble_adv.scan_rsp_data_len = ble_adv_update->scan_rsp_data_len;
            memcpy( ble_adv.adv_data, ble_adv_update->adv_data, ble_adv.adv_data_len );
            memcpy( ble_adv.scan_rsp_data, ble_adv_update->scan_rsp_data, ble_adv.scan_rsp_data_len );
            ble_advertising_advdata_update( &ble_adv );
        }
        break;


        case BXM_BLE_SCAN_START:
            ble_scan_start( ble_svc.scan_filter_duplic, ble_svc.scan_filt_policy, ble_svc.scan_mode );
            break;
        case BXM_BLE_CONNECT:
            memcpy( ble_svc.connect_addr, ( u8 * )param0, 6 );
            ble_connect_start( ble_svc.connect_addr );
            break;
        case BXM_BLE_GATTC_WRITE:
            ble_gatt_write( ble_svc.write_type, param0, ble_svc.write_handle, ( u8 * )param1 );
            break;
        case BXM_BLE_GATTC_READ:
            ble_gatt_read( ble_svc.read_trpe, param0, ble_svc.read_handle );
            break;
        case BXM_BLE_EXCHANGE_MTU:
            ble_exchange_mtu();
            break;
        case BXM_BLE_SET_PHY:
            ble_set_phy( param0, param1 );
            break;
        case BXM_BLE_UPDATE_PARAM: {
            struct ble_gapc_conn_param * conn_param;
            conn_param->intv_min = ble_svc.con_min_intv;
            conn_param->intv_max = ble_svc.con_max_intv;
            conn_param->latency = ble_svc.latency;
            conn_param->time_out = ble_svc.con_param_timeout;
            update_conn_params( conn_param );
        }
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
static bx_err_t ble_property_set( s32 id, u32 property, u32 param0, u32 param1 )
{
    switch( property ) {
        case BXP_BLE_ADV_DATA:
            ble_adv.adv_data_len = param1;
            memcpy( ble_adv.adv_data, ( u8 * )param0, param1 );
            break;

        case BXP_BLE_SCAN_RSP_DATA:
            ble_adv.scan_rsp_data_len = param1;
            memcpy( ble_adv.scan_rsp_data, ( u8 * )param0, param1 );
            break;

        case BXP_BLE_ADV_INTV:
            ble_adv.adv_intv_max = param0;
            ble_adv.adv_intv_min = param1;
            break;


        case BXP_BLE_OP_CODE:
            ble_adv.op_code = param0;
            break;

        case BXP_BLE_ADV_MODE:
            ble_adv.adv_mode = param0;
            break;

        case BXP_BLE_ADV_FILT_POLICY:
            ble_adv.adv_filt_policy = param0;
            break;

        case BXP_BLE_NOTIFY_HANDLE:
            ble_svc.notify_handle = param0;
            break;

        case BXP_BLE_SCAN_POLICY:
            ble_svc.scan_filt_policy = param0;
            break;

        case BXP_BLE_SCAN_DUPLIC:
            ble_svc.scan_filter_duplic = param0;
            break;

        case BXP_BLE_SCAN_MODE:
            ble_svc.scan_mode = param0;
            break;

        case BXP_BLE_WRITE_TYPE:
            ble_svc.write_type = param0;
            break;

        case BXP_BLE_WRITE_HANDLE:
            ble_svc.write_handle = param0;
            break;

        case BXP_BLE_READ_TYPE:
            ble_svc.read_trpe = param0;
            break;

        case BXP_BLE_READ_HANDLE:
            ble_svc.read_handle = param0;
            break;

        case BXP_BLE_CON_PARAM_MININTV:
            ble_svc.con_min_intv = param0;
            break;

        case BXP_BLE_CON_PARAM_MAXINTV:
            ble_svc.con_max_intv = param0;
            break;

        case BXP_BLE_CON_PARAM_LATENCY:
            ble_svc.latency = param0;
            break;

        case BXP_BLE_CON_PARAM_TIMEOUT:
            ble_svc.con_param_timeout = param0;
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
static bx_err_t ble_property_get( s32 id, u32 property, u32 param0, u32 param1 )
{
    switch( property ) {
        default:
            return BX_ERR_NOTSUP;
    }
}
/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 us_ble_id( void )
{
    return ble_svc.id;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t us_ble_register( void )
{
    memset( &ble_svc, 0, sizeof( struct bx_ble_service ) );
    struct bx_service svc;
    svc.name = "ble service";
    svc.msg_handle_func = ble_msg_handle;
    svc.prop_set_func = ble_property_set;
    svc.prop_get_func = ble_property_get;

    ble_svc.id = bx_register( &svc );
    if( ble_svc.id == -1 ) {
        return BX_ERR_NOMEM;
    }

    ble_adv.adv_intv_max = APP_ADV_INT_MAX;
    ble_adv.adv_intv_min = APP_ADV_INT_MIN;
    ble_adv.op_code = DEFAULT_OP_CODE;
    ble_adv.adv_mode = DEFAULT_ADV_MODE;
    ble_adv.adv_filt_policy = DEFAULT_ADV_FILT_POLICY;

    ble_adv.adv_data_len = sizeof( advData );
    ble_adv.scan_rsp_data_len = sizeof( scanRspData );
    memcpy( ble_adv.adv_data, advData, ble_adv.adv_data_len );
    memcpy( ble_adv.scan_rsp_data, scanRspData, ble_adv.scan_rsp_data_len );
    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

