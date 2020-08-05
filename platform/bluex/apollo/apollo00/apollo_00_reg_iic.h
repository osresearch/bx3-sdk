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
#ifndef __APOLLO_00_REG_IIC_H__
#define __APOLLO_00_REG_IIC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

typedef struct {
    __IO uint32_t CR;                   /* !< control register              0x0000 */
    __IO uint32_t TA;                   /* !< target address                0x0004 */
    __IO uint32_t SA;                   /* !< slave address                 0x0008 */
    __IO uint32_t HSM;                  /* !< hs-mode master                0x000C */
    __IO uint32_t DC;                   /* !< Data Comand                   0x0010 */
    __IO uint32_t SSSH;                 /* !< ss scl high count             0x0014 */
    __IO uint32_t SSSL;                 /* !< ss scl low count              0x0018 */
    __IO uint32_t FSSH;                 /* !< fs scl high count             0x001C */
    __IO uint32_t FSSL;                 /* !< fs scl low count              0x0020 */
    __IO uint32_t HSSH;                 /* !< hs scl high count             0x0024 */
    __IO uint32_t HSSL;                 /* !< hs scl low count              0x0028 */
    __I  uint32_t IS;                   /* !< interrupt status              0x002C */
    __IO uint32_t IM;                   /* !< Interrupt mask register       0x0030 */
    __I  uint32_t RIS;                  /* !< raw interrupt status          0x0034 */
    __IO uint32_t RFTL;                 /* !< Receive FIFO Threshold Level  0x0038 */
    __IO uint32_t TFTL;                 /* !< Transmit FIFO Threshold Level 0x003C */
    __I  uint32_t CLRI;                 /* !< clr interrupt                 0x0040 */
    __I  uint32_t CLRRUI;               /* !< clr RX_UNDER interrupt        0x0044 */
    __I  uint32_t CLRROI;               /* !< clr RX_OVER interrupt         0x0048 */
    __I  uint32_t CLRTOI;               /* !< clr TX_OVER interrupt         0x004C */
    __I  uint32_t CLRRRI;               /* !< clr RD_REQ interrupt          0x0050 */
    __I  uint32_t CLRTAI;               /* !< clr TX_ABRT interrupt         0x0054 */
    __I  uint32_t CLRRDI;               /* !< clr RX_DONE interrupt         0x0058 */
    __I  uint32_t CLRAI;                /* !< clr activity interrupt        0x005C */
    __I  uint32_t CLRSPDI;              /* !< clr STOP_DET interrupt        0x0060 */
    __I  uint32_t CLRSTDI;              /* !< clr START_DEF interrupt       0x0064 */
    __I  uint32_t CLRGCI;               /* !< clr GEN_CALL interrupt        0x0068 */
    __IO uint32_t EN;                   /* !< enable register               0x006C */
    __I  uint32_t STA;                  /* !< status register               0x0070 */
    __I  uint32_t TXFL;                 /* !< Transmit FIFO Level           0x0074 */
    __IO uint32_t RXFL;                 /* !< Receive FIFO Level            0x0078 */
    __IO uint32_t SDAHT;                /* !< SDA HOLD time                 0x007C */
    __I  uint32_t TAS;                  /* !< tx abrt source                0x0080 */
    __IO uint32_t SDNO;                 /* !< slave data nack only          0x0084 */
    __IO uint32_t DMAC;                 /* !< DMA control register          0x0088 */
    __IO uint32_t DTDL;                 /* !< DMA Transmit Data Level       0x008C */
    __IO uint32_t DRDL;                 /* !< DMA Receive Data Level        0x0090 */
    __IO uint32_t SDAS;                 /* !< SDA setup                     0x0094 */
    __IO uint32_t AGC;                  /* !< ACK General Call              0x0098 */
    __I  uint32_t ES;                   /* !< enable status                 0x009C */
    __IO uint32_t FSS;                  /* !< fs_spklen                     0x00A0 */
    __IO uint32_t HSS;                  /* !< hs_spklen                     0x00A4 */
    __I  uint32_t CLRRSTD;              /* !< clr RESTART_DET interrupt     0x00A8 */
         uint32_t reserved0[19];        /* !< no decription                 0x00AC */
    __I  uint32_t CV;                   /* !< company version               0x00F8 */
    __I  uint32_t CT;                   /* !< company type                  0x00FC */
} reg_iic_t;

/* bit definition ------------------------------------------------------------*/

/*****************  Bit definition for IIC_CR register  ***********************/
#define IIC_CR_MASTER_MODE_POS                          (0U)
#define IIC_CR_MASTER_MODE_MASK                         (0x1UL << IIC_CR_MASTER_MODE_POS)       /*!< 0x00000001 */
#define IIC_CR_MASTER_MODE                              IIC_CR_MASTER_MODE_MASK                 /*!< IIC master enable */
#define IIC_CR_SPEED_POS                                (1U)
#define IIC_CR_SPEED_MASK                               (0x3UL << IIC_CR_SPEED_POS)             /*!< 0x00000006 */
#define IIC_CR_SPEED                                    IIC_CR_SPEED_MASK                       /*!< IIC speed  */
#define IIC_CR_10BITADDR_SLAVE_POS                      (3U)
#define IIC_CR_10BITADDR_SLAVE_MASK                     (0x1UL << IIC_CR_10BITADDR_SLAVE_POS)
#define IIC_CR_10BITADDR_SLAVE                          IIC_CR_10BITADDR_SLAVE_MASK
#define IIC_CR_10BITADDR_MASTER_POS                     (4U)
#define IIC_CR_10BITADDR_MASTER_MASK                    (0x1UL << IIC_CR_10BITADDR_MASTER_POS)
#define IIC_CR_10BITADDR_MASTER                         IIC_CR_10BITADDR_MASTER_MASK
#define IIC_CR_RESTART_EN_POS                           (5U)
#define IIC_CR_RESTART_EN_MASK                          (0x1UL << IIC_CR_10BITADDR_MASTER_POS)
#define IIC_CR_RESTART_EN                               IIC_CR_10BITADDR_MASTER_MASK
#define IIC_CR_SLAVE_DISABLE_POS                        (6U)
#define IIC_CR_SLAVE_DISABLE_MASK                       (0x1UL << IIC_CR_SLAVE_DISABLE_POS)
#define IIC_CR_SLAVE_DISABLE                            IIC_CR_SLAVE_DISABLE_MASK
#define IIC_CR_STOP_DET_POS                             (7U)
#define IIC_CR_STOP_DET_MASK                            (0x1UL << IIC_CR_STOP_DET_POS)
#define IIC_CR_STOP_DET                                 IIC_CR_STOP_DET_MASK
#define IIC_CR_TX_EMPTY_POS                             (8U)
#define IIC_CR_TX_EMPTY_MASK                            (0x1UL << IIC_CR_TX_EMPTY_POS)
#define IIC_CR_TX_EMPTY                                 IIC_CR_TX_EMPTY_MASK
#define IIC_CR_RX_FIFO_FULL_POS                         (9U)
#define IIC_CR_RX_FIFO_FULL_MASK                        (0x1UL << IIC_CR_10BITADDR_MASTER_POS)
#define IIC_CR_RX_FIFO_FULL                             IIC_CR_10BITADDR_MASTER_MASK

