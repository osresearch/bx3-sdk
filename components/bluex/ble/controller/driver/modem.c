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
#include "modem.h"
#include "reg_sysc_awo.h"
#include "reg_sysc_awo_apollo_00.h"
#include "log.h"
#include "plf.h"
#include "compiler_flag.h"

/* private define ------------------------------------------------------------*/
//#define HARMONIC_ENABLE

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


/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



#if RF_PARAM == 0
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
#define RSSI_AVG_NUM 8
#define VCO_CALIB_NUM 16
struct vco_capdev_t {
    uint8_t valid;
    uint16_t vco_capdev[4];
};

struct vco_capdev_t vco_calibration = {
    .valid = 0,
};

void modem_vcocali_start()      //vco calibration will take 7ms at most.
{
    ble_mdm_vco_deviation_cal_start_setf( 1 );  //start vco calibration
}

void modem_vcocali( void )
{
    uint32_t calib_val[4];
    uint16_t avg_num;
    if( vco_calibration.valid == 0 ) {
        memset( ( uint8_t * )calib_val, 0, sizeof( calib_val ) );
        for( uint8_t i = 0; i < VCO_CALIB_NUM; i++ ) {
            modem_vcocali_start();
            while( !ble_mdm_vco_deviation_cal_start_getf() ); // sync register
            BX_DELAY_US( 1 );
            while( ble_mdm_in_vco_devia_cal_getf() ); //wait vco calibration finish
            ble_mdm_vco_deviation_cal_start_setf( 0 );

            calib_val[0] += ble_mdm_vcocali_capdev_1_getf() & 0x3f;
            calib_val[1] += ble_mdm_vcocali_capdev_2_getf() & 0x3f;
            calib_val[2] += ble_mdm_vcocali_capdev_3_getf() & 0x3f;
            calib_val[3] += ble_mdm_vcocali_capdev_4_getf() & 0x3f;
            ble_mdm_vcocali_capdev_1_setf( 0 );
            ble_mdm_vcocali_capdev_2_setf( 0 );
            ble_mdm_vcocali_capdev_3_setf( 0 );
            ble_mdm_vcocali_capdev_4_setf( 0 );
        }

        for( uint8_t i = 0; i < 4; i++ ) {
            avg_num = calib_val[i] / VCO_CALIB_NUM;
            if( calib_val[i] - avg_num * VCO_CALIB_NUM >= VCO_CALIB_NUM / 2 ) {
                avg_num++;
            }
            vco_calibration.vco_capdev[i] = avg_num;
        }
        ble_mdm_vcocali_capdev_1_setf( vco_calibration.vco_capdev[0] | ( ( vco_calibration.vco_capdev[0] * 2 ) << 6 ) );
        ble_mdm_vcocali_capdev_2_setf( vco_calibration.vco_capdev[1] | ( ( vco_calibration.vco_capdev[1] * 2 ) << 6 ) );
        ble_mdm_vcocali_capdev_3_setf( vco_calibration.vco_capdev[2] | ( ( vco_calibration.vco_capdev[2] * 2 ) << 6 ) );
        ble_mdm_vcocali_capdev_4_setf( vco_calibration.vco_capdev[3] | ( ( vco_calibration.vco_capdev[3] * 2 ) << 6 ) );
    }
    vco_calibration.valid = 1;
}

N_XIP_SECTION static void modem_vcocali_value_restore()
{
    if( vco_calibration.valid ) {
        ble_mdm_vcocali_capdev_1_setf( vco_calibration.vco_capdev[0] | ( ( vco_calibration.vco_capdev[0] * 2 ) << 6 ) );
        ble_mdm_vcocali_capdev_2_setf( vco_calibration.vco_capdev[1] | ( ( vco_calibration.vco_capdev[1] * 2 ) << 6 ) );
        ble_mdm_vcocali_capdev_3_setf( vco_calibration.vco_capdev[2] | ( ( vco_calibration.vco_capdev[2] * 2 ) << 6 ) );
        ble_mdm_vcocali_capdev_4_setf( vco_calibration.vco_capdev[3] | ( ( vco_calibration.vco_capdev[3] * 2 ) << 6 ) );
//        LOG(LOG_LVL_INFO,"vco restore to modem\n");
    }
}


#endif

#ifdef DEV_PATCH_V3

//#define TX_EN_TEST
#define RX_EN_TEST

#define CALIB_US * 6

