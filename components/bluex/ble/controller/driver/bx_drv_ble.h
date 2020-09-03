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
#include "bx_ble_type_def.h"
/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/


bx_err_t send_data_notify(uint8_t *data,uint8_t length,uint16_t handle);
/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t ble_scan_stop( void );
bx_err_t ble_bonding_pair(void);
bx_err_t ble_advtising_stop( void );
bx_err_t ble_connect_stop(void);
bx_err_t ble_bonding_pair_request( void );
bx_err_t ble_indication_enabled(u16 handle);
bx_err_t ble_notifaction_enabled(u16 handle);
bx_err_t ble_advtising_start(struct ble_adv_data *p_new_advdata_buf,bool default_adv_flag);
bx_err_t ble_advtining_advdata_update( struct ble_adv_data *p_new_advdata_buf,bool adv_update,bool scan_rsp_update);
bx_err_t ble_advertising_whitelist_set(struct whitelist_data *white_list, u8 addr_cnt);

bx_err_t ble_notify(struct ble_notify_data * p_data );

bx_err_t ble_scan_start( uint8_t filter_duplic, uint8_t filt_policy, uint8_t scan_mode );

#ifdef __cplusplus
}
#endif

#endif  /* __BX_DRV_BLE_H__ */



