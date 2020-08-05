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
#ifndef __PERIPH_LOCK_H__
#define __PERIPH_LOCK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
typedef bool periph_lock_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/
bool periph_lock(periph_lock_t *periph_lock);

bool periph_unlock(periph_lock_t *periph_lock);

bool periph_lock_state_get(periph_lock_t *periph_lock);

#ifdef __cplusplus
}
#endif

#endif /* __PERIPH_LOCK_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
