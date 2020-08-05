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
#ifndef __REG_SYSC_CPU_H__
#define __REG_SYSC_CPU_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_ble_reg.h"

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     reserved_1 : 16; /*15: 0,                No description.*/
        uint32_t          clk_div_timer_para_m1 :  8; /*23:16, divider parameter from clk_16mclk = clk_16m/(clk_div_*_para_m1+1)zero means divide by 2*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } bit_field;
} _T_SYSC_CPU_CLK_DIV_PARA;

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
    } bit_field;
} _T_SYSC_CPU_CLKG0;

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
    } bit_field;
} _T_SYSC_CPU_CLKG1;

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
    } bit_field;
} _T_SYSC_CPU_SRST;

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
    } bit_field;
} _T_SYSC_CPU_PIN_SHARE_EN;

//func_io_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                   func_io_en_r : 22; /*21: 0,                No description.*/
        uint32_t                     reserved_0 : 10; /*31:22,                No description.*/
    } bit_field;
} _T_SYSC_CPU_FUNC_IO_EN;

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
    } bit_field;
} _T_SYSC_CPU_FUNC_IO_SEL0;

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
    } bit_field;
} _T_SYSC_CPU_FUNC_IO_SEL1;

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
    } bit_field;
} _T_SYSC_CPU_FUNC_IO_SEL2;

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
    } bit_field;
} _T_SYSC_CPU_SYS_CTRL0;

//sft_intr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                     sft_intr_r :  1; /* 0: 0,                No description.*/
        uint32_t                     reserved_0 : 31; /*31: 1,                No description.*/
    } bit_field;
} _T_SYSC_CPU_SFT_INTR;

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
    } bit_field;
} _T_SYSC_CPU_CALB32;

//pgspy_addr0_l
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t    pgspy_addr0_l_pgspy_addr0_l : 24; /*23: 0, min address of the address spy space0*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } bit_field;
} _T_SYSC_CPU_PGSPY_ADDR0_L;

//pgspy_addr0_h
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t    pgspy_addr0_h_pgspy_addr0_h : 24; /*23: 0, max address of the address spy space0*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } bit_field;
} _T_SYSC_CPU_PGSPY_ADDR0_H;

//pgspy_addr1_l
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t    pgspy_addr1_l_pgspy_addr1_l : 24; /*23: 0, min address of the address spy space1*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } bit_field;
} _T_SYSC_CPU_PGSPY_ADDR1_L;

//pgspy_addr1_h
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t    pgspy_addr1_h_pgspy_addr1_h : 24; /*23: 0, max address of the address spy space1*/
        uint32_t                     reserved_0 :  8; /*31:24,                No description.*/
    } bit_field;
} _T_SYSC_CPU_PGSPY_ADDR1_H;

//pgspy_en
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t              pgspy_en_pgspy_en :  2; /* 1: 0,      page spy interrupt enable*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } bit_field;
} _T_SYSC_CPU_PGSPY_EN;

//pgspy_intr_mask
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t pgspy_intr_mask_pgspy_intr_mask :  2; /* 1: 0,        page spy interrupt mask*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } bit_field;
} _T_SYSC_CPU_PGSPY_INTR_MASK;

//pgspy_intr_raw
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t  pgspy_intr_raw_pgspy_intr_raw :  2; /* 1: 0,         page spy raw interrupt*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } bit_field;
} _T_SYSC_CPU_PGSPY_INTR_RAW;

//pgspy_intr
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t          pgspy_intr_pgspy_intr :  2; /* 1: 0,             page spy interrupt*/
        uint32_t                     reserved_0 : 30; /*31: 2,                No description.*/
    } bit_field;
} _T_SYSC_CPU_PGSPY_INTR;

//Registers Mapping to the same address

