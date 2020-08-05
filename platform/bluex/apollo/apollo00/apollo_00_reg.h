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
#ifndef __APOLLO_00_REG_H__
#define __APOLLO_00_REG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn {
    /******  Cortex-M# Processor Exceptions Numbers ***************************************************/

    /* ToDo: use this Cortex interrupt numbers if your device is a CORTEX-M0 device                   */
    NonMaskableInt_IRQn           = -14,        /*!<  2 Non Maskable Interrupt                        */
    HardFault_IRQn                = -13,        /*!<  3 Hard Fault Interrupt                          */
    SVCall_IRQn                   = -5,         /*!< 11 SV Call Interrupt                             */
    PendSV_IRQn                   = -2,         /*!< 14 Pend SV Interrupt                             */
    SysTick_IRQn                  = -1,         /*!< 15 System Tick Interrupt                         */

    /******  Device Specific Interrupt Numbers ********************************************************/
    WDT_IRQn                      =   0,
    BLE_LP_IRQn                   =   1,
    BLE_MAC_IRQn                  =   2,
    RTC_IRQn                      =   3,
    EXT_INTR_IRQn                 =   4,
    ECC_IRQn                      =   5,
    DMAC_IRQn                     =   6,
    QSPI_IRQn                     =   7,
    SPIM0_IRQn                    =   8,
    SPIM1_IRQn                    =   9,
    SPIS_IRQn                     =  10,
    UART0_IRQn                    =  11,
    UART1_IRQn                    =  12,
    IIC0_IRQn                     =  13,
    IIC1_IRQn                     =  14,
    GPIO_IRQn                     =  15,
    TIMER_IRQn                    =  16,
    SFT_IRQn                      =  17,
    PGSPY_IRQn                    =  18,

} IRQn_Type;
/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */

#define __CM0PLUS_REV             0x0000        /*!< Core Revision r0p0                               */
#define __VTOR_PRESENT            1             /*!< VTOR present or not                              */
#define __NVIC_PRIO_BITS          2             /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0             /*!< Set to 1 if different SysTick Config is used     */
#define __MPU_PRESENT             1             /*!< MPU present or not                               */
#define __FPU_PRESENT             0             /*!< FPU present or not                               */

#include "core_cm0plus.h"

/* exported types ------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/
#define REG_SRAM_BASE                           0x00100000
#define REG_DMA_BASE                            0x20120000
#define REG_SYSC_AWO_BASE                       0x20201000
#define REG_BROM_BASE                           0x00000000
#define REG_PWM_BASE                            0x20147000
#define REG_TIMER_BASE                          0x20130000
#define REG_QSPI_BASE                           0x20300000
#define REG_RTC_BASE                            0x20200000
#define REG_SYSC_PER_BASE                       0x20149000
#define REG_IIC0_BASE                           0x20145000
#define REG_IIC1_BASE                           0x20146000
#define REG_SPIS_BASE                           0x20142000
#define REG_WDT_BASE                            0x20131000
#define REG_BLE_MDM_BASE                        0x20110000
#define REG_SYSC_BLE_BASE                       0x20111000
#define REG_ADC_BASE                            0x20136000
#define REG_UART0_BASE                          0x20143000
#define REG_UART1_BASE                          0x20144000
#define REG_ECC_BASE                            0x20134000
#define REG_SPIM_0_BASE                         0x20140000
#define REG_SPIM_1_BASE                         0x20141000
#define REG_SYSC_CPU_BASE                       0x20132000
#define REG_GPIO_BASE                           0x20148000
#define REG_BLE_MAC_BASE                        0x20100000
#define REG_CACHE_MEM_BASE                      0x00130000
#define REG_BUS_PTCH_BASE                       0x20133000
#define REG_CACHE_BASE                          0x20121000
#define APOLLO_00_VTOR_BASE                     0x00803000

#define REG_TIMER0_ADDR_OFFSET                  (0X0U)
#define REG_TIMER1_ADDR_OFFSET                  (0X14U)
#define REG_TIMERX_ADDR_OFFSET                  (0XA0U)

#define REG_PWM0_ADDR_OFFSET                    (0X00U)
#define REG_PWM1_ADDR_OFFSET                    (0X10U)
#define REG_PWM2_ADDR_OFFSET                    (0X20U)
#define REG_PWM3_ADDR_OFFSET                    (0X30U)
#define REG_PWM4_ADDR_OFFSET                    (0X40U)

#define REG_DMA_CHANNEL0_ADDR_OFFSET            (0x000U)
#define REG_DMA_CHANNEL1_ADDR_OFFSET            (0x058U)
#define REG_DMA_CHANNEL2_ADDR_OFFSET            (0x0B0U)
#define REG_DMA_CHANNEL3_ADDR_OFFSET            (0x108U)
#define REG_DMA_CHANNEL4_ADDR_OFFSET            (0x160U)
#define REG_DMA_CHANNEL5_ADDR_OFFSET            (0x1B8U)
#define REG_DMAX_ADDR_OFFSET                    (0x2C0U)

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

/* exported include ----------------------------------------------------------*/
#include "apollo_00_reg_sysc_awo.h"
#include "apollo_00_reg_sysc_cpu.h"
#include "apollo_00_reg_sysc_per.h"

