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
#ifndef __APOLLO_00_REG_SPIS_H__
#define __APOLLO_00_REG_SPIS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

typedef struct {
    __IO uint32_t CTRL;                 /* !< Control Register                                  0x0000 */
         uint32_t reserved0;            /* !< description                                       0x0004 */
    __IO uint32_t SSIE;                 /* !< SSI Enable.                                       0x0008 */
    __IO uint32_t MC;                   /* !< Microwire Control Register                        0x000C */
         uint32_t reserved1[2];         /* !< description                                       0x0010 */
    __IO uint32_t TXFTL;                /* !< Transmit FIFO Threshold Level                     0x0018 */
    __IO uint32_t RXFTL;                /* !< Receive FIFO Threshold Level                      0x001C */
    __I  uint32_t TXFL;                 /* !< Transmit FIFO Level Register                      0x0020 */
    __I  uint32_t RXFL;                 /* !< Receive FIFO Level Register                       0x0024 */
    __I  uint32_t STA;                  /* !< Status Register                                   0x0028 */
    __IO uint32_t IM;                   /* !< Interrupt Mask Register                           0x002C */
    __I  uint32_t IS;                   /* !< Interrupt Status Register                         0x0030 */
    __I  uint32_t RIS;                  /* !< Raw Interrupt Status Register                     0x0034 */
    __I  uint32_t TXFOIC;               /* !< Transmit FIFO Overflow Interrupt Clear Register   0x0038 */
    __I  uint32_t RXFOIC;               /* !< Receive FIFO Overflow Interrupt Clear Register    0x003C */
    __I  uint32_t RXFUIC;               /* !< Receive FIFO Underflow Interrupt Clear Register   0x0040 */
    __I  uint32_t MMIC;                 /* !< Multi-Master Interrupt Clear Register             0x0044 */
    __I  uint32_t EOI;                  /* !< Interrupt Clear Register (End of Interrupt)       0x0048 */
    __IO uint32_t DMAC;                 /* !< DMA Control Register                              0x004C */
    __IO uint32_t DMATDL;               /* !< DMA Transmit Data Level                           0x0050 */
    __IO uint32_t DMARDL;               /* !< DMA Receive Data Level                            0x0054 */
    __I  uint32_t ID;                   /* !< Identification Register                           0x0058 */
    __I  uint32_t VER;                  /* !< coreKit version ID register                       0x005C */
    __IO uint32_t DATA;                 /* !< Data Register                                     0x0060 */
}reg_spis_t;

/* bit definition ------------------------------------------------------------*/

/******************  Bit definition for SPIS_CTRL register  ********************/
#define SPIS_CTRL_FF_POS                                (4U)
#define SPIS_CTRL_FF_MASK                               (0x3UL << SPIS_CTRL_FF_POS)
#define SPIS_CTRL_FF                                    SPIS_CTRL_FF_MASK
#define SPIS_CTRL_SCPH_POS                              (6U)
#define SPIS_CTRL_SCPH_MASK                             (0x1UL << SPIS_CTRL_SCPH_POS)
#define SPIS_CTRL_SCPH                                  SPIS_CTRL_SCPH_MASK
#define SPIS_CTRL_SCPOL_POS                             (7U)
#define SPIS_CTRL_SCPOL_MASK                            (0x1UL << SPIS_CTRL_SCPOL_POS)
#define SPIS_CTRL_SCPOL                                 SPIS_CTRL_SCPOL_MASK
#define SPIS_CTRL_TM_POS                                (8U)
#define SPIS_CTRL_TM_MASK                               (0x3UL << SPIS_CTRL_TM_POS)
#define SPIS_CTRL_TM                                    SPIS_CTRL_TM_MASK
#define SPIS_CTRL_SOE_POS                               (10U)
#define SPIS_CTRL_SOE_MASK                              (0x1UL << SPIS_CTRL_SOE_POS)
#define SPIS_CTRL_SOE                                   SPIS_CTRL_SOE_MASK
#define SPIS_CTRL_SRL_POS                               (11U)
#define SPIS_CTRL_SRL_MASK                              (0x1UL << SPIS_CTRL_SRL_POS)
#define SPIS_CTRL_SRL                                   SPIS_CTRL_SRL_MASK
#define SPIS_CTRL_CFS_POS                               (12U)
#define SPIS_CTRL_CFS_MASK                              (0xFUL << SPIS_CTRL_CFS_POS)
#define SPIS_CTRL_CFS                                   SPIS_CTRL_CFS_MASK
#define SPIS_CTRL_DFS32_POS                             (16U)
#define SPIS_CTRL_DFS32_MASK                            (0x1FUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32                                 SPIS_CTRL_DFS32_MASK

