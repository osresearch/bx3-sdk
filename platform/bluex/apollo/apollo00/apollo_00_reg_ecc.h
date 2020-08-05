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
#ifndef __APOLLO_00_REG_ECC_H__
#define __APOLLO_00_REG_ECC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/
typedef struct {
    __IO uint32_t PE;                   /*  pwm0 enable                                     */
    __O  uint32_t SS;                   /*  start select                                    */
    __IO uint32_t SB;                   /*  start the selsect calculation                   */
         uint32_t reserved0;            /*                                                  */
    __IO uint32_t IM;                   /*  interrupt mask register                         */
    __I  uint32_t IS;                   /*  Interrupt status register                       */
    __I  uint32_t RI;                   /*  Raw Interrupt  Register                         */
    __O  uint32_t IC;                   /*  Interrupt clear register                        */
    __IO uint32_t RC;                   /*  ram control                                     */
         uint32_t reserved1[119];       /*                                                  */
    __IO uint32_t ER[128];              /*  ecc ram                                         */
} reg_ecc_t;

/* bit definition -----------------------------------------------------------*/

/************************* type definition for ECC PE *************************/
#define ECC_PE_DBA_POS                                  (0U)
#define ECC_PE_DBA_MASK                                 (0xFUL << ECC_PE_DBA_POS)
#define ECC_PE_DBA                                      ECC_PE_DBA_MASK
#define ECC_PE_DAA_POS                                  (8U)
#define ECC_PE_DAA_MASK                                 (0xFUL << ECC_PE_DAA_POS)
#define ECC_PE_DAA                                      ECC_PE_DAA_MASK
#define ECC_PE_RA_POS                                   (16U)
#define ECC_PE_RA_MASK                                  (0xFUL << ECC_PE_RA_POS)
#define ECC_PE_RA                                       ECC_PE_RA_MASK
#define ECC_PE_CT_POS                                   (24U)
#define ECC_PE_CT_MASK                                  (0x7UL << ECC_PE_CT_POS)
#define ECC_PE_CT                                       ECC_PE_CT_MASK
#define ECC_PE_JCB_DBLE_IS_P_POS                        (28U)
#define ECC_PE_JCB_DBLE_IS_P_MASK                       (0x1UL << ECC_PE_JCB_DBLE_IS_P_POS)
#define ECC_PE_JCB_DBLE_IS_P                            ECC_PE_JCB_DBLE_IS_P_MASK

/************************* type definition for ECC SS *************************/
#define ECC_SS_SEL_POS                                  (0U)
#define ECC_SS_SEL_MASK                                 (0x3UL << ECC_SS_SEL_POS)
#define ECC_SS_SEL                                      ECC_SS_SEL_MASK
#define ECC_SS_EWI_POS                                  (4U)
#define ECC_SS_EWI_MASK                                 (0x1UL << ECC_SS_EWI_POS)
#define ECC_SS_EWI                                      ECC_SS_EWI_MASK

/************************* type definition for ECC SB *************************/
#define ECC_SB_BUSY_POS                                 (0U)
#define ECC_SB_BUSY_MASK                                (0x1UL << ECC_SB_BUSY_POS)
#define ECC_SB_BUSY                                     ECC_SB_BUSY_MASK

/************************* type definition for ECC IM *************************/
#define ECC_IM_POS                                      (0U)
#define ECC_IM_MASK                                     (0x1UL << ECC_IM_POS)
#define ECC_IM                                          ECC_IM_MASK

/************************* type definition for ECC IS *************************/
#define ECC_IS_POS                                      (0U)
#define ECC_IS_MASK                                     (0x1UL << ECC_IS_POS)
#define ECC_IS                                          ECC_IS_MASK

/************************* type definition for ECC IC *************************/
#define ECC_IC_POS                                      (0U)
#define ECC_IC_MASK                                     (0x1UL << ECC_IC_POS)
#define ECC_IC                                          ECC_IC_MASK

/************************* type definition for ECC RC *************************/
#define ECC_RC_RME_POS                                  (0U)
#define ECC_RC_RME_MASK                                 (0x1UL << ECC_RC_RME_POS)
#define ECC_RC_RME                                      ECC_RC_RME_MASK
#define ECC_RC_RM_POS                                   (4U)
#define ECC_RC_RM_MASK                                  (0xFUL << ECC_RC_RM_POS)
#define ECC_RC_RM                                       ECC_RC_RM_MASK
#define ECC_RC_LS_POS                                   (8U)
#define ECC_RC_LS_MASK                                  (0x1UL << ECC_RC_LS_POS)
#define ECC_RC_LS                                       ECC_RC_LS_MASK
#define ECC_RC_WA_POS                                   (12U)
#define ECC_RC_WA_MASK                                  (0x7UL << ECC_RC_WA_POS)
#define ECC_RC_WA                                       ECC_RC_WA_MASK
#define ECC_RC_RA_POS                                   (16U)
#define ECC_RC_RA_MASK                                  (0x3UL << ECC_RC_RA_POS)
#define ECC_RC_RA                                       ECC_RC_RA_MASK
#define ECC_RC_WPULSE_POS                               (20U)
#define ECC_RC_WPULSE_MASK                              (0x7UL << ECC_RC_WPULSE_POS)
#define ECC_RC_WPULSE                                   ECC_RC_WPULSE_MASK


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

