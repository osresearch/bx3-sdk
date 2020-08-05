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

#if HW_BX_VERSION == 00

//#if (defined(CFG_FREERTOS_SUPPORT)&&(CFG_FREERTOS_SUPPORT==1))
//#include "FreeRTOS.h"
//#include "timers.h"
//#endif


#define ADC_LDO_DELAY_DEFAULT      8
#define CP_SAMPLE_NUM 16
#define BAT_SAMPLE_NUM 16
#define CP_DEL_NUM 1
#define ADC_CAL_NUM 64
#define ADC_BAT_CAL_BASE_VAL 464
#define ADC_BATTERY_CHN 3
#define M_BAT_BASE 940

static uint8_t m_bat[ADC_CAL_NUM] =
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

#define ADC_GPADC_BASE_VAL_B 904
static uint8_t m_adc_beta_offset_904[ADC_CAL_NUM] =
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

#define ADC_GPADC_DIF_BASE_VAL 920
static uint8_t m_adc_dif_offset_920[ADC_CAL_NUM] =
{
    0,
    2,
    4,
    7,
    9,
    11,
    14,
    15,
    18,
    21,
    23,
    25,
    27,
    30,
    31,
    34,
    36,
    39,
    41,
    43,
    45,
    48,
    50,
    53,
    55,
    58,
    59,
    61,
    64,
    66,
    68,
    71,
    73,
    75,
    78,
    80,
    82,
    85,
    87,
    89,
    91,
    94,
    96,
    98,
    100,
    102,
    106,
    108,
    110,
    112,
    114,
    116,
    120,
    122,
    124,
    126,
    128,
    130,
    133,
    135,
    137,
    139,
    142,
    144,
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
static uint16_t AvgArray(uint16_t* numbers, uint32_t start, uint32_t last)
{
    uint32_t sum = 0;
    for(uint32_t i = start; i <= last; i++)
    {
        sum += numbers[i];
    }
    sum /= last-start+1;
    return (uint16_t)sum;
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
    adc_cp_RO = ADC_BAT_CAL_BASE_VAL - AvgArray(adc_val, CP_DEL_NUM, CP_SAMPLE_NUM-CP_DEL_NUM-1);
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

void app_adc_util_init(void)
{
	#ifdef ADC_RO_READ_FORCE_ON
    if(flash_read_security_reg(1, 0, 1, (uint8_t*)&adc_cp_RO) != PERIPH_NO_ERROR)
    {
        BX_ASSERT(0);
    }
    if(0xff == (uint8_t)adc_cp_RO)
    {
        uint8_t temp_bonding = 0;
    
        for(uint8_t i = 1; i < 6; i++)
        {
            temp_bonding |= app_adc_gpadc_bonding_RO_bit(i) << (i-1);
        }
        adc_cp_RO = adc_bonding_RO_array[temp_bonding];
    }
    #else
    adc_cp_RO = 33;
    #endif
	

    #if RF_PARAM == 2 || RF_PARAM == 3 
    extern void refresh_rf_param_with_ro(uint32_t ro);
    refresh_rf_param_with_ro(adc_cp_RO);
    #endif
    LOG(LOG_LVL_INFO,"RO=0x%x\n", adc_cp_RO);
    LOG(LOG_LVL_INFO,"RO=0x%x\n", adc_cp_RO);
}

uint32_t app_adc_battery(void)
{
    uint16_t adc_val[BAT_SAMPLE_NUM];
    uint32_t adc_val_cal;
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
    }
    app_adc_uninit(&(adc.inst));
    qsort(adc_val, BAT_SAMPLE_NUM, sizeof(adc_val[0]), adc_comparator);
    adc_val_16 = AvgArray(adc_val, 1, BAT_SAMPLE_NUM-1-1);
    adc_val_cal = adc_val_16*(m_bat[adc_cp_RO] + M_BAT_BASE);
    return adc_val_cal;
}

int16_t app_adc_tempSensor(void)
{
    uint16_t adc_val[BAT_SAMPLE_NUM];
    uint32_t adc_val_cal;
    uint16_t adc_val_16;
    int16_t temp_val;
    app_adc_inst_t adc = ADC_INSTANCE(0);
    //init
    adc.param.ldo_force_on = 1;
    adc.param.ldo_delay_us = ADC_LDO_DELAY_DEFAULT;
    adc.param.use_dma = 0;
    app_adc_init(&(adc.inst));

    for(uint8_t i = 0; i < BAT_SAMPLE_NUM; i++)
    {
        adc_val[i] = app_adc_tempSensor_raw(&adc);
    }
    app_adc_uninit(&(adc.inst));
    qsort(adc_val, BAT_SAMPLE_NUM, sizeof(adc_val[0]), adc_comparator);
    adc_val_16 = AvgArray(adc_val, 1, BAT_SAMPLE_NUM-1-1);
    adc_val_cal = adc_val_16*(m_bat[adc_cp_RO] + M_BAT_BASE);
    temp_val = (int32_t)(adc_val_cal - 448230)/720;
    
    LOG(LOG_LVL_INFO,"RO=%d\n", adc_cp_RO);
    LOG(LOG_LVL_INFO,"adc temp raw value=%d\n", adc_val_16);
    return temp_val;
}

uint32_t app_adc_gpadc_single_end(uint8_t channel)
{
    uint16_t adc_val[4];
    uint16_t adc_beta;
    int32_t adc_val_cal = 0, adc_val_return = 0;

    app_adc_inst_t adc = ADC_INSTANCE(0);
    //init
    adc.param.ldo_force_on = 1;
    adc.param.ldo_delay_us = ADC_LDO_DELAY_DEFAULT;
    adc.param.use_dma = 0;
    app_adc_init(&(adc.inst));

    rf_setting_single_mode_adc();

    adc_beta = m_adc_beta_offset_904[adc_cp_RO] + ADC_GPADC_BASE_VAL_B;

    for(uint8_t i = 0; i < 4; i++)
    {
        app_adc_read_without_dma(&(adc.inst) , channel , &adc_val[i]);
        adc_val_cal += adc_beta*adc_val[i] + 766000 - adc_beta*766;
    }
    //uninit
    app_adc_uninit(&(adc.inst));

    adc_val_return = ((adc_val_cal-255000*4))/2;  // adc/2 = adc*2/4

    return (adc_val_return > 0? (uint32_t)adc_val_return: 0);
}

uint32_t app_adc_gpadc_differential(uint8_t channel)
{
    uint16_t adc_val;
    uint16_t adc_beta;
    uint32_t adc_val_cal = 0;

    app_adc_inst_t adc = ADC_INSTANCE(0);
    //init
    adc.param.ldo_force_on = 1;
    adc.param.ldo_delay_us = ADC_LDO_DELAY_DEFAULT;
    adc.param.use_dma = 0;
    app_adc_init(&(adc.inst));

    rf_setting_differential_mode_adc();

    adc_beta = m_adc_dif_offset_920[adc_cp_RO] + ADC_GPADC_DIF_BASE_VAL;

    for(uint8_t i = 0; i < 16; i++)
    {
        app_adc_read_without_dma(&(adc.inst) , channel , &adc_val);
        adc_val_cal += adc_beta*adc_val;
    }
    //uninit
    app_adc_uninit(&(adc.inst));

    return (adc_val_cal)/4;
}


#elif HW_BX_VERSION == 01

#endif

