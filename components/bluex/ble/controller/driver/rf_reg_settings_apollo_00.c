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
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void reg_config_touch( void )
{
    hwp_rf_reg->rf_reg_2.RG_OPT_TK_CKDEL_09V = 0x01;
    hwp_rf_reg->rf_reg_2.RG_OPT_TK_ADCK_09V = 0x1;
    hwp_rf_reg->rf_reg_2.RG_TK_IGEN_N_09V = 0xc;//0x7;
    hwp_rf_reg->rf_reg_2.RG_clk_ctrl = 0x6;//0x4;
    hwp_rf_reg->rf_reg_2.RG_TK_SHIELD_MODE_09V = 0x1;

    hwp_rf_reg->rf_reg_3.RG_TK_IGEN_D_09V = 0x3;
    hwp_rf_reg->rf_reg_3.RG_TK_IGEN_l2X_09V = 0x1;
    hwp_rf_reg->rf_reg_3.RG_OPT_AFE_l2X_09V = 1;
}
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
    hwp_rf_reg->rf_reg_1.VDD_PAD0 = PAD0_GPIO_VDD;
    hwp_rf_reg->rf_reg_1.VDD_PAD1 = PAD1_GPIO_VDD;
    uint8_t boot_src_sel =  ( sysc_awo_boot_mode_get() ) & 0x1;
    if( boot_src_sel ) {
        hwp_rf_reg->rf_reg_1.VDD_PAD3 = PAD3_GPIO_VDD; // uart boot, PAD2 already set
    } else {
        hwp_rf_reg->rf_reg_1.VDD_PAD2 = PAD2_GPIO_VDD; // flash boot, PAD3 already set
    }
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
void rf_setting_battery_monitor_adc( void ) // typical value 0x22D80(bit 7/8/10/11/13/17)
{
    hwp_rf_reg->rf_reg_7.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_7.ADC_CLK_DIV = 0;
    hwp_rf_reg->rf_reg_7.ADC_REFP = 0 ;
    hwp_rf_reg->rf_reg_7.ADC_REF_BUF_Current = 3 ;
    hwp_rf_reg->rf_reg_7.Reserved0 = 0 ;
    hwp_rf_reg->rf_reg_7.LV_VCM = 1 ;
    hwp_rf_reg->rf_reg_7.Force_ADC_CH_VDD_to_INT = 1;
    hwp_rf_reg->rf_reg_7.Sinlge_ended_Mode = 1 ;
    hwp_rf_reg->rf_reg_7.External_Input_Buffer = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor_Type = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor = 0;
    hwp_rf_reg->rf_reg_7.Battery_Monitor = 1;
    hwp_rf_reg->rf_reg_7.Reserved2 = 0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setting_temperature_adc( void ) // typical value 0x12580(bit 7/8/10/13/16)
{
    hwp_rf_reg->rf_reg_7.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_7.ADC_CLK_DIV = 0;
    hwp_rf_reg->rf_reg_7.ADC_REFP = 0 ;
    hwp_rf_reg->rf_reg_7.ADC_REF_BUF_Current = 3 ;
    hwp_rf_reg->rf_reg_7.Reserved0 = 0 ;
    hwp_rf_reg->rf_reg_7.LV_VCM = 1 ;
    hwp_rf_reg->rf_reg_7.Force_ADC_CH_VDD_to_INT = 1;
    hwp_rf_reg->rf_reg_7.Sinlge_ended_Mode = 1 ;
    hwp_rf_reg->rf_reg_7.External_Input_Buffer = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor_Type = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor = 1;
    hwp_rf_reg->rf_reg_7.Battery_Monitor = 0;
    hwp_rf_reg->rf_reg_7.Reserved2 = 0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setting_differential_mode_adc( void ) // typical value 0x1980(bit 7/8/11/12)
{
    hwp_rf_reg->rf_reg_7.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_7.ADC_CLK_DIV = 0;
    hwp_rf_reg->rf_reg_7.ADC_REFP = 0 ;
    hwp_rf_reg->rf_reg_7.ADC_REF_BUF_Current = 3 ;
    hwp_rf_reg->rf_reg_7.Reserved0 = 0 ;
    hwp_rf_reg->rf_reg_7.LV_VCM = 0 ;
    hwp_rf_reg->rf_reg_7.Force_ADC_CH_VDD_to_INT = 1;
    hwp_rf_reg->rf_reg_7.ADC_SINGLE_DR = 1 ;
    hwp_rf_reg->rf_reg_7.Sinlge_ended_Mode = 0 ;
    hwp_rf_reg->rf_reg_7.External_Input_Buffer = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor_Type = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor = 0;
    hwp_rf_reg->rf_reg_7.Battery_Monitor = 0;
    hwp_rf_reg->rf_reg_7.Reserved2 = 0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setting_single_mode_adc( void ) // typical value 0x3980(bit 7/8/11/12/13)
{
    hwp_rf_reg->rf_reg_7.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_7.ADC_CLK_DIV = 0;
    hwp_rf_reg->rf_reg_7.ADC_REFP = 0 ;
    hwp_rf_reg->rf_reg_7.ADC_REF_BUF_Current = 3 ;
    hwp_rf_reg->rf_reg_7.Reserved0 = 0 ;
    hwp_rf_reg->rf_reg_7.LV_VCM = 0 ;
    hwp_rf_reg->rf_reg_7.Force_ADC_CH_VDD_to_INT = 1;
    hwp_rf_reg->rf_reg_7.ADC_SINGLE_DR = 1 ;
    hwp_rf_reg->rf_reg_7.Sinlge_ended_Mode = 1 ;
    hwp_rf_reg->rf_reg_7.External_Input_Buffer = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor_Type = 0;
    hwp_rf_reg->rf_reg_7.Temperature_Sensor = 0;
    hwp_rf_reg->rf_reg_7.Battery_Monitor = 0;
    hwp_rf_reg->rf_reg_7.Reserved2 = 0;
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

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_low_battery_config( void )
{
    reg_set_xtal_current( 0, 0, 0, 0 ); // set xtal current to max
    hwp_rf_reg->rf_reg_9.RX_Filter_Bandwidth_1mbps = 2;

    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 4;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 5;
    hwp_rf_reg->rf_reg_e.DM_Sync_LP = 1;

    hwp_rf_reg->rf_reg_f.C2_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.C3_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.Charge_Pump_Current_RX_1Mbps = 0;
}


#if (defined BX_BATTERY_MONITOR) && (BX_BATTERY_MONITOR == 1)
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_reg_adjust_bat( uint16_t bat_volt )
{
    if( bat_volt > BYPASS_VOLTAGE ) {
        hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 0;
        hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 0;
        hwp_rf_reg->rf_reg_6.LV_32K = 0;
    } else {
        hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 1;
        hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 1;
        hwp_rf_reg->rf_reg_6.LV_32K = 1;
    }
    hwp_rf_reg->rf_reg_4.VSLP = vslp_calc( bat_volt );
    hwp_rf_reg->rf_reg_4.FTSV = ftsv_calc( bat_volt );
}
#endif /* (defined BX_BATTERY_MONITOR) && (BX_BATTERY_MONITOR == 1) */

#if (defined BX_TEMP_SENSOR) && (BX_TEMP_SENSOR == 1)
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_reg_adjust_temp( int16_t temp )
{

}
#endif /* (defined BX_TEMP_SENSOR) && (BX_TEMP_SENSOR == 1) */

#if RF_PARAM == 0
#if RF_TX_POWER == 1 
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_negative2dbm( void )
{
    hwp_rf_reg->rf_reg_c.PA_Ramping_Up_Time_3V = 4;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Up_Down_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Down_Time = 0;
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
    hwp_rf_reg->rf_reg_c.PA0_BIAS2_EN_3V = 1;
    
    hwp_rf_reg->rf_reg_c.PA_8dBm_EN_3V = 0;
    hwp_rf_reg->rf_reg_c.Ramping_Manual = 2;
    hwp_rf_reg->rf_reg_c.R1_TX_2Mbps = 3;

    hwp_rf_reg->rf_reg_d.R1_TX_1Mbps = 0;
    hwp_rf_reg->rf_reg_d.R2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C3_TX_1Mbps = 6;
    
    hwp_rf_reg->rf_reg_d.VSEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;
    hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;
}
#elif RF_TX_POWER == 0
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_8dbm( void )
{
    hwp_rf_reg->rf_reg_c.PA_Ramping_Up_Time_3V = 4;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Up_Down_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Down_Time = 0;
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;

    hwp_rf_reg->rf_reg_c.VSEL_8PA_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_WCTL_3V = 3;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL2_3V = 7;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_FINE_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_COARSE_3V = 7;
    hwp_rf_reg->rf_reg_c.PA_8dBm_EN_3V = 1;
    hwp_rf_reg->rf_reg_c.Ramping_Manual = 2;
    hwp_rf_reg->rf_reg_c.R1_TX_2Mbps = 3;

    hwp_rf_reg->rf_reg_d.R1_TX_1Mbps = 0;
    hwp_rf_reg->rf_reg_d.R2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C3_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_COARSE = 7;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_FINE = 7;
    hwp_rf_reg->rf_reg_d.DTS_VCTL = 2;
}
#else
#error "Error in TX POWER Configuration!!!"
#endif /* RF_TX_POWER == 1 */
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_reg_settings_init_mp( void )
{
    hwp_rf_reg->rf_reg_0.freq_pulling = 1;
    reg_set_xtal_current_normal();
    reg_pad_voltage_init();
    
#if (defined(CPU_LDO_BYPASS)&&(CPU_LDO_BYPASS==1))
    hwp_rf_reg->rf_reg_1.Bypass_SRAM = 1;
    hwp_rf_reg->rf_reg_1.Bypass_TOP = 1;
    hwp_rf_reg->rf_reg_1. Bypass_CPU = 1;
    hwp_rf_reg->rf_reg_1.Bypass_BLE = 1;
    hwp_rf_reg->rf_reg_1.Bypass_PER = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V1;
#else
    hwp_rf_reg->rf_reg_1.Bypass_SRAM = 0;
    hwp_rf_reg->rf_reg_1.Bypass_TOP = 0;
    hwp_rf_reg->rf_reg_1. Bypass_CPU = 0;
    hwp_rf_reg->rf_reg_1.Bypass_BLE = 0;
    hwp_rf_reg->rf_reg_1.Bypass_PER = 0;
    if( AHB_CLK <= 32000000 ) {
        hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V1;
        hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V1;
    } else {
        hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V4;
        hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V4;
    }
#endif /* (defined(CPU_LDO_BYPASS)&&(CPU_LDO_BYPASS==1)) */
    hwp_rf_reg->rf_reg_1.DCDC_Bypass_Voltage_Option = 1;
    hwp_rf_reg->rf_reg_1.Charger_EN = 1;

#if ((VDD_AWO_SLEEP_MILLIVOLT >= 800) && (VDD_AWO_SLEEP_MILLIVOLT <= 950) && !(VDD_AWO_SLEEP_MILLIVOLT % 50))
    hwp_rf_reg->rf_reg_4.VDD_AWO_Sleep  = ( 0x3 - ( VDD_AWO_SLEEP_MILLIVOLT - 800 ) / 50 );
#else
#error "Error VDD_AWO_SLEEP_MILLIVOLT!!!"
#endif /* ((VDD_AWO_SLEEP_MILLIVOLT >= 800) && (VDD_AWO_SLEEP_MILLIVOLT <= 950) && !(VDD_AWO_SLEEP_MILLIVOLT % 50)) */

#if (defined(LDO_3V1_OUTPUT_SLEEP_RET)&&(LDO_3V1_OUTPUT_SLEEP_RET==1))
    hwp_rf_reg->rf_reg_4.RET_33 = 1;
#else
    hwp_rf_reg->rf_reg_4.RET_33 = 0;
#endif /* (defined(LDO_3V1_OUTPUT_SLEEP_RET)&&(LDO_3V1_OUTPUT_SLEEP_RET==1)) */

#if (defined(LDO_1V8_OUTPUT_SLEEP_RET)&&(LDO_1V8_OUTPUT_SLEEP_RET==1))
    hwp_rf_reg->rf_reg_4.RET_18 = 1;
#else
    hwp_rf_reg->rf_reg_4.RET_18 = 0;
#endif /* (defined(LDO_1V8_OUTPUT_SLEEP_RET)&&(LDO_1V8_OUTPUT_SLEEP_RET==1)) */

#if (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1))
    hwp_rf_reg->rf_reg_4.CREF = 1;
#else
    hwp_rf_reg->rf_reg_4.CREF = 0;
#endif /* (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1)) */

    hwp_rf_reg->rf_reg_4.VSLP = vslp_calc( VBAT_MILLIVOLT );
    hwp_rf_reg->rf_reg_4.FTSV = ftsv_calc( VBAT_MILLIVOLT );
    
#if (defined(DIG_VOLTAGE_CTRL_BY_RF_REG)&&(DIG_VOLTAGE_CTRL_BY_RF_REG==1))
    hwp_rf_reg->rf_reg_4.Dig_Voltage_Manual = AHB_CLK <= 32000000 ? 1 : 0;
#else
    hwp_rf_reg->rf_reg_4.Dig_Voltage_Manual = 0;
#endif /* (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1)) */

    hwp_rf_reg->rf_reg_4.VBYP = 3;
    hwp_rf_reg->rf_reg_4.DCDC_PWM = 4;
    hwp_rf_reg->rf_reg_4.EN_BG_AWO = 1;
    hwp_rf_reg->rf_reg_4.Sleep_Regulator = 1;
    
#if (VBAT_MILLIVOLT > BYPASS_VOLTAGE)
    hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 0;
    hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 0;
    hwp_rf_reg->rf_reg_6.LV_32K = 0;
#else
    hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 1;
    hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 1;
    hwp_rf_reg->rf_reg_6.LV_32K = 1;
#endif /* (VBAT_MILLIVOLT > BYPASS_VOLTAGE) */

    hwp_rf_reg->rf_reg_6.Slow_Clock_Current = 4 ;

    hwp_rf_reg->rf_reg_8.ADC_REF = 4;
    hwp_rf_reg->rf_reg_8.RSSI_Curve_Shift = 0;
    hwp_rf_reg->rf_reg_8.RSSI_Slope_Shift = 3;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_TX_2mbps = 3;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_TX_1mbps = 4;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_RX_2mbps = 3;
    hwp_rf_reg->rf_reg_8.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_REFN = 3;
    hwp_rf_reg->rf_reg_8.ADC_BUF_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_REF_BUF_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_BUF_BYPASS = 0;

    hwp_rf_reg->rf_reg_9.RX_Analog_Output_Enable = 0;
    hwp_rf_reg->rf_reg_9.RX_LA_Tune = 0;
    hwp_rf_reg->rf_reg_9.RX_HPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.Bypass_LPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.RX_LPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.RX_Filter_Manual_Bandwidth = 8;
    hwp_rf_reg->rf_reg_9.RXF_EN = 1;
    hwp_rf_reg->rf_reg_9.RX_Filter_Current = 2;
    hwp_rf_reg->rf_reg_9.RX_Mixer_Filter_Bias_Voltage = 1;
    hwp_rf_reg->rf_reg_9.RX_Mixer_LO_Bias_Voltage = 2;
    hwp_rf_reg->rf_reg_9.RSSI_Manual = 0;
    hwp_rf_reg->rf_reg_9.RX_MUX = 7;
    hwp_rf_reg->rf_reg_9.RX_Filter_Bandwidth_2mbps = 3;
    hwp_rf_reg->rf_reg_9.RX_Filter_Bandwidth_1mbps = 1;

    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 0;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 0;
    hwp_rf_reg->rf_reg_a.LNA_I_Control_1 = 2;
    hwp_rf_reg->rf_reg_a.LNA_I_Control_2 = 3;
    hwp_rf_reg->rf_reg_a.LNA_CA = 4;
    hwp_rf_reg->rf_reg_a.LNA_V_SEL = 0;
    hwp_rf_reg->rf_reg_a.LNA_I_SEL = 0;
    hwp_rf_reg->rf_reg_a.LNA_Gain_Control = 0;
    hwp_rf_reg->rf_reg_a.R1_RX_2Mbps = 1;
    hwp_rf_reg->rf_reg_a.R2_RX_2Mbps = 6;
    hwp_rf_reg->rf_reg_a.C2_RX_2Mbps = 6;
    hwp_rf_reg->rf_reg_a.C3_RX_2Mbps = 6;

    hwp_rf_reg->rf_reg_b.VDD_RF1_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF2_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_CP_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_A_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_BUF_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 2;
    hwp_rf_reg->rf_reg_b.VDD_CP_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    hwp_rf_reg->rf_reg_b.VDD_A_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.R2_TX_2Mbps = 6;
    hwp_rf_reg->rf_reg_b.C2_TX_2Mbps = 6;
    hwp_rf_reg->rf_reg_b.C3_TX_2Mbps = 6;

    hwp_rf_reg->rf_reg_c.PA_Ramping_Up_Time_3V = 4;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Up_Down_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Down_Time = 0;
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
    hwp_rf_reg->rf_reg_c.PA0_BIAS2_EN_3V = 1;
    hwp_rf_reg->rf_reg_c.VSEL_8PA_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_WCTL_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL2_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_FINE_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_COARSE_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_8dBm_EN_3V = 0;
    hwp_rf_reg->rf_reg_c.Ramping_Manual = 2;
    hwp_rf_reg->rf_reg_c.R1_TX_2Mbps = 3;

    hwp_rf_reg->rf_reg_d.R1_TX_1Mbps = 0;
    hwp_rf_reg->rf_reg_d.R2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C3_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_COARSE = 0;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_FINE = 0;
    hwp_rf_reg->rf_reg_d.DTS_VCTL = 0;
    hwp_rf_reg->rf_reg_d.VSEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;
    hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;

    hwp_rf_reg->rf_reg_e.VCO_Current_for_TX = 1;
    hwp_rf_reg->rf_reg_e.VCO_Current_for_RX = 1;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 3;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 1;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 4;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 4;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.DM_Sync_LP = 0;
    hwp_rf_reg->rf_reg_e.DM_Sync_HP = 1;
    hwp_rf_reg->rf_reg_e.Prescaler_D2S_Current = 0;
    hwp_rf_reg->rf_reg_e.Prescaler_Dummy = 1;
    hwp_rf_reg->rf_reg_e.TX_Dummy = 0 ;

    hwp_rf_reg->rf_reg_f.R1_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.R2_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.C2_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.C3_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.Charge_Pump_Disable = 0;
    hwp_rf_reg->rf_reg_f.Charge_Pump_Current_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.Cal_Start_Manual = 0;
    hwp_rf_reg->rf_reg_f.LOCK_en = 0;
    hwp_rf_reg->rf_reg_f.VCO_Band = 0;
    hwp_rf_reg->rf_reg_f.MVCO = 0 ;
    hwp_rf_reg->rf_reg_f.VCO_Off_Control = 0;
    hwp_rf_reg->rf_reg_f.Lock_Detector_Reference = 2;
    hwp_rf_reg->rf_reg_f.Prescaler_inv_Sync = 0;
    hwp_rf_reg->rf_reg_f.Xtal_32MHz_inv_Sync = 0;

#if RF_TX_POWER == 1
    rf_setPA_negative2dbm();
#elif RF_TX_POWER == 0
    rf_setPA_8dbm();
#else
#endif /* RF_TX_POWER == 1 */
}
#elif RF_PARAM == 1
_Static_assert( MAIN_CLOCK == 32000000, "Error in RF configuration!!!" );
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_negative2dbm_dcdc_on( void )
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 4;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 0;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 0;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 4;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 1;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 0;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_reg_settings_init_mp()
{
    hwp_rf_reg->rf_reg_0.freq_pulling = 0;
    reg_set_xtal_current_normal();
    reg_pad_voltage_init();
    
#if (defined(CPU_LDO_BYPASS)&&(CPU_LDO_BYPASS==1))
    hwp_rf_reg->rf_reg_1.Bypass_SRAM = 1;
    hwp_rf_reg->rf_reg_1.Bypass_TOP = 1;
    hwp_rf_reg->rf_reg_1. Bypass_CPU = 1;
    hwp_rf_reg->rf_reg_1.Bypass_BLE = 1;
    hwp_rf_reg->rf_reg_1.Bypass_PER = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V2;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V2;
#else
    hwp_rf_reg->rf_reg_1.Bypass_SRAM = 0;
    hwp_rf_reg->rf_reg_1.Bypass_TOP = 0;
    hwp_rf_reg->rf_reg_1. Bypass_CPU = 0;
    hwp_rf_reg->rf_reg_1.Bypass_BLE = 0;
    hwp_rf_reg->rf_reg_1.Bypass_PER = 0;
    if( AHB_CLK <= 32000000 ) {
        hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V2;
        hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V2;
    } else {
        hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V2;
        hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V2;
    }
#endif /* (defined(CPU_LDO_BYPASS)&&(CPU_LDO_BYPASS==1)) */

    hwp_rf_reg->rf_reg_1.DCDC_Bypass_Voltage_Option = 1;
    hwp_rf_reg->rf_reg_1.Charger_EN = 1;

#if ((VDD_AWO_SLEEP_MILLIVOLT >= 800) && (VDD_AWO_SLEEP_MILLIVOLT <= 950)\
        && !(VDD_AWO_SLEEP_MILLIVOLT % 50))
    hwp_rf_reg->rf_reg_4.VDD_AWO_Sleep  = ( 0x3 - ( VDD_AWO_SLEEP_MILLIVOLT - 800 ) / 50 );
#else
#error "Error VDD_AWO_SLEEP_MILLIVOLT!!!"
#endif /* (defined(CPU_LDO_BYPASS)&&(CPU_LDO_BYPASS==1)) */

#if (defined(LDO_3V1_OUTPUT_SLEEP_RET)&&(LDO_3V1_OUTPUT_SLEEP_RET==1))
    hwp_rf_reg->rf_reg_4.RET_33 = 1;
#else
    hwp_rf_reg->rf_reg_4.RET_33 = 0;
#endif /* (defined(LDO_3V1_OUTPUT_SLEEP_RET)&&(LDO_3V1_OUTPUT_SLEEP_RET==1)) */

#if (defined(LDO_1V8_OUTPUT_SLEEP_RET)&&(LDO_1V8_OUTPUT_SLEEP_RET==1))
    hwp_rf_reg->rf_reg_4.RET_18 = 1;
#else
    hwp_rf_reg->rf_reg_4.RET_18 = 0;
#endif /* (defined(LDO_1V8_OUTPUT_SLEEP_RET)&&(LDO_1V8_OUTPUT_SLEEP_RET==1)) */

#if (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1))
    hwp_rf_reg->rf_reg_4.CREF = 1;
#else
    hwp_rf_reg->rf_reg_4.CREF = 0;
#endif /* (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1)) */

    hwp_rf_reg->rf_reg_4.VSLP = vslp_calc( VBAT_MILLIVOLT );
    hwp_rf_reg->rf_reg_4.FTSV = ftsv_calc( VBAT_MILLIVOLT );
    
#if (defined(DIG_VOLTAGE_CTRL_BY_RF_REG)&&(DIG_VOLTAGE_CTRL_BY_RF_REG==1))
    hwp_rf_reg->rf_reg_4.Dig_Voltage_Manual = AHB_CLK <= 32000000 ? 1 : 0;
#else
    hwp_rf_reg->rf_reg_4.Dig_Voltage_Manual = 0;
#endif /* (defined(DIG_VOLTAGE_CTRL_BY_RF_REG)&&(DIG_VOLTAGE_CTRL_BY_RF_REG==1)) */

    hwp_rf_reg->rf_reg_4.VBYP = 1;
    hwp_rf_reg->rf_reg_4.DCDC_PWM = 4;
    hwp_rf_reg->rf_reg_4.EN_BG_AWO = 1;
    hwp_rf_reg->rf_reg_4.Sleep_Regulator = 1;
    
#if (VBAT_MILLIVOLT > BYPASS_VOLTAGE)
    hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 0;
    hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 0;
    hwp_rf_reg->rf_reg_6.LV_32K = 0;
#else
    hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 1;
    hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 1;
    hwp_rf_reg->rf_reg_6.LV_32K = 1;
#endif /* (VBAT_MILLIVOLT > BYPASS_VOLTAGE) */

    hwp_rf_reg->rf_reg_6.Slow_Clock_Current = 4 ;

    hwp_rf_reg->rf_reg_8.ADC_REF = 4;
    hwp_rf_reg->rf_reg_8.RSSI_Curve_Shift = 0;
    hwp_rf_reg->rf_reg_8.RSSI_Slope_Shift = 3;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_TX_2mbps = 4;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_TX_1mbps = 7;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_RX_2mbps = 3;
    hwp_rf_reg->rf_reg_8.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_REFN = 3;
    hwp_rf_reg->rf_reg_8.ADC_BUF_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_REF_BUF_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_BUF_BYPASS = 0;

    hwp_rf_reg->rf_reg_9.RX_Analog_Output_Enable = 0;
    hwp_rf_reg->rf_reg_9.RX_LA_Tune = 0;
    hwp_rf_reg->rf_reg_9.RX_HPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.Bypass_LPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.RX_LPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.RX_Filter_Manual_Bandwidth = 8;
    hwp_rf_reg->rf_reg_9.RXF_EN = 1;
    hwp_rf_reg->rf_reg_9.RX_Filter_Current = 2;
    hwp_rf_reg->rf_reg_9.RX_Mixer_Filter_Bias_Voltage = 1;
    hwp_rf_reg->rf_reg_9.RX_Mixer_LO_Bias_Voltage = 2;
    hwp_rf_reg->rf_reg_9.RSSI_Manual = 0;
    hwp_rf_reg->rf_reg_9.RX_MUX = 7;
    hwp_rf_reg->rf_reg_9.RX_Filter_Bandwidth_2mbps = 3;
    hwp_rf_reg->rf_reg_9.RX_Filter_Bandwidth_1mbps = 1;

    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 0;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 0;
    hwp_rf_reg->rf_reg_a.LNA_I_Control_1 = 2;
    hwp_rf_reg->rf_reg_a.LNA_I_Control_2 = 3;
    hwp_rf_reg->rf_reg_a.LNA_CA = 4;
    hwp_rf_reg->rf_reg_a.LNA_V_SEL = 0;
    hwp_rf_reg->rf_reg_a.LNA_I_SEL = 0;
    hwp_rf_reg->rf_reg_a.LNA_Gain_Control = 0;
    hwp_rf_reg->rf_reg_a.R1_RX_2Mbps = 1;
    hwp_rf_reg->rf_reg_a.R2_RX_2Mbps = 6;
    hwp_rf_reg->rf_reg_a.C2_RX_2Mbps = 6;
    hwp_rf_reg->rf_reg_a.C3_RX_2Mbps = 6;

    hwp_rf_reg->rf_reg_b.VDD_RF1_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF2_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_CP_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_A_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_BUF_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 1; // special configuration

    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;

    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0; // special configuration

    hwp_rf_reg->rf_reg_b.VDD_CP_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    hwp_rf_reg->rf_reg_b.VDD_A_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.R2_TX_2Mbps = 6;
    hwp_rf_reg->rf_reg_b.C2_TX_2Mbps = 6;
    hwp_rf_reg->rf_reg_b.C3_TX_2Mbps = 6;

    hwp_rf_reg->rf_reg_c.PA_Ramping_Up_Time_3V = 4;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Up_Down_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Down_Time = 0;
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
    hwp_rf_reg->rf_reg_c.PA0_BIAS2_EN_3V = 1;
    hwp_rf_reg->rf_reg_c.VSEL_8PA_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_WCTL_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL2_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_FINE_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_COARSE_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_8dBm_EN_3V = 0;
    hwp_rf_reg->rf_reg_c.Ramping_Manual = 2;
    hwp_rf_reg->rf_reg_c.R1_TX_2Mbps = 3;

    hwp_rf_reg->rf_reg_d.R1_TX_1Mbps = 0;
    hwp_rf_reg->rf_reg_d.R2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C3_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_COARSE = 0;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_FINE = 0;
    hwp_rf_reg->rf_reg_d.DTS_VCTL = 0;
    hwp_rf_reg->rf_reg_d.VSEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;
    hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;

    hwp_rf_reg->rf_reg_e.VCO_Current_for_TX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Current_for_RX = 1;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;

    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 0; 
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 1; 
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 4; 

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.DM_Sync_LP = 0;
    hwp_rf_reg->rf_reg_e.DM_Sync_HP = 1;
    hwp_rf_reg->rf_reg_e.Prescaler_D2S_Current = 0;
    hwp_rf_reg->rf_reg_e.Prescaler_Dummy = 1;
    hwp_rf_reg->rf_reg_e.TX_Dummy = 0 ;

    hwp_rf_reg->rf_reg_f.R1_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.R2_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.C2_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.C3_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.Charge_Pump_Disable = 0;
    hwp_rf_reg->rf_reg_f.Charge_Pump_Current_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.Cal_Start_Manual = 0;
    hwp_rf_reg->rf_reg_f.LOCK_en = 0;
    hwp_rf_reg->rf_reg_f.VCO_Band = 0;
    hwp_rf_reg->rf_reg_f.MVCO = 0 ;
    hwp_rf_reg->rf_reg_f.VCO_Off_Control = 0;
    hwp_rf_reg->rf_reg_f.Lock_Detector_Reference = 2;
    hwp_rf_reg->rf_reg_f.Prescaler_inv_Sync = 0;
    hwp_rf_reg->rf_reg_f.Xtal_32MHz_inv_Sync = 0;

    rf_setPA_negative2dbm_dcdc_on();
}

#elif RF_PARAM == 2
_Static_assert( MAIN_CLOCK == 32000000, "Error in RF configuration!!!" );
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_negative2dbm_dcdc_on( void )
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 4;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 0;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 0;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_reg_settings_init_mp( void )
{
    hwp_rf_reg->rf_reg_0.freq_pulling = 0;
    reg_set_xtal_current_normal();
    reg_pad_voltage_init();
    
#if (defined(CPU_LDO_BYPASS)&&(CPU_LDO_BYPASS==1))
    hwp_rf_reg->rf_reg_1.Bypass_SRAM = 1;
    hwp_rf_reg->rf_reg_1.Bypass_TOP = 1;
    hwp_rf_reg->rf_reg_1. Bypass_CPU = 1;
    hwp_rf_reg->rf_reg_1.Bypass_BLE = 1;
    hwp_rf_reg->rf_reg_1.Bypass_PER = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V2;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V2;
#else
    hwp_rf_reg->rf_reg_1.Bypass_SRAM = 0;
    hwp_rf_reg->rf_reg_1.Bypass_TOP = 0;
    hwp_rf_reg->rf_reg_1. Bypass_CPU = 0;
    hwp_rf_reg->rf_reg_1.Bypass_BLE = 0;
    hwp_rf_reg->rf_reg_1.Bypass_PER = 0;
    if( AHB_CLK <= 32000000 ) {
        hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V2;
        hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V2;
    } else {
        hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V2;
        hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V2;
    }
#endif /* (defined(CPU_LDO_BYPASS)&&(CPU_LDO_BYPASS==1)) */

    hwp_rf_reg->rf_reg_1.DCDC_Bypass_Voltage_Option = 1;
    hwp_rf_reg->rf_reg_1.Charger_EN = 1;

#if ((VDD_AWO_SLEEP_MILLIVOLT >= 800) && (VDD_AWO_SLEEP_MILLIVOLT <= 950) && !(VDD_AWO_SLEEP_MILLIVOLT % 50))
    hwp_rf_reg->rf_reg_4.VDD_AWO_Sleep  = ( 0x3 - ( VDD_AWO_SLEEP_MILLIVOLT - 800 ) / 50 );
#else
#error "Error VDD_AWO_SLEEP_MILLIVOLT!!!"
#endif /* ((VDD_AWO_SLEEP_MILLIVOLT >= 800) && (VDD_AWO_SLEEP_MILLIVOLT <= 950) && !(VDD_AWO_SLEEP_MILLIVOLT % 50)) */

#if (defined(LDO_3V1_OUTPUT_SLEEP_RET)&&(LDO_3V1_OUTPUT_SLEEP_RET==1))
    hwp_rf_reg->rf_reg_4.RET_33 = 1;
#else
    hwp_rf_reg->rf_reg_4.RET_33 = 0;
#endif /* (defined(LDO_3V1_OUTPUT_SLEEP_RET)&&(LDO_3V1_OUTPUT_SLEEP_RET==1)) */

#if (defined(LDO_1V8_OUTPUT_SLEEP_RET)&&(LDO_1V8_OUTPUT_SLEEP_RET==1))
    hwp_rf_reg->rf_reg_4.RET_18 = 1;
#else
    hwp_rf_reg->rf_reg_4.RET_18 = 0;
#endif /* (defined(LDO_1V8_OUTPUT_SLEEP_RET)&&(LDO_1V8_OUTPUT_SLEEP_RET==1)) */

#if (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1))
    hwp_rf_reg->rf_reg_4.CREF = 1;
#else
    hwp_rf_reg->rf_reg_4.CREF = 0;
#endif /* (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1)) */

    hwp_rf_reg->rf_reg_4.VSLP = vslp_calc( VBAT_MILLIVOLT );
    hwp_rf_reg->rf_reg_4.FTSV = ftsv_calc( VBAT_MILLIVOLT );
#if (defined(DIG_VOLTAGE_CTRL_BY_RF_REG)&&(DIG_VOLTAGE_CTRL_BY_RF_REG==1))
    hwp_rf_reg->rf_reg_4.Dig_Voltage_Manual = AHB_CLK <= 32000000 ? 1 : 0;
#else
    hwp_rf_reg->rf_reg_4.Dig_Voltage_Manual = 0;
#endif /* (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1)) */

    hwp_rf_reg->rf_reg_4.VBYP = 1;
    hwp_rf_reg->rf_reg_4.DCDC_PWM = 4;
    hwp_rf_reg->rf_reg_4.EN_BG_AWO = 1;
    hwp_rf_reg->rf_reg_4.Sleep_Regulator = 1;
#if (VBAT_MILLIVOLT > BYPASS_VOLTAGE)
    hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 0;
    hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 0;
    hwp_rf_reg->rf_reg_6.LV_32K = 0;
#else
    hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 1;
    hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 1;
    hwp_rf_reg->rf_reg_6.LV_32K = 1;
#endif /* (VBAT_MILLIVOLT > BYPASS_VOLTAGE) */

    hwp_rf_reg->rf_reg_6.Slow_Clock_Current = 4 ;

    hwp_rf_reg->rf_reg_8.ADC_REF = 4;
    hwp_rf_reg->rf_reg_8.RSSI_Curve_Shift = 0;
    hwp_rf_reg->rf_reg_8.RSSI_Slope_Shift = 3;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_TX_2mbps = 4;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_TX_1mbps = 7;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_RX_2mbps = 3;
    hwp_rf_reg->rf_reg_8.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_REFN = 3;
    hwp_rf_reg->rf_reg_8.ADC_BUF_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_REF_BUF_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_BUF_BYPASS = 0;

    hwp_rf_reg->rf_reg_9.RX_Analog_Output_Enable = 0;
    hwp_rf_reg->rf_reg_9.RX_LA_Tune = 0;
    hwp_rf_reg->rf_reg_9.RX_HPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.Bypass_LPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.RX_LPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.RX_Filter_Manual_Bandwidth = 8;
    hwp_rf_reg->rf_reg_9.RXF_EN = 1;
    hwp_rf_reg->rf_reg_9.RX_Filter_Current = 2;
    hwp_rf_reg->rf_reg_9.RX_Mixer_Filter_Bias_Voltage = 1;
    hwp_rf_reg->rf_reg_9.RX_Mixer_LO_Bias_Voltage = 2;
    hwp_rf_reg->rf_reg_9.RSSI_Manual = 0;
    hwp_rf_reg->rf_reg_9.RX_MUX = 7;
    hwp_rf_reg->rf_reg_9.RX_Filter_Bandwidth_2mbps = 3;
    hwp_rf_reg->rf_reg_9.RX_Filter_Bandwidth_1mbps = 1;

    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 0;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 0;
    hwp_rf_reg->rf_reg_a.LNA_I_Control_1 = 2;
    hwp_rf_reg->rf_reg_a.LNA_I_Control_2 = 3;
    hwp_rf_reg->rf_reg_a.LNA_CA = 4;
    hwp_rf_reg->rf_reg_a.LNA_V_SEL = 0;
    hwp_rf_reg->rf_reg_a.LNA_I_SEL = 0;
    hwp_rf_reg->rf_reg_a.LNA_Gain_Control = 0;
    hwp_rf_reg->rf_reg_a.R1_RX_2Mbps = 1;
    hwp_rf_reg->rf_reg_a.R2_RX_2Mbps = 6;
    hwp_rf_reg->rf_reg_a.C2_RX_2Mbps = 6;
    hwp_rf_reg->rf_reg_a.C3_RX_2Mbps = 6;

    hwp_rf_reg->rf_reg_b.VDD_RF1_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF2_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_CP_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_A_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_BUF_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0; // special configuration

    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;

    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0; // special configuration

    hwp_rf_reg->rf_reg_b.VDD_CP_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    hwp_rf_reg->rf_reg_b.VDD_A_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.R2_TX_2Mbps = 6;
    hwp_rf_reg->rf_reg_b.C2_TX_2Mbps = 6;
    hwp_rf_reg->rf_reg_b.C3_TX_2Mbps = 6;

    hwp_rf_reg->rf_reg_c.PA_Ramping_Up_Time_3V = 4;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Up_Down_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Down_Time = 0;
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
    hwp_rf_reg->rf_reg_c.PA0_BIAS2_EN_3V = 1;
    hwp_rf_reg->rf_reg_c.VSEL_8PA_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_WCTL_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL2_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_FINE_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_COARSE_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_8dBm_EN_3V = 0;
    hwp_rf_reg->rf_reg_c.Ramping_Manual = 2;
    hwp_rf_reg->rf_reg_c.R1_TX_2Mbps = 3;

    hwp_rf_reg->rf_reg_d.R1_TX_1Mbps = 0;
    hwp_rf_reg->rf_reg_d.R2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C3_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_COARSE = 0;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_FINE = 0;
    hwp_rf_reg->rf_reg_d.DTS_VCTL = 0;
    hwp_rf_reg->rf_reg_d.VSEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;
    hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;

    hwp_rf_reg->rf_reg_e.VCO_Current_for_TX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Current_for_RX = 1;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;

    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 0; // special configuration
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 1; // special configuration
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 4; // special configuration

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.DM_Sync_LP = 0;
    hwp_rf_reg->rf_reg_e.DM_Sync_HP = 1;
    hwp_rf_reg->rf_reg_e.Prescaler_D2S_Current = 0;
    hwp_rf_reg->rf_reg_e.Prescaler_Dummy = 1;
    hwp_rf_reg->rf_reg_e.TX_Dummy = 0 ;

    hwp_rf_reg->rf_reg_f.R1_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.R2_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.C2_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.C3_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.Charge_Pump_Disable = 0;
    hwp_rf_reg->rf_reg_f.Charge_Pump_Current_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.Cal_Start_Manual = 0;
    hwp_rf_reg->rf_reg_f.LOCK_en = 0;
    hwp_rf_reg->rf_reg_f.VCO_Band = 0;
    hwp_rf_reg->rf_reg_f.MVCO = 0 ;
    hwp_rf_reg->rf_reg_f.VCO_Off_Control = 0;
    hwp_rf_reg->rf_reg_f.Lock_Detector_Reference = 2;
    hwp_rf_reg->rf_reg_f.Prescaler_inv_Sync = 0;
    hwp_rf_reg->rf_reg_f.Xtal_32MHz_inv_Sync = 0;

    rf_setPA_negative2dbm_dcdc_on();
}

#elif RF_PARAM == 3
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_2dbm_dcdc_on( void )
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 0;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 0;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    #if(AHB_CLK<= 32000000 )
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
    #else
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
    #endif
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 1;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 7;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 7;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 0;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_2dbm_dcdc_off_3V3( void )
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 1;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_2dbm_dcdc_off_1V8( void )
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 7;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 7;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_0dbm_dcdc_on( void )
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 0;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 0;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    #if(AHB_CLK<= 32000000 )
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
    #else
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
    #endif
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 5;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_negative2dbm_dcdc_on( void )
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    #if(AHB_CLK<= 32000000 )
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
    #else
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
    #endif
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_negative10dbm_dcdc_on(void)
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;
        
    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
#if MAIN_CLOCK == 32000000
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
#else
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
#endif

    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
    
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_negative20dbm_dcdc_on(void)
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;
        
    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
#if MAIN_CLOCK == 32000000
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
#else
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
#endif
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
    
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 0;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_negative30dbm_dcdc_on(void)
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;
        
    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
#if MAIN_CLOCK == 32000000
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
#else
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
#endif
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
    
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 4;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 0;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_4dbm_dcdc_off_3V3( void )
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_8dbm_dcdc_off_3V3( void )
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 3;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 7;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 7;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_8dbm_dcdc_on_3V3(void)
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 0;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 0;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;

    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 3;
#if MAIN_CLOCK == 32000000
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
#else
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
#endif
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 1;

    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 7;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 7;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_setPA_negative2dbm_dcdc_on_3V3(void)
{
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 0;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 0;

    hwp_rf_reg->rf_reg_a.LNA_CA = 3;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 1;
    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 4;
        
    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
#if MAIN_CLOCK == 32000000
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
#else    
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 0;
#endif
    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
    
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;

    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 0;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2;

}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void rf_reg_settings_init_mp( void )
{
    hwp_rf_reg->rf_reg_0.freq_pulling = 1;
    reg_set_xtal_current_normal();
    reg_pad_voltage_init();
    
#if (defined(CPU_LDO_BYPASS)&&(CPU_LDO_BYPASS==1))
    hwp_rf_reg->rf_reg_1.Bypass_SRAM = 1;
    hwp_rf_reg->rf_reg_1.Bypass_TOP = 1;
    hwp_rf_reg->rf_reg_1. Bypass_CPU = 1;
    hwp_rf_reg->rf_reg_1.Bypass_BLE = 1;
    hwp_rf_reg->rf_reg_1.Bypass_PER = 1;
    hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V2;
    hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V2;
#else
    hwp_rf_reg->rf_reg_1.Bypass_SRAM = 0;
    hwp_rf_reg->rf_reg_1.Bypass_TOP = 0;
    hwp_rf_reg->rf_reg_1. Bypass_CPU = 0;
    hwp_rf_reg->rf_reg_1.Bypass_BLE = 0;
    hwp_rf_reg->rf_reg_1.Bypass_PER = 0;
    if( AHB_CLK <= 32000000 ) {
        hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V2;
        hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V2;
    } else {
        hwp_rf_reg->rf_reg_1.DCDC_Output_TX = DCDC_OUTPUT_1V2;
        hwp_rf_reg->rf_reg_1.DCDC_Output_RX = DCDC_OUTPUT_1V2;
    }
#endif /* (defined(CPU_LDO_BYPASS)&&(CPU_LDO_BYPASS==1)) */
    
    hwp_rf_reg->rf_reg_1.DCDC_Bypass_Voltage_Option = 1;
    hwp_rf_reg->rf_reg_1.Charger_EN = 1;

#if ((VDD_AWO_SLEEP_MILLIVOLT >= 800) && (VDD_AWO_SLEEP_MILLIVOLT <= 950) && !(VDD_AWO_SLEEP_MILLIVOLT % 50))
    hwp_rf_reg->rf_reg_4.VDD_AWO_Sleep  = ( 0x3 - ( VDD_AWO_SLEEP_MILLIVOLT - 800 ) / 50 );
#else
#error "Error VDD_AWO_SLEEP_MILLIVOLT!!!"
#endif /* ((VDD_AWO_SLEEP_MILLIVOLT >= 800) && (VDD_AWO_SLEEP_MILLIVOLT <= 950) && !(VDD_AWO_SLEEP_MILLIVOLT % 50)) */

#if (defined(LDO_3V1_OUTPUT_SLEEP_RET)&&(LDO_3V1_OUTPUT_SLEEP_RET==1))
    hwp_rf_reg->rf_reg_4.RET_33 = 1;
#else
    hwp_rf_reg->rf_reg_4.RET_33 = 0;
#endif /* (defined(LDO_3V1_OUTPUT_SLEEP_RET)&&(LDO_3V1_OUTPUT_SLEEP_RET==1)) */
    
#if (defined(LDO_1V8_OUTPUT_SLEEP_RET)&&(LDO_1V8_OUTPUT_SLEEP_RET==1))
    hwp_rf_reg->rf_reg_4.RET_18 = 1;
#else
    hwp_rf_reg->rf_reg_4.RET_18 = 0;
#endif /* (defined(LDO_1V8_OUTPUT_SLEEP_RET)&&(LDO_1V8_OUTPUT_SLEEP_RET==1)) */

#if (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1))
    hwp_rf_reg->rf_reg_4.CREF = 1;
#else
    hwp_rf_reg->rf_reg_4.CREF = 0;
#endif /* (defined(VDD_1V8_SLEEP_LDO1)&&(VDD_1V8_SLEEP_LDO1==1)) */

    hwp_rf_reg->rf_reg_4.VSLP = vslp_calc( VBAT_MILLIVOLT );
    hwp_rf_reg->rf_reg_4.FTSV = ftsv_calc( VBAT_MILLIVOLT );
    
#if (defined(DIG_VOLTAGE_CTRL_BY_RF_REG)&&(DIG_VOLTAGE_CTRL_BY_RF_REG==1))
    hwp_rf_reg->rf_reg_4.Dig_Voltage_Manual = AHB_CLK <= 32000000 ? 1 : 0;
#else
    hwp_rf_reg->rf_reg_4.Dig_Voltage_Manual = 0;
#endif /* (defined(DIG_VOLTAGE_CTRL_BY_RF_REG)&&(DIG_VOLTAGE_CTRL_BY_RF_REG==1)) */

    hwp_rf_reg->rf_reg_4.VBYP = 1;
    hwp_rf_reg->rf_reg_4.DCDC_PWM = 4;
    hwp_rf_reg->rf_reg_4.EN_BG_AWO = 1;
    hwp_rf_reg->rf_reg_4.Sleep_Regulator = 1;
    
#if (VBAT_MILLIVOLT > BYPASS_VOLTAGE)
    hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 0;
    hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 0;
    hwp_rf_reg->rf_reg_6.LV_32K = 0;
#else
    hwp_rf_reg->rf_reg_4.VDD_3V_1_Tr_enhance = 1;
    hwp_rf_reg->rf_reg_6.VDD_3V_2_Tr_enhance = 1;
    hwp_rf_reg->rf_reg_6.LV_32K = 1;
#endif /* (VBAT_MILLIVOLT > BYPASS_VOLTAGE) */

    hwp_rf_reg->rf_reg_6.Slow_Clock_Current = 4 ;

    hwp_rf_reg->rf_reg_8.ADC_REF = 4;
    hwp_rf_reg->rf_reg_8.RSSI_Curve_Shift = 0;
    hwp_rf_reg->rf_reg_8.RSSI_Slope_Shift = 3;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_TX_2mbps = 4;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_TX_1mbps = 7;
    hwp_rf_reg->rf_reg_8.Charge_Pump_Current_RX_2mbps = 3;
    hwp_rf_reg->rf_reg_8.ADC_COMP_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_REFN = 3;
    hwp_rf_reg->rf_reg_8.ADC_BUF_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_REF_BUF_Current = 0;
    hwp_rf_reg->rf_reg_8.ADC_BUF_BYPASS = 0;

    hwp_rf_reg->rf_reg_9.RX_Analog_Output_Enable = 0;
    hwp_rf_reg->rf_reg_9.RX_LA_Tune = 0;
    hwp_rf_reg->rf_reg_9.RX_HPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.Bypass_LPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.RX_LPF_Bandwidth = 0;
    hwp_rf_reg->rf_reg_9.RX_Filter_Manual_Bandwidth = 8;
    hwp_rf_reg->rf_reg_9.RXF_EN = 1;
    hwp_rf_reg->rf_reg_9.RX_Filter_Current = 2;
    hwp_rf_reg->rf_reg_9.RX_Mixer_Filter_Bias_Voltage = 1;
    hwp_rf_reg->rf_reg_9.RX_Mixer_LO_Bias_Voltage = 2;
    hwp_rf_reg->rf_reg_9.RSSI_Manual = 0;
    hwp_rf_reg->rf_reg_9.RX_MUX = 7;
    hwp_rf_reg->rf_reg_9.RX_Filter_Bandwidth_2mbps = 3;
    hwp_rf_reg->rf_reg_9.RX_Filter_Bandwidth_1mbps = 1;

    hwp_rf_reg->rf_reg_a.LNA_V_Contro = 0;
    hwp_rf_reg->rf_reg_a.LNA_V_Control_EN = 0;
    hwp_rf_reg->rf_reg_a.LNA_I_Control_1 = 2;
    hwp_rf_reg->rf_reg_a.LNA_I_Control_2 = 3;
    hwp_rf_reg->rf_reg_a.LNA_CA = 4;
    hwp_rf_reg->rf_reg_a.LNA_V_SEL = 0;
    hwp_rf_reg->rf_reg_a.LNA_I_SEL = 0;
    hwp_rf_reg->rf_reg_a.LNA_Gain_Control = 0;
    hwp_rf_reg->rf_reg_a.R1_RX_2Mbps = 1;
    hwp_rf_reg->rf_reg_a.R2_RX_2Mbps = 6;
    hwp_rf_reg->rf_reg_a.C2_RX_2Mbps = 6;
    hwp_rf_reg->rf_reg_a.C3_RX_2Mbps = 6;

    hwp_rf_reg->rf_reg_b.VDD_RF1_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF2_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_VCO_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_CP_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_A_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_BUF_Reg_Bypass = 0;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Reg_Bypass = 0;

    hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage = 0; // special configuration

    hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1; // special configuration
    hwp_rf_reg->rf_reg_b.VDD_CP_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
    hwp_rf_reg->rf_reg_b.VDD_A_Regulator_Voltage = 1;
    hwp_rf_reg->rf_reg_b.VDD_BUF_Regulator_Voltage = 0;
    hwp_rf_reg->rf_reg_b.R2_TX_2Mbps = 6;
    hwp_rf_reg->rf_reg_b.C2_TX_2Mbps = 6;
    hwp_rf_reg->rf_reg_b.C3_TX_2Mbps = 6;

    hwp_rf_reg->rf_reg_c.PA_Ramping_Up_Time_3V = 4;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Up_Down_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_Ramp_Down_Time = 0;
    hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
    hwp_rf_reg->rf_reg_c.PA0_BIAS2_EN_3V = 1;
    hwp_rf_reg->rf_reg_c.VSEL_8PA_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_WCTL_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL2_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_FINE_3V = 0;
    hwp_rf_reg->rf_reg_c.DRV_VCTRL1_COARSE_3V = 0;
    hwp_rf_reg->rf_reg_c.PA_8dBm_EN_3V = 0;
    hwp_rf_reg->rf_reg_c.Ramping_Manual = 2;
    hwp_rf_reg->rf_reg_c.R1_TX_2Mbps = 3;

    hwp_rf_reg->rf_reg_d.R1_TX_1Mbps = 0;
    hwp_rf_reg->rf_reg_d.R2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C2_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.C3_TX_1Mbps = 6;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_COARSE = 0;
    hwp_rf_reg->rf_reg_d.DTS_ICTL_FINE = 0;
    hwp_rf_reg->rf_reg_d.DTS_VCTL = 0;
    hwp_rf_reg->rf_reg_d.VSEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;
    hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
    hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
    hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;

    hwp_rf_reg->rf_reg_e.VCO_Current_for_TX = 2;
    hwp_rf_reg->rf_reg_e.VCO_Current_for_RX = 1;
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX = 6;

    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX = 2; // special configuration
    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX = 2; // special configuration
    hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_RX = 6; // special configuration

    hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
    hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
    hwp_rf_reg->rf_reg_e.DM_Sync_LP = 0;
    hwp_rf_reg->rf_reg_e.DM_Sync_HP = 1;
    hwp_rf_reg->rf_reg_e.Prescaler_D2S_Current = 0;
    hwp_rf_reg->rf_reg_e.Prescaler_Dummy = 1;
    hwp_rf_reg->rf_reg_e.TX_Dummy = 0 ;

    hwp_rf_reg->rf_reg_f.R1_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.R2_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.C2_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.C3_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.Charge_Pump_Disable = 0;
    hwp_rf_reg->rf_reg_f.Charge_Pump_Current_RX_1Mbps = 0;
    hwp_rf_reg->rf_reg_f.Cal_Start_Manual = 0;
    hwp_rf_reg->rf_reg_f.LOCK_en = 0;
    hwp_rf_reg->rf_reg_f.VCO_Band = 0;
    hwp_rf_reg->rf_reg_f.MVCO = 0 ;
    hwp_rf_reg->rf_reg_f.VCO_Off_Control = 0;
    hwp_rf_reg->rf_reg_f.Lock_Detector_Reference = 2;
    hwp_rf_reg->rf_reg_f.Prescaler_inv_Sync = 0;
    hwp_rf_reg->rf_reg_f.Xtal_32MHz_inv_Sync = 0;

#if RF_TX_POWER == 1 //RF_TX_POWER_2DBM_DCDC_ON
    rf_setPA_2dbm_dcdc_on();
#elif RF_TX_POWER == 2 //RF_TX_POWER_2DBM_DCDC_OFF_3V3
    rf_setPA_2dbm_dcdc_off_3V3();
#elif RF_TX_POWER == 3 //RF_TX_POWER_2DBM_DCDC_OFF_1V8
    rf_setPA_2dbm_dcdc_off_1V8();
#elif RF_TX_POWER == 4 //RF_TX_POWER_0DBM_DCDC_ON
    rf_setPA_0dbm_dcdc_on();
#elif RF_TX_POWER == 5 //RF_TX_POWER_N2DBM_DCDC_ON
    rf_setPA_negative2dbm_dcdc_on();
#elif RF_TX_POWER == 6 //RF_TX_POWER_4DBM_DCDC_OFF_3V3
    rf_setPA_4dbm_dcdc_off_3V3();
#elif RF_TX_POWER == 7 //RF_TX_POWER_8DBM_DCDC_OFF_3V3
    rf_setPA_8dbm_dcdc_off_3V3();
#elif RF_TX_POWER == 8 //RF_TX_POWER_8DBM_DCDC_ON_3V3
    rf_setPA_8dbm_dcdc_on_3V3();
#elif RF_TX_POWER == 9 //RF_TX_POWER_N10DBM_DCDC_ON
    rf_setPA_negative10dbm_dcdc_on();
#elif RF_TX_POWER == 10 //RF_TX_POWER_N20DBM_DCDC_ON
    rf_setPA_negative20dbm_dcdc_on();
#elif RF_TX_POWER == 11 //RF_TX_POWER_N30DBM_DCDC_ON
    rf_setPA_negative30dbm_dcdc_on();
#elif RF_TX_POWER == 12 //RF_TX_POWER_N2DBM_DCDC_ON_3V3
    rf_setPA_negative2dbm_dcdc_on_3V3();
#else
#error "Error in TX POWER Configuration!!!"
#endif
}
#endif /* RF_PARAM == 0 */

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

