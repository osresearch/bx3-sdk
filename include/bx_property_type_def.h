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
#ifndef __BX_PROPERTY_TYPE_DEF_H__
#define __BX_PROPERTY_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/\

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

enum bx_property {
    BXP_HANDLE,
    
    BXP_STATE,
    BXP_MODE,
    BXP_LOCK,
    
    BXP_TIMEOUT,
    BXP_SPEED,
    BXP_ADDR,
    BXP_SUB_ADDR,
    BXP_PIN,
    BXP_ADDR_BIT,
    BXP_DATA_BIT,
    
    BXP_CHANNEL,
    BXP_VALUE,
    
    BXP_RECEIVED_DATA,
	BXP_TRANSMIT_DATA,
    
    BXP_VERSION,
    BXP_FIRST_USER_PROP,
};



/* exported macros -----------------------------------------------------------*/
#define BX_FIRST_USER_PROPERTY(x)               ( BXP_FIRST_USER_PROP + (x) )

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BX_PROPERTY_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
