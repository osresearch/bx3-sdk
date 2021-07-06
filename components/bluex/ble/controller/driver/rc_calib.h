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
#ifndef __RC_CALIB_H__
#define __RC_CALIB_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "apollo_00_ble_reg.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void        rc_calib_start(void);
void        rc_calib_end(bool wait);
uint32_t    get_rc32k_calib_val(void);
void        rc_test_start(void);
void        rc_test_end(void);

#ifdef __cplusplus
}
#endif

#endif /* __RC_CALIB_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
