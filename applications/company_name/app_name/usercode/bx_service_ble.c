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

#include "bx_service_ble.h"
#include "bx_kernel.h"
#include "bx_drv_ble.h"

#include "app.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct bx_ble_service {
    s32 id;
};
/* private variables ---------------------------------------------------------*/
static struct bx_ble_service ble_svc = { 0 };


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
        case BXM_BLE_ADV_START:
            return ble_advtising_start( ( struct ble_adv_data * )param0,param1 );
            
        case BXM_BLE_ADV_STOP:
            ble_advtising_stop();
            break;
		case BXM_BLE_DIS_LINK:
			ble_connect_stop();
			break;
		case BXM_BLE_SCAN_STOP:
			ble_scan_stop();
			break;
        
        case BXM_BLE_NOTIFY:
			ble_notify((struct ble_notify_data *) param0);
			break;
        
		case BXM_BLE_NOTIFY_ENABLED:
			ble_notifaction_enabled(param0);
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
            break;
        
        case BXP_BLE_SCAN_RSP_DATA:
            break;
        
        case BXP_BLE_ADV_INTV:
            break;
        
        case BXP_BLE_CNT_INTV:
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
        case BXP_BLE_ADV_DATA:
            break;
        
        case BXP_BLE_SCAN_RSP_DATA:
            break;
        
        case BXP_BLE_ADV_INTV:
            break;
        
        case BXP_BLE_CNT_INTV:
            break;
        
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
s32 bxs_ble_id( void )
{
    return ble_svc.id;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxs_ble_register( void )
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
	
	return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

