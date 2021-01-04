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
#ifndef __APOLLO_00_MACRO_IIC_H__
#define __APOLLO_00_MACRO_IIC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"


/* exported types ------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/


#define iic_enable(iic_id)                      BX_SET_BIT( BX_IIC##iic_id->EN,IIC_EN_ENABLE )
#define iic_disable(iic_id)                     BX_CLR_BIT( BX_IIC##iic_id->EN,IIC_EN_ENABLE )
#define iic_control(iic_id,is_en)               ( is_en ? iic_enable(iic_id) : iic_disable(iic_id) )


__STATIC_INLINE bool cpu_set_fio_type( uint32_t pin,uint8_t type )
{
    switch( pin ) {
        //FIOS0
        case GPIO_PIN_2 ://FIO 0
            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO00,type << 0 );
            break;
        case GPIO_PIN_3 ://FIO 1
            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO01,type << 4 );
            break;
        case GPIO_PIN_4 ://FIO 2
            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO02,type << 8 );
            break;
        case GPIO_PIN_5 ://FIO 3
            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO03,type << 12 );
            break;
        case GPIO_PIN_6 ://FIO 4
            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO04,type << 16 );
            break;
        case GPIO_PIN_7 ://FIO 5
            break;
        case GPIO_PIN_8 ://FIO 6
            break;
        case GPIO_PIN_9 ://FIO 7
            break;
        
        //FIOS0
        case GPIO_PIN_10 ://FIO 8
            BX_MODIFY_REG(BX_CPU->FIOS1,CPU_FIOS1_IO08,type << 0 );
            break;
        case GPIO_PIN_11 ://FIO 9
            BX_MODIFY_REG(BX_CPU->FIOS1,CPU_FIOS1_IO09,type << 4 );
            break;
        case GPIO_PIN_12 ://FIO 10
            BX_MODIFY_REG(BX_CPU->FIOS1,CPU_FIOS1_IO09,type << 8 );
            break;
        default:
            return false;
    }
    return true;
}

#define iic_pin_as_iic0_scl( pin )              cpu_set_fio_type(pin,CPU_FIO_TYPE_IIC0_SCL)
#define iic_pin_as_iic0_sda( pin )              cpu_set_fio_type(pin,CPU_FIO_TYPE_IIC0_SDA)
#define iic_pin_as_iic1_scl( pin )              cpu_set_fio_type(pin,CPU_FIO_TYPE_IIC1_SCL)
#define iic_pin_as_iic1_sda( pin )              cpu_set_fio_type(pin,CPU_FIO_TYPE_IIC1_SDA)





/* exported functions --------------------------------------------------------*/

/* exported include ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_LL_CLK_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

