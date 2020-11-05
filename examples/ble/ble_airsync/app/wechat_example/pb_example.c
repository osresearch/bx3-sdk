//  pb_example.c
//  WeChat Embedded
//
//  Created by harlliu on 14-03-12.
//  Copyright 2014 Tencent. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc32.h"
#include "pb_example.h"

#include "epb_MmBp.h"
#include "ble_wechat_util.h"
#include "comsource.h"

#include "bx_shell.h"


//#define CATCH_LOG   

#if defined EAM_md5AndNoEnrypt || EAM_md5AndAesEnrypt
  uint8_t md5_type_id[] = MD5_TYPE_ID;
  uint8_t device_id[] = DEVICE_ID; 
  uint8_t device_key[] = DEVICE_KEY;      //与服务器握手时的初始 密钥
  uint8_t session_key[16] = {0};          //服务器返回的 加密密钥
#endif
//---------------------------------------------------------------------------
//-                             Extern Variables                            -
//---------------------------------------------------------------------------
//-----送包资料-----
uint8_t  PackProtobufData[PACKLEN] ;
uint16_t PackProtobufLen ;
//-----解包资料-----
uint8_t  UnPackProtobufData[UNPACKLEN] ;
uint16_t UnPackProtobufLen ;
uint16_t UnPackEmCmdID ;
//-----送数据报使用-----SendData
uint8_t  SendData[SEND_DATA_MAX] ;
uint16_t  SendDataLen ;

//-----包头长度
uint16_t bleDemoHeadLen = sizeof(BlueDemoHead);
uint8_t  fix_head_len = sizeof(BpFixHead);

// AES 加密使用
typedef struct 
{
	uint32_t random;
	uint32_t seq;
	uint32_t crc;
} auth_buf_t;

int auth_seq = 0;   // auth 登录认证次数

uint8_t challeange[CHALLENAGE_LENGTH] = {0};   //生成的随机数 数组

//-----设备状态标志
mpbledemo2_state  mpbledemo2Sta = {false, false, false, false, false, false,0,0,0};


/*******************************************************************************************************
 * LOCAL FUNCTIONS
 */
#if defined   EAM_md5AndAesEnrypt
  static uint16 aes_cbc_encrypt(uint8_t *r_data, uint16_t *r_len);
  static uint16 aes_cbc_decrypt(uint8_t *buf, uint16_t *buf_len);
#endif

/*
*********************************************************************************************************
*	@function name: pack_auth_request
*	@description  : 打包登录认证的数据
*	@param[in]    : 
*	@param[in]    : 
*	@return       : 
*********************************************************************************************************
*/

