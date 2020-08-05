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

/* includes ------------------------------------------------------------------*/
#include "bx_drv_pwm.h"
#include "bx_drv_io_mux.h"
#include "flash_wrapper.h"
#include <stdlib.h>

/* config --------------------------------------------------------------------*/
#define SG_END_VAL_HIGH                                 1023000
#define SG_END_VAL_LOW                                  0
#define SG_END_HIGH                                     2850
#define SG_END_LOW                                      0
#define SG_END_VOLT_STEP                                25
#define SG_END_INDEX_HIGH                               ( ( SG_END_HIGH - SG_END_LOW ) / SG_END_VOLT_STEP )
#define SG_END_SUBSTRATOR                               6000
#define SG_END_VAL_STEP                                 9

#define ADC_CAL_NUM                                     64

#define GPADC_BASE_VAL                                  904
#define ADC_SAMPLE_NUM                                  4
#define ADC_DEL_NUM                                     1
#define BAT_SAMPLE_NUM                                  ADC_SAMPLE_NUM
#define TMP_SAMPLE_NUM                                  ADC_SAMPLE_NUM

#define M_BAT_BASE                                      940


/* private define ------------------------------------------------------------*/
#define CHECK_HANDLE(hdl)                                   \
do{                                                         \
    if( (hdl) != BX_ADC ) {                                 \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_CHANNEL(ch)                                   \
do{                                                         \
    if( (ch) > 6 ){                                         \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/
static uint8_t g_beta_offset_904[64] = {
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


static uint16_t m_adc_2_bat_k[ADC_CAL_NUM] = {
    12886 - 10667,
    12837 - 10667,
    12802 - 10667,
    12752 - 10667,
    12713 - 10667,
    12679 - 10667,
    12651 - 10667,
    12557 - 10667,
    12500 - 10667,
    12500 - 10667,
    12500 - 10667,
    12500 - 10667,
    12392 - 10667,
    12336 - 10667,
    12312 - 10667,
    12299 - 10667,
    12240 - 10667,
    12192 - 10667,
    12164 - 10667,
    12120 - 10667,
    12086 - 10667,
    12049 - 10667,
    12019 - 10667,
    11972 - 10667,
    11935 - 10667,
    11903 - 10667,
    11866 - 10667,
    11823 - 10667,
    11800 - 10667,
    11760 - 10667,
    11716 - 10667,
    11688 - 10667,
    11656 - 10667,
    11626 - 10667,
    11584 - 10667,
    11553 - 10667,
    11517 - 10667,
    11486 - 10667,
    11445 - 10667,
    11418 - 10667,
    11375 - 10667,
    11345 - 10667,
    11319 - 10667,
    11280 - 10667,
    11250 - 10667,
    11221 - 10667,
    11187 - 10667,
    11149 - 10667,
    11121 - 10667,
    11089 - 10667,
    11056 - 10667,
    11028 - 10667,
    10997 - 10667,
    10969 - 10667,
    10947 - 10667,
    10908 - 10667,
    10870 - 10667,
    10843 - 10667,
    10812 - 10667,
    10780 - 10667,
    10753 - 10667,
    10713 - 10667,
    10699 - 10667,
    10667 - 10667,
};

static uint32_t m_adc_2_bat_base[ADC_CAL_NUM] = {
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

static uint8_t m_bat[ADC_CAL_NUM] = {
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


static uint8_t adc_bonding_RO_array[32] = {
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

uint32_t cp_ro = 0;

/* exported variables --------------------------------------------------------*/



/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void clk_init( void )
{
    BX_MODIFY_REG( BX_AWO->MISC, AWO_MISC_CS_HBUS0, ( uint32_t ) 1 );
    BX_SET_BIT( BX_AWO->CLKG, AWO_CLKG_CLR_AHB_32M_DIV );
    BX_SET_BIT( BX_AWO->CLKG, AWO_CLKG_CLR_AHB_PLL_DIV );

    BX_MODIFY_REG( BX_AWO->MISC, AWO_MISC_CS_HBUS0, ( uint32_t ) 4 );
    BX_SET_BIT( BX_AWO->CLKG, AWO_CLKG_CLR_AHB_32M_DIV );
    BX_SET_BIT( BX_AWO->CLKG, AWO_CLKG_CLR_AHB_PLL_DIV );

    BX_MODIFY_REG( BX_AWO->MISC, AWO_MISC_CS_HBUS0, ( uint32_t ) 1 );
    BX_SET_BIT( BX_AWO->CLKG, AWO_CLKG_CLR_AHB_32M_DIV );
    BX_SET_BIT( BX_AWO->CLKG, AWO_CLKG_CLR_AHB_PLL_DIV );

    BX_MODIFY_REG( BX_AWO->MISC, AWO_MISC_AHB_CDP, ( uint32_t ) ( 2 << AWO_MISC_AHB_CDP_POS ) );
    //BX_MODIFY_REG(BX_AWO->MISC,AWO_MISC_CS_HBUS1,(uint32_t) (0<<AWO_MISC_CS_HBUS1_POS));

    BX_SET_BIT( BX_AWO->CLKG, AWO_CLKG_SET_AHB_32M_DIV );

    BX_MODIFY_REG( BX_AWO->MISC, AWO_MISC_CS_HBUS0, ( uint32_t ) ( 2 << AWO_MISC_CS_HBUS0_POS ) );

    //BX_MODIFY_REG(BX_AWO->MISC,AWO_MISC_AHB_CDP,(uint32_t) (2<<AWO_MISC_AHB_CDP_POS));
    //BX_SET_BIT(BX_AWO->CLKG1,AWO_CLKG1_APB_CDP_UP);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void config_init( void )
{
    //init adc reg_rg
    BX_ADC_CFG->ADC_COMP_Current = 0;//ADC Comparator Current Option,000: 1uA  ; 001: 1.3uA  ; 010: 1.3uA ;  011: 1.6uA; 100: 1.3uA  ; 101: 1.6uA  ; 110:1.6uA ;  111:1.9uA
    BX_ADC_CFG->ADC_CLK_DIV = 0;//00 :  DIV1               01 :  DIV2            10 :  DIV4              11 :  DIV8
    BX_ADC_CFG->ADC_REFP = 0 ; //ADC REFN Voltage Option, 00 : 2.8V               01 :2.6V             10 : 2.4V             11 :2.2V
    BX_ADC_CFG->ADC_REF_BUF_Current = 3 ; //ADC Buffer Current Option, 00 : 0.5uA               01 : 1.5uA             10 : 3.5uA             11 : 7.5uA
    BX_ADC_CFG->Reserved0 = 0 ;
    BX_ADC_CFG->LV_VCM = 0 ; //ADC VREF Low Voltage Mode , 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Force_ADC_CH_VDD_to_INT = 1; //Force VDD_3V of ADC Channel Tie to VDD_3V_INT, 0 : Tie to VDD_3V_ADC  ;  1 : Tie to VDD_3V_INT
    BX_ADC_CFG->ADC_SINGLE_DR = 1 ; //Bypass Internal ADC Reference Buffer, 0 : 9.6b  ;  1 : 9b
    BX_ADC_CFG->Sinlge_ended_Mode = 1 ; //ADC Input Single-ended Mode, 0 : Differential Mode  ;  1 : Single-ended Mode
    BX_ADC_CFG->External_Input_Buffer = 0;//Double VCM Buffer Current Bias, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Temperature_Sensor_Type = 0;//Differential Types of Temperature Sensor Option, 0 : NTAT   ;  1 : Channel 3 Input Buffer Enable
    BX_ADC_CFG->Temperature_Sensor = 0;//Temperature Sensor Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Battery_Monitor = 0;//VBAT Voltage Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Reserved2 = 0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint32_t adc_val_to_volt( uint32_t adc_val )
{
    uint32_t temp, quotient, reminder;
    uint32_t adc_value_volt = 0;
    if( adc_val <= 0 ) {
        adc_val = 0;
    }
    if( adc_val > SG_END_VAL_HIGH ) {
        adc_value_volt = SG_END_LOW;
    } else if( adc_val <= SG_END_SUBSTRATOR ) { // not SG_END_VAL_LOW
        adc_value_volt =  SG_END_HIGH;
    } else {

        temp = ( adc_val - SG_END_SUBSTRATOR ) / SG_END_VAL_STEP;
        quotient = temp / 1000;
        reminder = temp % 1000;

        if( reminder > 400 ) { // round up and round down
            quotient++;
        }

        adc_value_volt =  ( SG_END_INDEX_HIGH - 1 - quotient ) * SG_END_VOLT_STEP;
    }
    return adc_value_volt;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_setting_battery_init( void )
{
    //init adc reg_rg
    BX_ADC_CFG->ADC_COMP_Current = 0;//ADC Comparator Current Option,000: 1uA  ; 001: 1.3uA  ; 010: 1.3uA ;  011: 1.6uA; 100: 1.3uA  ; 101: 1.6uA  ; 110:1.6uA ;  111:1.9uA
    BX_ADC_CFG->ADC_CLK_DIV = 0;//00 :  DIV1               01 :  DIV2            10 :  DIV4              11 :  DIV8
    BX_ADC_CFG->ADC_REFP = 0 ; //ADC REFN Voltage Option, 00 : 2.8V               01 :2.6V             10 : 2.4V             11 :2.2V
    BX_ADC_CFG->ADC_REF_BUF_Current = 3 ; //ADC Buffer Current Option, 00 : 0.5uA               01 : 1.5uA             10 : 3.5uA             11 : 7.5uA
    BX_ADC_CFG->Reserved0 = 0 ;
    BX_ADC_CFG->LV_VCM = 1 ; //ADC VREF Low Voltage Mode , 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Force_ADC_CH_VDD_to_INT = 1; //Force VDD_3V of ADC Channel Tie to VDD_3V_INT, 0 : Tie to VDD_3V_ADC  ;  1 : Tie to VDD_3V_INT
    BX_ADC_CFG->Sinlge_ended_Mode = 1 ; //ADC Input Single-ended Mode, 0 : Differential Mode  ;  1 : Single-ended Mode
    BX_ADC_CFG->External_Input_Buffer = 0;//Double VCM Buffer Current Bias, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Temperature_Sensor_Type = 0;//Differential Types of Temperature Sensor Option, 0 : NTAT   ;  1 : Channel 3 Input Buffer Enable
    BX_ADC_CFG->Temperature_Sensor = 0;//Temperature Sensor Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Battery_Monitor = 1;//VBAT Voltage Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Reserved2 = 0;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static int adc_comparator( const void * a, const void * b )
{
    return *( uint16_t * )a > *( uint16_t * )b ? 1 : -1;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint32_t app_adc_2_battery_volt( uint32_t adc_val )
{
    uint32_t k = m_adc_2_bat_k[cp_ro] + 10667;
    uint32_t base = m_adc_2_bat_base[cp_ro];
    uint32_t adc_minus_320_mult_1000 = adc_val - 250;
    uint32_t adc_minus_320 = adc_minus_320_mult_1000;//adc_minus_320_mult_1000 >> 10;

    return base - k * adc_minus_320;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint16_t AvgArray( uint16_t * numbers )
{
    uint32_t sum = 0;
    uint32_t avg = 0;
    for( uint32_t i = ADC_DEL_NUM; i <= ADC_SAMPLE_NUM - ADC_DEL_NUM - ADC_DEL_NUM; i++ ) {
        sum += numbers[i];
    }
    avg = sum / ( ADC_SAMPLE_NUM - ADC_DEL_NUM - ADC_DEL_NUM );
    if( sum - avg * ( ADC_SAMPLE_NUM - ADC_DEL_NUM - ADC_DEL_NUM ) >= ( ADC_SAMPLE_NUM - ADC_DEL_NUM - ADC_DEL_NUM ) / 2 ) {
        avg++;
    }
    return ( uint16_t )avg;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static void rf_setting_tempSensor_init( void )
{
    //init adc reg_rg
    BX_ADC_CFG->ADC_COMP_Current = 0;//ADC Comparator Current Option,000: 1uA  ; 001: 1.3uA  ; 010: 1.3uA ;  011: 1.6uA; 100: 1.3uA  ; 101: 1.6uA  ; 110:1.6uA ;  111:1.9uA
    BX_ADC_CFG->ADC_CLK_DIV = 0;//00 :  DIV1               01 :  DIV2            10 :  DIV4              11 :  DIV8
    BX_ADC_CFG->ADC_REFP = 0 ; //ADC REFN Voltage Option, 00 : 2.8V               01 :2.6V             10 : 2.4V             11 :2.2V
    BX_ADC_CFG->ADC_REF_BUF_Current = 3 ; //ADC Buffer Current Option, 00 : 0.5uA               01 : 1.5uA             10 : 3.5uA             11 : 7.5uA
    BX_ADC_CFG->Reserved0 = 0 ;
    BX_ADC_CFG->LV_VCM = 1 ; //ADC VREF Low Voltage Mode , 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Force_ADC_CH_VDD_to_INT = 1; //Force VDD_3V of ADC Channel Tie to VDD_3V_INT, 0 : Tie to VDD_3V_ADC  ;  1 : Tie to VDD_3V_INT
    BX_ADC_CFG->Sinlge_ended_Mode = 1 ; //ADC Input Single-ended Mode, 0 : Differential Mode  ;  1 : Single-ended Mode
    BX_ADC_CFG->External_Input_Buffer = 0;//Double VCM Buffer Current Bias, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Temperature_Sensor_Type = 0;//Differential Types of Temperature Sensor Option, 0 : NTAT   ;  1 : Channel 3 Input Buffer Enable
    BX_ADC_CFG->Temperature_Sensor = 1;//Temperature Sensor Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Battery_Monitor = 0;//VBAT Voltage Readout, 0 : Disable  ;  1 : Enable
    BX_ADC_CFG->Reserved2 = 0;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

bx_err_t bx_drv_adc_get_ro( void )
{
    uint16_t adc_val[8];
    int32_t adc_val_cal = 0;

    if( flash_read_security_reg( 1, 0, 1, ( uint8_t * )&cp_ro ) != 0 ) {
        return BX_ERR_INVAL;
    }

    if( 0xff == ( uint8_t )cp_ro ) {
        uint8_t temp_bonding = 0;
        BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
        BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
        BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
        BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.

        config_init();

        for( uint8_t i = 1; i < 6; i++ ) {
            adc_val_cal = 0;
            for( uint8_t j = 0; j < 8; j++ ) {
                BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t ) ( i << ADC_SSM_CH_NUM_POS ) );
                BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START );

                while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS );

                adc_val[j] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS );
                adc_val_cal += adc_val[j];
            }
            temp_bonding |= ( ( adc_val_cal / 8 ) < 675 ? 1 : 0 ) << ( i - 1 );
        }
        cp_ro = adc_bonding_RO_array[temp_bonding];

    }

    return BX_OK;

}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :需要注意实际芯片中是否有对应的IO口
 * @param   :channel[in]   取值范围0~5，对应P30~P35的模拟IO口
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_adc_get_value( void * hdl, u8 channel, int32_t * value )
{
    CHECK_HANDLE( hdl );
    CHECK_CHANNEL( channel );
    CHECK_POINTER( value );

    uint16_t adc_val[4];
    uint16_t cal_param = 0;

    int32_t adc_val_sum = 0;

    cal_param = g_beta_offset_904[cp_ro] + GPADC_BASE_VAL;

    BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.

    for( uint8_t i = 0; i < 4; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t ) ( channel << ADC_SSM_CH_NUM_POS ) );
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START );

        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS );

        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS );
        adc_val_sum += cal_param * adc_val[i] + 766000 - cal_param * 766;
    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off

    * value = ( ( adc_val_sum - 255000 * 4 ) ) / 2; // adc/2 = adc*2/4;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_adc_get_volt( void * hdl, u8 channel, u32 * value_mv )
{
    CHECK_HANDLE( hdl );
    CHECK_CHANNEL( channel );
    CHECK_POINTER( value_mv );

    int32_t adc_value;
    bx_err_t err = bx_drv_adc_get_value( hdl, channel, &adc_value );
    if( err != BX_OK ) {
        return err;
    }
    * value_mv = adc_val_to_volt( adc_value );
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_adc_get_battery( void * hdl, u32 * bat_value )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( bat_value );

    uint16_t adc_val[BAT_SAMPLE_NUM];
    uint16_t adc_val_16;
    uint32_t adc_battery_value = 0;


    BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.

    rf_setting_battery_init();

    for( uint8_t i = 0; i < BAT_SAMPLE_NUM; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t )( 3 << ADC_SSM_CH_NUM_POS ) ); //set battery channel
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START ); //start adc
        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS ); //wait for adc done
        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS ); //read adc data

    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off
    qsort( adc_val, BAT_SAMPLE_NUM, sizeof( adc_val[0] ), adc_comparator );

    adc_val_16 = AvgArray( adc_val );

    adc_battery_value = app_adc_2_battery_volt( adc_val_16 );

    *bat_value = adc_battery_value;

    return BX_OK;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_adc_get_chip_temperature( void * hdl, u32 * temp_value )
{
    CHECK_HANDLE( hdl );
    CHECK_POINTER( temp_value );

    uint16_t adc_val[TMP_SAMPLE_NUM];
    uint16_t adc_val_16;
    uint32_t adc_temp_value = 0;
    uint32_t adc_val_cal = 0;

    BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.
    rf_setting_tempSensor_init();

    for( uint8_t i = 0; i < TMP_SAMPLE_NUM; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t )( 3 << ADC_SSM_CH_NUM_POS ) ); //set tempSensor channel
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START ); //start adc
        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS ); //wait for adc done
        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS ); //read adc data

    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off
    qsort( adc_val, BAT_SAMPLE_NUM, sizeof( adc_val[0] ), adc_comparator );

    adc_val_16 = AvgArray( adc_val );

    adc_val_cal = ( int32_t )adc_val_16 * ( m_bat[cp_ro] + M_BAT_BASE );
    //adc_temp_value = (adc_val_cal - 448230)/720;
    adc_temp_value = ( adc_val_cal - 448230 ) / 72;

    *temp_value = adc_temp_value;

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_adc_open( void * hdl )
{
    CHECK_HANDLE( hdl );

    clk_init();
    config_init();

    bx_drv_adc_get_ro();

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bx_drv_adc_close( void * hdl )
{
    CHECK_HANDLE( hdl );

    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



