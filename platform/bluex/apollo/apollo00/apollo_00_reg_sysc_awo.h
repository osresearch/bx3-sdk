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
#ifndef __APOLLO_00_REG_SYSC_AWO_H__
#define __APOLLO_00_REG_SYSC_AWO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

typedef struct {
    __IO uint32_t MISC;                 /* <! CLK INTRP Register                            0x0000 */
    __IO uint32_t CLKG;                 /* <! clk gate Register                             0x0004 */
    __IO uint32_t IOSC;                 /* <! IO state control Register                     0x0008 */
    __IO uint32_t PDOF;                 /* <! SW control PD Register                        0x000C */
    __IO uint32_t SRAMRET;              /* <! SRAM retention Register                       0x0010 */
    __IO uint32_t PMUTIM;               /* <! PMU timer Register                            0x0014 */
    __IO uint32_t WSM;                  /* <! wakeup source mask Register                   0x0018 */
    __IO uint32_t LCC;                  /* <! LDO and CLK control Register                  0x001C */
    __I  uint32_t PDS;                  /* <! PD state Register                             0x0020 */
    __IO uint32_t EICFG;                /* <! external interrupt config Register            0x0024 */
    __IO uint32_t EIVAL;                /* <! external interrupt value Register.            0x0028 */
    __IO uint32_t EICLR;                /* <! external interrupt clear Register.            0x002C */
    __I  uint32_t BLELPIV ;             /* <! blelp interrupt value Register                0x0030 */
    __IO uint32_t BLELPIC;              /* <! blelp interrupt clear Register .              0x0034 */
    __IO uint32_t CLKG1;                /* <! clkgen_awo_signal 1.                          0x0038 */
    __IO uint32_t CLKG2;                /* <! clkgen_awo_signal 2.                          0x003C */
    __IO uint32_t SRST;                 /* <! software reset signals                        0x0040 */
    __IO uint32_t RAMP;                 /* <! ram parameter .                               0x0044 */
    __IO uint32_t VDDV;                 /* <! vdd_value.                                    0x0048 */
    __IO uint32_t GPIODS0;              /* <! gpio Drive select 0.                          0x004C */
    __IO uint32_t GPIODS1;              /* <! gpio Drive select 1.                          0x0050 */
    __IO uint32_t GPIOIE;               /* <! gpio input enable.                            0x0054 */
    __IO uint32_t GPIOIS;               /* <! gpio input select.                            0x0058 */
    __IO uint32_t GPIOPE;               /* <! gpio pull enable.                             0x005C */
    __IO uint32_t GPIOPS;               /* <! gpio pull select.                             0x0060 */
    __IO uint32_t TCFG1;                /* <! touch_cfg 1.                                  0x0064 */
    __IO uint32_t TCFG2;                /* <! touch_cfg 2.                                  0x0068 */
    __IO uint32_t TCFG3;                /* <! touch_cfg 3.                                  0x006C */
    __IO uint32_t RFR0;                 /* <! rf_reg_0.                                     0x0070 */
    __IO uint32_t RFR1;                 /* <! rf_reg_1.                                     0x0074 */
    __IO uint32_t RFR2;                 /* <! rf_reg_2.                                     0x0078 */
    __IO uint32_t RFR3;                 /* <! rf_reg_3.                                     0x007C */
    __IO uint32_t RFR4;                 /* <! rf_reg_4.                                     0x0080 */
    __IO uint32_t RFR5;                 /* <! rf_reg_5.                                     0x0084 */
    __IO uint32_t RFR6;                 /* <! rf_reg_6.                                     0x0088 */
    __IO uint32_t RFR7;                 /* <! rf_reg_7.                                     0x008C */
    __IO uint32_t RFR8;                 /* <! rf_reg_8.                                     0x0090 */
    __IO uint32_t RFR9;                 /* <! rf_reg_9.                                     0x0094 */
    __IO uint32_t RFRA;                 /* <! rf_reg_a.                                     0x0098 */
    __IO uint32_t RFRB;                 /* <! rf_reg_b.                                     0x009C */
    __IO uint32_t RFRC;                 /* <! rf_reg_c.                                     0x00A0 */
    __IO uint32_t RFRD;                 /* <! rf_reg_d.                                     0x00A4 */
    __IO uint32_t RFRE;                 /* <! rf_reg_e.                                     0x00A8 */
    __IO uint32_t RFRF;                 /* <! rf_reg_f.                                     0x00AC */
    __I  uint32_t RFRRD;                /* <! rf_reg_rd.                                    0x00B0 */
         uint32_t reserved0[3];         /* <!                                               0x00B4 */
    __IO uint32_t PP0;                  /* <! pulse width in 32KHz clock for power PWM 0    0x00C0 */
    __IO uint32_t PP1;                  /* <! pulse width in 32KHz clock for power PWM 1    0x00C4 */
    __IO uint32_t PP2;                  /* <! pulse width in 32KHz clock for power PWM 2    0x00C8 */
    __IO uint32_t PPC;                  /* <! power of pwm control .                        0x00CC */
    __I  uint32_t BM;                   /* <! boot mode.                                    0x00D0 */
} reg_sysc_awo_t;

/* exported variables --------------------------------------------------------*/

/*****************  Bit definition for AWO_MISC register  ***********************/
#define AWO_MISC_CS_HBUS0_POS                           (0U)
#define AWO_MISC_CS_HBUS0_MASK                          (0x7UL << AWO_MISC_CS_HBUS0_POS)
#define AWO_MISC_CS_HBUS0                               AWO_MISC_CS_HBUS0_MASK

#define AWO_MISC_CS_HBUS0_T_NONE                        (0x0UL << AWO_MISC_CS_HBUS0_POS)
#define AWO_MISC_CS_HBUS0_T_32M                         (0x1UL << AWO_MISC_CS_HBUS0_POS)
#define AWO_MISC_CS_HBUS0_T_32M_OR_PLL                  (0x2UL << AWO_MISC_CS_HBUS0_POS)
#define AWO_MISC_CS_HBUS0_T_32K                         (0x4UL << AWO_MISC_CS_HBUS0_POS)

#define AWO_MISC_CS_HBUS1_POS                           (3U)
#define AWO_MISC_CS_HBUS1_MASK                          (0x3UL << AWO_MISC_CS_HBUS1_POS)
#define AWO_MISC_CS_HBUS1                               AWO_MISC_CS_HBUS1_MASK
#define AWO_MISC_BLE_LP_IE_POS                          (5U)
#define AWO_MISC_BLE_LP_IE_MASK                         (0x3UL << AWO_MISC_BLE_LP_IE_POS)
#define AWO_MISC_BLE_LP_IE                              AWO_MISC_BLE_LP_IE_MASK
#define AWO_MISC_PMU_EN_POS                             (7U)
#define AWO_MISC_PMU_EN_MASK                            (0x1UL << AWO_MISC_PMU_EN_POS)
#define AWO_MISC_PMU_EN                                 AWO_MISC_PMU_EN_MASK
#define AWO_MISC_AHB_CDP_POS                            (8U)
#define AWO_MISC_AHB_CDP_MASK                           (0xFFUL << AWO_MISC_AHB_CDP_POS)
#define AWO_MISC_AHB_CDP                                AWO_MISC_AHB_CDP_MASK
#define AWO_MISC_APB_CDP_POS                            (16U)
#define AWO_MISC_APB_CDP_MASK                           (0x0FUL << AWO_MISC_APB_CDP_POS)
#define AWO_MISC_APB_CDP                                AWO_MISC_APB_CDP_MASK
#define AWO_MISC_I_WICENCK_POS                          (21U)
#define AWO_MISC_I_WICENCK_MASK                         (0x1UL << AWO_MISC_I_WICENCK_POS)
#define AWO_MISC_I_WICENCK                              AWO_MISC_I_WICENCK_MASK
#define AWO_MSIC_CPU_RET_EN_POS                         (22U)
#define AWO_MSIC_CPU_RET_EN_MASK                        (0x1UL << AWO_MSIC_CPU_RET_EN_POS)
#define AWO_MSIC_CPU_RET_EN                             AWO_MSIC_CPU_RET_EN_MASK
#define AWO_MSIC_BLE_MAC_RET_EN_POS                     (23U)
#define AWO_MSIC_BLE_MAC_RET_EN_MASK                    (0x1UL << AWO_MSIC_BLE_MAC_RET_EN_POS)
#define AWO_MSIC_BLE_MAC_RET_EN                         AWO_MSIC_BLE_MAC_RET_EN_MASK

