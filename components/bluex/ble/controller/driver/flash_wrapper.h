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
#ifndef __FLASH_WRAPPER_H__
#define __FLASH_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "periph_error.h"

/* exported define -----------------------------------------------------------*/
#define FLASH_TYPE_UNKNOWN                              0
#define FLASH_PAGE_SIZE                                 256

#define MANUFACTURER_XMC                                0x20
#define MANUFACTURER_ZBIT                               0x5E
#define MANUFACTURER_PUYA                               0x85
#define MANUFACTURER_WINBOND                            0xEF

/* exported types ------------------------------------------------------------*/
typedef enum{
    Page_Erase,
    Sector_Erase,
    Block_32KB_Erase,
    Block_64KB_Erase,
    Chip_Erase,
}erase_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

//periph_err_t flash_reset(void);

//periph_err_t flash_wakeup(void);

//periph_err_t flash_erase(uint32_t offset, erase_t type);
periph_err_t flash_erase_security_reg(uint8_t reg_num);

//periph_err_t flash_program(uint32_t offset, uint32_t length, uint8_t *buffer);
//periph_err_t flash_page_program(uint32_t offset,uint16_t length,uint8_t *buffer);
periph_err_t flash_program_security_reg(uint8_t reg_num, uint16_t offset, uint16_t length, uint8_t * buffer);
//periph_err_t flash_write_status_reg(uint8_t cmd,uint8_t *data,uint8_t length);

periph_err_t flash_std_read(uint32_t offset,uint32_t length,uint8_t *buffer);
//periph_err_t flash_multi_read(uint32_t offset, uint32_t length, uint8_t *buffer);
//periph_err_t flash_read_memory_density(uint32_t *mem_density);
//periph_err_t flash_read_sfdp(uint32_t addr,uint8_t *buf,uint8_t buf_len);
periph_err_t flash_read_security_reg(uint8_t reg_num, uint16_t offset, uint16_t length, uint8_t * buffer);
//periph_err_t flash_read_status_reg(uint8_t cmd,uint8_t *data,uint8_t length);
//periph_err_t flash_read_manufacturer_device_id(uint8_t *manufacturer_id,uint8_t *device_id);
//periph_err_t flash_read_jedec_id(uint8_t *manufacturer_id,uint8_t *mem_type,uint8_t *capacity);

//periph_err_t flash_deep_power_down(void);

periph_err_t flash_wakeup(void);
periph_err_t flash_erase(uint32_t offset, erase_t type);
periph_err_t flash_program(uint32_t offset, uint32_t length, uint8_t *buffer);
periph_err_t flash_page_program(uint32_t offset,uint16_t length,uint8_t *buffer);
periph_err_t flash_multi_read(uint32_t offset, uint32_t length, uint8_t *buffer);
periph_err_t flash_deep_power_down(void);

//void flash_test(void);
//void flash_security_reg_test(void);

periph_err_t flash_read_manufacturer_device_id(uint8_t *manufacturer_id,uint8_t *device_id);
periph_err_t ZBIT_flash_read_security_reg(uint8_t reg_num,uint16_t offset,uint16_t length,uint8_t *buffer);

periph_err_t XMC_flash_enter_OTP_mode(void);
periph_err_t XMC_flash_exit_OTP_mode(void);

#ifdef __cplusplus
}
#endif

#endif /* __FLASH_WRAPPER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

