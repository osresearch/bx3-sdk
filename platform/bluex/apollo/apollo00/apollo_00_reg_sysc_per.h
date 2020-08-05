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
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/
typedef struct {
    __IO uint32_t CS;                   /* !< clock select                      0x0000 */
    __IO uint32_t CDP0;                 /* !< iic0¡¢iic1¡¢pwm clock divide para 0x0004 */
    __IO uint32_t CDP1;                 /* !< uart0 clock divide para           0x0008 */
    __IO uint32_t CDP2;                 /* !< uart1 clock divide para           0x000C */
    __IO uint32_t CLKG0;                /* !< clock gate                        0x0010 */
    __IO uint32_t CLKG1;                /* !< clock gate                        0x0014 */
    __IO uint32_t SRST;                 /* !< soft reset                        0x0018 */
    __IO uint32_t UARTSIR;              /* !< high means uart0 is sir           0x001C */
} reg_sysc_per_t;

/* bit definition ------------------------------------------------------------*/

/*****************  Bit definition for SYS_PER CS register  ********************/
#define PER_CS_IIC0_POS                                 (0U)
#define PER_CS_IIC0_MASK                                (0X3UL << PER_CS_IIC0_POS)
#define PER_CS_IIC0                                     PER_CS_IIC0_MASK
#define PER_CS_IIC1_POS                                 (4U)
#define PER_CS_IIC1_MASK                                (0X3UL << PER_CS_IIC1_POS)
#define PER_CS_IIC1                                     PER_CS_IIC1_MASK
#define PER_CS_UART0_POS                                (8U)
#define PER_CS_UART0_MASK                               (0X3UL << PER_CS_UART0_POS)
#define PER_CS_UART0                                    PER_CS_UART0_MASK
#define PER_CS_UART1_POS                                (12U)
#define PER_CS_UART1_MASK                               (0X3UL << PER_CS_UART1_POS)
#define PER_CS_UART1                                    PER_CS_UART1_MASK

/*****************  Bit definition for SYS_PER IICx_PWM_CD register  ********************/
#define PER_CDP0_IIC0_POS                               ( 0U )
#define PER_CDP0_IIC0_MASK                              ( 0XFUL << PER_IICx_PWM_CD_IIC0_POS )
#define PER_CDP0_IIC0                                   PER_IICx_PWM_CD_IIC0_MASK
#define PER_CDP0_IIC1_POS                               ( 4U )
#define PER_CDP0_IIC1_MASK                              ( 0XFUL << PER_IICx_PWM_CD_IIC1_POS )
#define PER_CDP0_IIC1                                   PER_IICx_PWM_CD_IIC1_MASK
#define PER_CDP0_PWM_POS                                ( 24U )
#define PER_CDP0_PWM_MASK                               ( 0XFFUL << PER_IICx_PWM_CD_PWM_POS )
#define PER_CDP0_PWM                                    PER_IICx_PWM_CD_PWM_MASK

/*****************  Bit definition for SYS_PER UART0_CLK_DIV register  ********************/
#define PER_CDP1_LEN0_M1_POS                            ( 0U )
#define PER_CDP1_LEN0_M1_MASK                           ( 0X3FUL << PER_CDP1_LEN0_M1_POS )
#define PER_CDP1_LEN0_M1                                PER_CDP1_LEN0_M1_MASK
#define PER_CDP1_LEN1_M1_POS                            ( 8U )
#define PER_CDP1_LEN1_M1_MASK                           ( 0X3FUL << PER_CDP1_LEN1_M1_POS )
#define PER_CDP1_LEN1_M1                                PER_CDP1_LEN1_M1_MASK
#define PER_CDP1_NUM0_M1_POS                            ( 16U )
#define PER_CDP1_NUM0_M1_MASK                           ( 0XFUL << PER_CDP1_NUM0_M1_POS )
#define PER_CDP1_NUM0_M1                                PER_CDP1_NUM0_M1_MASK
#define PER_CDP1_NUM1_M1_POS                            ( 24U )
#define PER_CDP1_NUM1_M1_MASK                           ( 0XFUL << PER_CDP1_NUM1_M1_POS )
#define PER_CDP1_NUM1_M1                                PER_CDP1_NUM1_M1_MASK

