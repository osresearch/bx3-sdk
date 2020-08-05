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

#define BX_ERR_PERM             1         /* ����������          */
#define BX_ERR_NOMEM            2         /* �ռ䣨�ڴ棩����    */
#define BX_ERR_ACCES            3         /* Ȩ�޲���            */
#define BX_ERR_FAULT            4         /* ��ַ����            */
#define BX_ERR_BUSY             5         /* �豸����Դæ        */
#define BX_ERR_INVAL            6         /* ��Ч����            */
#define BX_ERR_NOTSUP           7         /* ��֧��              */
#define BX_ERR_MSGSIZE          8         /* ��Ϣ̫��            */

#define BX_ERR_FULL             9         /* ��                  */ 
#define BX_ERR_EMPTY            10        /* ��                  */
#define BX_ERR_HIGH             11        /* ֵ����              */
#define BX_ERR_LOW              12        /* ֵ����              */
#define BX_ERR_TIMEOUT          13        /* ��ʱ                */
#define BX_ERR_POINTER_EMPTY    13        /* ��ָ��              */

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BX_ERR_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
