;/**************************************************************************//**
; * @file     startup_apollo_00.s
; * @brief    CMSIS Cortex-M0+ Core Device Startup File for
; *           Device apollo
; * @version  V3.10
; * @date     23. November 2012
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met: 
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp



; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000100

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts

                DCD     WDT_IRQHandler
                DCD     BLE_LP_IRQHandler
                DCD     BLE_MAC_IRQHandler
                DCD    	RTC_IRQHandler
                DCD     EXT_INTR_IRQHandler
                DCD     ECC_IRQHandler
                DCD     DMAC_IRQHandler
                DCD     QSPI_IRQHandler
                DCD     SPIM0_IRQHandler
                DCD     SPIM1_IRQHandler
                DCD     SPIS_IRQHandler
                DCD     UART0_IRQHandler
                DCD     UART1_IRQHandler
                DCD     IIC0_IRQHandler
                DCD     IIC1_IRQHandler
                DCD     GPIO_IRQHandler
                DCD     TIMER_IRQHandler
                DCD     SFT_IRQHandler
                DCD     PGSPY_IRQHandler               
                
                
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |xip_section|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler                   [WEAK]
                IMPORT  __main
                LDR     R4, =__main
                BX      R4
                ENDP

            AREA    |.text.Default_Handler|, CODE, READONLY

; Dummy Exception Handlers (infinite loops which can be modified)

Default_Handler PROC
                EXPORT  NMI_Handler                     [WEAK]
                EXPORT  HardFault_Handler               [WEAK]
                EXPORT  SVC_Handler                     [WEAK]
                EXPORT  PendSV_Handler                  [WEAK]
                EXPORT  SysTick_Handler                 [WEAK]
                
                EXPORT  WDT_IRQHandler                  [WEAK]
                EXPORT  BLE_LP_IRQHandler               [WEAK]
                EXPORT  BLE_MAC_IRQHandler              [WEAK]
                EXPORT  RTC_IRQHandler                  [WEAK]
                EXPORT  EXT_INTR_IRQHandler             [WEAK]
                EXPORT  ECC_IRQHandler                  [WEAK]
                EXPORT  DMAC_IRQHandler                 [WEAK]
                EXPORT  QSPI_IRQHandler                 [WEAK]
                EXPORT  SPIM0_IRQHandler                [WEAK]
                EXPORT  SPIM1_IRQHandler                [WEAK]
                EXPORT  SPIS_IRQHandler                 [WEAK]
                EXPORT  UART0_IRQHandler                [WEAK]
                EXPORT  UART1_IRQHandler                [WEAK]
                EXPORT  IIC0_IRQHandler                 [WEAK]
                EXPORT  IIC1_IRQHandler                 [WEAK]
                EXPORT  GPIO_IRQHandler                 [WEAK]
                EXPORT  TIMER_IRQHandler                [WEAK]
                EXPORT  SFT_IRQHandler                  [WEAK]
                EXPORT  PGSPY_IRQHandler                [WEAK]
NMI_Handler
HardFault_Handler
SVC_Handler
PendSV_Handler
SysTick_Handler
WDT_IRQHandler
BLE_LP_IRQHandler
BLE_MAC_IRQHandler
RTC_IRQHandler
EXT_INTR_IRQHandler
ECC_IRQHandler
DMAC_IRQHandler
QSPI_IRQHandler
SPIM0_IRQHandler
SPIM1_IRQHandler
SPIS_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
IIC0_IRQHandler
IIC1_IRQHandler
GPIO_IRQHandler
TIMER_IRQHandler
SFT_IRQHandler
PGSPY_IRQHandler
                B       .
                ENDP
                
                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
