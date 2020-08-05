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
#ifndef __APOLLO_00_REG_SYSC_AWO_H__
#define __APOLLO_00_REG_SYSC_AWO_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_ble_reg.h"

/* exported types ------------------------------------------------------------*/

//reg_misc_1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                o_clk_sel_hbus0 :  3; /* 2: 0,                No description.*/
        uint32_t                o_clk_sel_hbus1 :  2; /* 4: 3,                No description.*/
        uint32_t                  blelp_inrp_en :  2; /* 6: 5, [0]---ose_en    [1]---radio_en*/
        uint32_t                     pmu_enable :  1; /* 7: 7, Enable PMU to carry out powerdown*/
        uint32_t           clk_div_hbus_para_m1 :  8; /*15: 8,                No description.*/
        uint32_t           clk_div_pbus_para_m1 :  4; /*19:16,                No description.*/
        uint32_t                     reserved_1 :  1; /*20:20,                       RESERVED*/
        uint32_t                     i_wicenack :  1; /*21:21, MCU read this bit to makesure WIC handshake has done, then can excute WFI/WFE*/
        uint32_t                   o_cpu_ret_en :  1; /*22:22,           cpu retention enable*/
        uint32_t                o_blemac_ret_en :  1; /*23:23,        blemac retention enable*/
        uint32_t                     reserved_0 :  8; /*31:24,                       RESERVED*/
    } ;
} T_SYSC_AWO_REG_MISC_1;

//reg_awo_clkg_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t              o_clkg_ble_lp_set :  1; /* 0: 0, write 1 to set clkg to 1. read clkg.  clk not gated*/
        uint32_t              o_clkg_ble_lp_clr :  1; /* 1: 1, write 1 to clr clkg to 0. read clkg . clk gated*/
        uint32_t                 o_clkg_rtc_set :  1; /* 2: 2, write 1 to set clkg to 1. read clkg */
        uint32_t                 o_clkg_rtc_clr :  1; /* 3: 3, write 1 to clr clkg to 0. read clkg */
        uint32_t        o_clkg_hbus_div_pll_set :  1; /* 4: 4, write 1 to set clkg to 1. read clkg */
        uint32_t        o_clkg_hbus_div_pll_clr :  1; /* 5: 5, write 1 to clr clkg to 0. read clkg */
        uint32_t        o_clkg_hbus_div_16m_set :  1; /* 6: 6, write 1 to set clkg to 1. read clkg */
        uint32_t        o_clkg_hbus_div_16m_clr :  1; /* 7: 7, write 1 to clr clkg to 0. read clkg */
        uint32_t                 o_clkg_wic_set :  1; /* 8: 8, write 1 to set clkg to 1. read clkg */
        uint32_t                 o_clkg_wic_clr :  1; /* 9: 9, write 1 to clr clkg to 0. read clkg */
        uint32_t                 o_clkg_ble_set :  1; /*10:10, write 1 to set clkg to 1. read clkg */
        uint32_t                 o_clkg_ble_clr :  1; /*11:11, write 1 to clr clkg to 0. read clkg */
        uint32_t           clkg_ble_mac_div_set :  1; /*12:12, write 1 to set clkg to 1. read clkg */
        uint32_t           clkg_ble_mac_div_clr :  1; /*13:13, write 1 to clr clkg to 0. read clkg */
        uint32_t        clkg_ble_mdm_rx_div_set :  1; /*14:14, write 1 to set clkg to 1. read clkg */
        uint32_t        clkg_ble_mdm_rx_div_clr :  1; /*15:15, write 1 to clr clkg to 0. read clkg */
        uint32_t                     reserved_0 : 16; /*31:16,                       RESERVED*/
    } ;
} T_SYSC_AWO_REG_AWO_CLKG_EN;

//reg_io_state
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                io_stat_ret_pmu :  1; /* 0: 0,    enable of PMU to retente IO*/
        uint32_t              io_stat_unret_pmu :  1; /* 1: 1,  enable of PMU to unretente IO*/
        uint32_t                    io_ctrl_sel :  1; /* 2: 2, SW control to seclect which IO state to output. 0---IO from pinshare  1---IO from retention by PMU or SW. Can also be controled by SW*/
        uint32_t                    io_stat_cap :  1; /* 3: 3, SW generate a pulse to retente IO*/
        uint32_t                     reserved_0 : 28; /*31: 4,                       RESERVED*/
    } ;
} T_SYSC_AWO_REG_IO_STATE;