/*****************  Bit definition for AWO_CLKG register  ***********************/
#define AWO_CLKG_SET_BLE_LP_POS                         (0U)
#define AWO_CLKG_SET_BLE_LP_MASK                        (0x1UL << AWO_CLKG_SET_BLE_LP_POS)
#define AWO_CLKG_SET_BLE_LP                             AWO_CLKG_SET_BLE_LP_MASK
#define AWO_CLKG_SET_RTC_POS                            (2U)
#define AWO_CLKG_SET_RTC_MASK                           (0x1UL << AWO_CLKG_SET_RTC_POS)
#define AWO_CLKG_SET_RTC                                AWO_CLKG_SET_RTC_MASK
#define AWO_CLKG_SET_AHB_PLL_DIV_POS                    (4U)
#define AWO_CLKG_SET_AHB_PLL_DIV_MASK                   (0x1UL << AWO_CLKG_SET_AHB_PLL_DIV_POS)
#define AWO_CLKG_SET_AHB_PLL_DIV                        AWO_CLKG_SET_AHB_PLL_DIV_MASK
#define AWO_CLKG_SET_AHB_32M_DIV_POS                    (6U)
#define AWO_CLKG_SET_AHB_32M_DIV_MASK                   (0x1UL << AWO_CLKG_SET_AHB_32M_DIV_POS)
#define AWO_CLKG_SET_AHB_32M_DIV                        AWO_CLKG_SET_AHB_32M_DIV_MASK
#define AWO_CLKG_SET_WIC_POS                            (8U)
#define AWO_CLKG_SET_WIC_MASK                           (0x1UL << AWO_CLKG_SET_WIC_POS)
#define AWO_CLKG_SET_WIC                                AWO_CLKG_SET_WIC_MASK
#define AWO_CLKG_SET_BLE_POS                            (10U)
#define AWO_CLKG_SET_BLE_MASK                           (0x1UL << AWO_CLKG_SET_BLE_POS)
#define AWO_CLKG_SET_BLE                                AWO_CLKG_SET_BLE_MASK
#define AWO_CLKG_SET_BLE_MAC_DIV_POS                    (12U)
#define AWO_CLKG_SET_BLE_MAC_DIV_MASK                   (0x1UL << AWO_CLKG_SET_BLE_MAC_DIV_POS)
#define AWO_CLKG_SET_BLE_MAC_DIV                        AWO_CLKG_SET_BLE_MAC_DIV_MASK
#define AWO_CLKG_SET_BLE_MDM_RX_DIV_POS                 (14U)
#define AWO_CLKG_SET_BLE_MDM_RX_DIV_MASK                (0x1UL << AWO_CLKG_SET_BLE_MDM_RX_DIV_POS)
#define AWO_CLKG_SET_BLE_MDM_RX_DIV                     AWO_CLKG_SET_BLE_MDM_RX_DIV_MASK

#define AWO_CLKG_CLR_BLE_LP_POS                         (1U)
#define AWO_CLKG_CLR_BLE_LP_MASK                        (0x1UL << AWO_CLKG_CLR_BLE_LP_POS)
#define AWO_CLKG_CLR_BLE_LP                             AWO_CLKG_CLR_BLE_LP_MASK
#define AWO_CLKG_CLR_RTC_POS                            (3U)
#define AWO_CLKG_CLR_RTC_MASK                           (0x1UL << AWO_CLKG_CLR_RTC_POS)
#define AWO_CLKG_CLR_RTC                                AWO_CLKG_CLR_RTC_MASK
#define AWO_CLKG_CLR_AHB_PLL_DIV_POS                    (5U)
#define AWO_CLKG_CLR_AHB_PLL_DIV_MASK                   (0x1UL << AWO_CLKG_CLR_AHB_PLL_DIV_POS)
#define AWO_CLKG_CLR_AHB_PLL_DIV                        AWO_CLKG_CLR_AHB_PLL_DIV_MASK
#define AWO_CLKG_CLR_AHB_32M_DIV_POS                    (7U)
#define AWO_CLKG_CLR_AHB_32M_DIV_MASK                   (0x1UL << AWO_CLKG_CLR_AHB_32M_DIV_POS)
#define AWO_CLKG_CLR_AHB_32M_DIV                        AWO_CLKG_CLR_AHB_32M_DIV_MASK
#define AWO_CLKG_CLR_WIC_POS                            (9U)
#define AWO_CLKG_CLR_WIC_MASK                           (0x1UL << AWO_CLKG_CLR_WIC_POS)
#define AWO_CLKG_CLR_WIC                                AWO_CLKG_CLR_WIC_MASK
#define AWO_CLKG_CLR_BLE_POS                            (11U)
#define AWO_CLKG_CLR_BLE_MASK                           (0x1UL << AWO_CLKG_CLR_BLE_POS)
#define AWO_CLKG_CLR_BLE                                AWO_CLKG_CLR_BLE_MASK
#define AWO_CLKG_CLR_BLE_MAC_DIV_POS                    (13U)
#define AWO_CLKG_CLR_BLE_MAC_DIV_MASK                   (0x1UL << AWO_CLKG_CLR_BLE_MAC_DIV_POS)
#define AWO_CLKG_CLR_BLE_MAC_DIV                        AWO_CLKG_CLR_BLE_MAC_DIV_MASK
#define AWO_CLKG_CLR_BLE_MDM_RX_DIV_POS                 (15U)
#define AWO_CLKG_CLR_BLE_MDM_RX_DIV_MASK                (0x1UL << AWO_CLKG_CLR_BLE_MDM_RX_DIV_POS)
#define AWO_CLKG_CLR_BLE_MDM_RX_DIV                     AWO_CLKG_CLR_BLE_MDM_RX_DIV_MASK

