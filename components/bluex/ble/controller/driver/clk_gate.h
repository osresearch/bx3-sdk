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
#ifndef __CLK_GATE_H__
#define __CLK_GATE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "reg_sysc_cpu.h"
#include "reg_sysc_per.h"
#include "reg_sysc_awo.h"

#include "co_math.h"
#include "bx_config.h"

/* exported define -----------------------------------------------------------*/

// use clk_gate_cpu_g0
#define BLE_CPU_CLKG_SET_TIMER_DIV                  CO_BIT(6)
#define BLE_CPU_CLKG_CLR_TIMER_DIV                  CO_BIT(7)

// use clk_gate_cpu_g1
#define BLE_CPU_CLKG_SET_WDT                        CO_BIT(4)
#define BLE_CPU_CLKG_CLR_WDT                        CO_BIT(5)
#define BLE_CPU_CLKG_SET_DMAC                       CO_BIT(6)
#define BLE_CPU_CLKG_CLR_DMAC                       CO_BIT(7)
#define BLE_CPU_CLKG_SET_CACHE                      CO_BIT(8)
#define BLE_CPU_CLKG_CLR_CACHE                      CO_BIT(9)
#define BLE_CPU_CLKG_SET_QSPI                       CO_BIT(10)
#define BLE_CPU_CLKG_CLR_QSPI                       CO_BIT(11)
#define BLE_CPU_CLKG_SET_TIMER0                     CO_BIT(12)
#define BLE_CPU_CLKG_CLR_TIMER0                     CO_BIT(13)
#define BLE_CPU_CLKG_SET_TIMER1                     CO_BIT(14)
#define BLE_CPU_CLKG_CLR_TIMER1                     CO_BIT(15)
#define BLE_CPU_CLKG_SET_UART2AHB                   CO_BIT(16)
#define BLE_CPU_CLKG_CLR_UART2AHB                   CO_BIT(17)
#define BLE_CPU_CLKG_SET_ECC                        CO_BIT(18)
#define BLE_CPU_CLKG_CLR_ECC                        CO_BIT(19)

// use clk_gate_per_g0
#define BLE_PER_CLKG1_CLR_SPIS                      CO_BIT(27)
#define BLE_PER_CLKG1_SET_SPIS                      CO_BIT(26)
#define BLE_PER_CLKG0_CLR_SPIS                      CO_BIT(25)
#define BLE_PER_CLKG0_SET_SPIS                      CO_BIT(24)
#define BLE_PER_CLKG1_CLR_SPIM1                     CO_BIT(23)
#define BLE_PER_CLKG1_SET_SPIM1                     CO_BIT(22)
#define BLE_PER_CLKG0_CLR_SPIM1                     CO_BIT(21)
#define BLE_PER_CLKG0_SET_SPIM1                     CO_BIT(20)
#define BLE_PER_CLKG1_CLR_SPIM0                     CO_BIT(19)
#define BLE_PER_CLKG1_SET_SPIM0                     CO_BIT(18)
#define BLE_PER_CLKG0_CLR_SPIM0                     CO_BIT(17)
#define BLE_PER_CLKG0_SET_SPIM0                     CO_BIT(16)
#define BLE_PER_CLKG1_CLR_UART1                     CO_BIT(15)
#define BLE_PER_CLKG1_SET_UART1                     CO_BIT(14)
#define BLE_PER_CLKG0_CLR_UART1                     CO_BIT(13)
#define BLE_PER_CLKG0_SET_UART1                     CO_BIT(12)
#define BLE_PER_CLKG1_CLR_UART0                     CO_BIT(11)
#define BLE_PER_CLKG1_SET_UART0                     CO_BIT(10)
#define BLE_PER_CLKG0_CLR_UART0                     CO_BIT(9)
#define BLE_PER_CLKG0_SET_UART0                     CO_BIT(8)
#define BLE_PER_CLKG1_CLR_IIC1                      CO_BIT(7)
#define BLE_PER_CLKG1_SET_IIC1                      CO_BIT(6)
#define BLE_PER_CLKG0_CLR_IIC1                      CO_BIT(5)
#define BLE_PER_CLKG0_SET_IIC1                      CO_BIT(4)
#define BLE_PER_CLKG1_CLR_IIC0                      CO_BIT(3)
#define BLE_PER_CLKG1_SET_IIC0                      CO_BIT(2)
#define BLE_PER_CLKG0_CLR_IIC0                      CO_BIT(1)
#define BLE_PER_CLKG0_SET_IIC0                      CO_BIT(0)

// use clk_gate_per_g1
#define BLE_PER_CLKG_CLR_GPIO                       CO_BIT(13)
#define BLE_PER_CLKG_SET_GPIO                       CO_BIT(12)
#define BLE_PER_CLKG_CLR_PWM4                       CO_BIT(11)
#define BLE_PER_CLKG_SET_PWM4                       CO_BIT(10)
#define BLE_PER_CLKG_CLR_PWM3                       CO_BIT(9)
#define BLE_PER_CLKG_SET_PWM3                       CO_BIT(8)
#define BLE_PER_CLKG_CLR_PWM2                       CO_BIT(7)
#define BLE_PER_CLKG_SET_PWM2                       CO_BIT(6)
#define BLE_PER_CLKG_CLR_PWM1                       CO_BIT(5)
#define BLE_PER_CLKG_SET_PWM1                       CO_BIT(4)
#define BLE_PER_CLKG_CLR_PWM0                       CO_BIT(3)
#define BLE_PER_CLKG_SET_PWM0                       CO_BIT(2)
#define BLE_PER_CLKG_CLR_PWM_DIV                    CO_BIT(1)
#define BLE_PER_CLKG_SET_PWM_DIV                    CO_BIT(0)

// use clk_gate_awo
#define BLE_AWO_CLKG_CLR_MDM_RX_DIV                 CO_BIT(15)
#define BLE_AWO_CLKG_SET_MDM_RX_DIV                 CO_BIT(14)
#define BLE_AWO_CLKG_CLR_MAC_DIV                    CO_BIT(13)
#define BLE_AWO_CLKG_SET_MAC_DIV                    CO_BIT(12)
#define BLE_AWO_CLKG_CLR_BLE                        CO_BIT(11)
#define BLE_AWO_CLKG_SET_BLE                        CO_BIT(10)
#define BLE_AWO_CLKG_CLR_WIC                        CO_BIT(9)
#define BLE_AWO_CLKG_SET_WIC                        CO_BIT(8)
#define BLE_AWO_CLKG_CLR_HBUS_DIV_16M               CO_BIT(7)
#define BLE_AWO_CLKG_SET_HBUS_DIV_16M               CO_BIT(6)
#define BLE_AWO_CLKG_CLR_HBUS_DIV_PLL               CO_BIT(5)
#define BLE_AWO_CLKG_SET_HBUS_DIV_PLL               CO_BIT(4)
#define BLE_AWO_CLKG_CLR_RTC                        CO_BIT(3)
#define BLE_AWO_CLKG_SET_RTC                        CO_BIT(2)
#define BLE_AWO_CLKG_CLR_BLE_LP                     CO_BIT(1)
#define BLE_AWO_CLKG_SET_BLE_LP                     CO_BIT(0)

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void ble_clk_gate_clr_all_clk( void );
void ble_clk_gate_awo( uint32_t map );
void ble_clk_gate_per_g0( uint32_t map );
void ble_clk_gate_per_g1( uint32_t map );
void ble_clk_gate_cpu_g0( uint32_t map );
void ble_clk_gate_cpu_g1( uint32_t map );

#ifdef __cplusplus
}
#endif

#endif /* __CLK_GATE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
