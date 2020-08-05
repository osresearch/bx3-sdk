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
#include "bx_dbg.h"
#include "pshare.h"
#include "reg_sysc_cpu.h"
#include "reg_sysc_cpu_apollo_00.h"
#include "compiler_flag.h"
#include "ll.h"
#include "log.h"

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
static void function_io_select_set( uint8_t func_io_num, uint8_t idx )
{
    uint32_t mem_offset = func_io_num / 8;
    uint32_t bit_offset = ( func_io_num % 8 ) * 4;
    uint32_t bit_mask = 0xF << bit_offset;
    uint32_t bit_mask_rev = ~bit_mask;
    uint32_t * mem_addr = ( uint32_t * )( ( uint32_t )&SYSC_CPU->FIO_SEL0 + mem_offset * 4 );
    uint32_t val = 0;

    //read
    val = *mem_addr;
    //clear
    val &= bit_mask_rev;
    //set
    val |= idx << bit_offset;
    //write
    *mem_addr = val;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :   set the function of function I/O
 * @note    :
 * @param   :   [in]io_num  choose from FUNC_IO_0 to FUNC_IO_21. Find definition in pshare.h
                [in]idx     choose from IO_UART0_TXD to IO_PWM_4. Find definition in pshare.h
                [in]en      enable the function io setting or not.
 * @retval  :
-----------------------------------------------------------------------------*/
void pshare_funcio_set( uint8_t io_num, uint8_t idx, uint8_t en )
{
    uint32_t enable_map;
    BX_ASSERT( ( io_num <= 21 ) );
    BX_ASSERT( ( idx <= 14 ) );
    BX_ASSERT( ( en == ENABLE ) || ( en == DISABLE ) );

    GLOBAL_INT_DISABLE();
    enable_map = sysc_cpu_func_io_en_r_getf();
    if( en == DISABLE ) {
        enable_map &= ( ~( 1 << io_num ) );
        sysc_cpu_func_io_en_r_setf( enable_map );
    } else {
        function_io_select_set( io_num, idx );
        enable_map |= ( 1 << io_num );
        sysc_cpu_func_io_en_r_setf( enable_map );
    }
    GLOBAL_INT_RESTORE();
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void pshare_funcio_disable_all()
{
    sysc_cpu_func_io_en_r_setf( 0 );

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void pshare_reset_to_gpio()
{
    sysc_cpu_func_io_en_set( 0 );
    sysc_cpu_pin_share_en_set( 0x1800 );
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


