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
#ifndef __USER_BLE_TASK_H__
#define __USER_BLE_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

#include "rwip_config.h"             // SW configuration

#if (BLE_APP_PRESENT)
#include "app.h"

/* config --------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void ble_connect_stop( void );
void ble_update_con_param( struct gapc_conn_param * conn_param );
void ble_scan_start( struct gapm_start_scan_cmd *scan_param );

#endif //(BLE_APP_PRESENT)

#ifdef __cplusplus
}
#endif

#endif /* __USER_BLE_TASK_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
