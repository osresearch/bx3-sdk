/*
 * app_adc_utils.c
 *
 *  Created on: 20180910
 *      Author: mingzhou
 */

#include "app_adc.h"
#include "plf.h"
#include <stdlib.h>
#include "log.h"
#include "rf_reg_settings.h"
#include "io_ctrl.h"
#include "flash_wrapper.h"
#include "app_adc_utils.h"
#include "bx_config.h"
#include "modem.h"
#include "rf_reg_typedef.h"
#include "rf_power_set.h"

uint8_t m_adc_beta_offset_904[ADC_CAL_NUM] =
{
    187,
    187,
    181,
    174,
    174,
    168,
    168,
    161,
    155,
    155,
    149,
    149,
    149,
    143,
    137,
    137,
    131,
    131,
    131,
    119,
    119,
    113,
    113,
    113,
    102,
    102,
    102,
    96,
    96,
    96,
    85,
    85,
    85,
    80,
    80,
    74,
    69,
    69,
    64,
    64,
    58,
    53,
    53,
    53,
    48,
    48,
    43,
    38,
    38,
    38,
    33,
    28,
    23,
    23,
    23,
    19,
    14,
    14,
    9,
    9,
    9,
    5,
    0,
    0
};
	
uint16_t m_adc_2_bat_k[ADC_CAL_NUM] =
{
    12886-10667,
    12837-10667,
    12802-10667,
    12752-10667,
    12713-10667,
    12679-10667,
    12651-10667,
    12557-10667,
    12500-10667,
    12500-10667,
    12500-10667,
    12500-10667,
    12392-10667,
    12336-10667,
    12312-10667,
    12299-10667,
    12240-10667,
    12192-10667,
    12164-10667,
    12120-10667,
    12086-10667,
    12049-10667,
    12019-10667,
    11972-10667,
    11935-10667,
    11903-10667,
    11866-10667,
    11823-10667,
    11800-10667,
    11760-10667,
    11716-10667,
    11688-10667,
    11656-10667,
    11626-10667,
    11584-10667,
    11553-10667,
    11517-10667,
    11486-10667,
    11445-10667,
    11418-10667,
    11375-10667,
    11345-10667,
    11319-10667,
    11280-10667,
    11250-10667,
    11221-10667,
    11187-10667,
    11149-10667,
    11121-10667,
    11089-10667,
    11056-10667,
    11028-10667,
    10997-10667,
    10969-10667,
    10947-10667,
    10908-10667,
    10870-10667,
    10843-10667,
    10812-10667,
    10780-10667,
    10753-10667,
    10713-10667,
    10699-10667,
    10667-10667,
};

uint32_t m_adc_2_bat_base[ADC_CAL_NUM] =
{
    6658000,
    6635500,
    6613600,
    6591400,
    6570600,
    6551300,
    6530700,
    6499900,
    6475000,
    6462500,
    6450000,
    6437500,
    6404700,
    6381100,
    6363700,
    6348700,
    6324300,
    6302600,
    6284700,
    6263800,
    6244000,
    6227800,
    6209200,
    6187300,
    6167400,
    6151600,
    6132300,
    6111400,
    6097100,
    6076700,
    6055700,
    6040700,
    6022000,
    6006700,
    5985700,
    5970400,
    5951000,
    5935000,
    5914700,
    5900100,
    5879300,
    5863800,
    5849400,
    5829400,
    5813800,
    5798700,
    5779400,
    5762900,
    5747800,
    5732400,
    5713200,
    5698300,
    5682600,
    5667800,
    5653300,
    5637300,
    5617000,
    5602300,
    5587000,
    5571400,
    5556600,
    5539100,
    5536900,
    5511100,
};

uint8_t m_bat[ADC_CAL_NUM] =
{
    0,
    2,
    4,
    6,
    8,
    10,
    12,
    14,
    16,
    18,
    20,
    22,
    25,
    27,
    29,
    31,
    33,
    35,
    38,
    40,
    42,
    44,
    46,
    49,
    51,
    53,
    55,
    58,
    60,
    62,
    65,
    67,
    69,
    72,
    74,
    76,
    79,
    81,
    83,
    86,
    88,
    91,
    93,
    96,
    98,
    101,
    103,
    106,
    108,
    111,
    113,
    116,
    118,
    121,
    123,
    126,
    129,
    131,
    134,
    137,
    139,
    142,
    145,
    147
};

static uint8_t adc_bonding_RO_array[32] =
{
    [4] = 51,
    [5] = 48,
    [6] = 45,
    [7] = 42,
    [8] = 39,
    [9] = 36,
    [10] = 33,
    [11] = 30,
    [12] = 27,
    [13] = 24,
    [14] = 21,
};

