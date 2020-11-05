/**
  ******************************************************************************
  * @file   :   .c
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
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "app_qspi_wrapper.h"
#include "spi_flash_cmd.h"
#include "reg_cache.h"
#include "apollo_00_ble_reg.h"
#include "periph_common.h"
#include "field_manipulate.h"
#include "flash_cache.h"
#include "arch_init.h"
#include "compiler_flag.h"
#include "clk_gate.h"
#include "reg_sysc_cpu_apollo_00.h"

/* private define ------------------------------------------------------------*/
#define CACHE_REG                                       ( ( ble_reg_cache_t * ) REG_CACHE_BASE )
#define CACHE_LINE_SIZE_IN_BYTES                        32

/* private typedef -----------------------------------------------------------*/

typedef enum {
    Little_Endian = 0,  /* !< Little_Endian */
    Big_Endian          /* !< Big_Endian */
} FLASH_OUTPUT_DATA_FORMAT;

typedef enum {
    Right_Justified = 0,
    Left_Justified
} CMD_ADDR_ALIGNMENT;

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
extern clk_gate_func_t cache_clk_gate_func;
extern sys_stat_func_t cache_sys_stat_func;

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void flash_cache_flush( uint32_t low_addr, uint32_t high_addr )
{
    CACHE_REG->REG_FLUSH_ALL = 0;
    CACHE_REG->REG_FLUSH_ADDR_L = low_addr;
    CACHE_REG->REG_FLUSH_ADDR_H = high_addr;
    CACHE_REG->REG_FLUSH_EN = 1;
    while( CACHE_REG->REG_FLUSH_EN );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void flash_cache_flush_all()
{
    CACHE_REG->REG_FLUSH_ALL = 1;
    CACHE_REG->REG_FLUSH_EN = 1;
    while( CACHE_REG->REG_FLUSH_EN );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void flash_cache_config( uint32_t flash_base_addr )
{
    sysc_cpu_cache_has_sram_setf( 1 );
    ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_CACHE );
    flash_cache_flush_all();
    CACHE_REG->REG_FLASH_BASE_ADDR = flash_base_addr;
    CACHE_REG->REG_QSPI_DR_ADDR = app_qspi_dr_reg_addr_for_cache_wrapper();
    CACHE_REG->REG_FLASH_CMD = FIELD_BUILD( CACHE_TRAM_PARA, 0x1380 ) |
                               FIELD_BUILD( CACHE_FLASH_RD_CMD_FORMAT, Right_Justified ) |
                               FIELD_BUILD( CACHE_FLASH_RD_DATA_FORMAT, Little_Endian ) |
                               FIELD_BUILD( CACHE_FLASH_RD_ADDR_FORMAT, Right_Justified );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t flash_cache_enable()
{
    periph_err_t error = app_qspi_config_for_cache_wrapper( CACHE_LINE_SIZE_IN_BYTES );
    if( error == PERIPH_NO_ERROR ) {
        ble_clk_gate_cpu_g1( BLE_CPU_CLKG_SET_CACHE );
        REG_FIELD_WR( CACHE_REG->REG_FLASH_CMD, CACHE_FLASH_RD_CMD, app_qspi_multi_read_cmd_get_wrapper() );
        CACHE_REG->REG_CACHE_EN = 1;
        uint32_t time=0xFF;
        while(time-->0);
    }
    return error;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t flash_cache_disable()
{
    periph_err_t error = app_qspi_disable_for_cache_wrapper();
    if( error == PERIPH_NO_ERROR ) {
        CACHE_REG->REG_CACHE_EN = 0;
        ble_clk_gate_cpu_g1( BLE_CPU_CLKG_CLR_CACHE );
    }
    return error;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