/*****************  Bit definition for AWO_IOSC register  ***********************/
#define AWO_IOSC_STA_RET_POS                            (0U)
#define AWO_IOSC_STA_RET_MASK                           (0x1UL << AWO_IOSC_STA_RET_POS)
#define AWO_IOSC_STA_RET                                AWO_IOSC_STA_RET_MASK
#define AWO_IOSC_STA_UNRET_POS                          (1U)
#define AWO_IOSC_STA_UNRET_MASK                         (0x1UL << AWO_IOSC_STA_UNRET_POS)
#define AWO_IOSC_STA_UNRET                              AWO_IOSC_STA_UNRET_MASK
#define AWO_IOSC_CTRL_SEL_POS                           (2U)
#define AWO_IOSC_CTRL_SEL_MASK                          (0x1UL << AWO_IOSC_CTRL_SEL_POS)
#define AWO_IOSC_CTRL_SEL                               AWO_IOSC_CTRL_SEL_MASK
#define AWO_IOSC_STA_CAP_POS                            (3U)
#define AWO_IOSC_STA_CAP_MASK                           (0x1UL << AWO_IOSC_STA_CAP_POS)
#define AWO_IOSC_STA_CAP                                AWO_IOSC_STA_CAP_MASK

/*****************  Bit definition for AWO_PDOF register  ***********************/
#define AWO_PDOF_SRAM_OFF_BY_PMU_POS                    (0U)
#define AWO_PDOF_SRAM_OFF_BY_PMU_MASK                   (0x7FUL << AWO_PDOF_SRAM_OFF_BY_PMU_POS)
#define AWO_PDOF_SRAM_OFF_BY_PMU                        AWO_PDOF_SRAM_OFF_BY_PMU_MASK
#define AWO_PDOF_BLE_MAC_OFF_BY_PMU_POS                 (8U)
#define AWO_PDOF_BLE_MAC_OFF_BY_PMU_MASK                (0x1UL << AWO_PDOF_BLE_MAC_OFF_BY_PMU_POS)
#define AWO_PDOF_BLE_MAC_OFF_BY_PMU                     AWO_PDOF_BLE_MAC_OFF_BY_PMU_MASK
#define AWO_PDOF_BLE_RF_OFF_BY_PMU_POS                  (9U)
#define AWO_PDOF_BLE_RF_OFF_BY_PMU_MASK                 (0x1UL << AWO_PDOF_BLE_RF_OFF_BY_PMU_POS)
#define AWO_PDOF_BLE_RF_OFF_BY_PMU                      AWO_PDOF_BLE_RF_OFF_BY_PMU_MASK
#define AWO_PDOF_PER_OFF_BY_PMU_POS                     (10U)
#define AWO_PDOF_PER_OFF_BY_PMU_MASK                    (0x1UL << AWO_PDOF_PER_OFF_BY_PMU_POS)
#define AWO_PDOF_PER_OFF_BY_PMU                         AWO_PDOF_PER_OFF_BY_PMU_MASK
#define AWO_PDOF_SRAM_ON_BY_PMU_POS                     (16U)
#define AWO_PDOF_SRAM_ON_BY_PMU_MASK                    (0x7FUL << AWO_PDOF_SRAM_ON_BY_PMU_POS)
#define AWO_PDOF_SRAM_ON_BY_PMU                         AWO_PDOF_SRAM_ON_BY_PMU_MASK
#define AWO_PDOF_BLE_MAC_ON_BY_PMU_POS                  (24U)
#define AWO_PDOF_BLE_MAC_ON_BY_PMU_MASK                 (0x1UL << AWO_PDOF_BLE_MAC_ON_BY_PMU_POS)
#define AWO_PDOF_BLE_MAC_ON_BY_PMU                      AWO_PDOF_BLE_MAC_ON_BY_PMU_MASK
#define AWO_PDOF_BLE_RF_ON_BY_PMU_POS                   (25U)
#define AWO_PDOF_BLE_RF_ON_BY_PMU_MASK                  (0x1UL << AWO_PDOF_BLE_RF_ON_BY_PMU_POS)
#define AWO_PDOF_BLE_RF_ON_BY_PMU                       AWO_PDOF_BLE_RF_ON_BY_PMU_MASK
#define AWO_PDOF_PER_ON_BY_PMU_POS                      (26U)
#define AWO_PDOF_PER_ON_BY_PMU_MASK                     (0x1UL << AWO_PDOF_PER_ON_BY_PMU_POS)
#define AWO_PDOF_PER_ON_BY_PMU                          AWO_PDOF_PER_ON_BY_PMU_MASK
#define AWO_PDOF_OFF_POS                                (30U)
#define AWO_PDOF_OFF_MASK                               (0x1UL << AWO_PDOF_OFF_POS)
#define AWO_PDOF_OFF                                    AWO_PDOF_OFF_MASK
#define AWO_PDOF_ON_POS                                 (31U)
#define AWO_PDOF_ON_MASK                                (0x1UL << AWO_PDOF_ON_POS)
#define AWO_PDOF_ON                                     AWO_PDOF_ON_MASK

/*****************  Bit definition for AWO_PMUTIM register  ***********************/
#define AWO_SRAMRET_REQ_POS                             (0U)
#define AWO_SRAMRET_REQ_MASK                            (0x7FUL << AWO_SRAMRET_REQ_POS)
#define AWO_SRAMRET_REQ                                 AWO_SRAMRET_REQ_MASK
#define AWO_SRAMRET_VDD_POS                             (16U)
#define AWO_SRAMRET_VDD_MASK                            (0xFUL << AWO_SRAMRET_VDD_POS)
#define AWO_SRAMRET_VDD                                 AWO_SRAMRET_VDD_MASK
#define AWO_SRAMRET_LS_EN_POS                           (24U)
#define AWO_SRAMRET_LS_EN_MASK                          (0x7FUL << AWO_SRAMRET_LS_EN_POS)
#define AWO_SRAMRET_LS_EN                               AWO_SRAMRET_LS_EN_MASK

/*****************  Bit definition for AWO_SRAMRET register  ***********************/
#define AWO_PMUTIM_LDO_STB_DLY_POS                      (0U)
#define AWO_PMUTIM_LDO_STB_DLY_MASK                     (0x1FUL << AWO_PMUTIM_LDO_STB_DLY_POS)
#define AWO_PMUTIM_LDO_STB_DLY                          AWO_PMUTIM_LDO_STB_DLY_MASK
#define AWO_PMUTIM_OSC_STB_DLY_POS                      (8U)
#define AWO_PMUTIM_OSC_STB_DLY_MASK                     (0x3FUL << AWO_PMUTIM_OSC_STB_DLY_POS)
#define AWO_PMUTIM_OSC_STB_DLY                          AWO_PMUTIM_OSC_STB_DLY_MASK
#define AWO_PMUTIM_LDO_SWC_DLY_POS                      (16U)
#define AWO_PMUTIM_LDO_SWC_DLY_MASK                     (0x0FUL << AWO_PMUTIM_LDO_SWC_DLY_POS)
#define AWO_PMUTIM_LDO_SWC_DLY                          AWO_PMUTIM_LDO_SWC_DLY_MASK
#define AWO_PMUTIM_CLK_SWC_DLY_POS                      (20U)
#define AWO_PMUTIM_CLK_SWC_DLY_MASK                     (0x0FUL << AWO_PMUTIM_CLK_SWC_DLY_POS)
#define AWO_PMUTIM_CLK_SWC_DLY                          AWO_PMUTIM_CLK_SWC_DLY_MASK
#define AWO_PMUTIM_REQ_TIME_POS                         (24U)
#define AWO_PMUTIM_REQ_TIME_MASK                        (0xFFUL << AWO_PMUTIM_REQ_TIME_POS)
#define AWO_PMUTIM_REQ_TIME                             AWO_PMUTIM_REQ_TIME_MASK

