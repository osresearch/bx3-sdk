#ifndef _SCHMITT_H_
#define _SCHMITT_H_
#include <stdint.h>

//temperature			
typedef enum
{
	MODE_BELOW0 = 0,
	MODE_NORMAL = 1,
	MODE_OVER50 = 2,
	MODE_MAX    = 3,
}temp_mode_t;


void init_rf_temp_adjust(void);	//called in  osapp_task function
void init_rf_temp_adjust_in_power_exchange(void);
void refresh_rf_regs_in_lp(void);
void handle_read_temp(void);	//called in adc_sys_adjust_temp function.
void try_to_update_rf_param_with_temp(void);






#endif
