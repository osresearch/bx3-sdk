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
#ifndef __COMPILER_FLAG_H__
#define __COMPILER_FLAG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported define -----------------------------------------------------------*/
#if !defined(__BOOT_RAM__)
#define USED_FLAG __attribute__((used))
#define XIP_SECTION __attribute__((section("xip_section")))
#define N_XIP_SECTION __attribute__((section("n_xip_section")))
#define N_XIP_VARIABLE __attribute__((section("n_xip_variable")))
#define NOINLINE __attribute__((noinline))
#else
#define USED_FLAG
#define XIP_SECTION
#define N_XIP_SECTION
#define N_XIP_VARIABLE
#define NOINLINE
#endif /* !defined(__BOOT_RAM__) */

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __COMPILER_FLAG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
