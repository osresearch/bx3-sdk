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
#ifndef __RST_GEN_H__
#define __RST_GEN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "co_math.h"

/* exported define -----------------------------------------------------------*/

#define CHIP_SRST_AWO           CO_BIT(1)
#define BLE_LP_SRST_AWO         CO_BIT(3)
#define RTC_SRST_AWO            CO_BIT(5)
#define BLE_MAC_MDM_SRST_AWO    CO_BIT(7)
#define TOUCH_SRST_AWO          CO_BIT(9)

#define DMAC_SRST_CPU           CO_BIT(5)
#define CACHE_SRST_CPU          CO_BIT(7)
#define WDT_SRST_CPU            CO_BIT(9)
#define TIMER_SRST_CPU          CO_BIT(11)
#define QSPI_SRST_CPU           CO_BIT(13)
#define ECC_SRST_CPU            CO_BIT(23)

#define IIC0_SRST_PER           CO_BIT(1)
#define IIC1_SRST_PER           CO_BIT(3)
#define UART0_SRST_PER          CO_BIT(5)
#define UART1_SRST_PER          CO_BIT(7)
#define SPIM0_SRST_PER          CO_BIT(9)
#define SPIM1_SRST_PER          CO_BIT(11)
#define SPIS_SRST_PER           CO_BIT(13)
#define PWM_SRST_PER            CO_BIT(15)
#define GPIO_SRST_PER           CO_BIT(17)

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void srst_awo(uint32_t mask);
void srst_cpu(uint32_t mask);
void srst_per(uint32_t mask);

#ifdef __cplusplus
}
#endif

#endif /* __RST_GEN_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