void pack_auth_request(BaseRequest basReq, BpFixHead fix_head, uint8_t *r_data, uint16_t *r_len)  
{
  
  #if defined EAM_md5AndAesEnrypt
      
    
  #endif
				
  #if defined EAM_macNoEncrypt
    uint8_t mac_address[MAC_ADDRESS_LENGTH];
//    Read_Mac(mac_address);
    AuthRequest authReq = {&basReq, false,{NULL, 0}, PROTO_VERSION, AUTH_PROTO, (EmAuthMethod)AUTH_METHOD, false,{NULL, 0}, true, {mac_address, MAC_ADDRESS_LENGTH}, false, {NULL, 0}, false, {NULL, 0},true,{DEVICE_ID,sizeof(DEVICE_ID)}};
  #endif
				
  #if defined EAM_md5AndNoEnrypt
    AuthRequest authReq = {&basReq, true,{md5_type_id, MD5_TYPE_AND_ID_LENGTH}, PROTO_VERSION, (EmAuthMethod)AUTH_PROTO, (EmAuthMethod)AUTH_METHOD, false ,{NULL, 0}, false, {NULL, 0}, false, {NULL, 0}, false, {NULL, 0},true,{DEVICE_ID,sizeof(DEVICE_ID)}};
  #endif
    
  *r_len = epb_auth_request_pack_size(&authReq) + fix_head_len;

  if(epb_pack_auth_request(&authReq, r_data+fix_head_len, *r_len-fix_head_len)<0)
  {
    r_data = NULL;
    return;
  }
  fix_head.nCmdId = htons(ECI_req_auth);
  fix_head.nLength = htons(*r_len);
  fix_head.nSeq = htons(mpbledemo2Sta.seq);
  memcpy(r_data, &fix_head, fix_head_len);
  
  return ;
}
/*
*********************************************************************************************************
*	@function name: pack_Init_request
*	@description  : 打包初始化数据
*	@param[in]    : 
*	@param[in]    : 
*	@return       : 
*********************************************************************************************************
*/
uint8_t pack_Init_request(BaseRequest basReq, BpFixHead fix_head, uint8_t *r_data, uint16_t *r_len) 
{
  
  //has challeange
  challeange[0]= rand();challeange[1]= rand();challeange[2]= rand();challeange[3]= rand();
  InitRequest initReq = {&basReq,false, {NULL, 0},true, {challeange, CHALLENAGE_LENGTH}};
  *r_len = epb_init_request_pack_size(&initReq) + fix_head_len;
    
  //pack data
  if(epb_pack_init_request(&initReq, r_data +fix_head_len, *r_len -fix_head_len)<0)
  {r_data = NULL;return 0;}
  
  //encrypt body
  #if defined EAM_md5AndAesEnrypt
    aes_cbc_encrypt( r_data,  r_len);
  #endif
  
  fix_head.nCmdId = htons(ECI_req_init);
  fix_head.nLength = htons(*r_len);
  fix_head.nSeq = htons(mpbledemo2Sta.seq);
//  osal_memcpy(r_data, &fix_head, fix_head_len);
  memcpy(r_data, &fix_head, fix_head_len);
  return  0;
}

/*
*********************************************************************************************************
*	@function name: pack_SendData_request
*	@description  : 打包要发送的数据
*	@param[in]    : 
*	@param[in]    : 
*	@return       : 
*********************************************************************************************************
*/
uint8_t pack_SendData_request(mpbledemo2_info *info, BaseRequest basReq, BpFixHead fix_head, uint8_t *r_data, uint16_t *r_len ) 
{
  
  BlueDemoHead  *bleDemoHead = (BlueDemoHead*)malloc(bleDemoHeadLen + info->send_msg.len);
  if(!bleDemoHead){bxsh_logln("\r\nNot enough memory!");return 0;}
  bleDemoHead->m_magicCode[0] = MPBLEDEMO2_MAGICCODE_H;
  bleDemoHead->m_magicCode[1] = MPBLEDEMO2_MAGICCODE_L;
  bleDemoHead->m_version = htons( MPBLEDEMO2_VERSION);
  bleDemoHead->m_totalLength = htons(bleDemoHeadLen + info->send_msg.len);
  bleDemoHead->m_cmdid = htons(sendTextReq);
  bleDemoHead->m_seq = htons(mpbledemo2Sta.seq);
  bleDemoHead->m_errorCode = 0;	

  /*connect body and head.*/
  /*turn to uint8_t* befort offset.*/
  memcpy((uint8_t*)bleDemoHead+bleDemoHeadLen, info->send_msg.str, info->send_msg.len);	
  //--------------------------此处修改发送数据的路径----------------------------
  //SEND_H5 true:微信客户端设备html5会话界面数据 false:表示设备发送厂商自定义数据到厂商服务器
  #if (SEND_TYPE_H5==TRUE)
     SendDataRequest sendDatReq = {&basReq, {(uint8_t*) bleDemoHead, (bleDemoHeadLen + info->send_msg.len)}, true, (EmDeviceDataType)EDDT_wxDeviceHtmlChatView};//发送数据到微信客户端设备html5会话界面数据
  #else
     SendDataRequest sendDatReq = {&basReq, {(uint8_t*) bleDemoHead, (bleDemoHeadLen + info->send_msg.len)}, false, (EmDeviceDataType)NULL};   //发送数据到厂商服务器
  #endif
  //----------------------------------------------------------------------------
  
  *r_len = epb_send_data_request_pack_size(&sendDatReq) + fix_head_len;
  
  if(epb_pack_send_data_request(&sendDatReq, r_data + fix_head_len, *r_len - fix_head_len)<0)
  {
    r_data = NULL;   
    bxsh_logln("\r\n epb_pack_send_data_request error!");
    return 0;
  }
  #if defined EAM_md5AndAesEnrypt
    //encrypt body
    aes_cbc_encrypt( r_data,  r_len);
  #endif
    
  fix_head.nCmdId = htons(ECI_req_sendData);
  fix_head.nLength = htons(*r_len);
  fix_head.nSeq = htons(mpbledemo2Sta.seq);
//  osal_memcpy(r_data, &fix_head, fix_head_len);
  memcpy(r_data, &fix_head, fix_head_len);
  
  if(bleDemoHead){free(bleDemoHead);bleDemoHead = NULL;}
  
  #ifdef CATCH_LOG
    bxsh_logln("\r\n##send data: ");
    uint8_t *d = r_data;
    for(uint8_t i=0;i<*r_len;++i){
    bxsh_logln(" ",d[i],16);}
    BpFixHead *fix_head2 = (BpFixHead *)r_data;
    bxsh_logln("\r\n CMDID: ",ntohs(fix_head2->nCmdId),10);
    bxsh_logln("\r\n len: ", ntohs(fix_head2->nLength ),10);
    bxsh_logln("\r\n Seq: ", ntohs(fix_head2->nSeq),10);
  #endif
  mpbledemo2Sta.send_data_seq++;
				
  return 0;
}



