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
#ifndef __BX_ADC_H__
#define __BX_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void bx_adc_init(void);
uint32_t bx_adc_battery(void);
int32_t bx_get_adc_value( uint8_t channel );
uint32_t bx_adc_tempSensor(void);


#ifdef __cplusplus
}
#endif

#endif /* __BX_ADC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

