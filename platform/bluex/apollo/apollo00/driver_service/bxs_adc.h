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
#ifndef __BXS_ADC_H__
#define __BXS_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/



enum bx_property_adc {
    BXP_ADC_FIRST = BXP_FIRST_USER_PROP,
    
    BXP_ADC_VOLT,
    BXP_ADC_BATTERY,
    BXP_ADC_TEMPERATURE,
    
};

enum bx_msg_adc{
    BXM_ADC_FIRST = BXM_FIRST_USER_MSG,
    
    BXM_ADC_VOLT,
    BXM_ADC_BATTERY,
    BXM_ADC_TEMPERATURE,

	BXM_ADV_VOLT_DATA_UPDATE,
	BXM_ADV_TEMP_DATA_UPDATE,
	BXM_ADV_BAT_DATA_UPDATE,
    
};
/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bool     bxs_adc_register( void );
s32      bxs_adc_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __BXS_ADC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
