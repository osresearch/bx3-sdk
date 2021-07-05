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
#define __RAM_CODE__
#define LOG_TAG "ARCH INIT"
/* includes ------------------------------------------------------------------*/

#include "bx_config.h"
#include "arch.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "plf.h"
#include "rwip.h"
#include "modem.h"
#include "boot.h"
#include "nvds.h"
#include "bx_dbg.h"
#include "rc_calib.h"
#include "patch.h"
#include "rst_gen.h"
#include "pshare.h"
#include "clk_gate.h"
#include "sysctrl.h"
#include "em_map.h"
#include "rf_reg_settings.h"
#include "app_dmac_wrapper.h"
#include "app_qspi_wrapper.h"
#include "app_hwecc_wrapper.h"
#include "rtc.h"
#include "swint.h"
#include "io_ctrl.h"
#include "sys_sleep.h"
#include "flash_cache.h"
#if (CFG_FREERTOS_SUPPORT==1)
#include "os_bridge.h"
#endif
#include "compiler_flag.h"
#include "arch_init.h"
#include "true_random.h"
#include "bxfs.h"
#include "ota_image.h"
#include "compiler_flag.h"
#include "bx_log.h"
#include "log.h"
#include "reg_sysc_awo_apollo_00.h"
#include "flash_wrapper.h"
#include "bx_sdk3_config.h"
#include "app_adc_utils.h"
#include "rf_temp_adjust.h"

/* private define ------------------------------------------------------------*/
#define XIP_REGION_MPU_NUM          7
#define XIP_REGION_BASE             0x800000
#define XIP_REGION_SIZE_POWER       23
#define RAM_BASE                    0x00100000
#define ROM_DATA_BASE               0x0012f5cc
#define RAM_LIMIT                   0x00130000

/* private typedef -----------------------------------------------------------*/
#if !defined(__BOOT_RAM__)
#define BOOT_TUNNEL __attribute__((section("boot_tunnel"), zero_init))
#else
#define BOOT_TUNNEL
#endif

/* private variables ---------------------------------------------------------*/
uint32_t mark_count = 0;
struct unloaded_area_tag * unloaded_area;
flash_info_t flash_info BOOT_TUNNEL;
app_info_t app_info BOOT_TUNNEL;

