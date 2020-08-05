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
#ifndef __PERIPH_ERROR_H__
#define __PERIPH_ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
typedef enum 
{
    PERIPH_NO_ERROR,
    PERIPH_INVALID_PARAM,
    PERIPH_BUSY,
    PERIPH_STATE_ERROR,
    PERIPH_INVALID_OPERATION,
    PERIPH_DMAC_NO_AVAILABLE_CHANNEL,
}periph_err_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __PERIPH_ERROR_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
