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
#ifndef __APOLLO_00_REG_SPIM_H__
#define __APOLLO_00_REG_SPIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/
typedef struct {
    __IO uint32_t CTRL;                 /* !< Control Register                                  0x0000 */
    __IO uint32_t NDF;                  /* !< Number of Data Frames.                            0x0004 */
    __IO uint32_t SSIE;                 /* !< SSI Enable.                                       0x0008 */
    __IO uint32_t MC;                   /* !< Microwire Control Register                        0x000C */
    __IO uint32_t SE;                   /* !< Slave Enable Register                             0x0010 */
    __IO uint32_t BRS;                  /* !< Baud Rate Select                                  0x0014 */
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
         uint32_t reserved0[35];        /* !< description                                       0x0064 */
    __IO uint32_t RXSD;                 /* !< Rx Sample Delay Register                          0x00F0 */
}reg_spim_t;


/* bit definition ------------------------------------------------------------*/

/******************  Bit definition for SPIM_CTRL register  ********************/
#define SPIM_CTRL_FF_POS                                (4U)
#define SPIM_CTRL_FF_MASK                               (0x3UL << SPIM_CTRL_FF_POS)
#define SPIM_CTRL_FF                                    SPIM_CTRL_FF_MASK
#define SPIM_CTRL_SCPH_POS                              (6U)
#define SPIM_CTRL_SCPH_MASK                             (0x1UL << SPIM_CTRL_SCPH_POS)
#define SPIM_CTRL_SCPH                                  SPIM_CTRL_SCPH_MASK
#define SPIM_CTRL_SCPOL_POS                             (7U)
#define SPIM_CTRL_SCPOL_MASK                            (0x1UL << SPIM_CTRL_SCPOL_POS)
#define SPIM_CTRL_SCPOL                                 SPIM_CTRL_SCPOL_MASK
#define SPIM_CTRL_TM_POS                                (8U)
#define SPIM_CTRL_TM_MASK                               (0x3UL << SPIM_CTRL_TM_POS)
#define SPIM_CTRL_TM                                    SPIM_CTRL_TM_MASK
#define SPIM_CTRL_SOE_POS                               (10U)
#define SPIM_CTRL_SOE_MASK                              (0x1UL << SPIM_CTRL_SOE_POS)
#define SPIM_CTRL_SOE                                   SPIM_CTRL_SOE_MASK
#define SPIM_CTRL_SRL_POS                               (11U)
#define SPIM_CTRL_SRL_MASK                              (0x1UL << SPIM_CTRL_SRL_POS)
#define SPIM_CTRL_SRL                                   SPIM_CTRL_SRL_MASK
#define SPIM_CTRL_CFS_POS                               (12U)
#define SPIM_CTRL_CFS_MASK                              (0xFUL << SPIM_CTRL_CFS_POS)
#define SPIM_CTRL_CFS                                   SPIM_CTRL_CFS_MASK
#define SPIM_CTRL_DFS32_POS                             (16U)
#define SPIM_CTRL_DFS32_MASK                            (0x1FUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32                                 SPIM_CTRL_DFS32_MASK

/******************  Bit definition for SPIM_NDF register  ********************/
#define SPIM_NDF_VAL_POS                                (0U)
#define SPIM_NDF_VAL_MASK                               (0xFFFFUL << SPIM_NDF_VAL_POS)
#define SPIM_NDF_VAL                                    SPIM_NDF_VAL_MASK

/******************  Bit definition for SPIM_SSIE register  ********************/
#define SPIM_SSIE_BIT_POS                               (0U)
#define SPIM_SSIE_BIT_MASK                              (0x1UL << SPIM_SSIE_BIT_POS)
#define SPIM_SSIE_BIT                                   SPIM_SSIE_BIT_MASK

