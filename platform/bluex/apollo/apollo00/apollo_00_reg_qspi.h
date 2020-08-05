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
#ifndef __APOLLO_00_REG_QSPI_H__
#define __APOLLO_00_REG_QSPI_H__

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
    __IO uint32_t SPIC;                 /* !< SPI Control Register                              0x00F4 */
}reg_qspi_t;


/* bit definition ------------------------------------------------------------*/

/******************  Bit definition for QSPI_CTRL register  ********************/
#define QSPI_CTRL_FF_POS                                (4U)
#define QSPI_CTRL_FF_MASK                               (0x3UL << QSPI_CTRL_FF_POS)
#define QSPI_CTRL_FF                                    QSPI_CTRL_FF_MASK
#define QSPI_CTRL_SCPH_POS                              (6U)
#define QSPI_CTRL_SCPH_MASK                             (0x1UL << QSPI_CTRL_SCPH_POS)
#define QSPI_CTRL_SCPH                                  QSPI_CTRL_SCPH_MASK
#define QSPI_CTRL_SCPOL_POS                             (7U)
#define QSPI_CTRL_SCPOL_MASK                            (0x1UL << QSPI_CTRL_SCPOL_POS)
#define QSPI_CTRL_SCPOL                                 QSPI_CTRL_SCPOL_MASK
#define QSPI_CTRL_TM_POS                                (8U)
#define QSPI_CTRL_TM_MASK                               (0x3UL << QSPI_CTRL_TM_POS)
#define QSPI_CTRL_TM                                    QSPI_CTRL_TM_MASK
#define QSPI_CTRL_SOE_POS                               (10U)
#define QSPI_CTRL_SOE_MASK                              (0x1UL << QSPI_CTRL_SOE_POS)
#define QSPI_CTRL_SOE                                   QSPI_CTRL_SOE_MASK
#define QSPI_CTRL_SRL_POS                               (11U)
#define QSPI_CTRL_SRL_MASK                              (0x1UL << QSPI_CTRL_SRL_POS)
#define QSPI_CTRL_SRL                                   QSPI_CTRL_SRL_MASK
#define QSPI_CTRL_CFS_POS                               (12U)
#define QSPI_CTRL_CFS_MASK                              (0xFUL << QSPI_CTRL_CFS_POS)
#define QSPI_CTRL_CFS                                   QSPI_CTRL_CFS_MASK
#define QSPI_CTRL_DFS32_POS                             (16U)
#define QSPI_CTRL_DFS32_MASK                            (0x1FUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32                                 QSPI_CTRL_DFS32_MASK

/******************  Bit definition for QSPI_NDF register  ********************/
#define QSPI_NDF_VAL_POS                                (0U)
#define QSPI_NDF_VAL_MASK                               (0xFFFFUL << QSPI_NDF_VAL_POS)
#define QSPI_NDF_VAL                                    QSPI_NDF_VAL_MASK

/******************  Bit definition for QSPI_SSIE register  ********************/
#define QSPI_SSIE_BIT_POS                               (0U)
#define QSPI_SSIE_BIT_MASK                              (0x1UL << QSPI_SSIE_BIT_POS)
#define QSPI_SSIE_BIT                                   QSPI_SSIE_BIT_MASK

/******************  Bit definition for QSPI_MC register  ********************/
#define QSPI_MC_TM_POS                                  (0U)
#define QSPI_MC_TM_MASK                                 (0x1UL << QSPI_MC_TM_POS)
#define QSPI_MC_TM                                      QSPI_MC_TM_MASK
#define QSPI_MC_DIR_POS                                 (1U)
#define QSPI_MC_DIR_MASK                                (0x1UL << QSPI_MC_DIR_POS)
#define QSPI_MC_DIR                                     QSPI_MC_DIR_MASK
#define QSPI_MC_HSK_POS                                 (2U)
#define QSPI_MC_HSK_MASK                                (0x1UL << QSPI_MC_HSK_POS)
#define QSPI_MC_HSK                                     QSPI_MC_HSK_MASK


