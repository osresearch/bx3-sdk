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
#ifndef __IO_CTRL_H__
#define __IO_CTRL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/**@brief IO pull type */
typedef enum 
{
    IO_PULL_DISABLE,
    IO_PULL_UP,
    IO_PULL_DOWN,    
}io_pull_type_t;

/**@brief external interrupt trigger mode */
typedef enum 
{
    EXT_INT_TRIGGER_HIGH_LEVEL,
    EXT_INT_TRIGGER_LOW_LEVEL,
    EXT_INT_TRIGGER_POS_EDGE,
    EXT_INT_TRIGGER_NEG_EDGE,    
}ext_int_mode_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


void        io_init(void);

void        io_write_all(uint32_t val);
uint32_t    io_read_all(void);
uint32_t    io_out_read_all(void);
uint32_t    io_dir_read_all(void);
uint8_t     io_pin_read(uint8_t pin_num);
uint8_t     io_pin_out_read(uint8_t pin_num);

void io_dir_write_all_noie(uint32_t dir);
void io_dir_write_all(uint32_t dir);
void io_dir_output_set(uint32_t output_mask);
void io_dir_input_set(uint32_t input_mask);

void io_cfg_output(uint8_t pin_num);
void io_cfg_input(uint8_t pin_num);

void io_pin_dir_set(uint8_t pin_num,uint8_t dir);
void io_pin_write(uint8_t pin_num,uint8_t val);
void io_pin_set(uint8_t pin_num);
void io_pin_clear(uint8_t pin_num);
void io_pin_toggle(uint8_t pin_num);

void io_pin_pull_write(uint8_t pin_num,io_pull_type_t pull);
io_pull_type_t io_pin_pull_read(uint8_t pin_num);

void ext_set_touch_cb(void (*cb)(void));
void io_ext_int_cfg(uint8_t pin_num,ext_int_mode_t mode,void (*callback)());
void io_ext_int_en(uint8_t pin_num,bool enable);
void io_ext_int_pin_en(uint8_t pin_num,bool enable);
void io_ext_int_mask(uint8_t pin_num,bool unmask);

#ifdef __cplusplus
}
#endif

#endif /* __IO_CTRL_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