/*****************  Bit definition for AWO_WSM register  ***********************/
#define AWO_WSM_LDO_STEUP_TIME_POS                      (0U)
#define AWO_WSM_LDO_STEUP_TIME_MASK                     (0xFFUL << AWO_WSM_LDO_STEUP_TIME_POS)
#define AWO_WSM_LDO_STEUP_TIME                          AWO_WSM_LDO_STEUP_TIME_MASK
#define AWO_WSM_TOUCH_LDO_STB_DLY_POS                   (8U)
#define AWO_WSM_TOUCH_LDO_STB_DLY_MASK                  (0x0FUL << AWO_WSM_TOUCH_LDO_STB_DLY_POS)
#define AWO_WSM_TOUCH_LDO_STB_DLY                       AWO_WSM_TOUCH_LDO_STB_DLY_MASK

/*****************  Bit definition for AWO_LCC register  ***********************/
#define AWO_LCC_DR_PMU_CS_POS                           (0U)
#define AWO_LCC_DR_PMU_CS_MASK                          (0x1UL << AWO_LCC_DR_PMU_CS_POS)
#define AWO_LCC_DR_PMU_CS                               AWO_LCC_DR_PMU_CS_MASK
#define AWO_LCC_DR_PMU_LS_POS                           (1U)
#define AWO_LCC_DR_PMU_LS_MASK                          (0x1UL << AWO_LCC_DR_PMU_LS_POS)
#define AWO_LCC_DR_PMU_LS                               AWO_LCC_DR_PMU_LS_MASK
#define AWO_LCC_DR_NORM_LDO_EN_POS                      (2U)
#define AWO_LCC_DR_NORM_LDO_EN_MASK                     (0x1UL << AWO_LCC_DR_NORM_LDO_EN_POS)
#define AWO_LCC_DR_NORM_LDO_EN                          AWO_LCC_DR_NORM_LDO_EN_MASK
#define AWO_LCC_DR_32M_RC_OSC_EN_POS                    (4U)
#define AWO_LCC_DR_32M_RC_OSC_EN_MASK                   (0x1UL << AWO_LCC_DR_32M_RC_OSC_EN_POS)
#define AWO_LCC_DR_32M_RC_OSC_EN                        AWO_LCC_DR_32M_RC_OSC_EN_MASK

#define AWO_LCC_REG_PMU_CS_POS                          (8U)
#define AWO_LCC_REG_PMU_CS_MASK                         (0x1UL << AWO_LCC_REG_PMU_CS_POS)
#define AWO_LCC_REG_PMU_CS                              AWO_LCC_REG_PMU_CS_MASK
#define AWO_LCC_REG_PMU_LS_POS                          (9U)
#define AWO_LCC_REG_PMU_LS_MASK                         (0x1UL << AWO_LCC_REG_PMU_LS_POS)
#define AWO_LCC_REG_PMU_LS                              AWO_LCC_REG_PMU_LS_MASK
#define AWO_LCC_REG_NORM_LDO_EN_POS                     (10U)
#define AWO_LCC_REG_NORM_LDO_EN_MASK                    (0x1UL << AWO_LCC_REG_NORM_LDO_EN_POS)
#define AWO_LCC_REG_NORM_LDO_EN                         AWO_LCC_REG_NORM_LDO_EN_MASK
#define AWO_LCC_REG_32M_RC_OSC_EN_POS                   (12U)
#define AWO_LCC_REG_32M_RC_OSC_EN_MASK                  (0x1UL << AWO_LCC_REG_32M_RC_OSC_EN_POS)
#define AWO_LCC_REG_32M_RC_OSC_EN                       AWO_LCC_REG_32M_RC_OSC_EN_MASK

#define AWO_LCC_32M_SRC_SEL_POS                         (16U)
#define AWO_LCC_32M_SRC_SEL_MASK                        (0x1UL << AWO_LCC_32M_SRC_SEL_POS)
#define AWO_LCC_32M_SRC_SEL                             AWO_LCC_32M_SRC_SEL_MASK
#define AWO_LCC_32M_SRC_SEL_T_RC                        ( (uint32_t)0x01 << AWO_LCC_32M_SRC_SEL_POS )
#define AWO_LCC_32M_SRC_SEL_T_XTAL                      ( (uint32_t)0x00 << AWO_LCC_32M_SRC_SEL_POS )

#define AWO_LCC_32M_XTAL_EN_POS                         (17U)
#define AWO_LCC_32M_XTAL_EN_MASK                        (0x1UL << AWO_LCC_32M_XTAL_EN_POS)
#define AWO_LCC_32M_XTAL_EN                             AWO_LCC_32M_XTAL_EN_MASK

#define AWO_LCC_32K_SRC_SEL_POS                         (18U)
#define AWO_LCC_32K_SRC_SEL_MASK                        (0x1UL << AWO_LCC_32K_SRC_SEL_POS)
#define AWO_LCC_32K_SRC_SEL                             AWO_LCC_32K_SRC_SEL_MASK
#define AWO_LCC_32K_SRC_SEL_T_RC                        ( (uint32_t)0x00 << AWO_LCC_32K_SRC_SEL_POS )
#define AWO_LCC_32K_SRC_SEL_T_XTAL                      ( (uint32_t)0x01 << AWO_LCC_32K_SRC_SEL_POS )

#define AWO_LCC_32K_XTAL_EN_POS                         (19U)
#define AWO_LCC_32K_XTAL_EN_MASK                        (0x1UL << AWO_LCC_32K_XTAL_EN_POS)
#define AWO_LCC_32K_XTAL_EN                             AWO_LCC_32K_XTAL_EN_MASK
#define AWO_LCC_32K_RCOSC_EN_POS                        (20U)
#define AWO_LCC_32K_RCOSC_EN_MASK                       (0x1UL << AWO_LCC_32K_RCOSC_EN_POS)
#define AWO_LCC_32K_RCOSC_EN                            AWO_LCC_32K_RCOSC_EN_MASK

/*****************  Bit definition for AWO_PDS register  ***********************/
#define AWO_PDS_SRAM_REQ_POS                            (0U)
#define AWO_PDS_SRAM_REQ_MASK                           (0x7FUL << AWO_PDS_SRAM_REQ_POS)
#define AWO_PDS_SRAM_REQ                                AWO_PDS_SRAM_REQ_MASK
#define AWO_PDS_BLE_MAC_REQ_POS                         (8U)
#define AWO_PDS_BLE_MAC_REQ_MASK                        (0x1UL << AWO_PDS_BLE_MAC_REQ_POS)
#define AWO_PDS_BLE_MAC_REQ                             AWO_PDS_BLE_MAC_REQ_MASK
#define AWO_PDS_PERC_REQ_POS                            (10U)
#define AWO_PDS_PERC_REQ_MASK                           (0x1UL << AWO_PDS_PERC_REQ_POS)
#define AWO_PDS_PERC_REQ                                AWO_PDS_PERC_REQ_MASK
#define AWO_PDS_CPU_REQ_POS                             (11U)
#define AWO_PDS_CPU_REQ_MASK                            (0x1UL << AWO_PDS_CPU_REQ_POS)
#define AWO_PDS_CPU_REQ                                 AWO_PDS_CPU_REQ_MASK