/******************  Bit definition for QSPI_SE register  ********************/
#define QSPI_SE_VAL_POS                                 (0U)
#define QSPI_SE_VAL_MASK                                (0x3UL << QSPI_SE_VAL_POS)
#define QSPI_SE_VAL                                     QSPI_SE_VAL_MASK

/******************  Bit definition for QSPI_BRS register  ********************/
#define QSPI_BRS_CD_POS                                 (0U)
#define QSPI_BRS_CD_MASK                                (0xFFFFUL << QSPI_BRS_CD_POS)
#define QSPI_BRS_CD                                     QSPI_BRS_CD_MASK

/******************  Bit definition for QSPI_TXFTL register  ********************/
#define QSPI_TXFTL_VAL_POS                              (0U)
#define QSPI_TXFTL_VAL_MASK                             (0x1FUL << QSPI_TXFTL_VAL_POS)
#define QSPI_TXFTL_VAL                                  QSPI_TXFTL_VAL_MASK

/******************  Bit definition for QSPI_RXFTL register  ********************/
#define QSPI_RXFTL_VAL_POS                              (0U)
#define QSPI_RXFTL_VAL_MASK                             (0x1FUL << QSPI_RXFTL_VAL_POS)
#define QSPI_RXFTL_VAL                                  QSPI_RXFTL_VAL_MASK

/******************  Bit definition for QSPI_TXFL register  ********************/
#define QSPI_TXFL_VAL_POS                               (0U)
#define QSPI_TXFL_VAL_MASK                              (0x3FUL << QSPI_TXFL_VAL_POS)
#define QSPI_TXFL_VAL                                   QSPI_TXFL_VAL_MASK

/******************  Bit definition for QSPI_RXFL register  ********************/
#define QSPI_RXFL_VAL_POS                               (0U)
#define QSPI_RXFL_VAL_MASK                              (0x3FUL << QSPI_RXFL_VAL_POS)
#define QSPI_RXFL_VAL                                   QSPI_RXFL_VAL_MASK

/******************  Bit definition for QSPI_STA register  ********************/
#define QSPI_STA_BUSY_POS                               (0U)
#define QSPI_STA_BUSY_MASK                              (0x1UL << QSPI_STA_BUSY_POS)
#define QSPI_STA_BUSY                                   QSPI_STA_BUSY_MASK
#define QSPI_STA_TFNF_POS                               (1U)
#define QSPI_STA_TFNF_MASK                              (0x1UL << QSPI_STA_TFNF_POS)
#define QSPI_STA_TFNF                                   QSPI_STA_TFNF_MASK
#define QSPI_STA_TFE_POS                                (2U)
#define QSPI_STA_TFE_MASK                               (0x1UL << QSPI_STA_TFE_POS)
#define QSPI_STA_TFE                                    QSPI_STA_TFE_MASK
#define QSPI_STA_RFNE_POS                               (3U)
#define QSPI_STA_RFNE_MASK                              (0x1UL << QSPI_STA_RFNE_POS)
#define QSPI_STA_RFNE                                   QSPI_STA_RFNE_MASK
#define QSPI_STA_RFF_POS                                (4U)
#define QSPI_STA_RFF_MASK                               (0x1UL << QSPI_STA_RFF_POS)
#define QSPI_STA_RFF                                    QSPI_STA_RFF_MASK
#define QSPI_STA_TX_ERR_POS                             (5U)
#define QSPI_STA_TX_ERR_MASK                            (0x1UL << QSPI_STA_TX_ERR_POS)
#define QSPI_STA_TX_ERR                                 QSPI_STA_TX_ERR_MASK
#define QSPI_STA_DC_ERR_POS                             (6U)
#define QSPI_STA_DC_ERR_MASK                            (0x1UL << QSPI_STA_DC_ERR_POS)
#define QSPI_STA_DC_ERR                                 QSPI_STA_DC_ERR_MASK

