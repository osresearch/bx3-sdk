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
#ifndef __APOLLO_00_MACRO_PMUX_H__
#define __APOLLO_00_MACRO_PMUX_H__

#ifdef __cplusplus
extern "C" {
#endif

/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"


/* exported types ------------------------------------------------------------*/
//pin share enable CPU_PSEN
#define PMUX_ENABLE_QSPI0           0
#define PMUX_ENABLE_QSPI1           1
#define PMUX_ENABLE_QSPI2           2
#define PMUX_ENABLE_QSPI3           3
#define PMUX_ENABLE_GPIO0           4
#define PMUX_ENABLE_GPIO1           5
#define PMUX_ENABLE_SPIM0_CS1       6
#define PMUX_ENABLE_SPIM0           7
#define PMUX_ENABLE_SPIM1_CS1       8
#define PMUX_ENABLE_SPIM1           9
#define PMUX_ENABLE_GPIO14          10
#define PMUX_ENABLE_SPIM15          11

//pin share enable CPU_PSEN
#define PMUX_ENABLE_SPI             12
#define PMUX_ENABLE_BLE_MAC_DBG0    13
#define PMUX_ENABLE_BLE_MAC_DBG1    14
#define PMUX_ENABLE_BLE_MAC_DBG2    15
#define PMUX_ENABLE_BLE_MAC_DBG3    16
#define PMUX_ENABLE_BLE_MAC_DBG4    17
#define PMUX_ENABLE_BLE_MAC_DBG5    18
#define PMUX_ENABLE_BLE_MAC_DBG6    19
#define PMUX_ENABLE_BLE_MAC_DBG7    20

//pin share enable CPU_FIO_EN
#define PMUX_ENABLE_FIO00  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO00  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO00  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0
#define PMUX_ENABLE_FIO01  0

//pin share enable CPU_PSEN
#define PMUX_ENABLE_RFIF          0

//pin share type 
#define PMUX_TYPE_GPIO0  0
#define PMUX_TYPE_GPIO1  0
#define PMUX_TYPE_GPIO2  0
#define PMUX_TYPE_GPIO3  0
#define PMUX_TYPE_GPIO4  0
#define PMUX_TYPE_GPIO5  0
#define PMUX_TYPE_GPIO6  0
#define PMUX_TYPE_GPIO7  0
#define PMUX_TYPE_GPIO8  0
#define PMUX_TYPE_GPIO0  0
#define PMUX_TYPE_GPIO0  0
#define PMUX_TYPE_GPIO0  0
#define PMUX_TYPE_GPIO0  0

/* exported constants --------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

__STATIC_INLINE bool pmux_enable( uint8_t en_type )
{
    
}

__STATIC_INLINE bool pmux_pin_set( uint32_t pin, uint8_t ps_type )
{
//    switch( pin ) {
//        //FIOS0
//        case GPIO_PIN_2 ://FIO 0
//            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO00,type << 0 );
//            break;
//        case GPIO_PIN_3 ://FIO 1
//            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO01,type << 4 );
//            break;
//        case GPIO_PIN_4 ://FIO 2
//            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO02,type << 8 );
//            break;
//        case GPIO_PIN_5 ://FIO 3
//            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO03,type << 12 );
//            break;
//        case GPIO_PIN_6 ://FIO 4
//            BX_MODIFY_REG(BX_CPU->FIOS0,CPU_FIOS0_IO04,type << 16 );
//            break;
//        case GPIO_PIN_7 ://FIO 5
//            break;
//        case GPIO_PIN_8 ://FIO 6
//            break;
//        case GPIO_PIN_9 ://FIO 7
//            break;
//        
//        //FIOS0
//        case GPIO_PIN_10 ://FIO 8
//            BX_MODIFY_REG(BX_CPU->FIOS1,CPU_FIOS1_IO08,type << 0 );
//            break;
//        case GPIO_PIN_11 ://FIO 9
//            BX_MODIFY_REG(BX_CPU->FIOS1,CPU_FIOS1_IO09,type << 4 );
//            break;
//        case GPIO_PIN_12 ://FIO 10
//            BX_MODIFY_REG(BX_CPU->FIOS1,CPU_FIOS1_IO09,type << 8 );
//            break;
//        default:
//            return false;
//    }
//    return true;
}

/* exported functions --------------------------------------------------------*/

/* exported include ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_LL_CLK_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

