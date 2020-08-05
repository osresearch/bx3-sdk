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
#ifndef __DMAC_TYPEDEF_H__
#define __DMAC_TYPEDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

typedef enum{
	DMAC_Disabled = 0,
	DMAC_Enabled
}DMACFGREG_DMA_EN_FIELD;

typedef enum{
	Interrupt_Disabled = 0,
	Interrupt_Enabled
}CTLx_INT_EN_FIELD;

typedef enum{
	Transfer_Width_8_bits = 0,
	Transfer_Width_16_bits,
	Transfer_Width_32_bits,
	Transfer_Width_64_bits,
	Transfer_Width_128_bits,
	Transfer_Width_256_bits
}CTLx_SRC_DST_TR_WIDTH_FIELD;

typedef enum{
	Address_Increment = 0,
	Address_Decrement,
	Address_No_Change
}CTLx_SINC_DINC_FIELD;

typedef enum{
	Burst_Transaction_Length_1 = 0,
	Burst_Transaction_Length_4,
	Burst_Transaction_Length_8,
	Burst_Transaction_Length_16,
	Burst_Transaction_Length_32,
	Burst_Transaction_Length_64,
	Burst_Transaction_Length_128,
	Burst_Transaction_Length_256
}CTLx_SRC_DST_MSIZE_FIELD;

typedef enum{
	Memory_to_Memory_DMAC_Flow_Controller = 0,
	Memory_to_Peripheral_DMAC_Flow_Controller,
	Peripheral_to_Memory_DMAC_Flow_Controller,
	Peripheral_to_Peripheral_DMAC_Flow_Controller,
	Peripheral_to_Memory_Peripheral_Flow_Controller,
	Peripheral_to_Peripheral_Source_Peripheral_Flow_Controller,
	Memory_to_Peripheral_Peripheral_Flow_Controller,
	Peripheral_to_Peripheral_Destination_Peripheral_Flow_Controller
}CTLx_TT_FC_FIELD;

typedef enum{
	Hardware_Handshaking = 0,
	Software_Handshaking,
}CFGx_HS_SEL_SRC_DST_FIELD;

typedef enum{
	HS_Polarity_Active_High = 0,
	HS_Polarity_Active_Low
}CFGx_SRC_DST_HS_POL_FIELD;

typedef enum{
	QSPI_TX_Handshaking = 0,
	QSPI_RX_Handshaking,
	SPI_Master0_TX_Handshaking,
	SPI_Master0_RX_Handshaking,
	SPI_Master1_TX_Handshaking,
	SPI_Master1_RX_Handshaking,
	SPI_Slave_TX_Handshaking,
	SPI_Slave_RX_Handshaking,
	UART0_TX_Handshaking,
	UART0_RX_Handshaking,
	UART1_TX_Handshaking,
	UART1_RX_Handshaking,
	IIC0_TX_Handshaking,
	IIC0_RX_Handshaking,
	IIC1_TX_Handshaking,
	IIC1_RX_Handshaking,
}CFGx_DEST_SRC_PER_FIELD;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __DMAC_TYPEDEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

