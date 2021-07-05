/**
 ****************************************************************************************
 *
 * @file modem.c
 *
 * @brief Implementation of modem functions
 *
 * Copyright (C) Apollo
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup MODEM
 * @ingroup DRIVERS
 *
 * @{
 ****************************************************************************************
 */

#include "bx_config.h"
#include "modem.h"
#include "reg_sysc_awo.h"
#include "log.h"
#include "plf.h"
#include "compiler_flag.h"
#include "reg_sysc_awo_apollo_00.h"
#include <string.h>


#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
#define RSSI_AVG_NUM 8
#define VCO_CALIB_NUM 64
#define VCO_CALIB_PARA 0x477
struct vco_capdev_t
{
    uint8_t valid;
//    uint16_t vco_capdev[4];
};

struct vco_capdev_t vco_calibration =
{
    .valid = 0,
};

static uint32_t vco_save_others[4];
static uint32_t vco_save_aa55[4];
typedef struct
{
    uint32_t band0_2M;
    uint32_t band1_2M;
    uint32_t band2_2M;
    uint32_t band3_2M;
    uint32_t band0_1M;
    uint32_t band1_1M;
    uint32_t band2_1M;
    uint32_t band3_1M;
} calib_val_t;

void modem_vcocali_start()      //vco calibration will take 7ms at most.
{
    calib_val_t calib_val;
    memset(&calib_val,0,sizeof(calib_val));
    for(uint8_t i = 0; i < VCO_CALIB_NUM; i++)
    {
        ble_mdm_vco_deviation_cal_start_setf(1);
        while(!ble_mdm_vco_deviation_cal_start_getf()); // sync register
        BX_DELAY_US(1);
        while(ble_mdm_in_vco_devia_cal_getf()); //wait vco calibration finish
        ble_mdm_vco_deviation_cal_start_setf(0);
                                        
        calib_val.band0_2M += (ble_mdm_vcocali_capdev_1_getf()>>6)&0x3f;
        calib_val.band1_2M += (ble_mdm_vcocali_capdev_2_getf()>>6)&0x3f;
        calib_val.band2_2M += (ble_mdm_vcocali_capdev_3_getf()>>6)&0x3f;
        calib_val.band3_2M += (ble_mdm_vcocali_capdev_4_getf()>>6)&0x3f;
        
        calib_val.band0_1M += ble_mdm_vcocali_capdev_1_getf()&0x3f;
        calib_val.band1_1M += ble_mdm_vcocali_capdev_2_getf()&0x3f;
        calib_val.band2_1M += ble_mdm_vcocali_capdev_3_getf()&0x3f;
        calib_val.band3_1M += ble_mdm_vcocali_capdev_4_getf()&0x3f;
    
        ble_mdm_vcocali_capdev_1_setf(0);
        ble_mdm_vcocali_capdev_2_setf(0);
        ble_mdm_vcocali_capdev_3_setf(0);
        ble_mdm_vcocali_capdev_4_setf(0);
    }

    calib_val.band0_2M = (calib_val.band0_2M - 7)/VCO_CALIB_NUM;
    calib_val.band1_2M = (calib_val.band1_2M - 7)/VCO_CALIB_NUM;
    calib_val.band2_2M = (calib_val.band2_2M - 7)/VCO_CALIB_NUM;
    calib_val.band3_2M = (calib_val.band3_2M - 7)/VCO_CALIB_NUM;
    calib_val.band0_1M = (calib_val.band0_1M - 7)/VCO_CALIB_NUM;
    calib_val.band1_1M = (calib_val.band1_1M - 7)/VCO_CALIB_NUM;
    calib_val.band2_1M = (calib_val.band2_1M - 7)/VCO_CALIB_NUM;
    calib_val.band3_1M = (calib_val.band3_1M - 7)/VCO_CALIB_NUM;

    vco_save_others[0] =((calib_val.band0_1M*2)<<6) | calib_val.band0_1M;
    vco_save_others[1] =((calib_val.band1_1M*2)<<6) | calib_val.band1_1M;
    vco_save_others[2] =((calib_val.band2_1M*2)<<6) | calib_val.band2_1M;
    vco_save_others[3] =((calib_val.band3_1M*2)<<6) | calib_val.band3_1M;
    vco_save_aa55[0] = (((calib_val.band0_1M+2)*2)<<6) | (calib_val.band0_1M+2);
    vco_save_aa55[1] = (((calib_val.band1_1M+2)*2)<<6) | (calib_val.band1_1M+2);
    vco_save_aa55[2] = (((calib_val.band2_1M+2)*2)<<6) | (calib_val.band2_1M+2);
    vco_save_aa55[3] = (((calib_val.band3_1M+2)*2)<<6) | (calib_val.band3_1M+2);

    enable_vco_value(false);
	//LOG_RAW("2 - O1 = %x, O2 = %x, O3 = %x, O4 = %x\n", vco_save_others[0],vco_save_others[1],vco_save_others[2],vco_save_others[3]);
	//LOG_RAW("2 - A1 = %x, A2 = %x, A3 = %x, A4 = %x\n", vco_save_aa55[0],vco_save_aa55[1],vco_save_aa55[2],vco_save_aa55[3]);
}

