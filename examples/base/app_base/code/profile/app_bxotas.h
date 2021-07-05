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
#ifndef APP_OTA_H_
#define APP_OTA_H_

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "rwip_config.h"     // SW Configuration

#if (BLE_BXOTA_SERVER)

#include <stdint.h>
/* config --------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
/// Table of message handlers
extern const struct ke_state_handler app_bxotas_table_handler;
/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/
void app_bxotas_init(void);
void app_bxotas_add_ota(void);
void app_bxotas_config(void);
#endif /* BLE_BXOTA_SERVER */

#ifdef __cplusplus
}
#endif

#endif /* __USER_APP_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
