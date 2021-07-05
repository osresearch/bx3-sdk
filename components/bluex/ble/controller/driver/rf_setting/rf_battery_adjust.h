#ifndef _RF_BATTERY_ADJUST_H_
#define _RF_BATTERY_ADJUST_H_
#include <stdint.h>
#include "bx_sys_config.h"

#if (defined BX_BATTERY_MONITOR) && (BX_BATTERY_MONITOR == 1)  
void app_set_cur_bat(void);
uint16_t app_get_cur_bat(void);
void adc_sys_adjust_bat(void);
void try_to_update_rf_param_with_bat(void);
#endif

#endif

