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
#ifndef __REG_SYSC_AWO_H__
#define __REG_SYSC_AWO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_ble_reg.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
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
    } bit_field;
} _T_SYSC_AWO_REG_MISC_1;

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
    } bit_field;
} _T_SYSC_AWO_REG_AWO_CLKG_EN;

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
    } bit_field;
} _T_SYSC_AWO_REG_IO_STATE;

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
    } bit_field;
} _T_SYSC_AWO_REG_PD_ONOFF;

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
    } bit_field;
} _T_SYSC_AWO_REG_SRAM_LOWVDD;

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
    } bit_field;
} _T_SYSC_AWO_REG_PMU_TIMER;

//reg_wakeup_src_mask
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               o_ldo_setup_time :  8; /* 7: 0,      PD ldo on/off stable time*/
        uint32_t            o_touch_ldo_stb_dly :  4; /*11: 8, the normal LDO stable time for touch ctrl use only.(touch need not turn on DCDC, so the dly is short)*/
        uint32_t                     reserved_0 : 20; /*31:12,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_REG_WAKEUP_SRC_MASK;

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
    } bit_field;
} _T_SYSC_AWO_REG_CLK_LDO_SEL;

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
    } bit_field;
} _T_SYSC_AWO_REG_PD_STATE;

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
    } bit_field;
} _T_SYSC_AWO_EXT_INRP_CONFIG;

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
    } bit_field;
} _T_SYSC_AWO_EXT_INRP_VALUE;

//ext_inrp_clr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 ext_inrp_clr_r :  6; /* 5: 0, clear 5 external interrupt and 1 touch interrupt*/
        uint32_t                     reserved_0 : 26; /*31: 6,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_EXT_INRP_CLR;

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
    } bit_field;
} _T_SYSC_AWO_BLELP_INRP_VALUE;

//blelp_inrp_clr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               blelp_inrp_clr_r :  2; /* 1: 0,        clear 2 blelp interrupt*/
        uint32_t                     reserved_0 : 30; /*31: 2,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_BLELP_INRP_CLR;

//clkgen_awo_signal_1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t           clk_div_pbus_para_up :  1; /* 0: 0,                No description.*/
        uint32_t        clk_div_ble_mac_para_up :  1; /* 1: 1,                No description.*/
        uint32_t                     reserved_0 : 30; /*31: 2,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_CLKGEN_AWO_SIGNAL_1;

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
    } bit_field;
} _T_SYSC_AWO_CLKGEN_AWO_SIGNAL_2;

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
    } bit_field;
} _T_SYSC_AWO_AWO_RESET_SIGNAL;

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
    } bit_field;
} _T_SYSC_AWO_RAM_PARAMETER;

//vdd_value
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    r_vdd_value :  1; /* 0: 0, configed PD ldo voltage value except PDsram */
        uint32_t                    o_vdd_value :  1; /* 1: 1, current value.1--1.1V  0--0.9V*/
        uint32_t                     reserved_0 : 30; /*31: 2,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_VDD_VALUE;

//gpio_ds0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     o_gpio_ds0 : 30; /*29: 0,                No description.*/
        uint32_t                     reserved_0 :  2; /*31:30,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_GPIO_DS0;

//gpio_ds1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     o_gpio_ds1 : 30; /*29: 0,                No description.*/
        uint32_t                     reserved_0 :  2; /*31:30,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_GPIO_DS1;

//gpio_ie
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      o_gpio_ie : 30; /*29: 0,                No description.*/
        uint32_t                     reserved_0 :  2; /*31:30,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_GPIO_IE;

//gpio_is
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      o_gpio_is : 30; /*29: 0,                No description.*/
        uint32_t                     reserved_0 :  2; /*31:30,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_GPIO_IS;

//gpio_pe
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      o_gpio_pe : 30; /*29: 0,                No description.*/
        uint32_t                     reserved_0 :  2; /*31:30,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_GPIO_PE;

//gpio_ps
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      o_gpio_ps : 30; /*29: 0,                No description.*/
        uint32_t                     reserved_0 :  2; /*31:30,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_GPIO_PS;

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
    } bit_field;
} _T_SYSC_AWO_TOUCH_CFG_1;

//touch_cfg_2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 touch_scan_dly :  8; /* 7: 0,                No description.*/
        uint32_t                 touch_scan_num :  8; /*15: 8,                No description.*/
        uint32_t                     reserved_0 : 16; /*31:16,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_TOUCH_CFG_2;

//touch_cfg_3
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                      touch_thr : 18; /*17: 0,                No description.*/
        uint32_t                     reserved_0 : 14; /*31:18,                       RESERVED*/
    } bit_field;
} _T_SYSC_AWO_TOUCH_CFG_3;

//RF_REG_0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_0 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_0;

//RF_REG_1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_1 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_1;

//RF_REG_2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_2 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_2;

//RF_REG_3
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_3 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_3;

//RF_REG_4
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_4 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_4;

//RF_REG_5
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_5 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_5;

//RF_REG_6
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_6 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_6;

//RF_REG_7
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_7 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_7;

//RF_REG_8
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_8 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_8;

//RF_REG_9
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_9 : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_9;

//RF_REG_a
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_a : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_A;

//RF_REG_b
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_b : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_B;

//RF_REG_c
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_c : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_C;

//RF_REG_d
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_d : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_D;

//RF_REG_e
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_e : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_E;

//RF_REG_f
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                       rf_reg_f : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_F;

//RF_REG_RD
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    i_rf_reg_ro : 32; /*31: 0,                No description.*/
    } bit_field;
} _T_SYSC_AWO_RF_REG_RD;

//pwr_pwm0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     pwm0_wid_l : 16; /*15: 0,                No description.*/
        uint32_t                     pwm0_wid_h : 16; /*31:16,                No description.*/
    } bit_field;
} _T_SYSC_AWO_PWR_PWM0;

//pwr_pwm1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     pwm1_wid_l : 16; /*15: 0,                No description.*/
        uint32_t                     pwm1_wid_h : 16; /*31:16,                No description.*/
    } bit_field;
} _T_SYSC_AWO_PWR_PWM1;

//pwr_pwm2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     pwm2_wid_l : 16; /*15: 0,                No description.*/
        uint32_t                     pwm2_wid_h : 16; /*31:16,                No description.*/
    } bit_field;
} _T_SYSC_AWO_PWR_PWM2;

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
    } bit_field;
} _T_SYSC_AWO_PWR_PWM_CTRL;

//boot_mode
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    boot_mode_0 :  1; /* 0: 0, 1----boot from uart     0------flash*/
        uint32_t                    boot_mode_1 :  1; /* 1: 1,                     IO voltage*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } bit_field;
} _T_SYSC_AWO_BOOT_MODE;

//Registers Mapping to the same address

typedef struct
{
    volatile           _T_SYSC_AWO_REG_MISC_1                     reg_misc_1; /*  0x0,    RW, 0x00E00081,             CLK INTRP Register*/
    volatile      _T_SYSC_AWO_REG_AWO_CLKG_EN                reg_awo_clkg_en; /*  0x4,    RW, 0x0000FFFF,          AWO clkg set Register*/
    volatile         _T_SYSC_AWO_REG_IO_STATE                   reg_io_state; /*  0x8,    RW, 0x00000000,      IO state control Register*/
    volatile         _T_SYSC_AWO_REG_PD_ONOFF                   reg_pd_onoff; /*  0xc,    RW, 0x00000000,         SW control PD Register*/
    volatile      _T_SYSC_AWO_REG_SRAM_LOWVDD                reg_sram_lowvdd; /* 0x10,    RW, 0x7F07007F,        SRAM retention Register*/
    volatile        _T_SYSC_AWO_REG_PMU_TIMER                  reg_pmu_timer; /* 0x14,    RW, 0x08A51A10,             PMU timer Register*/
    volatile  _T_SYSC_AWO_REG_WAKEUP_SRC_MASK            reg_wakeup_src_mask; /* 0x18,    RW, 0x00000680,           wakeup mask Register*/
    volatile      _T_SYSC_AWO_REG_CLK_LDO_SEL                reg_clk_ldo_sel; /* 0x1c,    RW, 0x00121C00,       LDO CLK control Register*/
    volatile         _T_SYSC_AWO_REG_PD_STATE                   reg_pd_state; /* 0x20,    RO, 0x00000F7F,              PD state Register*/
    volatile      _T_SYSC_AWO_EXT_INRP_CONFIG                ext_inrp_config; /* 0x24,    RW, 0x0002AA00,                No description.*/
    volatile       _T_SYSC_AWO_EXT_INRP_VALUE                 ext_inrp_value; /* 0x28,    RO, 0x00000000,                No description.*/
    volatile         _T_SYSC_AWO_EXT_INRP_CLR                   ext_inrp_clr; /* 0x2c,    RW, 0x00000000,                No description.*/
    volatile     _T_SYSC_AWO_BLELP_INRP_VALUE               blelp_inrp_value; /* 0x30,    RO, 0x00000000,                No description.*/
    volatile       _T_SYSC_AWO_BLELP_INRP_CLR                 blelp_inrp_clr; /* 0x34,    RW, 0x00000000,                No description.*/
    volatile  _T_SYSC_AWO_CLKGEN_AWO_SIGNAL_1            clkgen_awo_signal_1; /* 0x38,    RW, 0x00000000,                No description.*/
    volatile  _T_SYSC_AWO_CLKGEN_AWO_SIGNAL_2            clkgen_awo_signal_2; /* 0x3c,    RW, 0x00000002,                No description.*/
    volatile     _T_SYSC_AWO_AWO_RESET_SIGNAL               awo_reset_signal; /* 0x40,    RW, 0x000003FF,                No description.*/
    volatile        _T_SYSC_AWO_RAM_PARAMETER                  ram_parameter; /* 0x44,    RW, 0x12C012C0,                No description.*/
    volatile            _T_SYSC_AWO_VDD_VALUE                      vdd_value; /* 0x48,    RW, 0x00000003,                No description.*/
    volatile             _T_SYSC_AWO_GPIO_DS0                       gpio_ds0; /* 0x4c,    RW, 0x3FFFFFFF,                No description.*/
    volatile             _T_SYSC_AWO_GPIO_DS1                       gpio_ds1; /* 0x50,    RW, 0x3FFFFFFF,                No description.*/
    volatile              _T_SYSC_AWO_GPIO_IE                        gpio_ie; /* 0x54,    RW, 0x3FFFFFFF,                No description.*/
    volatile              _T_SYSC_AWO_GPIO_IS                        gpio_is; /* 0x58,    RW, 0x00000000,                No description.*/
    volatile              _T_SYSC_AWO_GPIO_PE                        gpio_pe; /* 0x5c,    RW, 0x00000000,                No description.*/
    volatile              _T_SYSC_AWO_GPIO_PS                        gpio_ps; /* 0x60,    RW, 0x00000000,                No description.*/
    volatile          _T_SYSC_AWO_TOUCH_CFG_1                    touch_cfg_1; /* 0x64,    RW, 0x00030000,                No description.*/
    volatile          _T_SYSC_AWO_TOUCH_CFG_2                    touch_cfg_2; /* 0x68,    RW, 0x00000000,                No description.*/
    volatile          _T_SYSC_AWO_TOUCH_CFG_3                    touch_cfg_3; /* 0x6c,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_0                       rf_reg_0; /* 0x70,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_1                       rf_reg_1; /* 0x74,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_2                       rf_reg_2; /* 0x78,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_3                       rf_reg_3; /* 0x7c,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_4                       rf_reg_4; /* 0x80,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_5                       rf_reg_5; /* 0x84,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_6                       rf_reg_6; /* 0x88,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_7                       rf_reg_7; /* 0x8c,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_8                       rf_reg_8; /* 0x90,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_9                       rf_reg_9; /* 0x94,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_A                       rf_reg_a; /* 0x98,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_B                       rf_reg_b; /* 0x9c,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_C                       rf_reg_c; /* 0xa0,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_D                       rf_reg_d; /* 0xa4,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_E                       rf_reg_e; /* 0xa8,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_RF_REG_F                       rf_reg_f; /* 0xac,    RW, 0x00000000,                No description.*/
    volatile            _T_SYSC_AWO_RF_REG_RD                      rf_reg_rd; /* 0xb0,    RO, 0x22446689,                No description.*/
    volatile                        uint32_t                  reserved_1[3];
    volatile             _T_SYSC_AWO_PWR_PWM0                       pwr_pwm0; /* 0xc0,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_PWR_PWM1                       pwr_pwm1; /* 0xc4,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_AWO_PWR_PWM2                       pwr_pwm2; /* 0xc8,    RW, 0x00000000,                No description.*/
    volatile         _T_SYSC_AWO_PWR_PWM_CTRL                   pwr_pwm_ctrl; /* 0xcc,    RW, 0x00000111,                No description.*/
    volatile            _T_SYSC_AWO_BOOT_MODE                      boot_mode; /* 0xd0,    RO, 0x00000000,                No description.*/
} _T_HWP_SYSC_AWO_T;

