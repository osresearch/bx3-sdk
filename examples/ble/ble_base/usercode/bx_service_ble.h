/**
  ******************************************************************************
  * @file   :   .h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BX_SERVICE_BLE_H__
#define __BX_SERVICE_BLE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
#include "bx_ble_type_def.h"
/* exported paras ------------------------------------------------------------*/
struct bx_ble_adv {
    uint16_t adv_intv_min;
    uint16_t adv_intv_max;
    uint8_t op_code;
    uint8_t host_mode;
    uint8_t host_adv_filt_policy;
    uint8_t host_adv_data_len;
    uint8_t host_adv_data[28];
    uint8_t host_scan_data_len;
    uint8_t host_scan_data[31];

};
/* exported types ------------------------------------------------------------*/
//extern uint8_t mac_buf[6];
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

enum bx_property_ble {
    BXP_BLE_FIRST = BXP_FIRST_USER_PROP,
    
    BXP_BLE_ADV_DATA,
    BXP_BLE_SCAN_RSP_DATA,
    
    BXP_BLE_ADV_INTV,
	BXP_BLE_ADV_FILT_POLICY,
	BXP_BLE_OP_CODE,
	BXP_BLE_ADV_MODE,
	BXP_BLE_NOTIFY_HANDLE,

	BXP_BLE_SCAN_MODE,
	BXP_BLE_SCAN_POLICY,
	BXP_BLE_SCAN_DUPLIC,
	BXP_BLE_WRITE_TYPE,
	BXP_BLE_WRITE_HANDLE,
	BXP_BLE_READ_TYPE,
	BXP_BLE_READ_HANDLE,
	BXP_BLE_CON_PARAM_MININTV,
	BXP_BLE_CON_PARAM_MAXINTV,
	BXP_BLE_CON_PARAM_LATENCY,
	BXP_BLE_CON_PARAM_TIMEOUT,
	
};

enum bx_msg_ble{
    BXM_BLE_FIRST = BXM_FIRST_USER_MSG,
    
    BXM_BLE_ADV_START,
	BXM_BLE_ADV_UPDATE,
	BXM_BLE_ADV_STOP,
	
	BXM_BLE_ADV_CHANGE_DATA,
    BXM_BLE_ADV_CHANGE_SCAN_RSP_DATA,
    BXM_BLE_ADV_CHANGE_INTV,
    BXM_BLE_ADV_CHANGE_OP_CODE,
    BXM_BLE_ADV_CHANGE_MODE,
    BXM_BLE_ADV_CHANGE_FILT_POLICY,
	
    BXM_BLE_SCAN_START,
	BXM_BLE_SCAN_STOP,
    
    BXM_BLE_DIS_LINK,
    
	BXM_BLE_NOTIFY,
	BXM_BLE_NOTIFY_ENABLED,
    
    BXM_BLE_CONNECT,
	BXM_BLE_GET_RSSI,
	BXM_BLE_GATTC_WRITE,
	BXM_BLE_GATTC_READ,
	BXM_BLE_EXCHANGE_MTU,
	BXM_BLE_SET_PHY,
	BXM_BLE_UPDATE_PARAM,
	
    
	BXM_BLE_READY,
	BXM_BLE_ADVERTISING,
    BXM_BLE_CONNECTED,
    BXM_BLE_DISCONNECTED,
    
   
};
/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t bxs_ble_register( void );
s32      bxs_ble_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __BX_SERVICE_BLE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
