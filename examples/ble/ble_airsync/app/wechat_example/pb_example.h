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
  
  
//  DEVICE_TYPE �� DEVICE_ID ΢��Ӳ��ƽ̨����
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
     // ������һ��MD5(deviceType+deviceId)������豸��MD5 ���鷳�Ļ���������
     // ��ã�ֱ���ս��豸���档��MD5 �������û�������ο� ��΢����������Э��1.0.4�� 14ҳ
     // http://tool.chinaz.com/tools/md5.aspx    ����MD5 ������վ  32λ��С��

//   #define    MD5_TYPE_ID   {0xd2, 0xce, 0x5a, 0xdd, 0xc9, 0x0d, 0x2c, 0x19, 0x9b, 0x82, 0xc7, 0xb8, 0x72, 0x24, 0x9e, 0xe8}
     #define    MD5_TYPE_ID   {0x37,0x60,0x8c,0x00,0x79,0x22,0xba,0x35,0x80,0x21,0x53,0x22,0x91,0x6d,0x35,0x45}
     // �豸��Ҫ��һ��Key��128 λ����Ӳ���ϣ�΢�ŷ�����ҲҪ��¼�����Key��    
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

#define PACKLEN                 100     //�Ͱ����ݵĻ���������
#define UNPACKLEN               100     //������ݵĻ���������
#define SEND_DATA_MAX           100     //�������ݵ���󳤶�

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
//-----�Ͱ�����-----
extern uint8_t  PackProtobufData[PACKLEN] ;
extern uint16_t PackProtobufLen ;
//-----�������-----
extern uint8_t  UnPackProtobufData[UNPACKLEN] ;
extern uint16_t UnPackProtobufLen ;
extern uint16_t UnPackEmCmdID ;
//-----�����ݱ�ʹ��-----SendData
extern uint8_t  SendData[SEND_DATA_MAX] ;
extern uint16_t SendDataLen ;
//-----��ͷ����
extern uint16_t bleDemoHeadLen ;
extern uint8_t  fix_head_len ;
//---------------------------------------------------------------------------
//-                             Extern product status Variables                            -
//---------------------------------------------------------------------------
//-----�豸״̬��־
extern mpbledemo2_state mpbledemo2Sta;
//---------------------------------------------------------------------------
//-                             Extern Function                             -
//---------------------------------------------------------------------------
/*
*********************************************************************************************************
*	@function name: Pack_Data
*	@description  : ���Ҫ���͵�����
*	@param[in] : args.cmd  ������������ݰ������� ; args.send_msg �������ݰ�ʱ������
*	@param[in] [out]  : r_data  ��������ݵĵ�ַָ��
*	@param[in] [out]  : r_len   ��������ݵĳ���ָ��
*	@return       : 
*********************************************************************************************************
*/
extern  uint8_t Pack_Data(mpbledemo2_info *args, uint8_t *r_data, uint16_t *r_len);
/*
*********************************************************************************************************
*	@function name: UnPack_Data
*	@description  : ����յ�������
*	@param[in] [out]  : buf  ��������ݵĵ�ַָ��
*	@param[in] [out]  : buf_len   ��������ݵĳ���ָ��
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  UnPack_Data(uint8_t *buf, uint16_t *buf_len);

/*
*********************************************************************************************************
*	@function name: unpack_push_switchBackgroud
*	@description  : ��������̨������
*	@param[in] [out]  : buf       ��������ݵĵ�ַָ�� �� ����������
*	@param[in] [out]  : buf_len   ��������ݵĳ���ָ�� �� ���������ݳ���
*	@return       : 
*********************************************************************************************************
*/  
extern  uint16_t  unpack_push_switchBackgroud(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_push_switchView
*	@description  : �����ͼ�л�������
*	@param[in] [out]  : buf       ��������ݵĵ�ַָ�� �� ����������
*	@param[in] [out]  : buf_len   ��������ݵĳ���ָ�� �� ���������ݳ���
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  unpack_push_switchView(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_push_recvData
*	@description  : ������յ�������
*	@param[in] [out]  : buf       ��������ݵĵ�ַָ�� �� ����������
*	@param[in] [out]  : buf_len   ��������ݵĳ���ָ�� �� ���������ݳ���
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  unpack_push_recvData(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_SendData_response
*	@description  : �������������Ӧ
*	@param[in] [out]  : buf       ��������ݵĵ�ַָ�� �� ����������
*	@param[in] [out]  : buf_len   ��������ݵĳ���ָ�� �� ���������ݳ���
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  unpack_SendData_response(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_Init_response
*	@description  : �����ʼ��������Ӧ
*	@param[in] [out]  : buf       ��������ݵĵ�ַָ�� �� ����������
*	@param[in] [out]  : buf_len   ��������ݵĳ���ָ�� �� ���������ݳ���
*	@return       : 
*********************************************************************************************************
*/
extern  uint16_t  unpack_Init_response(uint8_t *buf, uint16_t *buf_len);
/*
*********************************************************************************************************
*	@function name: unpack_auth_response
*	@description  : �����¼��֤������Ӧ
*	@param[in] [out]  : buf       ��������ݵĵ�ַָ�� �� ����������
*	@param[in] [out]  : buf_len   ��������ݵĳ���ָ�� �� ���������ݳ���
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
