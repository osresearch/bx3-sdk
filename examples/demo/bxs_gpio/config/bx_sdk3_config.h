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
#ifndef __BX_SDK3_CONFIG_H__
#define __BX_SDK3_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BX_DEEP_SLEEP
#define BX_DEEP_SLEEP                                   0
#endif

#define BX_ENABLE_LOG                                   1

#if ( BX_ENABLE_LOG > 0 )
    #define LOG_PRINTF_BUFFER_SIZE                      256
    #define GLOBAL_LOG_LVL                              5
    
    
    #define BX_USE_RTT_LOG                              0
    #define BX_USE_UART_LOG                             1
    #if ( BX_USE_RTT_LOG && BX_USE_UART_LOG )
        #error "You can only choose one. RTT or UART"
    #endif
    
    //#define BX_DATA_NEWLINE_SIGN                        "\r"
    #define BX_DATA_NEWLINE_SIGN                        "\n"
    //#define BX_DATA_NEWLINE_SIGN                        "\r\n"
    
    #define BX_USE_SYS_TICK_FOR_LOG                     0
#else
    #define GLOBAL_LOG_LVL                              (-1)
#endif 

#ifndef BX_USE_WDT
#define BX_USE_WDT                                      0
#endif

#ifdef __cplusplus
}
#endif

#endif /* __BX_SDK3_CONFIG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
