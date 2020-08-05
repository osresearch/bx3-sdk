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
#ifndef __REG_ECC_H__
#define __REG_ECC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>
/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
typedef struct
{
    volatile uint32_t PWM0_EN;
    volatile uint32_t START_SEL;
    volatile uint32_t START_BUSY;
    volatile uint32_t reserved0[1];
    volatile uint32_t INTR_MASK;
    volatile uint32_t INTR_STAT;
    volatile uint32_t RAW_INTR;
    volatile uint32_t INTR_CLR;
    volatile uint32_t RAM_CTRL;
    volatile uint32_t reserved1[119];
    volatile uint32_t ECC_RAM[128];
}ble_reg_ecc_t;

enum ECC_PWM0_EN_FIELD
{
    ECC_JCB_DBLE_IS_P_MASK = 0x10000000,
    ECC_JCB_DBLE_IS_P_POS = 28,
    ECC_CALC_TYPE_MASK = 0x7000000,
    ECC_CALC_TYPE_POS = 24,
    ECC_RSLT_ADDR_MASK = 0xf0000,
    ECC_RSLT_ADDR_POS = 16,
    ECC_DAT_A_ADDR_MASK = 0xf00,
    ECC_DAT_A_ADDR_POS = 8,
    ECC_DAT_B_ADDR_MASK = 0xf,
    ECC_DAT_B_ADDR_POS = 0,
};

enum ECC_START_SEL_FIELD
{
    ECC_ECC_WO_INV_MASK = 0x10,
    ECC_ECC_WO_INV_POS = 4,
    ECC_START_SEL_R_MASK = 0x7,
    ECC_START_SEL_R_POS = 0,
};

enum ECC_START_BUSY_FIELD
{
    ECC_START_BUSY_R_MASK = 0x1,
    ECC_START_BUSY_R_POS = 0,
};

enum ECC_INTR_MASK_FIELD
{
    ECC_INTR_MASK_R_MASK = 0x1,
    ECC_INTR_MASK_R_POS = 0,
};

enum ECC_INTR_STAT_FIELD
{
    ECC_INTR_STAT_R_MASK = 0x1,
    ECC_INTR_STAT_R_POS = 0,
};

enum ECC_RAW_INTR_FIELD
{
    ECC_RAW_INTR_R_MASK = 0x1,
    ECC_RAW_INTR_R_POS = 0,
};

enum ECC_INTR_CLR_FIELD
{
    ECC_INTR_CLR_R_MASK = 0x1,
    ECC_INTR_CLR_R_POS = 0,
};

enum ECC_RAM_CTRL_FIELD
{
    ECC_WPULSE_MASK = 0x700000,
    ECC_WPULSE_POS = 20,
    ECC_RA_MASK = 0x30000,
    ECC_RA_POS = 16,
    ECC_WA_MASK = 0x7000,
    ECC_WA_POS = 12,
    ECC_LS_MASK = 0x100,
    ECC_LS_POS = 8,
    ECC_RM_MASK = 0xf0,
    ECC_RM_POS = 4,
    ECC_RME_MASK = 0x1,
    ECC_RME_POS = 0,
};
/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __REG_ECC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