//reg_pd_onoff
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t           o_pd_sram_off_by_pmu :  7; /* 6: 0, SW want to power down 7 PD_RAM*/
        uint32_t                     reserved_3 :  1; /* 7: 7,                       RESERVED*/
        uint32_t         o_pd_blemac_off_by_pmu :  1; /* 8: 8, SW want to power down PD_BLE_MAC*/
        uint32_t          o_pd_blerf_off_by_pmu :  1; /* 9: 9, SW want to power down PD_BLE_RF*/
        uint32_t            o_pd_per_off_by_pmu :  1; /*10:10,   SW want to power down PD_PER*/
        uint32_t                     reserved_2 :  5; /*15:11,                       RESERVED*/
        uint32_t            o_pd_sram_on_by_pmu :  7; /*22:16,   SW want to power on 7 PD_RAM*/
        uint32_t                     reserved_1 :  1; /*23:23,                       RESERVED*/
        uint32_t          o_pd_blemac_on_by_pmu :  1; /*24:24, SW want to power on PD_BLE_MAC*/
        uint32_t           o_pd_blerf_on_by_pmu :  1; /*25:25,  SW want to power on PD_BLE_RF*/
        uint32_t             o_pd_per_on_by_pmu :  1; /*26:26,     SW want to power on PD_PER*/
        uint32_t                     reserved_0 :  3; /*29:27,                       RESERVED*/
        uint32_t                  o_sw_pd_start :  1; /*30:30, SW start a power down flow. power down which domain depends [10:0]*/
        uint32_t                  o_sw_pu_start :  1; /*31:31, SW start a power on flow.  power on which domain depends [26:16]*/
    } ;
} T_SYSC_AWO_REG_PD_ONOFF;

//reg_sram_lowvdd
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t           o_sram_retention_req :  7; /* 6: 0, 7 SRAM on or off when in sleep state. 0--off 1--on*/
        uint32_t                     reserved_2 :  9; /*15: 7,                       RESERVED*/
        uint32_t           o_sram_retention_vdd :  4; /*19:16, the SRAM retention VDD value when powered down*/
        uint32_t                     reserved_1 :  4; /*23:20,                       RESERVED*/
        uint32_t                   o_sram_ls_en :  7; /*30:24, sram light sleep enable. when sram reduce VDD, can enter LS mode.*/
        uint32_t                     reserved_0 :  1; /*31:31,                       RESERVED*/
    } ;
} T_SYSC_AWO_REG_SRAM_LOWVDD;

//reg_pmu_timer
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  o_ldo_stb_dly :  5; /* 4: 0, the normal LDO &amp; DCDC stable time */
        uint32_t                     reserved_1 :  3; /* 7: 5,                       RESERVED*/
        uint32_t                  o_osc_stb_dly :  6; /*13: 8,           the OSC stable time */
        uint32_t                     reserved_0 :  2; /*15:14,                       RESERVED*/
        uint32_t                  o_ldo_swc_dly :  4; /*19:16,            the LDO switch time*/
        uint32_t                  o_clk_swc_dly :  4; /*23:20,         the clock switch time */
        uint32_t                 o_pmu_seq_time :  8; /*31:24, the state stay time when PMU output power dowm/up signal sequence*/
    } ;
} T_SYSC_AWO_REG_PMU_TIMER;

//reg_wakeup_src_mask
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               o_ldo_setup_time :  8; /* 7: 0,      PD ldo on/off stable time*/
        uint32_t            o_touch_ldo_stb_dly :  4; /*11: 8, the normal LDO stable time for touch ctrl use only.(touch need not turn on DCDC, so the dly is short)*/
        uint32_t                     reserved_0 : 20; /*31:12,                       RESERVED*/
    } ;
} T_SYSC_AWO_REG_WAKEUP_SRC_MASK;