int32_t adc_cp_RO = 0;
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//void rf_setting_battery_monitor_adc( void ) // typical value 0x22D80(bit 7/8/10/11/13/17)
//{
//	#if(MAIN_CLOCK == 96000000)
//	{
//		RF_REG_7 = 0x00022d90;
//	}
//	#else
// 	{
//		RF_REG_7 = 0x00022d80;
//	}
//	#endif
//}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//void rf_setting_temperature_adc( void ) // typical value 0x12580(bit 7/8/10/13/16)
//{
//	#if(MAIN_CLOCK == 96000000)
//	{
//		RF_REG_7 = 0x00013d90;
//	}
//	#else
//	{
//		RF_REG_7 = 0x00013d80;
//	}
//	#endif
//}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
//void rf_setting_single_mode_adc( void ) // typical value 0x3980(bit 7/8/11/12/13)
//{
//	#if(MAIN_CLOCK == 96000000)
//	{
//		RF_REG_7 = 0x00003990;
//	}
//	#else
//	{
//		RF_REG_7 = 0x00003980;
//	}
//	#endif
//}

uint16_t AvgArray(uint16_t* numbers)
{
    uint32_t sum = 0;
    uint32_t avg = 0;
    for(uint32_t i = ADC_DEL_NUM; i <= ADC_SAMPLE_NUM-ADC_DEL_NUM-ADC_DEL_NUM; i++)
    {
        sum += numbers[i];
    }
    avg = sum/(ADC_SAMPLE_NUM-ADC_DEL_NUM-ADC_DEL_NUM);
    if(sum - avg*(ADC_SAMPLE_NUM-ADC_DEL_NUM-ADC_DEL_NUM) >= (ADC_SAMPLE_NUM-ADC_DEL_NUM-ADC_DEL_NUM)/2)
    {
        avg++;
    }
    return (uint16_t)avg;
}

static int adc_comparator(const void *a, const void *b)
{
    return *(uint16_t*)a > *(uint16_t*)b? 1: -1;
}

static uint16_t app_adc_battery_raw(app_adc_inst_t *adc_p)
{
    uint16_t result = 0;
    app_adc_inst_t adc = *adc_p;

    rf_setting_battery_monitor_adc();
    app_adc_read_without_dma(&(adc.inst) , 3 , &result);
    return result;
}

static uint16_t app_adc_tempSensor_raw(app_adc_inst_t *adc_p)
{
    uint16_t result = 0;
    app_adc_inst_t adc = *adc_p;

//    *(volatile uint32_t*)0x2020108c = 0x12580;
    rf_setting_temperature_adc();
    app_adc_read_without_dma(&(adc.inst) , 3 , &result);
    return result;
}

void app_adc_cp_sim(void)
{
    uint16_t adc_val[CP_SAMPLE_NUM];
    app_adc_inst_t adc = ADC_INSTANCE(0);
    //init
    adc.param.ldo_force_on = 1;
    adc.param.ldo_delay_us = ADC_LDO_DELAY_DEFAULT;
    adc.param.use_dma = 0;
    app_adc_init(&(adc.inst));

    for(uint8_t i = 0; i < CP_SAMPLE_NUM; i++)
    {
        adc_val[i] = app_adc_battery_raw(&adc);
    }
    app_adc_uninit(&(adc.inst));
    qsort(adc_val, CP_SAMPLE_NUM, sizeof(adc_val[0]), adc_comparator);
    adc_cp_RO = ADC_BAT_CAL_BASE_VAL - AvgArray(adc_val);
    if(adc_cp_RO > ADC_CAL_NUM-1)
    {
        adc_cp_RO = ADC_CAL_NUM-1;
    }
    if(adc_cp_RO < 0)
    {
        adc_cp_RO = 0;
    }
}

static uint16_t app_adc_gpadc_single_end_raw(uint8_t channel)
{
    uint16_t adc_val[8];
    int32_t adc_val_cal = 0;

    app_adc_inst_t adc = ADC_INSTANCE(0);
    adc.param.ldo_force_on = 1;
    adc.param.ldo_delay_us = ADC_LDO_DELAY_DEFAULT;
    adc.param.use_dma = 0;

    app_adc_init(&(adc.inst));

    rf_setting_single_mode_adc();

    for(uint8_t i = 0; i < 8; i++)
    {
        if(app_adc_read_without_dma(&(adc.inst) , channel, &adc_val[i]))
        {
            i--;
            continue; // redo the sample
        }
        adc_val_cal += adc_val[i];
    }
    //uninit
    app_adc_uninit(&(adc.inst));

    return (uint16_t)(adc_val_cal/8);
}

