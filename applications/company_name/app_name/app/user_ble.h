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
#ifndef __USER_BLE_H__
#define __USER_BLE_H__

#ifdef __cplusplus
extern "C" {
#endif




/* includes ------------------------------------------------------------------*/
#include "rwip_config.h"     // SW configuration

#if (BLE_APP_PRESENT)

#include <stdint.h>      
#include <co_bt.h>    
#include "arch.h"       
#include "gapc.h"   

/* config --------------------------------------------------------------------*/
#define APP_DEVICE_NAME_MAX_LEN      (18)

/* config --------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/// Application environment structure
struct app_env_tag
{
    /// Connection handle
    uint16_t conhdl;
    /// Connection Index
    uint8_t  conidx;

    /// Last initialized profile
    uint8_t next_svc;

    /// Bonding status
    bool bonded;

    /// Device Name length
    uint8_t dev_name_len;
    /// Device Name
    uint8_t dev_name[APP_DEVICE_NAME_MAX_LEN];

    /// Local device IRK( Identity Resolving Key)
    uint8_t loc_irk[KEY_LEN];

    /// Secure Connections on current link
    bool sec_con_enabled;

    /// Counter used to generate IRK
    uint8_t rand_cnt;
};

/* exported variables --------------------------------------------------------*/
extern struct app_env_tag app_env;
/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void    user_ble_init(void);
bool    user_ble_add_svc(void);

#ifdef __cplusplus
}
#endif

#endif //(BLE_APP_PRESENT)

#endif /* __USER_BLE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
