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
#ifndef __APOLLO_00_REG_SYSC_CPU_H__
#define __APOLLO_00_REG_SYSC_CPU_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* config --------------------------------------------------------------------*/


/* includes ------------------------------------------------------------------*/
#include "apollo_00_ble_reg.h"

/* exported types ------------------------------------------------------------*/

//clk_div_para
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 : 16; /*15: 0,                No description.*/
        uint32_t          clk_div_timer_para_m1 :  8; /*23:16, divider parameter from clk_16mclk = clk_16m/(clk_div_*_para_m1+1)zero means divide by 2*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } ;
} T_SYSC_CPU_CLK_DIV_PARA;

//clkg0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  6; /* 5: 0,                No description.*/
        uint32_t             clkg_set_timer_div :  1; /* 6: 6,                No description.*/
        uint32_t             clkg_clr_timer_div :  1; /* 7: 7, write 1 to clkg*_clr_* clear the corresponding clock gate control regwrite 1 to clkg*_set_* set the corresponding clock gate control reg*/
        uint32_t                     reserved_0 : 24; /*31: 8,                No description.*/
    } ;
} T_SYSC_CPU_CLKG0;

//clkg1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  4; /* 3: 0,                No description.*/
        uint32_t                   clkg_set_wdt :  1; /* 4: 4,                No description.*/
        uint32_t                   clkg_clr_wdt :  1; /* 5: 5,                No description.*/
        uint32_t                  clkg_set_dmac :  1; /* 6: 6,                No description.*/
        uint32_t                  clkg_clr_dmac :  1; /* 7: 7,                No description.*/
        uint32_t                 clkg_set_cache :  1; /* 8: 8,                No description.*/
        uint32_t                 clkg_clr_cache :  1; /* 9: 9,                No description.*/
        uint32_t                  clkg_set_qspi :  1; /*10:10,                No description.*/
        uint32_t                  clkg_clr_qspi :  1; /*11:11,                No description.*/
        uint32_t                clkg_set_timer0 :  1; /*12:12,                No description.*/
        uint32_t                clkg_clr_timer0 :  1; /*13:13,                No description.*/
        uint32_t                clkg_set_timer1 :  1; /*14:14,                No description.*/
        uint32_t                clkg_clr_timer1 :  1; /*15:15,                No description.*/
        uint32_t              clkg_set_uart2ahb :  1; /*16:16,                No description.*/
        uint32_t              clkg_clr_uart2ahb :  1; /*17:17,                No description.*/
        uint32_t                   clkg_set_ecc :  1; /*18:18,                No description.*/
        uint32_t                   clkg_clr_ecc :  1; /*19:19, write 1 to clkg*_clr_* clear the corresponding clock gate control regwrite 1 to clkg*_set_* set the corresponding clock gate control reg*/
        uint32_t                     reserved_0 : 12; /*31:20,                No description.*/
    } ;
} T_SYSC_CPU_CLKG1;

