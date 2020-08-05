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
#ifndef __FLASH_INTEGRATION_H__
#define __FLASH_INTEGRATION_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "app_qspi.h"
#include "periph_error.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

periph_err_t flash_program_operation(uint8_t cmd,uint32_t offset, uint32_t length, uint8_t *buffer);

periph_err_t flash_erase_operation(uint8_t cmd,uint32_t addr,bool whole_chip);

periph_err_t flash_read_operation(uint8_t *cmd_buf,uint8_t cmd_len,uint8_t *data_buf,uint16_t data_len);

periph_err_t flash_multi_read_32bits_operation(uint32_t *data,uint16_t length,uint32_t addr);

periph_err_t flash_write_status_reg_operation(uint8_t cmd,uint8_t *data,uint8_t length);


#ifdef __cplusplus
}
#endif

#endif /* __FLASH_INTEGRATION_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
