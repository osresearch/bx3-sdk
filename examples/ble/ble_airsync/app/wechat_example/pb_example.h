#ifndef __PB_EXAMPLE_H__
#define __PB_EXAMPLE_H__
//---------------------------------------------------------------------------
//-                             Write By Adam                               -
//---------------------------------------------------------------------------
#include <stdbool.h>
#include "epb.h"

#ifdef __cplusplus
extern "C" {
#endif
  
//---------------------------------------------------------------------------
//-                             Define                                      -
//---------------------------------------------------------------------------
#define CMD_NULL 0
#define CMD_AUTH 1
#define CMD_INIT 2
#define CMD_SENDDAT 3
  
  
//  DEVICE_TYPE 和 DEVICE_ID 微信硬件平台申请
//#define DEVICE_TYPE    "gh_7c7e34f42502"
//#define DEVICE_ID      "gh_7c7e34f42502_97018adbf0b5d53c"

#define DEVICE_TYPE    "WeChatDev"
#define DEVICE_ID      "WeChatBluetoothDevice"


#define PROTO_VERSION   0x010004
#define AUTH_PROTO      1

#define MAC_ADDRESS_LENGTH   6
  

#define EAM_md5AndNoEnrypt    1     
//#define EAM_md5AndAesEnrypt   1
//#define EAM_macNoEncrypt      2

#if defined EAM_md5AndNoEnrypt || EAM_md5AndAesEnrypt
     // 另外有一个MD5(deviceType+deviceId)，如果设备算MD5 很麻烦的话，建议先
     // 算好，直接烧进设备里面。该MD5 类似于用户名。请参考 《微信蓝牙外设协议1.0.4》 14页
     // http://tool.chinaz.com/tools/md5.aspx    在线MD5 加密网站  32位（小）

//   #define    MD5_TYPE_ID   {0xd2, 0xce, 0x5a, 0xdd, 0xc9, 0x0d, 0x2c, 0x19, 0x9b, 0x82, 0xc7, 0xb8, 0x72, 0x24, 0x9e, 0xe8}
     #define    MD5_TYPE_ID   {0x37,0x60,0x8c,0x00,0x79,0x22,0xba,0x35,0x80,0x21,0x53,0x22,0x91,0x6d,0x35,0x45}
     // 设备需要烧一个Key（128 位）到硬件上，微信服务器也要记录下这个Key。    
   #define    DEVICE_KEY    {0xaa, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x55}
#endif 
 

#ifdef EAM_macNoEncrypt
	#define AUTH_METHOD   EAM_macNoEncrypt
	#define MD5_TYPE_AND_ID_LENGTH   0
	#define CIPHER_TEXT_LENGTH   0
#endif

#ifdef EAM_md5AndAesEnrypt
	#define AUTH_METHOD   EAM_md5AndAesEnrypt
	#define MD5_TYPE_AND_ID_LENGTH   16
	#define CIPHER_TEXT_LENGTH   16
#endif
#ifdef EAM_md5AndNoEnrypt
	#define AUTH_METHOD   EAM_md5AndNoEnrypt
	#define MD5_TYPE_AND_ID_LENGTH   16
	#define CIPHER_TEXT_LENGTH   0
#endif

#define CHALLENAGE_LENGTH   4

#define MPBLEDEMO2_MAGICCODE_H   0xfe
#define MPBLEDEMO2_MAGICCODE_L   0xcf
#define MPBLEDEMO2_VERSION       0x01

#define PACKLEN                 100     //送包数据的缓存区长度
#define UNPACKLEN               100     //解包数据的缓存区长度
#define SEND_DATA_MAX           100     //发送数据的最大长度

typedef enum
{
	errorCodeUnpackAuthResp = 0x9990,
	errorCodeUnpackInitResp = 0x9991,
	errorCodeUnpackSendDataResp = 0x9992,
	errorCodeUnpackCtlCmdResp = 0x9993,
	errorCodeUnpackRecvDataPush = 0x9994,
	errorCodeUnpackSwitchViewPush = 0x9995,
	errorCodeUnpackSwitchBackgroundPush = 0x9996,
	errorCodeUnpackErrorDecode = 0x9997,
}mpbledemo2UnpackErrorCode;

typedef enum
{
	errorCodeProduce = 0x9980,
}mpbledemo2PackErrorCode;

typedef enum
{
	sendTextReq = 0x01,
	sendTextResp = 0x1001,
        LED1_OFF = 0x0100,
	LED1_ON = 0x0101,
	LED2_OFF = 0x0200,
	LED2_ON = 0x0201,
        LED3_OFF = 0x0300,
	LED3_ON = 0x0301,
}BleDemo2CmdID;

typedef struct
{
	uint8_t m_magicCode[2];
	uint16_t m_version;
	uint16_t m_totalLength;
	uint16_t m_cmdid;
	uint16_t m_seq;
	uint16_t m_errorCode;
}BlueDemoHead;

typedef struct 
{
	int cmd;
	CString send_msg;
} mpbledemo2_info;

typedef struct 
{
	bool wechats_switch_state; //
	bool indication_state;
	bool auth_state;
	bool init_state;
	bool auth_send;
	bool init_send;
	unsigned short send_data_seq;
	unsigned short push_data_seq;
	unsigned short seq; 
}mpbledemo2_state;

//---------------------------------------------------------------------------
//-                             Extern Variables                            -
//---------------------------------------------------------------------------
//-----送包资料-----
extern uint8_t  PackProtobufData[PACKLEN] ;
extern uint16_t PackProtobufLen ;
//-----解包资料-----
extern uint8_t  UnPackProtobufData[UNPACKLEN] ;
extern uint16_t UnPackProtobufLen ;
extern uint16_t UnPackEmCmdID ;
//-----送数据报使用-----SendData
extern uint8_t  SendData[SEND_DATA_MAX] ;
extern uint16_t SendDataLen ;
//-----包头长度
extern uint16_t bleDemoHeadLen ;
extern uint8_t  fix_head_len ;
//---------------------------------------------------------------------------
//-                             Extern product status Variables                            -
//---------------------------------------------------------------------------
//-----设备状态标志
extern mpbledemo2_state mpbledemo2Sta;
//---------------------------------------------------------------------------
//-                             Extern Function                             -
//---------------------------------------------------------------------------
/*
*********************************************************************************************************
*	@function name: Pack_Data
*	@description  : 打包要发送的数据
*	@param[in] : args.cmd  打包成哪种数据包的命令 ; args.send_msg 发送数据包时的数据
*	@param[in] [out]  : r_data  打包后数据的地址指针
*	@param[in] [out]  : r_len   打包后数据的长度指针
*	@return       : 
*********************************************************************************************************
*/
extern  uint8_t Pack_Data(mpbledemo2_info *args, uint8_t *r_data, uint16_t *r_len);
/*
*********************************************************************************************************
*	@function name: UnPack_Data
*	@description  : 解包收到的数据
*	@param[in] [out]  : buf  待拆包数据的地址指针
*	@param[in] [out]  : buf_len   待拆包数据的长度指针
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  UnPack_Data(uint8_t *buf, uint16_t *buf_len);

/*
*********************************************************************************************************
*	@function name: unpack_push_switchBackgroud
*	@description  : 拆包切入后台的数据
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/  
extern  uint16_t  unpack_push_switchBackgroud(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_push_switchView
*	@description  : 拆包视图切换的数据
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  unpack_push_switchView(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_push_recvData
*	@description  : 拆包接收到的数据
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  unpack_push_recvData(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_SendData_response
*	@description  : 拆包发送数据响应
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  unpack_SendData_response(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_Init_response
*	@description  : 拆包初始化数据响应
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  unpack_Init_response(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_auth_response
*	@description  : 拆包登录认证数据响应
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  unpack_auth_response(uint8_t *buf, uint16_t *buf_len);
  
  
//-----
#ifdef __cplusplus
}
#endif
//---------------------------------------------------------------------------
//-                             END                                         -
//---------------------------------------------------------------------------
#endif