/*****************  Bit definition for IIC_TA register  ********************/
#define IIC_TA_TAR_POS                                  (0U)
#define IIC_TA_TAR_MASK                                 (0x3FFUL << IIC_TA_TAR_POS)
#define IIC_TA_TAR                                      IIC_TA_TAR_MASK
#define IIC_TA_GC_OR_START_POS                          (10U)
#define IIC_TA_GC_OR_START_MASK                         (0x1UL << IIC_TA_GC_OR_START_POS)
#define IIC_TA_GC_OR_START                              IIC_TA_GC_OR_START_MASK
#define IIC_TA_SPECIAL_POS                              (11U)
#define IIC_TA_SPECIAL_MASK                             (0x1UL << IIC_TA_SPECIAL_POS)
#define IIC_TA_SPECIAL                                  IIC_TA_SPECIAL_MASK

/*****************  Bit definition for IIC_SA register  ********************/
#define IIC_SA_SAR_POS                                  (0U)
#define IIC_SA_SAR_MASK                                 (0x3FFUL << IIC_SA_SAR_POS)
#define IIC_SA_SAR                                      IIC_SA_SAR_MASK

/*****************  Bit definition for IIC_HSM register  ********************/
#define IIC_HSM_MAR_POS                                 (0U)
#define IIC_HSM_MAR_MASK                                (0x3UL << IIC_HSM_MAR_POS)
#define IIC_HSM_MAR                                     IIC_HSM_MAR_MASK

/*****************  Bit definition for IIC_DC register  ********************/
#define IIC_DC_DAT_POS                                  (0U)
#define IIC_DC_DAT_MASK                                 (0xFFUL << IIC_DC_DAT_POS)
#define IIC_DC_DAT                                      IIC_DC_DAT_MASK
#define IIC_DC_CMD_POS                                  (8U)
#define IIC_DC_CMD_MASK                                 (0x1UL << IIC_DC_CMD_POS)
#define IIC_DC_CMD                                      IIC_DC_CMD_MASK
#define IIC_DC_STOP_POS                                 (9U)
#define IIC_DC_STOP_MASK                                (0x1UL << IIC_DC_STOP_POS)
#define IIC_DC_STOP                                     IIC_DC_STOP_MASK
#define IIC_DC_RESTART_POS                              (10U)
#define IIC_DC_RESTART_MASK                             (0x1UL << IIC_DC_RESTART_POS)
#define IIC_DC_RESTART                                  IIC_DC_RESTART_MASK
#define IIC_DC_FIRST_DATA_BYTE_POS                      (11U)
#define IIC_DC_FIRST_DATA_BYTE_MASK                     (0x1UL << IIC_DC_FIRST_DATA_BYTE_POS)
#define IIC_DC_FIRST_DATA_BYTE                          IIC_DC_FIRST_DATA_BYTE_MASK

/*****************  Bit definition for IIC_SSSH register  ********************/
#define IIC_SSSH_POS                                    (0U)
#define IIC_SSSH_MASK                                   (0xFFFFUL << IIC_SSSH_POS)
#define IIC_SSSH                                        IIC_SSSH_MASK

/*****************  Bit definition for IIC_SSSL register  ********************/
#define IIC_SSSL_POS                                    (0U)
#define IIC_SSSL_MASK                                   (0xFFFFUL << IIC_SSSL_POS)
#define IIC_SSSL                                        IIC_SSSL_MASK

/*****************  Bit definition for IIC_FSSH register  ********************/
#define IIC_FSSH_POS                                    (0U)
#define IIC_FSSH_MASK                                   (0xFFFFUL << IIC_FSSH_POS)
#define IIC_FSSH                                        IIC_FSSH_MASK

/*****************  Bit definition for IIC_FSSL register  ********************/
#define IIC_FSSL_POS                                    (0U)
#define IIC_FSSL_MASK                                   (0xFFFFUL << IIC_FSSL_POS)
#define IIC_FSSL                                        IIC_FSSL_MASK

/*****************  Bit definition for IIC_HSSH register  ********************/
#define IIC_HSSH_POS                                    (0U)
#define IIC_HSSH_MASK                                   (0xFFFFUL << IIC_FSSH_POS)
#define IIC_HSSH                                        IIC_FSSH_MASK

/*****************  Bit definition for IIC_FSSL register  ********************/
#define IIC_HSSL_POS                                    (0U)
#define IIC_HSSL_MASK                                   (0xFFFFUL << IIC_HSSL_POS)
#define IIC_HSSL                                        IIC_HSSL_MASK