//reg_clk_ldo_sel
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 dr_pmu_clk_sel :  1; /* 0: 0, PMU clock sel. 0--- select sel signal from PMU, 1---select register*/
        uint32_t                 dr_pmu_ldo_sel :  1; /* 1: 1, PMU LDO sel. 0--- select sel signal from PMU, 1---select register*/
        uint32_t               dr_normal_ldo_en :  1; /* 2: 2, normal LDO enable sel. 0--- select sel signal from PMU, 1---select register*/
        uint32_t                     reserved_4 :  1; /* 3: 3,                       RESERVED*/
        uint32_t                dr_16m_rcosc_en :  1; /* 4: 4, 16MHz rcosc enable sel. 0--- select sel signal from PMU, 1---select register*/
        uint32_t                     reserved_3 :  3; /* 7: 5,                       RESERVED*/
        uint32_t                reg_pmu_clk_sel :  1; /* 8: 8, can be usefule only when dr bit =1*/
        uint32_t                reg_pmu_ldo_sel :  1; /* 9: 9,       same as the Previous bit*/
        uint32_t              reg_normal_ldo_en :  1; /*10:10,       same as the Previous bit*/
        uint32_t                     reserved_2 :  1; /*11:11,                       RESERVED*/
        uint32_t               reg_16m_rcosc_en :  1; /*12:12,       same as the Previous bit*/
        uint32_t                     reserved_1 :  3; /*15:13,                       RESERVED*/
        uint32_t                o_ana_16m_selrc :  1; /*16:16, 1 : 32MHz RC                          0 : 32MHz Crystal*/
        uint32_t                  o_16m_xtal_en :  1; /*17:17,                16M XTAL enable*/
        uint32_t              o_ana_32k_selxtal :  1; /*18:18, 1 : 32KHz Crystal                     0 : 32KHz RC*/
        uint32_t                  o_32k_xtal_en :  1; /*19:19, 1 : 32.768KHz Crystal  Enable       0 : Disable*/
        uint32_t                 o_32k_rcosc_en :  1; /*20:20, 1 : 32KHz RC Enable       0 : Disable*/
        uint32_t                     reserved_0 : 11; /*31:21,                       RESERVED*/
    } ;
} T_SYSC_AWO_REG_CLK_LDO_SEL;

//reg_pd_state
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  i_pd_sram_req :  7; /* 6: 0,    Pd_SRAM state. 0--off 1--on*/
        uint32_t                     reserved_1 :  1; /* 7: 7,                       RESERVED*/
        uint32_t                i_pd_blemac_req :  1; /* 8: 8, Pd_BLE_MAC state. 0--off 1--on*/
        uint32_t                 i_pd_blerf_req :  1; /* 9: 9,  Pd_BLE_RF state. 0--off 1--on*/
        uint32_t                   i_pd_per_req :  1; /*10:10,     Pd_PER state. 0--off 1--on*/
        uint32_t                   i_pd_cpu_req :  1; /*11:11,     Pd_CPU state. 0--off 1--on*/
        uint32_t                     reserved_0 : 20; /*31:12,                       RESERVED*/
    } ;
} T_SYSC_AWO_REG_PD_STATE;

//ext_inrp_config
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    ext_inrp_en :  6; /* 5: 0, enable of 5 external interrupt([4:0]) and 1 touch interrupt([5])*/
        uint32_t                     reserved_1 :  2; /* 7: 6,                       RESERVED*/
        uint32_t               ext_inrp_sense_0 :  2; /* 9: 8, indicate the external interrupt 0 triggle condition. 00--hi level 01--low level  10--posedge 11--negedge*/
        uint32_t               ext_inrp_sense_1 :  2; /*11:10, indicate the external interrupt 1 triggle condition. 00--hi level 01--low level  10--posedge 11--negedge*/
        uint32_t               ext_inrp_sense_2 :  2; /*13:12, indicate the external interrupt 2 triggle condition. 00--hi level 01--low level  10--posedge 11--negedge*/
        uint32_t               ext_inrp_sense_3 :  2; /*15:14, indicate the external interrupt 3 triggle condition. 00--hi level 01--low level  10--posedge 11--negedge*/
        uint32_t               ext_inrp_sense_4 :  2; /*17:16, indicate the external interrupt 4 triggle condition. 00--hi level 01--low level  10--posedge 11--negedge*/
        uint32_t               ext_inrp_sense_5 :  2; /*19:18, indicate the touchl interrupt 4 triggle condition. 00--hi level 01--low level  10--posedge 11--negedge*/
        uint32_t                pin_is_inrp_src :  5; /*24:20, indicate this pin as interrupt source pin.1---as inrp pin.    0---normal pin*/
        uint32_t                     reserved_0 :  7; /*31:25,                       RESERVED*/
    } ;
} T_SYSC_AWO_EXT_INRP_CONFIG;

