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
#ifndef __BXD_IO_MUX_H__
#define __BXD_IO_MUX_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/
enum bx_af_enable {
    QSPI_EN0,
    QSPI_EN1,
    QSPI_EN2,
    QSPI_EN3,
    
    GPIO00_EN,
    GPIO01_EN,
    SPIM0_CS1_EN,
    SPIM0_EN,
    SPIM1_CS1_EN,
    SPIM1_EN,
    GPIO14_EN,
    GPIO15_EN,
    
    SPIS_EN,
    
    BLE_MAC_DBG_EN0,
    BLE_MAC_DBG_EN1,
    BLE_MAC_DBG_EN2,
    BLE_MAC_DBG_EN3,
    BLE_MAC_DBG_EN4,
    BLE_MAC_DBG_EN5,
    BLE_MAC_DBG_EN6,
    BLE_MAC_DBG_EN7,
    
    FUNC_IO_EN00,
    FUNC_IO_EN01,
    FUNC_IO_EN02,
    FUNC_IO_EN03,
    FUNC_IO_EN04,
    FUNC_IO_EN05,
    FUNC_IO_EN06,
    FUNC_IO_EN07,
    FUNC_IO_EN08,
    FUNC_IO_EN09,
    FUNC_IO_EN10,
    FUNC_IO_EN11,
    FUNC_IO_EN12,
    FUNC_IO_EN13,
    FUNC_IO_EN14,
    FUNC_IO_EN15,
    FUNC_IO_EN16,
    FUNC_IO_EN17,
    FUNC_IO_EN18,
    FUNC_IO_EN19,
    FUNC_IO_EN20,
    FUNC_IO_EN21,
    
    RFIF_EN,
};

enum bx_pin_type {
    BX_PIN_TYPE_GENERAL_IO,
    
//    BX_PIN_TYPE_QSPI_NCS,
//    BX_PIN_TYPE_QSPI_CLK,
//    BX_PIN_TYPE_QSPI_DATA0,
//    BX_PIN_TYPE_QSPI_DATA1,
//    BX_PIN_TYPE_QSPI_DATA2,
//    BX_PIN_TYPE_QSPI_DATA3,
//    
//    BX_PIN_TYPE_SWCK,
//    BX_PIN_TYPE_SWD,
//    
//    BX_PIN_TYPE_SPIM0_CS1,
//    BX_PIN_TYPE_SPIM0_CS0,
//    BX_PIN_TYPE_SPIM0_CLK,
//    BX_PIN_TYPE_SPIM0_MISO,
//    BX_PIN_TYPE_SPIM0_MOSI,
//    
//    BX_PIN_TYPE_SPIM1_CS1,
//    BX_PIN_TYPE_SPIM1_CS0,
//    BX_PIN_TYPE_SPIM1_CLK,
//    BX_PIN_TYPE_SPIM1_MISO,
//    BX_PIN_TYPE_SPIM1_MOSI,
//    
//    BX_PIN_TYPE_SPIS_CS,
//    BX_PIN_TYPE_SPIS_CLK,
//    BX_PIN_TYPE_SPIS_MISO,
//    BX_PIN_TYPE_SPIS_MOSI,
//    
//    BX_PIN_TYPE_BLE_MAC_DBG0,
//    BX_PIN_TYPE_BLE_MAC_DBG1,
//    BX_PIN_TYPE_BLE_MAC_DBG2,
//    BX_PIN_TYPE_BLE_MAC_DBG3,
//    BX_PIN_TYPE_BLE_MAC_DBG4,
//    BX_PIN_TYPE_BLE_MAC_DBG5,
//    BX_PIN_TYPE_BLE_MAC_DBG6,
//    BX_PIN_TYPE_BLE_MAC_DBG7,
//    
//    BX_PIN_TYPE_RFIF_CLK,
//    BX_PIN_TYPE_RFIF_RX0,
//    BX_PIN_TYPE_RFIF_RX1,
//    BX_PIN_TYPE_RFIF_TX0,
//    BX_PIN_TYPE_RFIF_TX1,
//    BX_PIN_TYPE_RFIF_TX2,
//    BX_PIN_TYPE_RFIF_TX3,
//    BX_PIN_TYPE_RFIF_TX4,
//    BX_PIN_TYPE_RFIF_TX5,
//    BX_PIN_TYPE_RFIF_TX6,
//    BX_PIN_TYPE_RFIF_TX7,
//    BX_PIN_TYPE_RFIF_TX8,
//    BX_PIN_TYPE_RFIF_TX9,
//    BX_PIN_TYPE_RFIF_TX10,
//    BX_PIN_TYPE_RFIF_TX11,
    
    BX_PIN_TYPE_UART0_TX,
    BX_PIN_TYPE_UART0_RX,
    BX_PIN_TYPE_UART0_CTS,
    BX_PIN_TYPE_UART0_RTS,
    
    BX_PIN_TYPE_UART1_TX,
    BX_PIN_TYPE_UART1_RX,
    
    BX_PIN_TYPE_IIC0_SCL,
    BX_PIN_TYPE_IIC0_SDA,
    BX_PIN_TYPE_IIC1_SCL,
    BX_PIN_TYPE_IIC1_SDA,
    
    BX_PIN_TYPE_PWM0,
    BX_PIN_TYPE_PWM1,
    BX_PIN_TYPE_PWM2,
    BX_PIN_TYPE_PWM3,
    BX_PIN_TYPE_PWM4,
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t    bxd_iomux_af_enable( u8 enable_type );
bx_err_t    bxd_iomux_af_disable( u8 enable_type );

bx_err_t    bxd_iomux_set_pin_type(u8 pin_num , u8 pin_type );
bx_err_t    bxd_iomux_set_all_default( void );

#ifdef __cplusplus
}
#endif

#endif /* __BXD_IO_MUX_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

