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
#ifndef __REG_SYSC_PER_H__
#define __REG_SYSC_PER_H__

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
        uint32_t                   clk_sel_iic0 :  2; /* 1: 0, clock select:2'b00:  clk_16m2'b01:  divide from clk_16m2'b10:  clk_pll2'b11:  divide from clk_pll*/
        uint32_t                     reserved_3 :  2; /* 3: 2,                No description.*/
        uint32_t                   clk_sel_iic1 :  2; /* 5: 4, clock select:2'b00:  clk_16m2'b01:  divide from clk_16m2'b10:  clk_pll2'b11:  divide from clk_pll*/
        uint32_t                     reserved_2 :  2; /* 7: 6,                No description.*/
        uint32_t                  clk_sel_uart0 :  2; /* 9: 8, clock select:2'b00:  clk_16m2'b01:  divide from clk_16m2'b10:  clk_pll2'b11:  divide from clk_pll*/
        uint32_t                     reserved_1 :  2; /*11:10,                No description.*/
        uint32_t                  clk_sel_uart1 :  2; /*13:12, clock select:2'b00:  clk_16m2'b01:  divide from clk_16m2'b10:  clk_pll2'b11:  divide from clk_pll*/
        uint32_t                     reserved_0 : 18; /*31:14,                No description.*/
    } bit_field;
} _T_SYSC_PER_CLK_SEL;

//clk_div_param0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t           clk_div_iic0_para_m1 :  4; /* 3: 0, divider parameter for clk_pll and clk_16mclk = clk_16m/(clk_div_*_para_m1+1)clk = clk_pll/(clk_div_*_para_m1+1)zero means divide by 2*/
        uint32_t           clk_div_iic1_para_m1 :  4; /* 7: 4, divider parameter for clk_pll and clk_16mclk = clk_16m/(clk_div_*_para_m1+1)clk = clk_pll/(clk_div_*_para_m1+1)zero means divide by 2*/
        uint32_t                     reserved_0 : 16; /*23: 8,                No description.*/
        uint32_t            clk_div_pwm_para_m1 :  8; /*31:24, clk_pwm is divide from clk_16mclk_pwm = clk_16m/(clk_div_pwm_para_m1+1)zero means divide by 2*/
    } bit_field;
} _T_SYSC_PER_CLK_DIV_PARAM0;

//clk_div_param1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t     clk_div_uart0_para_len0_m1 :  6; /* 5: 0,                No description.*/
        uint32_t                     reserved_3 :  2; /* 7: 6,                No description.*/
        uint32_t     clk_div_uart0_para_len1_m1 :  6; /*13: 8,                No description.*/
        uint32_t                     reserved_2 :  2; /*15:14,                No description.*/
        uint32_t     clk_div_uart0_para_num0_m1 :  4; /*19:16,                No description.*/
        uint32_t                     reserved_1 :  4; /*23:20,                No description.*/
        uint32_t     clk_div_uart0_para_num1_m1 :  4; /*27:24, for first (clk_div_uart0_para_num1_m1+1) uart clk cycles clk_uart=clk/(clk_div_uart0_para_len1_m1+1)for following (clk_div_uart0_para_num0_m1+1) uart clk cycles clk_uart=clk/(clk_div_uart0_para_len0_m1+1)clk can be clk_16m or clk_pllclk_div_uart0_len*_m1 is zero means divide by 2*/
        uint32_t                     reserved_0 :  4; /*31:28,                No description.*/
    } bit_field;
} _T_SYSC_PER_CLK_DIV_PARAM1;

//clk_div_param2
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t     clk_div_uart1_para_len0_m1 :  6; /* 5: 0,                No description.*/
        uint32_t                     reserved_3 :  2; /* 7: 6,                No description.*/
        uint32_t     clk_div_uart1_para_len1_m1 :  6; /*13: 8,                No description.*/
        uint32_t                     reserved_2 :  2; /*15:14,                No description.*/
        uint32_t     clk_div_uart1_para_num0_m1 :  4; /*19:16,                No description.*/
        uint32_t                     reserved_1 :  4; /*23:20,                No description.*/
        uint32_t     clk_div_uart1_para_num1_m1 :  4; /*27:24, for first (clk_div_uart1_para_num1_m1+1) uart clk cycles clk_uart=clk/(clk_div_uart1_para_len1_m1+1)for following (clk_div_uart1_para_num0_m1+1) uart clk cycles clk_uart=clk/(clk_div_uart1_para_len0_m1+1)clk can be clk_16m or clk_pllclk_div_uart1_len*_m1 is zero means divide by 2*/
        uint32_t                     reserved_0 :  4; /*31:28,                No description.*/
    } bit_field;
} _T_SYSC_PER_CLK_DIV_PARAM2;

