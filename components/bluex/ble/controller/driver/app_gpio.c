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
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "app_gpio.h"
#include "co_utils.h"
#include "field_manipulate.h"
#include "compiler_flag.h"
#include "ll.h"
#include "clk_gate.h"
#include "periph_mngt.h"

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
//static app_gpio_inst_t * s_gpio_inst;

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_int_cfg( app_gpio_inst_t * inst, app_gpio_int_cfg_t * int_cfg )
{
    GLOBAL_INT_DISABLE();
    REG_BIT_WR( inst->reg->GPIO_INT_BOTHEDGE, int_cfg->idx, int_cfg->both_edge );
    REG_BIT_WR( inst->reg->GPIO_INTTYPE_LEVEL, int_cfg->idx, int_cfg->edge );
    REG_BIT_WR( inst->reg->GPIO_INT_POLARITY, int_cfg->idx, int_cfg->polarity );
    REG_BIT_WR( inst->reg->GPIO_INTEN, int_cfg->idx, 1 );
    REG_BIT_WR( inst->reg->GPIO_INTMASK, int_cfg->idx, 0 );
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void prv_set_sys_stat( app_gpio_inst_t * inst, uint32_t sys_stat )
{
    switch( sys_stat ) {
        case GPIO_INIT:
            recovery_list_add( periph_domain_recovery_buf, PERIPH_DOMAIN_GPIO, &inst->inst );
            break;
        case GPIO_UNINIT:
            recovery_list_remove( periph_domain_recovery_buf, PERIPH_DOMAIN_GPIO );
            break;
        default:
            //LOG( LOG_LVL_WARN, "unexpected sys stat: %d\n", sys_stat );
            break;
    }
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t app_gpio_init( periph_inst_handle_t hdl )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
    ble_clk_gate_per_g1( BLE_PER_CLKG_SET_GPIO );
#endif
    
    NVIC_ClearPendingIRQ( GPIO_IRQn );
//    s_gpio_inst = inst;
    NVIC_EnableIRQ( GPIO_IRQn );
    
    struct co_list_hdr * hdr = co_list_pick( &inst->env.int_list );
    while( hdr ) {
        app_gpio_int_cfg_t * int_cfg = CONTAINER_OF( hdr, app_gpio_int_cfg_t, hdr );
        prv_int_cfg( inst, int_cfg );
        hdr = co_list_next( hdr );
    }
    prv_set_sys_stat( inst, GPIO_INIT );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
periph_err_t app_gpio_uninit( periph_inst_handle_t hdl )
{

    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
    ble_clk_gate_per_g1( BLE_PER_CLKG_CLR_GPIO );
#endif
    NVIC_DisableIRQ( GPIO_IRQn );
    prv_set_sys_stat( inst, GPIO_UNINIT );
    return PERIPH_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_gpio_port_dir_output_set( periph_inst_handle_t hdl, uint32_t out_mask )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    GLOBAL_INT_DISABLE();
    inst->reg->GPIO_SWPORTA_DDR |= out_mask;
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_gpio_port_dir_input_set( periph_inst_handle_t hdl, uint32_t in_mask )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    GLOBAL_INT_DISABLE();
    inst->reg->GPIO_SWPORTA_DDR &= ~in_mask;
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void app_gpio_port_dir_write( periph_inst_handle_t hdl, uint32_t dir_mask )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    GLOBAL_INT_DISABLE();
    inst->reg->GPIO_SWPORTA_DDR = dir_mask;
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint32_t app_gpio_port_dir_read( periph_inst_handle_t hdl )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    return inst->reg->GPIO_SWPORTA_DDR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint32_t app_gpio_port_in_read( periph_inst_handle_t hdl )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    return inst->reg->GPIO_EXT_PORTA;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION uint32_t app_gpio_port_out_read( periph_inst_handle_t hdl )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    return inst->reg->GPIO_SWPORTA_DR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void app_gpio_port_out_write( periph_inst_handle_t hdl, uint32_t val )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    GLOBAL_INT_DISABLE();
    inst->reg->GPIO_SWPORTA_DR = val;
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_gpio_port_out_set( periph_inst_handle_t hdl, uint32_t set_mask )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    GLOBAL_INT_DISABLE();
    inst->reg->GPIO_SWPORTA_DR |= set_mask;
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_gpio_port_out_clr( periph_inst_handle_t hdl, uint32_t clr_mask )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    GLOBAL_INT_DISABLE();
    inst->reg->GPIO_SWPORTA_DR &= ~clr_mask;
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_gpio_port_out_toggle( periph_inst_handle_t hdl, uint32_t toggle_mask )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    GLOBAL_INT_DISABLE();
    inst->reg->GPIO_SWPORTA_DR ^= toggle_mask;
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_gpio_int_enable( periph_inst_handle_t hdl, app_gpio_int_cfg_t * int_cfg )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    if( co_list_find( &inst->env.int_list, &int_cfg->hdr ) == false ) {
        co_list_push_back( &inst->env.int_list, &int_cfg->hdr );
    }
    prv_int_cfg( inst, int_cfg );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_gpio_int_disable( periph_inst_handle_t hdl, uint8_t idx )
{
    app_gpio_inst_t * inst = CONTAINER_OF( hdl, app_gpio_inst_t, inst );
    struct co_list_hdr * hdr = co_list_pick( &inst->env.int_list );
    while( hdr ) {
        app_gpio_int_cfg_t * int_cfg = CONTAINER_OF( hdr, app_gpio_int_cfg_t, hdr );
        if( int_cfg->idx == idx ) {
            GLOBAL_INT_DISABLE();
            REG_BIT_WR( inst->reg->GPIO_INTEN, idx, 0 );
            GLOBAL_INT_RESTORE();
            co_list_extract( &inst->env.int_list, hdr, 0 );
            return;
        }
        hdr = co_list_next( hdr );
    }

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
void app_gpio_isr( app_gpio_inst_t * inst )
{
    struct co_list_hdr * hdr = co_list_pick( &inst->env.int_list );
    while( hdr ) {
        app_gpio_int_cfg_t * int_cfg = CONTAINER_OF( hdr, app_gpio_int_cfg_t, hdr );
        if( REG_BIT_RD( inst->reg->GPIO_INTSTATUS, int_cfg->idx ) ) {
            inst->reg->GPIO_PORTA_EOI = 1 << int_cfg->idx;
            int_cfg->callback();
        }
        hdr = co_list_next( hdr );
    }
}
///** ---------------------------------------------------------------------------
// * @brief   :
// * @note    :
// * @param   :
// * @retval  :
//-----------------------------------------------------------------------------*/
//void GPIO_IRQHandler( void )
//{
//    app_gpio_isr( s_gpio_inst );
//}
/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

