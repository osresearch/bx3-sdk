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

//1 => rf01
//2 => bx2416
//3 => rf03
//4 => rf04
//8 => rf08
#ifndef BX_CHIP_TYPE
#define BX_CHIP_TYPE                                    1
#endif


#ifndef BX_DEEP_SLEEP
#define BX_DEEP_SLEEP                                   1
#endif

#define BX_ENABLE_LOG                                   1

#if ( BX_ENABLE_LOG > 0 )
    #define LOG_PRINTF_BUFFER_SIZE                      64
    #define GLOBAL_LOG_LVL                              5
    
    
    #define BX_USE_RTT_LOG                              0
    #define BX_USE_UART_LOG                             1
    #if ( BX_USE_RTT_LOG && BX_USE_UART_LOG )
        #error "You can only choose one. RTT or UART"
    #endif
    
    //#define BX_DATA_NEWLINE_SIGN                        "\r"
    #define BX_DATA_NEWLINE_SIGN                        "\n"
    //#define BX_DATA_NEWLINE_SIGN                        "\r\n"
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
