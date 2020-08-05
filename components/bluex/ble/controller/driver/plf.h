/**
 ****************************************************************************************
 *
 * @file plf.h
 *
 * @brief This file contains the definitions of the macros and functions that are
 * platform dependent.  The implementation of those is implemented in the
 * appropriate platform directory.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */
#ifndef _PLF_H_
#define _PLF_H_

/**
 ****************************************************************************************
 * @defgroup PLF
 * @ingroup DRIVERS
 *
 * @brief Platform register driver
 *
 * @{
 *
 ****************************************************************************************
 */
#include "bx_config.h"
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

#define plf_read_rf_board_id()      0
#define plf_rf_switch()             0 //do not switch rf clk to 52 MHz


#if (MAIN_CLOCK>32000000)
#define USE_PLL                     1
#else
#define USE_PLL                     0
#endif

#define PLL_CLK						96000000
#define MHZ                         1000000
#define SET_CLOCK_MHZ(CLK_SRC)		((CLK_SRC)/MHZ)

#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
#define CRYSTAL_CLK                 32000000
#define AHB_CLK                         MAIN_CLOCK
#define APB_CLK						(AHB_CLK/2)            //APB_CLK should be less than half of AHB_CLK
#define BLE_MAC_CLK0				16000000
#define BLE_MAC_CLK1				24000000
#else
#define CRYSTAL_CLK                 32000000        //10000000
#define AHB_CLK						32000000        //10000000
#define APB_CLK						32000000        //10000000
#define BLE_MAC_CLK0				32000000        //10000000
#define BLE_MAC_CLK1                32000000        //10000000
#endif

extern void bx_delay_asm(unsigned int loop);
/**
 * 1. This macro should not be used until awo registers related to AHB_CLK have been set.
 * 2. Never set "a" as a value which is not an integer.
 * 3. Note that "a" should not result in overflow.
 * **/
#define BX_DELAY_US(a) bx_delay_asm((a)*(AHB_CLK/4000000))

#if (defined(CFG_ON_CHIP)&&(CFG_ON_CHIP==1))
#if ((AHB_CLK / APB_CLK) < 2)
    #error "APB_CLK should be less than half of AHB_CLK"
#endif
#endif

#if (BLE_MAC_CLK0 < 16000000)
	#error "BLE MAC works at least 16M"
#endif


#if ((AHB_CLK % APB_CLK) != 0)
    #error "AHB_CLK % APB_CLK != 0"
#endif


#if ((AHB_CLK % BLE_MAC_CLK0) != 0)
    #error "AHB_CLK % BLE_MAC_CLK0 != 0"
#endif

#if (USE_PLL == 1) && (PLL_CLK == 96000000)
#if ((AHB_CLK % BLE_MAC_CLK1) != 0)
    #error "AHB_CLK % BLE_MAC_CLK1 != 0"
#endif
#endif

#ifdef CFG_LOWEST_CURRENT
#if (AHB_CLK > 32000000)
	#error "AHB_CLK should be configured to 16MHz in lowest current mode"
#endif
#endif

/// @} PLF

#endif // _PLF_H_