/******************  Bit definition for QSPI_IM register  ********************/
#define QSPI_IM_TFE_POS                                 (0U)
#define QSPI_IM_TFE_MASK                                (0x1UL << QSPI_IM_TFE_POS)
#define QSPI_IM_TFE                                     QSPI_IM_TFE_MASK
#define QSPI_IM_TFO_POS                                 (1U)
#define QSPI_IM_TFO_MASK                                (0x1UL << QSPI_IM_TFO_POS)
#define QSPI_IM_TFO                                     QSPI_IM_TFO_MASK
#define QSPI_IM_RFU_POS                                 (2U)
#define QSPI_IM_RFU_MASK                                (0x1UL << QSPI_IM_RFU_POS)
#define QSPI_IM_RFU                                     QSPI_IM_RFU_MASK
#define QSPI_IM_RFO_POS                                 (3U)
#define QSPI_IM_RFO_MASK                                (0x1UL << QSPI_IM_RFO_POS)
#define QSPI_IM_RFO                                     QSPI_IM_RFO_MASK
#define QSPI_IM_RFF_POS                                 (4U)
#define QSPI_IM_RFF_MASK                                (0x1UL << QSPI_IM_RFF_POS)
#define QSPI_IM_RFF                                     QSPI_IM_RFF_MASK
#define QSPI_IM_MMC_POS                                 (5U)
#define QSPI_IM_MMC_MASK                                (0x1UL << QSPI_IM_MMC_POS)
#define QSPI_IM_MMC                                     QSPI_IM_MMC_MASK

/******************  Bit definition for QSPI_IS register  ********************/
#define QSPI_IS_TFE_POS                                 (0U)
#define QSPI_IS_TFE_MASK                                (0x1UL << QSPI_IS_TFE_POS)
#define QSPI_IS_TFE                                     QSPI_IS_TFE_MASK
#define QSPI_IS_TFO_POS                                 (1U)
#define QSPI_IS_TFO_MASK                                (0x1UL << QSPI_IS_TFO_POS)
#define QSPI_IS_TFO                                     QSPI_IS_TFO_MASK
#define QSPI_IS_RFU_POS                                 (2U)
#define QSPI_IS_RFU_MASK                                (0x1UL << QSPI_IS_RFU_POS)
#define QSPI_IS_RFU                                     QSPI_IS_RFU_MASK
#define QSPI_IS_RFO_POS                                 (3U)
#define QSPI_IS_RFO_MASK                                (0x1UL << QSPI_IS_RFO_POS)
#define QSPI_IS_RFO                                     QSPI_IS_RFO_MASK
#define QSPI_IS_RFF_POS                                 (4U)
#define QSPI_IS_RFF_MASK                                (0x1UL << QSPI_IS_RFF_POS)
#define QSPI_IS_RFF                                     QSPI_IS_RFF_MASK
#define QSPI_IS_MMC_POS                                 (5U)
#define QSPI_IS_MMC_MASK                                (0x1UL << QSPI_IS_MMC_POS)
#define QSPI_IS_MMC                                     QSPI_IS_MMC_MASK

/******************  Bit definition for QSPI_RIS register  ********************/
#define QSPI_RIS_TFE_POS                                (0U)
#define QSPI_RIS_TFE_MASK                               (0x1UL << QSPI_RIS_TFE_POS)
#define QSPI_RIS_TFE                                    QSPI_RIS_TFE_MASK
#define QSPI_RIS_TFO_POS                                (1U)
#define QSPI_RIS_TFO_MASK                               (0x1UL << QSPI_RIS_TFO_POS)
#define QSPI_RIS_TFO                                    QSPI_RIS_TFO_MASK
#define QSPI_RIS_RFU_POS                                (2U)
#define QSPI_RIS_RFU_MASK                               (0x1UL << QSPI_RIS_RFU_POS)
#define QSPI_RIS_RFU                                    QSPI_RIS_RFU_MASK
#define QSPI_RIS_RFO_POS                                (3U)
#define QSPI_RIS_RFO_MASK                               (0x1UL << QSPI_RIS_RFO_POS)
#define QSPI_RIS_RFO                                    QSPI_RIS_RFO_MASK
#define QSPI_RIS_RFF_POS                                (4U)
#define QSPI_RIS_RFF_MASK                               (0x1UL << QSPI_RIS_RFF_POS)
#define QSPI_RIS_RFF                                    QSPI_RIS_RFF_MASK
#define QSPI_RIS_MMC_POS                                (5U)
#define QSPI_RIS_MMC_MASK                               (0x1UL << QSPI_RIS_MMC_POS)
#define QSPI_RIS_MMC                                    QSPI_RIS_MMC_MASK

