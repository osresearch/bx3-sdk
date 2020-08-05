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
#ifndef __REG_CACHE_H__
#define __REG_CACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

typedef struct
{
    volatile uint32_t REG_CACHE_EN;
    volatile uint32_t REG_FLASH_BASE_ADDR;
    volatile uint32_t REG_QSPI_DR_ADDR;
    volatile uint32_t REG_FLASH_CMD;
    volatile uint32_t REG_FLUSH_ADDR_L;
    volatile uint32_t REG_FLUSH_ADDR_H;
    volatile uint32_t REG_FLUSH_ALL;
    volatile uint32_t REG_FLUSH_EN;
}ble_reg_cache_t;

enum CACHE_REG_CACHE_EN_FIELD
{
    CACHE_CACHE_EN_MASK = 0x1,
    CACHE_CACHE_EN_POS = 0,
};

enum CACHE_REG_FLASH_BASE_ADDR_FIELD
{
    CACHE_FLASH_BASE_ADDR_MASK = (int)0xffffffffL,
    CACHE_FLASH_BASE_ADDR_POS = 0,
};

enum CACHE_REG_QSPI_DR_ADDR_FIELD
{
    CACHE_QSPI_DR_ADDR_MASK = (int)0xffffffffL,
    CACHE_QSPI_DR_ADDR_POS = 0,
};

enum CACHE_REG_FLASH_CMD_FIELD
{
    CACHE_TRAM_PARA_MASK = 0x3fff0000,
    CACHE_TRAM_PARA_POS = 16,
    CACHE_FLASH_RD_CMD_FORMAT_MASK = 0x400,
    CACHE_FLASH_RD_CMD_FORMAT_POS = 10,
    CACHE_FLASH_RD_DATA_FORMAT_MASK = 0x200,
    CACHE_FLASH_RD_DATA_FORMAT_POS = 9,
    CACHE_FLASH_RD_ADDR_FORMAT_MASK = 0x100,
    CACHE_FLASH_RD_ADDR_FORMAT_POS = 8,
    CACHE_FLASH_RD_CMD_MASK = 0xff,
    CACHE_FLASH_RD_CMD_POS = 0,
};

enum CACHE_REG_FLUSH_ADDR_L_FIELD
{
    CACHE_FLUSH_ADDR_L_MASK = (int)0xffffffffL,
    CACHE_FLUSH_ADDR_L_POS = 0,
};

enum CACHE_REG_FLUSH_ADDR_H_FIELD
{
    CACHE_FLUSH_ADDR_H_MASK = (int)0xffffffffL,
    CACHE_FLUSH_ADDR_H_POS = 0,
};

enum CACHE_REG_FLUSH_ALL_FIELD
{
    CACHE_FLUSH_ALL_MASK = 0x1,
    CACHE_FLUSH_ALL_POS = 0,
};

enum CACHE_REG_FLUSH_EN_FIELD
{
    CACHE_FLUSH_EN_MASK = 0x1,
    CACHE_FLUSH_EN_POS = 0,
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __REG_CACHE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

