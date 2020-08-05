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
#ifndef __REG_BLE_MDM_H__
#define __REG_BLE_MDM_H__

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
        uint32_t                  o_rx_edge_sel :  1;   /* 0: 0, select edge of rx clk source                                                       */
        uint32_t                 o_rx_iq_format :  2;   /* 2: 1, invert input of rx data or not.[1]---I [0]---Q                                     */
        uint32_t                  o_rx_iq_order :  1;   /* 3: 3, interconver IQ order                                                               */
        uint32_t                  o_rx_rate_reg :  2;   /* 5: 4, rx rate. 0---1M 1---2M                                                             */
        uint32_t                  o_rx_rate_sel :  1;   /* 6: 6, 0---select rate from blemac. 1---select register                                   */
        uint32_t        o_rx_access_addr_format :  1;   /* 7: 7, inverted order the 32 bit access addr or not                                       */
        uint32_t              o_rx_cf_accum_sel :  1;   /* 8: 8, find CFO value method. 0---accumelate 8 preamble bits 1---accumelate 6             */
        uint32_t       o_extend_rx_en_low_delay :  3;   /*11: 9, to guarantee the minum low level time of i_rx_en. unit:us                          */
        uint32_t                     reserved_1 :  4;   /*15:12, RESERVED                                                                           */
        uint32_t                  o_tx_rate_reg :  2;   /*17:16, tx rate. 0---1M 1---2M                                                             */
        uint32_t                  o_tx_rate_sel :  1;   /*18:18, 0---select rate from blemac. 1---select register                                   */
        uint32_t                  o_tx_data_inv :  1;   /*19:19, invert tx bit or not                                                               */
        uint32_t                      o_tx_mode :  1;   /*20:20, tx mode. 0-----DM 1-----IQ                                                         */
        uint32_t                  o_tx_edge_sel :  1;   /*21:21, select edge of DAC clk source                                                      */
        uint32_t                o_tx_dac_format :  1;   /*22:22, DAC data format. 0----[-32,31] 1----[0,63]                                         */
        uint32_t                o_tx_sdm_order2 :  1;   /*23:23, 0----mash111 SDM 1---mash11                                                        */
        uint32_t             o_tx_sdm_accum_sel :  1;   /*24:24, mash SDM accumlation method sel. 0----accum current value 1----accum last vaule    */
        uint32_t                   o_tx_iq_swap :  1;   /*25:25, swap IQ of tx IQ output or not                                                     */
        uint32_t               o_tx_gaussf_out0 :  1;   /*26:26, make TX gauss fliter output 0                                                      */
        uint32_t                   o_tx_clk_sel :  1;   /*27:27, 0----select xtal 32m 1---select prescaler 32m clk                                  */
        uint32_t            o_prescaler_clk_inv :  1;   /*28:28, input prescaler clk edge selection 1----inv clk                                    */
        uint32_t                     reserved_0 :  3;   /*31:29, RESERVED                                                                           */
    } bit_field;
} T_BLE_MDM_RX_TX_MISC;


typedef union
{
    uint32_t val;
    struct
    {
        uint32_t             o_rx_nco_fcw_13_0_ : 14;   /*13: 0, rx freq mixer FCW in normal mode           */
        uint32_t                     reserved_1 :  2;   /*15:14, RESERVED                                   */
        uint32_t            o_rx_nco_fcw_27_14_ : 14;   /*29:16, rx freq mixer FCW used in rate conv mode   */
        uint32_t                     reserved_0 :  2;   /*31:30, RESERVED                                   */
    } bit_field;
} T_BLE_MDM_RX_NCO_FCW;

//rx_flt_byp
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               o_rx_hb_1_bypass :  1;   /* 0: 0,  half band flt 1 bypass or not */
        uint32_t               o_rx_hb_2_bypass :  1;   /* 1: 1,  half band flt 2 bypass or not */
        uint32_t             o_rx_acrlpf_bypass :  1;   /* 2: 2,       acrlpf flt bypass or not */
        uint32_t                     reserved_0 : 29;   /*31: 3,                       RESERVED */
    } bit_field;
} T_BLE_MDM_RX_FLT_BYP;

//diffdet_delta
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                o_rx_diff_delta :  3;   /* 2: 0, diff_det delta. range 0~7. indicate the angle delay    */
        uint32_t                     reserved_0 : 29;   /*31: 3, RESERVED                                               */
    } bit_field;
} T_BLE_MDM_DIFFDET_DELTA;

//cfo_trk_para
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  o_rx_envalpha :  3;   /* 2: 0, env flt coeff. range 0~6, represent 1 0.5 0.25 0.125.....respectively  */
        uint32_t                     reserved_2 :  1;   /* 3: 3, RESERVED                                                               */
        uint32_t                  o_rx_estalpha :  3;   /* 6: 4, est flt coeff. range 0~6, represent 1 0.5 0.25 0.125.....respectively  */
        uint32_t                     reserved_1 :  1;   /* 7: 7, RESERVED                                                               */
        uint32_t            o_rx_trk_stable_thd :  5;   /*12: 8, cfo est flt stable time. range 0~30.                                   */
        uint32_t                     reserved_0 : 19;   /*31:13, RESERVED                                                               */
    } bit_field;
} T_BLE_MDM_CFO_TRK_PARA;

//blemac_intf_para
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                o_rx_samp_delay :  6;   /* 5: 0, the delay beteewn cfo_trk output bit and blemac input bit                                                                                      */
        uint32_t                     reserved_2 :  2;   /* 7: 6, RESERVED                                                                                                                                       */
        uint32_t                o_tx_samp_delay :  4;   /*11: 8, the sample delay beteewn mac clk and rf clk. used in tx modem                                                                                  */
        uint32_t                     reserved_1 : 12;   /*23:12, RESERVED                                                                                                                                       */
        uint32_t             o_tx_pkt_vld_delay :  7;   /*30:24, the delay time to pull down pkt_vld compare MAC's i_tx_pkt_vld. this delay is the logic latency from i_tx_bit to o_tx_data_IQ. unit: 32M cycle */
        uint32_t                     reserved_0 :  1;   /*31:31, RESERVED                                                                                                                                       */
    } bit_field;
} T_BLE_MDM_BLEMAC_INTF_PARA;

//rate_conv_reg
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  rate_conv_mul :  8;   /* 7: 0, freq convert molecule(m)                   */
        uint32_t                  rate_conv_div :  8;   /*15: 8, freq convert denominator(n)                */
        uint32_t           rate_conv_fifo_delay :  3;   /*18:16, the pointer delay betweetn fifo WR and RD  */
        uint32_t           rate_conv_cic_bypass :  1;   /*19:19, 1---bypass cic filter in rate conv         */
        uint32_t                     reserved_0 : 12;   /*31:20, RESERVED                                   */
    } bit_field;
} T_BLE_MDM_RATE_CONV_REG;

//rate_conv_enable
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t       need_rate_conv_num_31_0_ : 32;   /*31: 0, which freq num is needed to rateconv to avoid harmanic. one hot. 0---need't  1---need*/
    } bit_field;
} T_BLE_MDM_RATE_CONV_ENABLE;

//rate_conv_clk
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t      need_rate_conv_num_39_32_ :  8;   /* 7: 0, which freq num is needed to rateconv to avoid harmanic. one hot. 0---need't 1---need   */
        uint32_t                    clk_rf_2sel :  6;   /*13: 8, [2:0]----the clock select when in need't do rateconv. [5:3]-----when need do rateconv. */
        uint32_t                     reserved_0 : 18;   /*31:14, RESERVED                                                                               */
    } bit_field;
} T_BLE_MDM_RATE_CONV_CLK;