/******************  Bit definition for SPIM_MC register  ********************/
#define SPIM_MC_TM_POS                                  (0U)
#define SPIM_MC_TM_MASK                                 (0x1UL << SPIM_MC_TM_POS)
#define SPIM_MC_TM                                      SPIM_MC_TM_MASK
#define SPIM_MC_DIR_POS                                 (1U)
#define SPIM_MC_DIR_MASK                                (0x1UL << SPIM_MC_DIR_POS)
#define SPIM_MC_DIR                                     SPIM_MC_DIR_MASK
#define SPIM_MC_HSK_POS                                 (2U)
#define SPIM_MC_HSK_MASK                                (0x1UL << SPIM_MC_HSK_POS)
#define SPIM_MC_HSK                                     SPIM_MC_HSK_MASK


/******************  Bit definition for SPIM_SE register  ********************/
#define SPIM_SE_VAL_POS                                 (0U)
#define SPIM_SE_VAL_MASK                                (0x3UL << SPIM_SE_VAL_POS)
#define SPIM_SE_VAL                                     SPIM_SE_VAL_MASK

/******************  Bit definition for SPIM_BRS register  ********************/
#define SPIM_BRS_CD_POS                                 (0U)
#define SPIM_BRS_CD_MASK                                (0xFFFFUL << SPIM_BRS_CD_POS)
#define SPIM_BRS_CD                                     SPIM_BRS_CD_MASK

/******************  Bit definition for SPIM_TXFTL register  ********************/
#define SPIM_TXFTL_VAL_POS                              (0U)
#define SPIM_TXFTL_VAL_MASK                             (0x1FUL << SPIM_TXFTL_VAL_POS)
#define SPIM_TXFTL_VAL                                  SPIM_TXFTL_VAL_MASK

/******************  Bit definition for SPIM_RXFTL register  ********************/
#define SPIM_RXFTL_VAL_POS                              (0U)
#define SPIM_RXFTL_VAL_MASK                             (0x1FUL << SPIM_RXFTL_VAL_POS)
#define SPIM_RXFTL_VAL                                  SPIM_RXFTL_VAL_MASK

/******************  Bit definition for SPIM_TXFL register  ********************/
#define SPIM_TXFL_VAL_POS                               (0U)
#define SPIM_TXFL_VAL_MASK                              (0x3FUL << SPIM_TXFL_VAL_POS)
#define SPIM_TXFL_VAL                                   SPIM_TXFL_VAL_MASK

/******************  Bit definition for SPIM_RXFL register  ********************/
#define SPIM_RXFL_VAL_POS                               (0U)
#define SPIM_RXFL_VAL_MASK                              (0x3FUL << SPIM_RXFL_VAL_POS)
#define SPIM_RXFL_VAL                                   SPIM_RXFL_VAL_MASK

/******************  Bit definition for SPIM_STA register  ********************/
#define SPIM_STA_BUSY_POS                               (0U)
#define SPIM_STA_BUSY_MASK                              (0x1UL << SPIM_STA_BUSY_POS)
#define SPIM_STA_BUSY                                   SPIM_STA_BUSY_MASK
#define SPIM_STA_TFNF_POS                               (1U)
#define SPIM_STA_TFNF_MASK                              (0x1UL << SPIM_STA_TFNF_POS)
#define SPIM_STA_TFNF                                   SPIM_STA_TFNF_MASK
#define SPIM_STA_TFE_POS                                (2U)
#define SPIM_STA_TFE_MASK                               (0x1UL << SPIM_STA_TFE_POS)
#define SPIM_STA_TFE                                    SPIM_STA_TFE_MASK
#define SPIM_STA_RFNE_POS                               (3U)
#define SPIM_STA_RFNE_MASK                              (0x1UL << SPIM_STA_RFNE_POS)
#define SPIM_STA_RFNE                                   SPIM_STA_RFNE_MASK
#define SPIM_STA_RFF_POS                                (4U)
#define SPIM_STA_RFF_MASK                               (0x1UL << SPIM_STA_RFF_POS)
#define SPIM_STA_RFF                                    SPIM_STA_RFF_MASK
#define SPIM_STA_TX_ERR_POS                             (5U)
#define SPIM_STA_TX_ERR_MASK                            (0x1UL << SPIM_STA_TX_ERR_POS)
#define SPIM_STA_TX_ERR                                 SPIM_STA_TX_ERR_MASK
#define SPIM_STA_DC_ERR_POS                             (6U)
#define SPIM_STA_DC_ERR_MASK                            (0x1UL << SPIM_STA_DC_ERR_POS)
#define SPIM_STA_DC_ERR                                 SPIM_STA_DC_ERR_MASK

