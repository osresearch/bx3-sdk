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
#ifndef __PERIPH_RECOVERY_H__
#define __PERIPH_RECOVERY_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "periph_mngt.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void recovery_list_add(periph_inst_handle_t *recovery_buf,uint8_t idx,periph_inst_handle_t hdl);

void recovery_list_remove(periph_inst_handle_t *recovery_buf,uint8_t idx);

void periph_recovery(periph_inst_handle_t *recovery_buf,uint8_t size);

#ifdef __cplusplus
}
#endif

#endif /* __PERIPH_RECOVERY_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
