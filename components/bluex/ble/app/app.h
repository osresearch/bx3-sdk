
#include "rwip_config.h"

#include <stdint.h>
#include <co_bt.h>
#include "arch.h"
#include "gapc.h"


#define APP_DEVICE_NAME_MAX_LEN      (16)


struct app_env_tag {
    /// Connection handle
    uint16_t conhdl;
    /// Connection Index
    uint8_t  conidx;

    /// Last initialized profile
    uint8_t next_svc;

    /// Bonding status
    bool bonded;

    /// Device Name length
    uint8_t dev_name_len;
    /// Device Name
    uint8_t dev_name[APP_DEVICE_NAME_MAX_LEN];

    /// Local device IRK( Identity Resolving Key)
    uint8_t loc_irk[KEY_LEN];

    /// Secure Connections on current link
    bool sec_con_enabled;

    /// Counter used to generate IRK
    uint8_t rand_cnt;
};

extern struct app_env_tag app_env;


void appm_init( void );
bool appm_add_svc( void );
void appm_start_advertising( void );
void appm_stop_advertising( void );
void appm_disconnect( void );
uint8_t appm_get_dev_name( uint8_t * name );


