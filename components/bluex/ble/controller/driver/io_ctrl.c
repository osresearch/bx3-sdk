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
#include "io_ctrl.h"
#include "app_gpio.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_awo_apollo_00.h"
#include "log.h"
#include "sysctrl.h"
#include "compiler_flag.h"
#include "ll.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
app_gpio_inst_t app_gpio_inst = GPIO_INSTANCE();

/* exported variables --------------------------------------------------------*/


/* private macros ------------------------------------------------------------*/
//static void ( *ext_int_cb[5] )();
//static void ( *touch_cb )();
static uint8_t ext_int_idx_get( uint8_t pin_num );

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint8_t ext_int_idx_get( uint8_t pin_num )
{
    uint8_t idx = 0xff;
    switch( pin_num ) {
        case 15:
            idx = 0;
            break;
        case 16:
            idx = 1;
            break;
        case 17:
            idx = 2;
            break;
        case 22:
            idx = 3;
            break;
        case 23:
            idx = 4;
            break;
    }
    return idx;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void io_ext_int_ctrl( uint8_t pin_num, bool enable, bool int_mask_ctrl )
{
    GLOBAL_INT_DISABLE();
    uint8_t idx = ext_int_idx_get( pin_num );
    BX_ASSERT( idx != 0xff );
    uint32_t ext_int_cfg = sysc_awo_ext_inrp_config_get();
    if( enable ) {
        sysctrl_io_config( pin_num, EXTERNAL_INTR_IO );
        sysc_awo_ext_inrp_clr_set( 1 << idx );
        ext_int_cfg |= 1 << ( idx + 20 );
        if( int_mask_ctrl ) {
            ext_int_cfg |= 1 << idx;
        }
        sysc_awo_ext_inrp_config_set( ext_int_cfg );
    } else {
        ext_int_cfg &= ~( 1 << ( idx + 20 ) );
        if( int_mask_ctrl ) {
            ext_int_cfg &= ~( 1 << idx );
        }
        sysc_awo_ext_inrp_config_set( ext_int_cfg );
        sysctrl_io_config( pin_num, 0 );
    }
    GLOBAL_INT_RESTORE();
}

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_init( void )
{
    app_gpio_init( &app_gpio_inst.inst );
    // enable ext interrupt
    NVIC_ClearPendingIRQ( EXT_INTR_IRQn );
    NVIC_EnableIRQ( EXT_INTR_IRQn );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void io_write_all( uint32_t val )
{
    app_gpio_port_out_write( &app_gpio_inst.inst, val );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint32_t io_read_all( void )
{
    return app_gpio_port_in_read( &app_gpio_inst.inst );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint32_t io_out_read_all( void )
{
    return app_gpio_port_out_read( &app_gpio_inst.inst );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint32_t io_dir_read_all( void )
{
    return app_gpio_port_dir_read( &app_gpio_inst.inst );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void io_dir_write_all_noie( uint32_t dir )
{
    app_gpio_port_dir_write( &app_gpio_inst.inst, dir );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_dir_write_all( uint32_t dir )
{
    GLOBAL_INT_DISABLE();
    sysctrl_io_config_mask( 0xffffffff, GENERAL_PURPOSE_IO );
    app_gpio_port_dir_write( &app_gpio_inst.inst, dir );
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_dir_output_set( uint32_t output_mask )
{
    GLOBAL_INT_DISABLE();
    sysctrl_io_config_mask( output_mask, GENERAL_PURPOSE_IO );
    app_gpio_port_dir_output_set( &app_gpio_inst.inst, output_mask );
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_dir_input_set( uint32_t input_mask )
{
    GLOBAL_INT_DISABLE();
    sysctrl_io_config_mask( input_mask, GENERAL_PURPOSE_IO );
    app_gpio_port_dir_input_set( &app_gpio_inst.inst, input_mask );
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_cfg_output( uint8_t pin_num )
{
    GLOBAL_INT_DISABLE();
    sysctrl_io_config_mask( 1 << pin_num, GENERAL_PURPOSE_IO );
    app_gpio_port_dir_output_set( &app_gpio_inst.inst, 1 << pin_num );
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_cfg_input( uint8_t pin_num )
{
    GLOBAL_INT_DISABLE();
    uint8_t ext_int_id = ext_int_idx_get( pin_num );
    if( ext_int_id == 0xff ) {
        sysctrl_io_config_mask( 1 << pin_num, GENERAL_PURPOSE_IO );
    } else {
        uint32_t ext_int_cfg = sysc_awo_ext_inrp_config_get();
        if( ( ext_int_cfg & 1 << ext_int_id + 20 ) == 0 ) {
            sysctrl_io_config_mask( 1 << pin_num, GENERAL_PURPOSE_IO );
        }
    }
    app_gpio_port_dir_input_set( &app_gpio_inst.inst, 1 << pin_num );
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_pin_dir_set( uint8_t pin_num, uint8_t dir )
{
    if( dir ) {
        io_cfg_output( pin_num );
    } else {
        io_cfg_input( pin_num );
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t io_pin_read( uint8_t pin_num )
{
    uint32_t input = app_gpio_port_in_read( &app_gpio_inst.inst );
    return input >> pin_num & 0x1;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint8_t io_pin_out_read( uint8_t pin_num )
{
    uint32_t output = app_gpio_port_out_read( &app_gpio_inst.inst );
    return output >> pin_num & 0x1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_pin_write( uint8_t pin_num, uint8_t val )
{

    GLOBAL_INT_DISABLE();
    uint32_t output = app_gpio_port_out_read( &app_gpio_inst.inst );
    if( val ) {
        output |= 1 << pin_num;
    } else {
        output &= ~( 1 << pin_num );
    }
    app_gpio_port_out_write( &app_gpio_inst.inst, output );

    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_pin_set( uint8_t pin_num )
{
    app_gpio_port_out_set( &app_gpio_inst.inst, 1 << pin_num );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_pin_clear( uint8_t pin_num )
{
    app_gpio_port_out_clr( &app_gpio_inst.inst, 1 << pin_num );
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_pin_toggle( uint8_t pin_num )
{
    app_gpio_port_out_toggle( &app_gpio_inst.inst, 1 << pin_num );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_pin_pull_write( uint8_t pin_num, io_pull_type_t pull )
{

    GLOBAL_INT_DISABLE();
    uint32_t pull_en = sysc_awo_gpio_pe_get();
    uint32_t pull_sel = sysc_awo_gpio_ps_get();
    switch( pull ) {
        case IO_PULL_DISABLE:
            pull_en &= ~( 1 << pin_num );
            sysc_awo_gpio_pe_set( pull_en );
            break;
        case IO_PULL_UP:
            pull_en |= 1 << pin_num;
            pull_sel |= 1 << pin_num;
            sysc_awo_gpio_ps_set( pull_sel );
            sysc_awo_gpio_pe_set( pull_en );
            break;
        case IO_PULL_DOWN:
            pull_en |= 1 << pin_num;
            pull_sel &= ~( 1 << pin_num );
            sysc_awo_gpio_ps_set( pull_sel );
            sysc_awo_gpio_pe_set( pull_en );
            break;
        default:
            BX_ASSERT( 0 );
            break;
    }

    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
io_pull_type_t io_pin_pull_read( uint8_t pin_num )
{
    uint32_t pull_en = sysc_awo_gpio_pe_get();
    uint32_t pull_sel = sysc_awo_gpio_ps_get();
    if( pull_en & 1 << pin_num ) {
        if( pull_sel & 1 << pin_num ) {
            return IO_PULL_UP;
        } else {
            return IO_PULL_DOWN;
        }
    } else {
        return IO_PULL_DISABLE;
    }
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ext_set_touch_cb( void ( *cb )( void ) )
{
    //touch_cb = cb;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_ext_int_cfg( uint8_t pin_num, ext_int_mode_t mode, void ( *callback )() )
{
    GLOBAL_INT_DISABLE();
    uint8_t idx = ext_int_idx_get( pin_num );
    BX_ASSERT( idx != 0xff );
    uint32_t ext_int_cfg = sysc_awo_ext_inrp_config_get();
    //ext_int_cb[idx] = callback;
    ext_int_cfg &= ~( 0x3 << ( 2 * idx + 8 ) );
    ext_int_cfg |=  mode << ( 2 * idx + 8 );
    sysc_awo_ext_inrp_config_set( ext_int_cfg );

    GLOBAL_INT_RESTORE();
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_ext_int_en( uint8_t pin_num, bool enable )
{
    io_ext_int_ctrl( pin_num, enable, true );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_ext_int_pin_en( uint8_t pin_num, bool enable )
{
    io_ext_int_ctrl( pin_num, enable, false );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void io_ext_int_mask( uint8_t pin_num, bool unmask )
{
    GLOBAL_INT_DISABLE();
    uint8_t idx = ext_int_idx_get( pin_num );
    BX_ASSERT( idx != 0xff );
    uint32_t ext_int_cfg = sysc_awo_ext_inrp_config_get();
    if( unmask ) {
        ext_int_cfg |= 1 << idx;
    } else {
        ext_int_cfg &= ~( 1 << idx );
    }
    sysc_awo_ext_inrp_config_set( ext_int_cfg );

    GLOBAL_INT_RESTORE();
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//void EXT_INTR_IRQHandler()
//{
//    uint8_t ext_int_stat = sysc_awo_ext_inrp_value_r_getf();
//    uint8_t i;
//    for( i = 0; i < 5; ++i ) {
//        if( 1 << i & ext_int_stat ) {
//            sysc_awo_ext_inrp_clr_set( 1 << i );
//            ext_int_cb[i]();
//        }
//    }
//    if( ext_int_stat & 1 << 5 ) {
//        sysc_awo_ext_inrp_clr_set( 1 << 5 );
//        touch_cb();
//    }
//}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