/*****************  Bit definition for SYS_PER UART1_CLK_DIV register  ********************/
#define PER_CDP2_LEN0_M1_POS                            ( 0U )
#define PER_CDP2_LEN0_M1_MASK                           ( 0x3FUL << PER_CDP2_LEN0_M1_POS )
#define PER_CDP2_LEN0_M1                                PER_CDP2_LEN0_M1_MASK
#define PER_CDP2_LEN1_M1_POS                            ( 8U )
#define PER_CDP2_LEN1_M1_MASK                           ( 0X3FUL << PER_CDP2_LEN1_M1_POS )
#define PER_CDP2_LEN1_M1                                PER_CDP2_LEN1_M1_MASK
#define PER_CDP2_NUM0_M1_POS                            ( 16U )
#define PER_CDP2_NUM0_M1_MASK                           ( 0XFUL << PER_CDP2_NUM0_M1_POS )
#define PER_CDP2_NUM0_M1                                PER_CDP2_NUM0_M1_MASK
#define PER_CDP2_NUM1_M1_POS                            ( 24U )
#define PER_CDP2_NUM1_M1_MASK                           ( 0XFUL << PER_CDP2_NUM1_M1_POS )
#define PER_CDP2_NUM1_M1                                PER_CDP2_NUM1_M1_MASK

