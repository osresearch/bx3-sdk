# 1.概述

​		本文档介绍启动广播、连接后修改连接参数的可连接广播例程，打开SDK3/examples/demo路径下的ble_adv_cnt工程



# 2.启动广播

## 2.1 功能代码

在app.c中

```c
void app_on_ble_ready( void )
{
    struct gapm_start_advertise_cmd adv_data;
    adv_data.op.addr_src    = GAPM_STATIC_ADDR;
    adv_data.channel_map    = ADV_ALL_CHNLS_EN;
    adv_data.intv_max   = 160;//unit is 625 us
    adv_data.intv_min   = 160;//unit is 625 us
    adv_data.op.code    = GAPM_ADV_UNDIRECT;
    adv_data.info.host.mode = GAP_GEN_DISCOVERABLE;
    adv_data.info.host.adv_data_len = sizeof( user_adv_data );
    adv_data.info.host.scan_rsp_data_len  = sizeof( user_scan_rsp_data );
    adv_data.info.host.adv_filt_policy = ADV_ALLOW_SCAN_ANY_CON_ANY;
    memcpy( adv_data.info.host.adv_data, user_adv_data, sizeof( user_adv_data ) );
    memcpy( adv_data.info.host.scan_rsp_data, user_scan_rsp_data, sizeof( user_scan_rsp_data ) );

    ble_advertising_start( &adv_data );

}
```

配置广播参数，开启广播



# 3.连接后修改连接参数

## 3.1功能代码

在ble.c中

```c
struct gapc_conn_param up_con_param;



void ble_update_con_param( struct gapc_conn_param * conn_param )
{
    // Prepare the GAPC_PARAM_UPDATE_CMD message
    struct gapc_param_update_cmd * cmd = KE_MSG_ALLOC( 	       GAPC_PARAM_UPDATE_CMD,TASK_GAPC, TASK_APP,gapc_param_update_cmd );

    cmd->operation  = GAPC_UPDATE_PARAMS;
    cmd->intv_min   = conn_param->intv_min;
    cmd->intv_max   = conn_param->intv_max;
    cmd->latency    = conn_param->latency;
    cmd->time_out   = conn_param->time_out;
    
    // not used by a slave device
    cmd->ce_len_min = 0xFFFF;
    cmd->ce_len_max = 0xFFFF;
    
    // Send the message
    ke_msg_send( cmd );

}
```

更新连接参数，连接间隔，延时时间，超时时间。调用该函数传入要更新的参数，即可更新连接参数。

```c
static int gapc_connection_req_ind_handler( ke_msg_id_t const msgid,
        struct gapc_connection_req_ind const * param,
        ke_task_id_t const dest_id,
        ke_task_id_t const src_id )
{
    app_env.conidx = KE_IDX_GET( src_id );

    if ( app_env.conidx != GAP_INVALID_CONIDX ) {
        app_env.conhdl = param->conhdl;


        struct gapc_connection_cfm * cfm = KE_MSG_ALLOC( GAPC_CONNECTION_CFM,
                                           KE_BUILD_ID( TASK_GAPC, app_env.conidx ), TASK_APP,
                                           gapc_connection_cfm );
    
        cfm->auth=GAP_AUTH_REQ_NO_MITM_NO_BOND;
        ke_msg_send( cfm );
        up_con_param.intv_min 	= 160;		//设置连接参数
        up_con_param.intv_max   = 160;
        up_con_param.latency    = 10;
        up_con_param.time_out   = 500;
        bx_dwork( ( void ( * )( void * ) )ble_update_con_param, &up_con_param, 2000, 1 );	//连接后将连接参数更新
    			
    } else {
        app_on_ble_connect_fail();
    }
    
    return ( KE_MSG_CONSUMED );

}
```



## 3.2 功能演示

将固件烧入设备，在手机上通过nrf软件可发现设备已经开启广播，连接设备后发现设备连接参数已经改变