//ext_inrp_value
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               ext_inrp_value_r :  6; /* 5: 0,       external interrupt value*/
        uint32_t                     reserved_1 :  2; /* 7: 6,                       RESERVED*/
        uint32_t              ext_rawinrp_value :  6; /*13: 8,   external interrupt raw value*/
        uint32_t                     reserved_0 : 18; /*31:14,                       RESERVED*/
    } ;
} T_SYSC_AWO_EXT_INRP_VALUE;

//ext_inrp_clr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 ext_inrp_clr_r :  6; /* 5: 0, clear 5 external interrupt and 1 touch interrupt*/
        uint32_t                     reserved_0 : 26; /*31: 6,                       RESERVED*/
    } ;
} T_SYSC_AWO_EXT_INRP_CLR;

//blelp_inrp_value
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t             blelp_inrp_value_r :  2; /* 1: 0,          blelp interrupt value*/
        uint32_t                     reserved_1 :  6; /* 7: 2,                       RESERVED*/
        uint32_t            blelp_rawinrp_value :  2; /* 9: 8,      blelp interrupt raw value*/
        uint32_t                     reserved_0 : 22; /*31:10,                       RESERVED*/
    } ;
} T_SYSC_AWO_BLELP_INRP_VALUE;

//blelp_inrp_clr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               blelp_inrp_clr_r :  2; /* 1: 0,        clear 2 blelp interrupt*/
        uint32_t                     reserved_0 : 30; /*31: 2,                       RESERVED*/
    } ;
} T_SYSC_AWO_BLELP_INRP_CLR;

//clkgen_awo_signal_1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t           clk_div_pbus_para_up :  1; /* 0: 0,                No description.*/
        uint32_t        clk_div_ble_mac_para_up :  1; /* 1: 1,                No description.*/
        uint32_t                     reserved_0 : 30; /*31: 2,                       RESERVED*/
    } ;
} T_SYSC_AWO_CLKGEN_AWO_SIGNAL_1;

//clkgen_awo_signal_2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                clk_sel_ble_mac :  1; /* 0: 0,                No description.*/
        uint32_t          clk_sel_ble_mdm_rx_sw :  3; /* 3: 1,                No description.*/
        uint32_t       clk_sel_ble_mdm_rx_by_hw :  1; /* 4: 4,                No description.*/
        uint32_t     clk_div_ble_mdm_rx_para_m1 :  2; /* 6: 5,                No description.*/
        uint32_t                     reserved_1 :  1; /* 7: 7,                       RESERVED*/
        uint32_t       clk_div_ble_mac_para0_m1 :  4; /*11: 8,                No description.*/
        uint32_t       clk_div_ble_mac_para1_m1 :  4; /*15:12,                No description.*/
        uint32_t          clk_sel_ble_mac_by_hw :  1; /*16:16,                No description.*/
        uint32_t                     reserved_0 : 15; /*31:17,                       RESERVED*/
    } ;
} T_SYSC_AWO_CLKGEN_AWO_SIGNAL_2;

//awo_reset_signal
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 srst_all_n_set :  1; /* 0: 0, write this bit to set srst_all_n to 1*/
        uint32_t                 srst_all_n_clr :  1; /* 1: 1, write this bit to clear srst_all_n to 0*/
        uint32_t              srst_ble_lp_n_set :  1; /* 2: 2, write this bit to set srst_ble_lp_n to 1*/
        uint32_t              srst_ble_lp_n_clr :  1; /* 3: 3, write this bit to clear srst_ble_lp_n to 0*/
        uint32_t                 srst_rtc_n_set :  1; /* 4: 4, write this bit to set srst_rtc_n to 1*/
        uint32_t                 srst_rtc_n_clr :  1; /* 5: 5, write this bit to clear srst_rtc_n to 0*/
        uint32_t                 srst_ble_n_set :  1; /* 6: 6, write this bit to set srst_rtc_n to 1*/
        uint32_t                 srst_ble_n_clr :  1; /* 7: 7, write this bit to clear srst_rtc_n to 0*/
        uint32_t               srst_touch_n_set :  1; /* 8: 8, write this bit to set srst_rtc_n to 1*/
        uint32_t               srst_touch_n_clr :  1; /* 9: 9, write this bit to clear srst_rtc_n to 0*/
        uint32_t                     reserved_0 : 22; /*31:10,                       RESERVED*/
    } ;
} T_SYSC_AWO_AWO_RESET_SIGNAL;

