/**
  ******************************************************************************
  * @file   :   bx_wdt_type_def.h
  * @version:
  * @author :
  * @brief  :   Define common wdt types for different MCU
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
#ifndef __BX_WDT_TYPE_DEF_H__
#define __BX_WDT_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

enum bx_wdt_reset_mode{
    BX_WDT_MODE_SYSTEM_RESET,
    BX_WDT_MODE_INT_FIRST,
};

#ifdef __cplusplus
}
#endif

#endif /* __BX_WDT_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