static uint8_t app_adc_gpadc_bonding_RO_bit(uint32_t channel)
{
    return app_adc_gpadc_single_end_raw(channel) < 675? 1: 0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void app_adc_util_init( void )
{
#ifdef ADC_RO_READ_FORCE_ON
    periph_err_t err;
    uint8_t manufacturer_id, device_id;
    flash_read_manufacturer_device_id( &manufacturer_id, &device_id );
//    bx_logln( "falsh id:%x", manufacturer_id );
    if( MANUFACTURER_ZBIT == manufacturer_id ) { /*ZBIT Serial Flash*/
        err = ZBIT_flash_read_security_reg( 0, 0, sizeof( uint8_t ), ( uint8_t * )&adc_cp_RO );
        if( err != PERIPH_NO_ERROR ) {
            BX_ASSERT( 0 );
        }
    } else if(    (  MANUFACTURER_WINBOND == manufacturer_id ) /*Winbond Serial Flash*/
                  || (  MANUFACTURER_PUYA == manufacturer_id )/*PUYA Serial Flash*/
             ) {
        if( flash_read_security_reg( 1, 0, 1, ( uint8_t * )&adc_cp_RO ) != PERIPH_NO_ERROR ) {
            BX_ASSERT( 0 );
        }
    } else if( MANUFACTURER_XMC == manufacturer_id ) {
        err = XMC_flash_enter_OTP_mode();
        if( err != PERIPH_NO_ERROR ) {
            bx_logln( "XMC_flash_enter_OTP_mode fail£º%u",err );
        }
        BX_ASSERT(err == PERIPH_NO_ERROR);
        err = flash_multi_read( 0xFFF000, sizeof( uint8_t ), ( uint8_t * )&adc_cp_RO );
        if( err != PERIPH_NO_ERROR ) {
            bx_logln( "flash_multi_read fail£º%u",err );
        }
        BX_ASSERT(err == PERIPH_NO_ERROR);
        err = XMC_flash_exit_OTP_mode();
        if( err != PERIPH_NO_ERROR ) {
            bx_logln( "XMC_flash_exit_OTP_mode fail£º%u",err );
            while(1);
        }
        BX_ASSERT(err == PERIPH_NO_ERROR);
    } else {
        LOG( LOG_LVL_INFO, "UNKONWN flash\n" );
        BX_ASSERT( 0 );
    }
    if( 0xff == ( uint8_t )adc_cp_RO ) {
        uint8_t temp_bonding = 0;

        for( uint8_t i = 1; i < 6; i++ ) {
            temp_bonding |= app_adc_gpadc_bonding_RO_bit( i ) << ( i - 1 );
        }
        adc_cp_RO = adc_bonding_RO_array[temp_bonding];
    }
#else
    adc_cp_RO = 33;
#endif

	extern void refresh_rf_param_with_ro( uint32_t ro );
	refresh_rf_param_with_ro( adc_cp_RO );
	
//	LOG_I("RO=%d", adc_cp_RO);
}

static uint32_t app_adc_battery_volt(uint32_t bat_val)
{
    uint32_t k = m_adc_2_bat_k[adc_cp_RO] + 10667;    
    uint32_t base = m_adc_2_bat_base[adc_cp_RO];
    uint32_t adc_minus_320_mult_1000 = bat_val - 250;
    uint32_t adc_minus_320 = adc_minus_320_mult_1000;//adc_minus_320_mult_1000 >> 10;

    // LOG(LOG_LVL_INFO,"bat_val=%d, recovered adc=%d, RO=0x%x\n", bat_val, adc_minus_320, adc_cp_RO);
    return base - k*adc_minus_320;
}

uint32_t app_adc_battery(void)
{
    uint16_t adc_val[BAT_SAMPLE_NUM];
    uint16_t adc_val_16;

    app_adc_inst_t adc = ADC_INSTANCE(0);
    //init
    adc.param.ldo_force_on = 1;
    adc.param.ldo_delay_us = ADC_LDO_DELAY_DEFAULT;
    adc.param.use_dma = 0;

    app_adc_init(&(adc.inst));

    for(uint8_t i = 0; i < BAT_SAMPLE_NUM; i++)
    {
        adc_val[i] = app_adc_battery_raw(&adc);
        if(adc_val[i] == (uint16_t)-1)
        {
            i--; // redo the sample
            continue;
        }
    }
    app_adc_uninit(&(adc.inst));
    qsort(adc_val, BAT_SAMPLE_NUM, sizeof(adc_val[0]), adc_comparator);
    adc_val_16 = AvgArray(adc_val);
    return app_adc_battery_volt(adc_val_16);
}

int16_t app_adc_tempSensor(void)
{
    uint16_t adc_val[TMP_SAMPLE_NUM];
    int32_t adc_val_cal;
    uint16_t adc_val_16;
    int16_t temp_val;

    app_adc_inst_t adc = ADC_INSTANCE(0);
    
    // init
    adc.param.ldo_force_on = 1;
    adc.param.ldo_delay_us = ADC_LDO_DELAY_DEFAULT;
    adc.param.use_dma = 0;

    app_adc_init(&(adc.inst));

    for(uint8_t i = 0; i < TMP_SAMPLE_NUM; i++)
    {
        adc_val[i] = app_adc_tempSensor_raw(&adc);
        if(adc_val[i] == (uint16_t)-1)
        {
            i--;
            continue; // redo the sample
        }
    }
    
    app_adc_uninit(&(adc.inst));
    qsort(adc_val, TMP_SAMPLE_NUM, sizeof(adc_val[0]), adc_comparator);
    adc_val_16 = AvgArray(adc_val);
    adc_val_cal = (int32_t)adc_val_16*(m_bat[adc_cp_RO] + M_BAT_BASE);
    temp_val = (adc_val_cal - 448230)/720;
    //LOG(LOG_LVL_INFO,"temp_val = %d\n", temp_val);
    return temp_val;
}