/******************  Bit definition for SPIM_IM register  ********************/
#define SPIM_IM_TFE_POS                                 (0U)
#define SPIM_IM_TFE_MASK                                (0x1UL << SPIM_IM_TFE_POS)
#define SPIM_IM_TFE                                     SPIM_IM_TFE_MASK
#define SPIM_IM_TFO_POS                                 (1U)
#define SPIM_IM_TFO_MASK                                (0x1UL << SPIM_IM_TFO_POS)
#define SPIM_IM_TFO                                     SPIM_IM_TFO_MASK
#define SPIM_IM_RFU_POS                                 (2U)
#define SPIM_IM_RFU_MASK                                (0x1UL << SPIM_IM_RFU_POS)
#define SPIM_IM_RFU                                     SPIM_IM_RFU_MASK
#define SPIM_IM_RFO_POS                                 (3U)
#define SPIM_IM_RFO_MASK                                (0x1UL << SPIM_IM_RFO_POS)
#define SPIM_IM_RFO                                     SPIM_IM_RFO_MASK
#define SPIM_IM_RFF_POS                                 (4U)
#define SPIM_IM_RFF_MASK                                (0x1UL << SPIM_IM_RFF_POS)
#define SPIM_IM_RFF                                     SPIM_IM_RFF_MASK
#define SPIM_IM_MMC_POS                                 (5U)
#define SPIM_IM_MMC_MASK                                (0x1UL << SPIM_IM_MMC_POS)
#define SPIM_IM_MMC                                     SPIM_IM_MMC_MASK

/******************  Bit definition for SPIM_IS register  ********************/
#define SPIM_IS_TFE_POS                                 (0U)
#define SPIM_IS_TFE_MASK                                (0x1UL << SPIM_IS_TFE_POS)
#define SPIM_IS_TFE                                     SPIM_IS_TFE_MASK
#define SPIM_IS_TFO_POS                                 (1U)
#define SPIM_IS_TFO_MASK                                (0x1UL << SPIM_IS_TFO_POS)
#define SPIM_IS_TFO                                     SPIM_IS_TFO_MASK
#define SPIM_IS_RFU_POS                                 (2U)
#define SPIM_IS_RFU_MASK                                (0x1UL << SPIM_IS_RFU_POS)
#define SPIM_IS_RFU                                     SPIM_IS_RFU_MASK
#define SPIM_IS_RFO_POS                                 (3U)
#define SPIM_IS_RFO_MASK                                (0x1UL << SPIM_IS_RFO_POS)
#define SPIM_IS_RFO                                     SPIM_IS_RFO_MASK
#define SPIM_IS_RFF_POS                                 (4U)
#define SPIM_IS_RFF_MASK                                (0x1UL << SPIM_IS_RFF_POS)
#define SPIM_IS_RFF                                     SPIM_IS_RFF_MASK
#define SPIM_IS_MMC_POS                                 (5U)
#define SPIM_IS_MMC_MASK                                (0x1UL << SPIM_IS_MMC_POS)
#define SPIM_IS_MMC                                     SPIM_IS_MMC_MASK