//clkg0
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                 clkg0_set_iic0 :  1; /* 0: 0,                No description.*/
        uint32_t                 clkg0_clr_iic0 :  1; /* 1: 1,                No description.*/
        uint32_t                 clkg1_set_iic0 :  1; /* 2: 2,                No description.*/
        uint32_t                 clkg1_clr_iic0 :  1; /* 3: 3,                No description.*/
        uint32_t                 clkg0_set_iic1 :  1; /* 4: 4,                No description.*/
        uint32_t                 clkg0_clr_iic1 :  1; /* 5: 5,                No description.*/
        uint32_t                 clkg1_set_iic1 :  1; /* 6: 6,                No description.*/
        uint32_t                 clkg1_clr_iic1 :  1; /* 7: 7,                No description.*/
        uint32_t                clkg0_set_uart0 :  1; /* 8: 8,                No description.*/
        uint32_t                clkg0_clr_uart0 :  1; /* 9: 9,                No description.*/
        uint32_t                clkg1_set_uart0 :  1; /*10:10,                No description.*/
        uint32_t                clkg1_clr_uart0 :  1; /*11:11,                No description.*/
        uint32_t                clkg0_set_uart1 :  1; /*12:12,                No description.*/
        uint32_t                clkg0_clr_uart1 :  1; /*13:13,                No description.*/
        uint32_t                clkg1_set_uart1 :  1; /*14:14,                No description.*/
        uint32_t                clkg1_clr_uart1 :  1; /*15:15,                No description.*/
        uint32_t                clkg0_set_spim0 :  1; /*16:16,                No description.*/
        uint32_t                clkg0_clr_spim0 :  1; /*17:17,                No description.*/
        uint32_t                clkg1_set_spim0 :  1; /*18:18,                No description.*/
        uint32_t                clkg1_clr_spim0 :  1; /*19:19,                No description.*/
        uint32_t                clkg0_set_spim1 :  1; /*20:20,                No description.*/
        uint32_t                clkg0_clr_spim1 :  1; /*21:21,                No description.*/
        uint32_t                clkg1_set_spim1 :  1; /*22:22,                No description.*/
        uint32_t                clkg1_clr_spim1 :  1; /*23:23,                No description.*/
        uint32_t                 clkg0_set_spis :  1; /*24:24,                No description.*/
        uint32_t                 clkg0_clr_spis :  1; /*25:25,                No description.*/
        uint32_t                 clkg1_set_spis :  1; /*26:26,                No description.*/
        uint32_t                 clkg1_clr_spis :  1; /*27:27, write 1 to clkg*_clr_* clear the corresponding clock gate control regwrite 1 to clkg*_set_* set the corresponding clock gate control regclkg0* is for the clk divide by clk_16mclkg1_* is for the clk divide by clk_pll*/
        uint32_t                     reserved_0 :  4; /*31:28,                No description.*/
    } bit_field;
} _T_SYSC_PER_CLKG0;

//clkg1
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t               clkg_set_pwm_div :  1; /* 0: 0,                No description.*/
        uint32_t               clkg_clr_pwm_div :  1; /* 1: 1,                No description.*/
        uint32_t                  clkg_set_pwm0 :  1; /* 2: 2,                No description.*/
        uint32_t                  clkg_clr_pwm0 :  1; /* 3: 3,                No description.*/
        uint32_t                  clkg_set_pwm1 :  1; /* 4: 4,                No description.*/
        uint32_t                  clkg_clr_pwm1 :  1; /* 5: 5,                No description.*/
        uint32_t                  clkg_set_pwm2 :  1; /* 6: 6,                No description.*/
        uint32_t                  clkg_clr_pwm2 :  1; /* 7: 7,                No description.*/
        uint32_t                  clkg_set_pwm3 :  1; /* 8: 8,                No description.*/
        uint32_t                  clkg_clr_pwm3 :  1; /* 9: 9,                No description.*/
        uint32_t                  clkg_set_pwm4 :  1; /*10:10,                No description.*/
        uint32_t                  clkg_clr_pwm4 :  1; /*11:11,                No description.*/
        uint32_t                  clkg_set_gpio :  1; /*12:12,                No description.*/
        uint32_t                  clkg_clr_gpio :  1; /*13:13, write 1 to clkg*_clr_* clear the corresponding clock gate control regwrite 1 to clkg*_set_* set the corresponding clock gate control reg*/
        uint32_t                     reserved_0 : 18; /*31:14,                No description.*/
    } bit_field;
} _T_SYSC_PER_CLKG1;

