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
#include <string.h>
#include "flash_integration.h"
#include "flash_wrapper.h"
#include "flash_base.h"
#include "arch_init.h"
#include "spi_flash_cmd.h"
#include "compiler_flag.h"
#include "app_dmac.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static periph_err_t flash_read_byte( uint32_t offset, uint16_t length, uint8_t * buffer )
{
    uint8_t read_cmd[4] = {FLASH_READ_DATA_BYTES, offset >> 16 & 0xff, offset >> 8 & 0xff, offset & 0xff};
    return flash_read_operation( read_cmd, sizeof( read_cmd ), buffer, length );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static periph_err_t flash_multi_read_word( uint32_t offset, uint16_t length, uint32_t * buffer )
{
    return flash_multi_read_32bits_operation( buffer, length, offset );
}

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_multi_read( uint32_t offset, uint32_t length, uint8_t * buffer )
{
    periph_err_t error = PERIPH_NO_ERROR;
    uint8_t head_bytes = ( uint32_t )buffer % sizeof( uint32_t );
    if( head_bytes ) {
        uint32_t head_word;
        error = flash_multi_read_word( offset, 1, &head_word );
        if( error != PERIPH_NO_ERROR ) {
            return PERIPH_NO_ERROR;
        }
        uint8_t head_length = length < ( sizeof( uint32_t ) - head_bytes ) ? length : ( sizeof( uint32_t ) - head_bytes );
        memcpy( buffer, ( uint8_t * )&head_word, head_length );
        buffer += head_length;
        offset += head_length;
        length -= head_length;
    }
    uint16_t max_transfer_size = dmac_get_max_block_transfer_size();
    uint32_t length_32bits = length / sizeof( uint32_t );
    while( length_32bits ) {
        uint16_t transfer_size = length_32bits > max_transfer_size ? max_transfer_size : length_32bits;
        error = flash_multi_read_word( offset, transfer_size, ( uint32_t * )buffer );
        if( error != PERIPH_NO_ERROR ) {
            return error;
        }
        offset += transfer_size * sizeof( uint32_t );
        buffer += transfer_size * sizeof( uint32_t );
        length_32bits -= transfer_size;
    }
    uint8_t tail_bytes = length % sizeof( uint32_t );
    if( tail_bytes ) {
        uint32_t tail_word;
        error = flash_multi_read_word( offset, 1, &tail_word );
        if( error != PERIPH_NO_ERROR ) {
            return PERIPH_NO_ERROR;
        }
        memcpy( buffer, &tail_word, tail_bytes );
    }
    return error;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_erase_security_reg( uint8_t reg_num )
{
    return flash_erase_operation( FLASH_ERASE_SECURITY_REGISTERS, reg_num << 12, false );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_program_security_reg( uint8_t reg_num, uint16_t offset, uint16_t length, uint8_t * buffer )
{
    return flash_program_operation( FLASH_PROGRAM_SECURITY_REGISTERS, reg_num << 12 | offset & 0x1ff, length, buffer );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_program( uint32_t offset, uint32_t length, uint8_t * buffer )
{
    periph_err_t error;
    uint32_t offset_base = offset & ( ~( FLASH_PAGE_SIZE - 1 ) );
    if( offset_base != offset ) {
        uint32_t tailing_length = offset_base + FLASH_PAGE_SIZE - offset;
        uint32_t prog_length = length < tailing_length ? length : tailing_length;
        error = flash_program_operation( FLASH_PAGE_PROGRAM, offset, prog_length, buffer );
        if( error != PERIPH_NO_ERROR ) {
            return error;
        }
        buffer += prog_length;
        offset += prog_length;
        length -= prog_length;
    }
    uint16_t cycles = length / FLASH_PAGE_SIZE;
    uint16_t remainder = length % FLASH_PAGE_SIZE;
    uint16_t i;
    for( i = 0; i < cycles; ++i ) {
        error = flash_program_operation( FLASH_PAGE_PROGRAM, offset, FLASH_PAGE_SIZE, buffer );
        if( error != PERIPH_NO_ERROR ) {
            return error;
        }
        offset += FLASH_PAGE_SIZE;
        buffer += FLASH_PAGE_SIZE;
    }
    if( remainder ) {
        error = flash_program_operation( FLASH_PAGE_PROGRAM, offset, remainder, buffer );
    }
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_page_program( uint32_t offset, uint16_t length, uint8_t * buffer )
{
    return flash_program_operation( FLASH_PAGE_PROGRAM, offset, length, buffer );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_erase( uint32_t offset, erase_t type )
{
    uint8_t cmd;
    bool whole_chip;
    switch( type ) {
        case Page_Erase:
            cmd = FLASH_PAGE_ERASE;
            whole_chip = false;
        case Sector_Erase:
            cmd = FLASH_SECTOR_ERASE;
            whole_chip = false;
            break;
        case Block_32KB_Erase:
            cmd = FLASH_32KB_BLOCK_ERASE;
            whole_chip = false;
            break;
        case Block_64KB_Erase:
            cmd = FLASH_64KB_BLOCK_ERASE;
            whole_chip = false;
            break;
        case Chip_Erase:
            cmd = FLASH_CHIP_ERASE;
            whole_chip = true;
            break;
    }
    return flash_erase_operation( cmd, offset, whole_chip );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_read_sfdp( uint32_t addr, uint8_t * buf, uint8_t buf_len )
{
    uint8_t flash_write_cmd[5] = {FLASH_READ_SFDP, ( addr >> 16 ) & 0xff, ( addr >> 8 ) & 0xff, addr & 0xff, 0};
    return flash_read_operation( flash_write_cmd, sizeof( flash_write_cmd ), buf, buf_len );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_read_jedec_ptp( uint32_t * jedec_ptp )
{
    return flash_read_sfdp( 0x0c, ( uint8_t * )jedec_ptp, sizeof( uint32_t ) );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_read_manufacturer_device_id( uint8_t * manufacturer_id, uint8_t * device_id )
{
    uint8_t read_cmd[4] = {FLASH_READ_DEVICE_ID, 0, 0, 0};
    uint16_t data;
    periph_err_t error = flash_read_operation( ( uint8_t * )&read_cmd, sizeof( read_cmd ), ( uint8_t * )&data, sizeof( data ) );
    if( error == PERIPH_NO_ERROR ) {
        *manufacturer_id = data & 0xff;
        *device_id = data >> 8 & 0xff;
    }
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_read_jedec_id( uint8_t * manufacturer_id, uint8_t * mem_type, uint8_t * capacity )
{
    uint8_t read_cmd = FLASH_READ_JEDEC_ID;
    uint8_t data[3];
    periph_err_t error = flash_read_operation( &read_cmd, sizeof( read_cmd ), data, sizeof( data ) );
    if( error == PERIPH_NO_ERROR ) {
        *manufacturer_id = data[0];
        *mem_type = data[1];
        *capacity = data[2];
    }
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_read_memory_density( uint32_t * mem_density )
{
    periph_err_t error;
    do {
        uint32_t jedec_ptp;
        error = flash_read_jedec_ptp( &jedec_ptp );
        if( error != PERIPH_NO_ERROR ) {
            break;
        }
        error = flash_read_sfdp( jedec_ptp + 4, ( uint8_t * )mem_density, sizeof( uint32_t ) );
    } while( 0 );
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_reset()
{
    periph_err_t error;
    do {
        uint8_t enable_reset = FLASH_ENABLE_RESET;
        error = flash_write_no_dma_operation_start( &enable_reset, sizeof( uint8_t ) );
        if( error != PERIPH_NO_ERROR ) {
            break;
        }
        uint8_t reset_device = FLASH_RESET_DEVICE;
        error = flash_write_no_dma_operation_start( &reset_device, sizeof( uint8_t ) );
        if( error != PERIPH_NO_ERROR ) {
            break;
        }
    } while( 0 );
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t flash_wakeup()
{
    uint8_t flash_res_cmd = FLASH_RELEASE_POWER_DOWN;
    return flash_write_no_dma_operation_start( &flash_res_cmd, sizeof( flash_res_cmd ) );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION periph_err_t flash_deep_power_down()
{
    uint8_t flash_dp_cmd = FLASH_DEEP_POWER_DOWN;
    return flash_write_no_dma_operation_start( &flash_dp_cmd, sizeof( flash_dp_cmd ) );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_std_read( uint32_t offset, uint32_t length, uint8_t * buffer )
{
    uint16_t max_transfer_size = dmac_get_max_block_transfer_size();
    uint32_t cycles = length / max_transfer_size;
    uint16_t remaining_bytes = length % max_transfer_size;
    periph_err_t error = PERIPH_NO_ERROR;
    while( cycles-- ) {
        error = flash_read_byte( offset, max_transfer_size, buffer );
        if( error != PERIPH_NO_ERROR ) {
            return PERIPH_NO_ERROR;
        }
        offset += max_transfer_size;
        buffer += max_transfer_size;
    }
    if( remaining_bytes ) {
        error = flash_read_byte( offset, remaining_bytes, buffer );
    }
    return error;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_read_security_reg( uint8_t reg_num, uint16_t offset, uint16_t length, uint8_t * buffer )
{
    uint8_t read_cmd[5] = {FLASH_READ_SECURITY_REGISTERS, 0, reg_num << 4 | ( offset >> 8 & 0x1 ), offset & 0xff, 0};
    return flash_read_operation( read_cmd, sizeof( read_cmd ), buffer, length );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_read_status_reg( uint8_t cmd, uint8_t * data, uint8_t length )
{
    return flash_read_operation( &cmd, sizeof( cmd ), data, length );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t flash_write_status_reg( uint8_t cmd, uint8_t * data, uint8_t length )
{
    return flash_write_status_reg_operation( cmd, data, length );
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
