/**
 ****************************************************************************************
 *
 * @file rvds/compiler.h
 *
 * @brief Definitions of compiler specific directives.
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef _COMPILER_H_
#define _COMPILER_H_

#ifndef __ARMCC_VERSION
#error "File only included with RVDS!"
#endif // __ARMCC_VERSION
#include "apollo_00_ble_reg.h"
#undef __INLINE
#define __INLINE __STATIC_INLINE
/// define the IRQ handler attribute for this compiler
#define __IRQ 

/// define the BLE IRQ handler attribute for this compiler
#define __BTIRQ

/// define the BLE IRQ handler attribute for this compiler
#define __BLEIRQ

/// define size of an empty array (used to declare structure with an array size not defined)
#define __ARRAY_EMPTY

/// Put a variable in a memory maintained during deep sleep
#define __LOWPOWER_SAVED

#define _Static_assert(expr,str) int __static_assert(int static_assert_failed[(expr)?1:-1])

#define SVCALL(number, return_type, signature) return_type __svc(number) signature

#endif // _COMPILER_H_
