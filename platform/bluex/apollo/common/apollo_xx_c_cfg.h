/**
  ******************************************************************************
  * @file   :   .h
  * @version:    
  * @author :
  * @brief  :   Just for Include Other Head File
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
#ifndef __APOLLO_XX_C_CFG_H__
#define __APOLLO_XX_C_CFG_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* config ------------------------------------------------------------------*/
#define BX_GPIO_MODULE_ENABLE

/* includes ------------------------------------------------------------------*/

#ifdef BX_GPIO_MODULE_ENABLE
  #include "bx_gpio.h"
#endif /* USE_BOARD_APOLLO00 */

#ifdef BX_UART_MODULE_ENABLE
  #include "bx_gpio.h"
#endif /* BX_UART_MODULE_ENABLE */

/* exported types ------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#ifdef  USE_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed( uint8_t * file, uint32_t line );
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_ASSERT */
/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_XX_C_CFG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

