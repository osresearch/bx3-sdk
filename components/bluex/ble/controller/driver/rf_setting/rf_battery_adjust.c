#include "rf_battery_adjust.h"
#include "rtc.h"
#include "app_adc_utils.h"
#include "rf_reg_settings.h"
#include "log.h"

#if (defined BX_BATTERY_MONITOR) && (BX_BATTERY_MONITOR == 1)  
#define BAT_VOLT_ARRAY_SIZE 1
#define portMAX_32_BIT_NUMBER       (0xffffffff)

static uint16_t bat_cur_volt[BAT_VOLT_ARRAY_SIZE] = {0};
void app_set_cur_bat(void)
{
    #if BAT_VOLT_ARRAY_SIZE > 1
    memcpy((void*)bat_cur_volt[0], (void*)bat_cur_volt[1], (BAT_VOLT_ARRAY_SIZE-1)*sizeof(bat_cur_volt[0]));
    bat_cur_volt[BAT_VOLT_ARRAY_SIZE-1] = (uint16_t)(app_adc_battery()/1000);
    if(bat_cur_volt[0] == 0) // first sample
    {
        for(uint32_t i = 0; i < BAT_VOLT_ARRAY_SIZE-1; i++)
        {
            bat_cur_volt[i] = bat_cur_volt[BAT_VOLT_ARRAY_SIZE-1];
        }
    }
    #else
    bat_cur_volt[0] = (uint16_t)(app_adc_battery()/1000);
    #endif
}
uint16_t app_get_cur_bat(void)
{
    uint32_t sum_bat = 0;
    for(uint32_t i = 0; i < BAT_VOLT_ARRAY_SIZE; i++)
    {
        sum_bat += bat_cur_volt[i];
    }
    return (uint16_t)(sum_bat/BAT_VOLT_ARRAY_SIZE);
}
void adc_sys_adjust_bat(void)
{
    app_set_cur_bat();
    rf_reg_adjust_bat(app_get_cur_bat());
}

void try_to_update_rf_param_with_bat(void)
{
    static uint32_t tick_count_last = 0;
    uint32_t tick_count_current = RTC_CURRENTCNT_GET();
    uint32_t tick_temp;
    if(tick_count_current > tick_count_last)
    {
        tick_temp = tick_count_current - tick_count_last;
    }
    else if(tick_count_current < tick_count_last)
    {
        tick_temp = (portMAX_32_BIT_NUMBER - tick_count_last) + tick_count_current;
    }
    if( tick_temp >= 0x20000 )	//0x8000 = 1s
    {
        tick_count_last = tick_count_current;
        adc_sys_adjust_bat();
    }
}

#endif