//ram_parameter
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                   r_ram_wpulse :  3; /* 2: 0,              configed ram para*/
        uint32_t                       r_ram_ra :  2; /* 4: 3,              configed ram para*/
        uint32_t                       r_ram_wa :  3; /* 7: 5,              configed ram para*/
        uint32_t                       r_ram_rm :  4; /*11: 8,              configed ram para*/
        uint32_t                      r_ram_rme :  1; /*12:12,              configed ram_para*/
        uint32_t                     reserved_1 :  3; /*15:13,                       RESERVED*/
        uint32_t                   o_ram_wpulse :  3; /*18:16,               current ram para*/
        uint32_t                       o_ram_ra :  2; /*20:19,               current ram para*/
        uint32_t                       o_ram_wa :  3; /*23:21,               current ram para*/
        uint32_t                       o_ram_rm :  4; /*27:24,               current ram para*/
        uint32_t                      o_ram_rme :  1; /*28:28,               current ram_para*/
        uint32_t                     reserved_0 :  3; /*31:29,                       RESERVED*/
    } ;
} T_SYSC_AWO_RAM_PARAMETER;

//vdd_value
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    r_vdd_value :  1; /* 0: 0, configed PD ldo voltage value except PDsram */
        uint32_t                    o_vdd_value :  1; /* 1: 1, current value.1--1.1V  0--0.9V*/
        uint32_t                     reserved_0 : 30; /*31: 2,                       RESERVED*/
    } ;
} T_SYSC_AWO_VDD_VALUE;

//gpio_ds0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     o_gpio_ds0 : 30; /*29: 0,                No description.*/
        uint32_t                     reserved_0 :  2; /*31:30,                       RESERVED*/
    } ;
} T_SYSC_AWO_GPIO_DS0;

//gpio_ds1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     o_gpio_ds1 : 30; /*29: 0,                No description.*/
        uint32_t                     reserved_0 :  2; /*31:30,                       RESERVED*/
    } ;
} T_SYSC_AWO_GPIO_DS1;

//touch_cfg_1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      touch_itv : 16; /*15: 0,                No description.*/
        uint32_t                  rcosc_16m_dly :  4; /*19:16,                No description.*/
        uint32_t                       touch_en :  1; /*20:20,                No description.*/
        uint32_t                     reserved_0 : 11; /*31:21,                       RESERVED*/
    } ;
} T_SYSC_AWO_TOUCH_CFG_1;

//touch_cfg_2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 touch_scan_dly :  8; /* 7: 0,                No description.*/
        uint32_t                 touch_scan_num :  8; /*15: 8,                No description.*/
        uint32_t                     reserved_0 : 16; /*31:16,                       RESERVED*/
    } ;
} T_SYSC_AWO_TOUCH_CFG_2;

//touch_cfg_3
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      touch_thr : 18; /*17: 0,                No description.*/
        uint32_t                     reserved_0 : 14; /*31:18,                       RESERVED*/
    } ;
} T_SYSC_AWO_TOUCH_CFG_3;

//RF_REG_0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_0 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_0;

//RF_REG_1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_1 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_1;

//RF_REG_2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_2 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_2;

//RF_REG_3
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_3 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_3;

//RF_REG_4
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_4 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_4;

//RF_REG_5
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_5 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_5;

//RF_REG_6
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_6 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_6;

//RF_REG_7
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_7 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_7;

//RF_REG_8
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_8 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_8;

//RF_REG_9
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_9 : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_9;

//RF_REG_a
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_a : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_A;

//RF_REG_b
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_b : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_B;

//RF_REG_c
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_c : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_C;

//RF_REG_d
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_d : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_D;

//RF_REG_e
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_e : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_E;

//RF_REG_f
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_f : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_F;

