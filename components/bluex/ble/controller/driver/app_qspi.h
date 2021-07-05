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
#ifndef __APP_QSPI_H__
#define __APP_QSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "periph_common.h"
#include "reg_ssi.h"
#include "apollo_00_ble_reg.h"
#include "periph_error.h"
#include "periph_lock.h"

/* exported define -----------------------------------------------------------*/
#define QSPI_CS_NUM                                     1
#define QSPI_CS0_PIN_NO                                 24
#define QSPI_CLK_PIN_NO                                 25
#define QSPI_D0_PIN_NO                                  26
#define QSPI_D1_PIN_NO                                  27
#define QSPI_D2_PIN_NO                                  28
#define QSPI_D3_PIN_NO                                  29

/* exported types ------------------------------------------------------------*/

enum qspi_sys_stat_config
{
    QSPI_INIT,
    QSPI_UNINIT,
    QSPI_OP_START,
    QSPI_OP_DONE,
};

enum qspi_pin_role_config
{
    QSPI_CLK_PIN,
    QSPI_D0_PIN,
    QSPI_D1_PIN,
    QSPI_D2_PIN,
    QSPI_D3_PIN,
    QSPI_CS0_PIN,
    QSPI_CS1_PIN,
    QSPI_CS2_PIN,
    QSPI_CS3_PIN,
};

typedef struct
{
    uint32_t extend_byte:8,
                    addr:24;
}qspi_addr_data_t;

typedef struct
{
    uint8_t cmd;
    uint8_t trans_type:2,
           wait_cycles:4,
             dual_quad:2;
}multi_read_param_t;

typedef struct
{
    uint16_t clk_div;
    uint8_t rxsample_dly;
    multi_read_param_t multi_read;
    uint8_t clk_pin_no;
    uint8_t data_pin_no[4];
    uint8_t cs_pin_no[QSPI_CS_NUM];
}app_qspi_init_param_t;

typedef struct
{
    periph_inst_t inst;
    app_qspi_init_param_t param;
    ble_reg_ssi_t *reg;
    periph_lock_t qspi_lock;
    uint8_t idx;
}app_qspi_inst_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

#define QSPI_INSTANCE(id) \
{\
    .inst = {.init_func = app_qspi_init,},\
    .reg = (ble_reg_ssi_t *)REG_QSPI##id##_BASE,\
}


/* exported functions --------------------------------------------------------*/

periph_err_t app_qspi_init(periph_inst_handle_t hdl);
periph_err_t app_qspi_uninit(periph_inst_handle_t hdl);

periph_err_t app_qspi_std_write(periph_inst_handle_t hdl,uint8_t cs_sel_mask,uint8_t *data,uint32_t length);
periph_err_t app_qspi_std_write_no_dma(periph_inst_handle_t hdl,uint8_t cs_sel_mask,uint8_t *data,uint16_t length);
periph_err_t app_qspi_4wire_write( periph_inst_handle_t hdl, uint8_t cs_sel_mask, uint8_t * data, uint32_t length );
periph_err_t app_qspi_4wire_write_ex( periph_inst_handle_t hdl, uint8_t cs_sel_mask, uint8_t cmd, uint32_t addr, uint8_t * data, uint32_t length );
periph_err_t app_qspi_flash_program(periph_inst_handle_t hdl,uint8_t cs_sel_mask,uint8_t cmd,uint32_t addr,uint8_t *data,uint32_t length);

periph_err_t app_qspi_std_read(periph_inst_handle_t hdl,uint8_t cs_sel_mask,uint8_t *cmd_buf,uint8_t cmd_len,uint8_t *data_buf,uint16_t data_len);
periph_err_t app_qspi_multi_read_32bits(periph_inst_handle_t hdl,uint8_t cs_sel_mask,uint32_t *data,uint16_t length,qspi_addr_data_t addr);
uint8_t      app_qspi_multi_read_cmd_get(periph_inst_handle_t hdl);

periph_err_t app_qspi_config_for_cache(periph_inst_handle_t hdl,uint8_t cs_sel_mask,uint16_t cache_line_size);
uint32_t     app_qspi_dr_reg_addr_for_cache(periph_inst_handle_t hdl);
periph_err_t app_qspi_disable_for_cache(periph_inst_handle_t hdl);

#ifdef __cplusplus
}
#endif

#endif /* __APP_QSPI_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
