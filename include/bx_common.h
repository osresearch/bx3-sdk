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
#ifndef __BX_COMMON_H__
#define __BX_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"

/* exported paras ------------------------------------------------------------*/\

/* exported types ------------------------------------------------------------*/

#define BX_OK               0           /**< \brief OK               */
#define BX_ERROR            (-1)        /**< \brief Ò»°ã´íÎó         */

#define BX_NO_WAIT          0           /**< \brief ³¬Ê±£º²»µÈ´ý     */
#define BX_WAIT_FOREVER     (-1)        /**< \brief ³¬Ê±£ºÓÀÔ¶µÈ´ý   */

#define BX_FOREVER          (-1)        /**< \brief ÓÀÔ¶Ö´ÐÐ   */
/* exported variables --------------------------------------------------------*/

extern volatile u32 interrupt_disable_count;

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define GLOBAL_DISABLE_IRQ()                                \
do{                                                         \
    interrupt_disable_count++;                              \
    __disable_irq();                                        \
}while(0)

#define GLOBAL_ENABLE_IRQ()                                 \
do{                                                         \
    if( interrupt_disable_count > 0 ) {                     \
        interrupt_disable_count--;                          \
    }                                                       \
    if( interrupt_disable_count == 0 ) {                    \
        __enable_irq();                                     \
    }                                                       \
}while(0)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0])) 
/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BX_COMMON_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