void devi_rxtx_on_patch( void )
{
    *( uint32_t * )0x20110000 = *( ( uint32_t * )0x20110000 ) | ( 1 << 20 ); // Enbale rf IQ mode
    *( uint32_t * )0x20110034 = *( ( uint32_t * )0x20110034 ) | ( 1 << 31 ); // freq = 0, rf_chip_en = 1
//    for(uint32_t i=0; i < 10000; i++)
    {
        __asm( "nop" );
    }
#ifdef RX_EN_TEST
    *( uint32_t * )0x20110034 = *( ( uint32_t * )0x20110034 ) | ( 1 << 3 ); // rx_en = 1
#endif
#ifdef TX_EN_TEST
    *( uint32_t * )0x20110034 = *( ( uint32_t * )0x20110034 ) | ( 1 << 2 ); // tx_en = 1
#endif
    for( uint32_t i = 0; i < 9000 CALIB_US; i++ ) {
        __asm( "nop" );
    }
}

void devi_rxtx_off_patch( void )
{
    *( uint32_t * )0x20110000 = *( uint32_t * )0x20110000 & ~( 1 << 20 ); // Disable rf IQ mode
    *( uint32_t * )0x20110034 = *( uint32_t * )0x20110034 & ~( 1 << 31 ); // rf_chip_en = 0
    *( uint32_t * )0x20110034 = *( uint32_t * )0x20110034 & ~( 1 << 3 ); // rx_en = 0
}


void devi_minus_val( void )      // the result of deviation calibration should minus one
{
    uint32_t * calib_val_addr = ( uint32_t * )0x20110044;
    LOG( LOG_LVL_INFO, "previous calib val\n" );
    while( calib_val_addr < ( uint32_t * )0x20110054 ) {
        LOG( LOG_LVL_INFO, "0x%8x\n", *calib_val_addr );
        *calib_val_addr -= 1;
        calib_val_addr++;
    }
}

#endif

void modem_dev_calib_in_main( void )
{
#ifdef DEV_PATCH_V3
    devi_rxtx_on_patch();
#endif
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
//    modem_vcocali_start();
    modem_vcocali();             //put it here temporarily, can be move to some place 7.5ms after modem_vcocali_start()
#else
    *( ( volatile uint32_t * )  0x20110044 ) = 0x84F;
    *( ( volatile uint32_t * )  0x20110048 ) = 0x80F;
    *( ( volatile uint32_t * )  0x2011004C ) = 0x7CE;
    *( ( volatile uint32_t * )  0x20110050 ) = 0x78E;
#endif
#ifdef DEV_PATCH_V3
    devi_rxtx_off_patch();
    devi_minus_val();
#endif
    ble_mdm_vco_cnt_spacing_setf( 0x6 );
    ble_mdm_vco_stb_time_setf( 0x3 );

}


N_XIP_SECTION void modem_init()
{
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
    modem_vcocali_value_restore();
    // Modify default values in modem
    ble_mdm_o_rx_samp_delay_setf( 5 );
    ble_mdm_o_tx_samp_delay_setf( 4 );
    ble_mdm_o_tx_pkt_vld_delay_setf( 0x24 );
    ble_mdm_o_extend_rx_en_low_delay_setf( 4 );
    ble_mdm_o_rx_iq_format_setf( 3 );
    ble_mdm_o_tx_sdm_order2_setf( 1 );

    uint32_t reg_ro_val = sysc_awo_rf_reg_rd_get();
    switch ( reg_ro_val & 0x1f ) {
        case APOLLO_00_V4A_V4AMC: // V4am
        case APOLLO_00_V4B_V4BMC: // V4bm
            ble_mdm_vco_stb_time_setf( 0x3 );
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
            ble_mdm_vco_stb_time_setf( 0x3 ); // A1
            break;
        default:
            ble_mdm_vco_stb_time_setf( 0x3 );
//        BX_ASSERT(0);
            break;
    }
    ble_mdm_vco_cnt_spacing_setf( 0x5 );

    ble_mdm_o_tx_clk_sel_setf( 0 );

    ble_mdm_o_agc_rssi_avg_num_setf( RSSI_AVG_NUM - 1 ); //for set rssi_avg_num 8

#ifdef HARMONIC_ENABLE
    ble_mdm_clk_rf_2sel_setf( 0x21 );

    ble_mdm_blemac_need_swc_clk_0_set( 0xaaaaaaaa );    // for test. 0xaa..a should be change in real application
    ble_mdm_blemac_need_swc_clk_1_set( 0xaa );          // for test. 0xaa..a should be change in real application

    ble_mdm_need_rate_conv_num_31_0__setf( 0xaaaaaaaa ); // for test. 0xaa..a should be change in real application
    ble_mdm_need_rate_conv_num_39_32__setf( 0xaa );     // for test. 0xaa..a should be change in real application
#else
    ble_mdm_need_rate_conv_num_31_0__setf( 0x0 );
    ble_mdm_need_rate_conv_num_39_32__setf( 0x0 );

#endif

#endif

}
#elif RF_PARAM == 1
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
#define RSSI_AVG_NUM 8
#define VCO_CALIB_PARA 0x477
struct vco_capdev_t {
    uint8_t valid;
    uint16_t vco_capdev[4];
};

