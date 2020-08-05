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
#ifndef __APOLLO_00_REG_SYSC_PER_H__
#define __APOLLO_00_REG_SYSC_PER_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* config --------------------------------------------------------------------*/


/* includes ------------------------------------------------------------------*/
#include "apollo_00_ble_reg.h"

/* exported types ------------------------------------------------------------*/



#define CLK_16M                                 ( ( uint32_t ) 0U )
#define CLK_16M_DIV                             ( ( uint32_t ) 1U )
#define CLK_PLL                                 ( ( uint32_t ) 2U )
#define CLK_PLL_DIV                             ( ( uint32_t ) 3U )

/** @defgroup sysc_per_clk_sel_type
  * @{
  */
#define CLK_SEL_IIC0_16M                        ( CLK_16M << 0 )
#define CLK_SEL_IIC0_16M_DIV                    ( CLK_16M_DIV << 0 )
#define CLK_SEL_IIC0_PLL                        ( CLK_16M << 0 )
#define CLK_SEL_IIC0_PLL_DIV                    ( CLK_16M_DIV << 0 )

#define CLK_SEL_IIC1_16M                        ( CLK_16M << 4 )
#define CLK_SEL_IIC1_16M_DIV                    ( CLK_16M_DIV << 4 )
#define CLK_SEL_IIC1_PLL                        ( CLK_16M << 4 )
#define CLK_SEL_IIC1_PLL_DIV                    ( CLK_16M_DIV << 4 )

#define CLK_SEL_UART0_16M                       ( CLK_16M << 4 )
#define CLK_SEL_UART0_16M_DIV                   ( CLK_16M_DIV << 4 )
#define CLK_SEL_UART0_PLL                       ( CLK_16M << 4 )
#define CLK_SEL_UART0_PLL_DIV                   ( CLK_16M_DIV << 4 )

#define CLK_SEL_UART1_16M                       ( CLK_16M << 4 )
#define CLK_SEL_UART1_16M_DIV                   ( CLK_16M_DIV << 4 )
#define CLK_SEL_UART1_PLL                       ( CLK_16M << 4 )
#define CLK_SEL_UART1_PLL_DIV                   ( CLK_16M_DIV << 4 )
/**
  * @}
  */


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
    } ;
} T_SYSC_PER_CLK_DIV_PARAM0;

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
    } ;
} T_SYSC_PER_CLK_DIV_PARAM1;

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
    } ;
} T_SYSC_PER_CLK_DIV_PARAM2;

/** @defgroup sysc_per_clkg0 value definition
  * @{
  */
#define PER_CLKG0_16M_SET_IIC0                  ((uint32_t)0X00000001U)  
#define PER_CLKG0_16M_CLR_IIC0                  ((uint32_t)0X00000002U)  
#define PER_CLKG0_PLL_SET_IIC0                  ((uint32_t)0X00000004U)  
#define PER_CLKG0_PLL_CLR_IIC0                  ((uint32_t)0X00000008U)  
#define PER_CLKG0_16M_SET_IIC1                  ((uint32_t)0X00000010U)  
#define PER_CLKG0_16M_CLR_IIC1                  ((uint32_t)0X00000020U)  
#define PER_CLKG0_PLL_SET_IIC1                  ((uint32_t)0X00000040U)  
#define PER_CLKG0_PLL_CLR_IIC1                  ((uint32_t)0X00000080U)  
#define PER_CLKG0_16M_SET_UART0                 ((uint32_t)0X00000100U)  
#define PER_CLKG0_16M_CLR_UART0                 ((uint32_t)0X00000200U)  
#define PER_CLKG0_PLL_SET_UART0                 ((uint32_t)0X00000400U)  
#define PER_CLKG0_PLL_CLR_UART0                 ((uint32_t)0X00000800U)  
#define PER_CLKG0_16M_SET_UART1                 ((uint32_t)0X00001000U)  
#define PER_CLKG0_16M_CLR_UART1                 ((uint32_t)0x00002000U) 
#define PER_CLKG0_PLL_SET_UART1                 ((uint32_t)0X00004000U)  
#define PER_CLKG0_PLL_CLR_UART1                 ((uint32_t)0x00008000U) 
#define PER_CLKG0_16M_SET_SPIM0                 ((uint32_t)0X00010000U)  
#define PER_CLKG0_16M_CLR_SPIM0                 ((uint32_t)0x00020000U) 
#define PER_CLKG0_PLL_SET_SPIM0                 ((uint32_t)0X00040000U)  
#define PER_CLKG0_PLL_CLR_SPIM0                 ((uint32_t)0x00080000U) 
#define PER_CLKG0_16M_SET_SPIM1                 ((uint32_t)0X00100000U)  
#define PER_CLKG0_16M_CLR_SPIM1                 ((uint32_t)0x00200000U) 
#define PER_CLKG0_PLL_SET_SPIM1                 ((uint32_t)0X00400000U)  
#define PER_CLKG0_PLL_CLR_SPIM1                 ((uint32_t)0x00800000U) 
#define PER_CLKG0_16M_SET_SPIS                  ((uint32_t)0X01000000U)  
#define PER_CLKG0_16M_CLR_SPIS                  ((uint32_t)0x02000000U) 
#define PER_CLKG0_PLL_SET_SPIS                  ((uint32_t)0X04000000U)  
#define PER_CLKG0_PLL_CLR_SPIS                  ((uint32_t)0x08000000U) 