//srst
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                srst_set_iic0_n :  1; /* 0: 0,                No description.*/
        uint32_t                srst_clr_iic0_n :  1; /* 1: 1,                No description.*/
        uint32_t                srst_set_iic1_n :  1; /* 2: 2,                No description.*/
        uint32_t                srst_clr_iic1_n :  1; /* 3: 3,                No description.*/
        uint32_t               srst_set_uart0_n :  1; /* 4: 4,                No description.*/
        uint32_t               srst_clr_uart0_n :  1; /* 5: 5,                No description.*/
        uint32_t               srst_set_uart1_n :  1; /* 6: 6,                No description.*/
        uint32_t               srst_clr_uart1_n :  1; /* 7: 7,                No description.*/
        uint32_t               srst_set_spim0_n :  1; /* 8: 8,                No description.*/
        uint32_t               srst_clr_spim0_n :  1; /* 9: 9,                No description.*/
        uint32_t               srst_set_spim1_n :  1; /*10:10,                No description.*/
        uint32_t               srst_clr_spim1_n :  1; /*11:11,                No description.*/
        uint32_t                srst_set_spis_n :  1; /*12:12,                No description.*/
        uint32_t                srst_clr_spis_n :  1; /*13:13,                No description.*/
        uint32_t                 srst_set_pwm_n :  1; /*14:14,                No description.*/
        uint32_t                 srst_clr_pwm_n :  1; /*15:15,                No description.*/
        uint32_t                srst_set_gpio_n :  1; /*16:16,                No description.*/
        uint32_t                srst_clr_gpio_n :  1; /*17:17, write 1 to srst*_clr_* clear the corresponding soft reset control regwrite 1 to srst*_set_* set the corresponding soft reset control reg*/
        uint32_t                     reserved_0 : 14; /*31:18,                No description.*/
    } bit_field;
} _T_SYSC_PER_SRST;

//uart_issir
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    uart_is_sir :  1; /* 0: 0,        high means uart0 is sir*/
        uint32_t                     reserved_0 : 31; /*31: 1,                No description.*/
    } bit_field;
} _T_SYSC_PER_UART_ISSIR;

//Registers Mapping to the same address

typedef struct
{
    volatile              _T_SYSC_PER_CLK_SEL                        clk_sel; /*  0x0,    RW, 0x00000000,                No description.*/
    volatile       _T_SYSC_PER_CLK_DIV_PARAM0                 clk_div_param0; /*  0x4,    RW, 0x00000000,                No description.*/
    volatile       _T_SYSC_PER_CLK_DIV_PARAM1                 clk_div_param1; /*  0x8,    RW, 0x00000000,                No description.*/
    volatile       _T_SYSC_PER_CLK_DIV_PARAM2                 clk_div_param2; /*  0xc,    RW, 0x00000000,                No description.*/
    volatile                _T_SYSC_PER_CLKG0                          clkg0; /* 0x10,    RW, 0x0FFFFFFF,                No description.*/
    volatile                _T_SYSC_PER_CLKG1                          clkg1; /* 0x14,    RW, 0x00003FFF,                No description.*/
    volatile                 _T_SYSC_PER_SRST                           srst; /* 0x18,    RW, 0x0003FFFF,                No description.*/
    volatile           _T_SYSC_PER_UART_ISSIR                     uart_issir; /* 0x1c,    RW, 0x00000000,                No description.*/
} _T_HWP_SYSC_PER_T;

