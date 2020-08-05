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
#ifndef __TASK_ID_PATCH_H__
#define __TASK_ID_PATCH_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_config.h"
#include "rwip_config.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
#if(LOCAL_NVDS==0)
enum extended_task_type
{
    #if(LOCAL_NVDS == 0)
    TASK_NVDS = (TASK_AHI - 1),
    #endif
};
#endif

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __TASK_ID_PATCH_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