/******************  Bit definition for QSPI_TXFOIC register  ********************/
#define QSPI_TXFOIC_BIT_POS                             (0U)
#define QSPI_TXFOIC_BIT_MASK                            (0x1UL << QSPI_TXFOIC_BIT_POS)
#define QSPI_TXFOIC_BIT                                 QSPI_TXFOIC_BIT_MASK

/******************  Bit definition for QSPI_RXFOIC register  ********************/
#define QSPI_RXFOIC_BIT_POS                             (0U)
#define QSPI_RXFOIC_BIT_MASK                            (0x1UL << QSPI_RXFOIC_BIT_POS)
#define QSPI_RXFOIC_BIT                                 QSPI_RXFOIC_BIT_MASK

/******************  Bit definition for QSPI_RXFUIC register  ********************/
#define QSPI_RXFUIC_BIT_POS                             (0U)
#define QSPI_RXFUIC_BIT_MASK                            (0x1UL << QSPI_RXFUIC_BIT_POS)
#define QSPI_RXFUIC_BIT                                 QSPI_RXFUIC_BIT_MASK

/******************  Bit definition for QSPI_MMCIC register  ********************/
#define QSPI_MMCIC_BIT_POS                              (0U)
#define QSPI_MMCIC_BIT_MASK                             (0x1UL << QSPI_MMCIC_BIT_POS)
#define QSPI_MMCIC_BIT                                  QSPI_MMCIC_BIT_MASK

/******************  Bit definition for QSPI_EOI register  ********************/
#define QSPI_EOI_BIT_POS                                (0U)
#define QSPI_EOI_BIT_MASK                               (0x1UL << QSPI_EOI_BIT_POS)
#define QSPI_EOI_BIT                                    QSPI_EOI_BIT_MASK

/******************  Bit definition for QSPI_DMAC register  ********************/
#define QSPI_DMAC_RX_EN_POS                             (0U)
#define QSPI_DMAC_RX_EN_MASK                            (0x1UL << QSPI_DMAC_RX_EN_POS)
#define QSPI_DMAC_RX_EN                                 QSPI_DMAC_RX_EN_MASK
#define QSPI_DMAC_TX_EN_POS                             (1U)
#define QSPI_DMAC_TX_EN_MASK                            (0x1UL << QSPI_DMAC_TX_EN_POS)
#define QSPI_DMAC_TX_EN                                 QSPI_DMAC_TX_EN_MASK

/******************  Bit definition for QSPI_DMATDL register  ********************/
#define QSPI_DMATDL_VAL_POS                             (0U)
#define QSPI_DMATDL_VAL_MASK                            (0x1FUL << QSPI_DMATDL_VAL_POS)
#define QSPI_DMATDL_VAL                                 QSPI_DMATDL_VAL_MASK

/******************  Bit definition for QSPI_DMARDL register  ********************/
#define QSPI_DMARDL_VAL_POS                             (0U)
#define QSPI_DMARDL_VAL_MASK                            (0x1FUL << QSPI_DMARDL_VAL_POS)
#define QSPI_DMARDL_VAL                                 QSPI_DMARDL_VAL_MASK

/******************  Bit definition for QSPI_RXSD register  ********************/
#define QSPI_RXSD_VAL_POS                               (0U)
#define QSPI_RXSD_VAL_MASK                              (0xFFUL << QSPI_RXSD_VAL_POS)
#define QSPI_RXSD_VAL                                   QSPI_RXSD_VAL_MASK