#include "apollo_00_reg_gpio.h"
#include "apollo_00_reg_uart.h"
#include "apollo_00_reg_pwm.h"
#include "apollo_00_reg_timer.h"
#include "apollo_00_reg_rtc.h"
#include "apollo_00_reg_iic.h"
#include "apollo_00_reg_adc.h"

#include "apollo_00_reg_wdt.h"
#include "apollo_00_reg_spis.h"
#include "apollo_00_reg_spim.h"
#include "apollo_00_reg_cache.h"
#include "apollo_00_reg_dma.h"

#include "apollo_reg_common.h"


/* exported variables --------------------------------------------------------*/
#define BX_AWO                                          ( ( reg_sysc_awo_t * ) REG_SYSC_AWO_BASE )
#define BX_PER                                          ( ( reg_sysc_per_t * ) REG_SYSC_PER_BASE )
#define BX_CPU                                          ( ( reg_sysc_cpu_t * ) REG_SYSC_CPU_BASE )

#define BX_GPIOA                                        ( ( reg_gpio_t * ) REG_GPIO_BASE )

#define BX_UART0                                        ( ( reg_uart_t * ) REG_UART0_BASE )
#define BX_UART1                                        ( ( reg_uart_t * ) REG_UART1_BASE )

#define BX_PWM0                                         ( ( reg_pwm_t * ) REG_PWM_BASE + REG_PWM0_ADDR_OFFSET )
#define BX_PWM1                                         ( ( reg_pwm_t * ) REG_PWM_BASE + REG_PWM1_ADDR_OFFSET )
#define BX_PWM2                                         ( ( reg_pwm_t * ) REG_PWM_BASE + REG_PWM2_ADDR_OFFSET )
#define BX_PWM3                                         ( ( reg_pwm_t * ) REG_PWM_BASE + REG_PWM3_ADDR_OFFSET )
#define BX_PWM4                                         ( ( reg_pwm_t * ) REG_PWM_BASE + REG_PWM4_ADDR_OFFSET )

#define BX_TIM0                                         ( ( reg_timer_t * ) ( REG_TIMER_BASE + REG_TIMER0_ADDR_OFFSET ) )
#define BX_TIM1                                         ( ( reg_timer_t * ) ( REG_TIMER_BASE + REG_TIMER1_ADDR_OFFSET ) )
#define BX_TIM_ALL                                      ( ( reg_timer_all_t * ) ( REG_TIMER_BASE + REG_TIMERX_ADDR_OFFSET ) )

#define BX_RTC                                          ( ( reg_rtc_t * ) REG_RTC_BASE )

#define BX_ADC                                          ( ( reg_adc_t * ) REG_ADC_BASE )
//SYSC_AWO->RFR7
#define BX_ADC_CFG                                      ( ( adc_cfg_reg_t * ) 0x2020108C )

#define BX_IIC0                                         ( ( reg_iic_t * ) REG_IIC0_BASE )
#define BX_IIC1                                         ( ( reg_iic_t * ) REG_IIC1_BASE )

#define BX_WDT                                          ( ( reg_wdt_t * ) REG_WDT_BASE )
#define BX_CACHE                                        ( ( reg_cache_t * ) REG_CACHE_BASE )

#define BX_SPIS                                         ( ( reg_spis_t * ) REG_SPIS_BASE )
#define BX_SPIM0                                        ( ( reg_spim_t * ) REG_SPIM_0_BASE )
#define BX_SPIM1                                        ( ( reg_spim_t * ) REG_SPIM_1_BASE )

#define BX_DMAC0                                        ( ( reg_dmac_t * ) REG_DMA_BASE + REG_DMA_CHANNEL0_ADDR_OFFSET )
#define BX_DMAC1                                        ( ( reg_dmac_t * ) REG_DMA_BASE + REG_DMA_CHANNEL1_ADDR_OFFSET )
#define BX_DMAC2                                        ( ( reg_dmac_t * ) REG_DMA_BASE + REG_DMA_CHANNEL2_ADDR_OFFSET )
#define BX_DMAC3                                        ( ( reg_dmac_t * ) REG_DMA_BASE + REG_DMA_CHANNEL3_ADDR_OFFSET )
#define BX_DMAC4                                        ( ( reg_dmac_t * ) REG_DMA_BASE + REG_DMA_CHANNEL4_ADDR_OFFSET )
#define BX_DMAC5                                        ( ( reg_dmac_t * ) REG_DMA_BASE + REG_DMA_CHANNEL5_ADDR_OFFSET )
#define BX_DMAX                                         ( ( reg_dmax_t * ) REG_DMA_BASE + REG_DMAX_ADDR_OFFSET )

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

