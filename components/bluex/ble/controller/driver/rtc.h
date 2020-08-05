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
#ifndef __RTC_H__
#define __RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "app_rtc_wrapper.h"
#include "reg_rtc.h"
#include "apollo_00_ble_reg.h"
#include "field_manipulate.h"

/* exported define -----------------------------------------------------------*/
#define RTC_REG                                         ( ( ble_reg_rtc_t * ) REG_RTC_BASE )

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define RTC_MATCHCNT_SET(val)                           RTC_REG->RTC_CMR = (val)
#define RTC_LOADCNT_SET(val)                            RTC_REG->RTC_CLR = (val)
#define RTC_EN_WITH_INT()                               RTC_REG->RTC_CCR = FIELD_BUILD(RTC_RTC_EN,1) | FIELD_BUILD(RTC_RTC_IEN,1)
#define RTC_EN_WITHOUT_INT()                            RTC_REG->RTC_CCR = FIELD_BUILD(RTC_RTC_EN,1)
#define RTC_CURRENTCNT_GET()                            RTC_REG->RTC_CCVR
#define RTC_INT_CLR()                                   RTC_REG->RTC_EOI
#define RTC_INT_STAT_GET()                              RTC_REG->RTC_STAT

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __AB_CD_EF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