/*****************  Bit definition for AWO_EICFG register  ***********************/
#define AWO_EICFG_EN_POS                                (0U)
#define AWO_EICFG_EN_MASK                               (0x3FUL << AWO_EICFG_EN_POS)
#define AWO_EICFG_EN                                    AWO_EICFG_EN_MASK
#define AWO_EICFG_S0_POS                                (8U)
#define AWO_EICFG_S0_MASK                               (0x3UL << AWO_EICFG_S0_POS)
#define AWO_EICFG_S0                                    AWO_EICFG_S0_MASK
#define AWO_EICFG_S1_POS                                (10U)
#define AWO_EICFG_S1_MASK                               (0x3UL << AWO_EICFG_S1_POS)
#define AWO_EICFG_S1                                    AWO_EICFG_S1_MASK
#define AWO_EICFG_S2_POS                                (12U)
#define AWO_EICFG_S2_MASK                               (0x3UL << AWO_EICFG_S2_POS)
#define AWO_EICFG_S2                                    AWO_EICFG_S2_MASK
#define AWO_EICFG_S3_POS                                (14U)
#define AWO_EICFG_S3_MASK                               (0x3UL << AWO_EICFG_S3_POS)
#define AWO_EICFG_S3                                    AWO_EICFG_S3_MASK
#define AWO_EICFG_S4_POS                                (16U)
#define AWO_EICFG_S4_MASK                               (0x3UL << AWO_EICFG_S4_POS)
#define AWO_EICFG_S4                                    AWO_EICFG_S4_MASK
#define AWO_EICFG_S5_POS                                (18U)
#define AWO_EICFG_S5_MASK                               (0x3UL << AWO_EICFG_S5_POS)
#define AWO_EICFG_S5                                    AWO_EICFG_S5_MASK
#define AWO_EICFG_PIN_IS_SRC_POS                        (20U)
#define AWO_EICFG_PIN_IS_SRC_MASK                       (0x1FUL << AWO_EICFG_PIN_IS_SRC_POS)
#define AWO_EICFG_PIN_IS_SRC                            AWO_EICFG_PIN_IS_SRC_MASK

/*****************  Bit definition for AWO_EIVAL register  ***********************/
#define AWO_EIVAL_VAL_POS                               (0U)
#define AWO_EIVAL_VAL_MASK                              (0x3FUL << AWO_EIVAL_VAL_POS)
#define AWO_EIVAL_VAL                                   AWO_EIVAL_VAL_EI_P15_MASK
#define AWO_EIVAL_RVAL_POS                              (8U)
#define AWO_EIVAL_RVAL_MASK                             (0x3FUL << AWO_EIVAL_RVAL_POS)
#define AWO_EIVAL_RVAL                                  AWO_EIVAL_RVAL_EI_P15_MASK

#define AWO_EIVAL_VAL_EI_P15_POS                        ( 0U )
#define AWO_EIVAL_VAL_EI_P15_MASK                       ( 0x1UL << AWO_EIVAL_VAL_EI_P15_POS )
#define AWO_EIVAL_VAL_EI_P15                            AWO_EIVAL_VAL_EI_P15_MASK
#define AWO_EIVAL_VAL_EI_P16_POS                        ( 1U )
#define AWO_EIVAL_VAL_EI_P16_MASK                       ( 0x1UL << AWO_EIVAL_VAL_EI_P16_POS )
#define AWO_EIVAL_VAL_EI_P16                            AWO_EIVAL_VAL_EI_P16_MASK
#define AWO_EIVAL_VAL_EI_P17_POS                        ( 2U )
#define AWO_EIVAL_VAL_EI_P17_MASK                       ( 0x1UL << AWO_EIVAL_VAL_EI_P17_POS )
#define AWO_EIVAL_VAL_EI_P17                            AWO_EIVAL_VAL_EI_P17_MASK
#define AWO_EIVAL_VAL_EI_P22_POS                        ( 3U )
#define AWO_EIVAL_VAL_EI_P22_MASK                       ( 0x1UL << AWO_EIVAL_VAL_EI_P22_POS )
#define AWO_EIVAL_VAL_EI_P22                            AWO_EIVAL_VAL_EI_P22_MASK
#define AWO_EIVAL_VAL_EI_P23_POS                        ( 4U )
#define AWO_EIVAL_VAL_EI_P23_MASK                       ( 0x1UL << AWO_EIVAL_VAL_EI_P23_POS )
#define AWO_EIVAL_VAL_EI_P23                            AWO_EIVAL_VAL_EI_P23_MASK
#define AWO_EIVAL_VAL_EI_TOUCH_POS                      ( 5U )
#define AWO_EIVAL_VAL_EI_TOUCH_MASK                     ( 0x1UL << AWO_EIVAL_VAL_EI_TOUCH_POS )
#define AWO_EIVAL_VAL_TOUCH                             AWO_EIVAL_VAL_EI_TOUCH_MASK
#define AWO_EIVAL_RVAL_EI_P15_POS                       ( 8U )
#define AWO_EIVAL_RVAL_EI_P15_MASK                      ( 0x1UL << AWO_EIVAL_RVAL_EI_P15_POS )
#define AWO_EIVAL_RVAL_EI_P15                           AWO_EIVAL_RVAL_EI_P15_MASK
#define AWO_EIVAL_RVAL_EI_P16_POS                       ( 9U )
#define AWO_EIVAL_RVAL_EI_P16_MASK                      ( 0x1UL << AWO_EIVAL_RVAL_EI_P16_POS )
#define AWO_EIVAL_RVAL_EI_P16                           AWO_EIVAL_RVAL_EI_P16_MASK
#define AWO_EIVAL_RVAL_EI_P17_POS                       ( 10U )
#define AWO_EIVAL_RVAL_EI_P17_MASK                      ( 0x1UL << AWO_EIVAL_RVAL_EI_P17_POS )
#define AWO_EIVAL_RVAL_EI_P17                           AWO_EIVAL_RVAL_EI_P17_MASK
#define AWO_EIVAL_RVAL_EI_P22_POS                       ( 11U )
#define AWO_EIVAL_RVAL_EI_P22_MASK                      ( 0x1UL << AWO_EIVAL_RVAL_EI_P22_POS )
#define AWO_EIVAL_RVAL_EI_P22                           AWO_EIVAL_RVAL_EI_P22_MASK
#define AWO_EIVAL_RVAL_EI_P23_POS                       ( 12U )
#define AWO_EIVAL_RVAL_EI_P23_MASK                      ( 0x1UL << AWO_EIVAL_RVAL_EI_P23_POS )
#define AWO_EIVAL_RVAL_EI_P23                           AWO_EIVAL_RVAL_EI_P23_MASK
#define AWO_EIVAL_RVAL_EI_TOUCH_POS                     ( 13U )
#define AWO_EIVAL_RVAL_EI_TOUCH_MASK                    ( 0x1UL << AWO_EIVAL_RVAL_EI_TOUCH_POS )
#define AWO_EIVAL_RVAL_TOUCH                            AWO_EIVAL_RVAL_EI_TOUCH_MASK
/*****************  Bit definition for AWO_EICLR register  ***********************/
#define AWO_EICLR_EI_P15_POS                               (0U)
#define AWO_EICLR_EI_P15_MASK                              (0x1UL << AWO_EICLR_EI_P15_POS)
#define AWO_EICLR_EI_P15                                   AWO_EICLR_EI_P15_MASK
#define AWO_EICLR_EI_P16_POS                               (1U)
#define AWO_EICLR_EI_P16_MASK                              (0x1UL << AWO_EICLR_EI_P16_POS)
#define AWO_EICLR_EI_P16                                   AWO_EICLR_EI_P16_MASK
#define AWO_EICLR_EI_P17_POS                               (2U)
#define AWO_EICLR_EI_P17_MASK                              (0x1UL << AWO_EICLR_EI_P17_POS)
#define AWO_EICLR_EI_P17                                   AWO_EICLR_EI_P17_MASK
#define AWO_EICLR_EI_P22_POS                               (3U)
#define AWO_EICLR_EI_P22_MASK                              (0x1UL << AWO_EICLR_EI_P22_POS)
#define AWO_EICLR_EI_P22                                   AWO_EICLR_EI_P22_MASK
#define AWO_EICLR_EI_P23_POS                               (4U)
#define AWO_EICLR_EI_P23_MASK                              (0x1UL << AWO_EICLR_EI_P23_POS)
#define AWO_EICLR_EI_P23                                   AWO_EICLR_EI_P23_MASK
#define AWO_EICLR_TOUCH_POS                             (5U)
#define AWO_EICLR_TOUCH_MASK                            (0x1UL << AWO_EICLR_TOUCH_POS)
#define AWO_EICLR_TOUCH                                 AWO_EICLR_TOUCH_MASK

