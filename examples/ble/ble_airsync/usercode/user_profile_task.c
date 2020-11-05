/**
 ****************************************************************************************
 *
 * @file hfp_task.c
 *
 * @brief Glucose Profile Sensor Task Implementation.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup GLPSTASK
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwip_config.h"


#include "gap.h"
#include "gattc_task.h"
#include "user_profile.h"
#include "user_profile_task.h"
#include "prf_utils.h"

#include "ke_mem.h"
#include "co_utils.h"

#include "bx_shell.h"
#include "bx_kernel.h"
#include "user_service_ble.h"
#include "bx_drv_ble.h"

#include "bx_service_uart.h"

#include "flash_wrapper.h"
#include "nvds_typedef.h"
#include "nvds_in_ram.h"

#include "pb_example.h"
#include "comsource.h"
#include "epb_MmBp.h"
/*
 *  GLUCOSE PROFILE ATTRIBUTES
 ****************************************************************************************
 */

#define WECHAT_STORE_MAX                      5

static uint8_t auth_buf[20];

uint8_t wechatStoreStartIndex = 0;
uint8_t  wechatStoreIndex = 0;

//static void wechatStoreIndications(attHandleValueInd_t* pInd)
static void wechatStoreIndications( uint8_t * buf, uint8_t length )
{

    //保存数据
    memcpy( auth_buf, buf, length );
    //存储指针 ++
    wechatStoreIndex = wechatStoreIndex + 1;

    if( wechatStoreIndex > WECHAT_STORE_MAX ) {
        wechatStoreIndex = 0;
    }
    if( wechatStoreIndex == wechatStoreStartIndex ) {
        // 丢掉未发送的那一帧
        wechatStoreStartIndex = wechatStoreStartIndex + 1;
        if( wechatStoreStartIndex > WECHAT_STORE_MAX ) {
            wechatStoreStartIndex = 0;
        }
    }
}

void wechatMeasIndicate( uint8_t * dataBuf, uint16_t Len )
{
    // att value notification structure
    uint16_t i = 0;
    static uint8_t store_buf[20];
    for( i = 0; i < Len; i++ ) {
        store_buf[i % 20] = dataBuf[i];
        if( ( i + 1 ) % 20 == 0 ) {
            wechatStoreIndications( store_buf, 20 );
            ble_send_data_indicate( store_buf, 20, 36 );
        } else if( ( i + 1 ) == Len ) { //  保存最后一帧
            wechatStoreIndications( store_buf, ( Len % 20 ) );
            ble_send_data_indicate( store_buf, ( Len % 20 ), 36 );
        }
    }

}

/*********************************************************************
 * @fn      GetDataSize
 *
 * @brief   获取接收到的数据长度
 *
 * @return  数据长度
 ***********************************************************/
uint16_t GetDataSize( void )
{
    return UnPackProtobufLen;
}


void wechatIOT_BLE_Device_Auth( void )
{
    mpbledemo2_info  m_info = {CMD_NULL, {NULL, 0}};
    m_info.cmd = CMD_AUTH;
    Pack_Data( &m_info, PackProtobufData, &PackProtobufLen );

    wechatMeasIndicate( PackProtobufData, PackProtobufLen );
}

void wechatIOT_BLE_Device_Init( void )
{
    mpbledemo2_info  m_info = {CMD_NULL, {NULL, 0}};
    m_info.cmd = CMD_INIT;
    Pack_Data( &m_info, PackProtobufData, &PackProtobufLen );
    wechatMeasIndicate( PackProtobufData, PackProtobufLen );
}


/*********************************************************************
 * @fn      SendDataToWechat
 *
 * @brief   发送数据给微信
 *
 * @param   buf - 要发送的数据源
 * @param   len - 要发送数据源长度
 *
 * @return  0    成功
 *          -1   发送数据长度过长
 *          -2   蓝牙未连接
 */
int8_t SendDataToWechat( char const * buf, uint16_t const buf_len )
{
    mpbledemo2_info  m_info = {CMD_NULL, {NULL, 0}};
    m_info.cmd = CMD_SENDDAT;
    m_info.send_msg.str = buf;
    m_info.send_msg.len = buf_len;

    Pack_Data( &m_info, SendData, &SendDataLen );

    wechatMeasIndicate( SendData, SendDataLen );
    return 0;
}

/*********************************************************************
* @fn      GetWechatData
*
* @brief   获得微信的数据
*
* @param   pBuf - 存放数据的地方
* @param   len -  接收到的数据长度
*
* @return  读到的字节数
*/
uint16_t  GetWechatData( uint8_t * pBuf, uint8_t * len )
{
    *len = UnPackProtobufLen;
    memcpy( pBuf, UnPackProtobufData, UnPackProtobufLen );
    return 0;
}


void mpbledemo2_reset( void )
{
    mpbledemo2Sta.indication_state = false;
    mpbledemo2Sta.auth_send = false;
    mpbledemo2Sta.auth_state = false;
    mpbledemo2Sta.init_send = false;
    mpbledemo2Sta.init_state = false;
    mpbledemo2Sta.send_data_seq = 0;
    mpbledemo2Sta.push_data_seq = 0;
    mpbledemo2Sta.seq = 0;

    wechatStoreStartIndex = 0;
    wechatStoreIndex = 0;
}

uint8_t mpbledemo2_init( void )
{
    mpbledemo2_reset();
    return 0;
}

void mpbledemo2_on_write( void )
{
    if ( 1 ) {
        mpbledemo2Sta.indication_state = true;
    } else {
        mpbledemo2Sta.indication_state = false;
    }

}

void mpbledemo2_on_disconnect( void )
{
    mpbledemo2_reset();
}

