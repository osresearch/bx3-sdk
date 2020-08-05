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
#ifndef __TRUE_RANDOM_H__
#define __TRUE_RANDOM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void     hw_trng_get_numbers(uint8_t *buffer, uint8_t length);
uint32_t get_random_seed(void);
void     generate_random_seed(void);

#ifdef __cplusplus
}
#endif

#endif /* __TRUE_RANDOM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
