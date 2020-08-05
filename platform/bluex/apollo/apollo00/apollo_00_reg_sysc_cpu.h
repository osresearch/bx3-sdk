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
#include "apollo_00_reg.h"


/* exported types ------------------------------------------------------------*/


typedef struct {
         uint32_t reserved0[2];         /* !< no decription                         0x0000 */
    __IO uint32_t TIMDP;                /* !< TIM divider parameter from clk_16m    0x0008 */
         uint32_t reserved1;            /* !< no decription                         0x000C */
    __IO uint32_t CLKG0;                /* !< clock gate control register           0x0010 */
    __IO uint32_t CLKG1;                /* !< clock gate control register           0x0014 */
    __IO uint32_t SRST;                 /* !< soft reset control reg                0x0018 */
         uint32_t reserved2;            /* !< no decription                         0x001C */
    __IO uint32_t PSEN;                 /* !< pin share enable                      0x0020 */
    __IO uint32_t FIOEN;                /* !< function io enable                    0x0024 */
         uint32_t reserved3[2];         /* !< no decription                         0x0028 */
    __IO uint32_t FIOS0;                /* !< function io0~7 select                 0x0030 */
    __IO uint32_t FIOS1;                /* !< function io8~15 select                0x0034 */
    __IO uint32_t FIOS2;                /* !< function io16~21 select               0x0038 */
         uint32_t reserved4;            /* !< no decription                         0x003C */
    __IO uint32_t SCR;                  /* !< system control register               0x0040 */
    __IO uint32_t SFI;                  /* !< software interrupt                    0x0044 */
         uint32_t reserved5;            /* !< no decription                         0x0048 */
    __IO uint32_t CAL32K;               /* !< 32KHz clock calibration               0x004C */
    __IO uint32_t PSA0L;                /* !< min address of the address spy space0 0x0050 */
    __IO uint32_t PSA0H;                /* !< max address of the address spy space0 0x0054 */
    __IO uint32_t PSA1L;                /* !< min address of the address spy space1 0x0058 */
    __IO uint32_t PSA1H;                /* !< max address of the address spy space1 0x005C */
    __IO uint32_t PSIE;                 /* !< page spy interrupt enable             0x0060 */
    __IO uint32_t PSIM;                 /* !< page spy interrupt mask               0x0064 */
    __I  uint32_t PSRI;                 /* !< page spy raw interrupt                0x0068 */
    __I  uint32_t PSI;                  /* !< page spy interrupt                    0x006C */
} reg_sysc_cpu_t;

/* bit definition ------------------------------------------------------------*/
/*****************  Bit definition for SYS_CPU TIM_DIV_PARA register  ********************/
#define CPU_TIMDP_POS                                   (16U)
#define CPU_TIMDP_MASK                                  (0xffUL << CPU_TIMDP_POS)                       /*!< 0x00FF0000*/
#define CPU_TIMDP                                       CPU_TIMDP_MASK                                  /*!< divider parameter from clk_16m*/

/*****************  Bit definition for SYS_CPU CLKG0 register  ********************/
#define CPU_CLKG0_SET_TIM_DIV_POS                       (6U)
#define CPU_CLKG0_SET_TIM_DIV_MASK                      (1UL << CPU_CLKG0_SET_TIM_DIV_POS)              /*!< 0x00000040*/
#define CPU_CLKG0_SET_TIM_DIV                           CPU_CLKG0_SET_TIM_DIV_MASK                      /*!< set timer div clock gate makes the clock active*/
#define CPU_CLKG0_CLR_TIM_DIV_POS                       (7U)
#define CPU_CLKG0_CLR_TIM_DIV_MASK                      (1UL << CPU_CLKG0_CLR_TIM_DIV_POS)              /*!< 0x00000080*/
#define CPU_CLKG0_CLR_TIM_DIV                           CPU_CLKG0_CLR_TIM_DIV_MASK                      /*!< clear timer div clock gate makes the clock inactive*/

