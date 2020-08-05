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
#ifndef __APOLLO_00_REG_CACHE_H__
#define __APOLLO_00_REG_CACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

typedef struct {
    __IO uint32_t EN;                   /* <! enable                    0x0000 */
    __IO uint32_t BA;                   /* <! base addr                 0x0004 */
    __IO uint32_t DA;                   /* <! data address .            0x0008 */
    __O  uint32_t CMD;                  /* <! command .                 0x000C */
    __I  uint32_t FAL;                  /* <! flush address low         0x0010 */
    __IO uint32_t FAH;                  /* <! flush address high        0x0014 */
    __IO uint32_t FADITR;               /* <! flush all data in tag ram 0x0018 */
    __IO uint32_t FE;                   /* <! flush enable .            0x001c */
} reg_cache_t;



/* bit definition ------------------------------------------------------------*/

/*****************  Bit definition for CACHE_EN register  *********************/
#define CACHE_EN_BIT_POS                                (0U)
#define CACHE_EN_BIT_MASK                               (0x1UL << CACHE_EN_BIT_POS)
#define CACHE_EN_BIT                                    CACHE_EN_BIT_MASK

/*****************  Bit definition for CACHE_BA register  *********************/
#define CACHE_BA_VAL_POS                                (0U)
#define CACHE_BA_VAL_MASK                               (0xFFFFFFFFUL << CACHE_BA_VAL_POS)
#define CACHE_BA_VAL                                    CACHE_BA_VAL_MASK

/*****************  Bit definition for CACHE_DA register  *********************/
#define CACHE_DA_VAL_POS                                (0U)
#define CACHE_DA_VAL_MASK                               (0xFFFFFFFFUL << CACHE_DA_VAL_POS)
#define CACHE_DA_VAL                                    CACHE_DA_VAL_MASK

/*****************  Bit definition for CACHE_CMD register  *********************/
#define CACHE_CMD_RD_CMD_POS                            (0U)
#define CACHE_CMD_RD_CMD_MASK                           (0xFFUL << CACHE_CMD_RD_CMD_POS)
#define CACHE_CMD_RD_CMD                                CACHE_CMD_RD_CMD_MASK
#define CACHE_CMD_RD_ADDR_FORMAT_POS                    (8U)
#define CACHE_CMD_RD_ADDR_FORMAT_MASK                   (0x1UL << CACHE_CMD_RD_ADDR_FORMAT_POS)
#define CACHE_CMD_RD_ADDR_FORMAT                        CACHE_CMD_RD_ADDR_FORMAT_MASK
#define CACHE_CMD_RD_DATA_FORMAT_POS                    (9U)
#define CACHE_CMD_RD_DATA_FORMAT_MASK                   (0x1UL << CACHE_CMD_RD_DATA_FORMAT_POS)
#define CACHE_CMD_RD_DATA_FORMAT                        CACHE_CMD_RD_DATA_FORMAT_MASK
#define CACHE_CMD_RD_CMD_FORMAT_POS                     (10U)
#define CACHE_CMD_RD_CMD_FORMAT_MASK                    (0x1UL << CACHE_CMD_RD_CMD_FORMAT_POS)
#define CACHE_CMD_RD_CMD_FORMAT                         CACHE_CMD_RD_CMD_FORMAT_MASK
#define CACHE_CMD_TAP_VAL_POS                           (16U)
#define CACHE_CMD_TAP_VAL_MASK                          (0x3FFFUL << CACHE_CMD_TAP_VAL_POS)
#define CACHE_CMD_TAP_VAL                               CACHE_CMD_TAP_VAL_MASK

/*****************  Bit definition for CACHE_FAL register  *********************/
#define CACHE_FAL_VAL_POS                               (0U)
#define CACHE_FAL_VAL_MASK                              (0xFFFFFFFFUL << CACHE_FAL_VAL_POS)
#define CACHE_FAL_VAL                                   CACHE_FAL_VAL_MASK

/*****************  Bit definition for CACHE_FAH register  *********************/
#define CACHE_FAH_VAL_POS                               (0U)
#define CACHE_FAH_VAL_MASK                              (0xFFFFFFFFUL << CACHE_FAH_VAL_POS)
#define CACHE_FAH_VAL                                   CACHE_FAH_VAL_MASK

/*****************  Bit definition for CACHE_FADITR register  *********************/
#define CACHE_FADITR_BIT_POS                            (0U)
#define CACHE_FADITR_BIT_MASK                           (0x1UL << CACHE_FADITR_BIT_POS)
#define CACHE_FADITR_BIT                                CACHE_FADITR_BIT_MASK

/*****************  Bit definition for CACHE_FE register  *********************/
#define CACHE_FE_BIT_POS                                (0U)
#define CACHE_FE_BIT_MASK                               (0x1UL << CACHE_FE_BIT_POS)
#define CACHE_FE_BIT                                    CACHE_FE_BIT_MASK


/* value type ----------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_CACHE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