struct vco_capdev_t vco_calibration = {
    .valid = 0,
};

void modem_vcocali_start()      //vco calibration will take 7ms at most.
{
    ble_mdm_vco_deviation_cal_start_setf( 1 );  //start vco calibration
}
void set_deriv_calib_0( uint8_t select )
{
    if( select == 2 ) {
        ble_mdm_vcocali_capdev_1_setf( 0x78f );
        ble_mdm_vcocali_capdev_2_setf( 0x78f );
        ble_mdm_vcocali_capdev_3_setf( 0x78e );
        ble_mdm_vcocali_capdev_4_setf( 0x78e );
    } else if( select == 3 ) {
        ble_mdm_vcocali_capdev_1_setf( 0x811 );
        ble_mdm_vcocali_capdev_2_setf( 0x811 );
        ble_mdm_vcocali_capdev_3_setf( 0x810 );
        ble_mdm_vcocali_capdev_4_setf( 0x810 );
    }
}

void modem_vcocali( void )
{
    if( vco_calibration.valid == 0 ) {
        set_deriv_calib_0( 2 );
    }
    vco_calibration.valid = 1;
}

static void modem_vcocali_value_restore()
{
    if( vco_calibration.valid ) {
        set_deriv_calib_0( 2 );
//        LOG(LOG_LVL_INFO,"vco restore to modem\n");
//        ble_mdm_vco_cnt_spacing_setf(0x8);
//        ble_mdm_vco_stb_time_setf(0x3);
        ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );
    }
}
#endif

void modem_dev_calib_in_main( void )
{
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
//    modem_vcocali_start();
    modem_vcocali();             //put it here temporarily, can be move to some place 7.5ms after modem_vcocali_start()
#endif
//    ble_mdm_vco_cnt_spacing_setf(0x8);
//    ble_mdm_vco_stb_time_setf(0x3);
    ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );
}

void modem_init()
{
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
//    modem_vcocali_value_restore();
    // Modify default values in modem
    ble_mdm_o_rx_samp_delay_setf( 5 );
    ble_mdm_o_tx_samp_delay_setf( 4 );
    ble_mdm_o_tx_pkt_vld_delay_setf( 0x24 );
    ble_mdm_o_extend_rx_en_low_delay_setf( 4 );
    ble_mdm_o_rx_iq_format_setf( 3 );
    ble_mdm_o_tx_sdm_order2_setf( 1 );

    uint32_t reg_ro_val = sysc_awo_rf_reg_rd_get();
    void ble_mdm_vco_stb_time_setf( uint8_t vco_stb_time );
    switch ( reg_ro_val & 0x1f ) {
        case APOLLO_00_V4A_V4AMC: // V4am
        case APOLLO_00_V4B_V4BMC: // V4bm
//        ble_mdm_vco_stb_time_setf(0x3);
            ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );
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
//        ble_mdm_vco_stb_time_setf(0x3); // A1
            ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );
            break;
        default:
//        ble_mdm_vco_stb_time_setf(0x3);
            ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );
//        BX_ASSERT(0);
            break;
    }
//    void ble_mdm_vco_cnt_spacing_setf(uint8_t vco_cnt_spacing);
//    ble_mdm_vco_cnt_spacing_setf(0x4);
    ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );

    ble_mdm_o_tx_clk_sel_setf( 0 );

    ble_mdm_o_agc_rssi_avg_num_setf( RSSI_AVG_NUM - 1 ); //for set rssi_avg_num 8

    modem_vcocali_value_restore(); // move here to update parameters from Frank