/******************  Bit definition for SPIS_SSIE register  ********************/
#define SPIS_SSIE_BIT_POS                               (0U)
#define SPIS_SSIE_BIT_MASK                              (0x1UL << SPIS_SSIE_BIT_POS)
#define SPIS_SSIE_BIT                                   SPIS_SSIE_BIT_MASK

/******************  Bit definition for SPIS_MC register  ********************/
#define SPIS_MC_TM_POS                                  (0U)
#define SPIS_MC_TM_MASK                                 (0x1UL << SPIS_MC_TM_POS)
#define SPIS_MC_TM                                      SPIS_MC_TM_MASK
#define SPIS_MC_DIR_POS                                 (1U)
#define SPIS_MC_DIR_MASK                                (0x1UL << SPIS_MC_DIR_POS)
#define SPIS_MC_DIR                                     SPIS_MC_DIR_MASK
#define SPIS_MC_HSK_POS                                 (2U)
#define SPIS_MC_HSK_MASK                                (0x1UL << SPIS_MC_HSK_POS)
#define SPIS_MC_HSK                                     SPIS_MC_HSK_MASK

/******************  Bit definition for SPIS_TXFTL register  ********************/
#define SPIS_TXFTL_VAL_POS                              (0U)
#define SPIS_TXFTL_VAL_MASK                             (0x1FUL << SPIS_TXFTL_VAL_POS)
#define SPIS_TXFTL_VAL                                  SPIS_TXFTL_VAL_MASK

/******************  Bit definition for SPIS_RXFTL register  ********************/
#define SPIS_RXFTL_VAL_POS                              (0U)
#define SPIS_RXFTL_VAL_MASK                             (0x1FUL << SPIS_RXFTL_VAL_POS)
#define SPIS_RXFTL_VAL                                  SPIS_RXFTL_VAL_MASK

/******************  Bit definition for SPIS_TXFL register  ********************/
#define SPIS_TXFL_VAL_POS                               (0U)
#define SPIS_TXFL_VAL_MASK                              (0x3FUL << SPIS_TXFL_VAL_POS)
#define SPIS_TXFL_VAL                                   SPIS_TXFL_VAL_MASK

/******************  Bit definition for SPIS_RXFL register  ********************/
#define SPIS_RXFL_VAL_POS                               (0U)
#define SPIS_RXFL_VAL_MASK                              (0x3FUL << SPIS_RXFL_VAL_POS)
#define SPIS_RXFL_VAL                                   SPIS_RXFL_VAL_MASK

/******************  Bit definition for SPIS_STA register  ********************/
#define SPIS_STA_BUSY_POS                               (0U)
#define SPIS_STA_BUSY_MASK                              (0x1UL << SPIS_STA_BUSY_POS)
#define SPIS_STA_BUSY                                   SPIS_STA_BUSY_MASK
#define SPIS_STA_TFNF_POS                               (1U)
#define SPIS_STA_TFNF_MASK                              (0x1UL << SPIS_STA_TFNF_POS)
#define SPIS_STA_TFNF                                   SPIS_STA_TFNF_MASK
#define SPIS_STA_TFE_POS                                (2U)
#define SPIS_STA_TFE_MASK                               (0x1UL << SPIS_STA_TFE_POS)
#define SPIS_STA_TFE                                    SPIS_STA_TFE_MASK
#define SPIS_STA_RFNE_POS                               (3U)
#define SPIS_STA_RFNE_MASK                              (0x1UL << SPIS_STA_RFNE_POS)
#define SPIS_STA_RFNE                                   SPIS_STA_RFNE_MASK
#define SPIS_STA_RFF_POS                                (4U)
#define SPIS_STA_RFF_MASK                               (0x1UL << SPIS_STA_RFF_POS)
#define SPIS_STA_RFF                                    SPIS_STA_RFF_MASK
#define SPIS_STA_TX_ERR_POS                             (5U)
#define SPIS_STA_TX_ERR_MASK                            (0x1UL << SPIS_STA_TX_ERR_POS)
#define SPIS_STA_TX_ERR                                 SPIS_STA_TX_ERR_MASK
#define SPIS_STA_DC_ERR_POS                             (6U)
#define SPIS_STA_DC_ERR_MASK                            (0x1UL << SPIS_STA_DC_ERR_POS)
#define SPIS_STA_DC_ERR                                 SPIS_STA_DC_ERR_MASK