/*****************  Bit definition for SYS_PER CLKG0 register  ********************/
#define PER_CLKG0_32M_SET_IIC0_POS                      (0U)
#define PER_CLKG0_32M_SET_IIC0_MASK                     (0X1UL << PER_CLKG0_32M_SET_IIC0_POS)
#define PER_CLKG0_32M_SET_IIC0                          PER_CLKG0_32M_SET_IIC0_MASK
#define PER_CLKG0_32M_CLR_IIC0_POS                      (1U)
#define PER_CLKG0_32M_CLR_IIC0_MASK                     (0X1UL << PER_CLKG0_32M_CLR_IIC0_POS)
#define PER_CLKG0_32M_CLR_IIC0                          PER_CLKG0_32M_CLR_IIC0_MASK
#define PER_CLKG0_PLL_SET_IIC0_POS                      (2U)
#define PER_CLKG0_PLL_SET_IIC0_MASK                     (0X1UL << PER_CLKG0_PLL_SET_IIC0_POS)
#define PER_CLKG0_PLL_SET_IIC0                          PER_CLKG0_PLL_SET_IIC0_MASK
#define PER_CLKG0_PLL_CLR_IIC0_POS                      (3U)
#define PER_CLKG0_PLL_CLR_IIC0_MASK                     (0X1UL << PER_CLKG0_PLL_CLR_IIC0_POS)
#define PER_CLKG0_PLL_CLR_IIC0                          PER_CLKG0_PLL_CLR_IIC0_MASK
#define PER_CLKG0_32M_SET_IIC1_POS                      (4U)
#define PER_CLKG0_32M_SET_IIC1_MASK                     (0X1UL << PER_CLKG0_32M_SET_IIC1_POS)
#define PER_CLKG0_32M_SET_IIC1                          PER_CLKG0_32M_SET_IIC1_MASK
#define PER_CLKG0_32M_CLR_IIC1_POS                      (5U)
#define PER_CLKG0_32M_CLR_IIC1_MASK                     (0X1UL << PER_CLKG0_32M_CLR_IIC1_POS)
#define PER_CLKG0_32M_CLR_IIC1                          PER_CLKG0_32M_CLR_IIC1_MASK
#define PER_CLKG0_PLL_SET_IIC1_POS                      (6U)
#define PER_CLKG0_PLL_SET_IIC1_MASK                     (0X1UL << PER_CLKG0_PLL_SET_IIC1_POS)
#define PER_CLKG0_PLL_SET_IIC1                          PER_CLKG0_PLL_SET_IIC1_MASK
#define PER_CLKG0_PLL_CLR_IIC1_POS                      (7U)
#define PER_CLKG0_PLL_CLR_IIC1_MASK                     (0X1UL << PER_CLKG0_PLL_CLR_IIC1_POS)
#define PER_CLKG0_PLL_CLR_IIC1                          PER_CLKG0_PLL_CLR_IIC1_MASK
#define PER_CLKG0_32M_SET_UART0_POS                     (8U)
#define PER_CLKG0_32M_SET_UART0_MASK                    (0X1UL << PER_CLKG0_32M_SET_UART0_POS)
#define PER_CLKG0_32M_SET_UART0                         PER_CLKG0_32M_SET_UART0_MASK
#define PER_CLKG0_32M_CLR_UART0_POS                     (9U)
#define PER_CLKG0_32M_CLR_UART0_MASK                    (0X1UL << PER_CLKG0_32M_CLR_UART0_POS)
#define PER_CLKG0_32M_CLR_UART0                         PER_CLKG0_32M_CLR_UART0_MASK
#define PER_CLKG0_PLL_SET_UART0_POS                     (10U)
#define PER_CLKG0_PLL_SET_UART0_MASK                    (0X1UL << PER_CLKG0_PLL_SET_UART0_POS)
#define PER_CLKG0_PLL_SET_UART0                         PER_CLKG0_PLL_SET_UART0_MASK
#define PER_CLKG0_PLL_CLR_UART0_POS                     (11U)
#define PER_CLKG0_PLL_CLR_UART0_MASK                    (0X1UL << PER_CLKG0_PLL_CLR_UART0_POS)
#define PER_CLKG0_PLL_CLR_UART0                         PER_CLKG0_PLL_CLR_UART0_MASK
#define PER_CLKG0_32M_SET_UART1_POS                     (12U)
#define PER_CLKG0_32M_SET_UART1_MASK                    (0X1UL << PER_CLKG0_32M_SET_UART1_POS)
#define PER_CLKG0_32M_SET_UART1                         PER_CLKG0_32M_SET_UART1_MASK
#define PER_CLKG0_32M_CLR_UART1_POS                     (13U)
#define PER_CLKG0_32M_CLR_UART1_MASK                    (0X1UL << PER_CLKG0_32M_CLR_UART1_POS)
#define PER_CLKG0_32M_CLR_UART1                         PER_CLKG0_32M_CLR_UART1_MASK
#define PER_CLKG0_PLL_SET_UART1_POS                     (14U)
#define PER_CLKG0_PLL_SET_UART1_MASK                    (0X1UL << PER_CLKG0_PLL_SET_UART1_POS)
#define PER_CLKG0_PLL_SET_UART1                         PER_CLKG0_PLL_SET_UART1_MASK
#define PER_CLKG0_PLL_CLR_UART1_POS                     (15U)
#define PER_CLKG0_PLL_CLR_UART1_MASK                    (0X1UL << PER_CLKG0_PLL_CLR_UART1_POS)
#define PER_CLKG0_PLL_CLR_UART1                         PER_CLKG0_PLL_CLR_UART1_MASK
#define PER_CLKG0_32M_SET_SPIM0_POS                     (16U)
#define PER_CLKG0_32M_SET_SPIM0_MASK                    (0X1UL << PER_CLKG0_32M_SET_SPIM0_POS)
#define PER_CLKG0_32M_SET_SPIM0                         PER_CLKG0_32M_SET_SPIM0_MASK
#define PER_CLKG0_32M_CLR_SPIM0_POS                     (17U)
#define PER_CLKG0_32M_CLR_SPIM0_MASK                    (0X1UL << PER_CLKG0_32M_CLR_SPIM0_POS)
#define PER_CLKG0_32M_CLR_SPIM0                         PER_CLKG0_32M_CLR_SPIM0_MASK
#define PER_CLKG0_PLL_SET_SPIM0_POS                     (18U)
#define PER_CLKG0_PLL_SET_SPIM0_MASK                    (0X1UL << PER_CLKG0_PLL_SET_SPIM0_POS)
#define PER_CLKG0_PLL_SET_SPIM0                         PER_CLKG0_PLL_SET_SPIM0_MASK
#define PER_CLKG0_PLL_CLR_SPIM0_POS                     (19U)
#define PER_CLKG0_PLL_CLR_SPIM0_MASK                    (0X1UL << PER_CLKG0_PLL_CLR_SPIM0_POS)
#define PER_CLKG0_PLL_CLR_SPIM0                         PER_CLKG0_PLL_CLR_SPIM0_MASK
#define PER_CLKG0_32M_SET_SPIM1_POS                     (20U)
#define PER_CLKG0_32M_SET_SPIM1_MASK                    (0X1UL << PER_CLKG0_32M_SET_SPIM1_POS)
#define PER_CLKG0_32M_SET_SPIM1                         PER_CLKG0_32M_SET_SPIM1_MASK
#define PER_CLKG0_32M_CLR_SPIM1_POS                     (21U)
#define PER_CLKG0_32M_CLR_SPIM1_MASK                    (0X1UL << PER_CLKG0_32M_CLR_SPIM1_POS)
#define PER_CLKG0_32M_CLR_SPIM1                         PER_CLKG0_32M_CLR_SPIM1_MASK
#define PER_CLKG0_PLL_SET_SPIM1_POS                     (22U)
#define PER_CLKG0_PLL_SET_SPIM1_MASK                    (0X1UL << PER_CLKG0_PLL_SET_SPIM1_POS)
#define PER_CLKG0_PLL_SET_SPIM1                         PER_CLKG0_PLL_SET_SPIM1_MASK
#define PER_CLKG0_PLL_CLR_SPIM1_POS                     (23U)
#define PER_CLKG0_PLL_CLR_SPIM1_MASK                    (0X1UL << PER_CLKG0_PLL_CLR_SPIM1_POS)
#define PER_CLKG0_PLL_CLR_SPIM1                         PER_CLKG0_PLL_CLR_SPIM1_MASK
#define PER_CLKG0_32M_SET_SPIS_POS                      (24U)
#define PER_CLKG0_32M_SET_SPIS_MASK                     (0X1UL << PER_CLKG0_32M_SET_SPIS_POS)
#define PER_CLKG0_32M_SET_SPIS                          PER_CLKG0_32M_SET_SPIS_MASK
#define PER_CLKG0_32M_CLR_SPIS_POS                      (25U)
#define PER_CLKG0_32M_CLR_SPIS_MASK                     (0X1UL << PER_CLKG0_32M_CLR_SPIS_POS)
#define PER_CLKG0_32M_CLR_SPIS                          PER_CLKG0_32M_CLR_SPIS_MASK
#define PER_CLKG0_PLL_SET_SPIS_POS                      (26U)
#define PER_CLKG0_PLL_SET_SPIS_MASK                     (0X1UL << PER_CLKG0_PLL_SET_SPIS_POS)
#define PER_CLKG0_PLL_SET_SPIS                          PER_CLKG0_PLL_SET_SPIS_MASK
#define PER_CLKG0_PLL_CLR_SPIS_POS                      (27U)
#define PER_CLKG0_PLL_CLR_SPIS_MASK                     (0X1UL << PER_CLKG0_PLL_CLR_SPIS_POS)
#define PER_CLKG0_PLL_CLR_SPIS                          PER_CLKG0_PLL_CLR_SPIS_MASK

