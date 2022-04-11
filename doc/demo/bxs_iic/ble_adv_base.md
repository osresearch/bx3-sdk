# 1.概述

介绍 gapm_start_advertise_cmd 命令的使用，介绍gapm_air_operation、gapm_adv_host、gap_bdaddr的内容
以及gapm_update_advertise_data_cmd的使用



# 2.开启广播

## 2.1功能代码

app.c

```c
#include "app.h"
#include "ble.h"
#include "flash_wrapper.h"
#include "app_dis.h"
#include "plf.h"

typedef void ( *appm_add_svc_func_t )( void );
uint8_t ble_scan_rsp_data[] = {
    0x08,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, //type of this data
    'B','X', '-', 'S', 'D', 'K', '5'
};

// GAP - Advertisement data (max size = (28) bytes)
uint8_t ble_adv_data[] = {
    0x08,// length of this data
    GAP_AD_TYPE_SHORTENED_NAME,//type of this data
    'B','X', '-', 'S', 'D', 'K','5'
};

uint8_t user_scan_rsp_data[] = {
    0x07,   // length of this data
    GAP_AD_TYPE_COMPLETE_NAME, //type of this data
    'B','X', '-', 'S', 'D', 'K'
};
uint8_t user_adv_data[] = {
    0x07,   // length of this data
    GAP_AD_TYPE_SHORTENED_NAME, //type of this data
    'B','X', '-', 'S', 'D', 'K'
};

static const appm_add_svc_func_t appm_add_svc_func_list[] = {
    (appm_add_svc_func_t)app_dis_add_dis
};

/* exported variables --------------------------------------------------------*/
s32 user_service_id;

struct gapm_start_advertise_cmd adv_data;
struct gapm_update_advertise_data_cmd adv_update_data;

void app_set_dev_cfg( struct gapm_set_dev_config_cmd * cmd )
{
    cmd->operation = GAPM_SET_DEV_CONFIG;
    cmd->role      = GAP_ROLE_PERIPHERAL;
    cmd->pairing_mode = GAPM_PAIRING_LEGACY;
    cmd->sugg_max_tx_octets = BLE_MAX_OCTETS;
    cmd->sugg_max_tx_time   = BLE_MAX_TIME;
}

bool app_add_svc( void )
{
    bool more_svc = false;
    if ( app_env.next_svc != sizeof( appm_add_svc_func_list ) / sizeof( appm_add_svc_func_t ) ) {
        appm_add_svc_func_list[app_env.next_svc]();
        app_env.next_svc++;
        more_svc = true;
    }
    return more_svc;
}

void app_on_ble_init( void )
{
    app_dis_init();
}

//gapm_start_advertise_cmd 命令的使用
void app_on_ble_ready( void )
{

    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160;//unit is 625 us
    adv_data.intv_min   = 160;//unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( ble_adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( ble_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, ble_adv_data, sizeof( ble_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, ble_scan_rsp_data, sizeof( ble_scan_rsp_data ) );

    ble_advertising_start( &adv_data );

}

void app_on_ble_disconnect( void )
{
    
    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160;//unit is 625 us
    adv_data.intv_min   = 160;//unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( ble_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, ble_adv_data, sizeof( ble_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, ble_scan_rsp_data, sizeof( ble_scan_rsp_data ) );

    ble_advertising_start( &adv_data );
}

void app_init( void )
{
    struct bx_service svc;
    svc.prop_set_func = NULL;
    svc.prop_get_func = NULL;
    svc.msg_handle_func = user_msg_handle_func;
    svc.name = "user service";
    user_service_id = bx_register(&svc);
	

	bx_defer(user_service_id,USER_BLE_ADV_UPDATE,0,0,5000);
}

bx_err_t user_msg_handle_func( s32 svc, u32 msg, u32 param0, u32 param1 )
{
	s32 src_id = bx_msg_source();
	
	if(src_id == user_service_id)
	{
			switch( msg ){
			case USER_BLE_ADV_START:
				ble_advertising_start( &adv_data );
			break;
			
			case USER_BLE_ADV_STOP:
				ble_advertising_stop();
			break;
			
			case USER_BLE_ADV_UPDATE:
				update_adv_data();
				bx_logln("update_adv_data");
			break;
			
			default:
            break;
		}
	}
	
	
}

//gapm_update_advertise_data_cmd的使用
void update_adv_data(void)
{
	
    adv_update_data.operation  = GAPM_STATIC_ADDR;
	adv_update_data.adv_data_len = sizeof(user_adv_data);
	adv_update_data.scan_rsp_data_len = sizeof(user_scan_rsp_data);
	memcpy( adv_update_data.adv_data, user_adv_data, sizeof( user_adv_data ) );
	memcpy( adv_update_data.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );
	

}
```



gapm_air_operation、gapm_adv_host、gap_bdaddr的内容

```c
/// Air operation default parameters
struct gapm_air_operation
{
    /// Operation code.
    uint8_t  code;

    /**
     * Own BD address source of the device:
     * - GAPM_STATIC_ADDR: Public or Private Static Address according to device address configuration
     * - GAPM_GEN_RSLV_ADDR: Generated resolvable private random address
     * - GAPM_GEN_NON_RSLV_ADDR: Generated non-resolvable private random address
     */
    uint8_t addr_src;

    /// Dummy data use to retrieve internal operation state (should be set to 0).
    uint16_t state;
};


struct gapm_adv_host
{
    /// Advertising mode :
    /// - GAP_NON_DISCOVERABLE: Non discoverable mode
    /// - GAP_GEN_DISCOVERABLE: General discoverable mode
    /// - GAP_LIM_DISCOVERABLE: Limited discoverable mode
    /// - GAP_BROADCASTER_MODE: Broadcaster mode
    uint8_t              mode;

    /// Advertising filter policy:
    /// - ADV_ALLOW_SCAN_ANY_CON_ANY: Allow both scan and connection requests from anyone
    /// - ADV_ALLOW_SCAN_WLST_CON_ANY: Allow both scan req from White List devices only and
    ///   connection req from anyone
    /// - ADV_ALLOW_SCAN_ANY_CON_WLST: Allow both scan req from anyone and connection req
    ///   from White List devices only
    /// - ADV_ALLOW_SCAN_WLST_CON_WLST: Allow scan and connection requests from White List
    ///   devices only
    uint8_t              adv_filt_policy;

    /// Advertising data length - maximum 28 bytes, 3 bytes are reserved to set
    /// Advertising AD type flags, shall not be set in advertising data
    uint8_t              adv_data_len;
    /// Advertising data
    uint8_t              adv_data[GAP_ADV_DATA_LEN-3];
    /// Scan response data length- maximum 31 bytes
    uint8_t              scan_rsp_data_len;
    /// Scan response data
    uint8_t              scan_rsp_data[GAP_SCAN_RSP_DATA_LEN];
    /// Peer address
    struct gap_bdaddr peer_addr;
};


/// Address information about a device address
struct gap_bdaddr
{
    /// BD Address of device
    bd_addr_t addr;
    /// Address type of the device 0=public/1=private random
    uint8_t addr_type;
};

```



## 2.2 功能演示

上电后程序自动广播，五秒后更改广播内容，无需停止广播。