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
#include "bx_config.h"
#include "apollo_00_ble_reg.h"
#include "app_qspi_wrapper.h"
#include "app_qspi.h"
#include "arch_init.h"
#include "compiler_flag.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
#define QSPI_CS_SEL_MASK                            0x1

/* private variables ---------------------------------------------------------*/
app_qspi_inst_t qspi_inst = QSPI_INSTANCE();

/* exported variables --------------------------------------------------------*/

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
N_XIP_SECTION void app_qspi_param_init_wrapper( multi_read_param_t * multi_read )
{
    qspi_inst.param.clk_div = 2;
    qspi_inst.param.rxsample_dly = 1;
    qspi_inst.param.multi_read = *multi_read;
    qspi_inst.param.clk_pin_no = QSPI_CLK_PIN_NO;
    qspi_inst.param.data_pin_no[0] = QSPI_D0_PIN_NO;
    qspi_inst.param.data_pin_no[1] = QSPI_D1_PIN_NO;
    qspi_inst.param.data_pin_no[2] = QSPI_D2_PIN_NO;
    qspi_inst.param.data_pin_no[3] = QSPI_D3_PIN_NO;
    qspi_inst.param.cs_pin_no[0] = QSPI_CS0_PIN_NO;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void app_qspi_init_wrapper()
{
    app_qspi_init( &qspi_inst.inst );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_std_write_wrapper( uint8_t * data, uint32_t length )
{
    periph_err_t error = app_qspi_std_write( &qspi_inst.inst, QSPI_CS_SEL_MASK, data, length );
    return error;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_std_write_no_dma_wrapper( uint8_t * data, uint16_t length )
{
    return app_qspi_std_write_no_dma( &qspi_inst.inst, QSPI_CS_SEL_MASK, data, length );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_flash_program_wrapper( uint8_t cmd, uint32_t addr, uint8_t * data, uint32_t length )
{
    periph_err_t error = app_qspi_flash_program( &qspi_inst.inst, QSPI_CS_SEL_MASK, cmd, addr, data, length );
    return error;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_std_read_wrapper( uint8_t * cmd_buf, uint8_t cmd_len, uint8_t * data_buf, uint16_t data_len )
{
    periph_err_t error = app_qspi_std_read( &qspi_inst.inst, QSPI_CS_SEL_MASK, cmd_buf, cmd_len, data_buf, data_len );
    return error;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_multi_read_32bits_wrapper( uint32_t * data, uint16_t length, qspi_addr_data_t addr )
{
    periph_err_t error = app_qspi_multi_read_32bits( &qspi_inst.inst, QSPI_CS_SEL_MASK, data, length, addr );
    return error;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_config_for_cache_wrapper( uint16_t cache_line_size )
{
    return app_qspi_config_for_cache( &qspi_inst.inst, QSPI_CS_SEL_MASK, cache_line_size );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint8_t app_qspi_multi_read_cmd_get_wrapper()
{
    return app_qspi_multi_read_cmd_get( &qspi_inst.inst );
}


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint32_t app_qspi_dr_reg_addr_for_cache_wrapper()
{
    return app_qspi_dr_reg_addr_for_cache( &qspi_inst.inst );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t app_qspi_disable_for_cache_wrapper()
{
    return app_qspi_disable_for_cache( &qspi_inst.inst );
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

