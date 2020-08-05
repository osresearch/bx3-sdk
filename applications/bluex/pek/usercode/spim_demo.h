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
#ifndef __SPIM_DEMO_H__
#define __SPIM_DEMO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
/* includes ------------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void spim_add_shell_cmd( void );

void oled_init(void);
void OLED_Refresh(void);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1,uint8_t mode);
#ifdef __cplusplus
}
#endif

#endif /* __SPIM_DEMO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

