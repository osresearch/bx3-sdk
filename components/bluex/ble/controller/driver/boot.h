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
#ifndef __BOOT_H__
#define __BOOT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

extern const uint32_t Load$$ISR_VECTOR$$Base;
#define LOAD_ISR_VECTOR_BASE (&Load$$ISR_VECTOR$$Base) 

extern const uint32_t Image$$ISR_VECTOR$$Base;
#define IMAGE_ISR_VECTOR_BASE (&Image$$ISR_VECTOR$$Base)

extern const uint32_t Load$$ISR_VECTOR$$Length;
#define LOAD_ISR_VECTOR_LENGTH (&Load$$ISR_VECTOR$$Length)

extern const uint32_t Image$$BOOT_PARAMS$$Base;
#define IMAGE_BOOT_PARAMS_BASE (&Image$$BOOT_PARAMS$$Base)


extern const uint32_t Image$$RAM_UNLOADED$$Base;
#define RAM_UNLOADED_BASE (&Image$$RAM_UNLOADED$$Base)

extern uint32_t __initial_sp;
#define STACK_TOP __initial_sp

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __BOOT_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