//srst
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 :  4; /* 3: 0,                No description.*/
        uint32_t                srst_set_dmac_n :  1; /* 4: 4,                No description.*/
        uint32_t                srst_clr_dmac_n :  1; /* 5: 5,                No description.*/
        uint32_t               srst_set_cache_n :  1; /* 6: 6,                No description.*/
        uint32_t               srst_clr_cache_n :  1; /* 7: 7,                No description.*/
        uint32_t                 srst_set_wdt_n :  1; /* 8: 8,                No description.*/
        uint32_t                 srst_clr_wdt_n :  1; /* 9: 9,                No description.*/
        uint32_t               srst_set_timer_n :  1; /*10:10,                No description.*/
        uint32_t               srst_clr_timer_n :  1; /*11:11,                No description.*/
        uint32_t                srst_set_qspi_n :  1; /*12:12,                No description.*/
        uint32_t                srst_clr_qspi_n :  1; /*13:13,                No description.*/
        uint32_t                 srst_set_all_n :  1; /*14:14,                No description.*/
        uint32_t                 srst_clr_all_n :  1; /*15:15,                No description.*/
        uint32_t              srst_set_ble_lp_n :  1; /*16:16,                No description.*/
        uint32_t              srst_clr_ble_lp_n :  1; /*17:17,                No description.*/
        uint32_t                 srst_set_rtc_n :  1; /*18:18,                No description.*/
        uint32_t                 srst_clr_rtc_n :  1; /*19:19,                No description.*/
        uint32_t            srst_set_uart2ahb_n :  1; /*20:20,                No description.*/
        uint32_t            srst_clr_uart2ahb_n :  1; /*21:21,                No description.*/
        uint32_t                 srst_set_ecc_n :  1; /*22:22,                No description.*/
        uint32_t                 srst_clr_ecc_n :  1; /*23:23, write 1 to srst*_clr_* clear the corresponding soft reset control regwrite 1 to srst*_set_* set the corresponding soft reset control reg*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } ;
} T_SYSC_CPU_SRST;

//pin_share_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                        qspi_en :  4; /* 3: 0,                No description.*/
        uint32_t                       spim0_en :  1; /* 4: 4,                No description.*/
        uint32_t                   spim0_cs1_en :  1; /* 5: 5,                No description.*/
        uint32_t                       spim1_en :  1; /* 6: 6,                No description.*/
        uint32_t                   spim1_cs1_en :  1; /* 7: 7,                No description.*/
        uint32_t                        spis_en :  1; /* 8: 8,                No description.*/
        uint32_t                      gpio00_en :  1; /* 9: 9,                No description.*/
        uint32_t                      gpio01_en :  1; /*10:10,                No description.*/
        uint32_t                      gpio14_en :  1; /*11:11,                No description.*/
        uint32_t                      gpio15_en :  1; /*12:12,                No description.*/
        uint32_t                        rfif_en :  1; /*13:13,                No description.*/
        uint32_t                     reserved_1 :  2; /*15:14,                No description.*/
        uint32_t                 ble_mac_dbg_en :  8; /*23:16,                No description.*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } ;
} T_SYSC_CPU_PIN_SHARE_EN;

//func_io_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                   func_io_en_r : 22; /*21: 0,                No description.*/
        uint32_t                     reserved_0 : 10; /*31:22,                No description.*/
    } ;
} T_SYSC_CPU_FUNC_IO_EN;

//func_io_sel0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  func_io00_sel :  4; /* 3: 0,                No description.*/
        uint32_t                  func_io01_sel :  4; /* 7: 4,                No description.*/
        uint32_t                  func_io02_sel :  4; /*11: 8,                No description.*/
        uint32_t                  func_io03_sel :  4; /*15:12,                No description.*/
        uint32_t                  func_io04_sel :  4; /*19:16,                No description.*/
        uint32_t                  func_io05_sel :  4; /*23:20,                No description.*/
        uint32_t                  func_io06_sel :  4; /*27:24,                No description.*/
        uint32_t                  func_io07_sel :  4; /*31:28,                No description.*/
    } ;
} T_SYSC_CPU_FUNC_IO_SEL0;

//func_io_sel1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  func_io08_sel :  4; /* 3: 0,                No description.*/
        uint32_t                  func_io09_sel :  4; /* 7: 4,                No description.*/
        uint32_t                  func_io10_sel :  4; /*11: 8,                No description.*/
        uint32_t                  func_io11_sel :  4; /*15:12,                No description.*/
        uint32_t                  func_io12_sel :  4; /*19:16,                No description.*/
        uint32_t                  func_io13_sel :  4; /*23:20,                No description.*/
        uint32_t                  func_io14_sel :  4; /*27:24,                No description.*/
        uint32_t                  func_io15_sel :  4; /*31:28,                No description.*/
    };
} T_SYSC_CPU_FUNC_IO_SEL1;