/*****************  Bit definition for IIC_IS register  ********************/
#define IIC_IS_RX_UNDER_POS                             (0U)
#define IIC_IS_RX_UNDER_MASK                            (1UL << IIC_IS_RX_UNDER_POS)
#define IIC_IS_RX_UNDER                                 IIC_IS_RX_UNDER_MASK
#define IIC_IS_RX_OVER_POS                              (1U)
#define IIC_IS_RX_OVER_MASK                             (1UL << IIC_IS_RX_OVER_POS)
#define IIC_IS_RX_OVER                                  IIC_IS_RX_OVER_MASK
#define IIC_IS_RX_FULL_POS                              (2U)
#define IIC_IS_RX_FULL_MASK                             (1UL << IIC_IS_RX_FULL_POS)
#define IIC_IS_RX_FULL                                  IIC_IS_RX_FULL_MASK
#define IIC_IS_TX_OVER_POS                              (3U)
#define IIC_IS_TX_OVER_MASK                             (1UL << IIC_IS_TX_OVER_POS)
#define IIC_IS_TX_OVER                                  IIC_IS_TX_OVER_MASK
#define IIC_IS_TX_EMPTY_POS                             (4U)
#define IIC_IS_TX_EMPTY_MASK                            (1UL << IIC_IS_TX_EMPTY_POS)
#define IIC_IS_TX_EMPTY                                 IIC_IS_TX_EMPTY_MASK
#define IIC_IS_RD_REQ_POS                               (5U)
#define IIC_IS_RD_REQ_MASK                              (1UL << IIC_IS_RD_REQ_POS)
#define IIC_IS_RD_REQ                                   IIC_IS_RD_REQ_MASK
#define IIC_IS_TX_ABRT_POS                              (6U)
#define IIC_IS_TX_ABRT_MASK                             (1UL << IIC_IS_TX_ABRT_POS)
#define IIC_IS_TX_ABRT                                  IIC_IS_TX_ABRT_MASK
#define IIC_IS_RX_DONE_POS                              (7U)
#define IIC_IS_RX_DONE_MASK                             (1UL << IIC_IS_RX_DONE_POS)
#define IIC_IS_RX_DONE                                  IIC_IS_RX_DONE_MASK
#define IIC_IS_ACTIVITY_POS                             (8U)
#define IIC_IS_ACTIVITY_MASK                            (1UL << IIC_IS_ACTIVITY_POS)
#define IIC_IS_ACTIVITY                                 IIC_IS_ACTIVITY_MASK
#define IIC_IS_STOP_DET_POS                             (9U)
#define IIC_IS_STOP_DET_MASK                            (1UL << IIC_IS_STOP_DET_POS)
#define IIC_IS_STOP_DET                                 IIC_IS_STOP_DET_MASK
#define IIC_IS_START_DET_POS                            (10U)
#define IIC_IS_START_DET_MASK                           (1UL << IIC_IS_START_DET_POS)
#define IIC_IS_START_DET                                IIC_IS_START_DET_MASK
#define IIC_IS_GEN_CALL_POS                             (11U)
#define IIC_IS_GEN_CALL_MASK                            (1UL << IIC_IS_GEN_CALL_POS)
#define IIC_IS_GEN_CALL                                 IIC_IS_GEN_CALL_MASK
#define IIC_IS_RESTART_DET_POS                          (12U)
#define IIC_IS_RESTART_DET_MASK                         (1UL << IIC_IS_RESTART_DET_POS)
#define IIC_IS_RESTART_DET                              IIC_IS_RESTART_DET_MASK
#define IIC_IS_MST_ON_HOLD_POS                          (13U)
#define IIC_IS_MST_ON_HOLD_MASK                         (1UL << IIC_IS_MST_ON_HOLD_POS)
#define IIC_IS_MST_ON_HOLD                              IIC_IS_MST_ON_HOLD_MASK
#define IIC_IS_SCL_STUCK_AT_LOW_POS                     (14U)
#define IIC_IS_SCL_STUCK_AT_LOW_MASK                    (1UL << IIC_IS_MST_ON_HOLD_POS)
#define IIC_IS_SCL_STUCK_AT_LOW                         IIC_IS_MST_ON_HOLD_MASK

/*****************  Bit definition for IIC_IM register  ********************/
#define IIC_IM_RX_UNDER_POS                             (0U)
#define IIC_IM_RX_UNDER_MASK                            (1UL << IIC_IM_RX_UNDER_POS)
#define IIC_IM_RX_UNDER                                 IIC_IM_RX_UNDER_MASK
#define IIC_IM_RX_OVER_POS                              (1U)
#define IIC_IM_RX_OVER_MASK                             (1UL << IIC_IM_RX_OVER_POS)
#define IIC_IM_RX_OVER                                  IIC_IM_RX_OVER_MASK
#define IIC_IM_RX_FULL_POS                              (2U)
#define IIC_IM_RX_FULL_MASK                             (1UL << IIC_IM_RX_FULL_POS)
#define IIC_IM_RX_FULL                                  IIC_IM_RX_FULL_MASK
#define IIC_IM_TX_OVER_POS                              (3U)
#define IIC_IM_TX_OVER_MASK                             (1UL << IIC_IM_TX_OVER_POS)
#define IIC_IM_TX_OVER                                  IIC_IM_TX_OVER_MASK
#define IIC_IM_TX_EMPTY_POS                             (4U)
#define IIC_IM_TX_EMPTY_MASK                            (1UL << IIC_IM_TX_EMPTY_POS)
#define IIC_IM_TX_EMPTY                                 IIC_IM_TX_EMPTY_MASK
#define IIC_IM_RD_REQ_POS                               (5U)
#define IIC_IM_RD_REQ_MASK                              (1UL << IIC_IM_RD_REQ_POS)
#define IIC_IM_RD_REQ                                   IIC_IM_RD_REQ_MASK
#define IIC_IM_TX_ABRT_POS                              (6U)
#define IIC_IM_TX_ABRT_MASK                             (1UL << IIC_IM_TX_ABRT_POS)
#define IIC_IM_TX_ABRT                                  IIC_IM_TX_ABRT_MASK
#define IIC_IM_RX_DONE_POS                              (7U)
#define IIC_IM_RX_DONE_MASK                             (1UL << IIC_IM_RX_DONE_POS)
#define IIC_IM_RX_DONE                                  IIC_IM_RX_DONE_MASK
#define IIC_IM_ACTIVITY_POS                             (8U)
#define IIC_IM_ACTIVITY_MASK                            (1UL << IIC_IM_ACTIVITY_POS)
#define IIC_IM_ACTIVITY                                 IIC_IM_ACTIVITY_MASK
#define IIC_IM_STOP_DET_POS                             (9U)
#define IIC_IM_STOP_DET_MASK                            (1UL << IIC_IM_STOP_DET_POS)
#define IIC_IM_STOP_DET                                 IIC_IM_STOP_DET_MASK
#define IIC_IM_START_DET_POS                            (10U)
#define IIC_IM_START_DET_MASK                           (1UL << IIC_IM_START_DET_POS)
#define IIC_IM_START_DET                                IIC_IM_START_DET_MASK
#define IIC_IM_GEN_CALL_POS                             (11U)
#define IIC_IM_GEN_CALL_MASK                            (1UL << IIC_IM_GEN_CALL_POS)
#define IIC_IM_GEN_CALL                                 IIC_IM_GEN_CALL_MASK
#define IIC_IM_RESTART_DET_POS                          (12U)
#define IIC_IM_RESTART_DET_MASK                         (1UL << IIC_IM_RESTART_DET_POS)
#define IIC_IM_RESTART_DET                              IIC_IM_RESTART_DET_MASK
#define IIC_IM_MST_ON_HOLD_POS                          (13U)
#define IIC_IM_MST_ON_HOLD_MASK                         (1UL << IIC_IM_MST_ON_HOLD_POS)
#define IIC_IM_MST_ON_HOLD                              IIC_IM_MST_ON_HOLD_MASK
#define IIC_IM_SCL_STUCK_AT_LOW_POS                     (14U)
#define IIC_IM_SCL_STUCK_AT_LOW_MASK                    (1UL << IIC_IM_SCL_STUCK_AT_LOW_POS)
#define IIC_IM_SCL_STUCK_AT_LOW                         IIC_IM_SCL_STUCK_AT_LOW_MASK

