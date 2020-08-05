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
#ifndef __AWO_H__
#define __AWO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "co_math.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_awo_apollo_00.h"

/* exported define -----------------------------------------------------------*/
///indicate bootram_init has run in bootram
#define BOOTINIT_FLAG       0x3399

///define for reg_pd_state @ awo
#define PD_SRAM0                                        CO_BIT( 0 )
#define PD_SRAM1                                        CO_BIT( 1 )
#define PD_SRAM2                                        CO_BIT( 2 )
#define PD_SRAM3                                        CO_BIT( 3 )
#define PD_SRAM4                                        CO_BIT( 4 )
#define PD_SRAM5                                        CO_BIT( 5 )
#define PD_SRAM6                                        CO_BIT( 6 )
#define PD_SRAM_ALL                                     0x7f
#define PD_BLE_MAC                                      CO_BIT( 8 )
#define PD_BLE_RF                                       CO_BIT( 9 )
#define PD_PER                                          CO_BIT( 10 )
#define PD_CPU                                          CO_BIT( 11 )

#define PD_POWER_ON                                     0
#define PD_POWER_DOWN                                   1


///define for reg_awo_clk_en @ awo
#define CLKG_BLE_LP_SET                                 CO_BIT( 0 )
#define CLKG_BLE_LP_CLR                                 CO_BIT( 1 )
#define CLKG_RTC_SET                                    CO_BIT( 2 )
#define CLKG_RTC_CLR                                    CO_BIT( 3 )
#define CLKG_HBUS_DIV_PLL_SET                           CO_BIT( 4 )
#define CLKG_HBUS_DIV_PLL_CLR                           CO_BIT( 5 )
#define CLKG_HBUS_DIV_16M_SET                           CO_BIT( 6 )
#define CLKG_HBUS_DIV_16M_CLR                           CO_BIT( 7 )
#define CLKG_WIC_SET                                    CO_BIT( 8 )
#define CLKG_WIC_CLR                                    CO_BIT( 9 )
#define CLKG_BLE_SET                                    CO_BIT( 10 )
#define CLKG_BLE_CLR                                    CO_BIT( 11 )
#define CLKG_BLE_MAC_DIV_SET                            CO_BIT( 12 )
#define CLKG_BLE_MAC_DIV_CLR                            CO_BIT( 13 )
#define CLKG_BLE_MDM_RX_DIV_SET                         CO_BIT( 14 )
#define CLKG_BLE_MDM_RX_DIV_CLR                         CO_BIT( 15 )


///define for awo_reset signal
#define SRST_ALL_SET                                    CO_BIT( 0 )
#define SRST_ALL_CLR                                    CO_BIT( 1 )
#define SRST_BLE_LP_SET                                 CO_BIT( 2 )
#define SRST_BLE_LP_CLR                                 CO_BIT( 3 )
#define SRST_RTC_SET                                    CO_BIT( 4 )
#define SRST_RTC_CLR                                    CO_BIT( 5 )
#define SRST_BLE_N_SET                                  CO_BIT( 6 )
#define SRST_BLE_N_CLR                                  CO_BIT( 7 )
#define SRST_TOUCH_N_SET                                CO_BIT( 8 )
#define SRST_TOUCH_N_CLR                                CO_BIT( 9 )

#define INT_OSE                                         CO_BIT( 0 )
#define INT_RADIO                                       CO_BIT( 1 )


///define for reg_io_state @ awo
#define IO_FROM_PINSHARE                                0
#define IO_FROM_RETENTION                               1
#define RETENTION_ENABLE                                1
#define RETENTION_DISABLE                               0

///define for reg_clk_ldo_sel @ awo
#define SEL_SIGNAL_PMU                                  0
#define SEL_SIGNAL_REG                                  1

#define REG_16M_RC_EN                                   CO_BIT( 4 )
#define REG_NORMAL_LDO                                  CO_BIT( 2 )
#define REG_PMU_LDO                                     CO_BIT( 1 )
#define REG_PMU_CLK                                     CO_BIT( 0 )

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define IO_IE_SET(mask)                                 hwp_sysc_awo->gpio_ie.val |= (mask)
#define IO_IE_CLR(mask)                                 hwp_sysc_awo->gpio_ie.val &= ~(mask)

/* exported functions --------------------------------------------------------*/

