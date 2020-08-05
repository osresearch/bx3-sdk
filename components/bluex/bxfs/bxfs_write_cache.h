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
#ifndef __BXFS_WRITE_CACHE_H__
#define __BXFS_WRITE_CACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/
#define BXFS_WRITE_CACHE_SIZE                   256

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void bxfs_nvm_program(uint32_t offset,uint32_t length,uint8_t *buffer);
void bxfs_nvm_read_with_cache(uint32_t offset, uint32_t length, uint8_t *buffer);
void bxfs_nvm_write_through(void);

#ifdef __cplusplus
}
#endif

#endif /* __BXFS_WRITE_CACHE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
