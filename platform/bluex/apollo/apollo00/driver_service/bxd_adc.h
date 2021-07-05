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
#ifndef __BXD_ADC_H__
#define __BXD_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_adc_type_def.h"
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


bx_err_t    bxd_adc_get_value(void * hdl, u8 channel, int32_t* value );
bx_err_t    bxd_adc_get_volt( void * hdl, u8 channel, u32* value_mv );
bx_err_t    bxd_adc_get_battery(void * hdl, u32* value );
bx_err_t    bxd_adc_get_chip_temperature(void * hdl, u32* value );

bx_err_t    bxd_adc_open(void * hdl );
bx_err_t    bxd_adc_close(void * hdl );

#ifdef __cplusplus
}
#endif

#endif /* __BXD_ADC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