#define PER_CLKG0_MASK                          ((uint32_t)0x0FFFFFFFU)
#define IS_PER_CLKG0_TYPE(arg)                  ( ( ( arg ) & PER_CLKG0_MASK ) > 0 )
/**
  * @}
  */

/** @defgroup sysc_per_clkg1 value definition
  * @{
  */
#define PER_CLKG1_SET_PWM_DIV           ((uint32_t)0X00000001U)  
#define PER_CLKG1_CLR_PWM_DIV           ((uint32_t)0X00000002U)  
#define PER_CLKG1_SET_PWM0              ((uint32_t)0X00000004U)  
#define PER_CLKG1_CLR_PWM0              ((uint32_t)0X00000008U)  
#define PER_CLKG1_SET_PWM1              ((uint32_t)0X00000010U)  
#define PER_CLKG1_CLR_PWM1              ((uint32_t)0X00000020U)  
#define PER_CLKG1_SET_PWM2              ((uint32_t)0X00000040U)  
#define PER_CLKG1_CLR_PWM2              ((uint32_t)0X00000080U)  
#define PER_CLKG1_SET_PWM3              ((uint32_t)0X00000100U)  
#define PER_CLKG1_CLR_PWM3              ((uint32_t)0X00000200U)  
#define PER_CLKG1_SET_PWM4              ((uint32_t)0X00000400U)  
#define PER_CLKG1_CLR_PWM4              ((uint32_t)0X00000800U)  
#define PER_CLKG1_SET_GPIO              ((uint32_t)0X00001000U)  
#define PER_CLKG1_CLR_GPIO              ((uint32_t)0x00002000U)  

#define PER_CLKG1_MASK                  ((uint32_t)0x00003FFFU)
#define IS_PER_CLKG1_TYPE(arg)          ( ( ( arg ) & PER_CLKG1_MASK ) > 0 )
/**
  * @}
  */
  
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
    } ;
} T_SYSC_PER_SRST;

//uart_issir
typedef union
{
    uint32_t val;
    struct
    {
        uint32_t                    uart_is_sir :  1; /* 0: 0,        high means uart0 is sir*/
        uint32_t                     reserved_0 : 31; /*31: 1,                No description.*/
    } ;
} T_SYSC_PER_UART_ISSIR;

typedef struct
{
    __IO    uint32_t        CLK_SEL;        /*  0x0,    RW, 0x00000000,                No description.*/
    __IO    uint32_t        IICx_CLK_DIV;   /*  0x4,    RW, 0x00000000,                No description.*/
    __IO    uint32_t        UART0_CLK_DIV;  /*  0x8,    RW, 0x00000000,                No description.*/
    __IO    uint32_t        UART1_CLK_DIV;  /*  0xc,    RW, 0x00000000,                No description.*/
    __IO    uint32_t        CLKG0;          /* 0x10,    RW, 0x0FFFFFFF,                No description.*/
    __IO    uint32_t        CLKG1;          /* 0x14,    RW, 0x00003FFF,                @ref gpio_pins_type.*/
    __IO                 T_SYSC_PER_SRST                           srst; /* 0x18,    RW, 0x0003FFFF,                No description.*/
    __IO           T_SYSC_PER_UART_ISSIR                     uart_issir; /* 0x1c,    RW, 0x00000000,                No description.*/
} T_HWP_SYSC_PER_T;

/* exported variables --------------------------------------------------------*/
#define		SYSC_PER 	((T_HWP_SYSC_PER_T*)REG_SYSC_PER_BASE)

/* exported constants --------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_SYSC_PER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

