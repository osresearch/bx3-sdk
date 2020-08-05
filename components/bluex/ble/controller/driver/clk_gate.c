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
#include "clk_gate.h"
#include "reg_sysc_cpu.h"
#include "reg_sysc_cpu_apollo_00.h"
#include "reg_sysc_awo_apollo_00.h"
#include "reg_sysc_per_apollo_00.h"
#include "bx_dbg.h"
#include "compiler_flag.h"
#include "ll.h"

/* private define ------------------------------------------------------------*/
#define CLK_MASK_CLR    0xaaaaaaaa
#define CLK_MASK_SET    (~CLK_MASK_CLR)

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

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
N_XIP_SECTION void ble_clk_gate_clr_all_clk()
{
    GLOBAL_INT_DISABLE();
    sysc_cpu_clkg0_set( CLK_MASK_CLR );
    sysc_cpu_clkg1_set( CLK_MASK_CLR );
    sysc_per_clkg0_set( CLK_MASK_CLR );
    sysc_per_clkg1_set( CLK_MASK_CLR );
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void ble_clk_gate_awo( uint32_t map )
{
    GLOBAL_INT_DISABLE();
    sysc_awo_reg_awo_clkg_en_set( map );
    if( map & CLK_MASK_CLR ) {
        while( sysc_awo_reg_awo_clkg_en_get()&map );
    } else if( map & CLK_MASK_SET ) {
        while( ( ~ sysc_awo_reg_awo_clkg_en_get() )&map );
    } else {
        BX_ASSERT( 0 );
    }
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_clk_gate_per_g0( uint32_t map )
{
    GLOBAL_INT_DISABLE();
    sysc_per_clkg0_set( map );
    if( map & CLK_MASK_CLR ) {        //clr
        while( ( sysc_per_clkg0_get() & map ) );
    } else if( map & CLK_MASK_SET ) { //set
        while( ( ~ sysc_per_clkg0_get() ) & map );
    } else {
        BX_ASSERT( 0 );
    }
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_clk_gate_per_g1( uint32_t map )
{
    GLOBAL_INT_DISABLE();
    sysc_per_clkg1_set( map );
    if( map & CLK_MASK_CLR ) {        //clr
        while( ( sysc_per_clkg1_get() & map ) );
    } else if( map & CLK_MASK_SET ) { //set
        while( ( ~ sysc_per_clkg1_get() ) & map );
    } else {
        BX_ASSERT( 0 );
    }
    GLOBAL_INT_RESTORE();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void ble_clk_gate_cpu_g0( uint32_t map )
{
    GLOBAL_INT_DISABLE();
    sysc_cpu_clkg0_set( map );
    if( map & CLK_MASK_CLR ) {        //clr
        while( ( sysc_cpu_clkg0_get() & map ) );
    } else if( map & CLK_MASK_SET ) { //set
        while( ( ~ sysc_cpu_clkg0_get() ) & map );
    } else {
        BX_ASSERT( 0 );
    }
    GLOBAL_INT_RESTORE();

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void ble_clk_gate_cpu_g1( uint32_t map )
{
    GLOBAL_INT_DISABLE();
    sysc_cpu_clkg1_set( map );
    if( map & CLK_MASK_CLR ) {
        while( ( sysc_cpu_clkg1_get() & map ) );
    } else if( map & CLK_MASK_SET ) {
        while( ( ~ sysc_cpu_clkg1_get() ) & map );
    } else {
        BX_ASSERT( 0 );
    }
    GLOBAL_INT_RESTORE();

}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
