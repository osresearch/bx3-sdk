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
#ifndef __FLASH_CACHE_H__
#define __FLASH_CACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "periph_error.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/
void flash_cache_config(uint32_t);
void flash_cache_flush(uint32_t,uint32_t);
void flash_cache_flush_all(void);

periph_err_t flash_cache_enable(void);
periph_err_t flash_cache_disable(void);

#ifdef __cplusplus
}
#endif

#endif /* __FLASH_CACHE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