//debug_sel
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t              o_ble_mac_dbg_sel :  3;   /* 2: 0, debug port select signal                                                                       */
        uint32_t            o_modem_loopback_en :  1;   /* 3: 3, enable loopback function                                                                       */
        uint32_t       o_modem_loopback_latency :  4;   /* 7: 4, the latency from TX to RX in loopback mode. use this vlaue to compare RX bit to TX. unit:bit   */
        uint32_t                     reserved_0 : 23;   /*30: 8, RESERVED                                                                                       */
        uint32_t           i_mdoem_loopback_err :  1;   /*31:31, indicate NOT pass loopback test                                                                */
    } bit_field;
} T_BLE_MDM_DEBUG_SEL;

//blemac_need_swc_clk_0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t      blemac_need_swc_clk_31_0_ : 32;   /*31: 0, which freq num is needed to switch blemac clk freq to avoid harmanic. one hot. 0---need't  1---need*/
    } bit_field;
} T_BLE_MDM_BLEMAC_NEED_SWC_CLK_0;

//blemac_need_swc_clk_1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t     blemac_need_swc_clk_39_32_ :  8;   /* 7: 0, which freq num is needed to switch blemac clk freq to avoid harmanic. one hot. 0---need't 1---need */
        uint32_t                     reserved_0 : 24;   /*31: 8, RESERVED                                                                                           */
    } bit_field;
} T_BLE_MDM_BLEMAC_NEED_SWC_CLK_1;

//tx_timing
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t              o_tx_en_off_delay : 11;   /*10: 0, extra delay for pull down tx_en from blemac by tx_modem. unit:32M cycle    */
        uint32_t                     reserved_1 :  5;   /*15:11, RESERVED                                                                   */
        uint32_t                 o_tx_vco_delay :  2;   /*17:16, put extra delay on vco path                                                */
        uint32_t                 o_tx_sdm_delay :  2;   /*19:18, put extra delay on sdm path                                                */
        uint32_t                     reserved_0 : 12;   /*31:20, RESERVED                                                                   */
    } bit_field;
} T_BLE_MDM_TX_TIMING;

//as_rf_chip
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                   rf_chip_rate :  2;   /* 1: 0, No description.    */
        uint32_t                   rf_chip_txen :  1;   /* 2: 2, No description.    */
        uint32_t                   rf_chip_rxen :  1;   /* 3: 3, No description.    */
        uint32_t              rf_chip_txclk_inv :  1;   /* 4: 4, No description.    */
        uint32_t              rf_chip_rxclk_inv :  1;   /* 5: 5, No description.    */
        uint32_t           rf_chip_pgm_edge_sel :  1;   /* 6: 6, No description.    */
        uint32_t                     reserved_1 :  1;   /* 7: 7, RESERVED           */
        uint32_t                  rf_chip_power :  8;   /*15: 8, No description.    */
        uint32_t               rf_chip_freq_num :  8;   /*23:16, No description.    */
        uint32_t                     reserved_0 :  7;   /*30:24, RESERVED           */
        uint32_t                     rf_chip_en :  1;   /*31:31, RFchip enable      */
    } bit_field;
} T_BLE_MDM_AS_RF_CHIP;

//adc_rssi_reg
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t           o_adc_rssi_ldo_delay : 10;   /* 9: 0, No description.    */
        uint32_t             o_adc_rssi_clk_pol :  1;   /*10:10, No description.    */
        uint32_t              o_adc_rssi_agc_en :  1;   /*11:11, No description.    */
        uint32_t             o_agc_rssi_avg_num :  3;   /*14:12, No description.    */
        uint32_t                     reserved_0 : 17;   /*31:15, RESERVED           */
    } bit_field;
} T_BLE_MDM_ADC_RSSI_REG;

//vco_cal_state
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t        vco_deviation_cal_start :  1;   /* 0: 0, WR 1 to start VCO deviation calibration        */
        uint32_t               in_vco_devia_cal :  1;   /* 1: 1, indicate is doing VCO deviation calibration    */
        uint32_t              vco_band_cal_done :  1;   /* 2: 2, indicate VCO band calibration has done         */
        uint32_t                     reserved_0 : 29;   /*31: 3, RESERVED                                       */
    } bit_field;
} T_BLE_MDM_VCO_CAL_STATE;

//vco_cal_capdev_1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               vcocali_capdev_1 : 12;   /*11: 0, VCO cap dev value of frequence in 2402~2420MHz. [11:6]---used in 2 Mbps mode, [5:0]---1Mbps mode   */
        uint32_t                     reserved_0 : 20;   /*31:12, RESERVED                                                                                           */
    } bit_field;
} T_BLE_MDM_VCO_CAL_CAPDEV_1;

//vco_cal_capdev_2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               vcocali_capdev_2 : 12;   /*11: 0, VCO cap dev value of frequence in 2420~2440MHz. [11:6]---used in 2 Mbps mode, [5:0]---1Mbps mode   */
        uint32_t                     reserved_0 : 20;   /*31:12, RESERVED                                                                                           */
    } bit_field;
} T_BLE_MDM_VCO_CAL_CAPDEV_2;

//vco_cal_capdev_3
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               vcocali_capdev_3 : 12;   /*11: 0, VCO cap dev value of frequence in 2440~2460MHz. [11:6]---used in 2 Mbps mode, [5:0]---1Mbps mode   */
        uint32_t                     reserved_0 : 20;   /*31:12, RESERVED                                                                                           */
    } bit_field;
} T_BLE_MDM_VCO_CAL_CAPDEV_3;

//vco_cal_capdev_4
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               vcocali_capdev_4 : 12;   /*11: 0, VCO cap dev value of frequence in 2460~2480MHz. [11:6]---used in 2 Mbps mode, [5:0]---1Mbps mode   */
        uint32_t                     reserved_0 : 20;   /*31:12, RESERVED                                                                                           */
    } bit_field;
} T_BLE_MDM_VCO_CAL_CAPDEV_4;

//vco_cal_para
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                   vco_stb_time :  4;   /* 3: 0, VCO table time. unit:us                            */
        uint32_t                vco_cnt_spacing :  4;   /* 7: 4, VCO band adjust step in band calibration           */
        uint32_t                vco_band_offset :  3;   /*10: 8, VCO band extra offset after calibration has done   */
        uint32_t                     reserved_0 : 21;   /*31:11, RESERVED                                           */
    } bit_field;
} T_BLE_MDM_VCO_CAL_PARA;
typedef struct
{
    volatile            T_BLE_MDM_RX_TX_MISC                     rx_tx_misc;    /* 0x0, RW, 0x08000406, No description.     */
    volatile            T_BLE_MDM_RX_NCO_FCW                     rx_nco_fcw;    /* 0x4, RW, 0x38003400, No description.     */
    volatile            T_BLE_MDM_RX_FLT_BYP                     rx_flt_byp;    /* 0x8, RW, 0x00000000, No description.     */
    volatile         T_BLE_MDM_DIFFDET_DELTA                  diffdet_delta;    /* 0xc, RW, 0x00000005, No description.     */
    volatile          T_BLE_MDM_CFO_TRK_PARA                   cfo_trk_para;    /* 0x10, RW, 0x00001043, No description.    */
    volatile      T_BLE_MDM_BLEMAC_INTF_PARA               blemac_intf_para;    /* 0x14, RW, 0x40000303, flush Register     */
    volatile         T_BLE_MDM_RATE_CONV_REG                  rate_conv_reg;    /* 0x18, RW, 0x00030302, No description.    */
    volatile      T_BLE_MDM_RATE_CONV_ENABLE               rate_conv_enable;    /* 0x1c, RW, 0x80008000, No description.    */
    volatile         T_BLE_MDM_RATE_CONV_CLK                  rate_conv_clk;    /* 0x20, RW, 0x00001100, No description.    */
    volatile             T_BLE_MDM_DEBUG_SEL                      debug_sel;    /* 0x24, RW, 0x00000070, No description.    */
    volatile T_BLE_MDM_BLEMAC_NEED_SWC_CLK_0          blemac_need_swc_clk_0;    /* 0x28, RW, 0x00000000, No description.    */
    volatile T_BLE_MDM_BLEMAC_NEED_SWC_CLK_1          blemac_need_swc_clk_1;    /* 0x2c, RW, 0x00000000, No description.    */
    volatile             T_BLE_MDM_TX_TIMING                      tx_timing;    /* 0x30, RW, 0x00000060, No description.    */
    volatile            T_BLE_MDM_AS_RF_CHIP                     as_rf_chip;    /* 0x34, RW, 0x00000000, No description.    */
    volatile          T_BLE_MDM_ADC_RSSI_REG                   adc_rssi_reg;    /* 0x38, RW, 0x000000A0, No description.    */
    volatile                        uint32_t                     reserved_1;    /* !< description                           */
    volatile         T_BLE_MDM_VCO_CAL_STATE                  vco_cal_state;    /* 0x40, RW, 0x00000000, No description.    */
    volatile      T_BLE_MDM_VCO_CAL_CAPDEV_1               vco_cal_capdev_1;    /* 0x44, RW, 0x00000000, No description.    */
    volatile      T_BLE_MDM_VCO_CAL_CAPDEV_2               vco_cal_capdev_2;    /* 0x48, RW, 0x00000000, No description.    */
    volatile      T_BLE_MDM_VCO_CAL_CAPDEV_3               vco_cal_capdev_3;    /* 0x4c, RW, 0x00000000, No description.    */
    volatile      T_BLE_MDM_VCO_CAL_CAPDEV_4               vco_cal_capdev_4;    /* 0x50, RW, 0x00000000, No description.    */
    volatile          T_BLE_MDM_VCO_CAL_PARA                   vco_cal_para;    /* 0x54, RW, 0x00000085, No description.    */
} T_HWP_BLE_MDM_T;

