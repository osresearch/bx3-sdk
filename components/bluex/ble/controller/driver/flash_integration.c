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
#include <stdbool.h>
#include <stdarg.h>
#include "apollo_00_ble_reg.h"
#include "spi_flash_cmd.h"
#include "bx_dbg.h"
#include "flash_integration.h"
#include "flash_base.h"
#include "arch_init.h"
#include "compiler_flag.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/

/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t flash_program_operation( uint8_t cmd, uint32_t offset, uint32_t length, uint8_t * buffer )
{
    periph_err_t error;
    __disable_irq();
    cache_disable();
    error = flash_program_operation_start( cmd, offset, length, buffer );
    cache_enable();
    __enable_irq();
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t flash_erase_operation( uint8_t cmd, uint32_t addr, bool whole_chip )
{
    periph_err_t error;
    __disable_irq();
    cache_disable();
    error = flash_erase_operation_start( cmd, addr, whole_chip );
    cache_enable();
    __enable_irq();
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t flash_read_operation( uint8_t * cmd_buf, uint8_t cmd_len, uint8_t * data_buf, uint16_t data_len )
{
    periph_err_t error;
    __disable_irq();
    cache_disable();
    error = flash_read_operation_start( cmd_buf, cmd_len, data_buf, data_len );
    cache_enable();
    __enable_irq();
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t flash_multi_read_32bits_operation( uint32_t * data, uint16_t length, uint32_t addr )
{
    periph_err_t error;
    __disable_irq();
    cache_disable();
    error = flash_multi_read_32bits_operation_start( data, length, addr );
    cache_enable();
    __enable_irq();
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t flash_write_status_reg_operation( uint8_t cmd, uint8_t * data, uint8_t length )
{
    periph_err_t error;
    __disable_irq();
    cache_disable();
    error = flash_write_status_reg_start( cmd, data, length );
    cache_enable();
    __enable_irq();
    return error;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