/**
 * @brief Normal settings of awo.
 * Step 1: initialize the clock of modem and mac
 * Step 2: set default parameter. Ram parameter, vdd_value, ldo setup time, pmu timer...
 * Step 3: pad settings of apollo_00
 * Step 4: set the power domain
 * Step 5: reset ble lp
 * Step 6: clear external interrupt
 * Step 7: clear ble lp interrupt
 */
void awo_init( void );
/**
 * @brief init rf settings.
 */
void rf_reg_settings( void );

/**
 * @brief awo init run in bootram. Mainly initialize the cpu clock.
 * enable 32k crystal: should wait 100ms on real chip, we use 32k rc by default, if we want to use 32k crystal we must wait 100ms.
 * step 1: select to use 32k rc or crystal
 * step 2: disable 32m rc
 * step 3: configure the clock of pbus.
 * step 4: open and set pll to the frequency we want and wait it stable.
 * step 5: set awo parameter.
 */
void awo_bootram_init( void );
/**
 * @brief configure the gpio settings.
 */
void awo_pad_setup( void );
/**
 * @brief set parameter for ram, vdd_value, ldo setup time, pmu timer ......
 */
void awo_set_parameter( void );
/**
 * @brief set the ble mac frequency. We can set two frequency to avoid harmonic.
 * Usually we use freq0, when some frequency may has harmonic ble mac frequency will change to freq1 automatically by hardware.
 * @param freq0: xx Mhz of usual frequency.
 * @param freq1: xx Mhz of frequency when meeting harmonic.
 * @param avoid_harmonic: enable or disable the function to avoid harmonic. When we don't need to avoid harmonic, only freq0 is useful.
 */
void awo_blefreq_set( uint8_t freq0, uint8_t freq1, bool avoid_harmonic );
/**
 * @brief We configure the clock of ble mac and modem.
 */
void awo_clk_gen_init( void );

/**
 * @brief pll should spend about 300us for stable. We read a rf register to confirm it is stable.
 * When the function return, pll is already stable.
 */
void awo_wait_pll_stable( void );
/**
 * @brief process to do before sleep.
 * step1: set power domain
 * step2: enable 32m rc and give right of control to pmu
 * step3: wait rc stable and clear 32M clock gate
 * step4: select rc and disable xtal
 * step5: switch to src clk_16m
 * step6: gate pll
 * step7: close pll
 */
void awo_before_sleep( void );
/**
 * @brief process to do after wakeup
 * step1: 32m rc automatically open by pmu
 * step2: enable 32m xtal and wait 32m stable
 * step3: switch to 32m xtal
 * step4: open pll and wait stable
 * step5: clear pll gate and switch to pll
 * step6: gate 32m
 */
void awo_after_sleep( void );
/**
 * @brief read wic handshake state. Wic handshake should finish before excute wfi/wfe
 * @return return 1 for handshake finish
 */
uint8_t awo_read_wicenack( void );
/**
 * @brief set the clock division for pbus.
 * @param a 4 bit parameter.
 */
void awo_clk_div_pbus_para_m1( uint8_t param );
/**
 * @brief set the clock division for pbus.
 * @param a 8 bit parameter.
 */
void awo_clk_div_hbus_para_set( uint8_t param );
/**
 * @brief enable pmu to carry out power down.
 * @param en: range from 0 to 1
 */
void awo_pmu_en( uint8_t en );
/**
 * @brief enable of ble & lp interrupt
 * @param map: bit map of interrupt
 */
void awo_blelp_intrp_en( uint8_t map );
/**
 * @brief switch to choose from 3 path(not a one hot switch). When use pll we usually set sel to 2
 * @param sel: range from 0 to 2
 */
void awo_hbus1_clksel( uint8_t sel );
/**
 * @brief one hot switch to choose from 3 path. When we set hbus directly to 32m crystal we set sel to 1
 * @param sel: choose from 1,2,4
 */
void awo_hbus0_clksel( uint8_t sel );
/**
 * @brief set and clr clock gate. Set: we have clock. Clr: we have no clock.
 * @param map: define in awo.h. use bit map to set the clock gate.
 */
void awo_clkgate_en( uint16_t map );
/**
 ****************************************************************************************
 * @brief software generate a pulse to capture I/O for retention
 ****************************************************************************************
 */
void awo_start_cap_io( void );
/**
 ****************************************************************************************
 * @brief enable i/o retention. Use this function with awo_start_cap_io together.
 * @param sel: sel = IO_FROM_RETENTION: enable retention. sel = IO_FROM_PINSHARE disable retention.
 ****************************************************************************************
 */