/*****************  Bit definition for SYS_CPU CLKG1 register  ********************/
#define CPU_CLKG1_SET_WDT_POS                           (4U)
#define CPU_CLKG1_SET_WDT_MASK                          (1UL << CPU_CLKG1_SET_WDT_POS)                  /*!< 0x00000010*/
#define CPU_CLKG1_SET_WDT                                CPU_CLKG1_SET_WDT_MASK                         /*!< set wdt clock gate makes the clock active*/
#define CPU_CLKG1_CLR_WDT_POS                           (5U)
#define CPU_CLKG1_CLR_WDT_MASK                          (1UL << CPU_CLKG1_CLR_WDT_POS)                  /*!< 0x00000020*/
#define CPU_CLKG1_CLR_WDT                               CPU_CLKG1_CLR_WDT_MASK                          /*!< clear wdt clock gate makes the clock inactive*/
#define CPU_CLKG1_SET_DMAC_POS                          (6U)
#define CPU_CLKG1_SET_DMAC_MASK                         (1UL << CPU_CLKG1_SET_DMAC_POS)                 /*!< 0x00000040*/
#define CPU_CLKG1_SET_DMAC                              CPU_CLKG1_SET_DMAC_MASK                         /*!< set DMAC clock gate makes the clock active*/
#define CPU_CLKG1_CLR_DMAC_POS                          (7U)
#define CPU_CLKG1_CLR_DMAC_MASK                         (1UL << CPU_CLKG1_CLR_DMAC_POS)                 /*!< 0x00000080*/
#define CPU_CLKG1_CLR_DMAC                              CPU_CLKG1_CLR_DMAC_MASK                         /*!< clear DMAC clock gate makes the clock inactive*/
#define CPU_CLKG1_SET_CACHE_POS                         (8U)
#define CPU_CLKG1_SET_CACHE_MASK                        (1UL << CPU_CLKG1_SET_CACHE_POS)                /*!< 0x00000100*/
#define CPU_CLKG1_SET_CACHE                             CPU_CLKG1_SET_CACHE_MASK                        /*!< set cache clock gate makes the clock active*/
#define CPU_CLKG1_CLR_CACHE_POS                         (9U)
#define CPU_CLKG1_CLR_CACHE_MASK                        (1UL << CPU_CLKG1_CLR_CACHE_POS)                /*!< 0x00000200*/
#define CPU_CLKG1_CLR_CACHE                             CPU_CLKG1_CLR_CACHE_MASK                        /*!< clear cache clock gate makes the clock inactive*/
#define CPU_CLKG1_SET_QSPI_POS                          (10U)
#define CPU_CLKG1_SET_QSPI_MASK                         (1UL << CPU_CLKG1_SET_QSPI_POS)                 /*!< 0x00000400*/
#define CPU_CLKG1_SET_QSPI                              CPU_CLKG1_SET_QSPI_MASK                         /*!< set qspi clock gate makes the clock active*/
#define CPU_CLKG1_CLR_QSPI_POS                          (11U)
#define CPU_CLKG1_CLR_QSPI_MASK                         (1UL << CPU_CLKG1_CLR_QSPI_POS)                 /*!< 0x00000800*/
#define CPU_CLKG1_CLR_QSPI                              CPU_CLKG1_CLR_QSPI_MASK                         /*!< clear qspi clock gate makes the clock inactive*/
#define CPU_CLKG1_SET_TIM0_POS                          (12U)
#define CPU_CLKG1_SET_TIM0_MASK                         (1UL << CPU_CLKG1_SET_TIM0_POS)                 /*!< 0x00001000*/
#define CPU_CLKG1_SET_TIM0                              CPU_CLKG1_SET_TIM0_MASK                         /*!< set timer0 clock gate makes the clock active*/
#define CPU_CLKG1_CLR_TIM0_POS                          (13U)
#define CPU_CLKG1_CLR_TIM0_MASK                         (1UL << CPU_CLKG1_CLR_TIM0_POS)                 /*!< 0x00002000*/
#define CPU_CLKG1_CLR_TIM0                              CPU_CLKG1_CLR_TIM0_MASK                         /*!< clear timer0 clock gate makes the clock inactive*/
#define CPU_CLKG1_SET_TIM1_POS                          (14U)
#define CPU_CLKG1_SET_TIM1_MASK                         (1UL << CPU_CLKG1_SET_TIM1_POS)                 /*!< 0x00004000*/
#define CPU_CLKG1_SET_TIM1                              CPU_CLKG1_SET_TIM1_MASK                         /*!< set timer1 clock gate makes the clock active*/
#define CPU_CLKG1_CLR_TIM1_POS                          (15U)
#define CPU_CLKG1_CLR_TIM1_MASK                         (1UL << CPU_CLKG1_CLR_TIM1_POS)                 /*!< 0x00008000*/
#define CPU_CLKG1_CLR_TIM1                              CPU_CLKG1_CLR_TIM1_MASK                         /*!< clear timer1 clock gate makes the clock inactive*/
#define CPU_CLKG1_SET_UART2AHB_POS                      (16U)
#define CPU_CLKG1_SET_UART2AHB_MASK                     (1UL << CPU_CLKG1_SET_UART2AHB_POS)             /*!< 0x00010000*/
#define CPU_CLKG1_SET_UART2AHB                          CPU_CLKG1_SET_UART2AHB_MASK                     /*!< set uart2ahb clock gate makes the clock active*/
#define CPU_CLKG1_CLR_UART2AHB_POS                      (17U)
#define CPU_CLKG1_CLR_UART2AHB_MASK                     (1UL << CPU_CLKG1_CLR_UART2AHB_POS)             /*!< 0x00020000*/
#define CPU_CLKG1_CLR_UART2AHB                           CPU_CLKG1_CLR_UART2AHB_MASK                    /*!< clear uart2ahb clock gate makes the clock inactive*/
#define CPU_CLKG1_SET_ECC_POS                           (18U)
#define CPU_CLKG1_SET_ECC_MASK                          (1UL << CPU_CLKG1_SET_ECC_POS)                  /*!< 0x00040000*/
#define CPU_CLKG1_SET_ECC                               CPU_CLKG1_SET_ECC_MASK                          /*!< set ecc clock gate makes the clock active*/
#define CPU_CLKG1_CLR_ECC_POS                           (19U)
#define CPU_CLKG1_CLR_ECC_MASK                          (1UL << CPU_CLKG1_CLR_ECC_POS)                  /*!< 0x00080000*/
#define CPU_CLKG1_CLR_ECC                               CPU_CLKG1_CLR_ECC_MASK                          /*!< clear ecc clock gate makes the clock inactive*/