/******************  Bit definition for QSPI_SPIC register  ********************/
#define QSPI_SPIC_TX_TYPE_POS                           (0U)
#define QSPI_SPIC_TX_TYPE_MASK                          (0x3UL << QSPI_SPIC_TX_TYPE_POS)
#define QSPI_SPIC_TX_TYPE                               QSPI_SPIC_TX_TYPE_MASK
#define QSPI_SPIC_ADDR_LEN_POS                          (2U)
#define QSPI_SPIC_ADDR_LEN_MASK                         (0xFUL << QSPI_SPIC_ADDR_LEN_POS)
#define QSPI_SPIC_ADDR_LEN                              QSPI_SPIC_ADDR_LEN_MASK
#define QSPI_SPIC_CMD_LEN_POS                           (8U)
#define QSPI_SPIC_CMD_LEN_MASK                          (0x3UL << QSPI_SPIC_CMD_LEN_POS)
#define QSPI_SPIC_CMD_LEN                               QSPI_SPIC_CMD_LEN_MASK
#define QSPI_SPIC_WAIT_CYCLE_POS                        (11U)
#define QSPI_SPIC_WAIT_CYCLE_MASK                       (0xFUL << QSPI_SPIC_WAIT_CYCLE_POS)
#define QSPI_SPIC_WAIT_CYCLE                            QSPI_SPIC_WAIT_CYCLE_MASK


/* value type ----------------------------------------------------------------*/

#define QSPI_CTRL_FF_T_MOTOROLA_SPI                     ((uint32_t)0x00000000UL << QSPI_CTRL_FF_POS)
#define QSPI_CTRL_FF_T_TEXAS_ISSP                       ((uint32_t)0x00000001UL << QSPI_CTRL_FF_POS)
#define QSPI_CTRL_FF_T_NATIONAL_SM                      ((uint32_t)0x00000002UL << QSPI_CTRL_FF_POS)

#define QSPI_CTRL_TM_T_TXRX                             ((uint32_t)0x00000000UL << QSPI_CTRL_TM_POS)
#define QSPI_CTRL_TM_T_TX                               ((uint32_t)0x00000001UL << QSPI_CTRL_TM_POS)
#define QSPI_CTRL_TM_T_RX                               ((uint32_t)0x00000002UL << QSPI_CTRL_TM_POS)

#define QSPI_CTRL_DFS32_T_4_BITS						((uint32_t)0x00000003UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_5_BITS						((uint32_t)0x00000004UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_6_BITS						((uint32_t)0x00000005UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_7_BITS						((uint32_t)0x00000006UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_8_BITS						((uint32_t)0x00000007UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_9_BITS						((uint32_t)0x00000008UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_10_BITS						((uint32_t)0x00000009UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_11_BITS						((uint32_t)0x0000000AUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_12_BITS						((uint32_t)0x0000000BUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_13_BITS						((uint32_t)0x0000000CUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_14_BITS						((uint32_t)0x0000000DUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_15_BITS						((uint32_t)0x0000000EUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_16_BITS						((uint32_t)0x0000000FUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_17_BITS						((uint32_t)0x00000010UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_18_BITS						((uint32_t)0x00000011UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_19_BITS						((uint32_t)0x00000012UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_20_BITS						((uint32_t)0x00000013UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_21_BITS						((uint32_t)0x00000014UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_22_BITS						((uint32_t)0x00000015UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_23_BITS						((uint32_t)0x00000016UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_24_BITS						((uint32_t)0x00000017UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_25_BITS						((uint32_t)0x00000018UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_26_BITS						((uint32_t)0x00000019UL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_27_BITS						((uint32_t)0x0000001AUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_28_BITS						((uint32_t)0x0000001BUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_29_BITS						((uint32_t)0x0000001CUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_30_BITS						((uint32_t)0x0000001DUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_31_BITS						((uint32_t)0x0000001EUL << QSPI_CTRL_DFS32_POS)
#define QSPI_CTRL_DFS32_T_32_BITS						((uint32_t)0x0000001FUL << QSPI_CTRL_DFS32_POS)



























/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_QSPI_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

