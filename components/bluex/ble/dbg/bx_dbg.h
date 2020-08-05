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
#ifndef __BX_DBG_H__
#define __BX_DBG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

#include "bx_config.h"
//#define NDEBUG

#define __ASSERT_MSG
#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include "jump_table.h"

/* exported define -----------------------------------------------------------*/

#define LVL_ERROR                       1
#define LVL_WARN                        2
#define LVL_INFO                        3
#define LVL_DBG                         4

#define SIM_REPORT_BASE                 0x2010f004
#define SIM_PRINT_BASE                  (SIM_REPORT_BASE+4)
#define SIM_PRINT_DATA_BASE             (SIM_REPORT_BASE+8)

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define RWIP_ASSERT(lvl,e,param0,param1) if(!(e)) rwip_assert_asm((lvl),(uint32_t)(param0),(uint32_t)(param1))   

/* exported functions --------------------------------------------------------*/

void __aeabi_assert(const char *expr,const char *file,int line);
void bx_simu_pass(void);
void bx_simu_fail(void);
void bx_simu_finish(void);
void rtt_output(int8_t level,bool linefeed,const char *format,...);

#if defined(__BOOT_RAM__)
    #define BX_ASSERT(e)
#else
    #if defined(__GNUC__)
        #define BX_ASSERT(e) ((e)? (void)0 : __aeabi_assert(#e,__FILE__,__LINE__))
    #elif defined(__arm__)
        #define BX_ASSERT(e) assert(e)
    #else
        #error "compiler not supported\n"
    #endif
#endif /* defined(__BOOT_RAM__) */

 #ifdef __RAM_CODE__
    void rwip_assert_asm(uint32_t,uint32_t,uint32_t);
 #else
    typedef void (*rwip_assert_fn)(uint32_t,uint32_t,uint32_t);
    #define rwip_assert_asm(lvl,param0,param1) ((rwip_assert_fn)jump_table[RWIP_ASSERT_DBG])((lvl),(param0),(param1))
 #endif /* __RAM_CODE__ */

#if (defined(BX_VERF)&&(BX_VERF==1))
    #define SIMU_PASS() bx_simu_pass()
    #define SIMU_FAIL() bx_simu_fail()
    #define SIMU_FINISH() bx_simu_finish()
#else
    #define SIMU_PASS()
    #define SIMU_FAIL()
    #define SIMU_FINISH()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __BX_DBG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