/*****************  Bit definition for SYS_CPU SRST register  ********************/
#define CPU_SRST_SET_DMAC_N_POS                         (4U)
#define CPU_SRST_SET_DMAC_N_MASK                        (1UL << CPU_SRST_SET_DMAC_N_POS)                /*!< 0x00000010*/
#define CPU_SRST_SET_DMAC_N                             CPU_SRST_SET_DMAC_N_MASK                        /*!< */
#define CPU_SRST_CLR_DMAC_N_POS                         (5U)
#define CPU_SRST_CLR_DMAC_N_MASK                        (1UL << CPU_SRST_CLR_DMAC_N_POS)                /*!< 0x00000020*/
#define CPU_SRST_CLR_DMAC_N                             CPU_SRST_CLR_DMAC_N_MASK                        /*!< */
#define CPU_SRST_SET_CACHE_N_POS                        (6U)
#define CPU_SRST_SET_CACHE_N_MASK                       (1UL << CPU_SRST_SET_CACHE_N_POS)               /*!< 0x00000040*/
#define CPU_SRST_SET_CACHE_N                            CPU_SRST_SET_CACHE_N_MASK                       /*!< */
#define CPU_SRST_CLR_CACHE_N_POS                        (7U)
#define CPU_SRST_CLR_CACHE_N_MASK                       (1UL << CPU_SRST_CLR_CACHE_N_POS)               /*!< 0x00000080*/
#define CPU_SRST_CLR_CACHE_N                            CPU_SRST_CLR_CACHE_N_MASK                       /*!< */
#define CPU_SRST_SET_WDT_N_POS                          (8U)
#define CPU_SRST_SET_WDT_N_MASK                         (1UL << CPU_SRST_SET_WDT_N_POS)                 /*!< 0x00000100*/
#define CPU_SRST_SET_WDT_N                              CPU_SRST_SET_WDT_N_MASK                         /*!< */
#define CPU_SRST_CLR_WDT_N_POS                          (9U)
#define CPU_SRST_CLR_WDT_N_MASK                         (1UL << CPU_SRST_CLR_WDT_N_POS)                 /*!< 0x00000200*/
#define CPU_SRST_CLR_WDT_N                              CPU_SRST_CLR_WDT_N_MASK                         /*!< */
#define CPU_SRST_SET_TIM_N_POS                          (10U)
#define CPU_SRST_SET_TIM_N_MASK                         (1UL << CPU_SRST_SET_TIM_N_POS)                 /*!< 0x00000400*/
#define CPU_SRST_SET_TIM_N                              CPU_SRST_SET_TIM_N_MASK                         /*!< */
#define CPU_SRST_CLR_TIM_N_POS                          (11U)
#define CPU_SRST_CLR_TIM_N_MASK                         (1UL << CPU_SRST_CLR_TIM_N_POS)                 /*!< 0x00000800*/
#define CPU_SRST_CLR_TIM_N                              CPU_SRST_CLR_TIM_N_MASK                         /*!< */
#define CPU_SRST_SET_QSPI_N_POS                         (12U)
#define CPU_SRST_SET_QSPI_N_MASK                        (1UL << CPU_SRST_SET_QSPI_N_POS)                /*!< 0x00001000*/
#define CPU_SRST_SET_QSPI_N                             CPU_SRST_SET_QSPI_N_MASK                        /*!< */
#define CPU_SRST_CLR_QSPI_N_POS                         (13U)
#define CPU_SRST_CLR_QSPI_N_MASK                        (1UL << CPU_SRST_CLR_QSPI_N_POS)                /*!< 0x00002000*/
#define CPU_SRST_CLR_QSPI_N                             CPU_SRST_CLR_QSPI_N_MASK                        /*!< */
#define CPU_SRST_SET_UART2AHB_N_POS                     (20U)
#define CPU_SRST_SET_UART2AHB_N_MASK                    (1UL << CPU_SRST_SET_UART2AHB_N_POS)            /*!< 0x001000000*/
#define CPU_SRST_SET_UART2AHB_N                         CPU_SRST_SET_UART2AHB_N_MASK                    /*!< */
#define CPU_SRST_CLR_UAER2AHB_N_POS                     (21U)
#define CPU_SRST_CLR_UART2AHB_N_MASK                    (1UL << CPU_SRST_CLR_UAER2AHB_N_POS)            /*!< 0x00200000*/
#define CPU_SRST_CLR_UART2AHB_N                         CPU_SRST_CLR_UART2AHB_N_MASK                    /*!< */
#define CPU_SRST_SET_ECC_N_POS                          (22U)
#define CPU_SRST_SET_ECC_N_MASK                         (1UL << CPU_SRST_SET_ECC_N_POS)                 /*!< 0x004000000*/
#define CPU_SRST_SET_ECC_N                              CPU_SRST_SET_ECC_N_MASK                         /*!< */
#define CPU_SRST_CLR_ECC_N_POS                          (23U)
#define CPU_SRST_CLR_ECC_N_MASK                         (1UL << CPU_SRST_CLR_ECC_N_POS)                 /*!< 0x00800000*/
#define CPU_SRST_CLR_ECC_N                              CPU_SRST_CLR_ECC_N_MASK                         /*!< */