//func_io_sel2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  func_io16_sel :  4; /* 3: 0,                No description.*/
        uint32_t                  func_io17_sel :  4; /* 7: 4,                No description.*/
        uint32_t                  func_io18_sel :  4; /*11: 8,                No description.*/
        uint32_t                  func_io19_sel :  4; /*15:12,                No description.*/
        uint32_t                  func_io20_sel :  4; /*19:16,                No description.*/
        uint32_t                  func_io21_sel :  4; /*23:20,                No description.*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } ;
} T_SYSC_CPU_FUNC_IO_SEL2;

//sys_ctrl0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 cache_has_sram :  1; /* 0: 0,                No description.*/
        uint32_t                    adc_has_dma :  1; /* 1: 1,                No description.*/
        uint32_t                     reserved_2 :  6; /* 7: 2,                No description.*/
        uint32_t                      ble_freq0 :  6; /*13: 8,                No description.*/
        uint32_t                     reserved_1 :  2; /*15:14,                No description.*/
        uint32_t                      ble_freq1 :  6; /*21:16,                No description.*/
        uint32_t                     reserved_0 : 10; /*31:22,                No description.*/
    } ;
} T_SYSC_CPU_SYS_CTRL0;

//sft_intr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     sft_intr_r :  1; /* 0: 0,                No description.*/
        uint32_t                     reserved_0 : 31; /*31: 1,                No description.*/
    } ;
} T_SYSC_CPU_SFT_INTR;

//calb32
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                  calb32k_start :  1; /* 0: 0,  32KHz clock calibration start*/
        uint32_t                     reserved_1 : 11; /*11: 1,                No description.*/
        uint32_t                   calb32k_rslt : 18; /*29:12, 32KHz clock calibration result; calb32k_rslt = 64*16MHz/32KHz*/
        uint32_t                     reserved_0 :  2; /*31:30,                No description.*/
    } ;
} T_SYSC_CPU_CALB32;

//pgspy_addr0_l
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t    pgspy_addr0_l_pgspy_addr0_l : 24; /*23: 0, min address of the address spy space0*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } ;
} T_SYSC_CPU_PGSPY_ADDR0_L;

//pgspy_addr0_h
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t    pgspy_addr0_h_pgspy_addr0_h : 24; /*23: 0, max address of the address spy space0*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } ;
} T_SYSC_CPU_PGSPY_ADDR0_H;

//pgspy_addr1_l
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t    pgspy_addr1_l_pgspy_addr1_l : 24; /*23: 0, min address of the address spy space1*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } ;
} T_SYSC_CPU_PGSPY_ADDR1_L;

//pgspy_addr1_h
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t    pgspy_addr1_h_pgspy_addr1_h : 24; /*23: 0, max address of the address spy space1*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } ;
} T_SYSC_CPU_PGSPY_ADDR1_H;

//pgspy_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t              pgspy_en_pgspy_en :  2; /* 1: 0,      page spy interrupt enable*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } ;
} T_SYSC_CPU_PGSPY_EN;

//pgspy_intr_mask
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t pgspy_intr_mask_pgspy_intr_mask :  2; /* 1: 0,        page spy interrupt mask*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } ;
} T_SYSC_CPU_PGSPY_INTR_MASK;

//pgspy_intr_raw
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t  pgspy_intr_raw_pgspy_intr_raw :  2; /* 1: 0,         page spy raw interrupt*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } ;
} T_SYSC_CPU_PGSPY_INTR_RAW;

//pgspy_intr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t          pgspy_intr_pgspy_intr :  2; /* 1: 0,             page spy interrupt*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } ;
} T_SYSC_CPU_PGSPY_INTR;

/** @defgroup func_io_type
  * @{
  */