void awo_io_ctrl_set( uint8_t sel );
/**
 * @brief use this function to let pmu control io retention. Normally we use pmu to automatically control io retention.
 */
void awo_pmu_io_retention( void );
/**
 ****************************************************************************************
 * @brief i/o retention settings
 ****************************************************************************************
 */
void awo_io_state_set( uint8_t before_sleep, uint8_t after_sleep );
/**
 * @brief configure the power domain.
 * @param sel: input the bitmap of the absolute value.
 * @param sw: PD_POWER_ON set which power domain should power on when wakeup. PD_POWER_DOWN set which power domain should power off when sleep
 */
void awo_pd_onoff_sw( uint16_t sel, uint8_t sw );
/**
 * @brief use when we want to use software to start power on.
 */
void awo_sw_powerdown_start( void );
/**
 * @brief use when we want to use software to start power off.
 */
void awo_sw_poweron_start( void );
/**
 * @brief sram retention request.
 * @param map: bit map for which sram need retent. default value is 0x7f.
 * if we need power off sram totally without retention when sleep, we should set that ram retention request to 0.
 */
void awo_sram_retention_req( uint8_t map );
/**
 * @brief set sram vdd value when power down.
 * @param value: set sram vdd.
 */
void awo_sram_vdd_set( uint8_t value );
/**
 * @brief sram light sleep enable.
 * @param map: bit map of sram which need turn into light sleep mode.
 */
void awo_sram_ls_en( uint8_t map );
/**
 * @brief set the pmu parameter.
 * @param pmu_seq_t: the state stay time when PMU output power down/up signal sequence.
 * @param clk_sw_t: the clock switch time.
 * @param ldo_sw_t: the LDO switch time.
 * @param osc_stb_t: the OSC stable time.
 * @param ldo_stb_t: the normal LDO & DCDC stable time.
 */
void awo_set_pmu_timer( uint8_t pmu_seq_t, uint8_t clk_sw_t, uint8_t ldo_sw_t, uint8_t osc_stb_t, uint8_t ldo_stb_t );
/**
 * @brief set pmu sequence time.
 * @param time: the state stay time when PMU output power down/up signal sequence.
 */
void awo_pmu_seq_time( uint8_t time );
/**
 * @brief set the ldo stable delay.
 * @param dly: the normal LDO & DCDC stable time.
 */
void awo_ldo_stb_dly( uint8_t dly );
/**
 * @brief set the ldo switch time.
 * @param dly: the LDO switch time.
 */
void awo_ldo_swc_dly( uint8_t dly );
/**
 * @brief set the OSC stable time.
 * @param dly: the OSC stable time.
 */
void awo_osc_stb_dly( uint8_t dly );
/**
 * @brief set the clock switch time
 * @param dly: the clock switch time
 */
void awo_clk_swc_dly( uint8_t dly );
/**
 * @brief set the normal LDO stable time for touch ctrl use only.(touch need not turn on DCDC, so the dly is short).
 * @param dly: the normal LDO stable time for touch ctrl use only.(touch need not turn on DCDC, so the dly is short).
 */
void awo_touch_ldo_stb_dly( uint8_t dly );
/**
 * @brief set power domain ldo on/off stable time
 * @param time: ldo on/off stable time for power domian.
 */
void awo_ldo_setup_time( uint8_t time );
/**
 * @brief set ldo & clk controller, select to control by pmu or register.
 * @param signal_map: bit map for signal, read awo.h for reference.
 * @param signal_from: signal controlled by pmu(0) or register(1).
 */
void awo_clk_ldo_sel( uint8_t signal_map, uint8_t signal_from );
/**
 * @brief select source of 16m clk(actually 32M). Choose from 32M RC or 32M Crystal.
 * @param sel: Default value 0. Range from 0 to 1. Choose from 32M RC(1) or 32M Crystal(0).
 */
void awo_ana_16m_selrc( uint8_t sel );
/**
 * @brief enable 16m crystal(actually 32m crystal).
 * @param en: 1 for enable, 0 for disable.
 */
void awo_16m_xtal_en( uint8_t en );
/**
 * @brief select source of 32k clk. Choose from 32k RC or 32k Crystal.
 * @param sel: Default value 0. Range from 0 to 1. Choose from 32k RC(0) or 32k Crystal(1).
 */
void awo_ana_32k_selxtal( uint8_t sel );
/**
 * @brief enable 32.768k crystal.
 * @param en: 1 for enable, 0 for disable.
 */
