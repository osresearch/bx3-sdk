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
#ifndef __BX_MSG_TYPE_DEF_H__
#define __BX_MSG_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/\

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/


enum bx_message {

    BXM_OPEN,
    BXM_CLOSE,
    
    BXM_READ,
    BXM_WRITE,
    BXM_TOGGLE,
    
    BXM_START,
    BXM_STOP,
    
    
    BXM_PREPARE_SLEEP,
    BXM_WAKEUP,
    
    BXM_READ_START,
    BXM_WRITE_START,
    
    BXM_DATA_RECEIVED,
	BXM_DATA_TRANSMIT,
    
    BXM_READ_DONE,
    BXM_WRITE_DONE,
    BXM_DATA_UPDATE,
    
    BXM_FIRST_USER_MSG,
};

/* exported macros -----------------------------------------------------------*/


/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BX_ERR_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
