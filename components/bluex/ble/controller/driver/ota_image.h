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
#ifndef __OTA_IMAGE_H__
#define __OTA_IMAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported define -----------------------------------------------------------*/
#define OTA_AVAILABLE_FLAG          0x12345678
#define OTA_IMAGE_HEADER_LENGTH     256

/* exported types ------------------------------------------------------------*/
typedef struct
{
    uint32_t valid_flag;
    uint32_t crc32;         //without image header
    uint32_t image_length;  //without image header
} ota_image_header_struct_t;

typedef union
{
    ota_image_header_struct_t   s;
    uint8_t                     a[OTA_IMAGE_HEADER_LENGTH];
} ota_image_header_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __OTA_IMAGE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