/* exported variables --------------------------------------------------------*/
#define hwp_sysc_awo ((_T_HWP_SYSC_AWO_T*)REG_SYSC_AWO_BASE)

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_reg_misc_1_get(void)
{
    return hwp_sysc_awo->reg_misc_1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_misc_1_set(uint32_t value)
{
    hwp_sysc_awo->reg_misc_1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_misc_1_pack(uint8_t o_blemac_ret_en, uint8_t o_cpu_ret_en, uint8_t clk_div_pbus_para_m1, uint8_t clk_div_hbus_para_m1, uint8_t pmu_enable, uint8_t blelp_inrp_en, uint8_t o_clk_sel_hbus1, uint8_t o_clk_sel_hbus0)
{
    hwp_sysc_awo->reg_misc_1.val = (((uint32_t)o_blemac_ret_en << 23) | ((uint32_t)o_cpu_ret_en << 22) | ((uint32_t)clk_div_pbus_para_m1 << 16) | ((uint32_t)clk_div_hbus_para_m1 << 8) | ((uint32_t)pmu_enable << 7) | ((uint32_t)blelp_inrp_en << 5) | ((uint32_t)o_clk_sel_hbus1 << 3) | ((uint32_t)o_clk_sel_hbus0 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_misc_1_unpack(uint8_t* o_blemac_ret_en, uint8_t* o_cpu_ret_en, uint8_t* i_wicenack, uint8_t* clk_div_pbus_para_m1, uint8_t* clk_div_hbus_para_m1, uint8_t* pmu_enable, uint8_t* blelp_inrp_en, uint8_t* o_clk_sel_hbus1, uint8_t* o_clk_sel_hbus0)
{
    _T_SYSC_AWO_REG_MISC_1 localVal = hwp_sysc_awo->reg_misc_1;

    *o_blemac_ret_en = localVal.bit_field.o_blemac_ret_en;
    *o_cpu_ret_en = localVal.bit_field.o_cpu_ret_en;
    *i_wicenack = localVal.bit_field.i_wicenack;
    *clk_div_pbus_para_m1 = localVal.bit_field.clk_div_pbus_para_m1;
    *clk_div_hbus_para_m1 = localVal.bit_field.clk_div_hbus_para_m1;
    *pmu_enable = localVal.bit_field.pmu_enable;
    *blelp_inrp_en = localVal.bit_field.blelp_inrp_en;
    *o_clk_sel_hbus1 = localVal.bit_field.o_clk_sel_hbus1;
    *o_clk_sel_hbus0 = localVal.bit_field.o_clk_sel_hbus0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_blemac_ret_en_getf(void)
{
    return hwp_sysc_awo->reg_misc_1.bit_field.o_blemac_ret_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_blemac_ret_en_setf(uint8_t o_blemac_ret_en)
{
    hwp_sysc_awo->reg_misc_1.bit_field.o_blemac_ret_en = o_blemac_ret_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_cpu_ret_en_getf(void)
{
    return hwp_sysc_awo->reg_misc_1.bit_field.o_cpu_ret_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_cpu_ret_en_setf(uint8_t o_cpu_ret_en)
{
    hwp_sysc_awo->reg_misc_1.bit_field.o_cpu_ret_en = o_cpu_ret_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_i_wicenack_getf(void)
{
    return hwp_sysc_awo->reg_misc_1.bit_field.i_wicenack;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_clk_div_pbus_para_m1_getf(void)
{
    return hwp_sysc_awo->reg_misc_1.bit_field.clk_div_pbus_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clk_div_pbus_para_m1_setf(uint8_t clk_div_pbus_para_m1)
{
    hwp_sysc_awo->reg_misc_1.bit_field.clk_div_pbus_para_m1 = clk_div_pbus_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_clk_div_hbus_para_m1_getf(void)
{
    return hwp_sysc_awo->reg_misc_1.bit_field.clk_div_hbus_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clk_div_hbus_para_m1_setf(uint8_t clk_div_hbus_para_m1)
{
    hwp_sysc_awo->reg_misc_1.bit_field.clk_div_hbus_para_m1 = clk_div_hbus_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_pmu_enable_getf(void)
{
    return hwp_sysc_awo->reg_misc_1.bit_field.pmu_enable;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pmu_enable_setf(uint8_t pmu_enable)
{
    hwp_sysc_awo->reg_misc_1.bit_field.pmu_enable = pmu_enable;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_blelp_inrp_en_getf(void)
{
    return hwp_sysc_awo->reg_misc_1.bit_field.blelp_inrp_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_blelp_inrp_en_setf(uint8_t blelp_inrp_en)
{
    hwp_sysc_awo->reg_misc_1.bit_field.blelp_inrp_en = blelp_inrp_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_clk_sel_hbus1_getf(void)
{
    return hwp_sysc_awo->reg_misc_1.bit_field.o_clk_sel_hbus1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_clk_sel_hbus1_setf(uint8_t o_clk_sel_hbus1)
{
    hwp_sysc_awo->reg_misc_1.bit_field.o_clk_sel_hbus1 = o_clk_sel_hbus1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_clk_sel_hbus0_getf(void)
{
    return hwp_sysc_awo->reg_misc_1.bit_field.o_clk_sel_hbus0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_clk_sel_hbus0_setf(uint8_t o_clk_sel_hbus0)
{
    hwp_sysc_awo->reg_misc_1.bit_field.o_clk_sel_hbus0 = o_clk_sel_hbus0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_reg_awo_clkg_en_get(void)
{
    return hwp_sysc_awo->reg_awo_clkg_en.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_awo_clkg_en_set(uint32_t value)
{
    hwp_sysc_awo->reg_awo_clkg_en.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_awo_clkg_en_pack(uint8_t clkg_ble_mdm_rx_div_clr, uint8_t clkg_ble_mdm_rx_div_set, uint8_t clkg_ble_mac_div_clr, uint8_t clkg_ble_mac_div_set, uint8_t o_clkg_ble_clr, uint8_t o_clkg_ble_set, uint8_t o_clkg_wic_clr, uint8_t o_clkg_wic_set, uint8_t o_clkg_hbus_div_16m_clr, uint8_t o_clkg_hbus_div_16m_set, uint8_t o_clkg_hbus_div_pll_clr, uint8_t o_clkg_hbus_div_pll_set, uint8_t o_clkg_rtc_clr, uint8_t o_clkg_rtc_set, uint8_t o_clkg_ble_lp_clr, uint8_t o_clkg_ble_lp_set)
{
    hwp_sysc_awo->reg_awo_clkg_en.val = (((uint32_t)clkg_ble_mdm_rx_div_clr << 15) | ((uint32_t)clkg_ble_mdm_rx_div_set << 14) | ((uint32_t)clkg_ble_mac_div_clr << 13) | ((uint32_t)clkg_ble_mac_div_set << 12) | ((uint32_t)o_clkg_ble_clr << 11) | ((uint32_t)o_clkg_ble_set << 10) | ((uint32_t)o_clkg_wic_clr << 9) | ((uint32_t)o_clkg_wic_set << 8) | ((uint32_t)o_clkg_hbus_div_16m_clr << 7) | ((uint32_t)o_clkg_hbus_div_16m_set << 6) | ((uint32_t)o_clkg_hbus_div_pll_clr << 5) | ((uint32_t)o_clkg_hbus_div_pll_set << 4) | ((uint32_t)o_clkg_rtc_clr << 3) | ((uint32_t)o_clkg_rtc_set << 2) | ((uint32_t)o_clkg_ble_lp_clr << 1) | ((uint32_t)o_clkg_ble_lp_set << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_reg_io_state_get(void)
{
    return hwp_sysc_awo->reg_io_state.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_io_state_set(uint32_t value)
{
    hwp_sysc_awo->reg_io_state.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_io_state_pack(uint8_t io_stat_cap, uint8_t io_ctrl_sel, uint8_t io_stat_unret_pmu, uint8_t io_stat_ret_pmu)
{
    hwp_sysc_awo->reg_io_state.val = (((uint32_t)io_stat_cap << 3) | ((uint32_t)io_ctrl_sel << 2) | ((uint32_t)io_stat_unret_pmu << 1) | ((uint32_t)io_stat_ret_pmu << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_io_state_unpack(uint8_t* io_ctrl_sel, uint8_t* io_stat_unret_pmu, uint8_t* io_stat_ret_pmu)
{
    _T_SYSC_AWO_REG_IO_STATE localVal = hwp_sysc_awo->reg_io_state;

    *io_ctrl_sel = localVal.bit_field.io_ctrl_sel;
    *io_stat_unret_pmu = localVal.bit_field.io_stat_unret_pmu;
    *io_stat_ret_pmu = localVal.bit_field.io_stat_ret_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_io_ctrl_sel_getf(void)
{
    return hwp_sysc_awo->reg_io_state.bit_field.io_ctrl_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_io_ctrl_sel_setf(uint8_t io_ctrl_sel)
{
    hwp_sysc_awo->reg_io_state.bit_field.io_ctrl_sel = io_ctrl_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_io_stat_unret_pmu_getf(void)
{
    return hwp_sysc_awo->reg_io_state.bit_field.io_stat_unret_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_io_stat_unret_pmu_setf(uint8_t io_stat_unret_pmu)
{
    hwp_sysc_awo->reg_io_state.bit_field.io_stat_unret_pmu = io_stat_unret_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_io_stat_ret_pmu_getf(void)
{
    return hwp_sysc_awo->reg_io_state.bit_field.io_stat_ret_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_io_stat_ret_pmu_setf(uint8_t io_stat_ret_pmu)
{
    hwp_sysc_awo->reg_io_state.bit_field.io_stat_ret_pmu = io_stat_ret_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_reg_pd_onoff_get(void)
{
    return hwp_sysc_awo->reg_pd_onoff.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_pd_onoff_set(uint32_t value)
{
    hwp_sysc_awo->reg_pd_onoff.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_pd_onoff_pack(uint8_t o_sw_pu_start, uint8_t o_sw_pd_start, uint8_t o_pd_per_on_by_pmu, uint8_t o_pd_blerf_on_by_pmu, uint8_t o_pd_blemac_on_by_pmu, uint8_t o_pd_sram_on_by_pmu, uint8_t o_pd_per_off_by_pmu, uint8_t o_pd_blerf_off_by_pmu, uint8_t o_pd_blemac_off_by_pmu, uint8_t o_pd_sram_off_by_pmu)
{
    hwp_sysc_awo->reg_pd_onoff.val = (((uint32_t)o_sw_pu_start << 31) | ((uint32_t)o_sw_pd_start << 30) | ((uint32_t)o_pd_per_on_by_pmu << 26) | ((uint32_t)o_pd_blerf_on_by_pmu << 25) | ((uint32_t)o_pd_blemac_on_by_pmu << 24) | ((uint32_t)o_pd_sram_on_by_pmu << 16) | ((uint32_t)o_pd_per_off_by_pmu << 10) | ((uint32_t)o_pd_blerf_off_by_pmu << 9) | ((uint32_t)o_pd_blemac_off_by_pmu << 8) | ((uint32_t)o_pd_sram_off_by_pmu << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_pd_onoff_unpack(uint8_t* o_pd_per_on_by_pmu, uint8_t* o_pd_blerf_on_by_pmu, uint8_t* o_pd_blemac_on_by_pmu, uint8_t* o_pd_sram_on_by_pmu, uint8_t* o_pd_per_off_by_pmu, uint8_t* o_pd_blerf_off_by_pmu, uint8_t* o_pd_blemac_off_by_pmu, uint8_t* o_pd_sram_off_by_pmu)
{
    _T_SYSC_AWO_REG_PD_ONOFF localVal = hwp_sysc_awo->reg_pd_onoff;

    *o_pd_per_on_by_pmu = localVal.bit_field.o_pd_per_on_by_pmu;
    *o_pd_blerf_on_by_pmu = localVal.bit_field.o_pd_blerf_on_by_pmu;
    *o_pd_blemac_on_by_pmu = localVal.bit_field.o_pd_blemac_on_by_pmu;
    *o_pd_sram_on_by_pmu = localVal.bit_field.o_pd_sram_on_by_pmu;
    *o_pd_per_off_by_pmu = localVal.bit_field.o_pd_per_off_by_pmu;
    *o_pd_blerf_off_by_pmu = localVal.bit_field.o_pd_blerf_off_by_pmu;
    *o_pd_blemac_off_by_pmu = localVal.bit_field.o_pd_blemac_off_by_pmu;
    *o_pd_sram_off_by_pmu = localVal.bit_field.o_pd_sram_off_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_pd_per_on_by_pmu_getf(void)
{
    return hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_per_on_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_pd_per_on_by_pmu_setf(uint8_t o_pd_per_on_by_pmu)
{
    hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_per_on_by_pmu = o_pd_per_on_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_pd_blerf_on_by_pmu_getf(void)
{
    return hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_blerf_on_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_pd_blerf_on_by_pmu_setf(uint8_t o_pd_blerf_on_by_pmu)
{
    hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_blerf_on_by_pmu = o_pd_blerf_on_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_pd_blemac_on_by_pmu_getf(void)
{
    return hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_blemac_on_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_pd_blemac_on_by_pmu_setf(uint8_t o_pd_blemac_on_by_pmu)
{
    hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_blemac_on_by_pmu = o_pd_blemac_on_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_pd_sram_on_by_pmu_getf(void)
{
    return hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_sram_on_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_pd_sram_on_by_pmu_setf(uint8_t o_pd_sram_on_by_pmu)
{
    hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_sram_on_by_pmu = o_pd_sram_on_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_pd_per_off_by_pmu_getf(void)
{
    return hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_per_off_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_pd_per_off_by_pmu_setf(uint8_t o_pd_per_off_by_pmu)
{
    hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_per_off_by_pmu = o_pd_per_off_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_pd_blerf_off_by_pmu_getf(void)
{
    return hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_blerf_off_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_pd_blerf_off_by_pmu_setf(uint8_t o_pd_blerf_off_by_pmu)
{
    hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_blerf_off_by_pmu = o_pd_blerf_off_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_pd_blemac_off_by_pmu_getf(void)
{
    return hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_blemac_off_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_pd_blemac_off_by_pmu_setf(uint8_t o_pd_blemac_off_by_pmu)
{
    hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_blemac_off_by_pmu = o_pd_blemac_off_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_pd_sram_off_by_pmu_getf(void)
{
    return hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_sram_off_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_pd_sram_off_by_pmu_setf(uint8_t o_pd_sram_off_by_pmu)
{
    hwp_sysc_awo->reg_pd_onoff.bit_field.o_pd_sram_off_by_pmu = o_pd_sram_off_by_pmu;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_reg_sram_lowvdd_get(void)
{
    return hwp_sysc_awo->reg_sram_lowvdd.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_sram_lowvdd_set(uint32_t value)
{
    hwp_sysc_awo->reg_sram_lowvdd.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_sram_lowvdd_pack(uint8_t o_sram_ls_en, uint8_t o_sram_retention_vdd, uint8_t o_sram_retention_req)
{
    hwp_sysc_awo->reg_sram_lowvdd.val = (((uint32_t)o_sram_ls_en << 24) | ((uint32_t)o_sram_retention_vdd << 16) | ((uint32_t)o_sram_retention_req << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_sram_lowvdd_unpack(uint8_t* o_sram_ls_en, uint8_t* o_sram_retention_vdd, uint8_t* o_sram_retention_req)
{
    _T_SYSC_AWO_REG_SRAM_LOWVDD localVal = hwp_sysc_awo->reg_sram_lowvdd;

    *o_sram_ls_en = localVal.bit_field.o_sram_ls_en;
    *o_sram_retention_vdd = localVal.bit_field.o_sram_retention_vdd;
    *o_sram_retention_req = localVal.bit_field.o_sram_retention_req;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_sram_ls_en_getf(void)
{
    return hwp_sysc_awo->reg_sram_lowvdd.bit_field.o_sram_ls_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_sram_ls_en_setf(uint8_t o_sram_ls_en)
{
    hwp_sysc_awo->reg_sram_lowvdd.bit_field.o_sram_ls_en = o_sram_ls_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_sram_retention_vdd_getf(void)
{
    return hwp_sysc_awo->reg_sram_lowvdd.bit_field.o_sram_retention_vdd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_sram_retention_vdd_setf(uint8_t o_sram_retention_vdd)
{
    hwp_sysc_awo->reg_sram_lowvdd.bit_field.o_sram_retention_vdd = o_sram_retention_vdd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_sram_retention_req_getf(void)
{
    return hwp_sysc_awo->reg_sram_lowvdd.bit_field.o_sram_retention_req;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_sram_retention_req_setf(uint8_t o_sram_retention_req)
{
    hwp_sysc_awo->reg_sram_lowvdd.bit_field.o_sram_retention_req = o_sram_retention_req;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_reg_pmu_timer_get(void)
{
    return hwp_sysc_awo->reg_pmu_timer.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_pmu_timer_set(uint32_t value)
{
    hwp_sysc_awo->reg_pmu_timer.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_pmu_timer_pack(uint8_t o_pmu_seq_time, uint8_t o_clk_swc_dly, uint8_t o_ldo_swc_dly, uint8_t o_osc_stb_dly, uint8_t o_ldo_stb_dly)
{
    hwp_sysc_awo->reg_pmu_timer.val = (((uint32_t)o_pmu_seq_time << 24) | ((uint32_t)o_clk_swc_dly << 20) | ((uint32_t)o_ldo_swc_dly << 16) | ((uint32_t)o_osc_stb_dly << 8) | ((uint32_t)o_ldo_stb_dly << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_pmu_timer_unpack(uint8_t* o_pmu_seq_time, uint8_t* o_clk_swc_dly, uint8_t* o_ldo_swc_dly, uint8_t* o_osc_stb_dly, uint8_t* o_ldo_stb_dly)
{
    _T_SYSC_AWO_REG_PMU_TIMER localVal = hwp_sysc_awo->reg_pmu_timer;

    *o_pmu_seq_time = localVal.bit_field.o_pmu_seq_time;
    *o_clk_swc_dly = localVal.bit_field.o_clk_swc_dly;
    *o_ldo_swc_dly = localVal.bit_field.o_ldo_swc_dly;
    *o_osc_stb_dly = localVal.bit_field.o_osc_stb_dly;
    *o_ldo_stb_dly = localVal.bit_field.o_ldo_stb_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_pmu_seq_time_getf(void)
{
    return hwp_sysc_awo->reg_pmu_timer.bit_field.o_pmu_seq_time;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_pmu_seq_time_setf(uint8_t o_pmu_seq_time)
{
    hwp_sysc_awo->reg_pmu_timer.bit_field.o_pmu_seq_time = o_pmu_seq_time;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_clk_swc_dly_getf(void)
{
    return hwp_sysc_awo->reg_pmu_timer.bit_field.o_clk_swc_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_clk_swc_dly_setf(uint8_t o_clk_swc_dly)
{
    hwp_sysc_awo->reg_pmu_timer.bit_field.o_clk_swc_dly = o_clk_swc_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ldo_swc_dly_getf(void)
{
    return hwp_sysc_awo->reg_pmu_timer.bit_field.o_ldo_swc_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_ldo_swc_dly_setf(uint8_t o_ldo_swc_dly)
{
    hwp_sysc_awo->reg_pmu_timer.bit_field.o_ldo_swc_dly = o_ldo_swc_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_osc_stb_dly_getf(void)
{
    return hwp_sysc_awo->reg_pmu_timer.bit_field.o_osc_stb_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_osc_stb_dly_setf(uint8_t o_osc_stb_dly)
{
    hwp_sysc_awo->reg_pmu_timer.bit_field.o_osc_stb_dly = o_osc_stb_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ldo_stb_dly_getf(void)
{
    return hwp_sysc_awo->reg_pmu_timer.bit_field.o_ldo_stb_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_ldo_stb_dly_setf(uint8_t o_ldo_stb_dly)
{
    hwp_sysc_awo->reg_pmu_timer.bit_field.o_ldo_stb_dly = o_ldo_stb_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_reg_wakeup_src_mask_get(void)
{
    return hwp_sysc_awo->reg_wakeup_src_mask.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_wakeup_src_mask_set(uint32_t value)
{
    hwp_sysc_awo->reg_wakeup_src_mask.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_wakeup_src_mask_pack(uint8_t o_touch_ldo_stb_dly, uint8_t o_ldo_setup_time)
{
    hwp_sysc_awo->reg_wakeup_src_mask.val = (((uint32_t)o_touch_ldo_stb_dly << 8) | ((uint32_t)o_ldo_setup_time << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_wakeup_src_mask_unpack(uint8_t* o_touch_ldo_stb_dly, uint8_t* o_ldo_setup_time)
{
    _T_SYSC_AWO_REG_WAKEUP_SRC_MASK localVal = hwp_sysc_awo->reg_wakeup_src_mask;

    *o_touch_ldo_stb_dly = localVal.bit_field.o_touch_ldo_stb_dly;
    *o_ldo_setup_time = localVal.bit_field.o_ldo_setup_time;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_touch_ldo_stb_dly_getf(void)
{
    return hwp_sysc_awo->reg_wakeup_src_mask.bit_field.o_touch_ldo_stb_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_touch_ldo_stb_dly_setf(uint8_t o_touch_ldo_stb_dly)
{
    hwp_sysc_awo->reg_wakeup_src_mask.bit_field.o_touch_ldo_stb_dly = o_touch_ldo_stb_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ldo_setup_time_getf(void)
{
    return hwp_sysc_awo->reg_wakeup_src_mask.bit_field.o_ldo_setup_time;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_ldo_setup_time_setf(uint8_t o_ldo_setup_time)
{
    hwp_sysc_awo->reg_wakeup_src_mask.bit_field.o_ldo_setup_time = o_ldo_setup_time;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_reg_clk_ldo_sel_get(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_clk_ldo_sel_set(uint32_t value)
{
    hwp_sysc_awo->reg_clk_ldo_sel.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_clk_ldo_sel_pack(uint8_t o_32k_rcosc_en, uint8_t o_32k_xtal_en, uint8_t o_ana_32k_selxtal, uint8_t o_16m_xtal_en, uint8_t o_ana_16m_selrc, uint8_t reg_16m_rcosc_en, uint8_t reg_normal_ldo_en, uint8_t reg_pmu_ldo_sel, uint8_t reg_pmu_clk_sel, uint8_t dr_16m_rcosc_en, uint8_t dr_normal_ldo_en, uint8_t dr_pmu_ldo_sel, uint8_t dr_pmu_clk_sel)
{
    hwp_sysc_awo->reg_clk_ldo_sel.val = (((uint32_t)o_32k_rcosc_en << 20) | ((uint32_t)o_32k_xtal_en << 19) | ((uint32_t)o_ana_32k_selxtal << 18) | ((uint32_t)o_16m_xtal_en << 17) | ((uint32_t)o_ana_16m_selrc << 16) | ((uint32_t)reg_16m_rcosc_en << 12) | ((uint32_t)reg_normal_ldo_en << 10) | ((uint32_t)reg_pmu_ldo_sel << 9) | ((uint32_t)reg_pmu_clk_sel << 8) | ((uint32_t)dr_16m_rcosc_en << 4) | ((uint32_t)dr_normal_ldo_en << 2) | ((uint32_t)dr_pmu_ldo_sel << 1) | ((uint32_t)dr_pmu_clk_sel << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_clk_ldo_sel_unpack(uint8_t* o_32k_rcosc_en, uint8_t* o_32k_xtal_en, uint8_t* o_ana_32k_selxtal, uint8_t* o_16m_xtal_en, uint8_t* o_ana_16m_selrc, uint8_t* reg_16m_rcosc_en, uint8_t* reg_normal_ldo_en, uint8_t* reg_pmu_ldo_sel, uint8_t* reg_pmu_clk_sel, uint8_t* dr_16m_rcosc_en, uint8_t* dr_normal_ldo_en, uint8_t* dr_pmu_ldo_sel, uint8_t* dr_pmu_clk_sel)
{
    _T_SYSC_AWO_REG_CLK_LDO_SEL localVal = hwp_sysc_awo->reg_clk_ldo_sel;

    *o_32k_rcosc_en = localVal.bit_field.o_32k_rcosc_en;
    *o_32k_xtal_en = localVal.bit_field.o_32k_xtal_en;
    *o_ana_32k_selxtal = localVal.bit_field.o_ana_32k_selxtal;
    *o_16m_xtal_en = localVal.bit_field.o_16m_xtal_en;
    *o_ana_16m_selrc = localVal.bit_field.o_ana_16m_selrc;
    *reg_16m_rcosc_en = localVal.bit_field.reg_16m_rcosc_en;
    *reg_normal_ldo_en = localVal.bit_field.reg_normal_ldo_en;
    *reg_pmu_ldo_sel = localVal.bit_field.reg_pmu_ldo_sel;
    *reg_pmu_clk_sel = localVal.bit_field.reg_pmu_clk_sel;
    *dr_16m_rcosc_en = localVal.bit_field.dr_16m_rcosc_en;
    *dr_normal_ldo_en = localVal.bit_field.dr_normal_ldo_en;
    *dr_pmu_ldo_sel = localVal.bit_field.dr_pmu_ldo_sel;
    *dr_pmu_clk_sel = localVal.bit_field.dr_pmu_clk_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_32k_rcosc_en_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_32k_rcosc_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_32k_rcosc_en_setf(uint8_t o_32k_rcosc_en)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_32k_rcosc_en = o_32k_rcosc_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_32k_xtal_en_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_32k_xtal_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_32k_xtal_en_setf(uint8_t o_32k_xtal_en)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_32k_xtal_en = o_32k_xtal_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ana_32k_selxtal_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_ana_32k_selxtal;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_ana_32k_selxtal_setf(uint8_t o_ana_32k_selxtal)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_ana_32k_selxtal = o_ana_32k_selxtal;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_16m_xtal_en_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_16m_xtal_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_16m_xtal_en_setf(uint8_t o_16m_xtal_en)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_16m_xtal_en = o_16m_xtal_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ana_16m_selrc_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_ana_16m_selrc;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_ana_16m_selrc_setf(uint8_t o_ana_16m_selrc)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.o_ana_16m_selrc = o_ana_16m_selrc;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_reg_16m_rcosc_en_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.reg_16m_rcosc_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_16m_rcosc_en_setf(uint8_t reg_16m_rcosc_en)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.reg_16m_rcosc_en = reg_16m_rcosc_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_reg_normal_ldo_en_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.reg_normal_ldo_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_normal_ldo_en_setf(uint8_t reg_normal_ldo_en)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.reg_normal_ldo_en = reg_normal_ldo_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_reg_pmu_ldo_sel_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.reg_pmu_ldo_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_pmu_ldo_sel_setf(uint8_t reg_pmu_ldo_sel)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.reg_pmu_ldo_sel = reg_pmu_ldo_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_reg_pmu_clk_sel_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.reg_pmu_clk_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_pmu_clk_sel_setf(uint8_t reg_pmu_clk_sel)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.reg_pmu_clk_sel = reg_pmu_clk_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_dr_16m_rcosc_en_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.dr_16m_rcosc_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_dr_16m_rcosc_en_setf(uint8_t dr_16m_rcosc_en)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.dr_16m_rcosc_en = dr_16m_rcosc_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_dr_normal_ldo_en_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.dr_normal_ldo_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_dr_normal_ldo_en_setf(uint8_t dr_normal_ldo_en)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.dr_normal_ldo_en = dr_normal_ldo_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_dr_pmu_ldo_sel_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.dr_pmu_ldo_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_dr_pmu_ldo_sel_setf(uint8_t dr_pmu_ldo_sel)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.dr_pmu_ldo_sel = dr_pmu_ldo_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_dr_pmu_clk_sel_getf(void)
{
    return hwp_sysc_awo->reg_clk_ldo_sel.bit_field.dr_pmu_clk_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_dr_pmu_clk_sel_setf(uint8_t dr_pmu_clk_sel)
{
    hwp_sysc_awo->reg_clk_ldo_sel.bit_field.dr_pmu_clk_sel = dr_pmu_clk_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_reg_pd_state_get(void)
{
    return hwp_sysc_awo->reg_pd_state.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_reg_pd_state_unpack(uint8_t* i_pd_cpu_req, uint8_t* i_pd_per_req, uint8_t* i_pd_blerf_req, uint8_t* i_pd_blemac_req, uint8_t* i_pd_sram_req)
{
    _T_SYSC_AWO_REG_PD_STATE localVal = hwp_sysc_awo->reg_pd_state;

    *i_pd_cpu_req = localVal.bit_field.i_pd_cpu_req;
    *i_pd_per_req = localVal.bit_field.i_pd_per_req;
    *i_pd_blerf_req = localVal.bit_field.i_pd_blerf_req;
    *i_pd_blemac_req = localVal.bit_field.i_pd_blemac_req;
    *i_pd_sram_req = localVal.bit_field.i_pd_sram_req;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_i_pd_cpu_req_getf(void)
{
    return hwp_sysc_awo->reg_pd_state.bit_field.i_pd_cpu_req;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_i_pd_per_req_getf(void)
{
    return hwp_sysc_awo->reg_pd_state.bit_field.i_pd_per_req;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_i_pd_blerf_req_getf(void)
{
    return hwp_sysc_awo->reg_pd_state.bit_field.i_pd_blerf_req;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_i_pd_blemac_req_getf(void)
{
    return hwp_sysc_awo->reg_pd_state.bit_field.i_pd_blemac_req;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_i_pd_sram_req_getf(void)
{
    return hwp_sysc_awo->reg_pd_state.bit_field.i_pd_sram_req;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_ext_inrp_config_get(void)
{
    return hwp_sysc_awo->ext_inrp_config.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_config_set(uint32_t value)
{
    hwp_sysc_awo->ext_inrp_config.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_config_pack(uint8_t pin_is_inrp_src, uint8_t ext_inrp_sense_5, uint8_t ext_inrp_sense_4, uint8_t ext_inrp_sense_3, uint8_t ext_inrp_sense_2, uint8_t ext_inrp_sense_1, uint8_t ext_inrp_sense_0, uint8_t ext_inrp_en)
{
    hwp_sysc_awo->ext_inrp_config.val = (((uint32_t)pin_is_inrp_src << 20) | ((uint32_t)ext_inrp_sense_5 << 18) | ((uint32_t)ext_inrp_sense_4 << 16) | ((uint32_t)ext_inrp_sense_3 << 14) | ((uint32_t)ext_inrp_sense_2 << 12) | ((uint32_t)ext_inrp_sense_1 << 10) | ((uint32_t)ext_inrp_sense_0 << 8) | ((uint32_t)ext_inrp_en << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_config_unpack(uint8_t* pin_is_inrp_src, uint8_t* ext_inrp_sense_5, uint8_t* ext_inrp_sense_4, uint8_t* ext_inrp_sense_3, uint8_t* ext_inrp_sense_2, uint8_t* ext_inrp_sense_1, uint8_t* ext_inrp_sense_0, uint8_t* ext_inrp_en)
{
    _T_SYSC_AWO_EXT_INRP_CONFIG localVal = hwp_sysc_awo->ext_inrp_config;

    *pin_is_inrp_src = localVal.bit_field.pin_is_inrp_src;
    *ext_inrp_sense_5 = localVal.bit_field.ext_inrp_sense_5;
    *ext_inrp_sense_4 = localVal.bit_field.ext_inrp_sense_4;
    *ext_inrp_sense_3 = localVal.bit_field.ext_inrp_sense_3;
    *ext_inrp_sense_2 = localVal.bit_field.ext_inrp_sense_2;
    *ext_inrp_sense_1 = localVal.bit_field.ext_inrp_sense_1;
    *ext_inrp_sense_0 = localVal.bit_field.ext_inrp_sense_0;
    *ext_inrp_en = localVal.bit_field.ext_inrp_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_pin_is_inrp_src_getf(void)
{
    return hwp_sysc_awo->ext_inrp_config.bit_field.pin_is_inrp_src;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pin_is_inrp_src_setf(uint8_t pin_is_inrp_src)
{
    hwp_sysc_awo->ext_inrp_config.bit_field.pin_is_inrp_src = pin_is_inrp_src;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_ext_inrp_sense_5_getf(void)
{
    return hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_sense_5_setf(uint8_t ext_inrp_sense_5)
{
    hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_5 = ext_inrp_sense_5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_ext_inrp_sense_4_getf(void)
{
    return hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_sense_4_setf(uint8_t ext_inrp_sense_4)
{
    hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_4 = ext_inrp_sense_4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_ext_inrp_sense_3_getf(void)
{
    return hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_sense_3_setf(uint8_t ext_inrp_sense_3)
{
    hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_3 = ext_inrp_sense_3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_ext_inrp_sense_2_getf(void)
{
    return hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_sense_2_setf(uint8_t ext_inrp_sense_2)
{
    hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_2 = ext_inrp_sense_2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_ext_inrp_sense_1_getf(void)
{
    return hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_sense_1_setf(uint8_t ext_inrp_sense_1)
{
    hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_1 = ext_inrp_sense_1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_ext_inrp_sense_0_getf(void)
{
    return hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_sense_0_setf(uint8_t ext_inrp_sense_0)
{
    hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_sense_0 = ext_inrp_sense_0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_ext_inrp_en_getf(void)
{
    return hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_en_setf(uint8_t ext_inrp_en)
{
    hwp_sysc_awo->ext_inrp_config.bit_field.ext_inrp_en = ext_inrp_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_ext_inrp_value_get(void)
{
    return hwp_sysc_awo->ext_inrp_value.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_value_unpack(uint8_t* ext_rawinrp_value, uint8_t* ext_inrp_value_r)
{
    _T_SYSC_AWO_EXT_INRP_VALUE localVal = hwp_sysc_awo->ext_inrp_value;

    *ext_rawinrp_value = localVal.bit_field.ext_rawinrp_value;
    *ext_inrp_value_r = localVal.bit_field.ext_inrp_value_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_ext_rawinrp_value_getf(void)
{
    return hwp_sysc_awo->ext_inrp_value.bit_field.ext_rawinrp_value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_ext_inrp_value_r_getf(void)
{
    return hwp_sysc_awo->ext_inrp_value.bit_field.ext_inrp_value_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_ext_inrp_clr_get(void)
{
    return hwp_sysc_awo->ext_inrp_clr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_clr_set(uint32_t value)
{
    hwp_sysc_awo->ext_inrp_clr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ext_inrp_clr_pack(uint8_t ext_inrp_clr_r)
{
    hwp_sysc_awo->ext_inrp_clr.val = (((uint32_t)ext_inrp_clr_r << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_blelp_inrp_value_get(void)
{
    return hwp_sysc_awo->blelp_inrp_value.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_blelp_inrp_value_unpack(uint8_t* blelp_rawinrp_value, uint8_t* blelp_inrp_value_r)
{
    _T_SYSC_AWO_BLELP_INRP_VALUE localVal = hwp_sysc_awo->blelp_inrp_value;

    *blelp_rawinrp_value = localVal.bit_field.blelp_rawinrp_value;
    *blelp_inrp_value_r = localVal.bit_field.blelp_inrp_value_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_blelp_rawinrp_value_getf(void)
{
    return hwp_sysc_awo->blelp_inrp_value.bit_field.blelp_rawinrp_value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_blelp_inrp_value_r_getf(void)
{
    return hwp_sysc_awo->blelp_inrp_value.bit_field.blelp_inrp_value_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_blelp_inrp_clr_get(void)
{
    return hwp_sysc_awo->blelp_inrp_clr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_blelp_inrp_clr_set(uint32_t value)
{
    hwp_sysc_awo->blelp_inrp_clr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_blelp_inrp_clr_pack(uint8_t blelp_inrp_clr_r)
{
    hwp_sysc_awo->blelp_inrp_clr.val = (((uint32_t)blelp_inrp_clr_r << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_clkgen_awo_signal_1_get(void)
{
    return hwp_sysc_awo->clkgen_awo_signal_1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clkgen_awo_signal_1_set(uint32_t value)
{
    hwp_sysc_awo->clkgen_awo_signal_1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clkgen_awo_signal_1_pack(uint8_t clk_div_ble_mac_para_up, uint8_t clk_div_pbus_para_up)
{
    hwp_sysc_awo->clkgen_awo_signal_1.val = (((uint32_t)clk_div_ble_mac_para_up << 1) | ((uint32_t)clk_div_pbus_para_up << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_clkgen_awo_signal_2_get(void)
{
    return hwp_sysc_awo->clkgen_awo_signal_2.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clkgen_awo_signal_2_set(uint32_t value)
{
    hwp_sysc_awo->clkgen_awo_signal_2.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clkgen_awo_signal_2_pack(uint8_t clk_sel_ble_mac_by_hw, uint8_t clk_div_ble_mac_para1_m1, uint8_t clk_div_ble_mac_para0_m1, uint8_t clk_div_ble_mdm_rx_para_m1, uint8_t clk_sel_ble_mdm_rx_by_hw, uint8_t clk_sel_ble_mdm_rx_sw, uint8_t clk_sel_ble_mac)
{
    hwp_sysc_awo->clkgen_awo_signal_2.val = (((uint32_t)clk_sel_ble_mac_by_hw << 16) | ((uint32_t)clk_div_ble_mac_para1_m1 << 12) | ((uint32_t)clk_div_ble_mac_para0_m1 << 8) | ((uint32_t)clk_div_ble_mdm_rx_para_m1 << 5) | ((uint32_t)clk_sel_ble_mdm_rx_by_hw << 4) | ((uint32_t)clk_sel_ble_mdm_rx_sw << 1) | ((uint32_t)clk_sel_ble_mac << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clkgen_awo_signal_2_unpack(uint8_t* clk_sel_ble_mac_by_hw, uint8_t* clk_div_ble_mac_para1_m1, uint8_t* clk_div_ble_mac_para0_m1, uint8_t* clk_div_ble_mdm_rx_para_m1, uint8_t* clk_sel_ble_mdm_rx_by_hw, uint8_t* clk_sel_ble_mdm_rx_sw, uint8_t* clk_sel_ble_mac)
{
    _T_SYSC_AWO_CLKGEN_AWO_SIGNAL_2 localVal = hwp_sysc_awo->clkgen_awo_signal_2;

    *clk_sel_ble_mac_by_hw = localVal.bit_field.clk_sel_ble_mac_by_hw;
    *clk_div_ble_mac_para1_m1 = localVal.bit_field.clk_div_ble_mac_para1_m1;
    *clk_div_ble_mac_para0_m1 = localVal.bit_field.clk_div_ble_mac_para0_m1;
    *clk_div_ble_mdm_rx_para_m1 = localVal.bit_field.clk_div_ble_mdm_rx_para_m1;
    *clk_sel_ble_mdm_rx_by_hw = localVal.bit_field.clk_sel_ble_mdm_rx_by_hw;
    *clk_sel_ble_mdm_rx_sw = localVal.bit_field.clk_sel_ble_mdm_rx_sw;
    *clk_sel_ble_mac = localVal.bit_field.clk_sel_ble_mac;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_clk_sel_ble_mac_by_hw_getf(void)
{
    return hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_sel_ble_mac_by_hw;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clk_sel_ble_mac_by_hw_setf(uint8_t clk_sel_ble_mac_by_hw)
{
    hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_sel_ble_mac_by_hw = clk_sel_ble_mac_by_hw;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_clk_div_ble_mac_para1_m1_getf(void)
{
    return hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_div_ble_mac_para1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clk_div_ble_mac_para1_m1_setf(uint8_t clk_div_ble_mac_para1_m1)
{
    hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_div_ble_mac_para1_m1 = clk_div_ble_mac_para1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_clk_div_ble_mac_para0_m1_getf(void)
{
    return hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_div_ble_mac_para0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clk_div_ble_mac_para0_m1_setf(uint8_t clk_div_ble_mac_para0_m1)
{
    hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_div_ble_mac_para0_m1 = clk_div_ble_mac_para0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_clk_div_ble_mdm_rx_para_m1_getf(void)
{
    return hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_div_ble_mdm_rx_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clk_div_ble_mdm_rx_para_m1_setf(uint8_t clk_div_ble_mdm_rx_para_m1)
{
    hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_div_ble_mdm_rx_para_m1 = clk_div_ble_mdm_rx_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_clk_sel_ble_mdm_rx_by_hw_getf(void)
{
    return hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_sel_ble_mdm_rx_by_hw;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clk_sel_ble_mdm_rx_by_hw_setf(uint8_t clk_sel_ble_mdm_rx_by_hw)
{
    hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_sel_ble_mdm_rx_by_hw = clk_sel_ble_mdm_rx_by_hw;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_clk_sel_ble_mdm_rx_sw_getf(void)
{
    return hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_sel_ble_mdm_rx_sw;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clk_sel_ble_mdm_rx_sw_setf(uint8_t clk_sel_ble_mdm_rx_sw)
{
    hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_sel_ble_mdm_rx_sw = clk_sel_ble_mdm_rx_sw;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_clk_sel_ble_mac_getf(void)
{
    return hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_sel_ble_mac;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_clk_sel_ble_mac_setf(uint8_t clk_sel_ble_mac)
{
    hwp_sysc_awo->clkgen_awo_signal_2.bit_field.clk_sel_ble_mac = clk_sel_ble_mac;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_awo_reset_signal_get(void)
{
    return hwp_sysc_awo->awo_reset_signal.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_awo_reset_signal_set(uint32_t value)
{
    hwp_sysc_awo->awo_reset_signal.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_awo_reset_signal_pack(uint8_t srst_touch_n_clr, uint8_t srst_touch_n_set, uint8_t srst_ble_n_clr, uint8_t srst_ble_n_set, uint8_t srst_rtc_n_clr, uint8_t srst_rtc_n_set, uint8_t srst_ble_lp_n_clr, uint8_t srst_ble_lp_n_set, uint8_t srst_all_n_clr, uint8_t srst_all_n_set)
{
    hwp_sysc_awo->awo_reset_signal.val = (((uint32_t)srst_touch_n_clr << 9) | ((uint32_t)srst_touch_n_set << 8) | ((uint32_t)srst_ble_n_clr << 7) | ((uint32_t)srst_ble_n_set << 6) | ((uint32_t)srst_rtc_n_clr << 5) | ((uint32_t)srst_rtc_n_set << 4) | ((uint32_t)srst_ble_lp_n_clr << 3) | ((uint32_t)srst_ble_lp_n_set << 2) | ((uint32_t)srst_all_n_clr << 1) | ((uint32_t)srst_all_n_set << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_ram_parameter_get(void)
{
    return hwp_sysc_awo->ram_parameter.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ram_parameter_set(uint32_t value)
{
    hwp_sysc_awo->ram_parameter.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ram_parameter_pack(uint8_t r_ram_rme, uint8_t r_ram_rm, uint8_t r_ram_wa, uint8_t r_ram_ra, uint8_t r_ram_wpulse)
{
    hwp_sysc_awo->ram_parameter.val = (((uint32_t)r_ram_rme << 12) | ((uint32_t)r_ram_rm << 8) | ((uint32_t)r_ram_wa << 5) | ((uint32_t)r_ram_ra << 3) | ((uint32_t)r_ram_wpulse << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_ram_parameter_unpack(uint8_t* o_ram_rme, uint8_t* o_ram_rm, uint8_t* o_ram_wa, uint8_t* o_ram_ra, uint8_t* o_ram_wpulse, uint8_t* r_ram_rme, uint8_t* r_ram_rm, uint8_t* r_ram_wa, uint8_t* r_ram_ra, uint8_t* r_ram_wpulse)
{
    _T_SYSC_AWO_RAM_PARAMETER localVal = hwp_sysc_awo->ram_parameter;

    *o_ram_rme = localVal.bit_field.o_ram_rme;
    *o_ram_rm = localVal.bit_field.o_ram_rm;
    *o_ram_wa = localVal.bit_field.o_ram_wa;
    *o_ram_ra = localVal.bit_field.o_ram_ra;
    *o_ram_wpulse = localVal.bit_field.o_ram_wpulse;
    *r_ram_rme = localVal.bit_field.r_ram_rme;
    *r_ram_rm = localVal.bit_field.r_ram_rm;
    *r_ram_wa = localVal.bit_field.r_ram_wa;
    *r_ram_ra = localVal.bit_field.r_ram_ra;
    *r_ram_wpulse = localVal.bit_field.r_ram_wpulse;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ram_rme_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.o_ram_rme;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ram_rm_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.o_ram_rm;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ram_wa_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.o_ram_wa;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ram_ra_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.o_ram_ra;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_ram_wpulse_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.o_ram_wpulse;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_r_ram_rme_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.r_ram_rme;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_r_ram_rme_setf(uint8_t r_ram_rme)
{
    hwp_sysc_awo->ram_parameter.bit_field.r_ram_rme = r_ram_rme;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_r_ram_rm_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.r_ram_rm;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_r_ram_rm_setf(uint8_t r_ram_rm)
{
    hwp_sysc_awo->ram_parameter.bit_field.r_ram_rm = r_ram_rm;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_r_ram_wa_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.r_ram_wa;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_r_ram_wa_setf(uint8_t r_ram_wa)
{
    hwp_sysc_awo->ram_parameter.bit_field.r_ram_wa = r_ram_wa;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_r_ram_ra_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.r_ram_ra;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_r_ram_ra_setf(uint8_t r_ram_ra)
{
    hwp_sysc_awo->ram_parameter.bit_field.r_ram_ra = r_ram_ra;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_r_ram_wpulse_getf(void)
{
    return hwp_sysc_awo->ram_parameter.bit_field.r_ram_wpulse;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_r_ram_wpulse_setf(uint8_t r_ram_wpulse)
{
    hwp_sysc_awo->ram_parameter.bit_field.r_ram_wpulse = r_ram_wpulse;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_vdd_value_get(void)
{
    return hwp_sysc_awo->vdd_value.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_vdd_value_set(uint32_t value)
{
    hwp_sysc_awo->vdd_value.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_vdd_value_pack(uint8_t r_vdd_value)
{
    hwp_sysc_awo->vdd_value.val = (((uint32_t)r_vdd_value << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_vdd_value_unpack(uint8_t* o_vdd_value, uint8_t* r_vdd_value)
{
    _T_SYSC_AWO_VDD_VALUE localVal = hwp_sysc_awo->vdd_value;

    *o_vdd_value = localVal.bit_field.o_vdd_value;
    *r_vdd_value = localVal.bit_field.r_vdd_value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_o_vdd_value_getf(void)
{
    return hwp_sysc_awo->vdd_value.bit_field.o_vdd_value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_r_vdd_value_getf(void)
{
    return hwp_sysc_awo->vdd_value.bit_field.r_vdd_value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_r_vdd_value_setf(uint8_t r_vdd_value)
{
    hwp_sysc_awo->vdd_value.bit_field.r_vdd_value = r_vdd_value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_gpio_ds0_get(void)
{
    return hwp_sysc_awo->gpio_ds0.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ds0_set(uint32_t value)
{
    hwp_sysc_awo->gpio_ds0.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ds0_pack(uint32_t o_gpio_ds0)
{
    hwp_sysc_awo->gpio_ds0.val = (((uint32_t)o_gpio_ds0 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ds0_unpack(uint32_t* o_gpio_ds0)
{
    _T_SYSC_AWO_GPIO_DS0 localVal = hwp_sysc_awo->gpio_ds0;

    *o_gpio_ds0 = localVal.bit_field.o_gpio_ds0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_o_gpio_ds0_getf(void)
{
    return hwp_sysc_awo->gpio_ds0.bit_field.o_gpio_ds0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_gpio_ds0_setf(uint32_t o_gpio_ds0)
{
    hwp_sysc_awo->gpio_ds0.bit_field.o_gpio_ds0 = o_gpio_ds0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_gpio_ds1_get(void)
{
    return hwp_sysc_awo->gpio_ds1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ds1_set(uint32_t value)
{
    hwp_sysc_awo->gpio_ds1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ds1_pack(uint32_t o_gpio_ds1)
{
    hwp_sysc_awo->gpio_ds1.val = (((uint32_t)o_gpio_ds1 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ds1_unpack(uint32_t* o_gpio_ds1)
{
    _T_SYSC_AWO_GPIO_DS1 localVal = hwp_sysc_awo->gpio_ds1;

    *o_gpio_ds1 = localVal.bit_field.o_gpio_ds1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_o_gpio_ds1_getf(void)
{
    return hwp_sysc_awo->gpio_ds1.bit_field.o_gpio_ds1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_gpio_ds1_setf(uint32_t o_gpio_ds1)
{
    hwp_sysc_awo->gpio_ds1.bit_field.o_gpio_ds1 = o_gpio_ds1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_gpio_ie_get(void)
{
    return hwp_sysc_awo->gpio_ie.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ie_set(uint32_t value)
{
    hwp_sysc_awo->gpio_ie.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ie_pack(uint32_t o_gpio_ie)
{
    hwp_sysc_awo->gpio_ie.val = (((uint32_t)o_gpio_ie << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ie_unpack(uint32_t* o_gpio_ie)
{
    _T_SYSC_AWO_GPIO_IE localVal = hwp_sysc_awo->gpio_ie;

    *o_gpio_ie = localVal.bit_field.o_gpio_ie;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_o_gpio_ie_getf(void)
{
    return hwp_sysc_awo->gpio_ie.bit_field.o_gpio_ie;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_gpio_ie_setf(uint32_t o_gpio_ie)
{
    hwp_sysc_awo->gpio_ie.bit_field.o_gpio_ie = o_gpio_ie;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_gpio_is_get(void)
{
    return hwp_sysc_awo->gpio_is.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_is_set(uint32_t value)
{
    hwp_sysc_awo->gpio_is.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_is_pack(uint32_t o_gpio_is)
{
    hwp_sysc_awo->gpio_is.val = (((uint32_t)o_gpio_is << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_is_unpack(uint32_t* o_gpio_is)
{
    _T_SYSC_AWO_GPIO_IS localVal = hwp_sysc_awo->gpio_is;

    *o_gpio_is = localVal.bit_field.o_gpio_is;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_o_gpio_is_getf(void)
{
    return hwp_sysc_awo->gpio_is.bit_field.o_gpio_is;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_gpio_is_setf(uint32_t o_gpio_is)
{
    hwp_sysc_awo->gpio_is.bit_field.o_gpio_is = o_gpio_is;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_gpio_pe_get(void)
{
    return hwp_sysc_awo->gpio_pe.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_pe_set(uint32_t value)
{
    hwp_sysc_awo->gpio_pe.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_pe_pack(uint32_t o_gpio_pe)
{
    hwp_sysc_awo->gpio_pe.val = (((uint32_t)o_gpio_pe << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_pe_unpack(uint32_t* o_gpio_pe)
{
    _T_SYSC_AWO_GPIO_PE localVal = hwp_sysc_awo->gpio_pe;

    *o_gpio_pe = localVal.bit_field.o_gpio_pe;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_o_gpio_pe_getf(void)
{
    return hwp_sysc_awo->gpio_pe.bit_field.o_gpio_pe;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_gpio_pe_setf(uint32_t o_gpio_pe)
{
    hwp_sysc_awo->gpio_pe.bit_field.o_gpio_pe = o_gpio_pe;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_gpio_ps_get(void)
{
    return hwp_sysc_awo->gpio_ps.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ps_set(uint32_t value)
{
    hwp_sysc_awo->gpio_ps.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ps_pack(uint32_t o_gpio_ps)
{
    hwp_sysc_awo->gpio_ps.val = (((uint32_t)o_gpio_ps << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_gpio_ps_unpack(uint32_t* o_gpio_ps)
{
    _T_SYSC_AWO_GPIO_PS localVal = hwp_sysc_awo->gpio_ps;

    *o_gpio_ps = localVal.bit_field.o_gpio_ps;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_o_gpio_ps_getf(void)
{
    return hwp_sysc_awo->gpio_ps.bit_field.o_gpio_ps;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_o_gpio_ps_setf(uint32_t o_gpio_ps)
{
    hwp_sysc_awo->gpio_ps.bit_field.o_gpio_ps = o_gpio_ps;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_touch_cfg_1_get(void)
{
    return hwp_sysc_awo->touch_cfg_1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_cfg_1_set(uint32_t value)
{
    hwp_sysc_awo->touch_cfg_1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_cfg_1_pack(uint8_t touch_en, uint8_t rcosc_16m_dly, uint16_t touch_itv)
{
    hwp_sysc_awo->touch_cfg_1.val = (((uint32_t)touch_en << 20) | ((uint32_t)rcosc_16m_dly << 16) | ((uint32_t)touch_itv << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_cfg_1_unpack(uint8_t* touch_en, uint8_t* rcosc_16m_dly, uint16_t* touch_itv)
{
    _T_SYSC_AWO_TOUCH_CFG_1 localVal = hwp_sysc_awo->touch_cfg_1;

    *touch_en = localVal.bit_field.touch_en;
    *rcosc_16m_dly = localVal.bit_field.rcosc_16m_dly;
    *touch_itv = localVal.bit_field.touch_itv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_touch_en_getf(void)
{
    return hwp_sysc_awo->touch_cfg_1.bit_field.touch_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_en_setf(uint8_t touch_en)
{
    hwp_sysc_awo->touch_cfg_1.bit_field.touch_en = touch_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_rcosc_16m_dly_getf(void)
{
    return hwp_sysc_awo->touch_cfg_1.bit_field.rcosc_16m_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rcosc_16m_dly_setf(uint8_t rcosc_16m_dly)
{
    hwp_sysc_awo->touch_cfg_1.bit_field.rcosc_16m_dly = rcosc_16m_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t sysc_awo_touch_itv_getf(void)
{
    return hwp_sysc_awo->touch_cfg_1.bit_field.touch_itv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_itv_setf(uint16_t touch_itv)
{
    hwp_sysc_awo->touch_cfg_1.bit_field.touch_itv = touch_itv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_touch_cfg_2_get(void)
{
    return hwp_sysc_awo->touch_cfg_2.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_cfg_2_set(uint32_t value)
{
    hwp_sysc_awo->touch_cfg_2.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_cfg_2_pack(uint8_t touch_scan_num, uint8_t touch_scan_dly)
{
    hwp_sysc_awo->touch_cfg_2.val = (((uint32_t)touch_scan_num << 8) | ((uint32_t)touch_scan_dly << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_cfg_2_unpack(uint8_t* touch_scan_num, uint8_t* touch_scan_dly)
{
    _T_SYSC_AWO_TOUCH_CFG_2 localVal = hwp_sysc_awo->touch_cfg_2;

    *touch_scan_num = localVal.bit_field.touch_scan_num;
    *touch_scan_dly = localVal.bit_field.touch_scan_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_touch_scan_num_getf(void)
{
    return hwp_sysc_awo->touch_cfg_2.bit_field.touch_scan_num;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_scan_num_setf(uint8_t touch_scan_num)
{
    hwp_sysc_awo->touch_cfg_2.bit_field.touch_scan_num = touch_scan_num;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_touch_scan_dly_getf(void)
{
    return hwp_sysc_awo->touch_cfg_2.bit_field.touch_scan_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_scan_dly_setf(uint8_t touch_scan_dly)
{
    hwp_sysc_awo->touch_cfg_2.bit_field.touch_scan_dly = touch_scan_dly;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_touch_cfg_3_get(void)
{
    return hwp_sysc_awo->touch_cfg_3.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_cfg_3_set(uint32_t value)
{
    hwp_sysc_awo->touch_cfg_3.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_cfg_3_pack(uint32_t touch_thr)
{
    hwp_sysc_awo->touch_cfg_3.val = (((uint32_t)touch_thr << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_cfg_3_unpack(uint32_t* touch_thr)
{
    _T_SYSC_AWO_TOUCH_CFG_3 localVal = hwp_sysc_awo->touch_cfg_3;

    *touch_thr = localVal.bit_field.touch_thr;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_touch_thr_getf(void)
{
    return hwp_sysc_awo->touch_cfg_3.bit_field.touch_thr;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_touch_thr_setf(uint32_t touch_thr)
{
    hwp_sysc_awo->touch_cfg_3.bit_field.touch_thr = touch_thr;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_0_get(void)
{
    return hwp_sysc_awo->rf_reg_0.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_0_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_0.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_0_pack(uint32_t rf_reg_0)
{
    hwp_sysc_awo->rf_reg_0.val = (((uint32_t)rf_reg_0 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_0_unpack(uint32_t* rf_reg_0)
{
    _T_SYSC_AWO_RF_REG_0 localVal = hwp_sysc_awo->rf_reg_0;

    *rf_reg_0 = localVal.bit_field.rf_reg_0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_0_getf(void)
{
    return hwp_sysc_awo->rf_reg_0.bit_field.rf_reg_0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_0_setf(uint32_t rf_reg_0)
{
    hwp_sysc_awo->rf_reg_0.bit_field.rf_reg_0 = rf_reg_0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_1_get(void)
{
    return hwp_sysc_awo->rf_reg_1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_1_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_1_pack(uint32_t rf_reg_1)
{
    hwp_sysc_awo->rf_reg_1.val = (((uint32_t)rf_reg_1 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_1_unpack(uint32_t* rf_reg_1)
{
    _T_SYSC_AWO_RF_REG_1 localVal = hwp_sysc_awo->rf_reg_1;

    *rf_reg_1 = localVal.bit_field.rf_reg_1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_1_getf(void)
{
    return hwp_sysc_awo->rf_reg_1.bit_field.rf_reg_1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_1_setf(uint32_t rf_reg_1)
{
    hwp_sysc_awo->rf_reg_1.bit_field.rf_reg_1 = rf_reg_1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_2_get(void)
{
    return hwp_sysc_awo->rf_reg_2.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_2_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_2.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_2_pack(uint32_t rf_reg_2)
{
    hwp_sysc_awo->rf_reg_2.val = (((uint32_t)rf_reg_2 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_2_unpack(uint32_t* rf_reg_2)
{
    _T_SYSC_AWO_RF_REG_2 localVal = hwp_sysc_awo->rf_reg_2;

    *rf_reg_2 = localVal.bit_field.rf_reg_2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_2_getf(void)
{
    return hwp_sysc_awo->rf_reg_2.bit_field.rf_reg_2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_2_setf(uint32_t rf_reg_2)
{
    hwp_sysc_awo->rf_reg_2.bit_field.rf_reg_2 = rf_reg_2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_3_get(void)
{
    return hwp_sysc_awo->rf_reg_3.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_3_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_3.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_3_pack(uint32_t rf_reg_3)
{
    hwp_sysc_awo->rf_reg_3.val = (((uint32_t)rf_reg_3 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_3_unpack(uint32_t* rf_reg_3)
{
    _T_SYSC_AWO_RF_REG_3 localVal = hwp_sysc_awo->rf_reg_3;

    *rf_reg_3 = localVal.bit_field.rf_reg_3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_3_getf(void)
{
    return hwp_sysc_awo->rf_reg_3.bit_field.rf_reg_3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_3_setf(uint32_t rf_reg_3)
{
    hwp_sysc_awo->rf_reg_3.bit_field.rf_reg_3 = rf_reg_3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_4_get(void)
{
    return hwp_sysc_awo->rf_reg_4.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_4_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_4.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_4_pack(uint32_t rf_reg_4)
{
    hwp_sysc_awo->rf_reg_4.val = (((uint32_t)rf_reg_4 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_4_unpack(uint32_t* rf_reg_4)
{
    _T_SYSC_AWO_RF_REG_4 localVal = hwp_sysc_awo->rf_reg_4;

    *rf_reg_4 = localVal.bit_field.rf_reg_4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_4_getf(void)
{
    return hwp_sysc_awo->rf_reg_4.bit_field.rf_reg_4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_4_setf(uint32_t rf_reg_4)
{
    hwp_sysc_awo->rf_reg_4.bit_field.rf_reg_4 = rf_reg_4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_5_get(void)
{
    return hwp_sysc_awo->rf_reg_5.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_5_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_5.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_5_pack(uint32_t rf_reg_5)
{
    hwp_sysc_awo->rf_reg_5.val = (((uint32_t)rf_reg_5 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_5_unpack(uint32_t* rf_reg_5)
{
    _T_SYSC_AWO_RF_REG_5 localVal = hwp_sysc_awo->rf_reg_5;

    *rf_reg_5 = localVal.bit_field.rf_reg_5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_5_getf(void)
{
    return hwp_sysc_awo->rf_reg_5.bit_field.rf_reg_5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_5_setf(uint32_t rf_reg_5)
{
    hwp_sysc_awo->rf_reg_5.bit_field.rf_reg_5 = rf_reg_5;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_6_get(void)
{
    return hwp_sysc_awo->rf_reg_6.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_6_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_6.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_6_pack(uint32_t rf_reg_6)
{
    hwp_sysc_awo->rf_reg_6.val = (((uint32_t)rf_reg_6 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_6_unpack(uint32_t* rf_reg_6)
{
    _T_SYSC_AWO_RF_REG_6 localVal = hwp_sysc_awo->rf_reg_6;

    *rf_reg_6 = localVal.bit_field.rf_reg_6;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_6_getf(void)
{
    return hwp_sysc_awo->rf_reg_6.bit_field.rf_reg_6;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_6_setf(uint32_t rf_reg_6)
{
    hwp_sysc_awo->rf_reg_6.bit_field.rf_reg_6 = rf_reg_6;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_7_get(void)
{
    return hwp_sysc_awo->rf_reg_7.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_7_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_7.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_7_pack(uint32_t rf_reg_7)
{
    hwp_sysc_awo->rf_reg_7.val = (((uint32_t)rf_reg_7 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_7_unpack(uint32_t* rf_reg_7)
{
    _T_SYSC_AWO_RF_REG_7 localVal = hwp_sysc_awo->rf_reg_7;

    *rf_reg_7 = localVal.bit_field.rf_reg_7;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_7_getf(void)
{
    return hwp_sysc_awo->rf_reg_7.bit_field.rf_reg_7;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_7_setf(uint32_t rf_reg_7)
{
    hwp_sysc_awo->rf_reg_7.bit_field.rf_reg_7 = rf_reg_7;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_8_get(void)
{
    return hwp_sysc_awo->rf_reg_8.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_8_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_8.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_8_pack(uint32_t rf_reg_8)
{
    hwp_sysc_awo->rf_reg_8.val = (((uint32_t)rf_reg_8 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_8_unpack(uint32_t* rf_reg_8)
{
    _T_SYSC_AWO_RF_REG_8 localVal = hwp_sysc_awo->rf_reg_8;

    *rf_reg_8 = localVal.bit_field.rf_reg_8;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_8_getf(void)
{
    return hwp_sysc_awo->rf_reg_8.bit_field.rf_reg_8;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_8_setf(uint32_t rf_reg_8)
{
    hwp_sysc_awo->rf_reg_8.bit_field.rf_reg_8 = rf_reg_8;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_9_get(void)
{
    return hwp_sysc_awo->rf_reg_9.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_9_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_9.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_9_pack(uint32_t rf_reg_9)
{
    hwp_sysc_awo->rf_reg_9.val = (((uint32_t)rf_reg_9 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_9_unpack(uint32_t* rf_reg_9)
{
    _T_SYSC_AWO_RF_REG_9 localVal = hwp_sysc_awo->rf_reg_9;

    *rf_reg_9 = localVal.bit_field.rf_reg_9;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_9_getf(void)
{
    return hwp_sysc_awo->rf_reg_9.bit_field.rf_reg_9;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_9_setf(uint32_t rf_reg_9)
{
    hwp_sysc_awo->rf_reg_9.bit_field.rf_reg_9 = rf_reg_9;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_a_get(void)
{
    return hwp_sysc_awo->rf_reg_a.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_a_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_a.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_a_pack(uint32_t rf_reg_a)
{
    hwp_sysc_awo->rf_reg_a.val = (((uint32_t)rf_reg_a << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_a_unpack(uint32_t* rf_reg_a)
{
    _T_SYSC_AWO_RF_REG_A localVal = hwp_sysc_awo->rf_reg_a;

    *rf_reg_a = localVal.bit_field.rf_reg_a;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_a_getf(void)
{
    return hwp_sysc_awo->rf_reg_a.bit_field.rf_reg_a;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_a_setf(uint32_t rf_reg_a)
{
    hwp_sysc_awo->rf_reg_a.bit_field.rf_reg_a = rf_reg_a;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_b_get(void)
{
    return hwp_sysc_awo->rf_reg_b.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_b_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_b.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_b_pack(uint32_t rf_reg_b)
{
    hwp_sysc_awo->rf_reg_b.val = (((uint32_t)rf_reg_b << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_b_unpack(uint32_t* rf_reg_b)
{
    _T_SYSC_AWO_RF_REG_B localVal = hwp_sysc_awo->rf_reg_b;

    *rf_reg_b = localVal.bit_field.rf_reg_b;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_b_getf(void)
{
    return hwp_sysc_awo->rf_reg_b.bit_field.rf_reg_b;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_b_setf(uint32_t rf_reg_b)
{
    hwp_sysc_awo->rf_reg_b.bit_field.rf_reg_b = rf_reg_b;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_c_get(void)
{
    return hwp_sysc_awo->rf_reg_c.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_c_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_c.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_c_pack(uint32_t rf_reg_c)
{
    hwp_sysc_awo->rf_reg_c.val = (((uint32_t)rf_reg_c << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_c_unpack(uint32_t* rf_reg_c)
{
    _T_SYSC_AWO_RF_REG_C localVal = hwp_sysc_awo->rf_reg_c;

    *rf_reg_c = localVal.bit_field.rf_reg_c;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_c_getf(void)
{
    return hwp_sysc_awo->rf_reg_c.bit_field.rf_reg_c;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_c_setf(uint32_t rf_reg_c)
{
    hwp_sysc_awo->rf_reg_c.bit_field.rf_reg_c = rf_reg_c;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_d_get(void)
{
    return hwp_sysc_awo->rf_reg_d.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_d_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_d.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_d_pack(uint32_t rf_reg_d)
{
    hwp_sysc_awo->rf_reg_d.val = (((uint32_t)rf_reg_d << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_d_unpack(uint32_t* rf_reg_d)
{
    _T_SYSC_AWO_RF_REG_D localVal = hwp_sysc_awo->rf_reg_d;

    *rf_reg_d = localVal.bit_field.rf_reg_d;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_d_getf(void)
{
    return hwp_sysc_awo->rf_reg_d.bit_field.rf_reg_d;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_d_setf(uint32_t rf_reg_d)
{
    hwp_sysc_awo->rf_reg_d.bit_field.rf_reg_d = rf_reg_d;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_e_get(void)
{
    return hwp_sysc_awo->rf_reg_e.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_e_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_e.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_e_pack(uint32_t rf_reg_e)
{
    hwp_sysc_awo->rf_reg_e.val = (((uint32_t)rf_reg_e << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_e_unpack(uint32_t* rf_reg_e)
{
    _T_SYSC_AWO_RF_REG_E localVal = hwp_sysc_awo->rf_reg_e;

    *rf_reg_e = localVal.bit_field.rf_reg_e;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_e_getf(void)
{
    return hwp_sysc_awo->rf_reg_e.bit_field.rf_reg_e;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_e_setf(uint32_t rf_reg_e)
{
    hwp_sysc_awo->rf_reg_e.bit_field.rf_reg_e = rf_reg_e;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_f_get(void)
{
    return hwp_sysc_awo->rf_reg_f.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_f_set(uint32_t value)
{
    hwp_sysc_awo->rf_reg_f.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_f_pack(uint32_t rf_reg_f)
{
    hwp_sysc_awo->rf_reg_f.val = (((uint32_t)rf_reg_f << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_f_unpack(uint32_t* rf_reg_f)
{
    _T_SYSC_AWO_RF_REG_F localVal = hwp_sysc_awo->rf_reg_f;

    *rf_reg_f = localVal.bit_field.rf_reg_f;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_f_getf(void)
{
    return hwp_sysc_awo->rf_reg_f.bit_field.rf_reg_f;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_f_setf(uint32_t rf_reg_f)
{
    hwp_sysc_awo->rf_reg_f.bit_field.rf_reg_f = rf_reg_f;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_rf_reg_rd_get(void)
{
    return hwp_sysc_awo->rf_reg_rd.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_rf_reg_rd_unpack(uint32_t* i_rf_reg_ro)
{
    _T_SYSC_AWO_RF_REG_RD localVal = hwp_sysc_awo->rf_reg_rd;

    *i_rf_reg_ro = localVal.bit_field.i_rf_reg_ro;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_i_rf_reg_ro_getf(void)
{
    return hwp_sysc_awo->rf_reg_rd.bit_field.i_rf_reg_ro;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_pwr_pwm0_get(void)
{
    return hwp_sysc_awo->pwr_pwm0.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm0_set(uint32_t value)
{
    hwp_sysc_awo->pwr_pwm0.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm0_pack(uint16_t pwm0_wid_h, uint16_t pwm0_wid_l)
{
    hwp_sysc_awo->pwr_pwm0.val = (((uint32_t)pwm0_wid_h << 16) | ((uint32_t)pwm0_wid_l << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm0_unpack(uint16_t* pwm0_wid_h, uint16_t* pwm0_wid_l)
{
    _T_SYSC_AWO_PWR_PWM0 localVal = hwp_sysc_awo->pwr_pwm0;

    *pwm0_wid_h = localVal.bit_field.pwm0_wid_h;
    *pwm0_wid_l = localVal.bit_field.pwm0_wid_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t sysc_awo_pwm0_wid_h_getf(void)
{
    return hwp_sysc_awo->pwr_pwm0.bit_field.pwm0_wid_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm0_wid_h_setf(uint16_t pwm0_wid_h)
{
    hwp_sysc_awo->pwr_pwm0.bit_field.pwm0_wid_h = pwm0_wid_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t sysc_awo_pwm0_wid_l_getf(void)
{
    return hwp_sysc_awo->pwr_pwm0.bit_field.pwm0_wid_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm0_wid_l_setf(uint16_t pwm0_wid_l)
{
    hwp_sysc_awo->pwr_pwm0.bit_field.pwm0_wid_l = pwm0_wid_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_pwr_pwm1_get(void)
{
    return hwp_sysc_awo->pwr_pwm1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm1_set(uint32_t value)
{
    hwp_sysc_awo->pwr_pwm1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm1_pack(uint16_t pwm1_wid_h, uint16_t pwm1_wid_l)
{
    hwp_sysc_awo->pwr_pwm1.val = (((uint32_t)pwm1_wid_h << 16) | ((uint32_t)pwm1_wid_l << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm1_unpack(uint16_t* pwm1_wid_h, uint16_t* pwm1_wid_l)
{
    _T_SYSC_AWO_PWR_PWM1 localVal = hwp_sysc_awo->pwr_pwm1;

    *pwm1_wid_h = localVal.bit_field.pwm1_wid_h;
    *pwm1_wid_l = localVal.bit_field.pwm1_wid_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t sysc_awo_pwm1_wid_h_getf(void)
{
    return hwp_sysc_awo->pwr_pwm1.bit_field.pwm1_wid_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm1_wid_h_setf(uint16_t pwm1_wid_h)
{
    hwp_sysc_awo->pwr_pwm1.bit_field.pwm1_wid_h = pwm1_wid_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t sysc_awo_pwm1_wid_l_getf(void)
{
    return hwp_sysc_awo->pwr_pwm1.bit_field.pwm1_wid_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm1_wid_l_setf(uint16_t pwm1_wid_l)
{
    hwp_sysc_awo->pwr_pwm1.bit_field.pwm1_wid_l = pwm1_wid_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_pwr_pwm2_get(void)
{
    return hwp_sysc_awo->pwr_pwm2.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm2_set(uint32_t value)
{
    hwp_sysc_awo->pwr_pwm2.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm2_pack(uint16_t pwm2_wid_h, uint16_t pwm2_wid_l)
{
    hwp_sysc_awo->pwr_pwm2.val = (((uint32_t)pwm2_wid_h << 16) | ((uint32_t)pwm2_wid_l << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm2_unpack(uint16_t* pwm2_wid_h, uint16_t* pwm2_wid_l)
{
    _T_SYSC_AWO_PWR_PWM2 localVal = hwp_sysc_awo->pwr_pwm2;

    *pwm2_wid_h = localVal.bit_field.pwm2_wid_h;
    *pwm2_wid_l = localVal.bit_field.pwm2_wid_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t sysc_awo_pwm2_wid_h_getf(void)
{
    return hwp_sysc_awo->pwr_pwm2.bit_field.pwm2_wid_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm2_wid_h_setf(uint16_t pwm2_wid_h)
{
    hwp_sysc_awo->pwr_pwm2.bit_field.pwm2_wid_h = pwm2_wid_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t sysc_awo_pwm2_wid_l_getf(void)
{
    return hwp_sysc_awo->pwr_pwm2.bit_field.pwm2_wid_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm2_wid_l_setf(uint16_t pwm2_wid_l)
{
    hwp_sysc_awo->pwr_pwm2.bit_field.pwm2_wid_l = pwm2_wid_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_pwr_pwm_ctrl_get(void)
{
    return hwp_sysc_awo->pwr_pwm_ctrl.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm_ctrl_set(uint32_t value)
{
    hwp_sysc_awo->pwr_pwm_ctrl.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm_ctrl_pack(uint8_t pwm2_en, uint8_t pwm2_fc_h, uint8_t pwm1_en, uint8_t pwm1_fc_h, uint8_t pwm0_en, uint8_t pwm0_fc_h)
{
    hwp_sysc_awo->pwr_pwm_ctrl.val = (((uint32_t)pwm2_en << 9) | ((uint32_t)pwm2_fc_h << 8) | ((uint32_t)pwm1_en << 5) | ((uint32_t)pwm1_fc_h << 4) | ((uint32_t)pwm0_en << 1) | ((uint32_t)pwm0_fc_h << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwr_pwm_ctrl_unpack(uint8_t* pwm2_en, uint8_t* pwm2_fc_h, uint8_t* pwm1_en, uint8_t* pwm1_fc_h, uint8_t* pwm0_en, uint8_t* pwm0_fc_h)
{
    _T_SYSC_AWO_PWR_PWM_CTRL localVal = hwp_sysc_awo->pwr_pwm_ctrl;

    *pwm2_en = localVal.bit_field.pwm2_en;
    *pwm2_fc_h = localVal.bit_field.pwm2_fc_h;
    *pwm1_en = localVal.bit_field.pwm1_en;
    *pwm1_fc_h = localVal.bit_field.pwm1_fc_h;
    *pwm0_en = localVal.bit_field.pwm0_en;
    *pwm0_fc_h = localVal.bit_field.pwm0_fc_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_pwm2_en_getf(void)
{
    return hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm2_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm2_en_setf(uint8_t pwm2_en)
{
    hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm2_en = pwm2_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_pwm2_fc_h_getf(void)
{
    return hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm2_fc_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm2_fc_h_setf(uint8_t pwm2_fc_h)
{
    hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm2_fc_h = pwm2_fc_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_pwm1_en_getf(void)
{
    return hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm1_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm1_en_setf(uint8_t pwm1_en)
{
    hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm1_en = pwm1_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_pwm1_fc_h_getf(void)
{
    return hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm1_fc_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm1_fc_h_setf(uint8_t pwm1_fc_h)
{
    hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm1_fc_h = pwm1_fc_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_pwm0_en_getf(void)
{
    return hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm0_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm0_en_setf(uint8_t pwm0_en)
{
    hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm0_en = pwm0_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_pwm0_fc_h_getf(void)
{
    return hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm0_fc_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_pwm0_fc_h_setf(uint8_t pwm0_fc_h)
{
    hwp_sysc_awo->pwr_pwm_ctrl.bit_field.pwm0_fc_h = pwm0_fc_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_awo_boot_mode_get(void)
{
    return hwp_sysc_awo->boot_mode.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_awo_boot_mode_unpack(uint8_t* boot_mode_1, uint8_t* boot_mode_0)
{
    _T_SYSC_AWO_BOOT_MODE localVal = hwp_sysc_awo->boot_mode;

    *boot_mode_1 = localVal.bit_field.boot_mode_1;
    *boot_mode_0 = localVal.bit_field.boot_mode_0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_boot_mode_1_getf(void)
{
    return hwp_sysc_awo->boot_mode.bit_field.boot_mode_1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_awo_boot_mode_0_getf(void)
{
    return hwp_sysc_awo->boot_mode.bit_field.boot_mode_0;
}

#ifdef __cplusplus
}
#endif

#endif /* __REG_SYSC_AWO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