typedef struct
{
    volatile                        uint32_t                  reserved_1[2];
    volatile         _T_SYSC_CPU_CLK_DIV_PARA                   clk_div_para; /*  0x8,    RW, 0x00000000,                No description.*/
    volatile                        uint32_t                     reserved_2;
    volatile                _T_SYSC_CPU_CLKG0                          clkg0; /* 0x10,    RW, 0x000000C0,                No description.*/
    volatile                _T_SYSC_CPU_CLKG1                          clkg1; /* 0x14,    RW, 0x000FFFF0,                No description.*/
    volatile                 _T_SYSC_CPU_SRST                           srst; /* 0x18,    RW, 0x00F03FF0,                No description.*/
    volatile                        uint32_t                     reserved_3;
    volatile         _T_SYSC_CPU_PIN_SHARE_EN                   pin_share_en; /* 0x20,    RW, 0x00000000,                No description.*/
    volatile           _T_SYSC_CPU_FUNC_IO_EN                     func_io_en; /* 0x24,    RW, 0x00000000,                No description.*/
    volatile                        uint32_t                  reserved_4[2];
    volatile         _T_SYSC_CPU_FUNC_IO_SEL0                   func_io_sel0; /* 0x30,    RW, 0x00000000,                No description.*/
    volatile         _T_SYSC_CPU_FUNC_IO_SEL1                   func_io_sel1; /* 0x34,    RW, 0x00000000,                No description.*/
    volatile         _T_SYSC_CPU_FUNC_IO_SEL2                   func_io_sel2; /* 0x38,    RW, 0x00000000,                No description.*/
    volatile                        uint32_t                     reserved_5;
    volatile            _T_SYSC_CPU_SYS_CTRL0                      sys_ctrl0; /* 0x40,    RW, 0x00101000,                No description.*/
    volatile             _T_SYSC_CPU_SFT_INTR                       sft_intr; /* 0x44,    RW, 0x00000000,                No description.*/
    volatile                        uint32_t                     reserved_6;
    volatile               _T_SYSC_CPU_CALB32                         calb32; /* 0x4c,    RW, 0x00000000,                No description.*/
    volatile        _T_SYSC_CPU_PGSPY_ADDR0_L                  pgspy_addr0_l; /* 0x50,    RW, 0x00000000,                No description.*/
    volatile        _T_SYSC_CPU_PGSPY_ADDR0_H                  pgspy_addr0_h; /* 0x54,    RW, 0x00000000,                No description.*/
    volatile        _T_SYSC_CPU_PGSPY_ADDR1_L                  pgspy_addr1_l; /* 0x58,    RW, 0x00000000,                No description.*/
    volatile        _T_SYSC_CPU_PGSPY_ADDR1_H                  pgspy_addr1_h; /* 0x5c,    RW, 0x00000000,                No description.*/
    volatile             _T_SYSC_CPU_PGSPY_EN                       pgspy_en; /* 0x60,    RW, 0x00000000,                No description.*/
    volatile      _T_SYSC_CPU_PGSPY_INTR_MASK                pgspy_intr_mask; /* 0x64,    RW, 0x00000000,                No description.*/
    volatile       _T_SYSC_CPU_PGSPY_INTR_RAW                 pgspy_intr_raw; /* 0x68,    RO, 0x00000000,                No description.*/
    volatile           _T_SYSC_CPU_PGSPY_INTR                     pgspy_intr; /* 0x6c,    RO, 0x00000000,                No description.*/
} _T_HWP_SYSC_CPU_T;