//RF_REG_RD
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    i_rf_reg_ro : 32; /*31: 0,                No description.*/
    } ;
} T_SYSC_AWO_RF_REG_RD;

//pwr_pwm0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     pwm0_wid_l : 16; /*15: 0,                No description.*/
        uint32_t                     pwm0_wid_h : 16; /*31:16,                No description.*/
    } ;
} T_SYSC_AWO_PWR_PWM0;

//pwr_pwm1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     pwm1_wid_l : 16; /*15: 0,                No description.*/
        uint32_t                     pwm1_wid_h : 16; /*31:16,                No description.*/
    } ;
} T_SYSC_AWO_PWR_PWM1;

//pwr_pwm2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     pwm2_wid_l : 16; /*15: 0,                No description.*/
        uint32_t                     pwm2_wid_h : 16; /*31:16,                No description.*/
    } ;
} T_SYSC_AWO_PWR_PWM2;

//pwr_pwm_ctrl
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      pwm0_fc_h :  1; /* 0: 0,                No description.*/
        uint32_t                        pwm0_en :  1; /* 1: 1,                No description.*/
        uint32_t                     reserved_2 :  2; /* 3: 2,                No description.*/
        uint32_t                      pwm1_fc_h :  1; /* 4: 4,                No description.*/
        uint32_t                        pwm1_en :  1; /* 5: 5,                No description.*/
        uint32_t                     reserved_1 :  2; /* 7: 6,                No description.*/
        uint32_t                      pwm2_fc_h :  1; /* 8: 8,                No description.*/
        uint32_t                        pwm2_en :  1; /* 9: 9,                No description.*/
        uint32_t                     reserved_0 : 22; /*31:10,                No description.*/
    } ;
} T_SYSC_AWO_PWR_PWM_CTRL;

