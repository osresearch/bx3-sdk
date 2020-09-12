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
#ifndef __BX_SERVICE_BLE_CENTRAL_H__
#define __BX_SERVICE_BLE_CENTRAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
#include "bx_ble_type_def.h"
/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

enum bx_property_ble {
    BXP_BLE_FIRST = BXP_FIRST_USER_PROP,
    
  
	BXP_BLE_SCAN_MODE,      //扫描模式
	BXP_BLE_SCAN_policy,	//扫描过滤
	BXP_BLE_SCAN_duplic,
	BXP_BLE_WRITE_TYPE,     //写类型
	BXP_BLE_WRITE_HANDLE,   //写操作handle
	BXP_BLE_READ_TYPE,
	BXP_BLE_READ_HANDLE,
	BXP_BLE_CON_PARAM_MININTV,		//最小连接间隔
	BXP_BLE_CON_PARAM_MAXINTV,		//最大连接间隔
	BXP_BLE_CON_PARAM_LATENCY,		
	BXP_BLE_CON_PARAM_TIMEOUT,		//超时
	
};

enum bx_msg_ble{
    BXM_BLE_FIRST = BXM_FIRST_USER_MSG,
    
    	
    BXM_BLE_SCAN_START,
	BXM_BLE_SCAN_STOP,
    BXM_BLE_DIS_LINK,
	BXM_BLE_NOTIFY_ENABLED,
    BXM_BLE_CONNECT,
	BXM_BLE_GATTC_WRITE,
	BXM_BLE_GATTC_READ,
	BXM_BLE_EXCHANGE_MTU,
	BXM_BLE_SET_PHY,
	BXM_BLE_UPDATE_PARAM,
	
	//public state
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