/*****************  Bit definition for IIC_RIS register  ********************/
#define IIC_RIS_RX_UNDER_POS                            (0U)
#define IIC_RIS_RX_UNDER_MASK                           (1UL << IIC_RIS_RX_UNDER_POS)
#define IIC_RIS_RX_UNDER                                IIC_RIS_RX_UNDER_MASK
#define IIC_RIS_RX_OVER_POS                             (1U)
#define IIC_RIS_RX_OVER_MASK                            (1UL << IIC_RIS_RX_OVER_POS)
#define IIC_RIS_RX_OVER                                 IIC_RIS_RX_OVER_MASK
#define IIC_RIS_RX_FULL_POS                             (2U)
#define IIC_RIS_RX_FULL_MASK                            (1UL << IIC_RIS_RX_FULL_POS)
#define IIC_RIS_RX_FULL                                 IIC_RIS_RX_FULL_MASK
#define IIC_RIS_TX_OVER_POS                             (3U)
#define IIC_RIS_TX_OVER_MASK                            (1UL << IIC_RIS_TX_OVER_POS)
#define IIC_RIS_TX_OVER                                 IIC_RIS_TX_OVER_MASK
#define IIC_RIS_TX_EMPTY_POS                            (4U)
#define IIC_RIS_TX_EMPTY_MASK                           (1UL << IIC_RIS_TX_EMPTY_POS)
#define IIC_RIS_TX_EMPTY                                IIC_RIS_TX_EMPTY_MASK
#define IIC_RIS_RD_REQ_POS                              (5U)
#define IIC_RIS_RD_REQ_MASK                             (1UL << IIC_RIS_RD_REQ_POS)
#define IIC_RIS_RD_REQ                                  IIC_RIS_RD_REQ_MASK
#define IIC_RIS_TX_ABRT_POS                             (6U)
#define IIC_RIS_TX_ABRT_MASK                            (1UL << IIC_RIS_TX_ABRT_POS)
#define IIC_RIS_TX_ABRT                                 IIC_RIS_TX_ABRT_MASK
#define IIC_RIS_RX_DONE_POS                             (7U)
#define IIC_RIS_RX_DONE_MASK                            (1UL << IIC_RIS_RX_DONE_POS)
#define IIC_RIS_RX_DONE                                 IIC_RIS_RX_DONE_MASK
#define IIC_RIS_ACTIVITY_RAW_POS                        (8U)
#define IIC_RIS_ACTIVITY_RAW_MASK                       (1UL << IIC_RIS_ACTIVITY_RAW_POS)
#define IIC_RIS_ACTIVITY_RAW                            IIC_RIS_ACTIVITY_RAW_MASK
#define IIC_RIS_STOP_DET_POS                            (9U)
#define IIC_RIS_STOP_DET_MASK                           (1UL << IIC_RIS_STOP_DET_POS)
#define IIC_RIS_STOP_DET                                IIC_RIS_STOP_DET_MASK
#define IIC_RIS_START_DET_POS                           (10U)
#define IIC_RIS_START_DET_MASK                          (1UL << IIC_RIS_START_DET_POS)
#define IIC_RIS_START_DET                               IIC_RIS_START_DET_MASK
#define IIC_RIS_GEN_CALL_POS                            (11U)
#define IIC_RIS_GEN_CALL_MASK                           (1UL << IIC_RIS_GEN_CALL_POS)
#define IIC_RIS_GEN_CALL                                IIC_RIS_GEN_CALL_MASK
#define IIC_RIS_RESTART_DET_POS                         (12U)
#define IIC_RIS_RESTART_DET_MASK                        (1UL << IIC_RIS_RESTART_DET_POS)
#define IIC_RIS_RESTART_DET                             IIC_RIS_RESTART_DET_MASK
#define IIC_RIS_MST_ON_HOLD_POS                         (13U)
#define IIC_RIS_MST_ON_HOLD_MASK                        (1UL << IIC_RIS_SCL_STUCK_AT_LOW_POS)
#define IIC_RIS_MST_ON_HOLD                             IIC_RIS_SCL_STUCK_AT_LOW_MASK
#define IIC_RIS_SCL_STUCK_AT_LOW_POS                    (14U)
#define IIC_RIS_SCL_STUCK_AT_LOW_MASK                   (1UL << IIC_RIS_SCL_STUCK_AT_LOW_POS)
#define IIC_RIS_SCL_STUCK_AT_LOW                        IIC_RIS_SCL_STUCK_AT_LOW_MASK

/*****************  Bit definition for IIC_RFTL register  ********************/
#define IIC_RFTL_RX_TL_POS                              (0U)
#define IIC_RFTL_RX_TL_MASK                             (0XFFUL << IIC_RFTL_RX_TL_POS)
#define IIC_RFTL_RX_TL                                  IIC_RFTL_RX_TL_MASK

/*****************  Bit definition for IIC_TFTL register  ********************/
#define IIC_TFTL_TX_TL_POS                              (0U)
#define IIC_TFTL_TX_TL_MASK                             (0XFFUL << IIC_TFTL_TX_TL_POS)
#define IIC_TFTL_TX_TL                                  IIC_TFTL_TX_TL_MASK

/*****************  Bit definition for IIC_CLRI register  ********************/
#define IIC_CLRI_INTR_POS                               (0U)
#define IIC_CLRI_INTR_MASK                              (1UL << IIC_CLRI_INTR_POS)
#define IIC_CLRI_INTR                                   IIC_CLRI_INTR_MASK

/*****************  Bit definition for IIC_CLRRUI register  ********************/
#define IIC_CLRRUI_RX_UNDER_POS                          (0U)
#define IIC_CLRRUI_RX_UNDER_MASK                         (1UL << IIC_CLRRUI_RX_UNDER_POS)
#define IIC_CLRRUI_RX_UNDER                              IIC_CLRRUI_RX_UNDER_MASK

