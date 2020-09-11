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

struct ble_gapc_conn_param
{
    /// Connection interval minimum
    u16 intv_min;
    /// Connection interval maximum
    u16 intv_max;
    /// Latency
    u16 latency;
    /// Supervision timeout
    u16 time_out;
};

struct ble_adv_data{
    u16 adv_intv_min;
	u16 adv_intv_max;
	u8 op_code;
	u8 adv_mode;
	u8 adv_filt_policy;
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

