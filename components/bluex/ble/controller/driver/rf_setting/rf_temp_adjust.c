#include "rf_temp_adjust.h"
#include "plf.h"
#include "log.h"
#include "rf_reg_typedef.h"
#include "sys_sleep.h"
#include "reg_ble_mdm.h"
#include "ll.h"
#include "rtc.h"
#include "rf_reg_settings.h"
#include "app_adc_utils.h"
#include "modem.h"
#include "rf_power_set.h"

/*
 *  schmitt TYPEDEF
 ****************************************************************************************    
 */
#define SMT_TAB_SIZE    3
//goal 0 threshold
#define GOAL0_L   -23
#define GOAL0_H   -18

//goal 1 threshold
#define GOAL1_L   -5
#define GOAL1_H   5

//goal 2 threshold
#define GOAL2_L   45
#define GOAL2_H   55
/*
 *  RF TYPEDEF
 ****************************************************************************************            
 */

//#define TEMP_TEST     MODE_BELOW0//MODE_BELOWN25/MODE_BELOW0/MODE_NORMAL/MODE_OVER50
typedef int16_t smt_t;    //schmitt value
extern int32_t adc_cp_RO;
typedef enum
{
    SCHMITT_IN_LOW,
    SCHMITT_IN_HIGH,
}smt_stat_t;

typedef struct
{
    smt_t       goal_l;
    smt_t       goal_h;
    smt_stat_t  current;
}schmitt_t;

#define DISPLAY_PERIOD  1000
#define portMAX_32_BIT_NUMBER       (0xffffffff)

/*
 * VARIABLE
 ****************************************************************************************
 */

schmitt_t smt_tab[SMT_TAB_SIZE]=
{
    {GOAL0_L , GOAL0_H , SCHMITT_IN_LOW},
    {GOAL1_L , GOAL1_H , SCHMITT_IN_LOW},
    {GOAL2_L , GOAL2_H , SCHMITT_IN_HIGH},
};
int16_t current_temp=25;
#ifdef TEMP_TEST
temp_mode_t temp_mode = TEMP_TEST;
static temp_mode_t mode_last = MODE_MAX;
#else
temp_mode_t temp_mode = MODE_NORMAL;
static temp_mode_t mode_last = MODE_MAX;
#endif

/*
 * Schmitt tools
 ****************************************************************************************
 */
static uint8_t smt_get_range(smt_t val)
{
    smt_t current_goal;
    uint8_t result = 0;
    uint8_t i;
    //calc every channel output
    for(i=0;i<SMT_TAB_SIZE;i++)
    {
        current_goal = (smt_tab[i].current == SCHMITT_IN_LOW) ? smt_tab[i].goal_l : smt_tab[i].goal_h;
        if(val > current_goal)
        {
            smt_tab[i].current = SCHMITT_IN_LOW;
            result++;
        }
        else
        {
            smt_tab[i].current = SCHMITT_IN_HIGH;
        }
    }
    return result;
}

void try_to_update_rf_param_with_temp(void)			
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
    if( tick_temp >= 0x20000 ) //0x8000 = 1s
    {
        tick_count_last = tick_count_current;
        handle_read_temp();
    }
}

void handle_read_temp(void)
{
    current_temp = app_adc_tempSensor();
    #ifdef TEMP_TEST
        temp_mode = TEMP_TEST;
    #else
        temp_mode = (temp_mode_t)smt_get_range(current_temp);
    #endif
    if( temp_mode != mode_last )
    {
//      LOG_RAW("temp_mode change = %d\r\n", temp_mode);
        mode_last = temp_mode;
        refresh_rf_regs_in_lp();
        //modem_vcocali_start();
    }
}

void refresh_rf_regs_in_lp(void)
{
    rf_power_setting();
}