/*****************  Bit definition for IIC_CLRROI register  ********************/
#define IIC_CLRROI_RX_OVER_POS                           (0U)
#define IIC_CLRROI_RX_OVER_MASK                          (1UL << IIC_CLRROI_RX_OVER_MASK)
#define IIC_CLRROI_RX_OVER                               IIC_CLRROI_RX_OVER_MASK

/*****************  Bit definition for IIC_CLRTOI register  ********************/
#define IIC_CLRTOI_TX_OVER_POS                           (0U)
#define IIC_CLRTOI_TX_OVER_MASK                          (1UL << IIC_CLRTOI_TX_OVER_MASK)
#define IIC_CLRTOI_TX_OVER                               IIC_CLRTOI_TX_OVER_POS

/*****************  Bit definition for IIC_CLRRRI register  ********************/
#define IIC_CLRRRI_RD_REQ_POS                            (0U)
#define IIC_CLRRRI_RD_REQ_MASK                           (1UL << IIC_CLRRRI_RD_REQ_POS)
#define IIC_CLRRRI_RD_REQ                                IIC_CLRRRI_RD_REQ_MASK

/*****************  Bit definition for IIC_CLRTAI register  ********************/
#define IIC_CLRTAI_TX_ABRT_POS                           (0U)
#define IIC_CLRTAI_TX_ABRT_MASK                          (1UL << IIC_CLRTAI_TX_ABRT_POS)
#define IIC_CLRTAI_TX_ABRT                               IIC_CLRTAI_TX_ABRT_MASK

/*****************  Bit definition for IIC_CLRRDI register  ********************/
#define IIC_CLRRDI_RX_DONE_POS                           (0U)
#define IIC_CLRRDI_RX_DONE_MASK                          (1UL << IIC_CLRRDI_RX_DONE_POS)
#define IIC_CLRRDI_RX_DONE                               IIC_CLRRDI_RX_DONE_MASK

/*****************  Bit definition for IIC_CLRAI register  ********************/
#define IIC_CLRAI_ACTIVITY_POS                           (0U)
#define IIC_CLRAI_ACTIVITY_MASK                          (1UL << IIC_CLRAI_ACTIVITY_POS)
#define IIC_CLRAI_ACTIVITY                               IIC_CLRAI_ACTIVITY_MASK

/*****************  Bit definition for IIC_CLRSPDI register  ********************/
#define IIC_CLRSPDI_STOP_DET_POS                         (0U)
#define IIC_CLRSPDI_STOP_DET_MASK                        (1UL << IIC_CLRSPDI_STOP_DET_POS)
#define IIC_CLRSPDI_STOP_DET                             IIC_CLRSPDI_STOP_DET_MASK

/*****************  Bit definition for IIC_CLRSTDI register  ********************/
#define IIC_CLRSTDI_START_DET_POS                        (0U)
#define IIC_CLRSTDI_START_DET_MASK                       (1UL << IIC_CLRSTDI_START_DET_POS)
#define IIC_CLRSTDI_START_DET                            IIC_CLRSTDI_START_DET_MASK

/*****************  Bit definition for IIC_CLRGCI register  ********************/
#define IIC_CLRGCI_GEN_CALL_POS                          (0U)
#define IIC_CLRGCI_GEN_CALL_MASK                         (1UL << IIC_CLRGCI_GEN_CALL_POS)
#define IIC_CLRGCI_GEN_CALL                              IIC_CLRGCI_GEN_CALL_MASK

/*****************  Bit definition for IIC_EN register  ********************/
#define IIC_EN_ENABLE_POS                               (0U)
#define IIC_EN_ENABLE_MASK                              (1UL << IIC_EN_ENABLE_POS)
#define IIC_EN_ENABLE                                   IIC_EN_ENABLE_MASK
#define IIC_EN_ABORT_POS                                (1U)
#define IIC_EN_ABORT_MASK                               (1UL << IIC_EN_ABORT_POS)
#define IIC_EN_ABORT                                    IIC_EN_ABORT_MASK

