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
#ifndef __NVDS_IN_RAM_H__
#define __NVDS_IN_RAM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "rwip_config.h"
#include "nvds_typedef.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

uint8_t nvds_init(void);
uint8_t nvds_get(uint8_t tag, nvds_tag_len_t * lengthPtr, uint8_t *buf);
uint8_t nvds_del(uint8_t tag);
uint8_t nvds_put(uint8_t tag, nvds_tag_len_t length, uint8_t *buf);
void    nvds_write_through(void);

#ifdef __cplusplus
}
#endif

#endif /* __NVDS_IN_RAM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