/******************  Bit definition for SPIM_RIS register  ********************/
#define SPIM_RIS_TFE_POS                                (0U)
#define SPIM_RIS_TFE_MASK                               (0x1UL << SPIM_RIS_TFE_POS)
#define SPIM_RIS_TFE                                    SPIM_RIS_TFE_MASK
#define SPIM_RIS_TFO_POS                                (1U)
#define SPIM_RIS_TFO_MASK                               (0x1UL << SPIM_RIS_TFO_POS)
#define SPIM_RIS_TFO                                    SPIM_RIS_TFO_MASK
#define SPIM_RIS_RFU_POS                                (2U)
#define SPIM_RIS_RFU_MASK                               (0x1UL << SPIM_RIS_RFU_POS)
#define SPIM_RIS_RFU                                    SPIM_RIS_RFU_MASK
#define SPIM_RIS_RFO_POS                                (3U)
#define SPIM_RIS_RFO_MASK                               (0x1UL << SPIM_RIS_RFO_POS)
#define SPIM_RIS_RFO                                    SPIM_RIS_RFO_MASK
#define SPIM_RIS_RFF_POS                                (4U)
#define SPIM_RIS_RFF_MASK                               (0x1UL << SPIM_RIS_RFF_POS)
#define SPIM_RIS_RFF                                    SPIM_RIS_RFF_MASK
#define SPIM_RIS_MMC_POS                                (5U)
#define SPIM_RIS_MMC_MASK                               (0x1UL << SPIM_RIS_MMC_POS)
#define SPIM_RIS_MMC                                    SPIM_RIS_MMC_MASK

/******************  Bit definition for SPIM_TXFOIC register  ********************/
#define SPIM_TXFOIC_BIT_POS                             (0U)
#define SPIM_TXFOIC_BIT_MASK                            (0x1UL << SPIM_TXFOIC_BIT_POS)
#define SPIM_TXFOIC_BIT                                 SPIM_TXFOIC_BIT_MASK

/******************  Bit definition for SPIM_RXFOIC register  ********************/
#define SPIM_RXFOIC_BIT_POS                             (0U)
#define SPIM_RXFOIC_BIT_MASK                            (0x1UL << SPIM_RXFOIC_BIT_POS)
#define SPIM_RXFOIC_BIT                                 SPIM_RXFOIC_BIT_MASK

/******************  Bit definition for SPIM_RXFUIC register  ********************/
#define SPIM_RXFUIC_BIT_POS                             (0U)
#define SPIM_RXFUIC_BIT_MASK                            (0x1UL << SPIM_RXFUIC_BIT_POS)
#define SPIM_RXFUIC_BIT                                 SPIM_RXFUIC_BIT_MASK

/******************  Bit definition for SPIM_MMCIC register  ********************/
#define SPIM_MMCIC_BIT_POS                              (0U)
#define SPIM_MMCIC_BIT_MASK                             (0x1UL << SPIM_MMCIC_BIT_POS)
#define SPIM_MMCIC_BIT                                  SPIM_MMCIC_BIT_MASK

/******************  Bit definition for SPIM_EOI register  ********************/
#define SPIM_EOI_BIT_POS                                (0U)
#define SPIM_EOI_BIT_MASK                               (0x1UL << SPIM_EOI_BIT_POS)
#define SPIM_EOI_BIT                                    SPIM_EOI_BIT_MASK

/******************  Bit definition for SPIM_DMAC register  ********************/
#define SPIM_DMAC_RX_EN_POS                             (0U)
#define SPIM_DMAC_RX_EN_MASK                            (0x1UL << SPIM_DMAC_RX_EN_POS)
#define SPIM_DMAC_RX_EN                                 SPIM_DMAC_RX_EN_MASK
#define SPIM_DMAC_TX_EN_POS                             (1U)
#define SPIM_DMAC_TX_EN_MASK                            (0x1UL << SPIM_DMAC_TX_EN_POS)
#define SPIM_DMAC_TX_EN                                 SPIM_DMAC_TX_EN_MASK

/******************  Bit definition for SPIM_DMATDL register  ********************/
#define SPIM_DMATDL_VAL_POS                             (0U)
#define SPIM_DMATDL_VAL_MASK                            (0x1FUL << SPIM_DMATDL_VAL_POS)
#define SPIM_DMATDL_VAL                                 SPIM_DMATDL_VAL_MASK

