#ifndef _SCHMITT_H_
#define _SCHMITT_H_
#include <stdint.h>


//temperature
typedef enum
{
    MODE_BELOWN25 = 0,
    MODE_BELOW0 = 1,
    MODE_NORMAL = 2,
    MODE_OVER50 = 3,
    MODE_MAX    = 4,
}temp_mode_t;


void try_to_update_rf_param_with_temp(void);
void handle_read_temp(void);
void refresh_rf_regs_in_lp(void);






#endif