void enable_vco_value(bool is_aa55)
{
    uint32_t *buff = is_aa55 ? vco_save_aa55 : vco_save_others;

    ble_mdm_vcocali_capdev_1_setf(buff[0]);
    ble_mdm_vcocali_capdev_2_setf(buff[1]);
    ble_mdm_vcocali_capdev_3_setf(buff[2]);
    ble_mdm_vcocali_capdev_4_setf(buff[3]);
}

void set_deriv_calib_0(uint8_t select)
{
  //enable_vco_value(select == 3);
	if(select==2)
	{
		ble_mdm_vcocali_capdev_1_setf( vco_save_others[0]);
		ble_mdm_vcocali_capdev_2_setf( vco_save_others[1]);
		ble_mdm_vcocali_capdev_3_setf( vco_save_others[2]);
		ble_mdm_vcocali_capdev_4_setf( vco_save_others[3]);

		//enable_vco_value(false);
	}
	else
	{
		ble_mdm_vcocali_capdev_1_setf( vco_save_aa55[0]);
		ble_mdm_vcocali_capdev_2_setf( vco_save_aa55[1]);
		ble_mdm_vcocali_capdev_3_setf( vco_save_aa55[2]);
		ble_mdm_vcocali_capdev_4_setf( vco_save_aa55[3]);
		//enable_vco_value(true);
	}
}

void modem_vcocali(void)
{
    vco_calibration.valid = 1;
}

static void modem_vcocali_value_restore()
{
    if(vco_calibration.valid)
    {
        set_deriv_calib_0(2);
        ble_mdm_vco_cal_para_set(VCO_CALIB_PARA);
    }
}

#endif

void modem_dev_calib_in_main(void)
{
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
    modem_vcocali_start();
    modem_vcocali();             //put it here temporarily, can be move to some place 7.5ms after modem_vcocali_start()
#else
    *( ( volatile uint32_t * )  0x20110044 ) = 0x84F;
    *( ( volatile uint32_t * )  0x20110048 ) = 0x80F;
    *( ( volatile uint32_t * )  0x2011004C ) = 0x7CE;
    *( ( volatile uint32_t * )  0x20110050 ) = 0x78E;
#endif

    ble_mdm_vco_cal_para_set(VCO_CALIB_PARA);
}

void modem_init()
{
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
//    modem_vcocali_value_restore();
 // Modify default values in modem
    ble_mdm_o_rx_samp_delay_setf(5);
    ble_mdm_o_tx_samp_delay_setf(4);
    ble_mdm_o_tx_pkt_vld_delay_setf(0x24);
    ble_mdm_o_extend_rx_en_low_delay_setf(4);
    ble_mdm_o_rx_iq_format_setf(3);
    ble_mdm_o_tx_sdm_order2_setf(1);

    uint32_t reg_ro_val = sysc_awo_rf_reg_rd_get();
    switch (reg_ro_val&0x1f)
    {
    case APOLLO_00_V4A_V4AMC: // V4am
    case APOLLO_00_V4B_V4BMC: // V4bm
        ble_mdm_vco_cal_para_set(VCO_CALIB_PARA);
        break;
    case APOLLO_00_A01:
    case APOLLO_00_A02:
    case APOLLO_00_A03:
    case APOLLO_00_A04:
    case APOLLO_00_A05:
    case APOLLO_00_A06:
    case APOLLO_00_A07:
    case APOLLO_00_A08:
    case APOLLO_00_A09:
    case APOLLO_00_A10:
    case APOLLO_00_A11:
    case APOLLO_00_A12:
    case APOLLO_00_B1:
    case APOLLO_00_B2:
    case APOLLO_00_B3:
        ble_mdm_vco_cal_para_set(VCO_CALIB_PARA); // A1
        break;
    default:
        ble_mdm_vco_cal_para_set(VCO_CALIB_PARA);
//        BX_ASSERT(0);
        break;
    }

    ble_mdm_vco_cnt_spacing_setf(0x4);

    ble_mdm_o_tx_clk_sel_setf(0);

    ble_mdm_o_agc_rssi_avg_num_setf(RSSI_AVG_NUM - 1); //for set rssi_avg_num 8

    modem_vcocali_value_restore(); // move here to update parameters from Frank

#ifdef HARMONIC_ENABLE
    ble_mdm_clk_rf_2sel_setf(0x21);

    ble_mdm_blemac_need_swc_clk_0_set(0xaaaaaaaa);      // for test. 0xaa..a should be change in real application
    ble_mdm_blemac_need_swc_clk_1_set(0xaa);            // for test. 0xaa..a should be change in real application

    ble_mdm_need_rate_conv_num_31_0__setf(0xaaaaaaaa);  // for test. 0xaa..a should be change in real application
    ble_mdm_need_rate_conv_num_39_32__setf(0xaa);       // for test. 0xaa..a should be change in real application
#else
    ble_mdm_need_rate_conv_num_31_0__setf(0x0);
    ble_mdm_need_rate_conv_num_39_32__setf(0x0);

#endif

#endif

}



