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
#ifndef __PERIPH_COMMON_H__
#define __PERIPH_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "periph_error.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

typedef enum
{
    INTR_ENABLE,
    INTR_DISABLE,
    INTR_CLR,    
}intr_operation_t;

typedef enum
{
    SET_CLK,
    CLR_CLK,
}clk_gate_operation_t;

typedef void (*intr_op_func_t)(void *, intr_operation_t op);
typedef void (*sw_rst_func_t)(void *);
typedef void (*clk_src_cfg_func_t)(void *,uint32_t clk_cfg);
typedef void (*clk_gate_func_t)(void *,clk_gate_operation_t op);
typedef void (*pin_cfg_func_t)(void *,uint8_t pin_num,uint32_t pin_role,bool enable);
typedef void (*sys_stat_func_t)(void *,uint32_t sys_stat);

typedef struct
{
    intr_op_func_t intr_op_func;
    sw_rst_func_t sw_rst_func;
    clk_src_cfg_func_t clk_src_cfg_func;
    clk_gate_func_t clk_gate_func;
    pin_cfg_func_t pin_cfg_func;
    sys_stat_func_t sys_stat_func;
}periph_universal_func_set_t;

typedef struct periph_inst_s
{
    periph_err_t (*init_func)(struct periph_inst_s*);
}periph_inst_t;

typedef periph_inst_t * periph_inst_handle_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __AB_CD_EF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
