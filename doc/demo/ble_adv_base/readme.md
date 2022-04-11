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
    0x08,   // 数据长度
    GAP_AD_TYPE_COMPLETE_NAME, //数据类型
    'B','X', '-', 'S', 'D', 'K', '5'
};

// GAP - 广播数据 (max size = (28) bytes)
uint8_t ble_adv_data[] = {
    0x08,// 数据长度
    GAP_AD_TYPE_SHORTENED_NAME,//数据类型
    'B','X', '-', 'S', 'D', 'K','5'
};

uint8_t user_scan_rsp_data[] = {
    0x07,   // 数据长度
    GAP_AD_TYPE_COMPLETE_NAME, //数据类型
    'B','X', '-', 'S', 'D', 'K'
};
uint8_t user_adv_data[] = {
    0x07,   // 数据长度
    GAP_AD_TYPE_SHORTENED_NAME, //数据类型
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
    cmd->operation = GAPM_SET_DEV_CONFIG; 		//GAPM请求的操作
    cmd->role      = GAP_ROLE_PERIPHERAL; 		//设备角色:主动连接、被动连接、扫描器、广播或所有角色。
    cmd->pairing_mode = GAPM_PAIRING_LEGACY;	//配对模式授权(参见enum gapm_pairing_mode)
    cmd->sugg_max_tx_octets = BLE_MAX_OCTETS;	//控制器要使用的最大传输有效载荷八位元组的建议值
    cmd->sugg_max_tx_time   = BLE_MAX_TIME;		//控制器所使用的最大数据包传输时间的建议值
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

    adv_data.op.addr_src    = GAPM_STATIC_ADDR; //GAPM_STATIC_ADDR:公网或私有静态地址，根据设备地址配置而定
    adv_data.channel_map    = ADV_ALL_CHNLS_EN; //ADV_ALL_CHNLS_EN：启用通道37、38和39的广告通道映射的字节值
    adv_data.intv_max   = 160;//unit is 625 us 最大广播间隔
    adv_data.intv_min   = 160;//unit is 625 us 最小广播间隔
    adv_data.op.code    = GAPM_ADV_UNDIRECT;//GAPM_ADV_UNDIRECT:可连接非定向广播
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;//GAP_GEN_DISCOVERABLE:通用发现模式
    adv_data.info.host.adv_data_len = sizeof( ble_adv_data );//广播数据长度-最大28字节，预留3字节设置
    adv_data.info.host.scan_rsp_data_len  = sizeof( ble_scan_rsp_data );//扫描响应数据长度-最大31字节
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;//广播过滤政策-ADV_ALLOW_SCAN_ANY_CON_ANY:																	  允许任何人的扫描和连接请求
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
    //注册一个服务
    struct bx_service svc;
    svc.prop_set_func = NULL;
    svc.prop_get_func = NULL;
    svc.msg_handle_func = user_msg_handle_func;
    svc.name = "user service";
    user_service_id = bx_register(&svc);
	
	//上电延迟5秒将广播数据更新
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
    //GAPM_UPDATE_ADVERTISE_DATA:动态更新广播数据
    adv_update_data.operation  = GAPM_STATIC_ADDR;
	adv_update_data.adv_data_len = sizeof(user_adv_data);
	adv_update_data.scan_rsp_data_len = sizeof(user_scan_rsp_data);
	memcpy( adv_update_data.adv_data, user_adv_data, sizeof( user_adv_data ) );
	memcpy( adv_update_data.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );
	

}
```



gapm_air_operation、gapm_adv_host、gap_bdaddr的内容

```c
/// 空中运行默认参数
struct gapm_air_operation
{
    /// 操作码
    uint8_t  code;

    /**
     * 设备自有BD地址来源:
     * - GAPM_STATIC_ADDR:公网或私有静态地址，根据设备地址配置而定
     * - GAPM_GEN_RSLV_ADDR: 生成可解析的私有随机地址
     * - GAPM_GEN_NON_RSLV_ADDR: 生成不可解析的私有随机地址
     */
    uint8_t addr_src;

    /// 虚拟数据用于检索内部操作状态(应设为0)。
    uint16_t state;
};


struct gapm_adv_host
{
    /// 广播模式 :
    /// - GAP_NON_DISCOVERABLE: 非可发现的模式
    /// - GAP_GEN_DISCOVERABLE: 一般可发现的模式
    /// - GAP_LIM_DISCOVERABLE: 限制的可发现的模式
    /// - GAP_BROADCASTER_MODE: 广播模式
    uint8_t              mode;

    /// 广播过滤政策:
    /// - ADV_ALLOW_SCAN_ANY_CON_ANY:允许来自任何人的扫描和连接请求
    /// - ADV_ALLOW_SCAN_WLST_CON_ANY: 只允许来自白名单的扫描请求和任何人的连接请求
    /// - ADV_ALLOW_SCAN_ANY_CON_WLST: 只允许来自白名单的连接请求和任何人的扫描请求
    /// - ADV_ALLOW_SCAN_WLST_CON_WLST: 只允许白名单设备的扫描和连接请求
    uint8_t              adv_filt_policy;

    /// 广播数据长度-最大28字节，预留3字节设置
    /// 广播的AD类型标志，不得在广播数据中设置
    uint8_t              adv_data_len;
    /// 广播数据
    uint8_t              adv_data[GAP_ADV_DATA_LEN-3];
    /// 扫描响应数据长度-最大31字节
    uint8_t              scan_rsp_data_len;
    /// 扫描响应数据
    uint8_t              scan_rsp_data[GAP_SCAN_RSP_DATA_LEN];
    /// 同行的地址
    struct gap_bdaddr peer_addr;
};


/// 设备地址信息
struct gap_bdaddr
{
    ///设备的BD地址
    bd_addr_t addr;
    /// 设备地址类型0=public/1=private random
    uint8_t addr_type;
};

```



## 2.2 功能演示

上电后程序自动广播，五秒后更改广播内容，无需停止广播。