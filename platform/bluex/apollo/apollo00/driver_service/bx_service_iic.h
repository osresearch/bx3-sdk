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
#ifndef __BX_SERVICE_IIC_H__
#define __BX_SERVICE_IIC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_msg_type_def.h"
#include "bx_property_type_def.h"
#include "bx_iic_type_def.h"

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

enum bx_property_iic {
    BXP_IIC_FIRST = BXP_FIRST_USER_PROP,

    BXP_IIC_PIN_SDA,
    BXP_IIC_PIN_SCL,

};

enum bx_msg_iic{
    BXM_IIC_FIRST = BXM_FIRST_USER_MSG,
	
	BXM_IIC_TEST,
    
};
/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t bxs_iic_register( void );
s32      bxs_iic0_id( void );
s32      bxs_iic1_id( void );

#ifdef __cplusplus
}
#endif

#endif /* __BX_SERVICE_IIC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
