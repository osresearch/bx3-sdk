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
#ifndef __APOLLO_00_REG_TIMER_H__
#define __APOLLO_00_REG_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

typedef struct {
    __IO uint32_t LC;                   /* Load Count Register          0x0000 */
    __I  uint32_t CV;                   /* Current Value Register       0x0004 */
    __IO uint32_t CTRL;                 /* Control register             0x0008 */
    __I  uint32_t EOI;                  /* End-of-Interrupt Register    0x000C */
    __I  uint32_t IS;                   /* Interrupt Status Register    0x0010 */
} reg_timer_t;

typedef struct {
    __I  uint32_t IS;                   /* Interrupt Status Register [1] TIM1 [0] TIM0      0x0000 */
    __I  uint32_t EOI;                  /* End-of-Interrupt Register [1] TIM1 [0] TIM0      0x0004 */
    __I  uint32_t RIS;                  /* Raw Interrupt Status Register [1] TIM1 [0] TIM0  0x0008 */
    __I  uint32_t VER;                  /* ComponentVersion                                 0x000C */
} reg_timer_all_t;

/* exported constants --------------------------------------------------------*/

/* bit definition ------------------------------------------------------------*/

/*****************  Bit definition for TIM_LC register  ***********************/
#define TIM_LC_VAL_POS                                  (0U)
#define TIM_LC_VAL_MASK                                 (0xFFFFFFUL << TIM_LC_VAL_POS)
#define TIM_LC_VAL                                      TIM_LC_VAL_MASK

/*****************  Bit definition for TIM_CV register  ***********************/
#define TIM_CV_VAL_POS                                  (0U)
#define TIM_CV_VAL_MASK                                 (0xFFFFFFUL << TIM_CV_VAL_POS)
#define TIM_CV_VAL                                      TIM_CV_VAL_MASK

/*****************  Bit definition for TIM_CTRL register  ***********************/
#define TIM_CTRL_EN_POS                                 (0U)
#define TIM_CTRL_EN_MASK                                (0x1UL << TIM_CTRL_EN_POS)
#define TIM_CTRL_EN                                     TIM_CTRL_EN_MASK
#define TIM_CTRL_MODE_POS                               (1U)
#define TIM_CTRL_MODE_MASK                              (0x1UL << TIM_CTRL_MODE_POS)
#define TIM_CTRL_MODE                                   TIM_CTRL_MODE_MASK
#define TIM_CTRL_IM_POS                                 (2U)
#define TIM_CTRL_IM_MASK                                (0x1UL << TIM_CTRL_IM_POS)
#define TIM_CTRL_IM                                     TIM_CTRL_IM_MASK

/*****************  Bit definition for TIM_EOI register  ***********************/
#define TIM_EOI_POS                                     (0U)
#define TIM_EOI_MASK                                    (0x1UL << TIM_EOI_POS)
#define TIM_EOI                                         TIM_EOI_MASK

/*****************  Bit definition for TIM_IS register  ***********************/
#define TIM_IS_POS                                      (0U)
#define TIM_IS_MASK                                     (0x1UL << TIM_IS_POS)
#define TIM_IS                                          TIM_IS_MASK

/* value type ----------------------------------------------------------------*/

/*****************  value definition for TIM_CTRL register  *********************/
#define TIM_CTRL_MODE_T_FREE_RUNING                     (0UL << TIM_CTRL_MODE_POS)
#define TIM_CTRL_MODE_T_USER_DEFINED                    (1UL << TIM_CTRL_MODE_POS)

/* exported variables --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_TIMER_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

