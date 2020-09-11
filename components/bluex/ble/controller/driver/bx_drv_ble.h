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


#ifndef __BX_DRV_BLE_H__
#define __BX_DRV_BLE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "lld.h"
#include "llm.h"
#include "gap.h"
#include "gapm_task.h"
#include "bx_type_def.h"
#include "bx_ble_type_def.h"

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/


/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t ble_scan_stop( void );
bx_err_t ble_bonding_pair(void);
bx_err_t ble_advtising_stop( void );
bx_err_t ble_connect_stop(void);
bx_err_t ble_bonding_pair_request( void );
bx_err_t ble_indication_enabled(u16 handle);
bx_err_t ble_notifaction_enabled(u16 handle);
bx_err_t ble_advtising_start( struct ble_adv_data * p_new_advdata_buf );
bx_err_t ble_advtising_advdata_update( struct ble_adv_data * p_new_advdata_buf );
bx_err_t ble_whitelist_set( struct whitelist_data *white_list, u8 addr_cnt );
bx_err_t ble_send_data_notify(u8 *data,u8 length,u16 handle);

bx_err_t ble_scan_start( u8 filter_duplic, u8 filt_policy, u8 scan_mode );
bx_err_t update_conn_params( struct ble_gapc_conn_param * conn_param );
bx_err_t send_data_notify(u8 *data,u8 length,u16 handle);
bx_err_t ble_connect_start( u8 * addr );
bx_err_t ble_get_dev_rssi(void);
bx_err_t ble_gatt_write(u8 operation,u8 length,u8 handle,u8 *pdata);
bx_err_t ble_gatt_read(u8 operation,u8 length,u8 handle);
bx_err_t ble_exchange_mtu(void);
bx_err_t ble_set_phy(u8 rx_rate,u8 tx_rate);

#ifdef __cplusplus
}
#endif

#endif  /* __BX_DRV_BLE_H__ */



