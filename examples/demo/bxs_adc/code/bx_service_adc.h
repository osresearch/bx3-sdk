/**
	*****************************************************************
	*	@file		:		.h
	*	@versuion:
	*	@author:
	*	@brief:
	*****************************************************************
	*	@attention
	*
	*<h2><center>&cpoy;	Copyright(c)	.	BLUEX	Microelectionics.
	*	All rights reserved.</center></h2>
	*
	*
	*****************************************************************
	*/
	
/*Define toprevent recursive inclusion--------------------------------*/
#ifndef _BX_SERVICE_ADC_H_
#define _BX_SERVICE_ADC_H_

#ifdef _cplusplus
extern "C" {
#endif
	
/* includes----------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"

/* exported paras---------------------------------------------------*/

/* exported types---------------------------------------------------*/

/* ecported variables------------------------------------------------*/

/* exported constants-------------------------------------------------*/



enum bx_property_adc {
		BXP_ADC_FIRST=BXP_FIRST_USER_PROP,
	
		BXP_ADC_VOLT,
		BXP_ADC_BATTERY,
		BXP_ADC_TEMPERATURE,
	
};

enum bx_msg_adc{
		BXM_ADCFIRST=BXM_FIRST_USER_MSG,
		
		BXM_ADC_VOLT,
		BXM_ADC_BATTERY,
		BXM_ADC_TEMPERATURE,
	
	BXM_ADV_VOLT_DATA_UPDATE,
	BXM_ADV_TEMP_DATA_UPDATE,
	BXM_ADV_BAT_DATA_UPDATE,
	
};
/* exported macros----------------------------------------------------*/

/* exported macros-----------------------------------------------------*/

bool			bxs_adc_register(void);
s32				bxs_adc_id(void);

#ifdef __cplusplus
}
#endif

#endif /* __BX_SERVICE_ADC_H__ */

/*********************** (C) COPYRIGHT BLUEX*************END OF FILE*/
