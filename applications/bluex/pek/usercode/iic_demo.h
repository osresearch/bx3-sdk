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
#ifndef __IIC_DEMO_H__
#define __IIC_DEMO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void    iic_add_shell_cmd( void );

void    iic_init(void);

uint8_t iic_read_byte( uint8_t dev_addr, uint8_t mem_addr );
void    iic_write_byte( uint8_t dev_addr, uint8_t mem_addr, uint8_t byte );

void    iic_read_buff( uint8_t dev_addr, uint8_t mem_addr, uint8_t * data, uint32_t read_len );
void    iic_write_buff( uint8_t dev_addr, uint8_t mem_addr, uint8_t * data, uint32_t buff_len );


#ifdef __cplusplus
}
#endif

#endif /* __IIC_DEMO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