/*
*********************************************************************************************************
*	@function name: unpack_auth_response
*	@description  : 拆包登录认证数据响应
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/

uint16_t unpack_auth_response(uint8_t *buf, uint16_t *buf_len)
{
  
  AuthResponse* authResp;
  authResp = epb_unpack_auth_response(buf + fix_head_len, *buf_len - fix_head_len);
  #ifdef CATCH_LOG
    bxsh_logln("\r\n@@Received 'authResp'\r\n");
  #endif
  if(!authResp)
  {
    return errorCodeUnpackAuthResp;
  }
  #ifdef CATCH_LOG
    bxsh_logln("\r\n unpack 'authResp' success!\r\n");
  #endif
  if(authResp->base_response)
  {
    if(authResp->base_response->err_code == 0)
    {
      mpbledemo2Sta.auth_state = true;
    }
    else
    {
      #ifdef CATCH_LOG
        bxsh_logln("\r\n error code: ", authResp->base_response->err_code, 10);
      #endif
        
      #ifdef CATCH_LOG
      if(authResp->base_response->has_err_msg)
      {
        bxsh_logln("\r\n base_response error msg:");	
        //bxsh_logln(uint8 *(authResp->base_response->err_msg.str));
      }
      #endif
      epb_unpack_auth_response_free(authResp);
      return authResp->base_response->err_code;
    }
  }
  #if defined EAM_md5AndAesEnrypt   // get sessionkey
   
  #endif
  epb_unpack_auth_response_free(authResp);  
  return 0;
}
/*
*********************************************************************************************************
*	@function name: unpack_Init_response
*	@description  : 拆包初始化数据响应
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
uint16_t unpack_Init_response(uint8_t *buf, uint16_t *buf_len)
{
  
  #ifdef CATCH_LOG
    bxsh_logln("\r\n@@Received 'initResp'\r\n");
  #endif
    
  #if defined EAM_md5AndAesEnrypt		
    aes_cbc_decrypt( buf,  buf_len);
  #endif	
    
  InitResponse *initResp = epb_unpack_init_response(buf + fix_head_len, *buf_len - fix_head_len);
  if(!initResp)
  {
    return errorCodeUnpackInitResp;
  }
  
  #ifdef CATCH_LOG
    bxsh_logln("\r\n unpack 'initResp' success!");
  #endif
  
  if(initResp->base_response)
  {
    if(initResp->base_response->err_code == 0)
    {
      if(initResp->has_challeange_answer)
      {
        if(crc32(0,challeange,CHALLENAGE_LENGTH) == initResp->challeange_answer)
        {
          mpbledemo2Sta.init_state = true;
        }
      }
      else 
      {
        mpbledemo2Sta.init_state = true;
      }
      mpbledemo2Sta.wechats_switch_state = true;
    }
    else
    {
      #ifdef CATCH_LOG
        bxsh_logln("\r\n error code: ", initResp->base_response->err_code, 10);
      #endif	
      if(initResp->base_response->has_err_msg)
      {
        #ifdef CATCH_LOG
          bxsh_logln("\r\n base_response error msg:");
          //bxsh_logln(initResp->base_response->err_msg.str);
        #endif	
      }
      epb_unpack_init_response_free(initResp);
      return initResp->base_response->err_code;
    }
  }
  epb_unpack_init_response_free(initResp);
  return 0;
}


/*
*********************************************************************************************************
*	@function name: unpack_SendData_response
*	@description  : 拆包发送数据响应
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
uint16_t unpack_SendData_response(uint8_t *buf, uint16_t *buf_len)
{
  #ifdef CATCH_LOG
    bxsh_logln("\r\n@@Received 'sendDataResp'\r\n");
  #endif
  #if defined EAM_md5AndAesEnrypt		
    aes_cbc_decrypt( buf, buf_len);
  #endif	
    
  SendDataResponse *sendDataResp;
  sendDataResp = epb_unpack_send_data_response(buf + fix_head_len, *buf_len - fix_head_len);
  if(!sendDataResp)
  {
    return errorCodeUnpackSendDataResp;
  }
  
  #ifdef CATCH_LOG
  BlueDemoHead *bledemohead = (BlueDemoHead*)sendDataResp->data.data;
  if(ntohs(bledemohead->m_cmdid) == sendTextResp)
  {
    bxsh_logln("\r\n received msg: ");
    //bxsh_logln(uint8 *(sendDataResp->data.data));
    bxsh_logln(" ",sizeof(BlueDemoHead),10);
  }
  #endif
  
  if(sendDataResp->base_response->err_code)
  {
    epb_unpack_send_data_response_free(sendDataResp);
    return sendDataResp->base_response->err_code;
  }
  epb_unpack_send_data_response_free(sendDataResp);
  return 0;
}

/*
*********************************************************************************************************
*	@function name: unpack_push_recvData
*	@description  : 拆包接收到的数据
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
uint16_t unpack_push_recvData(uint8_t *buf, uint16_t *buf_len)
{
  #if defined EAM_md5AndAesEnrypt
    aes_cbc_decrypt( buf, buf_len);
  #endif
  
  RecvDataPush *recvDatPush;
  recvDatPush = epb_unpack_recv_data_push(buf + fix_head_len, *buf_len - fix_head_len);
  
  #ifdef CATCH_LOG
    bxsh_logln("\r\n@@Received 'recvDataPush'\r\n");
  #endif
    
  if(!recvDatPush)
  {
    return errorCodeUnpackRecvDataPush;
  }
  
  #ifdef CATCH_LOG
    bxsh_logln("\r\n unpack the 'recvDataPush' successfully! \r\n");
    if(recvDatPush->base_push == NULL)
    {
      bxsh_logln("\r\n recvDatPush->base_push is NULL! \r\n");
    }
    else 
    {
      bxsh_logln("\r\n recvDatPush->base_push is not NULL! \r\n");
    }
    bxsh_logln("\r\n recvDatPush->data.len: ",recvDatPush->data.len,16);
    bxsh_logln("\r\n recvDatPush->data.data:  \r\n");
    const uint8_t *d = recvDatPush->data.data;
    for(uint8_t i=0;i<recvDatPush->data.len;++i){
    bxsh_logln(" ", d[i], 16);}
    if(recvDatPush->has_type)
    {
      bxsh_logln("\r\n recvDatPush has type! \r\n");
      bxsh_logln("\r\n type: ", recvDatPush->type, 10);                              
    }
  #endif
    
  BlueDemoHead *bledemohead = (BlueDemoHead*)recvDatPush->data.data;
  
  #ifdef CATCH_LOG
    bxsh_logln("\r\n magicCode: ", bledemohead->m_magicCode[0], 16);
    bxsh_logln(" ", bledemohead->m_magicCode[1], 16);
    bxsh_logln("\r\n version: ", ntohs(bledemohead->m_version), 16);
    bxsh_logln("\r\n totalLength: ", ntohs(bledemohead->m_totalLength), 16);
    bxsh_logln("\r\n cmdid: ", ntohs(bledemohead->m_cmdid ), 16);
    bxsh_logln("\r\n errorCode: ", ntohs(bledemohead->m_errorCode), 16);
  #endif
    
//  if(ntohs(bledemohead->m_cmdid ) == openLightPush)
//  {
//    					
//  }
//  else if(ntohs(bledemohead->m_cmdid )  == closeLightPush)
//  {
//   
//  }
  
  epb_unpack_recv_data_push_free(recvDatPush);
    
  
  mpbledemo2Sta.push_data_seq++;

  return 0;
}

/*
*********************************************************************************************************
*	@function name: unpack_push_switchView
*	@description  : 拆包视图切换的数据
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
uint16_t unpack_push_switchView(uint8_t *buf, uint16_t *buf_len)
{
  
  mpbledemo2Sta.wechats_switch_state = !mpbledemo2Sta.wechats_switch_state;
  
  #ifdef CATCH_LOG
    bxsh_logln("\r\n@@Received 'switchViewPush'\r\n");
  #endif
    
  #if defined EAM_md5AndAesEnrypt		
    aes_cbc_decrypt( buf,  buf_len);
  #endif	
    
  SwitchViewPush *swichViewPush;
  swichViewPush = epb_unpack_switch_view_push(buf + fix_head_len, *buf_len - fix_head_len);
  if(!swichViewPush)
  {
    return errorCodeUnpackSwitchViewPush;
  }
  epb_unpack_switch_view_push_free(swichViewPush);
  return 0;
}

/*
*********************************************************************************************************
*	@function name: unpack_push_switchBackgroud
*	@description  : 拆包切入后台的数据
*	@param[in] [out]  : buf       待拆包数据的地址指针 和 拆包后的数据
*	@param[in] [out]  : buf_len   待拆包数据的长度指针 和 拆包后的数据长度
*	@return       : 
*********************************************************************************************************
*/
uint16_t unpack_push_switchBackgroud(uint8_t *buf, uint16_t *buf_len)
{
  #ifdef CATCH_LOG
    bxsh_logln("\r\n@@Received 'switchBackgroudPush'\r\n");
  #endif
    
  #if defined EAM_md5AndAesEnrypt
    aes_cbc_decrypt( buf,  buf_len);
  #endif
    
  SwitchBackgroudPush *switchBackgroundPush = epb_unpack_switch_backgroud_push(buf + fix_head_len, *buf_len - fix_head_len);
  if(! switchBackgroundPush)
  {
    return errorCodeUnpackSwitchBackgroundPush;
  }	
  epb_unpack_switch_backgroud_push_free(switchBackgroundPush);
  return 0;
}

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
uint8_t Pack_Data(mpbledemo2_info *args, uint8_t *r_data, uint16_t *r_len)
{

  mpbledemo2_info *info = args;
  BaseRequest basReq = {NULL};
  BpFixHead fix_head = {0xFE, 1, 0, htons(ECI_req_auth), 0};
  mpbledemo2Sta.seq++;
  switch (info->cmd)
  {
    case CMD_AUTH:
    {
	pack_auth_request( basReq,  fix_head, r_data, r_len);	
    }
      break;
    case CMD_INIT:
    {
        pack_Init_request( basReq,  fix_head, r_data, r_len);	
    }
      break;
    case CMD_SENDDAT:
    {
	pack_SendData_request( info,  basReq,  fix_head,  r_data,  r_len );					
    }
      break;
  }
  return 0; 
}