/*****************  Bit definition for AWO_BLELPIV register  ***********************/
#define AWO_BLELPIV_VAL_POS                             (0U)
#define AWO_BLELPIV_VAL_MASK                            (0x3UL << AWO_BLELPIV_VAL_POS)
#define AWO_BLELPIV_VAL                                 AWO_BLELPIV_VAL_MASK
#define AWO_BLELPIV_RVAL_POS                            (8U)
#define AWO_BLELPIV_RVAL_MASK                           (0x3UL << AWO_BLELPIV_RVAL_POS)
#define AWO_BLELPIV_RVAL                                AWO_BLELPIV_RVAL_MASK

/*****************  Bit definition for AWO_BLELPIC register  ***********************/
#define AWO_BLELPIC_VAL_POS                             (0U)
#define AWO_BLELPIC_VAL_MASK                            (0x3UL << AWO_BLELPIC_VAL_POS)
#define AWO_BLELPIC_VAL                                 AWO_BLELPIC_VAL_MASK

/*****************  Bit definition for AWO_CLKG1 register  ***********************/
#define AWO_CLKG1_APB_CDP_UP_POS                        (0U)
#define AWO_CLKG1_APB_CDP_UP_MASK                       (0x1UL << AWO_CLKG1_APB_CDP_UP_POS)
#define AWO_CLKG1_APB_CDP_UP                            AWO_CLKG1_APB_CDP_UP_MASK
#define AWO_CLKG1_BLE_MAC_CDP_UP_POS                    (0U)
#define AWO_CLKG1_BLE_MAC_CDP_UP_MASK                   (0x1UL << AWO_CLKG1_BLE_MAC_CDP_UP_POS)
#define AWO_CLKG1_BLE_MAC_CDP_UP                        AWO_CLKGS1_BLE_MAC_CDP_UP_MASK

/*****************  Bit definition for AWO_CLKG2 register  ***********************/
#define AWO_CLKG2_BLE_MAC_CS_POS                        (0U)
#define AWO_CLKG2_BLE_MAC_CS_MASK                       (0x1UL << AWO_CLKG2_BLE_MAC_CS_POS)
#define AWO_CLKG2_BLE_MAC_CS                            AWO_CLKG2_BLE_MAC_CS_MASK
#define AWO_CLKG2_BLE_MAC_CS_T_HBUS_CLK                 (0x0UL << AWO_CLKG2_BLE_MAC_CS_POS)
#define AWO_CLKG2_BLE_MAC_CS_T_HBUS_DIV_CLK             (0x1UL << AWO_CLKG2_BLE_MAC_CS_POS)

#define AWO_CLKG2_BLE_MDM_RX_SW_CS_POS                  (1U)
#define AWO_CLKG2_BLE_MDM_RX_SW_CS_MASK                 (0x7UL << AWO_CLKG2_BLE_MDM_RX_SW_CS_POS)
#define AWO_CLKG2_BLE_MDM_RX_SW_CS                      AWO_CLKG2_BLE_MDM_RX_SW_CS_MASK
#define AWO_CLKG2_BLE_MDM_RX_SW_CS_T_NONE               (0x0UL << AWO_CLKG2_BLE_MDM_RX_SW_CS_POS)
#define AWO_CLKG2_BLE_MDM_RX_SW_CS_T_32M                (0x1UL << AWO_CLKG2_BLE_MDM_RX_SW_CS_POS)
#define AWO_CLKG2_BLE_MDM_RX_SW_CS_T_PLL                (0x2UL << AWO_CLKG2_BLE_MDM_RX_SW_CS_POS)
#define AWO_CLKG2_BLE_MDM_RX_SW_CS_T_PLL_DIV            (0x4UL << AWO_CLKG2_BLE_MDM_RX_SW_CS_POS)

#define AWO_CLKG2_BLE_MDM_RX_BY_HW_CS_POS               (4U)
#define AWO_CLKG2_BLE_MDM_RX_BY_HW_CS_MASK              (0x1UL << AWO_CLKG2_BLE_MDM_RX_BY_HW_CS_POS)
#define AWO_CLKG2_BLE_MDM_RX_BY_HW_CS                   AWO_CLKG2_BLE_MDM_RX_BY_HW_CS_MASK
#define AWO_CLKG2_BLE_MDM_RX_CDP_M1_POS                 (5U)
#define AWO_CLKG2_BLE_MDM_RX_CDP_M1_MASK                (0x2UL << AWO_CLKG2_BLE_MDM_RX_CDP_M1_POS)
#define AWO_CLKG2_BLE_MDM_RX_CDP_M1                     AWO_CLKG2_BLE_MDM_RX_CDP_M1_MASK
#define AWO_CLKG2_BLE_MAC_CDP0_M1_POS                   (8U)
#define AWO_CLKG2_BLE_MAC_CDP0_M1_MASK                  (0xFUL << AWO_CLKG2_BLE_MAC_CDP0_M1_POS)
#define AWO_CLKG2_BLE_MAC_CDP0_M1                       AWO_CLKG2_BLE_MAC_CDP0_M1_MASK
#define AWO_CLKG2_BLE_MAC_CDP1_M1_POS                   (12U)
#define AWO_CLKG2_BLE_MAC_CDP1_M1_MASK                  (0xFUL << AWO_CLKG2_BLE_MAC_CDP1_M1_POS)
#define AWO_CLKG2_BLE_MAC_CDP1_M1                       AWO_CLKG2_BLE_MAC_CDP1_M1_MASK
#define AWO_CLKG2_BLE_MAC_CS_BY_HW_POS                  (16U)
#define AWO_CLKG2_BLE_MAC_CS_BY_HW_MASK                 (0x1UL << AWO_CLKG2_BLE_MAC_CS_BY_HW_POS)
#define AWO_CLKG2_BLE_MAC_CS_BY_HW                      AWO_CLKG2_BLE_MAC_CS_BY_HW_MASK