#ifdef HARMONIC_ENABLE
    ble_mdm_clk_rf_2sel_setf( 0x21 );

    ble_mdm_blemac_need_swc_clk_0_set( 0xaaaaaaaa );    // for test. 0xaa..a should be change in real application
    ble_mdm_blemac_need_swc_clk_1_set( 0xaa );          // for test. 0xaa..a should be change in real application

    ble_mdm_need_rate_conv_num_31_0__setf( 0xaaaaaaaa ); // for test. 0xaa..a should be change in real application
    ble_mdm_need_rate_conv_num_39_32__setf( 0xaa );     // for test. 0xaa..a should be change in real application
#else
    ble_mdm_need_rate_conv_num_31_0__setf( 0x0 );
    ble_mdm_need_rate_conv_num_39_32__setf( 0x0 );

#endif

#endif
}
#elif RF_PARAM == 2 || RF_PARAM == 3

#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
#define RSSI_AVG_NUM 8
#define VCO_CALIB_NUM 64
#define VCO_CALIB_PARA 0x477
struct vco_capdev_t {
    uint8_t valid;
//    uint16_t vco_capdev[4];
};

struct vco_capdev_t vco_calibration = {
    .valid = 0,
};

//uint16_t deriv_calib_band0;
static uint32_t vco_save_others[4];
static uint32_t vco_save_aa55[4];

/**
 * @brief start vco calibration, the calibration should be finished before ble start work.
 * It takes about 7.5ms from vco calibration start to vco calibration finished. So modem_vcocali_start should be used as early as possible.
 */
void modem_vcocali_start()      //vco calibration will take 7ms at most.
{
    uint32_t calib_val_band_0;
    calib_val_band_0 = 0;
#if ((defined MODEM_DYNAMIC_DERIV_CALIB) && (MODEM_DYNAMIC_DERIV_CALIB == 1))
    uint32_t calib_val_band_1, calib_val_band_3;
    calib_val_band_1 = 0;
    calib_val_band_3 = 0;
#endif
    for( uint8_t i = 0; i < VCO_CALIB_NUM; i++ ) {
        ble_mdm_vco_deviation_cal_start_setf( 1 );
        while( !ble_mdm_vco_deviation_cal_start_getf() ); // sync register
        BX_DELAY_US( 1 );
        while( ble_mdm_in_vco_devia_cal_getf() ); //wait vco calibration finish
        ble_mdm_vco_deviation_cal_start_setf( 0 );

        calib_val_band_0 += ble_mdm_vcocali_capdev_1_getf() & 0x3f;
        ble_mdm_vcocali_capdev_1_setf( 0 );
#if ((defined MODEM_DYNAMIC_DERIV_CALIB) && (MODEM_DYNAMIC_DERIV_CALIB == 1))
        calib_val_band_1 += ble_mdm_vcocali_capdev_2_getf() & 0x3f;
        ble_mdm_vcocali_capdev_2_setf( 0 );
        calib_val_band_3 += ble_mdm_vcocali_capdev_4_getf() & 0x3f;
        ble_mdm_vcocali_capdev_4_setf( 0 );
#endif
    }
    uint16_t deriv_calib_band0 = ( uint16_t )( calib_val_band_0 / VCO_CALIB_NUM );
    vco_save_others[0] = ( ( deriv_calib_band0 * 2 ) << 6 ) | deriv_calib_band0;
    vco_save_aa55[0] = vco_save_others[0] + 2;
#if ((defined MODEM_DYNAMIC_DERIV_CALIB) && (MODEM_DYNAMIC_DERIV_CALIB == 1))
    uint16_t deriv_calib_band1 = ( uint16_t )( calib_val_band_1 / VCO_CALIB_NUM );
    vco_save_others[1] = ( ( deriv_calib_band1 * 2 ) << 6 ) | deriv_calib_band1;
    vco_save_aa55[1] = vco_save_others[1] + 2;

    uint16_t deriv_calib_band3 = ( uint16_t )( calib_val_band_3 / VCO_CALIB_NUM );
    vco_save_others[3] = ( ( deriv_calib_band3 * 2 ) << 6 ) | deriv_calib_band3;
    vco_save_aa55[3] = vco_save_others[3] + 2;
#endif
}

