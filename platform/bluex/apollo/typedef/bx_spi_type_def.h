/**
  ******************************************************************************
  * @file   :   bx_spi_type_def.h
  * @version:
  * @author :
  * @brief  :   Define common spi types for different MCU
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
#ifndef __BX_SPI_TYPE_DEF_H__
#define __BX_SPI_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

enum bx_spi_mode{
    BX_SPI_MODE_MASTER,
    BX_SPI_MODE_SLAVE,
    BX_SPI_MODE_MAX,
};

enum bx_spi_data_bit {
    BX_SPI_DATA_BIT_4B,
    BX_SPI_DATA_BIT_5B,
    BX_SPI_DATA_BIT_6B,
    BX_SPI_DATA_BIT_7B,
    BX_SPI_DATA_BIT_8B,
    BX_SPI_DATA_BIT_9B,
    BX_SPI_DATA_BIT_10B,
    BX_SPI_DATA_BIT_11B,
    BX_SPI_DATA_BIT_12B,
    BX_SPI_DATA_BIT_13B,
    BX_SPI_DATA_BIT_14B,
    BX_SPI_DATA_BIT_15B,
    BX_SPI_DATA_BIT_16B,
    BX_SPI_DATA_BIT_17B,
    BX_SPI_DATA_BIT_18B,
    BX_SPI_DATA_BIT_19B,
    BX_SPI_DATA_BIT_20B,
    BX_SPI_DATA_BIT_21B,
    BX_SPI_DATA_BIT_22B,
    BX_SPI_DATA_BIT_23B,
    BX_SPI_DATA_BIT_24B,
    BX_SPI_DATA_BIT_25B,
    BX_SPI_DATA_BIT_26B,
    BX_SPI_DATA_BIT_27B,
    BX_SPI_DATA_BIT_28B,
    BX_SPI_DATA_BIT_29B,
    BX_SPI_DATA_BIT_30B,
    BX_SPI_DATA_BIT_31B,
    BX_SPI_DATA_BIT_32B,
    BX_SPI_DATA_BIT_MAX,
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __BX_SPI_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

