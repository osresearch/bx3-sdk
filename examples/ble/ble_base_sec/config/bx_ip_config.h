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
#ifndef __BX_IP_CONFIG_H__
#define __BX_IP_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported define -----------------------------------------------------------*/
#define CFG_BLE
#define CFG_EMB
#define CFG_HOST
#define CFG_AHITL
#define CFG_HCITL
#define CFG_NVDS
#define CFG_ALLROLES
#define CFG_CON                                         10
#define CFG_HW_AUDIO
#define CFG_BLE_2MBPS
#define CFG_SLEEP
#define CFG_CHNL_ASSESS                                 
#define CFG_SEC_CON


//#define CFG_DBG
#define CFG_DBG_MEM
#define CFG_DBG_FLASH
#define CFG_DBG_NVDS
#define CFG_DBG_STACK_PROF


#define CFG_EXT_DB
#define CFG_ATTC
#define CFG_ATTS

//ble profiles config
#define CFG_PRF
#define CFG_NB_PRF                                      10

#define CFG_APP_SEC
#define CFG_APP_HID

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BX_IP_CONFIG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
