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
#define BX_DEEP_SLEEP                                  0
#endif

#if ( BX_DEEP_SLEEP > 0 )
#define BX_UART_SHELL_ENABLE                            0
#endif

#ifndef BX_UART_SHELL_ENABLE
#define BX_UART_SHELL_ENABLE                            1
#endif


#ifdef __cplusplus
}
#endif

#endif /* __BX_SDK3_CONFIG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