void set_vco_buff_aa55( uint32_t param2, uint32_t param3, uint32_t param4 )
{
#if !((defined MODEM_DYNAMIC_DERIV_CALIB) && (MODEM_DYNAMIC_DERIV_CALIB == 1))
    if( param2 != VCO_VALUE_INVALID ) {
        vco_save_aa55[1] = param2;
    }
#endif
    if( param3 != VCO_VALUE_INVALID ) {
        vco_save_aa55[2] = param3;
    }
#if !((defined MODEM_DYNAMIC_DERIV_CALIB) && (MODEM_DYNAMIC_DERIV_CALIB == 1))
    if( param4 != VCO_VALUE_INVALID ) {
        vco_save_aa55[3] = param4;
    }
#endif
}
void set_vco_buff_others( uint32_t param2, uint32_t param3, uint32_t param4 )
{
#if !((defined MODEM_DYNAMIC_DERIV_CALIB) && (MODEM_DYNAMIC_DERIV_CALIB == 1))
    if( param2 != VCO_VALUE_INVALID ) {
        vco_save_others[1] = param2;
    }
#endif
    if( param3 != VCO_VALUE_INVALID ) {
        vco_save_others[2] = param3;
    }
#if !((defined MODEM_DYNAMIC_DERIV_CALIB) && (MODEM_DYNAMIC_DERIV_CALIB == 1))
    if( param4 != VCO_VALUE_INVALID ) {
        vco_save_others[3] = param4;
    }
#endif
}
void enable_vco_value( bool is_aa55 )
{
    uint32_t * buff = is_aa55 ? vco_save_aa55 : vco_save_others;

    ble_mdm_vcocali_capdev_1_setf( buff[0] );
    ble_mdm_vcocali_capdev_2_setf( buff[1] );
    ble_mdm_vcocali_capdev_3_setf( buff[2] );
    ble_mdm_vcocali_capdev_4_setf( buff[3] );
}

void set_deriv_calib_0( uint8_t select )
{
    enable_vco_value( select == 3 );
}
/**
 * @brief wait vco calibration finish and save the result for future use.
 */
void modem_vcocali( void )
{
    vco_calibration.valid = 1;
}

static void modem_vcocali_value_restore()
{
    if( vco_calibration.valid ) {
        set_deriv_calib_0( 2 );
        ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );
    }
}

#endif

void modem_dev_calib_in_main( void )
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

    ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );
}


void modem_init()
{
#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
//    modem_vcocali_value_restore();
    // Modify default values in modem
    ble_mdm_o_rx_samp_delay_setf( 5 );
    ble_mdm_o_tx_samp_delay_setf( 4 );
    ble_mdm_o_tx_pkt_vld_delay_setf( 0x24 );
    ble_mdm_o_extend_rx_en_low_delay_setf( 4 );
    ble_mdm_o_rx_iq_format_setf( 3 );
    ble_mdm_o_tx_sdm_order2_setf( 1 );

    uint32_t reg_ro_val = sysc_awo_rf_reg_rd_get();
    switch ( reg_ro_val & 0x1f ) {
        case APOLLO_00_V4A_V4AMC: // V4am
        case APOLLO_00_V4B_V4BMC: // V4bm
            ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );
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
            ble_mdm_vco_cal_para_set( VCO_CALIB_PARA ); // A1
            break;
        default:
            ble_mdm_vco_cal_para_set( VCO_CALIB_PARA );
//        BX_ASSERT(0);
            break;
    }

    ble_mdm_vco_cnt_spacing_setf( 0x4 );

    ble_mdm_o_tx_clk_sel_setf( 0 );

    ble_mdm_o_agc_rssi_avg_num_setf( RSSI_AVG_NUM - 1 ); //for set rssi_avg_num 8

    modem_vcocali_value_restore(); // move here to update parameters from Frank

#ifdef HARMONIC_ENABLE
    ble_mdm_clk_rf_2sel_setf( 0x21 );

    ble_mdm_blemac_need_swc_clk_0_set( 0xaaaaaaaa );    // for test. 0xaa..a should be change in real application
    ble_mdm_blemac_need_swc_clk_1_set( 0xaa );          // for test. 0xaa..a should be change in real application

    ble_mdm_need_rate_conv_num_31_0__setf( 0xaaaaaaaa ); // for test. 0xaa..a should be change in real application
    ble_mdm_need_rate_conv_num_39_32__setf( 0xaa );     // for test. 0xaa..a should be change in real application
#else
    ble_mdm_need_rate_conv_num_31_0__setf( 0x0 );
    ble_mdm_need_rate_conv_num_39_32__setf( 0x0 );

#endif

#endif

}

#endif
/// @}


