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
#ifndef __APOLLO_00_REG_WDT_H__
#define __APOLLO_00_REG_WDT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/
typedef struct
{
    __IO uint32_t CTRL;                 /* !< Control Register                  0x0000 */
    __IO uint32_t TR;                   /* !< Timeout Range Register            0x0004 */
    __I  uint32_t CCV;                  /* !< Current Counter Value Register    0x0008 */
    __IO uint32_t CR;                   /* !< Counter Restart Register          0x000C */
    __I  uint32_t IS;                   /* !< Interrupt Status Register         0x0010 */
    __I  uint32_t EOI;                  /* !< End Of Interrupt                  0x0014 */
         uint32_t reserver[51];         /* !< description                       0x0018 */
    __I  uint32_t CP5;                  /* !< Component Parameters Register 5   0x00E4 */
    __I  uint32_t CP4;                  /* !< Component Parameters Register 4   0x00E8 */
    __I  uint32_t CP3;                  /* !< Component Parameters Register 3   0x00EC */
    __I  uint32_t CP2;                  /* !< Component Parameters Register 2   0x00F0 */
    __I  uint32_t CP1;                  /* !< Component Parameters Register 1   0x00F4 */
    __I  uint32_t VER;                  /* !< Component Version Register        0x00F8 */
    __I  uint32_t TYPE;                 /* !< Component Type Register           0x00FC */
}reg_wdt_t;

/* bit definition ------------------------------------------------------------*/
/*****************  Bit definition for WDT_CTRL register  ********************/
#define WDT_CTRL_EN_POS                                 (0U)
#define WDT_CTRL_EN_MASK                                (0x1UL << WDT_CTRL_EN_POS)
#define WDT_CTRL_EN                                     WDT_CTRL_EN_MASK
#define WDT_CTRL_RMOD_POS                               (1U)
#define WDT_CTRL_RMOD_MASK                              (0x1UL << WDT_CTRL_RMOD_POS)
#define WDT_CTRL_RMOD                                   WDT_CTRL_RMOD_MASK
#define WDT_CTRL_RST_PULSE_LEN_POS                      (2U)
#define WDT_CTRL_RST_PULSE_LEN_MASK                     (0x7UL << WDT_CTRL_RST_PULSE_LEN_POS)
#define WDT_CTRL_RST_PULSE_LEN                          WDT_CTRL_RST_PULSE_LEN_MASK
#define WDT_CTRL_DUMMY_POS                              (5U)
#define WDT_CTRL_DUMMY_MASK                             (0x1UL << WDT_CTRL_DUMMY_POS)
#define WDT_CTRL_DUMMY                                  WDT_CTRL_DUMMY_MASK

/*****************  Bit definition for WDT_TR register  ********************/
#define WDT_TR_PERIOD_POS                               (0U)
#define WDT_TR_PERIOD_MASK                              (0xFUL << WDT_TR_PERIOD_POS)
#define WDT_TR_PERIOD                                   WDT_TR_PERIOD_MASK
#define WDT_TR_PERIOD_INIT_POS                          (4U)
#define WDT_TR_PERIOD_INIT_MASK                         (0xFUL << WDT_TR_PERIOD_INIT_POS)
#define WDT_TR_PERIOD_INIT                              WDT_TR_PERIOD_INIT_MASK

/*****************  Bit definition for WDT_CCV register  ********************/
#define WDT_CCV_VAL_POS                                 (0U)
#define WDT_CCV_VAL_MASK                                (0xFFFFUL << WDT_CCV_VAL_POS)
#define WDT_CCV_VAL                                     WDT_CCV_VAL_MASK

/*****************  Bit definition for WDT_CR register  ********************/
#define WDT_CR_VAL_POS                                  (0U)
#define WDT_CR_VAL_MASK                                 (0xFFUL << WDT_CR_VAL_POS)
#define WDT_CR_VAL                                      WDT_CR_VAL_MASK

/*****************  Bit definition for WDT_IS register  ********************/
#define WDT_IS_VAL_POS                                  (0U)
#define WDT_IS_VAL_MASK                                 (0x1UL << WDT_IS_VAL_POS)
#define WDT_IS_VAL                                      WDT_IS_VAL_MASK