/* exported variables --------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void unloaded_area_init( void )
{
    unloaded_area = ( struct unloaded_area_tag * )RAM_UNLOADED_BASE;
    unloaded_area->error = RESET_NO_ERROR;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void irq_priority()
{
    NVIC_SetPriority( SVCall_IRQn, 1 );
    NVIC_SetPriority( WDT_IRQn, 2 );
    NVIC_SetPriority( BLE_LP_IRQn, 0 );
    NVIC_SetPriority( BLE_MAC_IRQn, 0 );
#if (SYSTICK_USED == 0)
    NVIC_SetPriority( RTC_IRQn, 0 );
#endif
    NVIC_SetPriority( EXT_INTR_IRQn, 2 );
    NVIC_SetPriority( ECC_IRQn, 2 );
    NVIC_SetPriority( DMAC_IRQn, 2 );
    NVIC_SetPriority( QSPI_IRQn, 2 );
    NVIC_SetPriority( SPIM0_IRQn, 2 );
    NVIC_SetPriority( SPIM1_IRQn, 2 );
    NVIC_SetPriority( SPIS_IRQn, 2 );
    NVIC_SetPriority( UART0_IRQn, 2 );
    NVIC_SetPriority( UART1_IRQn, 2 );
    NVIC_SetPriority( IIC0_IRQn, 2 );
    NVIC_SetPriority( IIC1_IRQn, 2 );
    NVIC_SetPriority( GPIO_IRQn, 2 );
    NVIC_SetPriority( TIMER_IRQn, 2 );
    NVIC_SetPriority( SFT_IRQn, 2 );
    NVIC_SetPriority( PGSPY_IRQn, 2 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
NOINLINE N_XIP_SECTION static void cache_restart()
{
    cache_disable();
    app_qspi_param_init_wrapper( &flash_info.multi_read_param );
    app_qspi_init_wrapper();
    cache_config();
    cache_enable();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_rtc_init_wrapper()
{
    srst_awo( RTC_SRST_AWO );
    ble_clk_gate_awo( BLE_AWO_CLKG_SET_RTC );
    NVIC_ClearPendingIRQ( RTC_IRQn );
    NVIC_EnableIRQ( RTC_IRQn );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void sys_setup()
{
    rc_calib_start();
    rf_reg_settings_init_mp();
    sysctrl_set_ahb_apb_blemac_clk();
    rc_calib_end( true );

    generate_random_seed();
#if (RC32K_USED == 0)
    sysctrl_32k_clk_init();
#endif
    sysctrl_awo_init();
    irq_priority();
    NVIC_ClearPendingIRQ( BLE_LP_IRQn );
    NVIC_ClearPendingIRQ( BLE_MAC_IRQn );
    NVIC_EnableIRQ( BLE_LP_IRQn );
    NVIC_EnableIRQ( BLE_MAC_IRQn );
    SWINT_SYS_INT_CLR();
    SWINT_SYS_INT_EN();

#if ( BX_USE_WDT > 0 )
    BX_CPU->CLKG1 |= CPU_CLKG1_SET_WDT;
    BX_MODIFY_REG( BX_WDT->CTRL, WDT_CTRL_RST_PULSE_LEN, WDT_CTRL_RST_PULSE_LEN_T_4_PCLK_CYCLES );
    BX_MODIFY_REG( BX_WDT->TR, WDT_TR_PERIOD, 1600 );
    BX_SET_BIT( BX_WDT->CTRL, WDT_CTRL_EN );
#endif

#if (SYSTICK_USED == 0)
    app_rtc_init_wrapper();
#else
    NVIC_ClearPendingIRQ( SysTick_IRQn );
    NVIC_EnableIRQ( SysTick_IRQn );
#endif
    cache_restart();
    app_dmac_init_wrapper();
    app_hwecc_init_wrapper();

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
#if defined(CFG_APP)
static void dummy_eif_read( uint8_t * bufptr, uint32_t size, rwip_eif_callback callback, void * dummy )
{
    //LOG_V( "in dummy_eif_read\n" );
}

static void dummy_eif_write( uint8_t * bufptr, uint32_t size, rwip_eif_callback callback, void * dummy )
{
    //LOG_V( "in dummy_eif_write\n" );
}

static void dummy_eif_on(void)
{
    //LOG_V( "in dummy_eif_on\n" );
}

static bool dummy_eif_off(void)
{
    //LOG_V( "in dummy_eif_off\n" );
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static const struct rwip_eif_api * dummy_eif_get()
{
    static const struct rwip_eif_api dummy_eif = {
        dummy_eif_read,
        dummy_eif_write,
        dummy_eif_on,
        dummy_eif_off,
    };
    return &dummy_eif;
}
#endif
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void mpu_enable_for_xip_region()
{
    MPU->RNR = XIP_REGION_MPU_NUM;
    MPU->RBAR = XIP_REGION_BASE;
    MPU->RASR = _VAL2FLD( MPU_RASR_XN, 1 ) | _VAL2FLD( MPU_RASR_AP, 0 ) |
                _VAL2FLD( MPU_RASR_C, 1 ) | _VAL2FLD( MPU_RASR_B, 0 ) | _VAL2FLD( MPU_RASR_S, 0 ) |
                _VAL2FLD( MPU_RASR_SRD, 0 ) | _VAL2FLD( MPU_RASR_SIZE, (XIP_REGION_SIZE_POWER - 1) ) |
                _VAL2FLD( MPU_RASR_ENABLE, 1 );
    MPU->CTRL = _VAL2FLD( MPU_CTRL_PRIVDEFENA, 1 ) | _VAL2FLD( MPU_CTRL_ENABLE, 1 );
    __DSB();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void mpu_disable_for_xip_region()
{
    MPU->CTRL = _VAL2FLD( MPU_CTRL_ENABLE, 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void cache_config()
{
#if (FLASH_XIP == 1)
    flash_cache_config( 0 );
#endif
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void cache_enable()
{
#if (FLASH_XIP == 1)
    flash_cache_enable();
    mpu_disable_for_xip_region();
#endif
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void cache_disable()
{
#if (FLASH_XIP == 1)
    mpu_enable_for_xip_region();
    flash_cache_disable();
#endif
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void soc_init()
{
    srst_cpu( WDT_SRST_CPU );

    set_scb_vtor(RAM_BASE);
    
    sys_setup();

    // Initialize unloaded RAM area
#if (!(defined(BX_VERF)&&(BX_VERF==1)))
    unloaded_area_init();
#endif

    patch_init();
    modem_init();

    app_adc_util_init();
	#if (defined BX_TEMP_SENSOR) && (BX_TEMP_SENSOR == 1) 
	init_rf_temp_adjust();
	#endif
    modem_dev_calib_in_main();

    bxfs_init( app_info.data_base );
    nvds_init();
    
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
const struct rwip_eif_api * rwip_eif_get( uint8_t type )
{
    const struct rwip_eif_api * ret = NULL;
    switch( type ) {
        case RWIP_EIF_AHI: {
#if (CFG_FREERTOS_SUPPORT==1)
            ret = os_get_eif_api();             //os_msg_api;
#elif (defined(CFG_APP))
            ret = dummy_eif_get();
#else
            ret = serial_eif_get();
#endif
        }
        break;
        default: {
            ASSERT_INFO( 0, type, 0 );
        }
        break;
    }
    return ret;
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/
/** ---------------------------------------------------------------------------
 * @brief   :   in arch.h
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void platform_reset( uint32_t error )
{
    GLOBAL_INT_STOP();

    unloaded_area->error = error;

    if( error == RESET_AND_LOAD_FW || error == RESET_TO_ROM ) {
    } else {
#if HW_BX_VERSION == 00
        srst_awo( CHIP_SRST_AWO );
#elif HW_BX_VERSION == 01
        sysc_awo_sft_rst_set( SRST_ALL_CLR );
#else
#error ERROR: ERROR to define HW_BX_VERSION
#endif
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :   in arch.h
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
uint16_t get_stack_usage( void )
{
    return STACK_TOP - __get_MSP();
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
XIP_SECTION void SystemInit( uint32_t param0, uint32_t param1, uint32_t param2, uint32_t param3 )
{
    if( param3 != BOOTINIT_FLAG ) { //indicate bootram has already run.

    } else {
        if( ( param0 == 0 ) && ( param1 == 0 ) && ( param2 == 0 ) ) { //just for ram boot run
            memset( ( void * )&app_info, 0, sizeof( app_info_t ) );
            memset( ( void * )&flash_info, 0, sizeof( flash_info_t ) );
        } else { //normal flash boot run
            app_info = *( app_info_t * )param0;
            flash_info = *( flash_info_t * )param1;
        }
    }
#ifndef ALL_IN_RAM
    memset( ( void * )EM_BASE_ADDR, 0, ( uint32_t )IMAGE_BOOT_PARAMS_BASE - EM_BASE_ADDR );
    // ROM Code RW ZI Section Initialization
    memset( ( void * )ROM_DATA_BASE, 0, RAM_LIMIT - ROM_DATA_BASE );
#endif
}

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
