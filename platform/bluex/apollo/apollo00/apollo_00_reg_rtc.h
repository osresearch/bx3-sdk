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
#ifndef __APOLLO_00_REG_RTC_H__
#define __APOLLO_00_REG_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/
typedef struct {
    __I  uint32_t CCV;                  /* Current Counter Value Register   0x0000 */
    __IO uint32_t CM;                   /* Counter Match Register           0x0004 */
    __IO uint32_t CL;                   /* Counter Load Register            0x0008 */
    __IO uint32_t CC;                   /* Counter Control Register         0x000C */
    __I  uint32_t IS;                   /* Interrupt Status Register        0x0010 */
    __I  uint32_t RIS;                  /* Raw Interrupt Status Register    0x0014 */
    __I  uint32_t EOI;                  /* End of Interrupt Register        0x0018 */
    __I  uint32_t VER;                  /* Component Version Register       0x001C */
} reg_rtc_t;

/* bit definition -----------------------------------------------------------*/

/*****************  Bit definition for RTC_CCV register  ********************/
#define RTC_CCV_VAL_POS                                	(0U)
#define RTC_CCV_VAL_MASK                               	(0xFFFFFFFFUL << RTC_CCV_VAL_POS)
#define RTC_CCV_VAL                                    	RTC_CCV_VAL_MASK

/*****************  Bit definition for RTC_CM register  ********************/
#define RTC_CM_VAL_POS                                 	(0U)
#define RTC_CM_VAL_MASK                                	(0xFFFFFFFFUL << RTC_CM_VAL_POS)
#define RTC_CM_VAL                                     	RTC_CM_VAL_MASK

/*****************  Bit definition for RTC_CL register  ********************/
#define RTC_CL_VAL_POS                                 	(0U)
#define RTC_CL_VAL_MASK                                	(0xFFFFFFFFUL << RTC_CL_VAL_POS)
#define RTC_CL_VAL                                     	RTC_CL_VAL_MASK

/*****************  Bit definition for RTC_CC register  ********************/
#define RTC_CC_IE_POS                                   (0U)
#define RTC_CC_IE_MASK                                  (0x1UL << RTC_CC_IE_POS)
#define RTC_CC_IE                                       RTC_CC_IE_MASK
#define RTC_CC_IM_POS                                   (1U)
#define RTC_CC_IM_MASK                                  (0x1UL << RTC_CC_IM_POS)
#define RTC_CC_IM                                       RTC_CC_IM_MASK
#define RTC_CC_EN_POS                                   (2U)
#define RTC_CC_EN_MASK                                  (0x1UL << RTC_CC_EN_POS)
#define RTC_CC_EN                                       RTC_CC_EN_MASK
#define RTC_CC_WRAP_EN_POS                              (3U)
#define RTC_CC_WRAP_EN_MASK                             (0x1UL << RTC_CC_WRAP_EN_POS)
#define RTC_CC_WRAP_EN                                  RTC_CC_WRAP_EN_MASK


/* value type ----------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_RTC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