/*****************  Bit definition for WDT_EOI register  ********************/
#define WDT_EOI_VAL_POS                                 (0U)
#define WDT_EOI_VAL_MASK                                (0x1UL << WDT_EOI_VAL_POS)
#define WDT_EOI_VAL                                     WDT_EOI_VAL_MASK

/*****************  Bit definition for WDT_CP5 register  ********************/
#define WDT_CP5_USER_TOP_MAX_POS                        (0U)
#define WDT_CP5_USER_TOP_MAX_MASK                       (0xFFFFFFFFUL << WDT_CP5_USER_TOP_MAX_POS)
#define WDT_CP5_USER_TOP_MAX                            WDT_CP5_USER_TOP_MAX_MASK

/*****************  Bit definition for WDT_CP4 register  ********************/
#define WDT_CP4_USER_TOP_INIT_MAX_POS                   (0U)
#define WDT_CP4_USER_TOP_INIT_MAX_MASK                  (0xFFFFFFFFUL << WDT_CP4_USER_TOP_INIT_MAX_POS)
#define WDT_CP4_USER_TOP_INIT_MAX                       WDT_CP4_USER_TOP_INIT_MAX_MASK

/*****************  Bit definition for WDT_CP3 register  ********************/
#define WDT_CP3_TOP_RST_POS                             (0U)
#define WDT_CP3_TOP_RST_MASK                            (0xFFFFFFFFUL << WDT_CP3_TOP_RST_POS)
#define WDT_CP3_TOP_RST                                 WDT_CP3_TOP_RST_MASK

/*****************  Bit definition for WDT_CP2register  ********************/
#define WDT_CP2_CNT_RST_POS                             (0U)
#define WDT_CP2_CNT_RST_MASK                            (0xFFFFFFFFUL << WDT_CP2_CNT_RST_POS)
#define WDT_CP2_CNT_RST                                 WDT_CP2_CNT_RST_MASK

/*****************  Bit definition for WDT_CP1 register  ********************/
#define WDT_CP1_AWAYS_EN_POS                            (0U)
#define WDT_CP1_AWAYS_EN_MASK                           (0x1UL << WDT_CP1_AWAYS_EN_POS)
#define WDT_CP1_AWAYS_EN                                WDT_CP1_AWAYS_EN_MASK
#define WDT_CP1_DFLT_RMOD_POS                           (1U)
#define WDT_CP1_DFLT_RMOD_MASK                          (0x1UL << WDT_CP1_DFLT_RMOD_POS)
#define WDT_CP1_DFLT_RMOD                               WDT_CP1_DFLT_RMOD_MASK
#define WDT_CP1_DUAL_TOP_POS                            (2U)
#define WDT_CP1_DUAL_TOP_MASK                           (0x1UL << WDT_CP1_DUAL_TOP_POS)
#define WDT_CP1_DUAL_TOP                                WDT_CP1_DUAL_TOP_MASK
#define WDT_CP1_HC_RMOD_POS                             (3U)
#define WDT_CP1_HC_RMOD_MASK                            (0x1UL << WDT_CP1_HC_RMOD_POS)
#define WDT_CP1_HC_RMOD                                 WDT_CP1_HC_RMOD_MASK
#define WDT_CP1_HC_RPL_POS                              (4U)
#define WDT_CP1_HC_RPL_MASK                             (0x1UL << WDT_CP1_HC_RPL_POS)
#define WDT_CP1_HC_RPL                                  WDT_CP1_HC_RPL_MASK
#define WDT_CP1_HC_TOP_POS                              (5U)
#define WDT_CP1_HC_TOP_MASK                             (0x1UL << WDT_CP1_HC_TOP_POS)
#define WDT_CP1_HC_TOP                                  WDT_CP1_HC_TOP_MASK
#define WDT_CP1_USE_FIX_TOP_POS                         (6U)
#define WDT_CP1_USE_FIX_TOP_MASK                        (0x1UL << WDT_CP1_USE_FIX_TOP_POS)
#define WDT_CP1_USE_FIX_TOP                             WDT_CP1_USE_FIX_TOP_MASK
#define WDT_CP1_PAUSE_POS                               (7U)
#define WDT_CP1_PAUSE_MASK                              (0x1UL << WDT_CP1_PAUSE_POS)
#define WDT_CP1_PAUSE                                   WDT_CP1_PAUSE_MASK
#define WDT_CP1_APB_DATA_WIDTH_POS                      (8U)
#define WDT_CP1_APB_DATA_WIDTH_MASK                     (0x3UL << WDT_CP1_APB_DATA_WIDTH_POS)
#define WDT_CP1_APB_DATA_WIDTH                          WDT_CP1_APB_DATA_WIDTH_MASK
#define WDT_CP1_DFLT_RPL_POS                            (10U)
#define WDT_CP1_DFLT_RPL_MASK                           (0xFUL << WDT_CP1_DFLT_RPL_POS)
#define WDT_CP1_DFLT_RPL                                WDT_CP1_DFLT_RPL_MASK
#define WDT_CP1_DFLT_TOP_POS                            (16U)
#define WDT_CP1_DFLT_TOP_MASK                           (0xFUL << WDT_CP1_DFLT_TOP_POS)
#define WDT_CP1_DFLT_TOP                                WDT_CP1_DFLT_TOP_MASK
#define WDT_CP1_DFLT_TOP_INIT_POS                       (20U)
#define WDT_CP1_DFLT_TOP_INIT_MASK                      (0xFUL << WDT_CP1_DFLT_TOP_INIT_POS)
#define WDT_CP1_DFLT_TOP_INIT                           WDT_CP1_DFLT_TOP_INIT_MASK
#define WDT_CP1_CNT_WIDTH_POS                           (24U)
#define WDT_CP1_CNT_WIDTH_MASK                          (0x1FUL << WDT_CP1_CNT_WIDTH_POS)
#define WDT_CP1_CNT_WIDTH                               WDT_CP1_CNT_WIDTH_MASK