/*****************  Bit definition for SYS_CPU PS_EN register  ********************/
#define CPU_PSEN_QSPI_POS                               (0U)
#define CPU_PSEN_QSPI_MASK                              (0XFUL << CPU_PSEN_QSPI_POS)                    /*!< 0x00000001*/
#define CPU_PSEN_QSPI                                   CPU_PSEN_QSPI_MASK                              /*!< */
#define CPU_PSEN_SPIM0_POS                              (4U)
#define CPU_PSEN_SPIM0_MASK                             (1UL << CPU_PSEN_SPIM0_POS)                     /*!< 0x00000010*/
#define CPU_PSEN_SPIM0                                  CPU_PSEN_SPIM0_MASK                             /*!< */
#define CPU_PSEN_SPIM0_CS1_POS                          (5U)
#define CPU_PSEN_SPIM0_CS1_MASK                         (1UL << CPU_PSEN_SPIM0_CS1_POS)                 /*!< 0x00000020*/
#define CPU_PSEN_SPIM0_CS1                              CPU_PSEN_SPIM0_CS1_MASK                         /*!< */
#define CPU_PSEN_SPIM1_POS                              (6U)
#define CPU_PSEN_SPIM1_MASK                             (1UL << CPU_PSEN_SPIM1_POS)                     /*!< 0x00000040*/
#define CPU_PSEN_SPIM1                                  CPU_PSEN_SPIM1_MASK                             /*!< */
#define CPU_PSEN_SPIM1_CS1_POS                          (7U)
#define CPU_PSEN_SPIM1_CS1_MASK                         (1UL << CPU_PSEN_SPIM1_CS1_POS)                 /*!< 0x00000080*/
#define CPU_PSEN_SPIM1_CS1                              CPU_PSEN_SPIM1_CS1_MASK                         /*!< */
#define CPU_PSEN_SPIS_POS                               (8U)
#define CPU_PSEN_SPIS_MASK                              (1UL << CPU_PSEN_SPIS_POS)                      /*!< 0x00000100*/
#define CPU_PSEN_SPIS                                   CPU_PSEN_SPIS_MASK                              /*!< */
#define CPU_PSEN_GPIO00_POS                             (9U)
#define CPU_PSEN_GPIO00_MASK                            (1UL << CPU_PSEN_GPIO00_POS)                    /*!< 0x00000200*/
#define CPU_PSEN_GPIO00                                 CPU_PSEN_GPIO00_MASK                            /*!< */
#define CPU_PSEN_GPIO01_POS                             (10U)
#define CPU_PSEN_GPIO01_MASK                            (1UL << CPU_PSEN_GPIO01_POS)                    /*!< 0x00000400*/
#define CPU_PSEN_GPIO01                                 CPU_PSEN_GPIO01_MASK                            /*!< */
#define CPU_PSEN_GPIO14_POS                             (11U)
#define CPU_PSEN_GPIO14_MASK                            (1UL << CPU_PSEN_GPIO14_POS)                    /*!< 0x00000800*/
#define CPU_PSEN_GPIO14                                 CPU_PSEN_GPIO14_MASK                            /*!< */
#define CPU_PSEN_GPIO15_POS                             (12U)
#define CPU_PSEN_GPIO15_MASK                            (1UL << CPU_PSEN_GPIO15_POS)                    /*!< 0x00001000*/
#define CPU_PSEN_GPIO15                                 CPU_PSEN_GPIO15_MASK                            /*!< */
#define CPU_PSEN_RFIF_POS                               (13U)
#define CPU_PSEN_RFIF_MASK                              (1UL << CPU_PSEN_RFIF_POS)                      /*!< 0x00002000*/
#define CPU_PSEN_RFIF                                   CPU_PSEN_RFIF_MASK                              /*!< */
#define CPU_PSEN_BMD_POS                                (16U)
#define CPU_PSEN_BMD_MASK                               (0XFFUL << CPU_PSEN_BMD_POS)                    /*!< 0x00FF0000*/
#define CPU_PSEN_BMD                                    CPU_PSEN_BMD_MASK                               /*!< ble_mac_dbg_en*/