/* exported variables --------------------------------------------------------*/
#define hwp_ble_mdm ((T_HWP_BLE_MDM_T*)REG_BLE_MDM_BASE)

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_rx_tx_misc_get(void)
{
    return hwp_ble_mdm->rx_tx_misc.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rx_tx_misc_set(uint32_t value)
{
    hwp_ble_mdm->rx_tx_misc.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rx_tx_misc_pack(uint8_t o_prescaler_clk_inv, uint8_t o_tx_clk_sel, uint8_t o_tx_gaussf_out0, uint8_t o_tx_iq_swap, uint8_t o_tx_sdm_accum_sel, uint8_t o_tx_sdm_order2, uint8_t o_tx_dac_format, uint8_t o_tx_edge_sel, uint8_t o_tx_mode, uint8_t o_tx_data_inv, uint8_t o_tx_rate_sel, uint8_t o_tx_rate_reg, uint8_t o_extend_rx_en_low_delay, uint8_t o_rx_cf_accum_sel, uint8_t o_rx_access_addr_format, uint8_t o_rx_rate_sel, uint8_t o_rx_rate_reg, uint8_t o_rx_iq_order, uint8_t o_rx_iq_format, uint8_t o_rx_edge_sel)
{
    hwp_ble_mdm->rx_tx_misc.val = (((uint32_t)o_prescaler_clk_inv << 28) | ((uint32_t)o_tx_clk_sel << 27) | ((uint32_t)o_tx_gaussf_out0 << 26) | ((uint32_t)o_tx_iq_swap << 25) | ((uint32_t)o_tx_sdm_accum_sel << 24) | ((uint32_t)o_tx_sdm_order2 << 23) | ((uint32_t)o_tx_dac_format << 22) | ((uint32_t)o_tx_edge_sel << 21) | ((uint32_t)o_tx_mode << 20) | ((uint32_t)o_tx_data_inv << 19) | ((uint32_t)o_tx_rate_sel << 18) | ((uint32_t)o_tx_rate_reg << 16) | ((uint32_t)o_extend_rx_en_low_delay << 9) | ((uint32_t)o_rx_cf_accum_sel << 8) | ((uint32_t)o_rx_access_addr_format << 7) | ((uint32_t)o_rx_rate_sel << 6) | ((uint32_t)o_rx_rate_reg << 4) | ((uint32_t)o_rx_iq_order << 3) | ((uint32_t)o_rx_iq_format << 1) | ((uint32_t)o_rx_edge_sel << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rx_tx_misc_unpack(uint8_t* o_prescaler_clk_inv, uint8_t* o_tx_clk_sel, uint8_t* o_tx_gaussf_out0, uint8_t* o_tx_iq_swap, uint8_t* o_tx_sdm_accum_sel, uint8_t* o_tx_sdm_order2, uint8_t* o_tx_dac_format, uint8_t* o_tx_edge_sel, uint8_t* o_tx_mode, uint8_t* o_tx_data_inv, uint8_t* o_tx_rate_sel, uint8_t* o_tx_rate_reg, uint8_t* o_extend_rx_en_low_delay, uint8_t* o_rx_cf_accum_sel, uint8_t* o_rx_access_addr_format, uint8_t* o_rx_rate_sel, uint8_t* o_rx_rate_reg, uint8_t* o_rx_iq_order, uint8_t* o_rx_iq_format, uint8_t* o_rx_edge_sel)
{
    T_BLE_MDM_RX_TX_MISC localVal = hwp_ble_mdm->rx_tx_misc;

    *o_prescaler_clk_inv = localVal.bit_field.o_prescaler_clk_inv;
    *o_tx_clk_sel = localVal.bit_field.o_tx_clk_sel;
    *o_tx_gaussf_out0 = localVal.bit_field.o_tx_gaussf_out0;
    *o_tx_iq_swap = localVal.bit_field.o_tx_iq_swap;
    *o_tx_sdm_accum_sel = localVal.bit_field.o_tx_sdm_accum_sel;
    *o_tx_sdm_order2 = localVal.bit_field.o_tx_sdm_order2;
    *o_tx_dac_format = localVal.bit_field.o_tx_dac_format;
    *o_tx_edge_sel = localVal.bit_field.o_tx_edge_sel;
    *o_tx_mode = localVal.bit_field.o_tx_mode;
    *o_tx_data_inv = localVal.bit_field.o_tx_data_inv;
    *o_tx_rate_sel = localVal.bit_field.o_tx_rate_sel;
    *o_tx_rate_reg = localVal.bit_field.o_tx_rate_reg;
    *o_extend_rx_en_low_delay = localVal.bit_field.o_extend_rx_en_low_delay;
    *o_rx_cf_accum_sel = localVal.bit_field.o_rx_cf_accum_sel;
    *o_rx_access_addr_format = localVal.bit_field.o_rx_access_addr_format;
    *o_rx_rate_sel = localVal.bit_field.o_rx_rate_sel;
    *o_rx_rate_reg = localVal.bit_field.o_rx_rate_reg;
    *o_rx_iq_order = localVal.bit_field.o_rx_iq_order;
    *o_rx_iq_format = localVal.bit_field.o_rx_iq_format;
    *o_rx_edge_sel = localVal.bit_field.o_rx_edge_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_prescaler_clk_inv_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_prescaler_clk_inv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_prescaler_clk_inv_setf(uint8_t o_prescaler_clk_inv)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_prescaler_clk_inv = o_prescaler_clk_inv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_clk_sel_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_clk_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_clk_sel_setf(uint8_t o_tx_clk_sel)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_clk_sel = o_tx_clk_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_gaussf_out0_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_gaussf_out0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_gaussf_out0_setf(uint8_t o_tx_gaussf_out0)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_gaussf_out0 = o_tx_gaussf_out0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_iq_swap_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_iq_swap;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_iq_swap_setf(uint8_t o_tx_iq_swap)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_iq_swap = o_tx_iq_swap;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_sdm_accum_sel_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_sdm_accum_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_sdm_accum_sel_setf(uint8_t o_tx_sdm_accum_sel)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_sdm_accum_sel = o_tx_sdm_accum_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_sdm_order2_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_sdm_order2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_sdm_order2_setf(uint8_t o_tx_sdm_order2)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_sdm_order2 = o_tx_sdm_order2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_dac_format_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_dac_format;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_dac_format_setf(uint8_t o_tx_dac_format)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_dac_format = o_tx_dac_format;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_edge_sel_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_edge_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_edge_sel_setf(uint8_t o_tx_edge_sel)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_edge_sel = o_tx_edge_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_mode_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_mode;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_mode_setf(uint8_t o_tx_mode)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_mode = o_tx_mode;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_data_inv_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_data_inv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_data_inv_setf(uint8_t o_tx_data_inv)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_data_inv = o_tx_data_inv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_rate_sel_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_rate_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_rate_sel_setf(uint8_t o_tx_rate_sel)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_rate_sel = o_tx_rate_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_rate_reg_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_rate_reg;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_rate_reg_setf(uint8_t o_tx_rate_reg)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_tx_rate_reg = o_tx_rate_reg;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_extend_rx_en_low_delay_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_extend_rx_en_low_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_extend_rx_en_low_delay_setf(uint8_t o_extend_rx_en_low_delay)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_extend_rx_en_low_delay = o_extend_rx_en_low_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_cf_accum_sel_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_cf_accum_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_cf_accum_sel_setf(uint8_t o_rx_cf_accum_sel)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_cf_accum_sel = o_rx_cf_accum_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_access_addr_format_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_access_addr_format;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_access_addr_format_setf(uint8_t o_rx_access_addr_format)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_access_addr_format = o_rx_access_addr_format;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_rate_sel_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_rate_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_rate_sel_setf(uint8_t o_rx_rate_sel)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_rate_sel = o_rx_rate_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_rate_reg_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_rate_reg;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_rate_reg_setf(uint8_t o_rx_rate_reg)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_rate_reg = o_rx_rate_reg;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_iq_order_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_iq_order;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_iq_order_setf(uint8_t o_rx_iq_order)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_iq_order = o_rx_iq_order;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_iq_format_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_iq_format;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_iq_format_setf(uint8_t o_rx_iq_format)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_iq_format = o_rx_iq_format;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_edge_sel_getf(void)
{
    return hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_edge_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_edge_sel_setf(uint8_t o_rx_edge_sel)
{
    hwp_ble_mdm->rx_tx_misc.bit_field.o_rx_edge_sel = o_rx_edge_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_rx_nco_fcw_get(void)
{
    return hwp_ble_mdm->rx_nco_fcw.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rx_nco_fcw_set(uint32_t value)
{
    hwp_ble_mdm->rx_nco_fcw.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rx_nco_fcw_pack(uint16_t o_rx_nco_fcw_27_14_, uint16_t o_rx_nco_fcw_13_0_)
{
    hwp_ble_mdm->rx_nco_fcw.val = (((uint32_t)o_rx_nco_fcw_27_14_ << 16) | ((uint32_t)o_rx_nco_fcw_13_0_ << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rx_nco_fcw_unpack(uint16_t* o_rx_nco_fcw_27_14_, uint16_t* o_rx_nco_fcw_13_0_)
{
    T_BLE_MDM_RX_NCO_FCW localVal = hwp_ble_mdm->rx_nco_fcw;

    *o_rx_nco_fcw_27_14_ = localVal.bit_field.o_rx_nco_fcw_27_14_;
    *o_rx_nco_fcw_13_0_ = localVal.bit_field.o_rx_nco_fcw_13_0_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t ble_mdm_o_rx_nco_fcw_27_14__getf(void)
{
    return hwp_ble_mdm->rx_nco_fcw.bit_field.o_rx_nco_fcw_27_14_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_nco_fcw_27_14__setf(uint16_t o_rx_nco_fcw_27_14_)
{
    hwp_ble_mdm->rx_nco_fcw.bit_field.o_rx_nco_fcw_27_14_ = o_rx_nco_fcw_27_14_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t ble_mdm_o_rx_nco_fcw_13_0__getf(void)
{
    return hwp_ble_mdm->rx_nco_fcw.bit_field.o_rx_nco_fcw_13_0_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_nco_fcw_13_0__setf(uint16_t o_rx_nco_fcw_13_0_)
{
    hwp_ble_mdm->rx_nco_fcw.bit_field.o_rx_nco_fcw_13_0_ = o_rx_nco_fcw_13_0_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_rx_flt_byp_get(void)
{
    return hwp_ble_mdm->rx_flt_byp.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rx_flt_byp_set(uint32_t value)
{
    hwp_ble_mdm->rx_flt_byp.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rx_flt_byp_pack(uint8_t o_rx_acrlpf_bypass, uint8_t o_rx_hb_2_bypass, uint8_t o_rx_hb_1_bypass)
{
    hwp_ble_mdm->rx_flt_byp.val = (((uint32_t)o_rx_acrlpf_bypass << 2) | ((uint32_t)o_rx_hb_2_bypass << 1) | ((uint32_t)o_rx_hb_1_bypass << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rx_flt_byp_unpack(uint8_t* o_rx_acrlpf_bypass, uint8_t* o_rx_hb_2_bypass, uint8_t* o_rx_hb_1_bypass)
{
    T_BLE_MDM_RX_FLT_BYP localVal = hwp_ble_mdm->rx_flt_byp;

    *o_rx_acrlpf_bypass = localVal.bit_field.o_rx_acrlpf_bypass;
    *o_rx_hb_2_bypass = localVal.bit_field.o_rx_hb_2_bypass;
    *o_rx_hb_1_bypass = localVal.bit_field.o_rx_hb_1_bypass;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_acrlpf_bypass_getf(void)
{
    return hwp_ble_mdm->rx_flt_byp.bit_field.o_rx_acrlpf_bypass;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_acrlpf_bypass_setf(uint8_t o_rx_acrlpf_bypass)
{
    hwp_ble_mdm->rx_flt_byp.bit_field.o_rx_acrlpf_bypass = o_rx_acrlpf_bypass;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_hb_2_bypass_getf(void)
{
    return hwp_ble_mdm->rx_flt_byp.bit_field.o_rx_hb_2_bypass;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_hb_2_bypass_setf(uint8_t o_rx_hb_2_bypass)
{
    hwp_ble_mdm->rx_flt_byp.bit_field.o_rx_hb_2_bypass = o_rx_hb_2_bypass;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_hb_1_bypass_getf(void)
{
    return hwp_ble_mdm->rx_flt_byp.bit_field.o_rx_hb_1_bypass;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_hb_1_bypass_setf(uint8_t o_rx_hb_1_bypass)
{
    hwp_ble_mdm->rx_flt_byp.bit_field.o_rx_hb_1_bypass = o_rx_hb_1_bypass;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_diffdet_delta_get(void)
{
    return hwp_ble_mdm->diffdet_delta.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_diffdet_delta_set(uint32_t value)
{
    hwp_ble_mdm->diffdet_delta.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_diffdet_delta_pack(uint8_t o_rx_diff_delta)
{
    hwp_ble_mdm->diffdet_delta.val = (((uint32_t)o_rx_diff_delta << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_diffdet_delta_unpack(uint8_t* o_rx_diff_delta)
{
    T_BLE_MDM_DIFFDET_DELTA localVal = hwp_ble_mdm->diffdet_delta;

    *o_rx_diff_delta = localVal.bit_field.o_rx_diff_delta;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_diff_delta_getf(void)
{
    return hwp_ble_mdm->diffdet_delta.bit_field.o_rx_diff_delta;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_diff_delta_setf(uint8_t o_rx_diff_delta)
{
    hwp_ble_mdm->diffdet_delta.bit_field.o_rx_diff_delta = o_rx_diff_delta;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_cfo_trk_para_get(void)
{
    return hwp_ble_mdm->cfo_trk_para.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_cfo_trk_para_set(uint32_t value)
{
    hwp_ble_mdm->cfo_trk_para.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_cfo_trk_para_pack(uint8_t o_rx_trk_stable_thd, uint8_t o_rx_estalpha, uint8_t o_rx_envalpha)
{
    hwp_ble_mdm->cfo_trk_para.val = (((uint32_t)o_rx_trk_stable_thd << 8) | ((uint32_t)o_rx_estalpha << 4) | ((uint32_t)o_rx_envalpha << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_cfo_trk_para_unpack(uint8_t* o_rx_trk_stable_thd, uint8_t* o_rx_estalpha, uint8_t* o_rx_envalpha)
{
    T_BLE_MDM_CFO_TRK_PARA localVal = hwp_ble_mdm->cfo_trk_para;

    *o_rx_trk_stable_thd = localVal.bit_field.o_rx_trk_stable_thd;
    *o_rx_estalpha = localVal.bit_field.o_rx_estalpha;
    *o_rx_envalpha = localVal.bit_field.o_rx_envalpha;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_trk_stable_thd_getf(void)
{
    return hwp_ble_mdm->cfo_trk_para.bit_field.o_rx_trk_stable_thd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_trk_stable_thd_setf(uint8_t o_rx_trk_stable_thd)
{
    hwp_ble_mdm->cfo_trk_para.bit_field.o_rx_trk_stable_thd = o_rx_trk_stable_thd;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_estalpha_getf(void)
{
    return hwp_ble_mdm->cfo_trk_para.bit_field.o_rx_estalpha;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_estalpha_setf(uint8_t o_rx_estalpha)
{
    hwp_ble_mdm->cfo_trk_para.bit_field.o_rx_estalpha = o_rx_estalpha;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_envalpha_getf(void)
{
    return hwp_ble_mdm->cfo_trk_para.bit_field.o_rx_envalpha;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_envalpha_setf(uint8_t o_rx_envalpha)
{
    hwp_ble_mdm->cfo_trk_para.bit_field.o_rx_envalpha = o_rx_envalpha;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_blemac_intf_para_get(void)
{
    return hwp_ble_mdm->blemac_intf_para.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_intf_para_set(uint32_t value)
{
    hwp_ble_mdm->blemac_intf_para.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_intf_para_pack(uint8_t o_tx_pkt_vld_delay, uint8_t o_tx_samp_delay, uint8_t o_rx_samp_delay)
{
    hwp_ble_mdm->blemac_intf_para.val = (((uint32_t)o_tx_pkt_vld_delay << 24) | ((uint32_t)o_tx_samp_delay << 8) | ((uint32_t)o_rx_samp_delay << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_intf_para_unpack(uint8_t* o_tx_pkt_vld_delay, uint8_t* o_tx_samp_delay, uint8_t* o_rx_samp_delay)
{
    T_BLE_MDM_BLEMAC_INTF_PARA localVal = hwp_ble_mdm->blemac_intf_para;

    *o_tx_pkt_vld_delay = localVal.bit_field.o_tx_pkt_vld_delay;
    *o_tx_samp_delay = localVal.bit_field.o_tx_samp_delay;
    *o_rx_samp_delay = localVal.bit_field.o_rx_samp_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_pkt_vld_delay_getf(void)
{
    return hwp_ble_mdm->blemac_intf_para.bit_field.o_tx_pkt_vld_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_pkt_vld_delay_setf(uint8_t o_tx_pkt_vld_delay)
{
    hwp_ble_mdm->blemac_intf_para.bit_field.o_tx_pkt_vld_delay = o_tx_pkt_vld_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_samp_delay_getf(void)
{
    return hwp_ble_mdm->blemac_intf_para.bit_field.o_tx_samp_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_samp_delay_setf(uint8_t o_tx_samp_delay)
{
    hwp_ble_mdm->blemac_intf_para.bit_field.o_tx_samp_delay = o_tx_samp_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_rx_samp_delay_getf(void)
{
    return hwp_ble_mdm->blemac_intf_para.bit_field.o_rx_samp_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_rx_samp_delay_setf(uint8_t o_rx_samp_delay)
{
    hwp_ble_mdm->blemac_intf_para.bit_field.o_rx_samp_delay = o_rx_samp_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_rate_conv_reg_get(void)
{
    return hwp_ble_mdm->rate_conv_reg.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_reg_set(uint32_t value)
{
    hwp_ble_mdm->rate_conv_reg.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_reg_pack(uint8_t rate_conv_cic_bypass, uint8_t rate_conv_fifo_delay, uint8_t rate_conv_div, uint8_t rate_conv_mul)
{
    hwp_ble_mdm->rate_conv_reg.val = (((uint32_t)rate_conv_cic_bypass << 19) | ((uint32_t)rate_conv_fifo_delay << 16) | ((uint32_t)rate_conv_div << 8) | ((uint32_t)rate_conv_mul << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_reg_unpack(uint8_t* rate_conv_cic_bypass, uint8_t* rate_conv_fifo_delay, uint8_t* rate_conv_div, uint8_t* rate_conv_mul)
{
    T_BLE_MDM_RATE_CONV_REG localVal = hwp_ble_mdm->rate_conv_reg;

    *rate_conv_cic_bypass = localVal.bit_field.rate_conv_cic_bypass;
    *rate_conv_fifo_delay = localVal.bit_field.rate_conv_fifo_delay;
    *rate_conv_div = localVal.bit_field.rate_conv_div;
    *rate_conv_mul = localVal.bit_field.rate_conv_mul;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rate_conv_cic_bypass_getf(void)
{
    return hwp_ble_mdm->rate_conv_reg.bit_field.rate_conv_cic_bypass;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_cic_bypass_setf(uint8_t rate_conv_cic_bypass)
{
    hwp_ble_mdm->rate_conv_reg.bit_field.rate_conv_cic_bypass = rate_conv_cic_bypass;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rate_conv_fifo_delay_getf(void)
{
    return hwp_ble_mdm->rate_conv_reg.bit_field.rate_conv_fifo_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_fifo_delay_setf(uint8_t rate_conv_fifo_delay)
{
    hwp_ble_mdm->rate_conv_reg.bit_field.rate_conv_fifo_delay = rate_conv_fifo_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rate_conv_div_getf(void)
{
    return hwp_ble_mdm->rate_conv_reg.bit_field.rate_conv_div;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_div_setf(uint8_t rate_conv_div)
{
    hwp_ble_mdm->rate_conv_reg.bit_field.rate_conv_div = rate_conv_div;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rate_conv_mul_getf(void)
{
    return hwp_ble_mdm->rate_conv_reg.bit_field.rate_conv_mul;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_mul_setf(uint8_t rate_conv_mul)
{
    hwp_ble_mdm->rate_conv_reg.bit_field.rate_conv_mul = rate_conv_mul;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_rate_conv_enable_get(void)
{
    return hwp_ble_mdm->rate_conv_enable.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_enable_set(uint32_t value)
{
    hwp_ble_mdm->rate_conv_enable.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_enable_pack(uint32_t need_rate_conv_num_31_0_)
{
    hwp_ble_mdm->rate_conv_enable.val = (((uint32_t)need_rate_conv_num_31_0_ << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_enable_unpack(uint32_t* need_rate_conv_num_31_0_)
{
    T_BLE_MDM_RATE_CONV_ENABLE localVal = hwp_ble_mdm->rate_conv_enable;

    *need_rate_conv_num_31_0_ = localVal.bit_field.need_rate_conv_num_31_0_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_need_rate_conv_num_31_0__getf(void)
{
    return hwp_ble_mdm->rate_conv_enable.bit_field.need_rate_conv_num_31_0_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_need_rate_conv_num_31_0__setf(uint32_t need_rate_conv_num_31_0_)
{
    hwp_ble_mdm->rate_conv_enable.bit_field.need_rate_conv_num_31_0_ = need_rate_conv_num_31_0_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_rate_conv_clk_get(void)
{
    return hwp_ble_mdm->rate_conv_clk.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_clk_set(uint32_t value)
{
    hwp_ble_mdm->rate_conv_clk.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_clk_pack(uint8_t clk_rf_2sel, uint8_t need_rate_conv_num_39_32_)
{
    hwp_ble_mdm->rate_conv_clk.val = (((uint32_t)clk_rf_2sel << 8) | ((uint32_t)need_rate_conv_num_39_32_ << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rate_conv_clk_unpack(uint8_t* clk_rf_2sel, uint8_t* need_rate_conv_num_39_32_)
{
    T_BLE_MDM_RATE_CONV_CLK localVal = hwp_ble_mdm->rate_conv_clk;

    *clk_rf_2sel = localVal.bit_field.clk_rf_2sel;
    *need_rate_conv_num_39_32_ = localVal.bit_field.need_rate_conv_num_39_32_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_clk_rf_2sel_getf(void)
{
    return hwp_ble_mdm->rate_conv_clk.bit_field.clk_rf_2sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_clk_rf_2sel_setf(uint8_t clk_rf_2sel)
{
    hwp_ble_mdm->rate_conv_clk.bit_field.clk_rf_2sel = clk_rf_2sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_need_rate_conv_num_39_32__getf(void)
{
    return hwp_ble_mdm->rate_conv_clk.bit_field.need_rate_conv_num_39_32_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_need_rate_conv_num_39_32__setf(uint8_t need_rate_conv_num_39_32_)
{
    hwp_ble_mdm->rate_conv_clk.bit_field.need_rate_conv_num_39_32_ = need_rate_conv_num_39_32_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_debug_sel_get(void)
{
    return hwp_ble_mdm->debug_sel.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_debug_sel_set(uint32_t value)
{
    hwp_ble_mdm->debug_sel.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_debug_sel_pack(uint8_t o_modem_loopback_latency, uint8_t o_modem_loopback_en, uint8_t o_ble_mac_dbg_sel)
{
    hwp_ble_mdm->debug_sel.val = (((uint32_t)o_modem_loopback_latency << 4) | ((uint32_t)o_modem_loopback_en << 3) | ((uint32_t)o_ble_mac_dbg_sel << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_debug_sel_unpack(uint8_t* i_mdoem_loopback_err, uint8_t* o_modem_loopback_latency, uint8_t* o_modem_loopback_en, uint8_t* o_ble_mac_dbg_sel)
{
    T_BLE_MDM_DEBUG_SEL localVal = hwp_ble_mdm->debug_sel;

    *i_mdoem_loopback_err = localVal.bit_field.i_mdoem_loopback_err;
    *o_modem_loopback_latency = localVal.bit_field.o_modem_loopback_latency;
    *o_modem_loopback_en = localVal.bit_field.o_modem_loopback_en;
    *o_ble_mac_dbg_sel = localVal.bit_field.o_ble_mac_dbg_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_i_mdoem_loopback_err_getf(void)
{
    return hwp_ble_mdm->debug_sel.bit_field.i_mdoem_loopback_err;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_modem_loopback_latency_getf(void)
{
    return hwp_ble_mdm->debug_sel.bit_field.o_modem_loopback_latency;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_modem_loopback_latency_setf(uint8_t o_modem_loopback_latency)
{
    hwp_ble_mdm->debug_sel.bit_field.o_modem_loopback_latency = o_modem_loopback_latency;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_modem_loopback_en_getf(void)
{
    return hwp_ble_mdm->debug_sel.bit_field.o_modem_loopback_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_modem_loopback_en_setf(uint8_t o_modem_loopback_en)
{
    hwp_ble_mdm->debug_sel.bit_field.o_modem_loopback_en = o_modem_loopback_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_ble_mac_dbg_sel_getf(void)
{
    return hwp_ble_mdm->debug_sel.bit_field.o_ble_mac_dbg_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_ble_mac_dbg_sel_setf(uint8_t o_ble_mac_dbg_sel)
{
    hwp_ble_mdm->debug_sel.bit_field.o_ble_mac_dbg_sel = o_ble_mac_dbg_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_blemac_need_swc_clk_0_get(void)
{
    return hwp_ble_mdm->blemac_need_swc_clk_0.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_need_swc_clk_0_set(uint32_t value)
{
    hwp_ble_mdm->blemac_need_swc_clk_0.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_need_swc_clk_0_pack(uint32_t blemac_need_swc_clk_31_0_)
{
    hwp_ble_mdm->blemac_need_swc_clk_0.val = (((uint32_t)blemac_need_swc_clk_31_0_ << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_need_swc_clk_0_unpack(uint32_t* blemac_need_swc_clk_31_0_)
{
    T_BLE_MDM_BLEMAC_NEED_SWC_CLK_0 localVal = hwp_ble_mdm->blemac_need_swc_clk_0;

    *blemac_need_swc_clk_31_0_ = localVal.bit_field.blemac_need_swc_clk_31_0_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_blemac_need_swc_clk_31_0__getf(void)
{
    return hwp_ble_mdm->blemac_need_swc_clk_0.bit_field.blemac_need_swc_clk_31_0_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_need_swc_clk_31_0__setf(uint32_t blemac_need_swc_clk_31_0_)
{
    hwp_ble_mdm->blemac_need_swc_clk_0.bit_field.blemac_need_swc_clk_31_0_ = blemac_need_swc_clk_31_0_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_blemac_need_swc_clk_1_get(void)
{
    return hwp_ble_mdm->blemac_need_swc_clk_1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_need_swc_clk_1_set(uint32_t value)
{
    hwp_ble_mdm->blemac_need_swc_clk_1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_need_swc_clk_1_pack(uint8_t blemac_need_swc_clk_39_32_)
{
    hwp_ble_mdm->blemac_need_swc_clk_1.val = (((uint32_t)blemac_need_swc_clk_39_32_ << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_need_swc_clk_1_unpack(uint8_t* blemac_need_swc_clk_39_32_)
{
    T_BLE_MDM_BLEMAC_NEED_SWC_CLK_1 localVal = hwp_ble_mdm->blemac_need_swc_clk_1;

    *blemac_need_swc_clk_39_32_ = localVal.bit_field.blemac_need_swc_clk_39_32_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_blemac_need_swc_clk_39_32__getf(void)
{
    return hwp_ble_mdm->blemac_need_swc_clk_1.bit_field.blemac_need_swc_clk_39_32_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_blemac_need_swc_clk_39_32__setf(uint8_t blemac_need_swc_clk_39_32_)
{
    hwp_ble_mdm->blemac_need_swc_clk_1.bit_field.blemac_need_swc_clk_39_32_ = blemac_need_swc_clk_39_32_;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_tx_timing_get(void)
{
    return hwp_ble_mdm->tx_timing.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_tx_timing_set(uint32_t value)
{
    hwp_ble_mdm->tx_timing.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_tx_timing_pack(uint8_t o_tx_sdm_delay, uint8_t o_tx_vco_delay, uint16_t o_tx_en_off_delay)
{
    hwp_ble_mdm->tx_timing.val = (((uint32_t)o_tx_sdm_delay << 18) | ((uint32_t)o_tx_vco_delay << 16) | ((uint32_t)o_tx_en_off_delay << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_tx_timing_unpack(uint8_t* o_tx_sdm_delay, uint8_t* o_tx_vco_delay, uint16_t* o_tx_en_off_delay)
{
    T_BLE_MDM_TX_TIMING localVal = hwp_ble_mdm->tx_timing;

    *o_tx_sdm_delay = localVal.bit_field.o_tx_sdm_delay;
    *o_tx_vco_delay = localVal.bit_field.o_tx_vco_delay;
    *o_tx_en_off_delay = localVal.bit_field.o_tx_en_off_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_sdm_delay_getf(void)
{
    return hwp_ble_mdm->tx_timing.bit_field.o_tx_sdm_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_sdm_delay_setf(uint8_t o_tx_sdm_delay)
{
    hwp_ble_mdm->tx_timing.bit_field.o_tx_sdm_delay = o_tx_sdm_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_tx_vco_delay_getf(void)
{
    return hwp_ble_mdm->tx_timing.bit_field.o_tx_vco_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_vco_delay_setf(uint8_t o_tx_vco_delay)
{
    hwp_ble_mdm->tx_timing.bit_field.o_tx_vco_delay = o_tx_vco_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t ble_mdm_o_tx_en_off_delay_getf(void)
{
    return hwp_ble_mdm->tx_timing.bit_field.o_tx_en_off_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_tx_en_off_delay_setf(uint16_t o_tx_en_off_delay)
{
    hwp_ble_mdm->tx_timing.bit_field.o_tx_en_off_delay = o_tx_en_off_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_as_rf_chip_get(void)
{
    return hwp_ble_mdm->as_rf_chip.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_as_rf_chip_set(uint32_t value)
{
    hwp_ble_mdm->as_rf_chip.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_as_rf_chip_pack(uint8_t rf_chip_en, uint8_t rf_chip_freq_num, uint8_t rf_chip_power, uint8_t rf_chip_pgm_edge_sel, uint8_t rf_chip_rxclk_inv, uint8_t rf_chip_txclk_inv, uint8_t rf_chip_rxen, uint8_t rf_chip_txen, uint8_t rf_chip_rate)
{
    hwp_ble_mdm->as_rf_chip.val = (((uint32_t)rf_chip_en << 31) | ((uint32_t)rf_chip_freq_num << 16) | ((uint32_t)rf_chip_power << 8) | ((uint32_t)rf_chip_pgm_edge_sel << 6) | ((uint32_t)rf_chip_rxclk_inv << 5) | ((uint32_t)rf_chip_txclk_inv << 4) | ((uint32_t)rf_chip_rxen << 3) | ((uint32_t)rf_chip_txen << 2) | ((uint32_t)rf_chip_rate << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_as_rf_chip_unpack(uint8_t* rf_chip_en, uint8_t* rf_chip_freq_num, uint8_t* rf_chip_power, uint8_t* rf_chip_pgm_edge_sel, uint8_t* rf_chip_rxclk_inv, uint8_t* rf_chip_txclk_inv, uint8_t* rf_chip_rxen, uint8_t* rf_chip_txen, uint8_t* rf_chip_rate)
{
    T_BLE_MDM_AS_RF_CHIP localVal = hwp_ble_mdm->as_rf_chip;

    *rf_chip_en = localVal.bit_field.rf_chip_en;
    *rf_chip_freq_num = localVal.bit_field.rf_chip_freq_num;
    *rf_chip_power = localVal.bit_field.rf_chip_power;
    *rf_chip_pgm_edge_sel = localVal.bit_field.rf_chip_pgm_edge_sel;
    *rf_chip_rxclk_inv = localVal.bit_field.rf_chip_rxclk_inv;
    *rf_chip_txclk_inv = localVal.bit_field.rf_chip_txclk_inv;
    *rf_chip_rxen = localVal.bit_field.rf_chip_rxen;
    *rf_chip_txen = localVal.bit_field.rf_chip_txen;
    *rf_chip_rate = localVal.bit_field.rf_chip_rate;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rf_chip_en_getf(void)
{
    return hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rf_chip_en_setf(uint8_t rf_chip_en)
{
    hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_en = rf_chip_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rf_chip_freq_num_getf(void)
{
    return hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_freq_num;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rf_chip_freq_num_setf(uint8_t rf_chip_freq_num)
{
    hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_freq_num = rf_chip_freq_num;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rf_chip_power_getf(void)
{
    return hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_power;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rf_chip_power_setf(uint8_t rf_chip_power)
{
    hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_power = rf_chip_power;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rf_chip_pgm_edge_sel_getf(void)
{
    return hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_pgm_edge_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rf_chip_pgm_edge_sel_setf(uint8_t rf_chip_pgm_edge_sel)
{
    hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_pgm_edge_sel = rf_chip_pgm_edge_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rf_chip_rxclk_inv_getf(void)
{
    return hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_rxclk_inv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rf_chip_rxclk_inv_setf(uint8_t rf_chip_rxclk_inv)
{
    hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_rxclk_inv = rf_chip_rxclk_inv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rf_chip_txclk_inv_getf(void)
{
    return hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_txclk_inv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rf_chip_txclk_inv_setf(uint8_t rf_chip_txclk_inv)
{
    hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_txclk_inv = rf_chip_txclk_inv;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rf_chip_rxen_getf(void)
{
    return hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_rxen;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rf_chip_rxen_setf(uint8_t rf_chip_rxen)
{
    hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_rxen = rf_chip_rxen;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rf_chip_txen_getf(void)
{
    return hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_txen;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rf_chip_txen_setf(uint8_t rf_chip_txen)
{
    hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_txen = rf_chip_txen;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_rf_chip_rate_getf(void)
{
    return hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_rate;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_rf_chip_rate_setf(uint8_t rf_chip_rate)
{
    hwp_ble_mdm->as_rf_chip.bit_field.rf_chip_rate = rf_chip_rate;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_adc_rssi_reg_get(void)
{
    return hwp_ble_mdm->adc_rssi_reg.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_adc_rssi_reg_set(uint32_t value)
{
    hwp_ble_mdm->adc_rssi_reg.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_adc_rssi_reg_pack(uint8_t o_agc_rssi_avg_num, uint8_t o_adc_rssi_agc_en, uint8_t o_adc_rssi_clk_pol, uint16_t o_adc_rssi_ldo_delay)
{
    hwp_ble_mdm->adc_rssi_reg.val = (((uint32_t)o_agc_rssi_avg_num << 12) | ((uint32_t)o_adc_rssi_agc_en << 11) | ((uint32_t)o_adc_rssi_clk_pol << 10) | ((uint32_t)o_adc_rssi_ldo_delay << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_adc_rssi_reg_unpack(uint8_t* o_agc_rssi_avg_num, uint8_t* o_adc_rssi_agc_en, uint8_t* o_adc_rssi_clk_pol, uint16_t* o_adc_rssi_ldo_delay)
{
    T_BLE_MDM_ADC_RSSI_REG localVal = hwp_ble_mdm->adc_rssi_reg;

    *o_agc_rssi_avg_num = localVal.bit_field.o_agc_rssi_avg_num;
    *o_adc_rssi_agc_en = localVal.bit_field.o_adc_rssi_agc_en;
    *o_adc_rssi_clk_pol = localVal.bit_field.o_adc_rssi_clk_pol;
    *o_adc_rssi_ldo_delay = localVal.bit_field.o_adc_rssi_ldo_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_agc_rssi_avg_num_getf(void)
{
    return hwp_ble_mdm->adc_rssi_reg.bit_field.o_agc_rssi_avg_num;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_agc_rssi_avg_num_setf(uint8_t o_agc_rssi_avg_num)
{
    hwp_ble_mdm->adc_rssi_reg.bit_field.o_agc_rssi_avg_num = o_agc_rssi_avg_num;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_adc_rssi_agc_en_getf(void)
{
    return hwp_ble_mdm->adc_rssi_reg.bit_field.o_adc_rssi_agc_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_adc_rssi_agc_en_setf(uint8_t o_adc_rssi_agc_en)
{
    hwp_ble_mdm->adc_rssi_reg.bit_field.o_adc_rssi_agc_en = o_adc_rssi_agc_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_o_adc_rssi_clk_pol_getf(void)
{
    return hwp_ble_mdm->adc_rssi_reg.bit_field.o_adc_rssi_clk_pol;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_adc_rssi_clk_pol_setf(uint8_t o_adc_rssi_clk_pol)
{
    hwp_ble_mdm->adc_rssi_reg.bit_field.o_adc_rssi_clk_pol = o_adc_rssi_clk_pol;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t ble_mdm_o_adc_rssi_ldo_delay_getf(void)
{
    return hwp_ble_mdm->adc_rssi_reg.bit_field.o_adc_rssi_ldo_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_o_adc_rssi_ldo_delay_setf(uint16_t o_adc_rssi_ldo_delay)
{
    hwp_ble_mdm->adc_rssi_reg.bit_field.o_adc_rssi_ldo_delay = o_adc_rssi_ldo_delay;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_vco_cal_state_get(void)
{
    return hwp_ble_mdm->vco_cal_state.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_state_set(uint32_t value)
{
    hwp_ble_mdm->vco_cal_state.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_state_pack(uint8_t vco_deviation_cal_start)
{
    hwp_ble_mdm->vco_cal_state.val = (((uint32_t)vco_deviation_cal_start << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_state_unpack(uint8_t* vco_band_cal_done, uint8_t* in_vco_devia_cal, uint8_t* vco_deviation_cal_start)
{
    T_BLE_MDM_VCO_CAL_STATE localVal = hwp_ble_mdm->vco_cal_state;

    *vco_band_cal_done = localVal.bit_field.vco_band_cal_done;
    *in_vco_devia_cal = localVal.bit_field.in_vco_devia_cal;
    *vco_deviation_cal_start = localVal.bit_field.vco_deviation_cal_start;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_vco_band_cal_done_getf(void)
{
    return hwp_ble_mdm->vco_cal_state.bit_field.vco_band_cal_done;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_in_vco_devia_cal_getf(void)
{
    return hwp_ble_mdm->vco_cal_state.bit_field.in_vco_devia_cal;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_vco_deviation_cal_start_getf(void)
{
    return hwp_ble_mdm->vco_cal_state.bit_field.vco_deviation_cal_start;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_deviation_cal_start_setf(uint8_t vco_deviation_cal_start)
{
    hwp_ble_mdm->vco_cal_state.bit_field.vco_deviation_cal_start = vco_deviation_cal_start;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_vco_cal_capdev_1_get(void)
{
    return hwp_ble_mdm->vco_cal_capdev_1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_1_set(uint32_t value)
{
    hwp_ble_mdm->vco_cal_capdev_1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_1_pack(uint16_t vcocali_capdev_1)
{
    hwp_ble_mdm->vco_cal_capdev_1.val = (((uint32_t)vcocali_capdev_1 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_1_unpack(uint16_t* vcocali_capdev_1)
{
    T_BLE_MDM_VCO_CAL_CAPDEV_1 localVal = hwp_ble_mdm->vco_cal_capdev_1;

    *vcocali_capdev_1 = localVal.bit_field.vcocali_capdev_1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t ble_mdm_vcocali_capdev_1_getf(void)
{
    return hwp_ble_mdm->vco_cal_capdev_1.bit_field.vcocali_capdev_1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vcocali_capdev_1_setf(uint16_t vcocali_capdev_1)
{
    hwp_ble_mdm->vco_cal_capdev_1.bit_field.vcocali_capdev_1 = vcocali_capdev_1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_vco_cal_capdev_2_get(void)
{
    return hwp_ble_mdm->vco_cal_capdev_2.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_2_set(uint32_t value)
{
    hwp_ble_mdm->vco_cal_capdev_2.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_2_pack(uint16_t vcocali_capdev_2)
{
    hwp_ble_mdm->vco_cal_capdev_2.val = (((uint32_t)vcocali_capdev_2 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_2_unpack(uint16_t* vcocali_capdev_2)
{
    T_BLE_MDM_VCO_CAL_CAPDEV_2 localVal = hwp_ble_mdm->vco_cal_capdev_2;

    *vcocali_capdev_2 = localVal.bit_field.vcocali_capdev_2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t ble_mdm_vcocali_capdev_2_getf(void)
{
    return hwp_ble_mdm->vco_cal_capdev_2.bit_field.vcocali_capdev_2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vcocali_capdev_2_setf(uint16_t vcocali_capdev_2)
{
    hwp_ble_mdm->vco_cal_capdev_2.bit_field.vcocali_capdev_2 = vcocali_capdev_2;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_vco_cal_capdev_3_get(void)
{
    return hwp_ble_mdm->vco_cal_capdev_3.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_3_set(uint32_t value)
{
    hwp_ble_mdm->vco_cal_capdev_3.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_3_pack(uint16_t vcocali_capdev_3)
{
    hwp_ble_mdm->vco_cal_capdev_3.val = (((uint32_t)vcocali_capdev_3 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_3_unpack(uint16_t* vcocali_capdev_3)
{
    T_BLE_MDM_VCO_CAL_CAPDEV_3 localVal = hwp_ble_mdm->vco_cal_capdev_3;

    *vcocali_capdev_3 = localVal.bit_field.vcocali_capdev_3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t ble_mdm_vcocali_capdev_3_getf(void)
{
    return hwp_ble_mdm->vco_cal_capdev_3.bit_field.vcocali_capdev_3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vcocali_capdev_3_setf(uint16_t vcocali_capdev_3)
{
    hwp_ble_mdm->vco_cal_capdev_3.bit_field.vcocali_capdev_3 = vcocali_capdev_3;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_vco_cal_capdev_4_get(void)
{
    return hwp_ble_mdm->vco_cal_capdev_4.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_4_set(uint32_t value)
{
    hwp_ble_mdm->vco_cal_capdev_4.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_4_pack(uint16_t vcocali_capdev_4)
{
    hwp_ble_mdm->vco_cal_capdev_4.val = (((uint32_t)vcocali_capdev_4 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_capdev_4_unpack(uint16_t* vcocali_capdev_4)
{
    T_BLE_MDM_VCO_CAL_CAPDEV_4 localVal = hwp_ble_mdm->vco_cal_capdev_4;

    *vcocali_capdev_4 = localVal.bit_field.vcocali_capdev_4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint16_t ble_mdm_vcocali_capdev_4_getf(void)
{
    return hwp_ble_mdm->vco_cal_capdev_4.bit_field.vcocali_capdev_4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vcocali_capdev_4_setf(uint16_t vcocali_capdev_4)
{
    hwp_ble_mdm->vco_cal_capdev_4.bit_field.vcocali_capdev_4 = vcocali_capdev_4;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t ble_mdm_vco_cal_para_get(void)
{
    return hwp_ble_mdm->vco_cal_para.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_para_set(uint32_t value)
{
    hwp_ble_mdm->vco_cal_para.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_para_pack(uint8_t vco_band_offset, uint8_t vco_cnt_spacing, uint8_t vco_stb_time)
{
    hwp_ble_mdm->vco_cal_para.val = (((uint32_t)vco_band_offset << 8) | ((uint32_t)vco_cnt_spacing << 4) | ((uint32_t)vco_stb_time << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cal_para_unpack(uint8_t* vco_band_offset, uint8_t* vco_cnt_spacing, uint8_t* vco_stb_time)
{
    T_BLE_MDM_VCO_CAL_PARA localVal = hwp_ble_mdm->vco_cal_para;

    *vco_band_offset = localVal.bit_field.vco_band_offset;
    *vco_cnt_spacing = localVal.bit_field.vco_cnt_spacing;
    *vco_stb_time = localVal.bit_field.vco_stb_time;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_vco_band_offset_getf(void)
{
    return hwp_ble_mdm->vco_cal_para.bit_field.vco_band_offset;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_band_offset_setf(uint8_t vco_band_offset)
{
    hwp_ble_mdm->vco_cal_para.bit_field.vco_band_offset = vco_band_offset;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_vco_cnt_spacing_getf(void)
{
    return hwp_ble_mdm->vco_cal_para.bit_field.vco_cnt_spacing;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_cnt_spacing_setf(uint8_t vco_cnt_spacing)
{
    hwp_ble_mdm->vco_cal_para.bit_field.vco_cnt_spacing = vco_cnt_spacing;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t ble_mdm_vco_stb_time_getf(void)
{
    return hwp_ble_mdm->vco_cal_para.bit_field.vco_stb_time;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void ble_mdm_vco_stb_time_setf(uint8_t vco_stb_time)
{
    hwp_ble_mdm->vco_cal_para.bit_field.vco_stb_time = vco_stb_time;
}
#ifdef __cplusplus
}
#endif

#endif /* __REG_BLE_MDM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

