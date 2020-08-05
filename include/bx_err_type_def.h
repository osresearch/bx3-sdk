/**
  ******************************************************************************
  * @file   :   .h
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BX_ERR_TYPE_DEF_H__
#define __BX_ERR_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/\

/* exported types ------------------------------------------------------------*/

typedef int bx_err_t;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

#define BX_ERR_PERM             1         /* 操作不允许          */
#define BX_ERR_NOMEM            2         /* 空间（内存）不足    */
#define BX_ERR_ACCES            3         /* 权限不够            */
#define BX_ERR_FAULT            4         /* 地址错误            */
#define BX_ERR_BUSY             5         /* 设备或资源忙        */
#define BX_ERR_INVAL            6         /* 无效参数            */
#define BX_ERR_NOTSUP           7         /* 不支持              */
#define BX_ERR_MSGSIZE          8         /* 消息太大            */

#define BX_ERR_FULL             9         /* 满                  */ 
#define BX_ERR_EMPTY            10        /* 空                  */
#define BX_ERR_HIGH             11        /* 值过高              */
#define BX_ERR_LOW              12        /* 值过低              */
#define BX_ERR_TIMEOUT          13        /* 超时                */
#define BX_ERR_POINTER_EMPTY    13        /* 空指针              */

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BX_ERR_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