/*****************  Bit definition for SYS_CPU FIO_EN register  ********************/
#define CPU_FIOEN_POS                                   (0U)
#define CPU_FIOEN_MASK                                  (0X3FFFFUL << CPU_FIO_EN_POS)                   /*!< 0x0003FFFF*/
#define CPU_FIOEN                                       CPU_FIO_EN_MASK                                 /*!< */

/*****************  Bit definition for SYS_CPU FIO_SEL0 register  ********************/
#define CPU_FIOS0_IO00_POS                              (0U)
#define CPU_FIOS0_IO00_MASK                             (0XFUL << CPU_FIOS0_IO00_POS)                   /*!< 0x0000000F*/
#define CPU_FIOS0_IO00                                  CPU_FIOS0_IO00_MASK                             /*!< */
#define CPU_FIOS0_IO01_POS                              (4U)
#define CPU_FIOS0_IO01_MASK                             (0X0FUL << CPU_FIOS0_IO01_POS)                  /*!< 0x000000F0*/
#define CPU_FIOS0_IO01                                  CPU_FIOS0_IO01_MASK                             /*!< */
#define CPU_FIOS0_IO02_POS                              (8U)
#define CPU_FIOS0_IO02_MASK                             (0XFUL << CPU_FIOS0_IO02_POS)                   /*!< 0x00000F00*/
#define CPU_FIOS0_IO02                                  CPU_FIOS0_IO02_MASK                             /*!< */
#define CPU_FIOS0_IO03_POS                              (12U)
#define CPU_FIOS0_IO03_MASK                             (0XFUL << CPU_FIOS0_IO03_POS)                   /*!< 0x0000F000*/
#define CPU_FIOS0_IO03                                  CPU_FIOS0_IO03_MASK                             /*!< */
#define CPU_FIOS0_IO04_POS                              (16U)
#define CPU_FIOS0_IO04_MASK                             (0X0FUL << CPU_FIOS0_IO04_POS)                  /*!< 0x000F0000*/
#define CPU_FIOS0_IO04                                  CPU_FIOS0_IO04_MASK                             /*!< */
#define CPU_FIOS0_IO05_POS                              (20U)
#define CPU_FIOS0_IO05_MASK                             (0X0FUL << CPU_FIOS0_IO05_POS)                  /*!< 0x00F00000*/
#define CPU_FIOS0_IO05                                  CPU_FIOS0_IO05_MASK                             /*!< */
#define CPU_FIOS0_IO06_POS                              (24U)
#define CPU_FIOS0_IO06_MASK                             (0XFUL << CPU_FIOS0_IO06_POS)                   /*!< 0x0F000000*/
#define CPU_FIOS0_IO06                                  CPU_FIOS0_IO06_MASK                             /*!< */
#define CPU_FIOS0_IO07_POS                              (28U)
#define CPU_FIOS0_IO07_MASK                             (0XFUL << CPU_FIOS0_IO07_POS)                   /*!< 0xF0000000*/
#define CPU_FIOS0_IO07                                  CPU_FIOS0_IO07_MASK                             /*!< */