/* exported variables --------------------------------------------------------*/
#define hwp_sysc_per ((_T_HWP_SYSC_PER_T*)REG_SYSC_PER_BASE)

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_per_clk_sel_get(void)
{
    return hwp_sysc_per->clk_sel.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_sel_set(uint32_t value)
{
    hwp_sysc_per->clk_sel.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_sel_pack(uint8_t clk_sel_uart1, uint8_t clk_sel_uart0, uint8_t clk_sel_iic1, uint8_t clk_sel_iic0)
{
    hwp_sysc_per->clk_sel.val = (((uint32_t)clk_sel_uart1 << 12) | ((uint32_t)clk_sel_uart0 << 8) | ((uint32_t)clk_sel_iic1 << 4) | ((uint32_t)clk_sel_iic0 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_sel_unpack(uint8_t* clk_sel_uart1, uint8_t* clk_sel_uart0, uint8_t* clk_sel_iic1, uint8_t* clk_sel_iic0)
{
    _T_SYSC_PER_CLK_SEL localVal = hwp_sysc_per->clk_sel;

    *clk_sel_uart1 = localVal.bit_field.clk_sel_uart1;
    *clk_sel_uart0 = localVal.bit_field.clk_sel_uart0;
    *clk_sel_iic1 = localVal.bit_field.clk_sel_iic1;
    *clk_sel_iic0 = localVal.bit_field.clk_sel_iic0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_sel_uart1_getf(void)
{
    return hwp_sysc_per->clk_sel.bit_field.clk_sel_uart1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_sel_uart1_setf(uint8_t clk_sel_uart1)
{
    hwp_sysc_per->clk_sel.bit_field.clk_sel_uart1 = clk_sel_uart1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_sel_uart0_getf(void)
{
    return hwp_sysc_per->clk_sel.bit_field.clk_sel_uart0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_sel_uart0_setf(uint8_t clk_sel_uart0)
{
    hwp_sysc_per->clk_sel.bit_field.clk_sel_uart0 = clk_sel_uart0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_sel_iic1_getf(void)
{
    return hwp_sysc_per->clk_sel.bit_field.clk_sel_iic1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_sel_iic1_setf(uint8_t clk_sel_iic1)
{
    hwp_sysc_per->clk_sel.bit_field.clk_sel_iic1 = clk_sel_iic1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_sel_iic0_getf(void)
{
    return hwp_sysc_per->clk_sel.bit_field.clk_sel_iic0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_sel_iic0_setf(uint8_t clk_sel_iic0)
{
    hwp_sysc_per->clk_sel.bit_field.clk_sel_iic0 = clk_sel_iic0;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_per_clk_div_param0_get(void)
{
    return hwp_sysc_per->clk_div_param0.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_param0_set(uint32_t value)
{
    hwp_sysc_per->clk_div_param0.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_param0_pack(uint8_t clk_div_pwm_para_m1, uint8_t clk_div_iic1_para_m1, uint8_t clk_div_iic0_para_m1)
{
    hwp_sysc_per->clk_div_param0.val = (((uint32_t)clk_div_pwm_para_m1 << 24) | ((uint32_t)clk_div_iic1_para_m1 << 4) | ((uint32_t)clk_div_iic0_para_m1 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_param0_unpack(uint8_t* clk_div_pwm_para_m1, uint8_t* clk_div_iic1_para_m1, uint8_t* clk_div_iic0_para_m1)
{
    _T_SYSC_PER_CLK_DIV_PARAM0 localVal = hwp_sysc_per->clk_div_param0;

    *clk_div_pwm_para_m1 = localVal.bit_field.clk_div_pwm_para_m1;
    *clk_div_iic1_para_m1 = localVal.bit_field.clk_div_iic1_para_m1;
    *clk_div_iic0_para_m1 = localVal.bit_field.clk_div_iic0_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_pwm_para_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param0.bit_field.clk_div_pwm_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_pwm_para_m1_setf(uint8_t clk_div_pwm_para_m1)
{
    hwp_sysc_per->clk_div_param0.bit_field.clk_div_pwm_para_m1 = clk_div_pwm_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_iic1_para_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param0.bit_field.clk_div_iic1_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_iic1_para_m1_setf(uint8_t clk_div_iic1_para_m1)
{
    hwp_sysc_per->clk_div_param0.bit_field.clk_div_iic1_para_m1 = clk_div_iic1_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_iic0_para_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param0.bit_field.clk_div_iic0_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_iic0_para_m1_setf(uint8_t clk_div_iic0_para_m1)
{
    hwp_sysc_per->clk_div_param0.bit_field.clk_div_iic0_para_m1 = clk_div_iic0_para_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_per_clk_div_param1_get(void)
{
    return hwp_sysc_per->clk_div_param1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_param1_set(uint32_t value)
{
    hwp_sysc_per->clk_div_param1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_param1_pack(uint8_t clk_div_uart0_para_num1_m1, uint8_t clk_div_uart0_para_num0_m1, uint8_t clk_div_uart0_para_len1_m1, uint8_t clk_div_uart0_para_len0_m1)
{
    hwp_sysc_per->clk_div_param1.val = (((uint32_t)clk_div_uart0_para_num1_m1 << 24) | ((uint32_t)clk_div_uart0_para_num0_m1 << 16) | ((uint32_t)clk_div_uart0_para_len1_m1 << 8) | ((uint32_t)clk_div_uart0_para_len0_m1 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_param1_unpack(uint8_t* clk_div_uart0_para_num1_m1, uint8_t* clk_div_uart0_para_num0_m1, uint8_t* clk_div_uart0_para_len1_m1, uint8_t* clk_div_uart0_para_len0_m1)
{
    _T_SYSC_PER_CLK_DIV_PARAM1 localVal = hwp_sysc_per->clk_div_param1;

    *clk_div_uart0_para_num1_m1 = localVal.bit_field.clk_div_uart0_para_num1_m1;
    *clk_div_uart0_para_num0_m1 = localVal.bit_field.clk_div_uart0_para_num0_m1;
    *clk_div_uart0_para_len1_m1 = localVal.bit_field.clk_div_uart0_para_len1_m1;
    *clk_div_uart0_para_len0_m1 = localVal.bit_field.clk_div_uart0_para_len0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_uart0_para_num1_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_num1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_uart0_para_num1_m1_setf(uint8_t clk_div_uart0_para_num1_m1)
{
    hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_num1_m1 = clk_div_uart0_para_num1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_uart0_para_num0_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_num0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_uart0_para_num0_m1_setf(uint8_t clk_div_uart0_para_num0_m1)
{
    hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_num0_m1 = clk_div_uart0_para_num0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_uart0_para_len1_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_len1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_uart0_para_len1_m1_setf(uint8_t clk_div_uart0_para_len1_m1)
{
    hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_len1_m1 = clk_div_uart0_para_len1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_uart0_para_len0_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_len0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_uart0_para_len0_m1_setf(uint8_t clk_div_uart0_para_len0_m1)
{
    hwp_sysc_per->clk_div_param1.bit_field.clk_div_uart0_para_len0_m1 = clk_div_uart0_para_len0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_per_clk_div_param2_get(void)
{
    return hwp_sysc_per->clk_div_param2.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_param2_set(uint32_t value)
{
    hwp_sysc_per->clk_div_param2.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_param2_pack(uint8_t clk_div_uart1_para_num1_m1, uint8_t clk_div_uart1_para_num0_m1, uint8_t clk_div_uart1_para_len1_m1, uint8_t clk_div_uart1_para_len0_m1)
{
    hwp_sysc_per->clk_div_param2.val = (((uint32_t)clk_div_uart1_para_num1_m1 << 24) | ((uint32_t)clk_div_uart1_para_num0_m1 << 16) | ((uint32_t)clk_div_uart1_para_len1_m1 << 8) | ((uint32_t)clk_div_uart1_para_len0_m1 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_param2_unpack(uint8_t* clk_div_uart1_para_num1_m1, uint8_t* clk_div_uart1_para_num0_m1, uint8_t* clk_div_uart1_para_len1_m1, uint8_t* clk_div_uart1_para_len0_m1)
{
    _T_SYSC_PER_CLK_DIV_PARAM2 localVal = hwp_sysc_per->clk_div_param2;

    *clk_div_uart1_para_num1_m1 = localVal.bit_field.clk_div_uart1_para_num1_m1;
    *clk_div_uart1_para_num0_m1 = localVal.bit_field.clk_div_uart1_para_num0_m1;
    *clk_div_uart1_para_len1_m1 = localVal.bit_field.clk_div_uart1_para_len1_m1;
    *clk_div_uart1_para_len0_m1 = localVal.bit_field.clk_div_uart1_para_len0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_uart1_para_num1_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_num1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_uart1_para_num1_m1_setf(uint8_t clk_div_uart1_para_num1_m1)
{
    hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_num1_m1 = clk_div_uart1_para_num1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_uart1_para_num0_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_num0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_uart1_para_num0_m1_setf(uint8_t clk_div_uart1_para_num0_m1)
{
    hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_num0_m1 = clk_div_uart1_para_num0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_uart1_para_len1_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_len1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_uart1_para_len1_m1_setf(uint8_t clk_div_uart1_para_len1_m1)
{
    hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_len1_m1 = clk_div_uart1_para_len1_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_clk_div_uart1_para_len0_m1_getf(void)
{
    return hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_len0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clk_div_uart1_para_len0_m1_setf(uint8_t clk_div_uart1_para_len0_m1)
{
    hwp_sysc_per->clk_div_param2.bit_field.clk_div_uart1_para_len0_m1 = clk_div_uart1_para_len0_m1;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_per_clkg0_get(void)
{
    return hwp_sysc_per->clkg0.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clkg0_set(uint32_t value)
{
    hwp_sysc_per->clkg0.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clkg0_pack(uint8_t clkg1_clr_spis, uint8_t clkg1_set_spis, uint8_t clkg0_clr_spis, uint8_t clkg0_set_spis, uint8_t clkg1_clr_spim1, uint8_t clkg1_set_spim1, uint8_t clkg0_clr_spim1, uint8_t clkg0_set_spim1, uint8_t clkg1_clr_spim0, uint8_t clkg1_set_spim0, uint8_t clkg0_clr_spim0, uint8_t clkg0_set_spim0, uint8_t clkg1_clr_uart1, uint8_t clkg1_set_uart1, uint8_t clkg0_clr_uart1, uint8_t clkg0_set_uart1, uint8_t clkg1_clr_uart0, uint8_t clkg1_set_uart0, uint8_t clkg0_clr_uart0, uint8_t clkg0_set_uart0, uint8_t clkg1_clr_iic1, uint8_t clkg1_set_iic1, uint8_t clkg0_clr_iic1, uint8_t clkg0_set_iic1, uint8_t clkg1_clr_iic0, uint8_t clkg1_set_iic0, uint8_t clkg0_clr_iic0, uint8_t clkg0_set_iic0)
{
    hwp_sysc_per->clkg0.val = (((uint32_t)clkg1_clr_spis << 27) | ((uint32_t)clkg1_set_spis << 26) | ((uint32_t)clkg0_clr_spis << 25) | ((uint32_t)clkg0_set_spis << 24) | ((uint32_t)clkg1_clr_spim1 << 23) | ((uint32_t)clkg1_set_spim1 << 22) | ((uint32_t)clkg0_clr_spim1 << 21) | ((uint32_t)clkg0_set_spim1 << 20) | ((uint32_t)clkg1_clr_spim0 << 19) | ((uint32_t)clkg1_set_spim0 << 18) | ((uint32_t)clkg0_clr_spim0 << 17) | ((uint32_t)clkg0_set_spim0 << 16) | ((uint32_t)clkg1_clr_uart1 << 15) | ((uint32_t)clkg1_set_uart1 << 14) | ((uint32_t)clkg0_clr_uart1 << 13) | ((uint32_t)clkg0_set_uart1 << 12) | ((uint32_t)clkg1_clr_uart0 << 11) | ((uint32_t)clkg1_set_uart0 << 10) | ((uint32_t)clkg0_clr_uart0 << 9) | ((uint32_t)clkg0_set_uart0 << 8) | ((uint32_t)clkg1_clr_iic1 << 7) | ((uint32_t)clkg1_set_iic1 << 6) | ((uint32_t)clkg0_clr_iic1 << 5) | ((uint32_t)clkg0_set_iic1 << 4) | ((uint32_t)clkg1_clr_iic0 << 3) | ((uint32_t)clkg1_set_iic0 << 2) | ((uint32_t)clkg0_clr_iic0 << 1) | ((uint32_t)clkg0_set_iic0 << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_per_clkg1_get(void)
{
    return hwp_sysc_per->clkg1.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clkg1_set(uint32_t value)
{
    hwp_sysc_per->clkg1.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_clkg1_pack(uint8_t clkg_clr_gpio, uint8_t clkg_set_gpio, uint8_t clkg_clr_pwm4, uint8_t clkg_set_pwm4, uint8_t clkg_clr_pwm3, uint8_t clkg_set_pwm3, uint8_t clkg_clr_pwm2, uint8_t clkg_set_pwm2, uint8_t clkg_clr_pwm1, uint8_t clkg_set_pwm1, uint8_t clkg_clr_pwm0, uint8_t clkg_set_pwm0, uint8_t clkg_clr_pwm_div, uint8_t clkg_set_pwm_div)
{
    hwp_sysc_per->clkg1.val = (((uint32_t)clkg_clr_gpio << 13) | ((uint32_t)clkg_set_gpio << 12) | ((uint32_t)clkg_clr_pwm4 << 11) | ((uint32_t)clkg_set_pwm4 << 10) | ((uint32_t)clkg_clr_pwm3 << 9) | ((uint32_t)clkg_set_pwm3 << 8) | ((uint32_t)clkg_clr_pwm2 << 7) | ((uint32_t)clkg_set_pwm2 << 6) | ((uint32_t)clkg_clr_pwm1 << 5) | ((uint32_t)clkg_set_pwm1 << 4) | ((uint32_t)clkg_clr_pwm0 << 3) | ((uint32_t)clkg_set_pwm0 << 2) | ((uint32_t)clkg_clr_pwm_div << 1) | ((uint32_t)clkg_set_pwm_div << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_per_srst_get(void)
{
    return hwp_sysc_per->srst.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_srst_set(uint32_t value)
{
    hwp_sysc_per->srst.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_srst_pack(uint8_t srst_clr_gpio_n, uint8_t srst_set_gpio_n, uint8_t srst_clr_pwm_n, uint8_t srst_set_pwm_n, uint8_t srst_clr_spis_n, uint8_t srst_set_spis_n, uint8_t srst_clr_spim1_n, uint8_t srst_set_spim1_n, uint8_t srst_clr_spim0_n, uint8_t srst_set_spim0_n, uint8_t srst_clr_uart1_n, uint8_t srst_set_uart1_n, uint8_t srst_clr_uart0_n, uint8_t srst_set_uart0_n, uint8_t srst_clr_iic1_n, uint8_t srst_set_iic1_n, uint8_t srst_clr_iic0_n, uint8_t srst_set_iic0_n)
{
    hwp_sysc_per->srst.val = (((uint32_t)srst_clr_gpio_n << 17) | ((uint32_t)srst_set_gpio_n << 16) | ((uint32_t)srst_clr_pwm_n << 15) | ((uint32_t)srst_set_pwm_n << 14) | ((uint32_t)srst_clr_spis_n << 13) | ((uint32_t)srst_set_spis_n << 12) | ((uint32_t)srst_clr_spim1_n << 11) | ((uint32_t)srst_set_spim1_n << 10) | ((uint32_t)srst_clr_spim0_n << 9) | ((uint32_t)srst_set_spim0_n << 8) | ((uint32_t)srst_clr_uart1_n << 7) | ((uint32_t)srst_set_uart1_n << 6) | ((uint32_t)srst_clr_uart0_n << 5) | ((uint32_t)srst_set_uart0_n << 4) | ((uint32_t)srst_clr_iic1_n << 3) | ((uint32_t)srst_set_iic1_n << 2) | ((uint32_t)srst_clr_iic0_n << 1) | ((uint32_t)srst_set_iic0_n << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint32_t sysc_per_uart_issir_get(void)
{
    return hwp_sysc_per->uart_issir.val;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_uart_issir_set(uint32_t value)
{
    hwp_sysc_per->uart_issir.val = value;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_uart_issir_pack(uint8_t uart_is_sir)
{
    hwp_sysc_per->uart_issir.val = (((uint32_t)uart_is_sir << 0));
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_uart_issir_unpack(uint8_t* uart_is_sir)
{
    _T_SYSC_PER_UART_ISSIR localVal = hwp_sysc_per->uart_issir;

    *uart_is_sir = localVal.bit_field.uart_is_sir;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE uint8_t sysc_per_uart_is_sir_getf(void)
{
    return hwp_sysc_per->uart_issir.bit_field.uart_is_sir;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
__STATIC_INLINE void sysc_per_uart_is_sir_setf(uint8_t uart_is_sir)
{
    hwp_sysc_per->uart_issir.bit_field.uart_is_sir = uart_is_sir;
}

#ifdef __cplusplus
}
#endif

#endif /* __REG_SYSC_PER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