/*****************  Bit definition for AWO_SRST register  ***********************/
#define AWO_SRST_ALL_SET_POS                            (0U)
#define AWO_SRST_ALL_SET_MASK                           (0x1UL << AWO_SRST_ALL_SET_POS)
#define AWO_SRST_ALL_SET                                AWO_SRST_ALL_SET_MASK
#define AWO_SRST_BLE_LP_SET_POS                         (2U)
#define AWO_SRST_BLE_LP_SET_MASK                        (0x1UL << AWO_SRST_BLE_LP_SET_POS)
#define AWO_SRST_BLE_LP_SET                             AWO_SRST_BLE_LP_SET_MASK
#define AWO_SRST_RTC_SET_POS                            (4U)
#define AWO_SRST_RTC_SET_MASK                           (0x1UL << AWO_SRST_RTC_SET_POS)
#define AWO_SRST_RTC_SET                                AWO_SRST_RTC_SET_MASK
#define AWO_SRST_BLE_SET_POS                            (6U)
#define AWO_SRST_BLE_SET_MASK                           (0x1UL << AWO_SRST_BLE_SET_POS)
#define AWO_SRST_BLE_SET                                AWO_SRST_BLE_SET_MASK
#define AWO_SRST_TOUCH_SET_POS                          (8U)
#define AWO_SRST_TOUCH_SET_MASK                         (0x1UL << AWO_SRST_TOUCH_SET_POS)
#define AWO_SRST_TOUCH_SET                              AWO_SRST_TOUCH_SET_MASK

#define AWO_SRST_ALL_CLR_POS                            (0U)
#define AWO_SRST_ALL_CLR_MASK                           (0x1UL << AWO_SRST_ALL_CLR_POS)
#define AWO_SRST_ALL_CLR                                AWO_SRST_ALL_CLR_MASK
#define AWO_SRST_BLE_LP_CLR_POS                         (2U)
#define AWO_SRST_BLE_LP_CLR_MASK                        (0x1UL << AWO_SRST_BLE_LP_CLR_POS)
#define AWO_SRST_BLE_LP_CLR                             AWO_SRST_BLE_LP_CLR_MASK
#define AWO_SRST_RTC_CLR_POS                            (4U)
#define AWO_SRST_RTC_CLR_MASK                           (0x1UL << AWO_SRST_RTC_CLR_POS)
#define AWO_SRST_RTC_CLR                                AWO_SRST_RTC_CLR_MASK
#define AWO_SRST_BLE_CLR_POS                            (6U)
#define AWO_SRST_BLE_CLR_MASK                           (0x1UL << AWO_SRST_BLE_CLR_POS)
#define AWO_SRST_BLE_CLR                                AWO_SRST_BLE_CLR_MASK
#define AWO_SRST_TOUCH_CLR_POS                          (8U)
#define AWO_SRST_TOUCH_CLR_MASK                         (0x1UL << AWO_SRST_TOUCH_CLR_POS)
#define AWO_SRST_TOUCH_CLR                              AWO_SRST_TOUCH_CLR_MASK

/*****************  Bit definition for AWO_RAMP register  ***********************/
#define AWO_RAMP_WPULSE_CFG_POS                         (0U)
#define AWO_RAMP_WPULSE_CFG_MASK                        (0x7UL << AWO_RAMP_WPULSE_CFG_POS)
#define AWO_RAMP_WPULSE_CFG                             AWO_RAMP_WPULSE_CFG_MASK
#define AWO_RAMP_RA_CFG_POS                             (3U)
#define AWO_RAMP_RA_CFG_MASK                            (0x3UL << AWO_RAMP_RA_CFG_POS)
#define AWO_RAMP_RA_CFG                                 AWO_RAMP_RA_CFG_MASK
#define AWO_RAMP_WA_CFG_POS                             (5U)
#define AWO_RAMP_WA_CFG_MASK                            (0x7UL << AWO_RAMP_WA_CFG_POS)
#define AWO_RAMP_WA_CFG                                 AWO_RAMP_WA_CFG_MASK
#define AWO_RAMP_RM_CFG_POS                             (8U)
#define AWO_RAMP_RM_CFG_MASK                            (0xFUL << AWO_RAMP_RM_CFG_POS)
#define AWO_RAMP_RM_CFG                                 AWO_RAMP_RM_CFG_MASK
#define AWO_RAMP_RME_CFG_POS                            (12U)
#define AWO_RAMP_RME_CFG_MASK                           (0x1UL << AWO_RAMP_RME_CFG_POS)
#define AWO_RAMP_RME_CFG                                AWO_RAMP_RME_CFG_MASK

#define AWO_RAMP_WPULSE_VAL_POS                         (16U)
#define AWO_RAMP_WPULSE_VAL_MASK                        (0x7UL << AWO_RAMP_WPULSE_VAL_POS)
#define AWO_RAMP_WPULSE_VAL                             AWO_RAMP_WPULSE_VAL_MASK
#define AWO_RAMP_RA_VAL_POS                             (19U)
#define AWO_RAMP_RA_VAL_MASK                            (0x3UL << AWO_RAMP_RA_VAL_POS)
#define AWO_RAMP_RA_VAL                                 AWO_RAMP_RA_VAL_MASK
#define AWO_RAMP_WA_VAL_POS                             (21U)
#define AWO_RAMP_WA_VAL_MASK                            (0x7UL << AWO_RAMP_WA_VAL_POS)
#define AWO_RAMP_WA_VAL                                 AWO_RAMP_WA_VAL_MASK
#define AWO_RAMP_RM_VAL_POS                             (24U)
#define AWO_RAMP_RM_VAL_MASK                            (0xFUL << AWO_RAMP_RM_VAL_POS)
#define AWO_RAMP_RM_VAL                                 AWO_RAMP_RM_VAL_MASK
#define AWO_RAMP_RME_VAL_POS                            (28U)
#define AWO_RAMP_RME_VAL_MASK                           (0x1UL << AWO_RAMP_RME_VAL_POS)
#define AWO_RAMP_RME_VAL                                AWO_RAMP_RME_VAL_MASK

/*****************  Bit definition for AWO_VDDV register  ***********************/
#define AWO_VDDV_CFG_POS                                (0U)
#define AWO_VDDV_CFG_MASK                               (0x1UL << AWO_VDDV_CFG_POS)
#define AWO_VDDV_CFG                                    AWO_VDDV_CFG_MASK
#define AWO_VDDV_VAL_POS                                (1U)
#define AWO_VDDV_VAL_MASK                               (0x1UL << AWO_VDDV_VAL_POS)
#define AWO_VDDV_VAL                                    AWO_VDDV_VAL_MASK

/*****************  Bit definition for AWO_GPIODS0 register  ***********************/
#define AWO_GPIODS0_POS                                 (0U)
#define AWO_GPIODS0_MASK                                (0x3FFFFFFFUL << AWO_GPIODS0_POS)
#define AWO_GPIODS0                                     AWO_GPIODS0_MASK

/*****************  Bit definition for AWO_GPIODS1 register  ***********************/
#define AWO_GPIODS1_POS                                 (0U)
#define AWO_GPIODS1_MASK                                (0x3FFFFFFFUL << AWO_GPIODS1_POS)
#define AWO_GPIODS1                                     AWO_GPIODS1_MASK

