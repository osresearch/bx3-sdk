/**
  ******************************************************************************
  * @file   :   .h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RF_REG_TYPEDEF_H__
#define __RF_REG_TYPEDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

typedef struct
{
   uint32_t s_kvco : 3,
            s_md : 3,
            s_pll : 2,
            s_fr : 3,
            s_cp2 : 3,
            s_cp1 : 3,
            pll_resb : 1,
            pll_pdb : 1,
            freq_pulling: 3,
            xtal_iboost: 1,
            xtal_vboost: 1,
            rc_32m_osc: 4,
            xtal_current: 2,
            iboost_current : 2;
}rf_reg_0_t;

typedef struct
{
  uint32_t  DCDC_Output_TX: 2,
            DCDC_Output_RX: 2,
            DCDC_Bypass: 1,
            DCDC_Bypass_Voltage_Option: 1,
            Charger_Current: 4,
            Charger_Auto_Shutoff: 1,
            Charger_EN: 1,
            Reserved: 1,
            VDD_PAD0: 1,
            VDD_PAD1: 1,
            VDD_PAD2: 1,
            VDD_PAD3: 1,
            Power_Test_SRAM: 1,
            Power_Test_AWO: 1,
            Power_Test_TOP: 1,
            Mode_SRAM: 1,
            Mode_AWO: 1,
            Mode_TOP: 1,
            Mode_CPU: 1,
            Mode_BLE: 1,
            Mode_PER: 1,
            Bypass_SRAM: 1,
            Bypass_AWO: 1,
            Bypass_TOP: 1,
            Bypass_CPU: 1,
            Bypass_BLE: 1,
            Bypass_PER: 1;
}rf_reg_1_t;

typedef struct
{
   uint32_t RG_TK_INIT_MODE_09V : 2,
            RG_OPT_TK_CYCLE_09V : 1,
            RG_OPT_TK_CYINV_09V : 1,
            RG_OPT_TK_CKDEL_09V : 2,
            RG_OPT_TK_ADCK_09V: 1,
            RG_TK_IGEN_N_09V: 6,
            Reserved: 1,
            RG_clk_ctrl: 4,
            RG_EN_TK_CTEST_09V: 1,
            RG_OPT_TK_MODE_09V: 1,
            RG_TK_SHIELD_MODE_09V: 2,
            RG_TK_SHIELD_DELAY_09V: 2,
            Touch_ADC_3V: 8;
}rf_reg_2_t;

typedef struct
{
   uint32_t  Reserved0: 23,
             RG_TK_IGEN_D_09V: 2,
             S10b_ON: 1,
             RG_TK_IGEN_l2X_09V: 1,
             RG_OPT_AFE_l2X_09V: 1,
             Reserved1: 3,
             BOR_Enable: 1;
}rf_reg_3_t;

typedef struct
{
     uint32_t FTSV: 3,
              Reserved: 1,
              RET_33: 1,
              RET_18: 1,
              VBYP: 2,
              CREF: 1,
              VDD_AWO_Sleep: 2,
              VDD_3V_1_Tr_enhance : 1,
              VDD_3V_1_REF_LPF: 1,
              Dig_Voltage_Force_1V0: 1,
              DCDC_PWM: 4,
              Dig_Voltage_Manual: 1,
              Dig_Voltage: 1,
              en_norm: 1,
              DIS_BGOK: 1,
              VSLP: 4,
              EN_BG_AWO: 1,
              VNW_EN: 1,
              VNW_Voltage: 2,
              Low_Voltage_Option: 1,
              Sleep_Regulator: 1;
}rf_reg_4_t;

typedef struct
{
    uint32_t Reserved: 32;
}rf_reg_5_t;

typedef struct
{
    uint32_t   Ring_Osc_Current: 2,
               Buffer_SW: 1,
               Slow_Clock_Current: 4,
               Ring_Osc_Stage: 1,
               VDD_3V_2_Tr_enhance: 1,
               LV_32K: 1,
               Reserved: 22;
 }rf_reg_6_t;

typedef struct
{
    uint32_t   ADC_COMP_Current: 3,
               ADC_CLK_DIV: 2,
               ADC_REFP: 2,
               ADC_REF_BUF_Current: 2,
               Reserved0: 1,
               LV_VCM: 1,
               Force_ADC_CH_VDD_to_INT: 1,
               ADC_SINGLE_DR: 1,
               Sinlge_ended_Mode: 1,
               External_Input_Buffer: 1,
               Temperature_Sensor_Type: 1,
               Temperature_Sensor: 1,
               Battery_Monitor: 1,
               Reserved2: 14;
}rf_reg_7_t;

typedef struct
{
    uint32_t   ADC_REF: 3,
               RSSI_Curve_Shift: 3,
               RSSI_Slope_Shift: 3,
               Charge_Pump_Current_TX_2mbps: 3,
               Charge_Pump_Current_TX_1mbps: 3,
               Charge_Pump_Current_RX_2mbps: 3,
               Reserved: 3,
               ADC_COMP_Current: 3,
               ADC_REFN: 2,
               ADC_BUF_Current: 3,
               ADC_REF_BUF_Current: 2,
               ADC_BUF_BYPASS: 1;
 }rf_reg_8_t;

typedef struct
{
    uint32_t   RX_Analog_Output_Enable: 1,
               RX_LA_Tune: 2,
               RX_HPF_Bandwidth: 2,
               Bypass_LPF_Bandwidth: 1,
               RX_LPF_Bandwidth: 1,
               RX_Filter_Manual_Bandwidth: 5,
               RXF_EN: 1,
               Reserved0: 2,
               RX_Filter_Current: 2,
               RX_Mixer_Filter_Bias_Voltage: 3,
               RX_Mixer_LO_Bias_Voltage: 3,
               RSSI_Manual: 1,
               RX_MUX: 3,
               RX_Filter_Bandwidth_2mbps: 2,
               RX_Filter_Bandwidth_1mbps: 2,
               Reserved1: 1;
}rf_reg_9_t;


typedef struct
{
    uint32_t   LNA_V_Contro: 3,
               LNA_V_Control_EN: 1,
               LNA_I_Control_1: 3,
               LNA_I_Control_2: 3,
               LNA_CA: 3,
               LNA_V_SEL: 1,
               LNA_I_SEL: 1,
               LNA_Gain_Control: 4,
               Reserved: 1,
               R1_RX_2Mbps: 3,
               R2_RX_2Mbps: 3,
               C2_RX_2Mbps: 3,
               C3_RX_2Mbps: 3;
}rf_reg_a_t;


typedef struct
{
    uint32_t   VDD_RF1_Reg_Bypass: 1,
               VDD_RF2_Reg_Bypass: 1,
               VDD_VCO_Reg_Bypass: 1,
               VDD_DIV2_Reg_Bypass: 1,
               VDD_CP_Reg_Bypass: 1,
               VDD_A_Reg_Bypass: 1,
               VDD_BUF_Reg_Bypass: 1,
               VDD_PLL_Reg_Bypass: 1,
               Reserved0: 2,
               VDD_VCO_Regulator_Voltage: 2,
               VDD_Div2_Regulator_Voltage: 2,
               VDD_PLL_Regulator_Voltage: 2,
               VDD_CP_Regulator_Voltage: 2,
               VDD_RF_Regulator_Voltage: 2,
               VDD_A_Regulator_Voltage: 1,
               VDD_BUF_Regulator_Voltage: 1,
               Reserved1: 1,
               R2_TX_2Mbps: 3,
               C2_TX_2Mbps: 3,
               C3_TX_2Mbps: 3;
}rf_reg_b_t;


typedef struct
{
    uint32_t   PA_Ramping_Up_Time_3V : 3,
               PA_Ramp_Up_Down_3V: 1,
               PA_Ramp_Down_Time: 2,
               VDD_RF2_Regulator_Voltage_3V: 3,
               PA0_BIAS2_EN_3V: 1,
               VSEL_8PA_3V: 1,
               DRV_WCTL_3V: 2,
               DRV_VCTRL2_3V: 3,
               DRV_VCTRL1_FINE_3V: 3,
               DRV_VCTRL1_COARSE_3V: 3,
               PA_8dBm_EN_3V: 1,
               Ramping_Manual: 2,
               Reserved: 4,
               R1_TX_2Mbps: 3;
}rf_reg_c_t;


typedef struct
{
    uint32_t   R1_TX_1Mbps: 3,
               R2_TX_1Mbps: 3,
               C2_TX_1Mbps: 3,
               C3_TX_1Mbps: 3,
               DTS_ICTL_COARSE: 3,
               DTS_ICTL_FINE: 3,
               DTS_VCTL: 3,
               VSEL_0PA: 1,
               VCTL_0PA: 3,
               ISEL_0PA: 1,
               ICTL_PA2: 3,
               ICTL_PA1: 3;
}rf_reg_d_t;


typedef struct
{
    uint32_t   VCO_Current_for_TX: 3,
               VCO_Current_for_RX: 3,
               VCO_Buffer_Current_for_TX: 3,
               VCO_Buffer_Current_for_RX: 3,
               Divide_by_2_current_for_TX: 3,
               Divide_by_2_current_for_RX: 3,
               LO_Buffer_current_TX: 3,
               LO_Buffer_current_RX: 3,
               Reserved: 1,
               DM_Sync_LP: 1,
               DM_Sync_HP: 1,
               Prescaler_D2S_Current: 3,
               Prescaler_Dummy: 1,
               TX_Dummy: 1;
  }rf_reg_e_t;


typedef struct
{
    uint32_t R1_RX_1Mbps: 3,
             R2_RX_1Mbps: 3,
             C2_RX_1Mbps: 3,
             C3_RX_1Mbps: 3,
             Charge_Pump_Disable: 1,
             Charge_Pump_Current_RX_1Mbps: 3,
             Reserved0: 1,
             Cal_Start_Manual: 1,
             LOCK_en: 1,
             VCO_Band: 6,
             MVCO: 1,
             VCO_Off_Control: 1,
             Lock_Detector_Reference: 2,
             Prescaler_inv_Sync: 1,
             Xtal_32MHz_inv_Sync : 1,
             Reserved1: 1;
}rf_reg_f_t;


typedef struct
{
    uint32_t Version: 5,
             PLL_96MHz_Lock: 1,
             ADC_Touch_OUT: 10,
             PLL_2_4GHz_Lock: 1,
             Charger: 1,
             Reserved: 14;
}rf_reg_ro_t;

typedef struct
{
    volatile rf_reg_0_t rf_reg_0;
    volatile rf_reg_1_t rf_reg_1;
    volatile rf_reg_2_t rf_reg_2;
    volatile rf_reg_3_t rf_reg_3;
    volatile rf_reg_4_t rf_reg_4;
    volatile rf_reg_5_t rf_reg_5;
    volatile rf_reg_6_t rf_reg_6;
    volatile rf_reg_7_t rf_reg_7;
    volatile rf_reg_8_t rf_reg_8;
    volatile rf_reg_9_t rf_reg_9;
    volatile rf_reg_a_t rf_reg_a;
    volatile rf_reg_b_t rf_reg_b;
    volatile rf_reg_c_t rf_reg_c;
    volatile rf_reg_d_t rf_reg_d;
    volatile rf_reg_e_t rf_reg_e;
    volatile rf_reg_f_t rf_reg_f;
    volatile rf_reg_ro_t rf_reg_ro;
}rf_reg_t;

/* exported variables --------------------------------------------------------*/
#define hwp_rf_reg ((rf_reg_t *)0x20201070)

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __RF_REG_TYPEDEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