/*****************  Bit definition for IIC_STA register  ********************/
#define IIC_STA_ACTIVITY_POS                            (0U)
#define IIC_STA_ACTIVITY_MASK                           (1UL << IIC_STA_ACTIVITY_POS)
#define IIC_STA_ACTIVITY                                IIC_STA_ACTIVITY_MASK
#define IIC_STA_TFNF_POS                                (1U)
#define IIC_STA_TFNF_MASK                               (1UL << IIC_STA_TFNF_POS)
#define IIC_STA_TFNF                                    IIC_STA_TFNF_MASK
#define IIC_STA_TFE_POS                                 (2U)
#define IIC_STA_TFE_MASK                                (1UL << IIC_STA_TFE_POS)
#define IIC_STA_TFE                                     IIC_STA_TFE_MASK
#define IIC_STA_RFNE_POS                                (3U)
#define IIC_STA_RFNE_MASK                               (1UL << IIC_STA_RFNE_POS)
#define IIC_STA_RFNE                                    IIC_STA_RFNE_MASK
#define IIC_STA_RFF_POS                                 (4U)
#define IIC_STA_RFF_MASK                                (1UL << IIC_STA_RFF_POS)
#define IIC_STA_RFF                                     IIC_STA_RFF_MASK
#define IIC_STA_MST_ACTIVITY_POS                        (5U)
#define IIC_STA_MST_ACTIVITY_MASK                       (1UL << IIC_STA_MST_ACTIVITY_POS)
#define IIC_STA_MST_ACTIVITY_EMPTY                      IIC_STA_MST_ACTIVITY_MASK
#define IIC_STA_SLV_ACTIVITY_POS                        (6U)
#define IIC_STA_SLV_ACTIVITY_MASK                       (1UL << IIC_STA_SLV_ACTIVITY_POS)
#define IIC_STA_SLV_ACTIVITY_EMPTY                      IIC_STA_SLV_ACTIVITY_MASK
#define IIC_STA_MST_HOLD_TX_FIFO_EMPTY_POS              (7U)
#define IIC_STA_MST_HOLD_TX_FIFO_EMPTY_MASK             (1UL << IIC_STA_MST_HOLD_TX_FIFO_EMPTY_POS)
#define IIC_STA_MST_HOLD_TX_FIFO_EMPTY                  IIC_STA_MST_HOLD_TX_FIFO_EMPTY_MASK
#define IIC_STA_MST_HOLD_RX_FIFO_FULL_POS               (8U)
#define IIC_STA_MST_HOLD_RX_FIFO_FULL_MASK              (1UL << IIC_STA_MST_HOLD_RX_FIFO_FULL_POS)
#define IIC_STA_MST_HOLD_RX_FIFO_FULL                   IIC_STA_MST_HOLD_RX_FIFO_FULL_MASK
#define IIC_STA_SLV_HOLD_TX_FIFO_EMPTY_POS              (9U)
#define IIC_STA_SLV_HOLD_TX_FIFO_EMPTY_MASK             (1UL << IIC_STA_SLV_HOLD_TX_FIFO_EMPTY_POS)
#define IIC_STA_SLV_HOLD_TX_FIFO_EMPTY                  IIC_STA_SLV_HOLD_TX_FIFO_EMPTY_MASK
#define IIC_STA_SLV_HOLD_RX_FIFO_FULL_POS               (10U)
#define IIC_STA_SLV_HOLD_RX_FIFO_FULL_MASK              (1UL << IIC_STA_SLV_HOLD_RX_FIFO_FULL_POS)
#define IIC_STA_SLV_HOLD_RX_FIFO_FULL                   IIC_STA_SLV_HOLD_RX_FIFO_FULL_MASK
#define IIC_STA_SDA_STUCK_NOT_RECOVERED_POS             (11U)
#define IIC_STA_SDA_STUCK_NOT_RECOVERED_MASK            (1UL << IIC_STA_SDA_STUCK_NOT_RECOVERED_POS)
#define IIC_STA_SDA_STUCK_NOT_RECOVERED                 IIC_STA_SDA_STUCK_NOT_RECOVERED_MASK
#define IIC_STA_SMBUS_QUICK_CMD_BIT_POS                 (16U)
#define IIC_STA_SMBUS_QUICK_CMD_BIT_MASK                (1UL << IIC_STA_SMBUS_QUICK_CMD_BIT_POS)
#define IIC_STA_SMBUS_QUICK_CMD_BIT                     IIC_STA_SMBUS_QUICK_CMD_BIT_MASK
#define IIC_STA_SMBUS_SLAVE_ADDR_VALID_POS              (17U)
#define IIC_STA_SMBUS_SLAVE_ADDR_VALID_MASK             (1UL << IIC_STA_SMBUS_SLAVE_ADDR_VALID_POS)
#define IIC_STA_SMBUS_SLAVE_ADDR_VALID                  IIC_STA_SMBUS_SLAVE_ADDR_VALID_MASK
#define IIC_STA_SMBUS_SLAVE_ADDR_RESOLVED_POS           (18U)
#define IIC_STA_SMBUS_SLAVE_ADDR_RESOLVED_MASK          (1UL << IIC_STA_SMBUS_SUSPEND_STATUS_POS)
#define IIC_STA_SMBUS_SLAVE_ADDR_RESOLVED               IIC_STA_SMBUS_SUSPEND_STATUS_MASK
#define IIC_STA_SMBUS_SUSPEND_STATUS_POS                (19U)
#define IIC_STA_SMBUS_SUSPEND_STATUS_MASK               (1UL << IIC_STA_SMBUS_SUSPEND_STATUS_POS)
#define IIC_STA_SMBUS_SUSPEND_STATUS                    IIC_STA_SMBUS_SUSPEND_STATUS_MASK
#define IIC_STA_SMBUS_ALERT_STATUS_POS                  (20U)
#define IIC_STA_SMBUS_ALERT_STATUS_MASK                 (1UL << IIC_STA_SMBUS_ALERT_STATUS_POS)
#define IIC_STA_SMBUS_ALERT_STATUS                      IIC_STA_SMBUS_ALERT_STATUS_MASK

/*****************  Bit definition for IIC_TXFL register  ********************/
#define IIC_TXFL_POS                                    (0U)
#define IIC_TXFL_MASK                                   (0X1FUL << IIC_TXFL_POS)
#define IIC_TXFL                                        IIC_TXFL_MASK

/*****************  Bit definition for IIC_RXFL register  ********************/
#define IIC_RXFL_POS                                    (0U)
#define IIC_RXFL_MASK                                   (0X1FUL << IIC_RXFL_POS)
#define IIC_RXFL                                        IIC_RXFL_MASK

/*****************  Bit definition for IIC_SDAHT register  ********************/
#define IIC_SDAHT_TX_HOLD_POS                           (0U)
#define IIC_SDAHT_TX_HOLD_MASK                          (0XFFFFUL << IIC_SDAHT_TX_HOLD_POS)
#define IIC_SDAHT_TX_HOLD                               IIC_SDAHT_TX_HOLD_MASK
#define IIC_SDAHT_RX_HOLD_POS                           (16U)
#define IIC_SDAHT_RX_HOLD_MASK                          (0XFF0000UL << IIC_SDAHT_RX_HOLD_POS)
#define IIC_SDAHT_RX_HOLD                               IIC_SDAHT_RX_HOLD_MASK

