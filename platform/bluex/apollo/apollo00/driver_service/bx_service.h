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
#ifndef __BX_SERVICE_H__
#define __BX_SERVICE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/

#include "bx_service_gpio.h"
#include "bx_service_tim.h"
#include "bx_service_pwm.h"
#include "bx_service_wdt.h"
#include "bx_service_iic.h"

//#include "bx_service_rtc.h"
#include "bx_service_uart.h"
#include "bx_service_adc.h"
#include "bx_service_spi.h"
//#include "bx_service_cache.h"
//#include "bx_service_dma.h"
//#include "bx_service_falsh.h"

//#include "bx_service_power_manager.h"
//#include "bx_service_sleep.h"
//#include "bx_service_clock.h"
//#include "bx_pm.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/


/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t bxs_register(void);


#ifdef __cplusplus
}
#endif

#endif /* __BX_SERVICE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
