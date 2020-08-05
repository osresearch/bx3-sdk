#ifndef _SCHMITT_H_
#define _SCHMITT_H_
#include <stdint.h>

//#define ENABLE_RF_ADJ_LOG


void init_rf_temp_adjust(void);	//called in  osapp_task function
void handle_read_temp(void);	//called in adc_sys_adjust_temp function.
void refresh_rf_regs_in_lp(void);
void try_to_update_rf_param_with_temp(void);




#endif
