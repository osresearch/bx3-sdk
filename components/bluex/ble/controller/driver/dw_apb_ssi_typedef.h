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
#ifndef __DW_APB_SSI_TYPEDEF_H__
#define __DW_APB_SSI_TYPEDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

typedef enum{
	Standard_SPI_Format = 0,
	Dual_SPI_Format = 1,
	Quad_SPI_Format = 2,
}CTRLR0_SPI_FRF_FIELD;

typedef enum{
	DFS_32_4_bits = 3,
	DFS_32_5_bits ,
	DFS_32_6_bits ,
	DFS_32_7_bits ,
	DFS_32_8_bits ,
	DFS_32_9_bits ,
	DFS_32_10_bits ,
	DFS_32_11_bits ,
	DFS_32_12_bits ,
	DFS_32_13_bits ,
	DFS_32_14_bits ,
	DFS_32_15_bits ,
	DFS_32_16_bits ,
	DFS_32_17_bits ,
	DFS_32_18_bits ,
	DFS_32_19_bits ,
	DFS_32_20_bits ,
	DFS_32_21_bits ,
	DFS_32_22_bits ,
	DFS_32_23_bits ,
	DFS_32_24_bits ,
	DFS_32_25_bits ,
	DFS_32_26_bits ,
	DFS_32_27_bits ,
	DFS_32_28_bits ,
	DFS_32_29_bits ,
	DFS_32_30_bits ,
	DFS_32_31_bits ,
	DFS_32_32_bits 
}CTRLR0_DFS_32_FIELD;

typedef enum{
	Control_Word_1_bit = 0,
	Control_Word_2_bit ,
	Control_Word_3_bit ,
	Control_Word_4_bit ,
	Control_Word_5_bit ,
	Control_Word_6_bit ,
	Control_Word_7_bit ,
	Control_Word_8_bit ,
	Control_Word_9_bit ,
	Control_Word_10_bit ,
	Control_Word_11_bit ,
	Control_Word_12_bit ,
	Control_Word_13_bit ,
	Control_Word_14_bit ,
	Control_Word_15_bit ,
	Control_Word_16_bit ,
}CTRLR0_CFS_FIELD;

typedef enum{
	Normal_Mode_Operation = 0,
	Test_Mode_Operation
}CTRLR0_SRL_FIELD;

typedef enum{
	Slave_txd_Enabled = 0,
	Slave_txd_Disabled
}CTRLR0_SLV_OE_FIELD;

typedef enum{
	Transmit_and_Receive = 0,
	Transmit_Only,
	Receive_Only,
	EEPROM_Read
}CTRLR0_TMOD_FIELD;

typedef enum{
	Inactive_Low = 0,
	Inactive_High
}CTRLR0_SCPOL_FIELD;

typedef enum{
	SCLK_Toggle_In_Middle = 0,
	SCLK_Toggle_At_Start
}CTRLR0_SCPH_FIELD;

typedef enum{
	Motorola_SPI = 0,
	Texas_Instruments_SSP,
	National_Semiconductors_Microwire,
}CTRLR0_FRF_FIELD;

typedef enum{
	Handshaking_Interface_Disabled = 0,
	Handshaking_Interface_Enabled
}MWCR_MHS_FIELD;

typedef enum{
	Microwire_Receive = 0,
	Microwire_Transmit
}MWCR_MDD_FIELD;

typedef enum{
	Non_Sequential_Transfer = 0,
	Sequential_Transfer
}MWCR_MWMOD_FIELD;

typedef enum
{
	SSI_Disabled = 0,
	SSI_Enabled
}SSIENR_SSI_EN_FIELD;

typedef enum
{
	No_Transmit_Data_Collision_Error = 0,
	Transmit_Data_Collision_Error
}SR_DCOL_FIELD;

typedef enum
{
	No_Transmission_Error = 0,
	Transmission_Error
}SR_TXE_FIELD;

typedef enum
{
	Receive_FIFO_Not_Full = 0,
	Receive_FIFO_Full
}SR_RFF_FIELD;

typedef enum
{
	Receive_FIFO_Empty = 0,
	Receive_FIFO_Not_Empty
}SR_RFNE_FIELD;

typedef enum
{
	Transmit_FIFO_Not_Empty = 0,
	Transmit_FIFO_Empty
}SR_TFE_FIELD;

typedef enum
{
	Transmit_FIFO_Full = 0,
	Transmit_FIFO_Not_Full
}SR_TFNF_FIELD;

typedef enum
{
	SSI_Idle_or_Disabled = 0,
	SSI_Busy
}SR_BUSY_FIELD;


typedef enum
{
	Multi_Master_Con_Interrupt_Disable = 0,
	Multi_Master_Con_Interrupt_Enable
}IMR_MSTIM_MASK;

typedef enum
{
	Receive_FIFO_Full_Disable = 0,
	Receive_FIFO_Full_Enable
}IMR_RXFIM_MASK;

typedef enum
{
	Receive_FIFO_OverFlow_Disable = 0,
	Receive_FIFO_OverFlow_Enable
}IMR_RXOIM_MASK;

typedef enum
{
	Receive_FIFO_UnderFlow_Disable = 0,
	Receive_FIFO_UnderFlow_Enable
}IMR_RXUIM_MASK;

typedef enum
{
	Transmit_FIFO_OverFlow_Disable = 0,
	Transmit_FIFO_OverFlow_Enable
}IMR_TXOIM_MASK;

typedef enum
{
	Transmit_FIFO_Empty_Disable = 0,
	Transmit_FIFO_Empty_Enable
}IMR_TXEIM_MASK;	

typedef enum
{
	Transmit_DMA_Disabled = 0,
	Transmit_DMA_Enabled
}DMACR_TDMAE_FIELD;

typedef enum
{
	Receive_DMA_Disabled = 0,
	Receive_DMA_Enabled
}DMACR_RDMAE_FIELD;

typedef enum
{
	Instruction_Length_0_bit = 0,
	Instruction_Length_4_bits,
	Instruction_Length_8_bits,
	Instruction_Length_16_bits,
}SPI_CTRLR0_INST_L_FIELD;

typedef enum
{
	Addr_Width_0_bit = 0,
	Addr_Width_4_bits,
	Addr_Width_8_bits,
	Addr_Width_12_bits,
	Addr_Width_16_bits,
	Addr_Width_20_bits,
	Addr_Width_24_bits,
	Addr_Width_28_bits,
	Addr_Width_32_bits,
	Addr_Width_36_bits,
	Addr_Width_40_bits,
	Addr_Width_44_bits,
	Addr_Width_48_bits,
	Addr_Width_52_bits,
	Addr_Width_56_bits,
	Addr_Width_60_bits
}SPI_CTRLR0_ADDR_L_FIELD;

typedef enum
{
	Both_Standard_SPI_Mode = 0,
	Instruction_Standard_Address_Specific,
	Both_Specific_Mode,
}SPI_CTRLR0_TRANS_TYPE_FIELD;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __DW_APB_SSI_TYPEDEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
