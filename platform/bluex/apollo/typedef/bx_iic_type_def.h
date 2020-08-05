/**
  ******************************************************************************
  * @file   :   bx_iic_type_def.h
  * @version:
  * @author :
  * @brief  :   Define common iic types for different MCU
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
#ifndef __BX_IIC_TYPE_DEF_H__
#define __BX_IIC_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

enum bx_iic_mode{
    BX_IIC_MODE_MASTER,
    BX_IIC_MODE_SLAVE,
    BX_IIC_MODE_MAX,
};

enum bx_iic_speed{
    //100kHz
    BX_IIC_SPEED_STANDARD,
    //400kHz
    BX_IIC_SPEED_FAST,
    //1000kHz
    BX_IIC_SPEED_HIGHEST,
    
    BX_IIC_SPEED_MAX,
};

enum bx_iic_addr_bit {
    BX_IIC_ADDR_BIT_7B,
    BX_IIC_ADDR_BIT_10B,
    BX_IIC_ADDR_BIT_MAX,
};

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __BX_IIC_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