//boot_mode
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    boot_mode_0 :  1; /* 0: 0, 1----boot from uart     0------flash*/
        uint32_t                    boot_mode_1 :  1; /* 1: 1,                     IO voltage*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } ;
} T_SYSC_AWO_BOOT_MODE;

typedef struct
{
    __IO           T_SYSC_AWO_REG_MISC_1                     reg_misc_1; /*  0x0,    RW, 0x00E00081,             CLK INTRP Register*/
    __IO      T_SYSC_AWO_REG_AWO_CLKG_EN                reg_awo_clkg_en; /*  0x4,    RW, 0x0000FFFF,          AWO clkg set Register*/
    __IO         T_SYSC_AWO_REG_IO_STATE                   reg_io_state; /*  0x8,    RW, 0x00000000,      IO state control Register*/
    __IO         T_SYSC_AWO_REG_PD_ONOFF                   reg_pd_onoff; /*  0xc,    RW, 0x00000000,         SW control PD Register*/
    __IO      T_SYSC_AWO_REG_SRAM_LOWVDD                reg_sram_lowvdd; /* 0x10,    RW, 0x7F07007F,        SRAM retention Register*/
    __IO        T_SYSC_AWO_REG_PMU_TIMER                  reg_pmu_timer; /* 0x14,    RW, 0x08A51A10,             PMU timer Register*/
    __IO  T_SYSC_AWO_REG_WAKEUP_SRC_MASK            reg_wakeup_src_mask; /* 0x18,    RW, 0x00000680,           wakeup mask Register*/
    __IO      T_SYSC_AWO_REG_CLK_LDO_SEL                reg_clk_ldo_sel; /* 0x1c,    RW, 0x00121C00,       LDO CLK control Register*/
    __IO         T_SYSC_AWO_REG_PD_STATE                   reg_pd_state; /* 0x20,    RO, 0x00000F7F,              PD state Register*/
    __IO      T_SYSC_AWO_EXT_INRP_CONFIG                ext_inrp_config; /* 0x24,    RW, 0x0002AA00,                No description.*/
    __IO       T_SYSC_AWO_EXT_INRP_VALUE                 ext_inrp_value; /* 0x28,    RO, 0x00000000,                No description.*/
    __IO         T_SYSC_AWO_EXT_INRP_CLR                   ext_inrp_clr; /* 0x2c,    RW, 0x00000000,                No description.*/
    __IO     T_SYSC_AWO_BLELP_INRP_VALUE               blelp_inrp_value; /* 0x30,    RO, 0x00000000,                No description.*/
    __IO       T_SYSC_AWO_BLELP_INRP_CLR                 blelp_inrp_clr; /* 0x34,    RW, 0x00000000,                No description.*/
    __IO  T_SYSC_AWO_CLKGEN_AWO_SIGNAL_1            clkgen_awo_signal_1; /* 0x38,    RW, 0x00000000,                No description.*/
    __IO  T_SYSC_AWO_CLKGEN_AWO_SIGNAL_2            clkgen_awo_signal_2; /* 0x3c,    RW, 0x00000002,                No description.*/
    __IO     T_SYSC_AWO_AWO_RESET_SIGNAL               awo_reset_signal; /* 0x40,    RW, 0x000003FF,                No description.*/
    __IO        T_SYSC_AWO_RAM_PARAMETER                  ram_parameter; /* 0x44,    RW, 0x12C012C0,                No description.*/
    __IO            T_SYSC_AWO_VDD_VALUE                      vdd_value; /* 0x48,    RW, 0x00000003,                No description.*/
    __IO             T_SYSC_AWO_GPIO_DS0                       gpio_ds0; /* 0x4c,    RW, 0x3FFFFFFF,                No description.*/
    __IO             T_SYSC_AWO_GPIO_DS1                       gpio_ds1; /* 0x50,    RW, 0x3FFFFFFF,                No description.*/
    __IO    uint32_t    GPIO_IE; /* 0x54,    RW, 0x3FFFFFFF,                No description.*/
    __IO    uint32_t    GPIO_IS; /* 0x58,    RW, 0x00000000,                No description.*/
    __IO    uint32_t    GPIO_PE; /* 0x5c,    RW, 0x00000000,                No description.*/
    __IO    uint32_t    GPIO_PS; /* 0x60,    RW, 0x00000000,                No description.*/
    __IO          T_SYSC_AWO_TOUCH_CFG_1                    touch_cfg_1; /* 0x64,    RW, 0x00030000,                No description.*/
    __IO          T_SYSC_AWO_TOUCH_CFG_2                    touch_cfg_2; /* 0x68,    RW, 0x00000000,                No description.*/
    __IO          T_SYSC_AWO_TOUCH_CFG_3                    touch_cfg_3; /* 0x6c,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_0                       rf_reg_0; /* 0x70,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_1                       rf_reg_1; /* 0x74,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_2                       rf_reg_2; /* 0x78,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_3                       rf_reg_3; /* 0x7c,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_4                       rf_reg_4; /* 0x80,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_5                       rf_reg_5; /* 0x84,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_6                       rf_reg_6; /* 0x88,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_7                       rf_reg_7; /* 0x8c,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_8                       rf_reg_8; /* 0x90,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_9                       rf_reg_9; /* 0x94,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_A                       rf_reg_a; /* 0x98,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_B                       rf_reg_b; /* 0x9c,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_C                       rf_reg_c; /* 0xa0,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_D                       rf_reg_d; /* 0xa4,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_E                       rf_reg_e; /* 0xa8,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_RF_REG_F                       rf_reg_f; /* 0xac,    RW, 0x00000000,                No description.*/
    __IO            T_SYSC_AWO_RF_REG_RD                      rf_reg_rd; /* 0xb0,    RO, 0x22446689,                No description.*/
    __IO    uint32_t                  reserved_1[3];
    __IO             T_SYSC_AWO_PWR_PWM0                       pwr_pwm0; /* 0xc0,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_PWR_PWM1                       pwr_pwm1; /* 0xc4,    RW, 0x00000000,                No description.*/
    __IO             T_SYSC_AWO_PWR_PWM2                       pwr_pwm2; /* 0xc8,    RW, 0x00000000,                No description.*/
    __IO         T_SYSC_AWO_PWR_PWM_CTRL                   pwr_pwm_ctrl; /* 0xcc,    RW, 0x00000111,                No description.*/
    __IO            T_SYSC_AWO_BOOT_MODE                      boot_mode; /* 0xd0,    RO, 0x00000000,                No description.*/
} T_HWP_SYSC_AWO_T;

/* exported variables --------------------------------------------------------*/
#define		SYSC_AWO	((T_HWP_SYSC_AWO_T*)REG_SYSC_AWO_BASE)


/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_SYSC_AWO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

