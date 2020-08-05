/**
  ******************************************************************************
  * @file   :   bx_gpio_type_def.h
  * @version:
  * @author :
  * @brief  :   Define common gpio types for different MCU
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
#ifndef __BX_GPIO_TYPE_DEF_H__
#define __BX_GPIO_TYPE_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

enum bx_pin_mode{
    BX_GPIO_MODE_INPUT,                      /*!< Input Floating Mode                   */
    BX_GPIO_MODE_OUTPUT,                     /*!< Output Push Pull Mode                 */

    /* 内部中断 */
    BX_GPIO_MODE_IT_LOW,                     /*!< GPIO Interrupt Mode with Low level trigger detection            */
    BX_GPIO_MODE_IT_HIGH,                    /*!< GPIO Interrupt Mode with High level trigger detection           */
    BX_GPIO_MODE_IT_RISING,                  /*!< GPIO Interrupt Mode with Rising edge trigger detection          */
    BX_GPIO_MODE_IT_FALLING,                 /*!< GPIO Interrupt Mode with Falling edge trigger detection         */
    BX_GPIO_MODE_IT_RISING_FALLING,          /*!< GPIO Interrupt Mode with Rising/Falling edge trigger detection  */

    /* 外部中断 */
    BX_GPIO_MODE_EIT_LOW,                    /*!< External Interrupt Mode with Low level trigger detection              */
    BX_GPIO_MODE_EIT_HIGH,                   /*!< External Interrupt Mode with High level trigger detection             */
    BX_GPIO_MODE_EIT_RISING,                 /*!< External Interrupt Mode with Rising edge trigger detection            */
    BX_GPIO_MODE_EIT_FALLING,                /*!< External Interrupt Mode with Falling edge trigger detection           */
    BX_GPIO_MODE_EIT_RISING_FALLING,         /*!< External Interrupt Mode with Rising/Falling edge trigger detection    */
    
    BX_GPIO_MODE_MAX,
};

enum bx_pin_pull{
    BX_GPIO_PULLUP,
    BX_GPIO_PULLDOWN,
    BX_GPIO_NOPULL,
    
    BX_GPIO_PULL_MAX,
};

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __BX_GPIO_TYPE_DEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