/******************  Bit definition for SPIS_IM register  ********************/
#define SPIS_IM_TFE_POS                                 (0U)
#define SPIS_IM_TFE_MASK                                (0x1UL << SPIS_IM_TFE_POS)
#define SPIS_IM_TFE                                     SPIS_IM_TFE_MASK
#define SPIS_IM_TFO_POS                                 (1U)
#define SPIS_IM_TFO_MASK                                (0x1UL << SPIS_IM_TFO_POS)
#define SPIS_IM_TFO                                     SPIS_IM_TFO_MASK
#define SPIS_IM_RFU_POS                                 (2U)
#define SPIS_IM_RFU_MASK                                (0x1UL << SPIS_IM_RFU_POS)
#define SPIS_IM_RFU                                     SPIS_IM_RFU_MASK
#define SPIS_IM_RFO_POS                                 (3U)
#define SPIS_IM_RFO_MASK                                (0x1UL << SPIS_IM_RFO_POS)
#define SPIS_IM_RFO                                     SPIS_IM_RFO_MASK
#define SPIS_IM_RFF_POS                                 (4U)
#define SPIS_IM_RFF_MASK                                (0x1UL << SPIS_IM_RFF_POS)
#define SPIS_IM_RFF                                     SPIS_IM_RFF_MASK
#define SPIS_IM_MMC_POS                                 (5U)
#define SPIS_IM_MMC_MASK                                (0x1UL << SPIS_IM_MMC_POS)
#define SPIS_IM_MMC                                     SPIS_IM_MMC_MASK

/******************  Bit definition for SPIS_IS register  ********************/
#define SPIS_IS_TFE_POS                                 (0U)
#define SPIS_IS_TFE_MASK                                (0x1UL << SPIS_IS_TFE_POS)
#define SPIS_IS_TFE                                     SPIS_IS_TFE_MASK
#define SPIS_IS_TFO_POS                                 (1U)
#define SPIS_IS_TFO_MASK                                (0x1UL << SPIS_IS_TFO_POS)
#define SPIS_IS_TFO                                     SPIS_IS_TFO_MASK
#define SPIS_IS_RFU_POS                                 (2U)
#define SPIS_IS_RFU_MASK                                (0x1UL << SPIS_IS_RFU_POS)
#define SPIS_IS_RFU                                     SPIS_IS_RFU_MASK
#define SPIS_IS_RFO_POS                                 (3U)
#define SPIS_IS_RFO_MASK                                (0x1UL << SPIS_IS_RFO_POS)
#define SPIS_IS_RFO                                     SPIS_IS_RFO_MASK
#define SPIS_IS_RFF_POS                                 (4U)
#define SPIS_IS_RFF_MASK                                (0x1UL << SPIS_IS_RFF_POS)
#define SPIS_IS_RFF                                     SPIS_IS_RFF_MASK
#define SPIS_IS_MMC_POS                                 (5U)
#define SPIS_IS_MMC_MASK                                (0x1UL << SPIS_IS_MMC_POS)
#define SPIS_IS_MMC                                     SPIS_IS_MMC_MASK

