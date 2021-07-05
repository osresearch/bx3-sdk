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
#include "bx_config.h"
#include "rf_power_set.h"
#include "bxd_pwm.h"
#include "bxd_io_mux.h"
#include "flash_wrapper.h"
#include "app_adc_utils.h"
#include <stdlib.h>

/* config --------------------------------------------------------------------*/


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



/* exported variables --------------------------------------------------------*/
extern int32_t adc_cp_RO;


/*============================= private function =============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static uint32_t adc_val_to_volt( int32_t adc_val )
{
    uint32_t temp;
    uint32_t adc_value_volt = 0;

    adc_val = ( adc_val  > 0 ? ( uint32_t )adc_val : 0 );

    if( adc_val <= 0 ) {
        adc_val = 0;
    }

    if( adc_val > SG_END_VAL_HIGH << 1 ) {
        adc_value_volt = SG_END_LOW;
    } else if( adc_val <= SG_END_SUBSTRATOR << 1 ) { // not SG_END_VAL_LOW
        adc_value_volt =  SG_END_HIGH;
    } else {

        temp = ( SG_END_VAL_STEP * 2 * 1000 ) * ( SG_END_INDEX_HIGH - 1 ) - adc_val + 12000;
        adc_value_volt = temp / ( ( SG_END_VAL_STEP * 2 * 1000 ) / SG_END_VOLT_STEP );	
    }
    return adc_value_volt;
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
    uint32_t k = m_adc_2_bat_k[adc_cp_RO] + 10667;
    uint32_t base = m_adc_2_bat_base[adc_cp_RO];
    uint32_t adc_minus_320_mult_1000 = adc_val - 250;
    uint32_t adc_minus_320 = adc_minus_320_mult_1000;//adc_minus_320_mult_1000 >> 10;

    return base - k * adc_minus_320;
}
/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :需要注意实际芯片中是否有对应的IO口
 * @param   :channel[in]   取值范围0~5，对应P30~P35的模拟IO口
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_adc_get_value( void * hdl, u8 channel, int32_t * value )
{
    CHECK_HANDLE( hdl );
    CHECK_CHANNEL( channel );
    CHECK_POINTER( value );

    uint16_t adc_val[ADC_SAMPLE_NUM];
    uint16_t cal_param = 0;

    int32_t adc_val_cal = 0;

    cal_param = m_adc_beta_offset_904[adc_cp_RO] + GPADC_BASE_VAL;

    BX_SET_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //high will force the ADC LDO to be power up
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_LDO, ( uint32_t ) ( 8 << ADC_DLY_LDO_POS ) ); //LDO on/off delay of ADC
    BX_MODIFY_REG( BX_ADC->DLY, ADC_DLY_CHANNEL, ( uint32_t ) ( 8 << ADC_DLY_CHANNEL_POS ) ); //LDO on/off delay of ADC
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_DMA_EN ); //dma disable. High means the hardware handshake signals between the DAMC and ADC will be active. Then system can move the ADC data from the ADC FIFO to the system SRAM through DMAC.
    rf_setting_single_mode_adc();

    for( uint8_t i = 0; i < ADC_SAMPLE_NUM; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t ) ( channel << ADC_SSM_CH_NUM_POS ) );
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START );

        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS );

        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS );
    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off

    qsort( adc_val, ADC_SAMPLE_NUM, sizeof( adc_val[0] ), adc_comparator );
    adc_val_cal += cal_param * adc_val[1] + 511000 - cal_param * 766;
    adc_val_cal += cal_param * adc_val[2] + 511000 - cal_param * 766;
    adc_val_cal += cal_param * adc_val[3] + 511000 - cal_param * 766;
    adc_val_cal += cal_param * adc_val[4] + 511000 - cal_param * 766;

    * value = adc_val_cal;
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_adc_get_volt( void * hdl, u8 channel, u32 * value_mv )
{
    CHECK_HANDLE( hdl );
    CHECK_CHANNEL( channel );
    CHECK_POINTER( value_mv  );

    int32_t adc_value;
    bx_err_t err = bxd_adc_get_value( hdl, channel, &adc_value );
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
bx_err_t bxd_adc_get_battery( void * hdl, u32 * bat_value )
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

    rf_setting_battery_monitor_adc();

    for( uint8_t i = 0; i < BAT_SAMPLE_NUM; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t )( 3 << ADC_SSM_CH_NUM_POS ) ); //set battery channel
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START ); //start adc
        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS ); //wait for adc done
        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS ); //read adc data

    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off

	rf_setting_single_mode_adc();
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
bx_err_t bxd_adc_get_chip_temperature( void * hdl, u32 * temp_value )
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
    rf_setting_temperature_adc();

    for( uint8_t i = 0; i < TMP_SAMPLE_NUM; i++ ) {
        BX_MODIFY_REG( BX_ADC->SSM, ADC_SSM_CH_NUM, ( uint32_t )( 3 << ADC_SSM_CH_NUM_POS ) ); //set tempSensor channel
        BX_SET_BIT( BX_ADC->SSM, ADC_SSM_START ); //start adc
        while( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_START ) >> ADC_SSM_START_POS ); //wait for adc done
        adc_val[i] = ( BX_READ_BIT( BX_ADC->SSM, ADC_SSM_DATA ) >> ADC_SSM_DATA_POS ); //read adc data

    }
    BX_CLR_BIT( BX_ADC->CTRL, ADC_CTRL_LDO_FORCE_ON ); //low will force the ADC LDO to be power off

	rf_setting_single_mode_adc();
    qsort( adc_val, BAT_SAMPLE_NUM, sizeof( adc_val[0] ), adc_comparator );

    adc_val_16 = AvgArray( adc_val );

    adc_val_cal = ( int32_t )adc_val_16 * ( m_bat[adc_cp_RO] + M_BAT_BASE );
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
bx_err_t bxd_adc_open( void * hdl )
{
    CHECK_HANDLE( hdl );

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_adc_close( void * hdl )
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