/*****************  Bit definition for SYS_PER CLKG1 register  ********************/
#define PER_CLKG1_SET_PWM_DIV_POS                       (0U)
#define PER_CLKG1_SET_PWM_DIV_MASK                      (0X1UL << PER_CLKG1_SET_PWM_DIV_POS)
#define PER_CLKG1_SET_PWM_DIV                           PER_CLKG1_SET_PWM_DIV_MASK
#define PER_CLKG1_CLR_PWM_DIV_POS                       (1U)
#define PER_CLKG1_CLR_PWM_DIV_MASK                      (0X1UL << PER_CLKG1_CLR_PWM_DIV_POS)
#define PER_CLKG1_CLR_PWM_DIV                           PER_CLKG1_CLR_PWM_DIV_MASK
#define PER_CLKG1_SET_PWM0_POS                          (2U)
#define PER_CLKG1_SET_PWM0_MASK                         (0X1UL << PER_CLKG1_SET_PWM0_POS)
#define PER_CLKG1_SET_PWM0                              PER_CLKG1_SET_PWM0_MASK
#define PER_CLKG1_CLR_PWM0_POS                          (3U)
#define PER_CLKG1_CLR_PWM0_MASK                         (0X1UL << PER_CLKG1_CLR_PWM0_POS)
#define PER_CLKG1_CLR_PWM0                              PER_CLKG1_CLR_PWM0_MASK
#define PER_CLKG1_SET_PWM1_POS                          (4U)
#define PER_CLKG1_SET_PWM1_MASK                         (0X1UL << PER_CLKG1_SET_PWM1_POS)
#define PER_CLKG1_SET_PWM1                              PER_CLKG1_SET_PWM1_MASK
#define PER_CLKG1_CLR_PWM1_POS                          (5U)
#define PER_CLKG1_CLR_PWM1_MASK                         (0X1UL << PER_CLKG1_CLR_PWM1_POS)
#define PER_CLKG1_CLR_PWM1                              PER_CLKG1_CLR_PWM1_MASK
#define PER_CLKG1_SET_PWM2_POS                          (6U)
#define PER_CLKG1_SET_PWM2_MASK                         (0X1UL << PER_CLKG1_SET_PWM2_POS)
#define PER_CLKG1_SET_PWM2                              PER_CLKG1_SET_PWM2_MASK
#define PER_CLKG1_CLR_PWM2_POS                          (7U)
#define PER_CLKG1_CLR_PWM2_MASK                         (0X1UL << PER_CLKG1_CLR_PWM2_POS)
#define PER_CLKG1_CLR_PWM2                              PER_CLKG1_CLR_PWM2_MASK
#define PER_CLKG1_SET_PWM3_POS                          (8U)
#define PER_CLKG1_SET_PWM3_MASK                         (0X1UL << PER_CLKG1_SET_PWM3_POS)
#define PER_CLKG1_SET_PWM3                              PER_CLKG1_SET_PWM3_MASK
#define PER_CLKG1_CLR_PWM3_POS                          (9U)
#define PER_CLKG1_CLR_PWM3_MASK                         (0X1UL << PER_CLKG1_CLR_PWM3_POS)
#define PER_CLKG1_CLR_PWM3                              PER_CLKG1_CLR_PWM3_MASK
#define PER_CLKG1_SET_PWM4_POS                          (10U)
#define PER_CLKG1_SET_PWM4_MASK                         (0X1UL << PER_CLKG1_SET_PWM4_POS)
#define PER_CLKG1_SET_PWM4                              PER_CLKG1_SET_PWM4_MASK
#define PER_CLKG1_CLR_PWM4_POS                          (11U)
#define PER_CLKG1_CLR_PWM4_MASK                         (0X1UL << PER_CLKG1_CLR_PWM4_POS)
#define PER_CLKG1_CLR_PWM4                              PER_CLKG1_CLR_PWM4_MASK
#define PER_CLKG1_SET_GPIO_POS                          (12U)
#define PER_CLKG1_SET_GPIO_MASK                         (0X1UL << PER_CLKG1_SET_GPIO_POS)
#define PER_CLKG1_SET_GPIO                              PER_CLKG1_SET_GPIO_MASK
#define PER_CLKG1_CLR_GPIO_POS                          (13U)
#define PER_CLKG1_CLR_GPIO_MASK                         (0X1UL << PER_CLKG1_CLR_GPIO_POS)
#define PER_CLKG1_CLR_GPIO                              PER_CLKG1_CLR_GPIO_MASK