/*****************  Bit definition for SYS_CPU FIO_SEL1 register  ********************/
#define CPU_FIOS1_IO08_POS                              (0U)
#define CPU_FIOS1_IO08_MASK                             (0XFUL << CPU_FIOS1_IO08_POS)                   /*!< 0x0000000F*/
#define CPU_FIOS1_IO08                                  CPU_FIOS1_IO08_MASK                             /*!< */
#define CPU_FIOS1_IO09_POS                              (4U)
#define CPU_FIOS1_IO09_MASK                             (0XFUL << CPU_FIOS1_IO09_POS)                   /*!< 0x000000F0*/
#define CPU_FIOS1_IO09                                  CPU_FIOS1_IO09_MASK                             /*!< */
#define CPU_FIOS1_IO10_POS                              (8U)
#define CPU_FIOS1_IO10_MASK                             (0XFUL << CPU_FIOS1_IO10_POS)                   /*!< 0x00000F00*/
#define CPU_FIOS1_IO10                                  CPU_FIOS1_IO10_MASK                             /*!< */
#define CPU_FIOS1_IO11_POS                              (12U)
#define CPU_FIOS1_IO11_MASK                             (0XFUL << CPU_FIOS1_IO11_POS)                   /*!< 0x0000F000*/
#define CPU_FIOS1_IO11                                  CPU_FIOS1_IO11_MASK                             /*!< */
#define CPU_FIOS1_IO12_POS                              (16U)
#define CPU_FIOS1_IO12_MASK                             (0XFUL << CPU_FIOS1_IO12_POS)                   /*!< 0x000F0000*/
#define CPU_FIOS1_IO12                                  CPU_FIOS1_IO12_MASK                             /*!< */
#define CPU_FIOS1_IO13_POS                              (20U)
#define CPU_FIOS1_IO13_MASK                             (0XFUL << CPU_FIOS1_IO13_POS)                   /*!< 0x00F00000*/
#define CPU_FIOS1_IO13                                  CPU_FIOS1_IO13_MASK                             /*!< */
#define CPU_FIOS1_IO14_POS                              (24U)
#define CPU_FIOS1_IO14_MASK                             (0XFUL << CPU_FIOS1_IO14_POS)                   /*!< 0x0F000000*/
#define CPU_FIOS1_IO14                                  CPU_FIOS1_IO14_MASK                             /*!< */
#define CPU_FIOS1_IO15_POS                              (28U)
#define CPU_FIOS1_IO15_MASK                             (0XFUL << CPU_FIOS1_IO15_POS)                   /*!< 0xF0000000*/
#define CPU_FIOS1_IO15                                  CPU_FIOS1_IO15_MASK                             /*!< */

/*****************  Bit definition for SYS_CPU FIO_SEL2 register  ********************/
#define CPU_FIOS2_IO16_POS                              (0U)
#define CPU_FIOS2_IO16_MASK                             (0XFUL << CPU_FIOS2_IO16_POS)                   /*!< 0x0000000F*/
#define CPU_FIOS2_IO16                                  CPU_FIOS2_IO16_MASK                             /*!< */
#define CPU_FIOS2_IO17_POS                              (4U)
#define CPU_FIOS2_IO17_MASK                             (0XFUL << CPU_FIOS2_IO17_POS)                   /*!< 0x000000F0*/
#define CPU_FIOS2_IO17                                  CPU_FIOS2_IO17_MASK                             /*!< */
#define CPU_FIOS2_IO18_POS                              (8U)
#define CPU_FIOS2_IO18_MASK                             (0XFUL << CPU_FIOS2_IO18_POS)                   /*!< 0x00000F00*/
#define CPU_FIOS2_IO18                                  CPU_FIOS2_IO18_MASK                             /*!< */
#define CPU_FIOS2_IO19_POS                              (12U)
#define CPU_FIOS2_IO19_MASK                             (0XFUL << CPU_FIOS2_IO19_POS)                   /*!< 0x0000F000*/
#define CPU_FIOS2_IO19                                  CPU_FIOS2_IO19_MASK                             /*!< */
#define CPU_FIOS2_IO20_POS                              (16U)
#define CPU_FIOS2_IO20_MASK                             (0XFUL << CPU_FIOS2_IO20_POS)                   /*!< 0x000F0000*/
#define CPU_FIOS2_IO20                                  CPU_FIOS2_IO20_MASK                             /*!< */
#define CPU_FIOS2_IO21_POS                              (20U)
#define CPU_FIOS2_IO21_MASK                             (0XFUL << CPU_FIOS2_IO21_POS)                   /*!< 0x00F00000*/
#define CPU_FIOS2_IO21                                  CPU_FIOS2_IO21_MASK                             /*!< */

