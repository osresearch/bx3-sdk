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

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

enum bx_property_ble {
    BXP_BLE_FIRST = BXP_FIRST_USER_PROP,
    
    BXP_BLE_ADV_DATA,       //广播数据
    BXP_BLE_SCAN_RSP_DATA,  //扫描回复数据
    
    BXP_BLE_ADV_INTV,       //广播间隔
    BXP_BLE_CNT_INTV,       //连接间隔
};

enum bx_msg_ble{
    BXM_BLE_FIRST = BXM_FIRST_USER_MSG,
    
    BXM_BLE_ADV_START,
	BXM_BLE_ADV_STOP,
	
    BXM_BLE_SCAN_START,
	BXM_BLE_SCAN_STOP,
    
    BXM_BLE_DIS_LINK,
    
	BXM_BLE_NOTIFY,
	BXM_BLE_NOTIFY_ENABLED,
    
    BXM_BLE_ADVERTISING,
    BXM_BLE_CONNECTED,
    BXM_BLE_DISCONNECT,
    
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