/*****************  Bit definition for SYS_PER SRST register  ********************/
#define PER_SRST_SET_IIC0_POS                           (0U)
#define PER_SRST_SET_IIC0_MASK                          (0X1UL << PER_SRST_SET_IIC0_POS)
#define PER_SRST_SET_IIC0                               PER_SRST_SET_IIC0_MASK
#define PER_SRST_CLR_IIC0_POS                           (1U)
#define PER_SRST_CLR_IIC0_MASK                          (0X1UL << PER_SRST_CLR_IIC0_POS)
#define PER_SRST_CLR_IIC0                               PER_SRST_CLR_IIC0_MASK
#define PER_SRST_SET_IIC1_POS                           (2U)
#define PER_SRST_SET_IIC1_MASK                          (0X1UL << PER_SRST_SET_IIC1_POS)
#define PER_SRST_SET_IIC1                               PER_SRST_SET_IIC1_MASK
#define PER_SRST_CLR_IIC1_POS                           (3U)
#define PER_SRST_CLR_IIC1_MASK                          (0X1UL << PER_SRST_CLR_IIC1_POS)
#define PER_SRST_CLR_IIC1                               PER_SRST_CLR_IIC1_MASK
#define PER_SRST_SET_UART0_POS                          (4U)
#define PER_SRST_SET_UART0_MASK                         (0X1UL << PER_SRST_SET_UART0_POS)
#define PER_SRST_SET_UART0                              PER_SRST_SET_UART0_MASK
#define PER_SRST_CLR_UART0_POS                          (5U)
#define PER_SRST_CLR_UART0_MASK                         (0X1UL << PER_SRST_CLR_UART0_POS)
#define PER_SRST_CLR_UART0                              PER_SRST_CLR_UART0_MASK
#define PER_SRST_SET_UART1_POS                          (6U)
#define PER_SRST_SET_UART1_MASK                         (0X1UL << PER_SRST_SET_UART1_POS)
#define PER_SRST_SET_UART1                              PER_SRST_SET_UART1_MASK
#define PER_SRST_CLR_UART1_POS                          (7U)
#define PER_SRST_CLR_UART1_MASK                         (0X1UL << PER_SRST_CLR_UART1_POS)
#define PER_SRST_CLR_UART1                              PER_SRST_CLR_UART1_MASK
#define PER_SRST_SET_SPIM0_POS                          (8U)
#define PER_SRST_SET_SPIM0_MASK                         (0X1UL << PER_SRST_SET_SPIM0_POS)
#define PER_SRST_SET_SPIM0                              PER_SRST_SET_SPIM0_MASK
#define PER_SRST_CLR_SPIM0_POS                          (9U)
#define PER_SRST_CLR_SPIM0_MASK                         (0X1UL << PER_SRST_CLR_SPIM0_POS)
#define PER_SRST_CLR_SPIM0                              PER_SRST_CLR_SPIM0_MASK
#define PER_SRST_SET_SPIM1_POS                          (10U)
#define PER_SRST_SET_SPIM1_MASK                         (0X1UL << PER_SRST_SET_SPIM1_POS)
#define PER_SRST_SET_SPIM1                              PER_SRST_SET_SPIM1_MASK
#define PER_SRST_CLR_SPIM1_POS                          (11U)
#define PER_SRST_CLR_SPIM1_MASK                         (0X1UL << PER_SRST_CLR_SPIM1_POS)
#define PER_SRST_CLR_SPIM1                              PER_SRST_CLR_SPIM1_MASK
#define PER_SRST_SET_SPIS_POS                           (12U)
#define PER_SRST_SET_SPIS_MASK                          (0X1UL << PER_SRST_SET_SPIS_POS)
#define PER_SRST_SET_SPIS                               PER_SRST_SET_SPIS_MASK
#define PER_SRST_CLR_SPIS_POS                           (13U)
#define PER_SRST_CLR_SPIS_MASK                          (0X1UL << PER_SRST_CLR_SPIS_POS)
#define PER_SRST_CLR_SPIS                               PER_SRST_CLR_SPIS_MASK
#define PER_SRST_SET_PWM_POS                            (14U)
#define PER_SRST_SET_PWM_MASK                           (0X1UL << PER_SRST_SET_PWM_POS)
#define PER_SRST_SET_PWM                                PER_SRST_SET_PWM_MASK
#define PER_SRST_CLR_PWM_POS                            (15U)
#define PER_SRST_CLR_PWM_MASK                           (0X1UL << PER_SRST_CLR_PWM_POS)
#define PER_SRST_CLR_PWM                                PER_SRST_CLR_PWM_MASK
#define PER_SRST_SET_GPIO_POS                           (16U)
#define PER_SRST_SET_GPIO_MASK                          (0X1UL << PER_SRST_SET_GPIO_POS)
#define PER_SRST_SET_GPIO                               PER_SRST_SET_GPIO_MASK
#define PER_SRST_CLR_GPIO_POS                           (17U)
#define PER_SRST_CLR_GPIO_MASK                          (0X1UL << PER_SRST_CLR_GPIO_POS)
#define PER_SRST_CLR_GPIO                               PER_SRST_CLR_GPIO_MASK

