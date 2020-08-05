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
#ifndef __SWINT_H__
#define __SWINT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_ble_reg.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define SWINT_SYS_INT_CLR()     NVIC_ClearPendingIRQ(SFT_IRQn)
#define SWINT_SYS_INT_EN()      NVIC_EnableIRQ(SFT_IRQn)

/* exported functions --------------------------------------------------------*/

void swint_req(void (*cb)());

#ifdef __cplusplus
}
#endif

#endif /* __SWINT_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
