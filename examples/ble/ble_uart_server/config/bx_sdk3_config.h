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
#define BX_CHIP_TYPE                                    3
#endif


#ifndef BX_DEEP_SLEEP
#define BX_DEEP_SLEEP                                   1
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