/******************  Bit definition for SPIS_RIS register  ********************/
#define SPIS_RIS_TFE_POS                                (0U)
#define SPIS_RIS_TFE_MASK                               (0x1UL << SPIS_RIS_TFE_POS)
#define SPIS_RIS_TFE                                    SPIS_RIS_TFE_MASK
#define SPIS_RIS_TFO_POS                                (1U)
#define SPIS_RIS_TFO_MASK                               (0x1UL << SPIS_RIS_TFO_POS)
#define SPIS_RIS_TFO                                    SPIS_RIS_TFO_MASK
#define SPIS_RIS_RFU_POS                                (2U)
#define SPIS_RIS_RFU_MASK                               (0x1UL << SPIS_RIS_RFU_POS)
#define SPIS_RIS_RFU                                    SPIS_RIS_RFU_MASK
#define SPIS_RIS_RFO_POS                                (3U)
#define SPIS_RIS_RFO_MASK                               (0x1UL << SPIS_RIS_RFO_POS)
#define SPIS_RIS_RFO                                    SPIS_RIS_RFO_MASK
#define SPIS_RIS_RFF_POS                                (4U)
#define SPIS_RIS_RFF_MASK                               (0x1UL << SPIS_RIS_RFF_POS)
#define SPIS_RIS_RFF                                    SPIS_RIS_RFF_MASK
#define SPIS_RIS_MMC_POS                                (5U)
#define SPIS_RIS_MMC_MASK                               (0x1UL << SPIS_RIS_MMC_POS)
#define SPIS_RIS_MMC                                    SPIS_RIS_MMC_MASK

/******************  Bit definition for SPIS_TXFOIC register  ********************/
#define SPIS_TXFOIC_BIT_POS                             (0U)
#define SPIS_TXFOIC_BIT_MASK                            (0x1UL << SPIS_TXFOIC_BIT_POS)
#define SPIS_TXFOIC_BIT                                 SPIS_TXFOIC_BIT_MASK

/******************  Bit definition for SPIS_RXFOIC register  ********************/
#define SPIS_RXFOIC_BIT_POS                             (0U)
#define SPIS_RXFOIC_BIT_MASK                            (0x1UL << SPIS_RXFOIC_BIT_POS)
#define SPIS_RXFOIC_BIT                                 SPIS_RXFOIC_BIT_MASK

/******************  Bit definition for SPIS_RXFUIC register  ********************/
#define SPIS_RXFUIC_BIT_POS                             (0U)
#define SPIS_RXFUIC_BIT_MASK                            (0x1UL << SPIS_RXFUIC_BIT_POS)
#define SPIS_RXFUIC_BIT                                 SPIS_RXFUIC_BIT_MASK

/******************  Bit definition for SPIS_MMCIC register  ********************/
#define SPIS_MMCIC_BIT_POS                              (0U)
#define SPIS_MMCIC_BIT_MASK                             (0x1UL << SPIS_MMCIC_BIT_POS)
#define SPIS_MMCIC_BIT                                  SPIS_MMCIC_BIT_MASK

/******************  Bit definition for SPIS_EOI register  ********************/
#define SPIS_EOI_BIT_POS                                (0U)
#define SPIS_EOI_BIT_MASK                               (0x1UL << SPIS_EOI_BIT_POS)
#define SPIS_EOI_BIT                                    SPIS_EOI_BIT_MASK

/******************  Bit definition for SPIS_DMAC register  ********************/
#define SPIS_DMAC_RX_EN_POS                             (0U)
#define SPIS_DMAC_RX_EN_MASK                            (0x1UL << SPIS_DMAC_RX_EN_POS)
#define SPIS_DMAC_RX_EN                                 SPIS_DMAC_RX_EN_MASK
#define SPIS_DMAC_TX_EN_POS                             (1U)
#define SPIS_DMAC_TX_EN_MASK                            (0x1UL << SPIS_DMAC_TX_EN_POS)
#define SPIS_DMAC_TX_EN                                 SPIS_DMAC_TX_EN_MASK

/******************  Bit definition for SPIS_DMATDL register  ********************/
#define SPIS_DMATDL_VAL_POS                             (0U)
#define SPIS_DMATDL_VAL_MASK                            (0x1FUL << SPIS_DMATDL_VAL_POS)
#define SPIS_DMATDL_VAL                                 SPIS_DMATDL_VAL_MASK