#define FUNC_IO_TYPE_UART0_TX       0
#define FUNC_IO_TYPE_UART0_RX       1
#define FUNC_IO_TYPE_UART0_CTS      2
#define FUNC_IO_TYPE_UART0_RTS      3
#define FUNC_IO_TYPE_UART1_TX       4
#define FUNC_IO_TYPE_UART1_RX       5
#define FUNC_IO_TYPE_IIC0_SCL       6
#define FUNC_IO_TYPE_IIC0_SDA       7
#define FUNC_IO_TYPE_IIC1_SCL       8
#define FUNC_IO_TYPE_IIC1_SDA       9
#define FUNC_IO_TYPE_PWM0           10
#define FUNC_IO_TYPE_PWM1           11
#define FUNC_IO_TYPE_PWM2           12
#define FUNC_IO_TYPE_PWM3           13
#define FUNC_IO_TYPE_PWM4           14
/**
  * @}
  */
  
typedef struct
{
    volatile                        uint32_t                  reserved_1[2];
    volatile         T_SYSC_CPU_CLK_DIV_PARA                   clk_div_para; /*  0x8,    RW, 0x00000000,                No description.*/
    volatile                        uint32_t                     reserved_2;
    volatile                T_SYSC_CPU_CLKG0                          clkg0; /* 0x10,    RW, 0x000000C0,                No description.*/
    volatile                T_SYSC_CPU_CLKG1                          clkg1; /* 0x14,    RW, 0x000FFFF0,                No description.*/
    volatile                 T_SYSC_CPU_SRST                           srst; /* 0x18,    RW, 0x00F03FF0,                No description.*/
    volatile                        uint32_t                     reserved_3;
    volatile         T_SYSC_CPU_PIN_SHARE_EN                   pin_share_en; /* 0x20,    RW, 0x00000000,                No description.*/
    __IO    uint32_t                        FIO_EN;     /* 0x24,    RW, 0x00000000,                No description.*/
            uint32_t                  reserved_4[2];
    __IO    uint32_t                       FIO_SEL0;    /* 0x30,    RW, 0x00000000,                No description.*/
    __IO    uint32_t                       FIO_SEL1;    /* 0x34,    RW, 0x00000000,                No description.*/
    __IO    uint32_t                       FIO_SEL2;    /* 0x38,    RW, 0x00000000,                No description.*/
    volatile                        uint32_t                     reserved_5;
    volatile            T_SYSC_CPU_SYS_CTRL0                      sys_ctrl0; /* 0x40,    RW, 0x00101000,                No description.*/
    volatile             T_SYSC_CPU_SFT_INTR                       sft_intr; /* 0x44,    RW, 0x00000000,                No description.*/
    volatile                        uint32_t                     reserved_6;
    volatile               T_SYSC_CPU_CALB32                         calb32; /* 0x4c,    RW, 0x00000000,                No description.*/
    volatile        T_SYSC_CPU_PGSPY_ADDR0_L                  pgspy_addr0_l; /* 0x50,    RW, 0x00000000,                No description.*/
    volatile        T_SYSC_CPU_PGSPY_ADDR0_H                  pgspy_addr0_h; /* 0x54,    RW, 0x00000000,                No description.*/
    volatile        T_SYSC_CPU_PGSPY_ADDR1_L                  pgspy_addr1_l; /* 0x58,    RW, 0x00000000,                No description.*/
    volatile        T_SYSC_CPU_PGSPY_ADDR1_H                  pgspy_addr1_h; /* 0x5c,    RW, 0x00000000,                No description.*/
    volatile             T_SYSC_CPU_PGSPY_EN                       pgspy_en; /* 0x60,    RW, 0x00000000,                No description.*/
    volatile      T_SYSC_CPU_PGSPY_INTR_MASK                pgspy_intr_mask; /* 0x64,    RW, 0x00000000,                No description.*/
    volatile       T_SYSC_CPU_PGSPY_INTR_RAW                 pgspy_intr_raw; /* 0x68,    RO, 0x00000000,                No description.*/
    volatile           T_SYSC_CPU_PGSPY_INTR                     pgspy_intr; /* 0x6c,    RO, 0x00000000,                No description.*/
} T_HWP_SYSC_CPU_T;

/* exported variables --------------------------------------------------------*/
#define		SYSC_CPU	((T_HWP_SYSC_CPU_T*)REG_SYSC_CPU_BASE)

/* exported constants --------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_SYSC_PER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

