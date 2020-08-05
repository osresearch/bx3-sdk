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
#ifndef __BX_LOG_H__
#define __BX_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_dbg.h"

/* exported define -----------------------------------------------------------*/
#define GLOBAL_OUTPUT_LVL           LVL_DBG

#if !defined(LOG_TAG)
    #define LOG_TAG                 "NO_TAG"
#endif

#if !defined(LOG_LVL)
    #define LOG_LVL                 LVL_DBG
#endif

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

#if (LOG_LVL >= LVL_DBG) && (GLOBAL_OUTPUT_LVL >= LVL_DBG)
    #define bxlog_d(TAG, ...)           rtt_output(LVL_DBG, true,"D/"TAG":"__VA_ARGS__)
#else
    #define bxlog_d(TAG, ...)
#endif

#if (LOG_LVL >= LVL_INFO) && (GLOBAL_OUTPUT_LVL >= LVL_INFO)
    #define bxlog_i(TAG, ...)           rtt_output(LVL_INFO,true,"I/"TAG":"__VA_ARGS__)
#else
    #define bxlog_i(TAG, ...)
#endif

#if (LOG_LVL >= LVL_WARN) && (GLOBAL_OUTPUT_LVL >= LVL_WARN)
    #define bxlog_w(TAG, ...)           rtt_output(LVL_WARN,true,"W/"TAG":"__VA_ARGS__)
#else
    #define bxlog_w(TAG, ...)
#endif 

#if (LOG_LVL >= LVL_ERROR) && (GLOBAL_OUTPUT_LVL >= LVL_ERROR)
    #define bxlog_e(TAG, ...)           rtt_output(LVL_ERROR,true,"E/"TAG":"__VA_ARGS__)
#else
    #define bxlog_e(TAG, ...)
#endif 
    
#define LOG_D(...)      bxlog_d(LOG_TAG,__VA_ARGS__)
#define LOG_I(...)      bxlog_i(LOG_TAG,__VA_ARGS__)
#define LOG_W(...)      bxlog_w(LOG_TAG,__VA_ARGS__)
#define LOG_E(...)      bxlog_e(LOG_TAG,__VA_ARGS__)
#define LOG_RAW(...)    rtt_output(LVL_DBG,false, __VA_ARGS__)
    
/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BX_LOG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
