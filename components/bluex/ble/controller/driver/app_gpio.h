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
#ifndef __APP_GPIO_H__
#define __APP_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "periph_common.h"
#include "periph_recovery.h"

#include "apollo_00_ble_reg.h"
#include "reg_gpio.h"
#include "co_list.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
enum gpio_sys_stat_config
{
    GPIO_INIT,
    GPIO_UNINIT,
};

typedef struct
{
    struct  co_list_hdr hdr;
    void    (*callback)();
    uint8_t idx;
    uint8_t edge: 1,
            polarity: 1,
            both_edge: 1;
}app_gpio_int_cfg_t;

typedef struct
{
    struct  co_list int_list;
}app_gpio_env_t;

typedef struct
{
    periph_inst_t   inst;
    app_gpio_env_t  env;
    ble_reg_gpio_t *    reg;
    uint8_t         idx;
}app_gpio_inst_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define GPIO_INSTANCE(id) \
{\
    .inst = {.init_func = app_gpio_init,},\
    .reg = (ble_reg_gpio_t *)REG_GPIO##id##_BASE,\
}
/* exported functions --------------------------------------------------------*/

periph_err_t app_gpio_init(periph_inst_handle_t hdl);
periph_err_t app_gpio_uninit(periph_inst_handle_t hdl);

uint32_t app_gpio_port_dir_read(periph_inst_handle_t hdl);
uint32_t app_gpio_port_in_read(periph_inst_handle_t hdl);
uint32_t app_gpio_port_out_read(periph_inst_handle_t hdl);

void app_gpio_port_dir_output_set(periph_inst_handle_t hdl,uint32_t out_mask);
void app_gpio_port_dir_input_set(periph_inst_handle_t hdl,uint32_t in_mask);
void app_gpio_port_dir_write(periph_inst_handle_t hdl,uint32_t dir_mask);

void app_gpio_port_out_write(periph_inst_handle_t hdl,uint32_t val);
void app_gpio_port_out_set(periph_inst_handle_t hdl,uint32_t set_mask);
void app_gpio_port_out_clr(periph_inst_handle_t hdl,uint32_t clr_mask);
void app_gpio_port_out_toggle(periph_inst_handle_t hdl,uint32_t toggle_mask);

void app_gpio_int_enable(periph_inst_handle_t hdl,app_gpio_int_cfg_t *int_cfg);
void app_gpio_int_disable(periph_inst_handle_t hdl,uint8_t idx);


#ifdef __cplusplus
}
#endif

#endif /* __APP_GPIO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