/*****************  Bit definition for WDT_VER register  ********************/
#define WDT_VER_VAL_POS                                 (0U)
#define WDT_VER_VAL_MASK                                (0xFFFFFFFFUL << WDT_VER_VAL_POS)
#define WDT_VER_VAL                                     WDT_VER_VAL_MASK

/*****************  Bit definition for WDT_TYPE register  ********************/
#define WDT_TYPE_VAL_POS                                (0U)
#define WDT_TYPE_VAL_MASK                               (0xFFFFFFFFUL << WDT_TYPE_VAL_POS)
#define WDT_TYPE_VAL                                    WDT_TYPE_VAL_MASK

/* value type ----------------------------------------------------------------*/

#define WDT_CTRL_RST_PULSE_LEN_T_2_PCLK_CYCLES          ((uint32_t)0X00000000U << WDT_CTRL_RST_PULSE_LEN_POS )
#define WDT_CTRL_RST_PULSE_LEN_T_4_PCLK_CYCLES          ((uint32_t)0X00000001U << WDT_CTRL_RST_PULSE_LEN_POS )
#define WDT_CTRL_RST_PULSE_LEN_T_8_PCLK_CYCLES          ((uint32_t)0X00000002U << WDT_CTRL_RST_PULSE_LEN_POS )
#define WDT_CTRL_RST_PULSE_LEN_T_16_PCLK_CYCLES         ((uint32_t)0X00000003U << WDT_CTRL_RST_PULSE_LEN_POS )
#define WDT_CTRL_RST_PULSE_LEN_T_32_PCLK_CYCLES         ((uint32_t)0X00000004U << WDT_CTRL_RST_PULSE_LEN_POS )
#define WDT_CTRL_RST_PULSE_LEN_T_64_PCLK_CYCLES         ((uint32_t)0X00000005U << WDT_CTRL_RST_PULSE_LEN_POS )
#define WDT_CTRL_RST_PULSE_LEN_T_128_PCLK_CYCLES        ((uint32_t)0X00000006U << WDT_CTRL_RST_PULSE_LEN_POS )
#define WDT_CTRL_RST_PULSE_LEN_T_256_PCLK_CYCLES        ((uint32_t)0X00000007U << WDT_CTRL_RST_PULSE_LEN_POS )

#define WDT_CTRL_RMOD_T_SYSTEM_RESET                    ((uint32_t)0X00000000U << WDT_CTRL_RMOD_POS )
#define WDT_CTRL_RMOD_T_INTERRUPT_FIRST                 ((uint32_t)0X00000001U << WDT_CTRL_RMOD_POS )

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_WDT_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

