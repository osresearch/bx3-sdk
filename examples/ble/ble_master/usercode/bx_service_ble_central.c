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

#include "bx_service_ble_central.h"
#include "bx_kernel.h"
#include "bx_drv_ble.h"

#include "app.h"
#include "bx_shell.h"
/* private define ------------------------------------------------------------*/
#define APP_ADV_INT_MIN                                 64 //40ms (64*0.625ms)  unit:0.625ms
#define APP_ADV_INT_MAX                                 64 //40ms (64*0.625ms)  unit:0.625ms

#define DEFAULT_OP_CODE                                 GAPM_ADV_UNDIRECT
#define DEFAULT_ADV_MODE                               GAP_GEN_DISCOVERY

#define DEFAULT_SCAN_OPERATION                          GAPM_SCAN_ACTIVE
#define DEFAULT_ADV_FILT_POLICY                         ADV_ALLOW_SCAN_ANY_CON_ANY
/* private typedef -----------------------------------------------------------*/
struct bx_ble_central_service {
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
	
};
/* private variables ---------------------------------------------------------*/
static struct bx_ble_central_service ble_svc = { 0 };

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

/* exported variables --------------------------------------------------------*/



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

		case BXM_BLE_DIS_LINK:
			ble_connect_stop();
			break;
		
		case BXM_BLE_SCAN_STOP:
			ble_scan_stop();
			break;
		
		case BXM_BLE_NOTIFY_ENABLED:
			ble_notifaction_enabled(param0);
			break;	 
		
		case BXM_BLE_SCAN_START:
			ble_scan_start( ble_svc.scan_filter_duplic, ble_svc.scan_filt_policy, ble_svc.scan_mode );				
			break;
		
		case BXM_BLE_CONNECT:
			memcpy(ble_svc.connect_addr,( u8 * )param0,6);
			ble_connect_start(ble_svc.connect_addr);
			break;
		
		case BXM_BLE_GATTC_WRITE:
			ble_gatt_write(ble_svc.write_type,param0,ble_svc.write_handle,(u8 *)param1);
			break;
		
		case BXM_BLE_GATTC_READ:
			ble_gatt_read(ble_svc.read_trpe,param0,ble_svc.read_handle);
			break;
		
		case BXM_BLE_EXCHANGE_MTU:
			ble_exchange_mtu();
			break;
		
		case BXM_BLE_SET_PHY:
			ble_set_phy(param0,param1);
			break;
		
		case BXM_BLE_UPDATE_PARAM:
			{
				struct ble_gapc_conn_param * conn_param;
				conn_param->intv_min=ble_svc.con_min_intv;
				conn_param->intv_max=ble_svc.con_max_intv;
				conn_param->latency=ble_svc.latency;
				conn_param->time_out=ble_svc.con_param_timeout;
				update_conn_params( conn_param);
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

		case BXP_BLE_SCAN_policy:
			ble_svc.scan_filt_policy=param0;
			break;
		
		case BXP_BLE_SCAN_duplic:
			ble_svc.scan_filter_duplic=param0;
			break;
		
		case BXP_BLE_SCAN_MODE:
			ble_svc.scan_mode=param0;
			break;
		
		case BXP_BLE_WRITE_TYPE:
			ble_svc.write_type=param0;
			break;
		
		case BXP_BLE_WRITE_HANDLE:
			ble_svc.write_handle=param0;
			break;
		
		case BXP_BLE_READ_TYPE:
			ble_svc.read_trpe=param0;
			break;
		
		case BXP_BLE_READ_HANDLE:
			ble_svc.read_handle=param0;
			break;
		
		case BXP_BLE_CON_PARAM_MININTV:
			ble_svc.con_min_intv=param0;
			break;
		
		case BXP_BLE_CON_PARAM_MAXINTV:
			ble_svc.con_max_intv=param0;
			break;
		
		case BXP_BLE_CON_PARAM_LATENCY:
			ble_svc.latency=param0;
			break;
		
		case BXP_BLE_CON_PARAM_TIMEOUT:
			ble_svc.con_param_timeout=param0;
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
    return BX_OK;
}
/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 bxs_ble_central_id( void )
{
    return ble_svc.id;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxs_ble_central_register( void )
{
    memset( &ble_svc, 0, sizeof( struct bx_ble_central_service ) );
    struct bx_service svc;
    svc.name = "ble central service";
    svc.msg_handle_func = ble_msg_handle;
    svc.prop_set_func = ble_property_set;
    svc.prop_get_func = ble_property_get;

    ble_svc.id = bx_register( &svc );
    if( ble_svc.id == -1 ) {
        return BX_ERR_NOMEM;
    }
    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