void awo_32k_xtal_en( uint8_t en );
/**
 * @brief enable 32k RC.
 * @param en: 1 for enable, 0 for disable.
 */
void awo_32k_rcosc_en( uint8_t en );
/**
 * @brief read pd state
 * @return state of power domian. 0--off 1--on
 */
uint32_t awo_read_pd_state( void );
/**
 * @brief enable of enable of 5 external interrupt([4:0]) and 1 touch interrupt([5])
 * @param map: 5 external interrupt([4:0]) and 1 touch interrupt([5])
 */
void awo_external_inten( uint8_t map );
/**
 * @brief set trigger type of external interrupt.
 * @param int_src: interrupt source.
 * @param trig_type: 00--high level 01--low level  10--positive edge 11--negative edge
 */
void awo_external_int_trig( uint8_t int_src, uint8_t trig_type );
/**
 * @brief set pin as normal pin or interrupt pin
 * 5 external int: IO[23:22],IO[17:15]
 */
void awo_external_pinisint( uint8_t map );
/**
 * @brief get raw value of external interrupt.
 * @return return a bit map of raw value of external interrupt.
 */
uint8_t awo_ext_rawinrp_value( void );
/**
 * @brief get value of external interrupt.
 * @return return a bit map of value of external interrupt.
 */
uint8_t awo_ext_inrp_value_r( void );
/**
 * @brief write 1 to clear 5 external int
 * 5 external int: IO[23:22],IO[17:15]
 * @param map: bit map for the external interrupt.
 */
void awo_external_intclr( uint8_t map );
/**
 * @brief read raw value of blelp interrupt.
 * @return the raw value of blelp interrupt.
 */
uint8_t awo_blelp_rawinrp_value( void );
/**
 * @brief read value of blelp interrupt.
 * @return the value of blelp interrupt.
 */
uint8_t awo_blelp_inrp_value_r( void );
/**
 * @brief write 1 to clear ble & lp interrupt.
 * @param map: bit map of ble lp interrupt.
 */
void awo_ble_lp_intclr( uint8_t map );
/**
 * @brief upload clock division of pbus parameter to hardware.
 */
void awo_clk_div_pbus_para_up( void );
/**
 * @brief upload clock division of ble mac parameter to hardware.
 */
void awo_clk_div_ble_mac_para_up( void );
/**
 * @brief let hardware control the clock of ble mac
 * @param param: hardware:1 software:0
 */
void awo_clk_sel_ble_mac_by_hw( uint8_t param );
/**
 * @brief set clock division 1 for avoid harmonics.
 * @param param: clock division - 1
 */
void awo_clk_div_ble_mac_para1_m1( uint8_t param );
/**
 * @brief set clock division 0 for ble mac
 * @param param: clock division - 1
 */
void awo_clk_div_ble_mac_para0_m1( uint8_t param );
/**
 * @brief set clock division for modem.
 * @param param: clock division - 1
 */
void awo_clk_div_ble_mdm_rx_para_m1( uint8_t param );
/**
 * @brief let hardware control the clock of ble modem.
 * @param param: hardware:1 software:0
 */
void awo_clk_sel_ble_mdm_rx_by_hw( uint8_t param );
/**
 * @brief select the clock source of modem by software.
 * @param param: 0----32M  1----pll  2---pll_div
 */
void awo_clk_sel_ble_mdm_rx_sw( uint8_t param );
/**
 * @brief select the clock, through a division or not, when we need to avoid harmonics we should go through a division.
 * @param param: 1 -- go through clk_div_ble_mac_para_m1. 0 -- bypass clock division.
 */
void awo_clk_sel_ble_mac( uint8_t param );
/**
 * @brief reset signal. clr and than set to perform a reset.
 * @param map: Read awo.h for reference.
 */
void awo_reset_signal( uint16_t map );
/**
 * @brief set ram parameter.
 */
void awo_ram_param_write( uint8_t rme, uint8_t rm, uint8_t wa, uint8_t ra, uint8_t wpulse );
/**
 * @brief read ram parameter.
 */
void awo_ram_param_read( uint8_t * rme, uint8_t * rm, uint8_t * wa, uint8_t * ra, uint8_t * wpulse );
/**
 * @brief configure PD ldo voltage value except PDsram
 * @param value: 1--1.1V  0--0.9V
 */
void awo_vdd_value_set( uint8_t value );
/**
 * @brief read PD ldo value except PDsram.
 * @return: 1--1.1V  0--0.9V
 */
