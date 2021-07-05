#include "app_adc.h"


#define SG_END_VAL_HIGH                                 1023000
#define SG_END_VAL_LOW                                  0
#define SG_END_HIGH                                     2850
#define SG_END_LOW                                      0
#define SG_END_VOLT_STEP                                25
#define SG_END_INDEX_HIGH                               ( ( SG_END_HIGH - SG_END_LOW ) / SG_END_VOLT_STEP )
#define SG_END_SUBSTRATOR                               6000
#define SG_END_VAL_STEP                                 9

#define ADC_LDO_DELAY_DEFAULT      						8
#define ADC_CAL_NUM                                     64
#define ADC_BAT_CAL_BASE_VAL 							464
#define M_BAT_BASE                                      940

#define GPADC_BASE_VAL                                  904
#define ADC_SAMPLE_NUM                                  6
#define ADC_DEL_NUM                                     1
#define CP_SAMPLE_NUM 									ADC_SAMPLE_NUM
#define BAT_SAMPLE_NUM                                  ADC_SAMPLE_NUM
#define TMP_SAMPLE_NUM                                  ADC_SAMPLE_NUM

#define ADC_RO_READ_FORCE_ON

extern uint8_t m_adc_beta_offset_904[ADC_CAL_NUM];
extern uint16_t m_adc_2_bat_k[ADC_CAL_NUM];
extern uint32_t m_adc_2_bat_base[ADC_CAL_NUM];
extern uint8_t m_bat[ADC_CAL_NUM];

void rf_setting_battery_monitor_adc(void);
void rf_setting_temperature_adc(void);
void rf_setting_single_mode_adc(void);
uint16_t AvgArray(uint16_t* numbers);

/**
 *******************************************************************************************************************************************
 * @brief          Calculate RO value under battery=3.9V.
 *******************************************************************************************************************************************
 */
void app_adc_cp_sim(void);
/**
 *******************************************************************************************************************************************
 * @brief          Calculate RO value under any circumstance.
 *******************************************************************************************************************************************
 */
void app_adc_util_init(void);
/**
 *******************************************************************************************************************************************
 * @brief          Get current battery voltage.
 * @return         Current battery voltage value(in mini volt).
 *******************************************************************************************************************************************
 */
uint32_t app_adc_battery(void);
/**
 *******************************************************************************************************************************************
 * @brief          Get current temperature sensor.
 * @return         Current temperature sensor value.
 *******************************************************************************************************************************************
 */
int16_t app_adc_tempSensor(void);