/*****************  Bit definition for IIC_TAS register  ********************/
#define IIC_TAS_ABRT_7BADDR_NOACK_POS                   (0U)
#define IIC_TAS_ABRT_7BADDR_NOACK_MASK                  (1UL << IIC_TAS_ABRT_7BADDR_NOACK_POS)
#define IIC_TAS_ABRT_7BADDR_NOACK                       IIC_TAS_ABRT_7BADDR_NOACK_MASK
#define IIC_TAS_ABRT_10ADDR1_NOACK_POS                  (1U)
#define IIC_TAS_ABRT_10ADDR1_NOACK_MASK                 (1UL << IIC_TAS_ABRT_10ADDR1_NOACK_POS)
#define IIC_TAS_ABRT_10ADDR1_NOACK                      IIC_TAS_ABRT_10ADDR1_NOACK_MASK
#define IIC_TAS_ABRT_10ADDR2_NOACK_POS                  (2U)
#define IIC_TAS_ABRT_10ADDR2_NOACK_MASK                 (1UL << IIC_TAS_ABRT_10ADDR2_NOACK_POS)
#define IIC_TAS_ABRT_10ADDR2_NOACK                      IIC_TAS_ABRT_10ADDR2_NOACK_MASK
#define IIC_TAS_ABRT_TXDATA_NOACK_POS                   (3U)
#define IIC_TAS_ABRT_TXDATA_NOACK_MASK                  (1UL << IIC_TAS_ABRT_TXDATA_NOACK_POS)
#define IIC_TAS_ABRT_TXDATA_NOACK                       IIC_TAS_ABRT_TXDATA_NOACK_MASK
#define IIC_TAS_ABRT_GCALL_NOACK_POS                    (4U)
#define IIC_TAS_ABRT_GCALL_NOACK_MASK                   (1UL << IIC_TAS_ABRT_GCALL_NOACK_POS)
#define IIC_TAS_ABRT_GCALL_NOACK                        IIC_TAS_ABRT_GCALL_NOACK_MASK
#define IIC_TAS_ABRT_GCALL_READ_POS                     (5U)
#define IIC_TAS_ABRT_GCALL_READ_MASK                    (1UL << IIC_TAS_ABRT_GCALL_READ_POS)
#define IIC_TAS_ABRT_GCALL_READ                         IIC_TAS_ABRT_GCALL_READ_MASK
#define IIC_TAS_ABRT_HS_ACKDET_POS                      (6U)
#define IIC_TAS_ABRT_HS_ACKDET_MASK                     (1UL << IIC_TAS_ABRT_HS_ACKDET_POS)
#define IIC_TAS_ABRT_HS_ACKDET                          IIC_TAS_ABRT_HS_ACKDET_MASK
#define IIC_TAS_ABRT_SBYTE_ACKDET_POS                   (7U)
#define IIC_TAS_ABRT_SBYTE_ACKDET_MASK                  (1UL << IIC_TAS_ABRT_SBYTE_ACKDET_POS)
#define IIC_TAS_ABRT_SBYTE_ACKDET                       IIC_TAS_ABRT_SBYTE_ACKDET_MASK
#define IIC_TAS_ABRT_HS_NORSTRT_POS                     (8U)
#define IIC_TAS_ABRT_HS_NORSTRT_MASK                    (1UL << IIC_TAS_ABRT_HS_NORSTRT_POS)
#define IIC_TAS_ABRT_HS_NORSTRT                         IIC_TAS_ABRT_HS_NORSTRT_MASK
#define IIC_TAS_ABRT_SBYTE_NORSTRT_POS                  (9U)
#define IIC_TAS_ABRT_SBYTE_NORSTRT_MASK                 (1UL << IIC_TAS_ABRT_SBYTE_NORSTRT_POS)
#define IIC_TAS_ABRT_SBYTE_NORSTRT                      IIC_TAS_ABRT_SBYTE_NORSTRT_MASK
#define IIC_TAS_ABRT_10B_RD_NORSTRT_POS                 (10U)
#define IIC_TAS_ABRT_10B_RD_NORSTRT_MASK                (1UL << IIC_TAS_ABRT_10B_RD_NORSTRT_POS)
#define IIC_TAS_ABRT_10B_RD_NORSTRT                     IIC_TAS_ABRT_10B_RD_NORSTRT_MASK
#define IIC_TAS_ABRT_MASTER_DIS_POS                     (11U)
#define IIC_TAS_ABRT_MASTER_DIS_MASK                    (1UL << IIC_TAS_ABRT_MASTER_DIS_POS)
#define IIC_TAS_ABRT_MASTER_DIS                         IIC_TAS_ABRT_MASTER_DIS_MASK
#define IIC_TAS_ARB_LOST_POS                            (12U)
#define IIC_TAS_ARB_LOST_MASK                           (1UL << IIC_TAS_ARB_LOST_POS)
#define IIC_TAS_ARB_LOST                                IIC_TAS_ARB_LOST_MASK
#define IIC_TAS_ABRT_SLVFLUSH_TXFIFO_POS                (13U)
#define IIC_TAS_ABRT_SLVFLUSH_TXFIFO_MASK               (1UL << IIC_TAS_ABRT_SLVFLUSH_TXFIFO_POS)
#define IIC_TAS_ABRT_SLVFLUSH_TXFIFO                    IIC_TAS_ABRT_SLVFLUSH_TXFIFO_MASK
#define IIC_TAS_ABRT_SLV_ARBLOST_POS                    (14U)
#define IIC_TAS_ABRT_SLV_ARBLOST_MASK                   (1UL << IIC_TAS_ABRT_SLV_ARBLOST_POS)
#define IIC_TAS_ABRT_SLV_ARBLOST                        IIC_TAS_ABRT_SLV_ARBLOST_MASK
#define IIC_TAS_ABRT_SLVRD_INTX_POS                     (15U)
#define IIC_TAS_ABRT_SLVRD_INTX_MASK                    (1UL << IIC_TAS_ABRT_SLVRD_INTX_POS)
#define IIC_TAS_ABRT_SLVRD_INTX                         IIC_TAS_ABRT_SLVRD_INTX_MASK
#define IIC_TAS_ABRT_USER_ABRT_POS                      (16U)
#define IIC_TAS_ABRT_USER_ABRT_MASK                     (1UL << IIC_TAS_ABRT_USER_ABRT_POS)
#define IIC_TAS_ABRT_USER_ABRT                          IIC_TAS_ABRT_SDA_STUCK_AT_LOW_MASK
#define IIC_TAS_ABRT_SDA_STUCK_AT_LOW_POS               (17U)
#define IIC_TAS_ABRT_SDA_STUCK_AT_LOW_MASK              (1UL << IIC_TAS_ABRT_SDA_STUCK_AT_LOW_POS)
#define IIC_TAS_ABRT_SDA_STUCK_AT_LOW                   IIC_TAS_ABRT_SDA_STUCK_AT_LOW_MASK
#define IIC_TAS_ABRT_DEVICE_NOACK_POS                   (18U)
#define IIC_TAS_ABRT_DEVICE_NOACK_MASK                  (1UL << IIC_TAS_ABRT_DEVICE_NOACK_POS)
#define IIC_TAS_ABRT_DEVICE_NOACK                       IIC_TAS_ABRT_DEVICE_NOACK_MASK
#define IIC_TAS_ABRT_DEVICE_SLVADDR_NOACK_POS           (19U)
#define IIC_TAS_ABRT_DEVICE_SLVADDR_NOACK_MASK          (1UL << IIC_TAS_ABRT_DEVICE_SLVADDR_NOACK_POS)
#define IIC_TAS_ABRT_DEVICE_SLVADDR_NOACK               IIC_TAS_ABRT_DEVICE_SLVADDR_NOACK_MASK
#define IIC_TAS_ABRT_DEVICE_WRITE_POS                   (20U)
#define IIC_TAS_ABRT_DEVICE_WRITE_MASK                  (1UL << IIC_TAS_ABRT_DEVICE_WRITE_POS)
#define IIC_TAS_ABRT_DEVICE_WRITE                       IIC_TAS_ABRT_DEVICE_WRITE_MASK
#define IIC_TAS_TX_FLUSH_CNT_POS                        (23U)
#define IIC_TAS_TX_FLUSH_CNT_MASK                       (0XFF800000UL << IIC_TAS_TX_FLUSH_CNT_POS)
#define IIC_TAS_TX_FLUSH_CNT                            IIC_TAS_TX_FLUSH_CNT_MASK