/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATT_CODE_ATT_WR_CMD_IND message.
 * The handler compares the new values with current ones and notifies them if they changed.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_write_req_ind_handler( ke_msg_id_t const msgid,
                                        struct gattc_write_req_ind * param,
                                        ke_task_id_t const dest_id,
                                        ke_task_id_t const src_id )
{
//    bxsh_logln("user gattc_write_req_ind_handler");
    uint8_t state  = ke_state_get( dest_id );
    if( state == USER_PROFILE_IDLE ) {
        static uint8_t  i = 0;
        static uint16_t count = 0;
        uint8_t status = GAP_ERR_NO_ERROR;
        struct gattc_write_cfm * cfm;

        //Send write response
        cfm = KE_MSG_ALLOC( GATTC_WRITE_CFM, src_id, dest_id, gattc_write_cfm );
        cfm->handle = param->handle;
        cfm->status = status;
        ke_msg_send( cfm );

        if( param->handle == 37 && param->value[0] == 2 && param->value[1] == 0 ) { //发送auth请求
            mpbledemo2_on_write();

            wechatIOT_BLE_Device_Auth();
            mpbledemo2Sta.auth_send = true;
        }
        if( param->handle == 34 ) {

            if( ( param->value[0] == 0xfe ) && ( param->value[1] == 0x01 ) ) { //magic
                memcpy( UnPackProtobufData, param->value, 20 );
                i = 1;
                count =  param->value[2] ;
                count = ( count << 8 ) | param->value[3] ;
            } else {
                if( count > ( i * 20 ) ) {
                    memcpy( ( UnPackProtobufData + ( i * 20 ) ), param->value, 20 );
                    i++;
                }
            }

            if( count <= ( i * 20 ) ) {  //接收了一帧数据

                UnPackProtobufLen = count;
                UnPackEmCmdID = UnPack_Data( UnPackProtobufData, &UnPackProtobufLen );
                if ( UnPackEmCmdID == ECI_resp_auth ) {

                    wechatIOT_BLE_Device_Init();
                    mpbledemo2Sta.init_send = true;
                } else if ( UnPackEmCmdID == ECI_resp_init ) {
                    bxsh_logln( "解码 init respect\r\n" );
                } else if ( UnPackEmCmdID == ECI_resp_sendData ) {
                    bxsh_logln( "解码 send respect\r\n" );
                } else if ( UnPackEmCmdID == ECI_push_recvData ) {
                    static uint8_t push_buf[20];
                    char send_data[20] = {0x02, 0x03, 0x04};
                    uint8_t push_length;
                    bxsh_logln( "解码 ECI_push_recvData\r\n" );
                    GetWechatData( push_buf, &push_length );
                    memcpy( send_data, push_buf, push_length );
                    SendDataToWechat( send_data, 3 );

                } else if ( UnPackEmCmdID == ECI_push_switchView ) {
                    bxsh_logln( "解码 ECI_push_switchView\r\n" );
                } else if ( UnPackEmCmdID == ECI_push_switchBackgroud ) {
                    bxsh_logln( "解码 ECI_push_switchBackgroud\r\n" );
                }

            }


        }

    }
    return ( KE_MSG_CONSUMED );
}


/**
 ****************************************************************************************
 * @brief Handles reception of the read request from peer device
 *
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_read_req_ind_handler( ke_msg_id_t const msgid,
                                       struct gattc_read_req_ind const * param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id )
{
    bxsh_logln( "user gattc_read_req_ind_handler" );
    ke_state_t state = ke_state_get( dest_id );

    if( state == USER_PROFILE_IDLE ) {
        static uint8_t mac_buf[6];
        static uint8_t bd_ad_length = 6;
        nvds_get( NVDS_TAG_BD_ADDRESS, &bd_ad_length, mac_buf );
        struct gattc_read_cfm * cfm = KE_MSG_ALLOC_DYN( GATTC_READ_CFM, src_id, dest_id, gattc_read_cfm, 6 );
        cfm->handle = param->handle;
        cfm->status = ATT_ERR_NO_ERROR;
        cfm->length = 6;
        cfm->value[0] = mac_buf[5];
        cfm->value[1] = mac_buf[4];
        cfm->value[2] = mac_buf[3];
        cfm->value[3] = mac_buf[2];
        cfm->value[4] = mac_buf[1];
        cfm->value[5] = mac_buf[0];
        ke_msg_send( cfm );
    }

    return ( KE_MSG_CONSUMED );
}


/**
 ****************************************************************************************
 * @brief Handles @ref GATTC_CMP_EVT for GATTC_NOTIFY and GATT_INDICATE message meaning
 * that Measurement notification/indication has been correctly sent to peer device
 *
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_cmp_evt_handler( ke_msg_id_t const msgid, struct gattc_cmp_evt const * param,
                                  ke_task_id_t const dest_id, ke_task_id_t const src_id )
{
    bxsh_logln( "gattc_cmp_evt_handler" );


    return ( KE_MSG_CONSUMED );
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

/// Default State handlers definition
const struct ke_msg_handler user_default_handler[] = {
    {GATTC_WRITE_REQ_IND,                 ( ke_msg_func_t ) gattc_write_req_ind_handler},
    {GATTC_READ_REQ_IND,                  ( ke_msg_func_t ) gattc_read_req_ind_handler},
    {GATTC_CMP_EVT,                       ( ke_msg_func_t ) gattc_cmp_evt_handler},
};

/// Specifies the message handlers that are common to all states.
const struct ke_state_handler userp_default_handler = KE_STATE_HANDLER( user_default_handler );


/// @} GLPSTASK