/*****************  Bit definition for AWO_GPIOIE register  ***********************/
#define AWO_GPIOIE_POS                                 (0U)
#define AWO_GPIOIE_MASK                                (0x3FFFFFFFUL << AWO_GPIOIE_POS)
#define AWO_GPIOIE                                     AWO_GPIOIE_MASK

/*****************  Bit definition for AWO_GPIOIS register  ***********************/
#define AWO_GPIOIS_POS                                 (0U)
#define AWO_GPIOIS_MASK                                (0x3FFFFFFFUL << AWO_GPIOIS_POS)
#define AWO_GPIOIS                                     AWO_GPIOIS_MASK

/*****************  Bit definition for AWO_GPIOPE register  ***********************/
#define AWO_GPIOPE_POS                                 (0U)
#define AWO_GPIOPE_MASK                                (0x3FFFFFFFUL << AWO_GPIOPE_POS)
#define AWO_GPIOPE                                     AWO_GPIOPE_MASK

/*****************  Bit definition for AWO_GPIOPS register  ***********************/
#define AWO_GPIOPS_POS                                 (0U)
#define AWO_GPIOPS_MASK                                (0x3FFFFFFFUL << AWO_GPIOPS_POS)
#define AWO_GPIOPS                                     AWO_GPIOPS_MASK

/*****************  Bit definition for AWO_TCFG1 register  ***********************/
#define AWO_TCFG1_ITV_POS                               (0U)
#define AWO_TCFG1_ITV_MASK                              (0xFFFFUL << AWO_TCFG1_ITV_POS)
#define AWO_TCFG1_ITV                                   AWO_TCFG1_ITV_MASK
#define AWO_TCFG1_RCOSC_32M_DLY_POS                     (16U)
#define AWO_TCFG1_RCOSC_32M_DLY_MASK                    (0xFUL << AWO_TCFG1_RCOSC_32M_DLY_POS)
#define AWO_TCFG1_RCOSC_32M_DLY                         AWO_TCFG1_RCOSC_32M_DLY_MASK
#define AWO_TCFG1_EN_POS                                (20U)
#define AWO_TCFG1_EN_MASK                               (0x1UL << AWO_TCFG1_EN_POS)
#define AWO_TCFG1_EN                                    AWO_TCFG1_EN_MASK

/*****************  Bit definition for AWO_TCFG2 register  ***********************/
#define AWO_TCFG2_SCAN_DLY_POS                          (0U)
#define AWO_TCFG2_SCAN_DLY_MASK                         (0xFFUL << AWO_TCFG2_SCAN_DLY_POS)
#define AWO_TCFG2_SCAN_DLY                              AWO_TCFG2_SCAN_DLY_MASK
#define AWO_TCFG2_SCAN_NUM_POS                          (0U)
#define AWO_TCFG2_SCAN_NUM_MASK                         (0xFFUL << AWO_TCFG2_SCAN_NUM_POS)
#define AWO_TCFG2_SCAN_NUM                              AWO_TCFG2_SCAN_NUM_MASK

/*****************  Bit definition for AWO_TCFG3 register  ***********************/
#define AWO_TCFG3_THR_POS                               (0U)
#define AWO_TCFG3_THR_MASK                              (0x3FFFFUL << AWO_TCFG3_THR_POS)
#define AWO_TCFG3_THR                                   AWO_TCFG3_THR_MASK

/*****************  Bit definition for AWO_PP0 register  ***********************/
#define AWO_PP0_WID_L_POS                               (0U)
#define AWO_PP0_WID_L_MASK                              (0xFFFFUL << AWO_PP0_WID_L_POS)
#define AWO_PP0_WID_L                                   AWO_PP0_WID_L_MASK
#define AWO_PP0_WID_H_POS                               (16U)
#define AWO_PP0_WID_H_MASK                              (0xFFFFUL << AWO_PP0_WID_H_POS)
#define AWO_PP0_WID_H                                   AWO_PP0_WID_H_MASK

/*****************  Bit definition for AWO_PP1 register  ***********************/
#define AWO_PP1_WID_L_POS                               (0U)
#define AWO_PP1_WID_L_MASK                              (0xFFFFUL << AWO_PP1_WID_L_POS)
#define AWO_PP1_WID_L                                   AWO_PP1_WID_L_MASK
#define AWO_PP1_WID_H_POS                               (16U)
#define AWO_PP1_WID_H_MASK                              (0xFFFFUL << AWO_PP1_WID_H_POS)
#define AWO_PP1_WID_H                                   AWO_PP1_WID_H_MASK

/*****************  Bit definition for AWO_PP2 register  ***********************/
#define AWO_PP2_WID_L_POS                               (0U)
#define AWO_PP2_WID_L_MASK                              (0xFFFFUL << AWO_PP2_WID_L_POS)
#define AWO_PP2_WID_L                                   AWO_PP2_WID_L_MASK
#define AWO_PP2_WID_H_POS                               (16U)
#define AWO_PP2_WID_H_MASK                              (0xFFFFUL << AWO_PP2_WID_H_POS)
#define AWO_PP2_WID_H                                   AWO_PP2_WID_H_MASK

/*****************  Bit definition for AWO_PPC register  ***********************/
#define AWO_PPC_PWM0_FCH_POS                            (0U)
#define AWO_PPC_PWM0_FCH_MASK                           (0x1UL << AWO_PPC_PWM0_FCH_POS)
#define AWO_PPC_PWM0_FCH                                AWO_PPC_PWM0_FCH_MASK
#define AWO_PPC_PWM0_EN_POS                             (1U)
#define AWO_PPC_PWM0_EN_MASK                            (0x1UL << AWO_PPC_PWM0_EN_POS)
#define AWO_PPC_PWM0_EN                                 AWO_PPC_PWM0_EN_MASK

#define AWO_PPC_PWM1_FCH_POS                            (0U)
#define AWO_PPC_PWM1_FCH_MASK                           (0x1UL << AWO_PPC_PWM1_FCH_POS)
#define AWO_PPC_PWM1_FCH                                AWO_PPC_PWM1_FCH_MASK
#define AWO_PPC_PWM1_EN_POS                             (1U)
#define AWO_PPC_PWM1_EN_MASK                            (0x1UL << AWO_PPC_PWM1_EN_POS)
#define AWO_PPC_PWM1_EN                                 AWO_PPC_PWM1_EN_MASK

#define AWO_PPC_PWM2_FCH_POS                            (0U)
#define AWO_PPC_PWM2_FCH_MASK                           (0x1UL << AWO_PPC_PWM2_FCH_POS)
#define AWO_PPC_PWM2_FCH                                AWO_PPC_PWM2_FCH_MASK
#define AWO_PPC_PWM2_EN_POS                             (1U)
#define AWO_PPC_PWM2_EN_MASK                            (0x1UL << AWO_PPC_PWM2_EN_POS)
#define AWO_PPC_PWM2_EN                                 AWO_PPC_PWM2_EN_MASK

/*****************  Bit definition for AWO_BM register  ***********************/
#define AWO_BM_0_POS                                    (0U)
#define AWO_BM_0_MASK                                   (0x1UL << AWO_BM_0_POS)
#define AWO_BM_0                                        AWO_BM_0_MASK

#define AWO_BM_1_POS                                    (1U)
#define AWO_BM_1_MASK                                   (0x1UL << AWO_BM_1_POS)
#define AWO_BM_1                                        AWO_BM_1_MASK

/* value type ----------------------------------------------------------------*/


/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_SYSC_AWO_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
