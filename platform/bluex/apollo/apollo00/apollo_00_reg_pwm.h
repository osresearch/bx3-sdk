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
#ifndef __APOLLO_00_REG_PWM_H__
#define __APOLLO_00_REG_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

typedef struct {
    __IO uint32_t EN;                   /* !< enable register           0x0000 */
    __IO uint32_t PS;                   /* !< pulse setting register    0x0004 */
} reg_pwm_t;

/* bit definition ------------------------------------------------------------*/

/* value type ----------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_PWM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