/*****************  Bit definition for SYS_CPU SCR register  ********************/
#define CPU_SCR_CACHE_HAS_SRAM_POS                      (0U)
#define CPU_SCR_CACHE_HAS_SRAM_MASK                     (1UL << CPU_SCR_CACHE_HAS_SRAM_POS)             /*!< 0x00000001*/
#define CPU_SCR_CACHE_HAS_SRAM                          CPU_SCR_CACHE_HAS_SRAM_MASK                     /*!< */
#define CPU_SCR_ADC_HAS_DMA_POS                         (1U)
#define CPU_SCR_ADC_HAS_DMA_MASK                        (1UL << CPU_SCR_ADC_HAS_DMA_POS)                /*!< 0x00000002*/
#define CPU_SCR_ADC_HAS_DMA                             CPU_SCR_ADC_HAS_DMA_MASK                        /*!< */
#define CPU_SCR_BLE_FREQ0_POS                           (8U)
#define CPU_SCR_BLE_FREQ0_MASK                          (0x3FUL << CPU_SCR_BLE_FREQ0_POS)               /*!< 0x00003F00*/
#define CPU_SCR_BLE_FREQ0                               CPU_SCR_BLE_FREQ0_MASK                          /*!< */
#define CPU_SCR_BLE_FREQ1_POS                           (16U)
#define CPU_SCR_BLE_FREQ1_MASK                          (0X3FUL << CPU_SCR_BLE_FREQ1_POS)               /*!< 0x003F0000*/
#define CPU_SCR_BLE_FREQ1                               CPU_SCR_BLE_FREQ1_MASK                          /*!< */

/*****************  Bit definition for SYS_CPU SFT_INTR register  ********************/
#define CPU_SFT_INTR_POS                                (0U)
#define CPU_SFT_INTR_MASK                               (1UL << CPU_SFT_INTR_POS)                       /*!< 0x00000001*/
#define CPU_SFT_INTR                                    CPU_SFT_INTR_MASK                               /*!< */

/*****************  Bit definition for SYS_CPU CALB32 register  ********************/
#define CPU_CAL32K_START_POS                            (0U)
#define CPU_CAL32K_START_MASK                           (1UL << CPU_CAL32K_START_POS)                   /*!< 0x00000001*/
#define CPU_CAL32K_START                                CPU_CAL32K_START_MASK                           /*!< */
#define CPU_CAL32K_RSLT_POS                             (12U)
#define CPU_CAL32K_RSLT_MASK                            (0X3FFFFUL << CPU_CAL32K_RSLT_POS)              /*!< 0x3FFFF000*/
#define CPU_CAL32K_RSLT                                 CPU_CAL32K_RSLT_MASK                            /*!< */

/*****************  Bit definition for SYS_CPU PSA0L register  ********************/
#define CPU_PSA0L_PGSPY_ADDR0_L_POS                     (0U)
#define CPU_PSA0L_PGSPY_ADDR0_L_MASK                    (0XFFFFFFUL << CPU_PSA0L_PGSPY_ADDR0_L_POS)     /*!< 0x00FFFFFF*/
#define CPU_PSA0L_PGSPY_ADDR0_L                         CPU_PSA0L_PGSPY_ADDR0_L_MASK                    /*!< */

/*****************  Bit definition for SYS_CPU PSA0H register  ********************/
#define CPU_PSA0H_PGSPY_ADDR0_H_POS                     (0U)
#define CPU_PSA0H_PGSPY_ADDR0_H_MASK                    (0XFFFFFFUL << CPU_PSA0H_PGSPY_ADDR0_H_POS)     /*!< 0x00FFFFFF*/
#define CPU_PSA0H_PGSPY_ADDR0_H                         CPU_PSA0H_PGSPY_ADDR0_H_MASK                    /*!< */

