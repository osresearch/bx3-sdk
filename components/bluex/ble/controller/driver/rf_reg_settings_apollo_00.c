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
#include "plf.h"
#include "bx_dbg.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_awo_apollo_00.h"
#include "rf_reg_typedef.h"
#include "rf_reg_settings.h"
#include "compiler_flag.h"
#include "rf_power_set.h"

/* private define ------------------------------------------------------------*/

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
N_XIP_SECTION void reg_set_xtal_current( uint32_t iboost_current, uint32_t xtal_current, uint32_t vboost, uint32_t iboost )
{
    hwp_rf_reg->rf_reg_0.xtal_iboost = iboost;
    hwp_rf_reg->rf_reg_0.xtal_vboost = vboost;
    hwp_rf_reg->rf_reg_0.xtal_current = xtal_current;
    hwp_rf_reg->rf_reg_0.iboost_current = iboost_current;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void reg_set_xtal_current_startup()
{
    reg_set_xtal_current( 0, 0, 0, 0 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
N_XIP_SECTION void reg_pll_enable( uint8_t en )
{
    hwp_rf_reg->rf_reg_0.pll_pdb = en;
	if(en == 1)
	{
		BX_DELAY_US(60);
	}
    hwp_rf_reg->rf_reg_0.pll_resb = en;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void reg_pad_voltage_init()
{
    uint8_t flash_voltage = (sysc_awo_boot_mode_get()) & 0x2;
    if( flash_voltage )
    {
        hwp_rf_reg->rf_reg_1.VDD_PAD3 = VDD_3V;
    }
    else
    {
        hwp_rf_reg->rf_reg_1.VDD_PAD3 = VDD_1V8;
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void reg_set_xtal_current_below_temp0()
{
    reg_set_xtal_current( 0, 1, 1, 1 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void reg_set_xtal_current_normal()
{
    reg_set_xtal_current( 0, 1, 1, 1 );
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void reg_set_pll( uint32_t freq )
{
    hwp_rf_reg->rf_reg_0.s_cp1 = 5;
    hwp_rf_reg->rf_reg_0.s_cp2 = 3;
    hwp_rf_reg->rf_reg_0.s_fr = 4;
    hwp_rf_reg->rf_reg_0.s_kvco = 3;
    hwp_rf_reg->rf_reg_0.s_pll = 2;
    hwp_rf_reg->rf_reg_0.s_md = freq;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool reg_pll_lock()
{
    return hwp_rf_reg->rf_reg_ro.PLL_96MHz_Lock ? true : false;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void reg_wait_pll_stable()
{
    uint8_t i;
    //wait a few cycle
    for( i = 0; i < 5; i++ ) {
        __NOP();
    }
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
    while( reg_pll_lock() == false );
#endif
}

#if (defined BX_BATTERY_MONITOR) && (BX_BATTERY_MONITOR == 1)
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint32_t vslp_calc( uint32_t bat_volt )
{
    uint32_t vslp = 0;
#if (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1))
    if( bat_volt > 3700 ) {
        vslp = 7;
    } else if( bat_volt > 1800 ) {
        vslp = 0xf;
    } else {
        BX_ASSERT( 0 );
    }
#else
    if( bat_volt > 3700 ) {
        vslp = 7;
    } else if( bat_volt > 3100 ) {
        vslp = 0xf;
    } else if( bat_volt > 2600 ) {
        vslp = 0xb;
    } else if( bat_volt > 2300 ) {
        vslp = 9;
    } else if( bat_volt > 1800 ) {
        vslp = 8;
    } else {
        BX_ASSERT( 0 );
    }
#endif
    return vslp;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint32_t ftsv_calc( uint32_t bat_volt )
{
    uint32_t ftsv = 0;
    if( bat_volt > 4150 ) {
        ftsv = 5;
    } else if( bat_volt > 4050 ) {
        ftsv = 6;
    } else if( bat_volt > 3950 ) {
        ftsv = 4;
    } else if( bat_volt > 3750 ) {
        ftsv = 0;
    } else if( bat_volt > 3580 ) {
        ftsv = 7;
    } else if( bat_volt > 3350 ) {
        ftsv = 5;
    } else if( bat_volt > 1850 ) {
        ftsv = 0;
    } else {
        BX_ASSERT( 0 );
    }
    return ftsv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_reg_adjust_bat( uint16_t bat_volt )
{
	//LOG_RAW("bat_volt = %d\r\n", bat_volt);
    if( bat_volt > BYPASS_VOLTAGE ) {
        hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 0;
        hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 0;
    } else {
        hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 1;
        hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 1;
    }
    hwp_rf_reg->rf_reg_4.VSLP = vslp_calc( bat_volt );
    hwp_rf_reg->rf_reg_4.FTSV = ftsv_calc( bat_volt );
}
#endif /* (defined BX_BATTERY_MONITOR) && (BX_BATTERY_MONITOR == 1) */
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_reg_settings_init_mp(void)
{
	rf_power_setting();
	reg_pad_voltage_init();
}

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