/*
*********************************************************************************************************
*	@function name: UnPack_Data
*	@description  : 解包要发送的数据
*	@param[in] [out]  : buf  待拆包数据的地址指针
*	@param[in] [out]  : buf_len   待拆包数据的长度指针
*	@return       : 
*********************************************************************************************************
*/
uint16_t UnPack_Data(uint8_t *buf, uint16_t *buf_len) 
{
  	BpFixHead *fix_head = (BpFixHead *)buf;
	fix_head_len = sizeof(BpFixHead);
	#ifdef CATCH_LOG
	    bxsh_logln("\r\n##Received data: ");
	    uint8_t *d = buf;
	    for(uint8_t i=0; i<buf_len; ++i){
	    bxsh_logln("  ", d[i], 16);}
	    bxsh_logln("\r\n CMDID: ", ntohs(fix_head->nCmdId), 10);
	    bxsh_logln("\r\n len: ", ntohs(fix_head->nLength), 10);
	    bxsh_logln("\r\n Seq: ", ntohs(fix_head->nSeq), 10);
	#endif
        switch(ntohs(fix_head->nCmdId))
        {
          case ECI_none:
	    {
	    }
	    break;
	  case ECI_resp_auth:
            {
              unpack_auth_response(buf, buf_len);
            }
            break;
          case ECI_resp_init:
            {
              unpack_Init_response(buf, buf_len);
            }
            break;
          case ECI_resp_sendData:
            {
              unpack_SendData_response( buf,  buf_len);
            }
            break;
          case ECI_push_recvData:
            {
              unpack_push_recvData( buf,  buf_len);
            }
            break;
          case ECI_push_switchView:
            {
              unpack_push_switchView( buf,  buf_len);
            }
            break;
          case ECI_push_switchBackgroud:
            {
              unpack_push_switchBackgroud( buf, buf_len);
            }
            break;
          case ECI_err_decode:
            {
                #ifdef CATCH_LOG
		  bxsh_logln("\r\n ECI_err_decode");
		#endif
            }
            break;
	default:
	  {
		#ifdef CATCH_LOG
			bxsh_logln("\r\n !!ERROR CMDID:",ntohs(fix_head->nCmdId),10);
		#endif
	  }
	  break;
        
        }
        return ntohs(fix_head->nCmdId);

}



#if defined  EAM_md5AndAesEnrypt

/*
*********************************************************************************************************
*	@function name: aes_cbc_encrypt
*	@description  : AES 加密要发送的数据
*	@param[in] [out]  : r_data  待发送数据的地址指针
*	@param[in] [out]  : r_len   待发送数据的长度指针
*	@return       : 
*********************************************************************************************************
*/
uint16 aes_cbc_encrypt(uint8_t *r_data, uint16_t *r_len)
{

    return 0;
}

/*
*********************************************************************************************************
*	@function name: aes_cbc_decrypt
*	@description  : AES 解密接收到的数据
*	@param[in] [out]  : buf      待解密数据的地址指针
*	@param[in] [out]  : buf_len  待解密数据的长度指针
*	@return       : 
*********************************************************************************************************
*/
uint16 aes_cbc_decrypt(uint8_t *buf, uint16_t *buf_len)
{
   
    return 0;
}

#endif