/******************  Bit definition for SPIS_DMARDL register  ********************/
#define SPIS_DMARDL_VAL_POS                             (0U)
#define SPIS_DMARDL_VAL_MASK                            (0x1FUL << SPIS_DMARDL_VAL_POS)
#define SPIS_DMARDL_VAL                                 SPIS_DMARDL_VAL_MASK

/******************  Bit definition for SPIS_RXSD register  ********************/
#define SPIS_RXSD_VAL_POS                               (0U)
#define SPIS_RXSD_VAL_MASK                              (0xFFUL << SPIS_RXSD_VAL_POS)
#define SPIS_RXSD_VAL                                   SPIS_RXSD_VAL_MASK


/* value type ----------------------------------------------------------------*/

#define SPIS_CTRL_FF_T_MOTOROLA_SPI                     ((uint32_t)0x00000000UL << SPIS_CTRL_FF_POS)
#define SPIS_CTRL_FF_T_TEXAS_ISSP                       ((uint32_t)0x00000001UL << SPIS_CTRL_FF_POS)
#define SPIS_CTRL_FF_T_NATIONAL_SM                      ((uint32_t)0x00000002UL << SPIS_CTRL_FF_POS)

#define SPIS_CTRL_TM_T_TXRX                             ((uint32_t)0x00000000UL << SPIS_CTRL_TM_POS)
#define SPIS_CTRL_TM_T_TX                               ((uint32_t)0x00000001UL << SPIS_CTRL_TM_POS)
#define SPIS_CTRL_TM_T_RX                               ((uint32_t)0x00000002UL << SPIS_CTRL_TM_POS)

#define SPIS_CTRL_DFS32_T_4_BITS						((uint32_t)0x00000003UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_5_BITS						((uint32_t)0x00000004UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_6_BITS						((uint32_t)0x00000005UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_7_BITS						((uint32_t)0x00000006UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_8_BITS						((uint32_t)0x00000007UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_9_BITS						((uint32_t)0x00000008UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_10_BITS						((uint32_t)0x00000009UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_11_BITS						((uint32_t)0x0000000AUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_12_BITS						((uint32_t)0x0000000BUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_13_BITS						((uint32_t)0x0000000CUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_14_BITS						((uint32_t)0x0000000DUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_15_BITS						((uint32_t)0x0000000EUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_16_BITS						((uint32_t)0x0000000FUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_17_BITS						((uint32_t)0x00000010UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_18_BITS						((uint32_t)0x00000011UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_19_BITS						((uint32_t)0x00000012UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_20_BITS						((uint32_t)0x00000013UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_21_BITS						((uint32_t)0x00000014UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_22_BITS						((uint32_t)0x00000015UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_23_BITS						((uint32_t)0x00000016UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_24_BITS						((uint32_t)0x00000017UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_25_BITS						((uint32_t)0x00000018UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_26_BITS						((uint32_t)0x00000019UL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_27_BITS						((uint32_t)0x0000001AUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_28_BITS						((uint32_t)0x0000001BUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_29_BITS						((uint32_t)0x0000001CUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_30_BITS						((uint32_t)0x0000001DUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_31_BITS						((uint32_t)0x0000001EUL << SPIS_CTRL_DFS32_POS)
#define SPIS_CTRL_DFS32_T_32_BITS						((uint32_t)0x0000001FUL << SPIS_CTRL_DFS32_POS)


#define SPIS_CTRL_SCPH_T_MIDDLE							((uint32_t)0x00000000UL << SPIS_CTRL_SCPH_POS)
#define SPIS_CTRL_SCPH_T_START							((uint32_t)0x00000001UL << SPIS_CTRL_SCPH_POS)


#define SPIS_CTRL_SCPOL_T_LOW							((uint32_t)0x00000000UL << SPIS_CTRL_SCPOL_POS)
#define SPIS_CTRL_SCPOL_T_HIGH							((uint32_t)0x00000001UL << SPIS_CTRL_SCPOL_POS)

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_SPIS_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