/* exported variables --------------------------------------------------------*/
#define hwp_sysc_cpu ((_T_HWP_SYSC_CPU_T*)REG_SYSC_CPU_BASE)

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_clk_div_para_get(void)
{
    return hwp_sysc_cpu->clk_div_para.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_clk_div_para_set(uint32_t value)
{
    hwp_sysc_cpu->clk_div_para.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_clk_div_para_pack(uint8_t clk_div_timer_para_m1)
{
    hwp_sysc_cpu->clk_div_para.val = (((uint32_t)clk_div_timer_para_m1 << 16));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_clk_div_para_unpack(uint8_t* clk_div_timer_para_m1)
{
    _T_SYSC_CPU_CLK_DIV_PARA localVal = hwp_sysc_cpu->clk_div_para;

    *clk_div_timer_para_m1 = localVal.bit_field.clk_div_timer_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_clk_div_timer_para_m1_getf(void)
{
    return hwp_sysc_cpu->clk_div_para.bit_field.clk_div_timer_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_clk_div_timer_para_m1_setf(uint8_t clk_div_timer_para_m1)
{
    hwp_sysc_cpu->clk_div_para.bit_field.clk_div_timer_para_m1 = clk_div_timer_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_clkg0_get(void)
{
    return hwp_sysc_cpu->clkg0.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_clkg0_set(uint32_t value)
{
    hwp_sysc_cpu->clkg0.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_clkg0_pack(uint8_t clkg_clr_timer_div, uint8_t clkg_set_timer_div)
{
    hwp_sysc_cpu->clkg0.val = (((uint32_t)clkg_clr_timer_div << 7) | ((uint32_t)clkg_set_timer_div << 6));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_clkg1_get(void)
{
    return hwp_sysc_cpu->clkg1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_clkg1_set(uint32_t value)
{
    hwp_sysc_cpu->clkg1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_clkg1_pack(uint8_t clkg_clr_ecc, uint8_t clkg_set_ecc, uint8_t clkg_clr_uart2ahb, uint8_t clkg_set_uart2ahb, uint8_t clkg_clr_timer1, uint8_t clkg_set_timer1, uint8_t clkg_clr_timer0, uint8_t clkg_set_timer0, uint8_t clkg_clr_qspi, uint8_t clkg_set_qspi, uint8_t clkg_clr_cache, uint8_t clkg_set_cache, uint8_t clkg_clr_dmac, uint8_t clkg_set_dmac, uint8_t clkg_clr_wdt, uint8_t clkg_set_wdt)
{
    hwp_sysc_cpu->clkg1.val = (((uint32_t)clkg_clr_ecc << 19) | ((uint32_t)clkg_set_ecc << 18) | ((uint32_t)clkg_clr_uart2ahb << 17) | ((uint32_t)clkg_set_uart2ahb << 16) | ((uint32_t)clkg_clr_timer1 << 15) | ((uint32_t)clkg_set_timer1 << 14) | ((uint32_t)clkg_clr_timer0 << 13) | ((uint32_t)clkg_set_timer0 << 12) | ((uint32_t)clkg_clr_qspi << 11) | ((uint32_t)clkg_set_qspi << 10) | ((uint32_t)clkg_clr_cache << 9) | ((uint32_t)clkg_set_cache << 8) | ((uint32_t)clkg_clr_dmac << 7) | ((uint32_t)clkg_set_dmac << 6) | ((uint32_t)clkg_clr_wdt << 5) | ((uint32_t)clkg_set_wdt << 4));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_srst_get(void)
{
    return hwp_sysc_cpu->srst.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_srst_set(uint32_t value)
{
    hwp_sysc_cpu->srst.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_srst_pack(uint8_t srst_clr_ecc_n, uint8_t srst_set_ecc_n, uint8_t srst_clr_uart2ahb_n, uint8_t srst_set_uart2ahb_n, uint8_t srst_clr_qspi_n, uint8_t srst_set_qspi_n, uint8_t srst_clr_timer_n, uint8_t srst_set_timer_n, uint8_t srst_clr_wdt_n, uint8_t srst_set_wdt_n, uint8_t srst_clr_cache_n, uint8_t srst_set_cache_n, uint8_t srst_clr_dmac_n, uint8_t srst_set_dmac_n)
{
    hwp_sysc_cpu->srst.val = (((uint32_t)srst_clr_ecc_n << 23) | ((uint32_t)srst_set_ecc_n << 22) | ((uint32_t)srst_clr_uart2ahb_n << 21) | ((uint32_t)srst_set_uart2ahb_n << 20) | ((uint32_t)srst_clr_qspi_n << 13) | ((uint32_t)srst_set_qspi_n << 12) | ((uint32_t)srst_clr_timer_n << 11) | ((uint32_t)srst_set_timer_n << 10) | ((uint32_t)srst_clr_wdt_n << 9) | ((uint32_t)srst_set_wdt_n << 8) | ((uint32_t)srst_clr_cache_n << 7) | ((uint32_t)srst_set_cache_n << 6) | ((uint32_t)srst_clr_dmac_n << 5) | ((uint32_t)srst_set_dmac_n << 4));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_srst_unpack(uint8_t* srst_clr_rtc_n, uint8_t* srst_set_rtc_n, uint8_t* srst_clr_ble_lp_n, uint8_t* srst_set_ble_lp_n, uint8_t* srst_clr_all_n, uint8_t* srst_set_all_n)
{
    _T_SYSC_CPU_SRST localVal = hwp_sysc_cpu->srst;

    *srst_clr_rtc_n = localVal.bit_field.srst_clr_rtc_n;
    *srst_set_rtc_n = localVal.bit_field.srst_set_rtc_n;
    *srst_clr_ble_lp_n = localVal.bit_field.srst_clr_ble_lp_n;
    *srst_set_ble_lp_n = localVal.bit_field.srst_set_ble_lp_n;
    *srst_clr_all_n = localVal.bit_field.srst_clr_all_n;
    *srst_set_all_n = localVal.bit_field.srst_set_all_n;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_srst_clr_rtc_n_getf(void)
{
    return hwp_sysc_cpu->srst.bit_field.srst_clr_rtc_n;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_srst_set_rtc_n_getf(void)
{
    return hwp_sysc_cpu->srst.bit_field.srst_set_rtc_n;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_srst_clr_ble_lp_n_getf(void)
{
    return hwp_sysc_cpu->srst.bit_field.srst_clr_ble_lp_n;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_srst_set_ble_lp_n_getf(void)
{
    return hwp_sysc_cpu->srst.bit_field.srst_set_ble_lp_n;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_srst_clr_all_n_getf(void)
{
    return hwp_sysc_cpu->srst.bit_field.srst_clr_all_n;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_srst_set_all_n_getf(void)
{
    return hwp_sysc_cpu->srst.bit_field.srst_set_all_n;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pin_share_en_get(void)
{
    return hwp_sysc_cpu->pin_share_en.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pin_share_en_set(uint32_t value)
{
    hwp_sysc_cpu->pin_share_en.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pin_share_en_pack(uint8_t ble_mac_dbg_en, uint8_t rfif_en, uint8_t gpio15_en, uint8_t gpio14_en, uint8_t gpio01_en, uint8_t gpio00_en, uint8_t spis_en, uint8_t spim1_cs1_en, uint8_t spim1_en, uint8_t spim0_cs1_en, uint8_t spim0_en, uint8_t qspi_en)
{
    hwp_sysc_cpu->pin_share_en.val = (((uint32_t)ble_mac_dbg_en << 16) | ((uint32_t)rfif_en << 13) | ((uint32_t)gpio15_en << 12) | ((uint32_t)gpio14_en << 11) | ((uint32_t)gpio01_en << 10) | ((uint32_t)gpio00_en << 9) | ((uint32_t)spis_en << 8) | ((uint32_t)spim1_cs1_en << 7) | ((uint32_t)spim1_en << 6) | ((uint32_t)spim0_cs1_en << 5) | ((uint32_t)spim0_en << 4) | ((uint32_t)qspi_en << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pin_share_en_unpack(uint8_t* ble_mac_dbg_en, uint8_t* rfif_en, uint8_t* gpio15_en, uint8_t* gpio14_en, uint8_t* gpio01_en, uint8_t* gpio00_en, uint8_t* spis_en, uint8_t* spim1_cs1_en, uint8_t* spim1_en, uint8_t* spim0_cs1_en, uint8_t* spim0_en, uint8_t* qspi_en)
{
    _T_SYSC_CPU_PIN_SHARE_EN localVal = hwp_sysc_cpu->pin_share_en;

    *ble_mac_dbg_en = localVal.bit_field.ble_mac_dbg_en;
    *rfif_en = localVal.bit_field.rfif_en;
    *gpio15_en = localVal.bit_field.gpio15_en;
    *gpio14_en = localVal.bit_field.gpio14_en;
    *gpio01_en = localVal.bit_field.gpio01_en;
    *gpio00_en = localVal.bit_field.gpio00_en;
    *spis_en = localVal.bit_field.spis_en;
    *spim1_cs1_en = localVal.bit_field.spim1_cs1_en;
    *spim1_en = localVal.bit_field.spim1_en;
    *spim0_cs1_en = localVal.bit_field.spim0_cs1_en;
    *spim0_en = localVal.bit_field.spim0_en;
    *qspi_en = localVal.bit_field.qspi_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_ble_mac_dbg_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.ble_mac_dbg_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_ble_mac_dbg_en_setf(uint8_t ble_mac_dbg_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.ble_mac_dbg_en = ble_mac_dbg_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_rfif_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.rfif_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_rfif_en_setf(uint8_t rfif_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.rfif_en = rfif_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_gpio15_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.gpio15_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_gpio15_en_setf(uint8_t gpio15_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.gpio15_en = gpio15_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_gpio14_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.gpio14_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_gpio14_en_setf(uint8_t gpio14_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.gpio14_en = gpio14_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_gpio01_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.gpio01_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_gpio01_en_setf(uint8_t gpio01_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.gpio01_en = gpio01_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_gpio00_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.gpio00_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_gpio00_en_setf(uint8_t gpio00_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.gpio00_en = gpio00_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_spis_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spis_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_spis_en_setf(uint8_t spis_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spis_en = spis_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_spim1_cs1_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spim1_cs1_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_spim1_cs1_en_setf(uint8_t spim1_cs1_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spim1_cs1_en = spim1_cs1_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_spim1_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spim1_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_spim1_en_setf(uint8_t spim1_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spim1_en = spim1_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_spim0_cs1_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spim0_cs1_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_spim0_cs1_en_setf(uint8_t spim0_cs1_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spim0_cs1_en = spim0_cs1_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_spim0_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.spim0_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_spim0_en_setf(uint8_t spim0_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.spim0_en = spim0_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_qspi_en_getf(void)
{
    return hwp_sysc_cpu->pin_share_en.bit_field.qspi_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_qspi_en_setf(uint8_t qspi_en)
{
    hwp_sysc_cpu->pin_share_en.bit_field.qspi_en = qspi_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_func_io_en_get(void)
{
    return hwp_sysc_cpu->func_io_en.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_en_set(uint32_t value)
{
    hwp_sysc_cpu->func_io_en.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_en_pack(uint32_t func_io_en_r)
{
    hwp_sysc_cpu->func_io_en.val = (((uint32_t)func_io_en_r << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_en_unpack(uint32_t* func_io_en_r)
{
    _T_SYSC_CPU_FUNC_IO_EN localVal = hwp_sysc_cpu->func_io_en;

    *func_io_en_r = localVal.bit_field.func_io_en_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_func_io_en_r_getf(void)
{
    return hwp_sysc_cpu->func_io_en.bit_field.func_io_en_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_en_r_setf(uint32_t func_io_en_r)
{
    hwp_sysc_cpu->func_io_en.bit_field.func_io_en_r = func_io_en_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_func_io_sel0_get(void)
{
    return hwp_sysc_cpu->func_io_sel0.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_sel0_set(uint32_t value)
{
    hwp_sysc_cpu->func_io_sel0.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_sel0_pack(uint8_t func_io07_sel, uint8_t func_io06_sel, uint8_t func_io05_sel, uint8_t func_io04_sel, uint8_t func_io03_sel, uint8_t func_io02_sel, uint8_t func_io01_sel, uint8_t func_io00_sel)
{
    hwp_sysc_cpu->func_io_sel0.val = (((uint32_t)func_io07_sel << 28) | ((uint32_t)func_io06_sel << 24) | ((uint32_t)func_io05_sel << 20) | ((uint32_t)func_io04_sel << 16) | ((uint32_t)func_io03_sel << 12) | ((uint32_t)func_io02_sel << 8) | ((uint32_t)func_io01_sel << 4) | ((uint32_t)func_io00_sel << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_sel0_unpack(uint8_t* func_io07_sel, uint8_t* func_io06_sel, uint8_t* func_io05_sel, uint8_t* func_io04_sel, uint8_t* func_io03_sel, uint8_t* func_io02_sel, uint8_t* func_io01_sel, uint8_t* func_io00_sel)
{
    _T_SYSC_CPU_FUNC_IO_SEL0 localVal = hwp_sysc_cpu->func_io_sel0;

    *func_io07_sel = localVal.bit_field.func_io07_sel;
    *func_io06_sel = localVal.bit_field.func_io06_sel;
    *func_io05_sel = localVal.bit_field.func_io05_sel;
    *func_io04_sel = localVal.bit_field.func_io04_sel;
    *func_io03_sel = localVal.bit_field.func_io03_sel;
    *func_io02_sel = localVal.bit_field.func_io02_sel;
    *func_io01_sel = localVal.bit_field.func_io01_sel;
    *func_io00_sel = localVal.bit_field.func_io00_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io07_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io07_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io07_sel_setf(uint8_t func_io07_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io07_sel = func_io07_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io06_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io06_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io06_sel_setf(uint8_t func_io06_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io06_sel = func_io06_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io05_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io05_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io05_sel_setf(uint8_t func_io05_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io05_sel = func_io05_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io04_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io04_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io04_sel_setf(uint8_t func_io04_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io04_sel = func_io04_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io03_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io03_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io03_sel_setf(uint8_t func_io03_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io03_sel = func_io03_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io02_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io02_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io02_sel_setf(uint8_t func_io02_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io02_sel = func_io02_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io01_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io01_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io01_sel_setf(uint8_t func_io01_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io01_sel = func_io01_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io00_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel0.bit_field.func_io00_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io00_sel_setf(uint8_t func_io00_sel)
{
    hwp_sysc_cpu->func_io_sel0.bit_field.func_io00_sel = func_io00_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_func_io_sel1_get(void)
{
    return hwp_sysc_cpu->func_io_sel1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_sel1_set(uint32_t value)
{
    hwp_sysc_cpu->func_io_sel1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_sel1_pack(uint8_t func_io15_sel, uint8_t func_io14_sel, uint8_t func_io13_sel, uint8_t func_io12_sel, uint8_t func_io11_sel, uint8_t func_io10_sel, uint8_t func_io09_sel, uint8_t func_io08_sel)
{
    hwp_sysc_cpu->func_io_sel1.val = (((uint32_t)func_io15_sel << 28) | ((uint32_t)func_io14_sel << 24) | ((uint32_t)func_io13_sel << 20) | ((uint32_t)func_io12_sel << 16) | ((uint32_t)func_io11_sel << 12) | ((uint32_t)func_io10_sel << 8) | ((uint32_t)func_io09_sel << 4) | ((uint32_t)func_io08_sel << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_sel1_unpack(uint8_t* func_io15_sel, uint8_t* func_io14_sel, uint8_t* func_io13_sel, uint8_t* func_io12_sel, uint8_t* func_io11_sel, uint8_t* func_io10_sel, uint8_t* func_io09_sel, uint8_t* func_io08_sel)
{
    _T_SYSC_CPU_FUNC_IO_SEL1 localVal = hwp_sysc_cpu->func_io_sel1;

    *func_io15_sel = localVal.bit_field.func_io15_sel;
    *func_io14_sel = localVal.bit_field.func_io14_sel;
    *func_io13_sel = localVal.bit_field.func_io13_sel;
    *func_io12_sel = localVal.bit_field.func_io12_sel;
    *func_io11_sel = localVal.bit_field.func_io11_sel;
    *func_io10_sel = localVal.bit_field.func_io10_sel;
    *func_io09_sel = localVal.bit_field.func_io09_sel;
    *func_io08_sel = localVal.bit_field.func_io08_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io15_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io15_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io15_sel_setf(uint8_t func_io15_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io15_sel = func_io15_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io14_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io14_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io14_sel_setf(uint8_t func_io14_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io14_sel = func_io14_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io13_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io13_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io13_sel_setf(uint8_t func_io13_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io13_sel = func_io13_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io12_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io12_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io12_sel_setf(uint8_t func_io12_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io12_sel = func_io12_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io11_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io11_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io11_sel_setf(uint8_t func_io11_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io11_sel = func_io11_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io10_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io10_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io10_sel_setf(uint8_t func_io10_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io10_sel = func_io10_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io09_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io09_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io09_sel_setf(uint8_t func_io09_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io09_sel = func_io09_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io08_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel1.bit_field.func_io08_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io08_sel_setf(uint8_t func_io08_sel)
{
    hwp_sysc_cpu->func_io_sel1.bit_field.func_io08_sel = func_io08_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_func_io_sel2_get(void)
{
    return hwp_sysc_cpu->func_io_sel2.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_sel2_set(uint32_t value)
{
    hwp_sysc_cpu->func_io_sel2.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_sel2_pack(uint8_t func_io21_sel, uint8_t func_io20_sel, uint8_t func_io19_sel, uint8_t func_io18_sel, uint8_t func_io17_sel, uint8_t func_io16_sel)
{
    hwp_sysc_cpu->func_io_sel2.val = (((uint32_t)func_io21_sel << 20) | ((uint32_t)func_io20_sel << 16) | ((uint32_t)func_io19_sel << 12) | ((uint32_t)func_io18_sel << 8) | ((uint32_t)func_io17_sel << 4) | ((uint32_t)func_io16_sel << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io_sel2_unpack(uint8_t* func_io21_sel, uint8_t* func_io20_sel, uint8_t* func_io19_sel, uint8_t* func_io18_sel, uint8_t* func_io17_sel, uint8_t* func_io16_sel)
{
    _T_SYSC_CPU_FUNC_IO_SEL2 localVal = hwp_sysc_cpu->func_io_sel2;

    *func_io21_sel = localVal.bit_field.func_io21_sel;
    *func_io20_sel = localVal.bit_field.func_io20_sel;
    *func_io19_sel = localVal.bit_field.func_io19_sel;
    *func_io18_sel = localVal.bit_field.func_io18_sel;
    *func_io17_sel = localVal.bit_field.func_io17_sel;
    *func_io16_sel = localVal.bit_field.func_io16_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io21_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io21_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io21_sel_setf(uint8_t func_io21_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io21_sel = func_io21_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io20_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io20_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io20_sel_setf(uint8_t func_io20_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io20_sel = func_io20_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io19_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io19_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io19_sel_setf(uint8_t func_io19_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io19_sel = func_io19_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io18_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io18_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io18_sel_setf(uint8_t func_io18_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io18_sel = func_io18_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io17_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io17_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io17_sel_setf(uint8_t func_io17_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io17_sel = func_io17_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_func_io16_sel_getf(void)
{
    return hwp_sysc_cpu->func_io_sel2.bit_field.func_io16_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_func_io16_sel_setf(uint8_t func_io16_sel)
{
    hwp_sysc_cpu->func_io_sel2.bit_field.func_io16_sel = func_io16_sel;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_sys_ctrl0_get(void)
{
    return hwp_sysc_cpu->sys_ctrl0.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_sys_ctrl0_set(uint32_t value)
{
    hwp_sysc_cpu->sys_ctrl0.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_sys_ctrl0_pack(uint8_t ble_freq1, uint8_t ble_freq0, uint8_t adc_has_dma, uint8_t cache_has_sram)
{
    hwp_sysc_cpu->sys_ctrl0.val = (((uint32_t)ble_freq1 << 16) | ((uint32_t)ble_freq0 << 8) | ((uint32_t)adc_has_dma << 1) | ((uint32_t)cache_has_sram << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_sys_ctrl0_unpack(uint8_t* ble_freq1, uint8_t* ble_freq0, uint8_t* adc_has_dma, uint8_t* cache_has_sram)
{
    _T_SYSC_CPU_SYS_CTRL0 localVal = hwp_sysc_cpu->sys_ctrl0;

    *ble_freq1 = localVal.bit_field.ble_freq1;
    *ble_freq0 = localVal.bit_field.ble_freq0;
    *adc_has_dma = localVal.bit_field.adc_has_dma;
    *cache_has_sram = localVal.bit_field.cache_has_sram;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_ble_freq1_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.ble_freq1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_ble_freq1_setf(uint8_t ble_freq1)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.ble_freq1 = ble_freq1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_ble_freq0_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.ble_freq0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_ble_freq0_setf(uint8_t ble_freq0)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.ble_freq0 = ble_freq0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_adc_has_dma_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.adc_has_dma;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_adc_has_dma_setf(uint8_t adc_has_dma)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.adc_has_dma = adc_has_dma;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_cache_has_sram_getf(void)
{
    return hwp_sysc_cpu->sys_ctrl0.bit_field.cache_has_sram;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_cache_has_sram_setf(uint8_t cache_has_sram)
{
    hwp_sysc_cpu->sys_ctrl0.bit_field.cache_has_sram = cache_has_sram;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_sft_intr_get(void)
{
    return hwp_sysc_cpu->sft_intr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_sft_intr_set(uint32_t value)
{
    hwp_sysc_cpu->sft_intr.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_sft_intr_pack(uint8_t sft_intr_r)
{
    hwp_sysc_cpu->sft_intr.val = (((uint32_t)sft_intr_r << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_sft_intr_unpack(uint8_t* sft_intr_r)
{
    _T_SYSC_CPU_SFT_INTR localVal = hwp_sysc_cpu->sft_intr;

    *sft_intr_r = localVal.bit_field.sft_intr_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_sft_intr_r_getf(void)
{
    return hwp_sysc_cpu->sft_intr.bit_field.sft_intr_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_sft_intr_r_setf(uint8_t sft_intr_r)
{
    hwp_sysc_cpu->sft_intr.bit_field.sft_intr_r = sft_intr_r;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_calb32_get(void)
{
    return hwp_sysc_cpu->calb32.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_calb32_set(uint32_t value)
{
    hwp_sysc_cpu->calb32.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_calb32_pack(uint8_t calb32k_start)
{
    hwp_sysc_cpu->calb32.val = (((uint32_t)calb32k_start << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_calb32_unpack(uint32_t* calb32k_rslt, uint8_t* calb32k_start)
{
    _T_SYSC_CPU_CALB32 localVal = hwp_sysc_cpu->calb32;

    *calb32k_rslt = localVal.bit_field.calb32k_rslt;
    *calb32k_start = localVal.bit_field.calb32k_start;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_calb32k_rslt_getf(void)
{
    return hwp_sysc_cpu->calb32.bit_field.calb32k_rslt;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_calb32k_start_getf(void)
{
    return hwp_sysc_cpu->calb32.bit_field.calb32k_start;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_calb32k_start_setf(uint8_t calb32k_start)
{
    hwp_sysc_cpu->calb32.bit_field.calb32k_start = calb32k_start;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr0_l_get(void)
{
    return hwp_sysc_cpu->pgspy_addr0_l.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr0_l_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_addr0_l.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr0_l_pack(uint32_t pgspy_addr0_l_pgspy_addr0_l)
{
    hwp_sysc_cpu->pgspy_addr0_l.val = (((uint32_t)pgspy_addr0_l_pgspy_addr0_l << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr0_l_unpack(uint32_t* pgspy_addr0_l_pgspy_addr0_l)
{
    _T_SYSC_CPU_PGSPY_ADDR0_L localVal = hwp_sysc_cpu->pgspy_addr0_l;

    *pgspy_addr0_l_pgspy_addr0_l = localVal.bit_field.pgspy_addr0_l_pgspy_addr0_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr0_l_pgspy_addr0_l_getf(void)
{
    return hwp_sysc_cpu->pgspy_addr0_l.bit_field.pgspy_addr0_l_pgspy_addr0_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr0_l_pgspy_addr0_l_setf(uint32_t pgspy_addr0_l_pgspy_addr0_l)
{
    hwp_sysc_cpu->pgspy_addr0_l.bit_field.pgspy_addr0_l_pgspy_addr0_l = pgspy_addr0_l_pgspy_addr0_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr0_h_get(void)
{
    return hwp_sysc_cpu->pgspy_addr0_h.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr0_h_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_addr0_h.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr0_h_pack(uint32_t pgspy_addr0_h_pgspy_addr0_h)
{
    hwp_sysc_cpu->pgspy_addr0_h.val = (((uint32_t)pgspy_addr0_h_pgspy_addr0_h << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr0_h_unpack(uint32_t* pgspy_addr0_h_pgspy_addr0_h)
{
    _T_SYSC_CPU_PGSPY_ADDR0_H localVal = hwp_sysc_cpu->pgspy_addr0_h;

    *pgspy_addr0_h_pgspy_addr0_h = localVal.bit_field.pgspy_addr0_h_pgspy_addr0_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr0_h_pgspy_addr0_h_getf(void)
{
    return hwp_sysc_cpu->pgspy_addr0_h.bit_field.pgspy_addr0_h_pgspy_addr0_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr0_h_pgspy_addr0_h_setf(uint32_t pgspy_addr0_h_pgspy_addr0_h)
{
    hwp_sysc_cpu->pgspy_addr0_h.bit_field.pgspy_addr0_h_pgspy_addr0_h = pgspy_addr0_h_pgspy_addr0_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr1_l_get(void)
{
    return hwp_sysc_cpu->pgspy_addr1_l.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr1_l_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_addr1_l.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr1_l_pack(uint32_t pgspy_addr1_l_pgspy_addr1_l)
{
    hwp_sysc_cpu->pgspy_addr1_l.val = (((uint32_t)pgspy_addr1_l_pgspy_addr1_l << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr1_l_unpack(uint32_t* pgspy_addr1_l_pgspy_addr1_l)
{
    _T_SYSC_CPU_PGSPY_ADDR1_L localVal = hwp_sysc_cpu->pgspy_addr1_l;

    *pgspy_addr1_l_pgspy_addr1_l = localVal.bit_field.pgspy_addr1_l_pgspy_addr1_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr1_l_pgspy_addr1_l_getf(void)
{
    return hwp_sysc_cpu->pgspy_addr1_l.bit_field.pgspy_addr1_l_pgspy_addr1_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr1_l_pgspy_addr1_l_setf(uint32_t pgspy_addr1_l_pgspy_addr1_l)
{
    hwp_sysc_cpu->pgspy_addr1_l.bit_field.pgspy_addr1_l_pgspy_addr1_l = pgspy_addr1_l_pgspy_addr1_l;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr1_h_get(void)
{
    return hwp_sysc_cpu->pgspy_addr1_h.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr1_h_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_addr1_h.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr1_h_pack(uint32_t pgspy_addr1_h_pgspy_addr1_h)
{
    hwp_sysc_cpu->pgspy_addr1_h.val = (((uint32_t)pgspy_addr1_h_pgspy_addr1_h << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr1_h_unpack(uint32_t* pgspy_addr1_h_pgspy_addr1_h)
{
    _T_SYSC_CPU_PGSPY_ADDR1_H localVal = hwp_sysc_cpu->pgspy_addr1_h;

    *pgspy_addr1_h_pgspy_addr1_h = localVal.bit_field.pgspy_addr1_h_pgspy_addr1_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_addr1_h_pgspy_addr1_h_getf(void)
{
    return hwp_sysc_cpu->pgspy_addr1_h.bit_field.pgspy_addr1_h_pgspy_addr1_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_addr1_h_pgspy_addr1_h_setf(uint32_t pgspy_addr1_h_pgspy_addr1_h)
{
    hwp_sysc_cpu->pgspy_addr1_h.bit_field.pgspy_addr1_h_pgspy_addr1_h = pgspy_addr1_h_pgspy_addr1_h;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_en_get(void)
{
    return hwp_sysc_cpu->pgspy_en.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_en_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_en.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_en_pack(uint8_t pgspy_en_pgspy_en)
{
    hwp_sysc_cpu->pgspy_en.val = (((uint32_t)pgspy_en_pgspy_en << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_en_unpack(uint8_t* pgspy_en_pgspy_en)
{
    _T_SYSC_CPU_PGSPY_EN localVal = hwp_sysc_cpu->pgspy_en;

    *pgspy_en_pgspy_en = localVal.bit_field.pgspy_en_pgspy_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_pgspy_en_pgspy_en_getf(void)
{
    return hwp_sysc_cpu->pgspy_en.bit_field.pgspy_en_pgspy_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_en_pgspy_en_setf(uint8_t pgspy_en_pgspy_en)
{
    hwp_sysc_cpu->pgspy_en.bit_field.pgspy_en_pgspy_en = pgspy_en_pgspy_en;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_intr_mask_get(void)
{
    return hwp_sysc_cpu->pgspy_intr_mask.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_intr_mask_set(uint32_t value)
{
    hwp_sysc_cpu->pgspy_intr_mask.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_intr_mask_pack(uint8_t pgspy_intr_mask_pgspy_intr_mask)
{
    hwp_sysc_cpu->pgspy_intr_mask.val = (((uint32_t)pgspy_intr_mask_pgspy_intr_mask << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_intr_mask_unpack(uint8_t* pgspy_intr_mask_pgspy_intr_mask)
{
    _T_SYSC_CPU_PGSPY_INTR_MASK localVal = hwp_sysc_cpu->pgspy_intr_mask;

    *pgspy_intr_mask_pgspy_intr_mask = localVal.bit_field.pgspy_intr_mask_pgspy_intr_mask;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_pgspy_intr_mask_pgspy_intr_mask_getf(void)
{
    return hwp_sysc_cpu->pgspy_intr_mask.bit_field.pgspy_intr_mask_pgspy_intr_mask;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_intr_mask_pgspy_intr_mask_setf(uint8_t pgspy_intr_mask_pgspy_intr_mask)
{
    hwp_sysc_cpu->pgspy_intr_mask.bit_field.pgspy_intr_mask_pgspy_intr_mask = pgspy_intr_mask_pgspy_intr_mask;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_intr_raw_get(void)
{
    return hwp_sysc_cpu->pgspy_intr_raw.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_intr_raw_unpack(uint8_t* pgspy_intr_raw_pgspy_intr_raw)
{
    _T_SYSC_CPU_PGSPY_INTR_RAW localVal = hwp_sysc_cpu->pgspy_intr_raw;

    *pgspy_intr_raw_pgspy_intr_raw = localVal.bit_field.pgspy_intr_raw_pgspy_intr_raw;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_pgspy_intr_raw_pgspy_intr_raw_getf(void)
{
    return hwp_sysc_cpu->pgspy_intr_raw.bit_field.pgspy_intr_raw_pgspy_intr_raw;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_cpu_pgspy_intr_get(void)
{
    return hwp_sysc_cpu->pgspy_intr.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_cpu_pgspy_intr_unpack(uint8_t* pgspy_intr_pgspy_intr)
{
    _T_SYSC_CPU_PGSPY_INTR localVal = hwp_sysc_cpu->pgspy_intr;

    *pgspy_intr_pgspy_intr = localVal.bit_field.pgspy_intr_pgspy_intr;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_cpu_pgspy_intr_pgspy_intr_getf(void)
{
    return hwp_sysc_cpu->pgspy_intr.bit_field.pgspy_intr_pgspy_intr;
}
#ifdef __cplusplus
}
#endif

#endif /* __REG_SYSC_CPU_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
