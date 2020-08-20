/**
  ******************************************************************************
  * @file   :   .h
  * @version:
  * @author :
  * @brief  :   Define common ble types 
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
#ifndef __BX_BLE_TYPE_DEF_H__
#define __BX_BLE_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"

/* exported types ------------------------------------------------------------*/


struct ble_adv_data {
    u8 adv_data_len;
    u8 adv_data[28];
    u8 scan_rsp_data_len;
    u8 scan_rsp_data[31];
};

struct whitelist_data{
	u8 addr_type; 			
	u8 addr[6];
};

struct ble_notify_data {
    u16 hdl;
    u16 len;
    u8 * data;
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __BX_BLE_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

