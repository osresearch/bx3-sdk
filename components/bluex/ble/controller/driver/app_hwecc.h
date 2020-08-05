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
#ifndef __APP_HWECC_H__
#define __APP_HWECC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "periph_common.h"
#include "apollo_00_ble_reg.h"
#include "reg_ecc.h"
#include "periph_error.h"
#include "periph_lock.h"

/* exported define -----------------------------------------------------------*/
#define ECC_BLOCK_SIZE          32

/* exported types ------------------------------------------------------------*/

enum hwecc_sys_stat_config
{
    HWECC_INIT,
    HWECC_UNINIT,
    HWECC_START,
    HWECC_DONE,
    
};

typedef struct {
    uint8_t content[ECC_BLOCK_SIZE]; 
}ecc_ram_field_t;
typedef struct {
    ecc_ram_field_t block[16];
}ecc_ram_t;

typedef struct {
    uint8_t const *secret_key;
    uint8_t const *public_key[2];
}ecc_in_t;

typedef struct {
    uint8_t *key[2];
}ecc_out_t;

typedef struct{
    ecc_out_t out;
    void (*callback)(void *);
    void *dummy;
}ecc_rslt_t;

typedef struct
{
    periph_inst_t inst;         /**< Peripheral common instance for HWECC.  */
    ble_reg_ecc_t *reg;             /**< HWECC register base address.           */
    ecc_rslt_t rslt;
    periph_lock_t ecc_lock;
}app_hwecc_inst_t; 

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define HWECC_INSTANCE(id)\
{\
    .inst = {.init_func = app_hwecc_init,},\
    .reg = (ble_reg_ecc_t *)REG_ECC##id##_BASE,\
}

/* exported functions --------------------------------------------------------*/

periph_err_t app_hwecc_init(periph_inst_handle_t hdl);
periph_err_t app_hwecc_uninit(periph_inst_handle_t hdl);
periph_err_t app_hwecc_calculate(periph_inst_handle_t hdl,ecc_in_t *in,ecc_rslt_t *rslt);

void app_hwecc_isr(app_hwecc_inst_t *inst);

#ifdef __cplusplus
}
#endif

#endif /* __APP_HWECC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
