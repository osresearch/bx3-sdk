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
#ifndef __PATCH_H__
#define __PATCH_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "reg_bus_ptch.h"

/* exported define -----------------------------------------------------------*/
//#define V4_ROM
#define MP_ROM

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define PATCH_ENABLE(no)            ( hwp_bus_ptch->trap_en.val |= 1 << (no) )

/* exported functions --------------------------------------------------------*/

void     patch_init(void);

bool     patch_alloc(uint8_t *no);

void     patch_entrance_exit_addr(uint8_t patch_no, uint32_t entrance_addr, uint32_t run_code);

void     patch_enable_set(uint16_t trap_en_map);

uint16_t patch_status_get(void);

uint32_t cal_patch_bl(uint32_t srcAddr,uint32_t dstAddr);

uint32_t cal_patch_pushlr(uint32_t patched_func);

void     half_word_aligned_bl_patch(uint32_t src_addr,void *patch_func);


#ifdef __cplusplus
}
#endif

#endif /* __PATCH_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