/******************  Bit definition for SPIM_DMARDL register  ********************/
#define SPIM_DMARDL_VAL_POS                             (0U)
#define SPIM_DMARDL_VAL_MASK                            (0x1FUL << SPIM_DMARDL_VAL_POS)
#define SPIM_DMARDL_VAL                                 SPIM_DMARDL_VAL_MASK

/******************  Bit definition for SPIM_RXSD register  ********************/
#define SPIM_RXSD_VAL_POS                               (0U)
#define SPIM_RXSD_VAL_MASK                              (0xFFUL << SPIM_RXSD_VAL_POS)
#define SPIM_RXSD_VAL                                   SPIM_RXSD_VAL_MASK


/* value type ----------------------------------------------------------------*/

#define SPIM_CTRL_FF_T_MOTOROLA_SPI                     ((uint32_t)0x00000000UL << SPIM_CTRL_FF_POS)
#define SPIM_CTRL_FF_T_TEXAS_ISSP                       ((uint32_t)0x00000001UL << SPIM_CTRL_FF_POS)
#define SPIM_CTRL_FF_T_NATIONAL_SM                      ((uint32_t)0x00000002UL << SPIM_CTRL_FF_POS)

#define SPIM_CTRL_TM_T_TXRX                             ((uint32_t)0x00000000UL << SPIM_CTRL_TM_POS)
#define SPIM_CTRL_TM_T_TX                               ((uint32_t)0x00000001UL << SPIM_CTRL_TM_POS)
#define SPIM_CTRL_TM_T_RX                               ((uint32_t)0x00000002UL << SPIM_CTRL_TM_POS)

#define SPIM_CTRL_DFS32_T_4_BITS						((uint32_t)0x00000003UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_5_BITS						((uint32_t)0x00000004UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_6_BITS						((uint32_t)0x00000005UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_7_BITS						((uint32_t)0x00000006UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_8_BITS						((uint32_t)0x00000007UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_9_BITS						((uint32_t)0x00000008UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_10_BITS						((uint32_t)0x00000009UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_11_BITS						((uint32_t)0x0000000AUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_12_BITS						((uint32_t)0x0000000BUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_13_BITS						((uint32_t)0x0000000CUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_14_BITS						((uint32_t)0x0000000DUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_15_BITS						((uint32_t)0x0000000EUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_16_BITS						((uint32_t)0x0000000FUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_17_BITS						((uint32_t)0x00000010UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_18_BITS						((uint32_t)0x00000011UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_19_BITS						((uint32_t)0x00000012UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_20_BITS						((uint32_t)0x00000013UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_21_BITS						((uint32_t)0x00000014UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_22_BITS						((uint32_t)0x00000015UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_23_BITS						((uint32_t)0x00000016UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_24_BITS						((uint32_t)0x00000017UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_25_BITS						((uint32_t)0x00000018UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_26_BITS						((uint32_t)0x00000019UL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_27_BITS						((uint32_t)0x0000001AUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_28_BITS						((uint32_t)0x0000001BUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_29_BITS						((uint32_t)0x0000001CUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_30_BITS						((uint32_t)0x0000001DUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_31_BITS						((uint32_t)0x0000001EUL << SPIM_CTRL_DFS32_POS)
#define SPIM_CTRL_DFS32_T_32_BITS						((uint32_t)0x0000001FUL << SPIM_CTRL_DFS32_POS)


#define SPIM_CTRL_SCPH_T_MIDDLE							((uint32_t)0x00000000UL << SPIM_CTRL_SCPH_POS)
#define SPIM_CTRL_SCPH_T_START							((uint32_t)0x00000001UL << SPIM_CTRL_SCPH_POS)


#define SPIM_CTRL_SCPOL_T_LOW							((uint32_t)0x00000000UL << SPIM_CTRL_SCPOL_POS)
#define SPIM_CTRL_SCPOL_T_HIGH							((uint32_t)0x00000001UL << SPIM_CTRL_SCPOL_POS)


/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_SPIM_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