uint8_t awo_vdd_value_read( void );
/**
 * @brief set drive strength of gpio.
 * @param pin_num: from 0-29
 * @param value: 0--2mA 2--4mA 1--8mA 3--12mA
 */
void awo_gpio_drive_strength( uint8_t pin_num, uint8_t value );
/**
 * @brief enable pin input.
 * @param input_map: bit map for 30 pins.
 */
void awo_gpio_input_en( uint32_t input_map );
/**
 * @brief read pin input state.
 * @return return pin input state.
 */
uint32_t awo_get_gpio_input_state( void );
/**
 * @brief set gpio as Schmitt-triggered input
 * @param input_map: bit map for 30 pins
 */
void awo_gpio_schmitt_en( uint32_t input_map );
/**
 * @brief read schmitt input state.
 * @return bit map for 30 pins
 */
uint32_t awo_get_gpio_schmitt_state( void );
/**
 * @brief enable gpio weak pull.
 * @param input_map: bit map for 30 pins
 */
void awo_gpio_pull_en( uint32_t input_map );
/**
 * @brief read gpio weak pull state.
 * @return: bit map for 30 pins
 */
uint32_t awo_get_gpio_pullen_state( void );
/**
 * @brief select pull up or pull down of gpio.
 * @param input_map: bit map for 30 pins. 1--pull up 0--pull down.
 */
void awo_gpio_pull_sel( uint32_t input_map );
/**
 * @brief read the pull select state.
 * @return bit map for 30 pins. 1--pull up 0--pull down.
 */
uint32_t awo_get_gpio_pullsel_state( void );
/**
 * @brief init of touch adc, touch should calibrate when power on.
 */
void awo_touch_init( void );
/**
 * @brief start touch adc
 * @param interval count in 32k cycle
 * @param num actual sample number
 * @param dly count in 32k cycle
 * @param thd threshold
 * @param intr enable interrupt.
 */
void awo_touch_start( uint16_t interval, uint8_t num, uint8_t dly, uint32_t thd, uint8_t intr );

void awo_touch_test( void );

void awo_touch_calibrate( void );

/**
 * @brief set rf register.
 * @param num: rf register number.
 * @param reg: value of the register.
 */
void awo_rf_reg( uint8_t num, uint32_t reg );
/**
 * @brief read the last rf read only register.
 * @return register value
 */
uint32_t awo_rf_reg_ro( void );
/**
 * @brief set power pwm to give power to other device.
 * @param pwm_high: pwm high time. Range from 0-65525
 * @param pwm_low: pwm low time. Range from 0-65525
 * @param enable: enable == 1 & force_high == 0  out put as pwm settings.
 * @param force_high: force high == 1 output is force to high. force_high == 0 & enable == 0 output is force to low.
 */
void awo_set_pwr_pwm0( uint16_t pwm_high, uint16_t pwm_low, uint8_t enable, uint8_t force_high );
/**
 * @brief set power pwm to give power to other device.
 * @param pwm_high: pwm high time. Range from 0-65525
 * @param pwm_low: pwm low time. Range from 0-65525
 * @param enable: enable == 1 & force_high == 0  out put as pwm settings.
 * @param force_high: force high == 1 output is force to high. force_high == 0 & enable == 0 output is force to low.
 */
void awo_set_pwr_pwm1( uint16_t pwm_high, uint16_t pwm_low, uint8_t enable, uint8_t force_high );
/**
 * @brief set power pwm to give power to other device.
 * @param pwm_high: pwm high time. Range from 0-65525
 * @param pwm_low: pwm low time. Range from 0-65525
 * @param enable: enable == 1 & force_high == 0  out put as pwm settings.
 * @param force_high: force high == 1 output is force to high. force_high == 0 & enable == 0 output is force to low.
 */
void awo_set_pwr_pwm2( uint16_t pwm_high, uint16_t pwm_low, uint8_t enable, uint8_t force_high );

/**
 * @brief 5 external interrupt and touch interrupt handle here.
 */
void awo_ext_isr( void );
/**
 * @brief Change pll clock. Clock will be changed after next wakeup from sleep.
 * @param pll_freq: pll_freq = xxxxxx hz. if we want to set pll to 96Mhz, pll_freq = 96000000
 */
void awo_change_clock( uint32_t pll_freq );
void rf_settings_V2( void );
void rf_settings_V3( void );

#ifdef __cplusplus
}
#endif

#endif /* __AWO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