/*****************  Bit definition for IIC_SDNO register  ********************/
#define IIC_SDNO_NACK_POS                               (0U)
#define IIC_SDNO_NACK_MASK                              (1UL << IIC_SDNO_NACK_POS)
#define IIC_SDNO_NACK                                   IIC_SDNO_NACK_MASK

/*****************  Bit definition for IIC_DMAC register  ********************/
#define IIC_DMAC_RX_EN_POS                              (0U)
#define IIC_DMAC_RX_EN_MASK                             (0x1UL << IIC_DMAC_RX_EN_POS)
#define IIC_DMAC_RX_EN                                  IIC_DMAC_RX_EN_MASK
#define IIC_DMAC_TX_EN_POS                              (1U)
#define IIC_DMAC_TX_EN_MASK                             (0x1UL << IIC_DMAC_TX_EN_POS)
#define IIC_DMAC_TX_EN                                  IIC_DMAC_TX_EN_MASK

/*****************  Bit definition for IIC_DCR register  ********************/
#define IIC_DCR_RDMAE_POS                               (0U)
#define IIC_DCR_RDMAE_MASK                              (1UL << IIC_DCR_RDMAE_POS)
#define IIC_DCR_RDMAE                                   IIC_DCR_RDMAE_MASK
#define IIC_DCR_TDMAE_POS                               (1U)
#define IIC_DCR_TDMAE_MASK                              (1UL << IIC_DCR_TDMAE_POS)
#define IIC_DCR_TDMAE                                   IIC_DCR_TDMAE_MASK

/*****************  Bit definition for IIC_DTDL register  ********************/
#define IIC_DTDL_VAL_POS                                (0U)
#define IIC_DTDL_VAL_MASK                               (0XFUL << IIC_DTDL_VAL_POS)
#define IIC_DTDL_VAL                                    IIC_DTDL_VAL_MASK

/*****************  Bit definition for IIC_DRDL register  ********************/
#define IIC_DRDL_VAL_POS                                (0U)
#define IIC_DRDL_VAL_MASK                               (0XFUL << IIC_DRDL_VAL_POS)
#define IIC_DRDL_VAL                                    IIC_DRDL_VAL_MASK


/*****************  Bit definition for IIC_SDAS register  ********************/
#define IIC_SDAS_SDA_SETUP_POS                          (0U)
#define IIC_SDAS_SDA_SETUP_MASK                         (0XFFUL << IIC_SDAS_SDA_SETUP_POS)
#define IIC_SDAS_SDA_SETUP                              IIC_SDAS_SDA_SETUP_MASK

/*****************  Bit definition for IIC_AGC register  ********************/
#define IIC_AGC_ACK_GEN_CALL_POS                        (0U)
#define IIC_AGC_ACK_GEN_CALL_MASK                       (1UL << IIC_AGC_ACK_GEN_CALL_POS)
#define IIC_AGC_ACK_GEN_CALL                            IIC_AGC_ACK_GEN_CALL_MASK

/*****************  Bit definition for IIC_ES register  ********************/
#define IIC_ES_EN_POS                                   (0U)
#define IIC_ES_EN_MASK                                  (1UL << IIC_ES_EN_POS)
#define IIC_ES_EN_BUSY                                  IIC_ES_EN_MASK
#define IIC_ES_SLV_DISABLED_WHILE_BUSY_POS              (1U)
#define IIC_ES_SLV_DISABLED_WHILE_BUSY_MASK             (1UL << IIC_ES_SLV_RX_DATA_LOST_POS)
#define IIC_ES_SLV_DISABLED_WHILE_BUSY                  IIC_ES_SLV_RX_DATA_LOST_MASK
#define IIC_ES_SLV_RX_DATA_LOST_POS                     (2U)
#define IIC_ES_SLV_RX_DATA_LOST_MASK                    (1UL << IIC_ES_SLV_RX_DATA_LOST_POS)
#define IIC_ES_SLV_RX_DATA_LOST                         IIC_ES_SLV_RX_DATA_LOST_MASK

/*****************  Bit definition for IIC_FSS register  ********************/
#define IIC_FSS_FS_SPKLEN_POS                           (0U)
#define IIC_FSS_FS_SPKLEN_MASK                          (0XFFUL << IIC_FSS_FS_SPKLEN_POS)
#define IIC_FSS_FS_SPKLEN                               IIC_FSS_FS_SPKLEN_MASK

/*****************  Bit definition for IIC_HSS register  ********************/
#define IIC_HSS_HS_SPKLEN_POS                           (0U)
#define IIC_HSS_HS_SPKLEN_MASK                          (0XFFUL << IIC_HSS_HS_SPKLEN_POS)
#define IIC_HSS_HS_SPKLEN                               IIC_HSS_HS_SPKLEN_MASK

/*****************  Bit definition for IIC_CRD register  ********************/
#define IIC_CLRRSTD_RESTART_DET_POS                     (0U)
#define IIC_CLRRSTD_RESTART_DET_MASK                    (1UL << IIC_CLRRSTD_RESTART_DET_POS)
#define IIC_CLRRSTD_RESTART_DET                         IIC_CLRRSTD_RESTART_DET_MASK

/*****************  Bit definition for IIC_CV register  ********************/
#define IIC_CV_COMP_VERSION_POS                         (0U)
#define IIC_CV_COMP_VERSION_MASK                        (0XFFFFFFFFUL << IIC_CV_COMP_VERSION_POS)
#define IIC_CV_COMP_VERSION                             IIC_CV_COMP_VERSION_MASK

/*****************  Bit definition for IIC_CT register  ********************/
#define IIC_CT_COMP_TYPE_POS                            (0U)
#define IIC_CT_COMP_TYPE_MASK                           (0XFFFFFFFFUL << IIC_CT_COMP_TYPE_POS)
#define IIC_CT_COMP_TYPE                                IIC_CT_COMP_TYPE_MASK

/* value type ----------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_IIC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

