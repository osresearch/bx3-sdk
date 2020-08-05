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
#ifndef __APOLLO_00_BLE_REG_H__
#define __APOLLO_00_BLE_REG_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* config ------------------------------------------------------------------*/
#define USE_ASSERT

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

//typedef enum IRQn
//{
///******  Cortex-M# Processor Exceptions Numbers ***************************************************/

///* ToDo: use this Cortex interrupt numbers if your device is a CORTEX-M0 device                   */
//  NonMaskableInt_IRQn           = -14,      /*!<  2 Non Maskable Interrupt                        */
//  HardFault_IRQn                = -13,      /*!<  3 Hard Fault Interrupt                          */
//  SVCall_IRQn                   = -5,       /*!< 11 SV Call Interrupt                             */
//  PendSV_IRQn                   = -2,       /*!< 14 Pend SV Interrupt                             */
//  SysTick_IRQn                  = -1,       /*!< 15 System Tick Interrupt                         */

///******  Device Specific Interrupt Numbers ********************************************************/
//  WDT_IRQn               		=   0,      
//  BLE_LP_IRQn               	=   1,     
//  BLE_MAC_IRQn             	  	=   2,      
//  RTC_IRQn                 		=   3,      
//  EXT_INTR_IRQn             	=   4,     
//  ECC_IRQn               	    =   5,
//  DMAC_IRQn            	    	=   6,     
//  QSPI_IRQn                     =   7,      
//  SPIM0_IRQn                    =   8,     
//  SPIM1_IRQn                    =   9,     
//  SPIS_IRQn                     =  10,    
//  UART0_IRQn                    =  11,     
//  UART1_IRQn                    =  12,     
//  IIC0_IRQn                     =  13,      
//  IIC1_IRQn                     =  14,    
//  GPIO_IRQn                     =  15,      
//  TIMER_IRQn                    =  16,     
//  SFT_IRQn                      =  17,
//  PGSPY_IRQn                    =  18,

//} IRQn_Type;
///*
// * ==========================================================================
// * ----------- Processor and Core Peripheral Section ------------------------
// * ==========================================================================
// */

///* Configuration of the Cortex-M0 Processor and Core Peripherals */

//#define __CM0PLUS_REV             0x0000    /*!< Core Revision r0p0                               */
//#define __VTOR_PRESENT            1         /*!< VTOR present or not 					          */
//#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels          */
//#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */
//#define __MPU_PRESENT             1         /*!< MPU present or not                               */
//#define __FPU_PRESENT             0         /*!< FPU present or not                               */

//#include "core_cm0plus.h"

#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

#define    REG_SRAM_BASE                    0x00100000
#define    REG_DMAC_BASE                    0x20120000
#define    REG_SYSC_AWO_BASE                0x20201000
#define    REG_BROM_BASE                    0x00000000
#define    REG_PWM_BASE                     0x20147000
#define    REG_TIMER_BASE                   0x20130000
#define    REG_QSPI_BASE                    0x20300000
#define    REG_RTC_BASE                     0x20200000
#define    REG_SYSC_PER_BASE                0x20149000
#define    REG_IIC0_BASE                    0x20145000
#define    REG_IIC1_BASE                    0x20146000
#define    REG_SPIS_BASE                    0x20142000
#define    REG_WDT_BASE                     0x20131000
#define    REG_BLE_MDM_BASE                 0x20110000
#define    REG_SYSC_BLE_BASE                0x20111000
#define    REG_ADC_CTRL_BASE                0x20136000
#define    REG_UART0_BASE                   0x20143000
#define    REG_UART1_BASE                   0x20144000
#define    REG_ECC_BASE                     0x20134000
#define    REG_SPIM_0_BASE                  0x20140000
#define    REG_SPIM_1_BASE                  0x20141000
#define    REG_SYSC_CPU_BASE                0x20132000
#define    REG_GPIO_BASE                    0x20148000
#define    REG_BLE_MAC_BASE                 0x20100000
#define    REG_CACHE_MEM_BASE               0x00130000
#define    REG_BUS_PTCH_BASE                0x20133000
#define    REG_CACHE_BASE                   0x20121000

//#define    APOLLO_00_VTOR_BASE              0x00100000
#define    APOLLO_00_VTOR_BASE              0x00803000
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
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_ASSERT */

#define PARAM_UNNULL(arg)      ( (arg) != NULL )
/* exported functions --------------------------------------------------------*/



/* exported include ----------------------------------------------------------*/
#if defined(__CC_ARM)
#pragma anon_unions
#endif
#include "reg_sysc_awo.h"
#include "reg_sysc_cpu.h"
#include "reg_sysc_per.h"

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_BLE_REG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