/*****************  Bit definition for SYS_CPU PSA1L register  ********************/
#define CPU_PSA1L_PGSPY_ADDR1_L_POS                     (0U)
#define CPU_PSA1L_PGSPY_ADDR1_L_MASK                    (0XFFFFFFUL << CPU_PSA1L_PGSPY_ADDR1_L_POS)     /*!< 0x00FFFFFF*/
#define CPU_PSA1L_PGSPY_ADDR1_L                         CPU_PSA1L_PGSPY_ADDR1_L_MASK                    /*!< */

/*****************  Bit definition for SYS_CPU PSA1H register  ********************/
#define CPU_PSA1H_PGSPY_ADDR1_H_POS                     (0U)
#define CPU_PSA1H_PGSPY_ADDR1_H_MASK                    (0XFFFFFFUL << CPU_PSA1H_PGSPY_ADDR1_H_POS)     /*!< 0x00FFFFFF*/
#define CPU_PSA1H_PGSPY_ADDR1_H                         CPU_PSA1H_PGSPY_ADDR1_H_MASK                    /*!< */

/*****************  Bit definition for SYS_CPU PSI_EN register  ********************/
#define CPU_PSIE_PGSPY_POS                              (0U)
#define CPU_PSIE_PGSPY_MASK                             (3UL << CPU_PSIE_PGSPY_POS)                   /*!< 0x00000003*/
#define CPU_PSIE_PGSPY                                  CPU_PSIE_PGSPY_MASK                           /*!< */

/*****************  Bit definition for SYS_CPU PSIM register  ********************/
#define CPU_PSIM_PGSPY_INTR_MASK_POS                    (0U)
#define CPU_PSIM_PGSPY_INTR_MASK_MASK                   (3UL << CPU_PSIM_PGSPY_INTR_MASK_POS)           /*!< 0x00000003*/
#define CPU_PSIM_PGSPY_INTR_MASK                        CPU_PSIM_PGSPY_INTR_MASK_MASK                   /*!< */

/*****************  Bit definition for SYS_CPU PSIR register  ********************/
#define CPU_PSRI_PGSPY_INTR_RAW_POS                     (0U)
#define CPU_PSRI_PGSPY_INTR_RAW_MASK                    (3UL << CPU_PSRI_PGSPY_INTR_RAW_POS)            /*!< 0x00000003*/
#define CPU_PSRI_PGSPY_INTR_RAW                             CPU_PSRI_PGSPY_INTR_RAW_MASK                    /*!< */

/*****************  Bit definition for SYS_CPU PSI register  ********************/
#define CPU_PSI_PGSPY_INTR_POS                          (0U)
#define CPU_PSI_PGSPY_INTR_MASK                         (3UL << CPU_PSI_PGSPY_INTR_POS)                /*!< 0x00000003*/
#define CPU_PSI_PGSPY_INTR                              CPU_PSI_PGSPY_INTR_MASK                        /*!< */

/* value definition ----------------------------------------------------------*/

/***************  type definition for function io (fio_type)  *****************/
#define CPU_FIO_TYPE_UART0_TX                               ((uint32_t)0UL)
#define CPU_FIO_TYPE_UART0_RX                               ((uint32_t)1UL)
#define CPU_FIO_TYPE_UART0_CTS                              ((uint32_t)2UL)
#define CPU_FIO_TYPE_UART0_RTS                              ((uint32_t)3UL)
#define CPU_FIO_TYPE_UART1_TX                               ((uint32_t)4UL)
#define CPU_FIO_TYPE_UART1_RX                               ((uint32_t)5UL)
#define CPU_FIO_TYPE_IIC0_SCL                               ((uint32_t)6UL)
#define CPU_FIO_TYPE_IIC0_SDA                               ((uint32_t)7UL)
#define CPU_FIO_TYPE_IIC1_SCL                               ((uint32_t)8UL)
#define CPU_FIO_TYPE_IIC1_SDA                               ((uint32_t)9UL)
#define CPU_FIO_TYPE_PWM0                                   ((uint32_t)10UL)
#define CPU_FIO_TYPE_PWM1                                   ((uint32_t)11UL)
#define CPU_FIO_TYPE_PWM2                                   ((uint32_t)12UL)
#define CPU_FIO_TYPE_PWM3                                   ((uint32_t)13UL)
#define CPU_FIO_TYPE_PWM4                                   ((uint32_t)14UL)

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_SYSC_PER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