/*****************  Bit definition for SYS_PER UART0_ISSI register  ********************/
#define PER_UARTSIR_POS                                 (0U)
#define PER_UARTSIR_MASK                                (0X1UL << PER_UARTSIR_POS)
#define PER_UARTSIR                                     PER_UARTSIR_MASK


/* value type ----------------------------------------------------------------*/

/***********  type definition for per clock select (per_cs_type)  *************/
#define PER_CS_TYPE_16M_IIC0                            ( ( uint32_t ) 0X00UL << 0 )
#define PER_CS_TYPE_16M_DIV_IIC0                        ( ( uint32_t ) 0X01UL << 0 )
#define PER_CS_TYPE_PLL_IIC0                            ( ( uint32_t ) 0X02UL << 0 )
#define PER_CS_TYPE_PLL_DIV_IIC0                        ( ( uint32_t ) 0X03UL << 0 )

#define PER_CS_TYPE_16M_IIC1                            ( ( uint32_t ) 0X00UL << 4 )
#define PER_CS_TYPE_16M_DIV_IIC1                        ( ( uint32_t ) 0X01UL << 4 )
#define PER_CS_TYPE_PLL_IIC1                            ( ( uint32_t ) 0X02UL << 4 )
#define PER_CS_TYPE_PLL_DIV_IIC1                        ( ( uint32_t ) 0X03UL << 4 )

#define PER_CS_TYPE_16M_UART0                           ( ( uint32_t ) 0X00UL << 8 )
#define PER_CS_TYPE_16M_DIV_UART0                       ( ( uint32_t ) 0X01UL << 8 )
#define PER_CS_TYPE_PLL_UART0                           ( ( uint32_t ) 0X02UL << 8 )
#define PER_CS_TYPE_PLL_DIV_UART0                       ( ( uint32_t ) 0X03UL << 8 )

#define PER_CS_TYPE_16M_UART1                           ( ( uint32_t ) 0X00UL << 12 )
#define PER_CS_TYPE_16M_DIV_UART1                       ( ( uint32_t ) 0X01UL << 12 )
#define PER_CS_TYPE_PLL_UART1                           ( ( uint32_t ) 0X02UL << 12 )
#define PER_CS_TYPE_PLL_DIV_UART1                       ( ( uint32_t ) 0X03UL << 12 )
#define IS_PER_CS_TYPE(arg)


/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_SYSC_PER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
