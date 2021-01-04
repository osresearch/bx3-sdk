/**
  ******************************************************************************
  * @file   :   bx_uart_type_def.h
  * @version:
  * @author :
  * @brief  :   Define common uart types for different MCU
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
#ifndef __BX_UART_TYPE_DEF_H__
#define __BX_UART_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
enum bx_uart_baudrate{
    BX_UART_BD_1200,
    BX_UART_BD_2400,
    BX_UART_BD_4800,
    BX_UART_BD_9600,
    BX_UART_BD_14400,
    BX_UART_BD_19200,
    BX_UART_BD_38400,
    BX_UART_BD_57600,
    BX_UART_BD_76800,
    BX_UART_BD_115200,
    BX_UART_BD_230400,
    BX_UART_BD_250000,
    BX_UART_BD_256000,
    BX_UART_BD_460800,
    BX_UART_BD_500000,
    BX_UART_BD_921600,
    BX_UART_BD_1000000,
    BX_UART_BD_2000000,
    
    BX_UART_BD_MAX,
};

enum bx_uart_stop_bit{
    BX_UART_SB_ONE,
    BX_UART_SB_TWO,
    BX_UART_SB_ONE_POINT_FIVE,

    BX_UART_SB_MAX
};

enum bx_uart_data_bit{
    BX_UART_DB_5B,
    BX_UART_DB_6B,
    BX_UART_DB_7B,
    BX_UART_DB_8B,
    
    BX_UART_DB_MAX
};

enum bx_uart_parity{
    //     不发生奇偶校验检查。
    BX_UART_PARITY_NONE,
    //     设置奇偶校验位，使位数等于奇数。
    BX_UART_PARITY_ODD,
    //     设置奇偶校验位，使位数等于偶数。
    BX_UART_PARITY_EVEN,
    //     将奇偶校验位保留为 1。
    BX_UART_PARITY_MARK,
    //     将奇偶校验位保留为 0。
    BX_UART_PARITY_SPACE,
    
    BX_UART_PARITY_MAX,
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __BX_UART_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

