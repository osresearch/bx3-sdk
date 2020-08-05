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
#ifndef __APOLLO_00_REG_DMA_H__
#define __APOLLO_00_REG_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/
typedef struct {
    __IO uint32_t SA;                   /* !< Source Address        0x0000 */
         uint32_t reserve0;             /* !<                       0x0004 */
    __IO uint32_t DA;                   /* !< Destination Address   0x0008 */
         uint32_t reserve1[3];          /* !<                       0x000C */
    __IO uint32_t CTRL0;                /* !< Control 0             0x0018 */
    __IO uint32_t CTRL1;                /* !< Control 1             0x001C */
         uint32_t reserve2[8];          /* !<                       0x0020 */
    __IO uint32_t CFG0;                 /* !< Configuration 0       0x0040 */
    __IO uint32_t CFG1;                 /* !< Configuration 1       0x0044 */
} reg_dmac_t;


/* <! BTCI – Block Transfer Complete Interrupt (IntBlock)             */
/* <! DCI – Destination Transaction Complete Interrupt (IntDstTran)   */
/* <! EI – Error Interrupt (IntErr)                                   */
/* <! STCI – Source Transaction Complete Interrupt (IntSrcTran)       */
/* <! TCI – Transfer Complete Interrupt (IntTfr)                      */
typedef struct {
    __I  uint32_t RSTCI;                /* Raw Status for TCI                                0x2C0  */
         uint32_t reserve0;
    __I  uint32_t RSBTCI;               /* Raw Status for BTCI                               0x2C8  */
         uint32_t reserve1;
    __I  uint32_t RSSTCI;               /* Raw Status for STCI                               0x2D0  */
         uint32_t reserve2;
    __I  uint32_t RSDCI;                /* Raw Status for DCI                                0x2D8  */
         uint32_t reserve3;
    __I  uint32_t RSEI;                 /* Raw Status for EI                                 0x2E0  */
         uint32_t reserve4;

    __I  uint32_t STCI;                 /* Status for TCI                                    0x2E8  */
         uint32_t reserve5;
    __I  uint32_t SBTCI;                /* Status for BTCI                                   0x2F0  */
         uint32_t reserve6;
    __I  uint32_t SSTCI;                /* Status for STCI                                   0x2F8  */
         uint32_t reserve7;
    __I  uint32_t SDCI;                 /* Status for DCI                                    0x300  */
         uint32_t reserve8;
    __I  uint32_t SEI;                  /* Status for EI                                     0x308  */
         uint32_t reserve9;

    __IO uint32_t MTCI;                 /* Mask for TCI                                      0x310  */
         uint32_t reserve10;
    __IO uint32_t MBTCI;                /* Mask for BTCI                                     0x318  */
         uint32_t reserve11;
    __IO uint32_t MSTCI;                /* Mask for STCI                                     0x320  */
         uint32_t reserve12;
    __IO uint32_t MDCI;                 /* Mask for DCI                                      0x328  */
         uint32_t reserve13;
    __IO uint32_t MEI;                  /* Mask for EI                                       0x330  */
         uint32_t reserve14;

    __O  uint32_t CTCI;                 /* Clear for TCI                                     0x338  */
         uint32_t reserve15;
    __O  uint32_t CBTCI;                /* Clear for BTCI                                    0x340  */
         uint32_t reserve16;
    __O  uint32_t CSTCI;                /* Clear for STCI                                    0x348  */
         uint32_t reserve17;
    __O  uint32_t CDCI;                 /* Clear for DCI                                     0x350  */
         uint32_t reserve18;
    __O  uint32_t CEI;                  /* Clear for EI                                      0x358  */
         uint32_t reserve19;

    __I  uint32_t CIS;                  /* Combined Interrupt Status Register                0x360  */
         uint32_t reserve20;
    __IO uint32_t SRCSTR;               /* Source(SRC) Software Transaction Request Register 0x368  */
         uint32_t reserved21;
    __IO uint32_t DSTR;                 /* Destination Software Transaction Request Register 0x370  */
         uint32_t reserved22;
    __IO uint32_t SGLSTR;               /* Single(SGL) Source Transaction Request Register   0x378  */
         uint32_t reserved23;
    __IO uint32_t SDTR;                 /* Single Destination Transaction Request Register   0x380  */
         uint32_t reserved24;
    __IO uint32_t LSTR;                 /* Last Source Transaction Request Register          0x388  */
         uint32_t reserved25;
    __IO uint32_t LDTR;                 /* Last Destination Transaction Request Register     0x390  */
         uint32_t reserved26;

    __IO uint32_t EN;                   /* Enable Register                                   0x398  */
         uint32_t reserved27;
    __IO uint32_t CE;                   /* Channel Enable Register                           0x3A0  */
         uint32_t reserved28;
    __IO uint32_t ID;                   /* ID Register                                       0x3A8  */
         uint32_t reserved29;
    __IO uint32_t TEST;                 /* Test Register                                     0x3B0  */
         uint32_t reserved30[7];
    __IO uint32_t CP5;                  /* Component Parameters for channel 5                0x3D4  */
    __IO uint32_t CP4;                  /* Component Parameters for channel 4                0x3D8  */
    __IO uint32_t CP3;                  /* Component Parameters for channel 3                0x3DC  */
    __IO uint32_t CP2;                  /* Component Parameters for channel 2                0x3E0  */
    __IO uint32_t CP1;                  /* Component Parameters for channel 1                0x3E4  */
    __IO uint32_t CP0;                  /* Component Parameters for channel 0                0x3E8  */
    __IO uint32_t MBTP;                 /* Multi-Block type parameter for Channel 0 to Channel 7    0x3EC  */
    __IO uint32_t MBSP;                 /* maximum block size parameters for Channel 0 to Channel 7 0x3F0  */
    __IO uint32_t TLP;                  /* top-level parameters                              0x308  0x3F4  */
    __IO uint32_t TYPE;                 /* Component TYPE                                    0x308  */
    __IO uint32_t VER;                  /* Component Version                                 0x308  */
} reg_dmax_t;

/* bit definition ------------------------------------------------------------*/

/*****************  Bit definition for DMAC_SA register  **********************/
#define DMAC_SA_VAL_POS                                 (0U)
#define DMAC_SA_VAL_MASK                                (0xFFFFFFFFUL << DMAC_SA_VAL_POS)
#define DMAC_SA_VAL                                     DMAC_SA_VAL_MASK

/*****************  Bit definition for DMAC_DA register  **********************/
#define DMAC_DA_VAL_POS                                 (0U)
#define DMAC_DA_VAL_MASK                                (0xFFFFFFFFUL << DMAC_DA_VAL_POS)
#define DMAC_DA_VAL                                     DMAC_DA_VAL_MASK

/*****************  Bit definition for DMAC_CTRL0 register  *******************/
#define DMAC_CTRL0_IE_POS                               (0U)            /*!< Interrupt Enable */
#define DMAC_CTRL0_IE_MASK                              (0x1UL << DMAC_CTRL0_IE_POS)
#define DMAC_CTRL0_IE                                   DMAC_CTRL0_IE_MASK
#define DMAC_CTRL0_DTW_POS                              (1U)            /*!< Destination Transfer Width */
#define DMAC_CTRL0_DTW_MASK                             (0x7UL << DMAC_CTRL0_DTW_POS)
#define DMAC_CTRL0_DTW                                  DMAC_CTRL0_DTW_MASK
#define DMAC_CTRL0_STW_POS                              (4U)            /*!< Source Transfer Width */
#define DMAC_CTRL0_STW_MASK                             (0x7UL << DMAC_CTRL0_STW_POS)
#define DMAC_CTRL0_STW                                  DMAC_CTRL0_STW_MASK
#define DMAC_CTRL0_DAI_POS                              (7U)            /*!< Destination Address Increment */
#define DMAC_CTRL0_DAI_MASK                             (0x3UL << DMAC_CTRL0_DAI_POS)
#define DMAC_CTRL0_DAI                                  DMAC_CTRL0_DAI_MASK
#define DMAC_CTRL0_SAI_POS                              (9U)            /*!< Source Address Increment */
#define DMAC_CTRL0_SAI_MASK                             (0x3UL << DMAC_CTRL0_SAI_POS)
#define DMAC_CTRL0_SAI                                  DMAC_CTRL0_SAI_MASK
#define DMAC_CTRL0_DBTL_POS                             (11U)           /*!< Destination Burst Transaction Length */
#define DMAC_CTRL0_DBTL_MASK                            (0x7UL << DMAC_CTRL0_DBTL_POS)
#define DMAC_CTRL0_DBTL                                 DMAC_CTRL0_DBTL_MASK
#define DMAC_CTRL0_SBTL_POS                             (14U)           /*!< Source Burst Transaction Length */
#define DMAC_CTRL0_SBTL_MASK                            (0x7UL << DMAC_CTRL0_SBTL_POS)
#define DMAC_CTRL0_SBTL                                 DMAC_CTRL0_SBTL_MASK
#define DMAC_CTRL0_SGE_POS                              (17U)           /*!< Source gather enable */
#define DMAC_CTRL0_SGE_MASK                             (0x1UL << DMAC_CTRL0_SGE_POS)
#define DMAC_CTRL0_SGE                                  DMAC_CTRL0_SGE_MASK
#define DMAC_CTRL0_DSE_POS                              (18U)           /*!< Destination scatter enable */
#define DMAC_CTRL0_DSE_MASK                             (0x1UL << DMAC_CTRL0_DSE_POS)
#define DMAC_CTRL0_DSE                                  DMAC_CTRL0_DSE_MASK
#define DMAC_CTRL0_TTFC_POS                             (20U)           /*!< Transfer Type and Flow Control. */
#define DMAC_CTRL0_TTFC_MASK                            (0x3UL << DMAC_CTRL0_TTFC_POS)
#define DMAC_CTRL0_TTFC                                 DMAC_CTRL0_TTFC_MASK
#define DMAC_CTRL0_DMS_POS                              (22U)           /*!< Destination Master Select */
#define DMAC_CTRL0_DMS_MASK                             (0x7UL << DMAC_CTRL0_DMS_POS)
#define DMAC_CTRL0_DMS                                  DMAC_CTRL0_DMS_MASK
#define DMAC_CTRL0_SMS_POS                              (25U)           /*!< Source Master Select */
#define DMAC_CTRL0_SMS_MASK                             (0x7UL << DMAC_CTRL0_SMS_POS)
#define DMAC_CTRL0_SMS                                  DMAC_CTRL0_SMS_MASK

/*****************  Bit definition for DMAC_CTRL1 register  *******************/
#define DMAC_CTRL1_BTS_POS                              (0U)           /*!< Block Transfer Size */
#define DMAC_CTRL1_BTS_MASK                             (0xFFFUL << DMAC_CTRL1_BTS_POS)
#define DMAC_CTRL1_BTS                                  DMAC_CTRL1_BTS_MASK
#define DMAC_CTRL1_DONE_POS                             (12U)
#define DMAC_CTRL1_DONE_MASK                            (0x1UL << DMAC_CTRL1_DONE_POS)
#define DMAC_CTRL1_DONE                                 DMAC_CTRL1_DONE_MASK

/*****************  Bit definition for DMAC_CFG0 register  ********************/
#define DMAC_CFG0_CP_POS                                (5U)           /*!< Channel priority */
#define DMAC_CFG0_CP_MASK                               (0x7UL << DMAC_CFG0_CP_POS)
#define DMAC_CFG0_CP                                    DMAC_CFG0_CP_MASK
#define DMAC_CFG0_CS_POS                                (8U)           /*!< Channel Suspend */
#define DMAC_CFG0_CS_MASK                               (0x1UL << DMAC_CFG0_CS_POS)
#define DMAC_CFG0_CS                                    DMAC_CFG0_CS_MASK
#define DMAC_CFG0_FE_POS                                (9U)           /*!< Fifo Empty */
#define DMAC_CFG0_FE_MASK                               (0x1UL << DMAC_CFG0_FE_POS)
#define DMAC_CFG0_FE                                    DMAC_CFG0_FE_MASK
#define DMAC_CFG0_DSHHS_POS                             (10U)          /*!< Destination Software or Hardware Handshaking Select */
#define DMAC_CFG0_DSHHS_MASK                            (0x1UL << DMAC_CFG0_DSHHS_POS)
#define DMAC_CFG0_DSHHS                                 DMAC_CFG0_DSHHS_MASK
#define DMAC_CFG0_SSHHS_POS                             (11U)          /*!< Source Software or Hardware Handshaking Selectl */
#define DMAC_CFG0_SSHHS_MASK                            (0x1UL << DMAC_CFG0_SSHHS_POS)
#define DMAC_CFG0_SSHHS                                 DMAC_CFG0_SSHHS_MASK
#define DMAC_CFG0_CLL_POS                               (12U)          /*!< Channel Lock Level */
#define DMAC_CFG0_CLL_MASK                              (0x3UL << DMAC_CFG0_CLL_POS)
#define DMAC_CFG0_CLL                                   DMAC_CFG0_CLL_MASK
#define DMAC_CFG0_BLL_POS                               (14U)          /*!< Bus Lock Level */
#define DMAC_CFG0_BLL_MASK                              (0x3UL << DMAC_CFG0_BLL_POS)
#define DMAC_CFG0_BLL                                   DMAC_CFG0_BLL_MASK
#define DMAC_CFG0_CLB_POS                               (16U)          /*!< Channel Lock Bit */
#define DMAC_CFG0_CLB_MASK                              (0x1UL << DMAC_CFG0_CLB_POS)
#define DMAC_CFG0_CLB                                   DMAC_CFG0_CLB_MASK
#define DMAC_CFG0_BLB_POS                               (17U)          /*!< Bus Lock Bit */
#define DMAC_CFG0_BLB_MASK                              (0x1UL << DMAC_CFG0_BLB_POS)
#define DMAC_CFG0_BLB                                   DMAC_CFG0_BLB_MASK
#define DMAC_CFG0_DHIP_POS                              (18U)          /*!< Destination Handshaking Interface Polarity. */
#define DMAC_CFG0_DHIP_MASK                             (0x1UL << DMAC_CFG0_DHIP_POS)
#define DMAC_CFG0_DHIP                                  DMAC_CFG0_DHIP_MASK
#define DMAC_CFG0_SHIP_POS                              (19U)          /*!< Source Handshaking Interface Polarity. */
#define DMAC_CFG0_SHIP_MASK                             (0x1UL << DMAC_CFG0_SHIP_POS)
#define DMAC_CFG0_SHIP                                  DMAC_CFG0_SHIP_MASK
#define DMAC_CFG0_AMBA_MBL_POS                          (20U)          /*!< AMBA Maximum Burst Length */
#define DMAC_CFG0_AMBA_MBL_MASK                         (0x3FFUL << DMAC_CFG0_AMBA_MBL_POS)
#define DMAC_CFG0_AMBA_MBL                              DMAC_CFG0_AMBA_MBL_MASK
#define DMAC_CFG0_ASR_POS                               (30U)          /*!< Automatic Source Reload */
#define DMAC_CFG0_ASR_MASK                              (0x1UL << DMAC_CFG0_ASR_POS)
#define DMAC_CFG0_ASR                                   DMAC_CFG0_ASR_MASK
#define DMAC_CFG0_ADR_POS                               (31U)          /*!< Automatic Destination Reload */
#define DMAC_CFG0_ADR_MASK                              (0x1UL << DMAC_CFG0_ADR_POS)
#define DMAC_CFG0_ADR                                   DMAC_CFG0_ADR_MASK

/*****************  Bit definition for DMAC_CFG1 register  ********************/
#define DMAC_CFG1_FCM_POS                               (0U)           /*!< Flow Control Mode */
#define DMAC_CFG1_FCM_MASK                              (0x1UL << DMAC_CFG1_FCM_POS)
#define DMAC_CFG1_FCM                                   DMAC_CFG1_FCM_MASK
#define DMAC_CFG1_FMS_POS                               (1U)           /*!< FIFO Mode Select */
#define DMAC_CFG1_FMS_MASK                              (0x1UL << DMAC_CFG1_FMS_POS)
#define DMAC_CFG1_FMS                                   DMAC_CFG1_FMS_MASK
#define DMAC_CFG1_PC_POS                                (2U)           /*!< Protection Control */
#define DMAC_CFG1_PC_MASK                               (0x7UL << DMAC_CFG1_PC_POS)
#define DMAC_CFG1_PC                                    DMAC_CFG1_PC_MASK
#define DMAC_CFG1_DSUE_POS                              (5U)           /*!< Destination Status Update Enable */
#define DMAC_CFG1_DSUE_MASK                             (0x1UL << DMAC_CFG1_DSUE_POS)
#define DMAC_CFG1_DSUE                                  DMAC_CFG1_DSUE_MASK
#define DMAC_CFG1_SSUE_POS                              (6U)           /*!< Source Status Update Enable */
#define DMAC_CFG1_SSUE_MASK                             (0x1UL << DMAC_CFG1_SSUE_POS)
#define DMAC_CFG1_SSUE                                  DMAC_CFG1_SSUE_MASK
#define DMAC_CFG1_SRC_PER_POS                           (7U)
#define DMAC_CFG1_SRC_PER_MASK                          (0xFUL << DMAC_CFG1_SRC_PER_POS)
#define DMAC_CFG1_SRC_PER                               DMAC_CFG1_SRC_PER_MASK
#define DMAC_CFG1_DEST_PER_POS                          (11U)
#define DMAC_CFG1_DEST_PER_MASK                         (0xFUL << DMAC_CFG1_DEST_PER_POS)
#define DMAC_CFG1_DEST_PER                              DMAC_CFG1_DEST_PER_MASK

/*****************  Bit definition for DMAX_RSTCI register  ********************/
#define DMAX_RSTCI_VAL_POS                              (0U)
#define DMAX_RSTCI_VAL_MASK                             (0x3FUL << DMAX_RSTCI_VAL_POS)
#define DMAX_RSTCI_VAL                                  DMAX_RSTCI_VAL_MASK

/*****************  Bit definition for DMAX_RSBTCI register  ********************/
#define DMAX_RSBTCI_VAL_POS                             (0U)
#define DMAX_RSBTCI_VAL_MASK                            (0x3FUL << DMAX_RSBTCI_VAL_POS)
#define DMAX_RSBTCI_VAL                                 DMAX_RSBTCI_VAL_MASK

/*****************  Bit definition for DMAX_RSSTCI register  ********************/
#define DMAX_RSSTCI_VAL_POS                             (0U)
#define DMAX_RSSTCI_VAL_MASK                            (0x3FUL << DMAX_RSSTCI_VAL_POS)
#define DMAX_RSSTCI_VAL                                 DMAX_RSSTCI_VAL_MASK

/*****************  Bit definition for DMAX_RSDCI register  ********************/
#define DMAX_RSDCI_VAL_POS                              (0U)
#define DMAX_RSDCI_VAL_MASK                             (0x3FUL << DMAX_RSDCI_VAL_POS)
#define DMAX_RSDCI_VAL                                  DMAX_RSDCI_VAL_MASK

/*****************  Bit definition for DMAX_RSEI register  ********************/
#define DMAX_RSEI_VAL_POS                               (0U)
#define DMAX_RSEI_VAL_MASK                              (0x3FUL << DMAX_RSEI_VAL_POS)
#define DMAX_RSEI_VAL                                   DMAX_RSEI_VAL_MASK

/*****************  Bit definition for DMAX_STCI register  ********************/
#define DMAX_STCI_VAL_POS                               (0U)
#define DMAX_STCI_VAL_MASK                              (0x3FUL << DMAX_STCI_VAL_POS)
#define DMAX_STCI_VAL                                   DMAX_STCI_VAL_MASK

/*****************  Bit definition for DMAX_SBTCI register  ********************/
#define DMAX_SBTCI_VAL_POS                              (0U)
#define DMAX_SBTCI_VAL_MASK                             (0x3FUL << DMAX_SBTCI_VAL_POS)
#define DMAX_SBTCI_VAL                                  DMAX_SBTCI_VAL_MASK

/*****************  Bit definition for DMAX_SSTCI register  ********************/
#define DMAX_SSTCI_VAL_POS                              (0U)
#define DMAX_SSTCI_VAL_MASK                             (0x3FUL << DMAX_SSTCI_VAL_POS)
#define DMAX_SSTCI_VAL                                  DMAX_SSTCI_VAL_MASK

/*****************  Bit definition for DMAX_SDCI register  ********************/
#define DMAX_SDCI_VAL_POS                               (0U)
#define DMAX_SDCI_VAL_MASK                              (0x3FUL << DMAX_SDCI_VAL_POS)
#define DMAX_SDCI_VAL                                   DMAX_SDCI_VAL_MASK

/*****************  Bit definition for DMAX_SEI register  ********************/
#define DMAX_SEI_VAL_POS                                (0U)
#define DMAX_SEI_VAL_MASK                               (0x3FUL << DMAX_SEI_VAL_POS)
#define DMAX_SEI_VAL                                    DMAX_SEI_VAL_MASK

/*****************  Bit definition for DMAX_MTCI register  ********************/
#define DMAX_MTCI_IM_POS                                (0U)
#define DMAX_MTCI_IM_MASK                               (0x3FUL << DMAX_MTCI_IM_POS)
#define DMAX_MTCI_IM                                    DMAX_MTCI_IM_MASK
#define DMAX_MTCI_IMWE_POS                              (8U)
#define DMAX_MTCI_IMWE_MASK                             (0x3FUL << DMAX_MTCI_IMWE_POS)
#define DMAX_MTCI_IMWE                                  DMAX_MTCI_IMWE_MASK

/*****************  Bit definition for DMAX_MBTCI register  ********************/
#define DMAX_MBTCI_IM_POS                               (0U)
#define DMAX_MBTCI_IM_MASK                              (0x3FUL << DMAX_MBTCI_IM_POS)
#define DMAX_MBTCI_IM                                   DMAX_MBTCI_IM_MASK
#define DMAX_MBTCI_IMWE_POS                             (8U)
#define DMAX_MBTCI_IMWE_MASK                            (0x3FUL << DMAX_MBTCI_IMWE_POS)
#define DMAX_MBTCI_IMWE                                 DMAX_MBTCI_IMWE_MASK

/*****************  Bit definition for DMAX_MSTCI register  ********************/
#define DMAX_MSTCI_IM_POS                               (0U)
#define DMAX_MSTCI_IM_MASK                              (0x3FUL << DMAX_MSTCI_IM_POS)
#define DMAX_MSTCI_IM                                   DMAX_MSTCI_IM_MASK
#define DMAX_MSTCI_IMWE_POS                             (8U)
#define DMAX_MSTCI_IMWE_MASK                            (0x3FUL << DMAX_MSTCI_IMWE_POS)
#define DMAX_MSTCI_IMWE                                 DMAX_MSTCI_IMWE_MASK

/*****************  Bit definition for DMAX_MDCI register  ********************/
#define DMAX_MDCI_IM_POS                                (0U)
#define DMAX_MDCI_IM_MASK                               (0x3FUL << DMAX_MDCI_IM_POS)
#define DMAX_MDCI_IM                                    DMAX_MDCI_IM_MASK
#define DMAX_MDCI_IMWE_POS                              (8U)
#define DMAX_MDCI_IMWE_MASK                             (0x3FUL << DMAX_MDCI_IMWE_POS)
#define DMAX_MDCI_IMWE                                  DMAX_MDCI_IMWE_MASK

/*****************  Bit definition for DMAX_MEI register  ********************/
#define DMAX_MEI_IM_POS                                 (0U)
#define DMAX_MEI_IM_MASK                                (0x3FUL << DMAX_MEI_IM_POS)
#define DMAX_MEI_IM                                     DMAX_MEI_IM_MASK
#define DMAX_MEI_IMWE_POS                               (8U)
#define DMAX_MEI_IMWE_MASK                              (0x3FUL << DMAX_MEI_IMWE_POS)
#define DMAX_MEI_IMWE                                   DMAX_MEI_IMWE_MASK



/*****************  Bit definition for DMAX_CTCI register  ********************/
#define DMAX_CTCI_VAL_POS                               (0U)
#define DMAX_CTCI_VAL_MASK                              (0x3FUL << DMAX_CTCI_VAL_POS)
#define DMAX_CTCI_VAL                                   DMAX_CTCI_VAL_MASK

/*****************  Bit definition for DMAX_CBTCI register  ********************/
#define DMAX_CBTCI_VAL_POS                              (0U)
#define DMAX_CBTCI_VAL_MASK                             (0x3FUL << DMAX_CBTCI_VAL_POS)
#define DMAX_CBTCI_VAL                                  DMAX_CBTCI_VAL_MASK

/*****************  Bit definition for DMAX_CSTCI register  ********************/
#define DMAX_CSTCI_VAL_POS                              (0U)
#define DMAX_CSTCI_VAL_MASK                             (0x3FUL << DMAX_CSTCI_VAL_POS)
#define DMAX_CSTCI_VAL                                  DMAX_CSTCI_VAL_MASK

/*****************  Bit definition for DMAX_CDCI register  ********************/
#define DMAX_CDCI_VAL_POS                               (0U)
#define DMAX_CDCI_VAL_MASK                              (0x3FUL << DMAX_CDCI_VAL_POS)
#define DMAX_CDCI_VAL                                   DMAX_CDCI_VAL_MASK

/*****************  Bit definition for DMAX_CEI register  ********************/
#define DMAX_CEI_VAL_POS                                (0U)
#define DMAX_CEI_VAL_MASK                               (0x3FUL << DMAX_CEI_VAL_POS)
#define DMAX_CEI_VAL                                    DMAX_CEI_VAL_MASK

/*****************  Bit definition for DMAX_CIS register  ********************/
#define DMAX_CIS_TFR_POS                                (0U)
#define DMAX_CIS_TFR_MASK                               (0x1UL << DMAX_CIS_TFR_POS)
#define DMAX_CIS_TFR                                    DMAX_CIS_TFR_MASK
#define DMAX_CIS_BLOCK_POS                              (1U)
#define DMAX_CIS_BLOCK_MASK                             (0x1UL << DMAX_CIS_BLOCK_POS)
#define DMAX_CIS_BLOCK                                  DMAX_CIS_BLOCK_MASK
#define DMAX_CIS_SRCT_POS                               (2U)
#define DMAX_CIS_SRCT_MASK                              (0x1UL << DMAX_CIS_SRCT_POS)
#define DMAX_CIS_SRCT                                   DMAX_CIS_SRCT_MASK
#define DMAX_CIS_DSTT_POS                               (3U)
#define DMAX_CIS_DSTT_MASK                              (0x1UL << DMAX_CIS_DSTT_POS)
#define DMAX_CIS_DSTT                                   DMAX_CIS_DSTT_MASK
#define DMAX_CIS_ERR_POS                                (4U)
#define DMAX_CIS_ERR_MASK                               (0x1UL << DMAX_CIS_ERR_POS)
#define DMAX_CIS_ERR                                    DMAX_CIS_ERR_MASK

/*****************  Bit definition for DMAX_SRCSTR register  ********************/
#define DMAX_SRCSTR_REQ_POS                             (0U)            /*!< request */
#define DMAX_SRCSTR_REQ_MASK                            (0x3FUL << DMAX_SRCSTR_REQ_POS)
#define DMAX_SRCSTR_REQ                                 DMAX_SRCSTR_REQ_MASK
#define DMAX_SRCSTR_RWE_POS                             (8U)            /*!< request write enable */
#define DMAX_SRCSTR_RWE_MASK                            (0x3FUL << DMAX_SRCSTR_RWE_POS)
#define DMAX_SRCSTR_RWE                                 DMAX_SRCSTR_RWE_MASK

/*****************  Bit definition for DMAX_DSTR register  ********************/
#define DMAX_DSTR_REQ_POS                               (0U)            /*!< request */
#define DMAX_DSTR_REQ_MASK                              (0x3FUL << DMAX_DSTR_REQ_POS)
#define DMAX_DSTR_REQ                                   DMAX_DSTR_REQ_MASK
#define DMAX_DSTR_RWE_POS                               (8U)            /*!< request write enable */
#define DMAX_DSTR_RWE_MASK                              (0x3FUL << DMAX_DSTR_RWE_POS)
#define DMAX_DSTR_RWE                                   DMAX_DSTR_RWE_MASK

/*****************  Bit definition for DMAX_SGLSTR register  ********************/
#define DMAX_SGLSTR_REQ_POS                             (0U)            /*!< request */
#define DMAX_SGLSTR_REQ_MASK                            (0x3FUL << DMAX_SGLSTR_REQ_POS)
#define DMAX_SGLSTR_REQ                                 DMAX_SGLSTR_REQ_MASK
#define DMAX_SGLSTR_RWE_POS                             (8U)            /*!< request write enable */
#define DMAX_SGLSTR_RWE_MASK                            (0x3FUL << DMAX_SGLSTR_RWE_POS)
#define DMAX_SGLSTR_RWE                                 DMAX_SGLSTR_RWE_MASK

/*****************  Bit definition for DMAX_SDTR register  ********************/
#define DMAX_SDTR_REQ_POS                               (0U)            /*!< request */
#define DMAX_SDTR_REQ_MASK                              (0x3FUL << DMAX_SDTR_REQ_POS)
#define DMAX_SDTR_REQ                                   DMAX_SDTR_REQ_MASK
#define DMAX_SDTR_RWE_POS                               (8U)            /*!< request write enable */
#define DMAX_SDTR_RWE_MASK                              (0x3FUL << DMAX_SDTR_RWE_POS)
#define DMAX_SDTR_RWE                                   DMAX_SDTR_RWE_MASK

/*****************  Bit definition for DMAX_LSTR register  ********************/
#define DMAX_LSTR_REQ_POS                               (0U)            /*!< request */
#define DMAX_LSTR_REQ_MASK                              (0x3FUL << DMAX_LSTR_REQ_POS)
#define DMAX_LSTR_REQ                                   DMAX_LSTR_REQ_MASK
#define DMAX_LSTR_RWE_POS                               (8U)            /*!< request write enable */
#define DMAX_LSTR_RWE_MASK                              (0x3FUL << DMAX_LSTR_RWE_POS)
#define DMAX_LSTR_RWE                                   DMAX_LSTR_RWE_MASK

/*****************  Bit definition for DMAX_LDTR register  ********************/
#define DMAX_LDTR_REQ_POS                               (0U)            /*!< request */
#define DMAX_LDTR_REQ_MASK                              (0x3FUL << DMAX_LDTR_REQ_POS)
#define DMAX_LDTR_REQ                                   DMAX_LDTR_REQ_MASK
#define DMAX_LDTR_RWE_POS                               (8U)            /*!< request write enable */
#define DMAX_LDTR_RWE_MASK                              (0x3FUL << DMAX_LDTR_RWE_POS)
#define DMAX_LDTR_RWE                                   DMAX_LDTR_RWE_MASK

/*****************  Bit definition for DMAX_EN register  ********************/
#define DMAX_EN_BIT_POS                                 (0U)
#define DMAX_EN_BIT_MASK                                (0x1UL << DMAX_EN_BIT_POS)
#define DMAX_EN_BIT                                     DMAX_EN_BIT_MASK

/*****************  Bit definition for DMAX_CE register  ********************/
#define DMAX_CE_VAL_POS                                 (0U)
#define DMAX_CE_VAL_MASK                                (0x3FUL << DMAX_CE_VAL_POS)
#define DMAX_CE_VAL                                     DMAX_CE_VAL_MASK
#define DMAX_CE_WE_POS                                  (8U)            /* !< write enable */
#define DMAX_CE_WE_MASK                                 (0x3FUL << DMAX_CE_WE_POS)
#define DMAX_CE_WE                                      DMAX_CE_WE_MASK

/*****************  Bit definition for DMAX_ID register  ********************/
#define DMAX_ID_VAL_POS                                 (0U)
#define DMAX_ID_VAL_MASK                                (0xFFFFFFFFUL << DMAX_ID_VAL_POS)
#define DMAX_ID_VAL                                     DMAX_ID_VAL_MASK

/*****************  Bit definition for DMAX_TEST register  ********************/
#define DMAX_TEST_VAL_POS                               (0U)
#define DMAX_TEST_VAL_MASK                              (0xFFFFFFFFUL << DMAX_TEST_VAL_POS)
#define DMAX_TEST_VAL                                   DMAX_TEST_VAL_MASK

/*****************  Bit definition for DMAX_CP5 register  ********************/
#define DMAX_CP5_DTW_POS                                (0U)
#define DMAX_CP5_DTW_MASK                               (0x7UL << DMAX_CP5_DTW_POS)
#define DMAX_CP5_DTW                                    DMAX_CP5_DTW_MASK
#define DMAX_CP5_DTW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP5_DTW_POS )
#define DMAX_CP5_DTW_T_8                                ( 0x01 << DMAX_CP5_DTW_POS )
#define DMAX_CP5_DTW_T_16                               ( 0x02 << DMAX_CP5_DTW_POS )
#define DMAX_CP5_DTW_T_32                               ( 0x03 << DMAX_CP5_DTW_POS )
#define DMAX_CP5_DTW_T_64                               ( 0x04 << DMAX_CP5_DTW_POS )
#define DMAX_CP5_DTW_T_128                              ( 0x05 << DMAX_CP5_DTW_POS )
#define DMAX_CP5_DTW_T_256                              ( 0x06 << DMAX_CP5_DTW_POS )

#define DMAX_CP5_STW_POS                                (3U)
#define DMAX_CP5_STW_MASK                               (0x7UL << DMAX_CP5_STW_POS)
#define DMAX_CP5_STW                                    DMAX_CP5_STW_MASK
#define DMAX_CP5_STW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP5_STW_POS )
#define DMAX_CP5_STW_T_8                                ( 0x01 << DMAX_CP5_STW_POS )
#define DMAX_CP5_STW_T_16                               ( 0x02 << DMAX_CP5_STW_POS )
#define DMAX_CP5_STW_T_32                               ( 0x03 << DMAX_CP5_STW_POS )
#define DMAX_CP5_STW_T_64                               ( 0x04 << DMAX_CP5_STW_POS )
#define DMAX_CP5_STW_T_128                              ( 0x05 << DMAX_CP5_STW_POS )
#define DMAX_CP5_STW_T_256                              ( 0x06 << DMAX_CP5_STW_POS )

#define DMAX_CP5_STAT_DST_POS                           (6U)
#define DMAX_CP5_STAT_DST_MASK                          (0x1UL << DMAX_CP5_STAT_DST_POS)
#define DMAX_CP5_STAT_DST                               DMAX_CP5_STAT_DST_MASK
#define DMAX_CP5_STAT_SRC_POS                           (7U)
#define DMAX_CP5_STAT_SRC_MASK                          (0x1UL << DMAX_CP5_STAT_SRC_POS)
#define DMAX_CP5_STAT_SRC                               DMAX_CP5_STAT_SRC_MASK
#define DMAX_CP5_DST_SCA_EN_POS                         (8U)
#define DMAX_CP5_DST_SCA_EN_MASK                        (0x1UL << DMAX_CP5_DST_SCA_EN_POS)
#define DMAX_CP5_DST_SCA_EN                             DMAX_CP5_DST_SCA_EN_MASK
#define DMAX_CP5_SRC_GAT_EN_POS                         (9U)
#define DMAX_CP5_SRC_GAT_EN_MASK                        (0x1UL << DMAX_CP5_SRC_GAT_EN_POS)
#define DMAX_CP5_SRC_GAT_EN                             DMAX_CP5_SRC_GAT_EN_MASK
#define DMAX_CP5_LOCK_EN_POS                            (10U)
#define DMAX_CP5_LOCK_EN_MASK                           (0x1UL << DMAX_CP5_LOCK_EN_POS)
#define DMAX_CP5_LOCK_EN                                DMAX_CP5_LOCK_EN_MASK
#define DMAX_CP5_MULTI_BLK_EN_POS                       (11U)
#define DMAX_CP5_MULTI_BLK_EN_MASK                      (0x1UL << DMAX_CP5_MULTI_BLK_EN_POS)
#define DMAX_CP5_MULTI_BLK_EN                           DMAX_CP5_MULTI_BLK_EN_MASK
#define DMAX_CP5_CTL_WB_EN_POS                          (12U)
#define DMAX_CP5_CTL_WB_EN_MASK                         (0x1UL << DMAX_CP5_CTL_WB_EN_POS)
#define DMAX_CP5_CTL_WB_EN                              DMAX_CP5_CTL_WB_EN_MASK
#define DMAX_CP5_HC_LLP_POS                             (13U)
#define DMAX_CP5_HC_LLP_MASK                            (0x1UL << DMAX_CP5_HC_LLP_POS)
#define DMAX_CP5_HC_LLP                                 DMAX_CP5_HC_LLP_MASK

#define DMAX_CP5_FC_POS                                 (14U)
#define DMAX_CP5_FC_MASK                                (0x3UL << DMAX_CP5_FC_POS)
#define DMAX_CP5_FC                                     DMAX_CP5_FC_MASK
#define DMAX_CP5_FC_T_DMA                               ( 0x00 << DMAX_CP5_FC_POS )
#define DMAX_CP5_FC_T_SRC                               ( 0x01 << DMAX_CP5_FC_POS )
#define DMAX_CP5_FC_T_DST                               ( 0x02 << DMAX_CP5_FC_POS )
#define DMAX_CP5_FC_T_ANY                               ( 0x03 << DMAX_CP5_FC_POS )

#define DMAX_CP5_MAX_MULT_SIZE_POS                      (16U)
#define DMAX_CP5_MAX_MULT_SIZE_MASK                     (0x7UL << DMAX_CP5_MAX_MULT_SIZE_POS)
#define DMAX_CP5_MAX_MULT_SIZE                          DMAX_CP5_MAX_MULT_SIZE_MASK
#define DMAX_CP5_MAX_MULT_SIZE_T_4                      ( 0x00 << DMAX_CP5_MAX_MULT_SIZE_POS )
#define DMAX_CP5_MAX_MULT_SIZE_T_8                      ( 0x01 << DMAX_CP5_MAX_MULT_SIZE_POS )
#define DMAX_CP5_MAX_MULT_SIZE_T_16                     ( 0x02 << DMAX_CP5_MAX_MULT_SIZE_POS )
#define DMAX_CP5_MAX_MULT_SIZE_T_32                     ( 0x03 << DMAX_CP5_MAX_MULT_SIZE_POS )
#define DMAX_CP5_MAX_MULT_SIZE_T_64                     ( 0x04 << DMAX_CP5_MAX_MULT_SIZE_POS )
#define DMAX_CP5_MAX_MULT_SIZE_T_128                    ( 0x05 << DMAX_CP5_MAX_MULT_SIZE_POS )
#define DMAX_CP5_MAX_MULT_SIZE_T_256                    ( 0x06 << DMAX_CP5_MAX_MULT_SIZE_POS )

#define DMAX_CP5_DMS_POS                                (19U)
#define DMAX_CP5_DMS_MASK                               (0x7UL << DMAX_CP5_DMS_POS)
#define DMAX_CP5_DMS                                    DMAX_CP5_DMS_MASK
#define DMAX_CP5_DMS_T_MASTER1                          ( 0x00 << DMAX_CP5_DMS_POS )
#define DMAX_CP5_DMS_T_MASTER2                          ( 0x01 << DMAX_CP5_DMS_POS )
#define DMAX_CP5_DMS_T_MASTER3                          ( 0x02 << DMAX_CP5_DMS_POS )
#define DMAX_CP5_DMS_T_MASTER4                          ( 0x03 << DMAX_CP5_DMS_POS )
#define DMAX_CP5_DMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP5_DMS_POS )

#define DMAX_CP5_LMS_POS                                (22U)
#define DMAX_CP5_LMS_MASK                               (0x7UL << DMAX_CP5_LMS_POS)
#define DMAX_CP5_LMS                                    DMAX_CP5_LMS_MASK
#define DMAX_CP5_LMS_T_MASTER1                          ( 0x00 << DMAX_CP5_LMS_POS )
#define DMAX_CP5_LMS_T_MASTER2                          ( 0x01 << DMAX_CP5_LMS_POS )
#define DMAX_CP5_LMS_T_MASTER3                          ( 0x02 << DMAX_CP5_LMS_POS )
#define DMAX_CP5_LMS_T_MASTER4                          ( 0x03 << DMAX_CP5_LMS_POS )
#define DMAX_CP5_LMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP5_LMS_POS )

#define DMAX_CP5_SMS_POS                                (22U)
#define DMAX_CP5_SMS_MASK                               (0x7UL << DMAX_CP5_SMS_POS)
#define DMAX_CP5_SMS                                    DMAX_CP5_SMS_MASK
#define DMAX_CP5_SMS_T_MASTER1                          ( 0x00 << DMAX_CP5_SMS_POS )
#define DMAX_CP5_SMS_T_MASTER2                          ( 0x01 << DMAX_CP5_SMS_POS )
#define DMAX_CP5_SMS_T_MASTER3                          ( 0x02 << DMAX_CP5_SMS_POS )
#define DMAX_CP5_SMS_T_MASTER4                          ( 0x03 << DMAX_CP5_SMS_POS )
#define DMAX_CP5_SMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP5_SMS_POS )

#define DMAX_CP5_FIFO_DEPTH_POS                         (28U)
#define DMAX_CP5_FIFO_DEPTH_MASK                        (0x7UL << DMAX_CP5_FIFO_DEPTH_POS)
#define DMAX_CP5_FIFO_DEPTH                             DMAX_CP5_FIFO_DEPTH_MASK
#define DMAX_CP5_FIFO_DEPTH_T_8                         ( 0x00 << DMAX_CP5_FIFO_DEPTH_POS )
#define DMAX_CP5_FIFO_DEPTH_T_16                        ( 0x01 << DMAX_CP5_FIFO_DEPTH_POS )
#define DMAX_CP5_FIFO_DEPTH_T_32                        ( 0x02 << DMAX_CP5_FIFO_DEPTH_POS )
#define DMAX_CP5_FIFO_DEPTH_T_64                        ( 0x03 << DMAX_CP5_FIFO_DEPTH_POS )
#define DMAX_CP5_FIFO_DEPTH_T_128                       ( 0x04 << DMAX_CP5_FIFO_DEPTH_POS )

/*****************  Bit definition for DMAX_CP4 register  ********************/
#define DMAX_CP4_DTW_POS                                (0U)
#define DMAX_CP4_DTW_MASK                               (0x7UL << DMAX_CP4_DTW_POS)
#define DMAX_CP4_DTW                                    DMAX_CP4_DTW_MASK
#define DMAX_CP4_DTW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP4_DTW_POS )
#define DMAX_CP4_DTW_T_8                                ( 0x01 << DMAX_CP4_DTW_POS )
#define DMAX_CP4_DTW_T_16                               ( 0x02 << DMAX_CP4_DTW_POS )
#define DMAX_CP4_DTW_T_32                               ( 0x03 << DMAX_CP4_DTW_POS )
#define DMAX_CP4_DTW_T_64                               ( 0x04 << DMAX_CP4_DTW_POS )
#define DMAX_CP4_DTW_T_128                              ( 0x05 << DMAX_CP4_DTW_POS )
#define DMAX_CP4_DTW_T_256                              ( 0x06 << DMAX_CP4_DTW_POS )

#define DMAX_CP4_STW_POS                                (3U)
#define DMAX_CP4_STW_MASK                               (0x7UL << DMAX_CP4_STW_POS)
#define DMAX_CP4_STW                                    DMAX_CP4_STW_MASK
#define DMAX_CP4_STW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP4_STW_POS )
#define DMAX_CP4_STW_T_8                                ( 0x01 << DMAX_CP4_STW_POS )
#define DMAX_CP4_STW_T_16                               ( 0x02 << DMAX_CP4_STW_POS )
#define DMAX_CP4_STW_T_32                               ( 0x03 << DMAX_CP4_STW_POS )
#define DMAX_CP4_STW_T_64                               ( 0x04 << DMAX_CP4_STW_POS )
#define DMAX_CP4_STW_T_128                              ( 0x05 << DMAX_CP4_STW_POS )
#define DMAX_CP4_STW_T_256                              ( 0x06 << DMAX_CP4_STW_POS )

#define DMAX_CP4_STAT_DST_POS                           (6U)
#define DMAX_CP4_STAT_DST_MASK                          (0x1UL << DMAX_CP4_STAT_DST_POS)
#define DMAX_CP4_STAT_DST                               DMAX_CP4_STAT_DST_MASK
#define DMAX_CP4_STAT_SRC_POS                           (7U)
#define DMAX_CP4_STAT_SRC_MASK                          (0x1UL << DMAX_CP4_STAT_SRC_POS)
#define DMAX_CP4_STAT_SRC                               DMAX_CP4_STAT_SRC_MASK
#define DMAX_CP4_DST_SCA_EN_POS                         (8U)
#define DMAX_CP4_DST_SCA_EN_MASK                        (0x1UL << DMAX_CP4_DST_SCA_EN_POS)
#define DMAX_CP4_DST_SCA_EN                             DMAX_CP4_DST_SCA_EN_MASK
#define DMAX_CP4_SRC_GAT_EN_POS                         (9U)
#define DMAX_CP4_SRC_GAT_EN_MASK                        (0x1UL << DMAX_CP4_SRC_GAT_EN_POS)
#define DMAX_CP4_SRC_GAT_EN                             DMAX_CP4_SRC_GAT_EN_MASK
#define DMAX_CP4_LOCK_EN_POS                            (10U)
#define DMAX_CP4_LOCK_EN_MASK                           (0x1UL << DMAX_CP4_LOCK_EN_POS)
#define DMAX_CP4_LOCK_EN                                DMAX_CP4_LOCK_EN_MASK
#define DMAX_CP4_MULTI_BLK_EN_POS                       (11U)
#define DMAX_CP4_MULTI_BLK_EN_MASK                      (0x1UL << DMAX_CP4_MULTI_BLK_EN_POS)
#define DMAX_CP4_MULTI_BLK_EN                           DMAX_CP4_MULTI_BLK_EN_MASK
#define DMAX_CP4_CTL_WB_EN_POS                          (12U)
#define DMAX_CP4_CTL_WB_EN_MASK                         (0x1UL << DMAX_CP4_CTL_WB_EN_POS)
#define DMAX_CP4_CTL_WB_EN                              DMAX_CP4_CTL_WB_EN_MASK
#define DMAX_CP4_HC_LLP_POS                             (13U)
#define DMAX_CP4_HC_LLP_MASK                            (0x1UL << DMAX_CP4_HC_LLP_POS)
#define DMAX_CP4_HC_LLP                                 DMAX_CP4_HC_LLP_MASK

#define DMAX_CP4_FC_POS                                 (14U)
#define DMAX_CP4_FC_MASK                                (0x3UL << DMAX_CP4_FC_POS)
#define DMAX_CP4_FC                                     DMAX_CP4_FC_MASK
#define DMAX_CP4_FC_T_DMA                               ( 0x00 << DMAX_CP4_FC_POS )
#define DMAX_CP4_FC_T_SRC                               ( 0x01 << DMAX_CP4_FC_POS )
#define DMAX_CP4_FC_T_DST                               ( 0x02 << DMAX_CP4_FC_POS )
#define DMAX_CP4_FC_T_ANY                               ( 0x03 << DMAX_CP4_FC_POS )

#define DMAX_CP4_MAX_MULT_SIZE_POS                      (16U)
#define DMAX_CP4_MAX_MULT_SIZE_MASK                     (0x7UL << DMAX_CP4_MAX_MULT_SIZE_POS)
#define DMAX_CP4_MAX_MULT_SIZE                          DMAX_CP4_MAX_MULT_SIZE_MASK
#define DMAX_CP4_MAX_MULT_SIZE_T_4                      ( 0x00 << DMAX_CP4_MAX_MULT_SIZE_POS )
#define DMAX_CP4_MAX_MULT_SIZE_T_8                      ( 0x01 << DMAX_CP4_MAX_MULT_SIZE_POS )
#define DMAX_CP4_MAX_MULT_SIZE_T_16                     ( 0x02 << DMAX_CP4_MAX_MULT_SIZE_POS )
#define DMAX_CP4_MAX_MULT_SIZE_T_32                     ( 0x03 << DMAX_CP4_MAX_MULT_SIZE_POS )
#define DMAX_CP4_MAX_MULT_SIZE_T_64                     ( 0x04 << DMAX_CP4_MAX_MULT_SIZE_POS )
#define DMAX_CP4_MAX_MULT_SIZE_T_128                    ( 0x05 << DMAX_CP4_MAX_MULT_SIZE_POS )
#define DMAX_CP4_MAX_MULT_SIZE_T_256                    ( 0x06 << DMAX_CP4_MAX_MULT_SIZE_POS )

#define DMAX_CP4_DMS_POS                                (19U)
#define DMAX_CP4_DMS_MASK                               (0x7UL << DMAX_CP4_DMS_POS)
#define DMAX_CP4_DMS                                    DMAX_CP4_DMS_MASK
#define DMAX_CP4_DMS_T_MASTER1                          ( 0x00 << DMAX_CP4_DMS_POS )
#define DMAX_CP4_DMS_T_MASTER2                          ( 0x01 << DMAX_CP4_DMS_POS )
#define DMAX_CP4_DMS_T_MASTER3                          ( 0x02 << DMAX_CP4_DMS_POS )
#define DMAX_CP4_DMS_T_MASTER4                          ( 0x03 << DMAX_CP4_DMS_POS )
#define DMAX_CP4_DMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP4_DMS_POS )

#define DMAX_CP4_LMS_POS                                (22U)
#define DMAX_CP4_LMS_MASK                               (0x7UL << DMAX_CP4_LMS_POS)
#define DMAX_CP4_LMS                                    DMAX_CP4_LMS_MASK
#define DMAX_CP4_LMS_T_MASTER1                          ( 0x00 << DMAX_CP4_LMS_POS )
#define DMAX_CP4_LMS_T_MASTER2                          ( 0x01 << DMAX_CP4_LMS_POS )
#define DMAX_CP4_LMS_T_MASTER3                          ( 0x02 << DMAX_CP4_LMS_POS )
#define DMAX_CP4_LMS_T_MASTER4                          ( 0x03 << DMAX_CP4_LMS_POS )
#define DMAX_CP4_LMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP4_LMS_POS )

#define DMAX_CP4_SMS_POS                                (22U)
#define DMAX_CP4_SMS_MASK                               (0x7UL << DMAX_CP4_SMS_POS)
#define DMAX_CP4_SMS                                    DMAX_CP4_SMS_MASK
#define DMAX_CP4_SMS_T_MASTER1                          ( 0x00 << DMAX_CP4_SMS_POS )
#define DMAX_CP4_SMS_T_MASTER2                          ( 0x01 << DMAX_CP4_SMS_POS )
#define DMAX_CP4_SMS_T_MASTER3                          ( 0x02 << DMAX_CP4_SMS_POS )
#define DMAX_CP4_SMS_T_MASTER4                          ( 0x03 << DMAX_CP4_SMS_POS )
#define DMAX_CP4_SMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP4_SMS_POS )

#define DMAX_CP4_FIFO_DEPTH_POS                         (28U)
#define DMAX_CP4_FIFO_DEPTH_MASK                        (0x7UL << DMAX_CP4_FIFO_DEPTH_POS)
#define DMAX_CP4_FIFO_DEPTH                             DMAX_CP4_FIFO_DEPTH_MASK
#define DMAX_CP4_FIFO_DEPTH_T_8                         ( 0x00 << DMAX_CP4_FIFO_DEPTH_POS )
#define DMAX_CP4_FIFO_DEPTH_T_16                        ( 0x01 << DMAX_CP4_FIFO_DEPTH_POS )
#define DMAX_CP4_FIFO_DEPTH_T_32                        ( 0x02 << DMAX_CP4_FIFO_DEPTH_POS )
#define DMAX_CP4_FIFO_DEPTH_T_64                        ( 0x03 << DMAX_CP4_FIFO_DEPTH_POS )
#define DMAX_CP4_FIFO_DEPTH_T_128                       ( 0x04 << DMAX_CP4_FIFO_DEPTH_POS )

/*****************  Bit definition for DMAX_CP3 register  ********************/
#define DMAX_CP3_DTW_POS                                (0U)
#define DMAX_CP3_DTW_MASK                               (0x7UL << DMAX_CP3_DTW_POS)
#define DMAX_CP3_DTW                                    DMAX_CP3_DTW_MASK
#define DMAX_CP3_DTW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP3_DTW_POS )
#define DMAX_CP3_DTW_T_8                                ( 0x01 << DMAX_CP3_DTW_POS )
#define DMAX_CP3_DTW_T_16                               ( 0x02 << DMAX_CP3_DTW_POS )
#define DMAX_CP3_DTW_T_32                               ( 0x03 << DMAX_CP3_DTW_POS )
#define DMAX_CP3_DTW_T_64                               ( 0x04 << DMAX_CP3_DTW_POS )
#define DMAX_CP3_DTW_T_128                              ( 0x05 << DMAX_CP3_DTW_POS )
#define DMAX_CP3_DTW_T_256                              ( 0x06 << DMAX_CP3_DTW_POS )

#define DMAX_CP3_STW_POS                                (3U)
#define DMAX_CP3_STW_MASK                               (0x7UL << DMAX_CP3_STW_POS)
#define DMAX_CP3_STW                                    DMAX_CP3_STW_MASK
#define DMAX_CP3_STW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP3_STW_POS )
#define DMAX_CP3_STW_T_8                                ( 0x01 << DMAX_CP3_STW_POS )
#define DMAX_CP3_STW_T_16                               ( 0x02 << DMAX_CP3_STW_POS )
#define DMAX_CP3_STW_T_32                               ( 0x03 << DMAX_CP3_STW_POS )
#define DMAX_CP3_STW_T_64                               ( 0x04 << DMAX_CP3_STW_POS )
#define DMAX_CP3_STW_T_128                              ( 0x05 << DMAX_CP3_STW_POS )
#define DMAX_CP3_STW_T_256                              ( 0x06 << DMAX_CP3_STW_POS )

#define DMAX_CP3_STAT_DST_POS                           (6U)
#define DMAX_CP3_STAT_DST_MASK                          (0x1UL << DMAX_CP3_STAT_DST_POS)
#define DMAX_CP3_STAT_DST                               DMAX_CP3_STAT_DST_MASK
#define DMAX_CP3_STAT_SRC_POS                           (7U)
#define DMAX_CP3_STAT_SRC_MASK                          (0x1UL << DMAX_CP3_STAT_SRC_POS)
#define DMAX_CP3_STAT_SRC                               DMAX_CP3_STAT_SRC_MASK
#define DMAX_CP3_DST_SCA_EN_POS                         (8U)
#define DMAX_CP3_DST_SCA_EN_MASK                        (0x1UL << DMAX_CP3_DST_SCA_EN_POS)
#define DMAX_CP3_DST_SCA_EN                             DMAX_CP3_DST_SCA_EN_MASK
#define DMAX_CP3_SRC_GAT_EN_POS                         (9U)
#define DMAX_CP3_SRC_GAT_EN_MASK                        (0x1UL << DMAX_CP3_SRC_GAT_EN_POS)
#define DMAX_CP3_SRC_GAT_EN                             DMAX_CP3_SRC_GAT_EN_MASK
#define DMAX_CP3_LOCK_EN_POS                            (10U)
#define DMAX_CP3_LOCK_EN_MASK                           (0x1UL << DMAX_CP3_LOCK_EN_POS)
#define DMAX_CP3_LOCK_EN                                DMAX_CP3_LOCK_EN_MASK
#define DMAX_CP3_MULTI_BLK_EN_POS                       (11U)
#define DMAX_CP3_MULTI_BLK_EN_MASK                      (0x1UL << DMAX_CP3_MULTI_BLK_EN_POS)
#define DMAX_CP3_MULTI_BLK_EN                           DMAX_CP3_MULTI_BLK_EN_MASK
#define DMAX_CP3_CTL_WB_EN_POS                          (12U)
#define DMAX_CP3_CTL_WB_EN_MASK                         (0x1UL << DMAX_CP3_CTL_WB_EN_POS)
#define DMAX_CP3_CTL_WB_EN                              DMAX_CP3_CTL_WB_EN_MASK
#define DMAX_CP3_HC_LLP_POS                             (13U)
#define DMAX_CP3_HC_LLP_MASK                            (0x1UL << DMAX_CP3_HC_LLP_POS)
#define DMAX_CP3_HC_LLP                                 DMAX_CP3_HC_LLP_MASK

#define DMAX_CP3_FC_POS                                 (14U)
#define DMAX_CP3_FC_MASK                                (0x3UL << DMAX_CP3_FC_POS)
#define DMAX_CP3_FC                                     DMAX_CP3_FC_MASK
#define DMAX_CP3_FC_T_DMA                               ( 0x00 << DMAX_CP3_FC_POS )
#define DMAX_CP3_FC_T_SRC                               ( 0x01 << DMAX_CP3_FC_POS )
#define DMAX_CP3_FC_T_DST                               ( 0x02 << DMAX_CP3_FC_POS )
#define DMAX_CP3_FC_T_ANY                               ( 0x03 << DMAX_CP3_FC_POS )

#define DMAX_CP3_MAX_MULT_SIZE_POS                      (16U)
#define DMAX_CP3_MAX_MULT_SIZE_MASK                     (0x7UL << DMAX_CP3_MAX_MULT_SIZE_POS)
#define DMAX_CP3_MAX_MULT_SIZE                          DMAX_CP3_MAX_MULT_SIZE_MASK
#define DMAX_CP3_MAX_MULT_SIZE_T_4                      ( 0x00 << DMAX_CP3_MAX_MULT_SIZE_POS )
#define DMAX_CP3_MAX_MULT_SIZE_T_8                      ( 0x01 << DMAX_CP3_MAX_MULT_SIZE_POS )
#define DMAX_CP3_MAX_MULT_SIZE_T_16                     ( 0x02 << DMAX_CP3_MAX_MULT_SIZE_POS )
#define DMAX_CP3_MAX_MULT_SIZE_T_32                     ( 0x03 << DMAX_CP3_MAX_MULT_SIZE_POS )
#define DMAX_CP3_MAX_MULT_SIZE_T_64                     ( 0x04 << DMAX_CP3_MAX_MULT_SIZE_POS )
#define DMAX_CP3_MAX_MULT_SIZE_T_128                    ( 0x05 << DMAX_CP3_MAX_MULT_SIZE_POS )
#define DMAX_CP3_MAX_MULT_SIZE_T_256                    ( 0x06 << DMAX_CP3_MAX_MULT_SIZE_POS )

#define DMAX_CP3_DMS_POS                                (19U)
#define DMAX_CP3_DMS_MASK                               (0x7UL << DMAX_CP3_DMS_POS)
#define DMAX_CP3_DMS                                    DMAX_CP3_DMS_MASK
#define DMAX_CP3_DMS_T_MASTER1                          ( 0x00 << DMAX_CP3_DMS_POS )
#define DMAX_CP3_DMS_T_MASTER2                          ( 0x01 << DMAX_CP3_DMS_POS )
#define DMAX_CP3_DMS_T_MASTER3                          ( 0x02 << DMAX_CP3_DMS_POS )
#define DMAX_CP3_DMS_T_MASTER4                          ( 0x03 << DMAX_CP3_DMS_POS )
#define DMAX_CP3_DMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP3_DMS_POS )

#define DMAX_CP3_LMS_POS                                (22U)
#define DMAX_CP3_LMS_MASK                               (0x7UL << DMAX_CP3_LMS_POS)
#define DMAX_CP3_LMS                                    DMAX_CP3_LMS_MASK
#define DMAX_CP3_LMS_T_MASTER1                          ( 0x00 << DMAX_CP3_LMS_POS )
#define DMAX_CP3_LMS_T_MASTER2                          ( 0x01 << DMAX_CP3_LMS_POS )
#define DMAX_CP3_LMS_T_MASTER3                          ( 0x02 << DMAX_CP3_LMS_POS )
#define DMAX_CP3_LMS_T_MASTER4                          ( 0x03 << DMAX_CP3_LMS_POS )
#define DMAX_CP3_LMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP3_LMS_POS )

#define DMAX_CP3_SMS_POS                                (22U)
#define DMAX_CP3_SMS_MASK                               (0x7UL << DMAX_CP3_SMS_POS)
#define DMAX_CP3_SMS                                    DMAX_CP3_SMS_MASK
#define DMAX_CP3_SMS_T_MASTER1                          ( 0x00 << DMAX_CP3_SMS_POS )
#define DMAX_CP3_SMS_T_MASTER2                          ( 0x01 << DMAX_CP3_SMS_POS )
#define DMAX_CP3_SMS_T_MASTER3                          ( 0x02 << DMAX_CP3_SMS_POS )
#define DMAX_CP3_SMS_T_MASTER4                          ( 0x03 << DMAX_CP3_SMS_POS )
#define DMAX_CP3_SMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP3_SMS_POS )

#define DMAX_CP3_FIFO_DEPTH_POS                         (28U)
#define DMAX_CP3_FIFO_DEPTH_MASK                        (0x7UL << DMAX_CP3_FIFO_DEPTH_POS)
#define DMAX_CP3_FIFO_DEPTH                             DMAX_CP3_FIFO_DEPTH_MASK
#define DMAX_CP3_FIFO_DEPTH_T_8                         ( 0x00 << DMAX_CP3_FIFO_DEPTH_POS )
#define DMAX_CP3_FIFO_DEPTH_T_16                        ( 0x01 << DMAX_CP3_FIFO_DEPTH_POS )
#define DMAX_CP3_FIFO_DEPTH_T_32                        ( 0x02 << DMAX_CP3_FIFO_DEPTH_POS )
#define DMAX_CP3_FIFO_DEPTH_T_64                        ( 0x03 << DMAX_CP3_FIFO_DEPTH_POS )
#define DMAX_CP3_FIFO_DEPTH_T_128                       ( 0x04 << DMAX_CP3_FIFO_DEPTH_POS )

/*****************  Bit definition for DMAX_CP2 register  ********************/
#define DMAX_CP2_DTW_POS                                (0U)
#define DMAX_CP2_DTW_MASK                               (0x7UL << DMAX_CP2_DTW_POS)
#define DMAX_CP2_DTW                                    DMAX_CP2_DTW_MASK
#define DMAX_CP2_DTW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP2_DTW_POS )
#define DMAX_CP2_DTW_T_8                                ( 0x01 << DMAX_CP2_DTW_POS )
#define DMAX_CP2_DTW_T_16                               ( 0x02 << DMAX_CP2_DTW_POS )
#define DMAX_CP2_DTW_T_32                               ( 0x03 << DMAX_CP2_DTW_POS )
#define DMAX_CP2_DTW_T_64                               ( 0x04 << DMAX_CP2_DTW_POS )
#define DMAX_CP2_DTW_T_128                              ( 0x05 << DMAX_CP2_DTW_POS )
#define DMAX_CP2_DTW_T_256                              ( 0x06 << DMAX_CP2_DTW_POS )

#define DMAX_CP2_STW_POS                                (3U)
#define DMAX_CP2_STW_MASK                               (0x7UL << DMAX_CP2_STW_POS)
#define DMAX_CP2_STW                                    DMAX_CP2_STW_MASK
#define DMAX_CP2_STW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP2_STW_POS )
#define DMAX_CP2_STW_T_8                                ( 0x01 << DMAX_CP2_STW_POS )
#define DMAX_CP2_STW_T_16                               ( 0x02 << DMAX_CP2_STW_POS )
#define DMAX_CP2_STW_T_32                               ( 0x03 << DMAX_CP2_STW_POS )
#define DMAX_CP2_STW_T_64                               ( 0x04 << DMAX_CP2_STW_POS )
#define DMAX_CP2_STW_T_128                              ( 0x05 << DMAX_CP2_STW_POS )
#define DMAX_CP2_STW_T_256                              ( 0x06 << DMAX_CP2_STW_POS )

#define DMAX_CP2_STAT_DST_POS                           (6U)
#define DMAX_CP2_STAT_DST_MASK                          (0x1UL << DMAX_CP2_STAT_DST_POS)
#define DMAX_CP2_STAT_DST                               DMAX_CP2_STAT_DST_MASK
#define DMAX_CP2_STAT_SRC_POS                           (7U)
#define DMAX_CP2_STAT_SRC_MASK                          (0x1UL << DMAX_CP2_STAT_SRC_POS)
#define DMAX_CP2_STAT_SRC                               DMAX_CP2_STAT_SRC_MASK
#define DMAX_CP2_DST_SCA_EN_POS                         (8U)
#define DMAX_CP2_DST_SCA_EN_MASK                        (0x1UL << DMAX_CP2_DST_SCA_EN_POS)
#define DMAX_CP2_DST_SCA_EN                             DMAX_CP2_DST_SCA_EN_MASK
#define DMAX_CP2_SRC_GAT_EN_POS                         (9U)
#define DMAX_CP2_SRC_GAT_EN_MASK                        (0x1UL << DMAX_CP2_SRC_GAT_EN_POS)
#define DMAX_CP2_SRC_GAT_EN                             DMAX_CP2_SRC_GAT_EN_MASK
#define DMAX_CP2_LOCK_EN_POS                            (10U)
#define DMAX_CP2_LOCK_EN_MASK                           (0x1UL << DMAX_CP2_LOCK_EN_POS)
#define DMAX_CP2_LOCK_EN                                DMAX_CP2_LOCK_EN_MASK
#define DMAX_CP2_MULTI_BLK_EN_POS                       (11U)
#define DMAX_CP2_MULTI_BLK_EN_MASK                      (0x1UL << DMAX_CP2_MULTI_BLK_EN_POS)
#define DMAX_CP2_MULTI_BLK_EN                           DMAX_CP2_MULTI_BLK_EN_MASK
#define DMAX_CP2_CTL_WB_EN_POS                          (12U)
#define DMAX_CP2_CTL_WB_EN_MASK                         (0x1UL << DMAX_CP2_CTL_WB_EN_POS)
#define DMAX_CP2_CTL_WB_EN                              DMAX_CP2_CTL_WB_EN_MASK
#define DMAX_CP2_HC_LLP_POS                             (13U)
#define DMAX_CP2_HC_LLP_MASK                            (0x1UL << DMAX_CP2_HC_LLP_POS)
#define DMAX_CP2_HC_LLP                                 DMAX_CP2_HC_LLP_MASK

#define DMAX_CP2_FC_POS                                 (14U)
#define DMAX_CP2_FC_MASK                                (0x3UL << DMAX_CP2_FC_POS)
#define DMAX_CP2_FC                                     DMAX_CP2_FC_MASK
#define DMAX_CP2_FC_T_DMA                               ( 0x00 << DMAX_CP2_FC_POS )
#define DMAX_CP2_FC_T_SRC                               ( 0x01 << DMAX_CP2_FC_POS )
#define DMAX_CP2_FC_T_DST                               ( 0x02 << DMAX_CP2_FC_POS )
#define DMAX_CP2_FC_T_ANY                               ( 0x03 << DMAX_CP2_FC_POS )

#define DMAX_CP2_MAX_MULT_SIZE_POS                      (16U)
#define DMAX_CP2_MAX_MULT_SIZE_MASK                     (0x7UL << DMAX_CP2_MAX_MULT_SIZE_POS)
#define DMAX_CP2_MAX_MULT_SIZE                          DMAX_CP2_MAX_MULT_SIZE_MASK
#define DMAX_CP2_MAX_MULT_SIZE_T_4                      ( 0x00 << DMAX_CP2_MAX_MULT_SIZE_POS )
#define DMAX_CP2_MAX_MULT_SIZE_T_8                      ( 0x01 << DMAX_CP2_MAX_MULT_SIZE_POS )
#define DMAX_CP2_MAX_MULT_SIZE_T_16                     ( 0x02 << DMAX_CP2_MAX_MULT_SIZE_POS )
#define DMAX_CP2_MAX_MULT_SIZE_T_32                     ( 0x03 << DMAX_CP2_MAX_MULT_SIZE_POS )
#define DMAX_CP2_MAX_MULT_SIZE_T_64                     ( 0x04 << DMAX_CP2_MAX_MULT_SIZE_POS )
#define DMAX_CP2_MAX_MULT_SIZE_T_128                    ( 0x05 << DMAX_CP2_MAX_MULT_SIZE_POS )
#define DMAX_CP2_MAX_MULT_SIZE_T_256                    ( 0x06 << DMAX_CP2_MAX_MULT_SIZE_POS )

#define DMAX_CP2_DMS_POS                                (19U)
#define DMAX_CP2_DMS_MASK                               (0x7UL << DMAX_CP2_DMS_POS)
#define DMAX_CP2_DMS                                    DMAX_CP2_DMS_MASK
#define DMAX_CP2_DMS_T_MASTER1                          ( 0x00 << DMAX_CP2_DMS_POS )
#define DMAX_CP2_DMS_T_MASTER2                          ( 0x01 << DMAX_CP2_DMS_POS )
#define DMAX_CP2_DMS_T_MASTER3                          ( 0x02 << DMAX_CP2_DMS_POS )
#define DMAX_CP2_DMS_T_MASTER4                          ( 0x03 << DMAX_CP2_DMS_POS )
#define DMAX_CP2_DMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP2_DMS_POS )

#define DMAX_CP2_LMS_POS                                (22U)
#define DMAX_CP2_LMS_MASK                               (0x7UL << DMAX_CP2_LMS_POS)
#define DMAX_CP2_LMS                                    DMAX_CP2_LMS_MASK
#define DMAX_CP2_LMS_T_MASTER1                          ( 0x00 << DMAX_CP2_LMS_POS )
#define DMAX_CP2_LMS_T_MASTER2                          ( 0x01 << DMAX_CP2_LMS_POS )
#define DMAX_CP2_LMS_T_MASTER3                          ( 0x02 << DMAX_CP2_LMS_POS )
#define DMAX_CP2_LMS_T_MASTER4                          ( 0x03 << DMAX_CP2_LMS_POS )
#define DMAX_CP2_LMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP2_LMS_POS )

#define DMAX_CP2_SMS_POS                                (22U)
#define DMAX_CP2_SMS_MASK                               (0x7UL << DMAX_CP2_SMS_POS)
#define DMAX_CP2_SMS                                    DMAX_CP2_SMS_MASK
#define DMAX_CP2_SMS_T_MASTER1                          ( 0x00 << DMAX_CP2_SMS_POS )
#define DMAX_CP2_SMS_T_MASTER2                          ( 0x01 << DMAX_CP2_SMS_POS )
#define DMAX_CP2_SMS_T_MASTER3                          ( 0x02 << DMAX_CP2_SMS_POS )
#define DMAX_CP2_SMS_T_MASTER4                          ( 0x03 << DMAX_CP2_SMS_POS )
#define DMAX_CP2_SMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP2_SMS_POS )

#define DMAX_CP2_FIFO_DEPTH_POS                         (28U)
#define DMAX_CP2_FIFO_DEPTH_MASK                        (0x7UL << DMAX_CP2_FIFO_DEPTH_POS)
#define DMAX_CP2_FIFO_DEPTH                             DMAX_CP2_FIFO_DEPTH_MASK
#define DMAX_CP2_FIFO_DEPTH_T_8                         ( 0x00 << DMAX_CP2_FIFO_DEPTH_POS )
#define DMAX_CP2_FIFO_DEPTH_T_16                        ( 0x01 << DMAX_CP2_FIFO_DEPTH_POS )
#define DMAX_CP2_FIFO_DEPTH_T_32                        ( 0x02 << DMAX_CP2_FIFO_DEPTH_POS )
#define DMAX_CP2_FIFO_DEPTH_T_64                        ( 0x03 << DMAX_CP2_FIFO_DEPTH_POS )
#define DMAX_CP2_FIFO_DEPTH_T_128                       ( 0x04 << DMAX_CP2_FIFO_DEPTH_POS )

/*****************  Bit definition for DMAX_CP1 register  ********************/
#define DMAX_CP1_DTW_POS                                (0U)
#define DMAX_CP1_DTW_MASK                               (0x7UL << DMAX_CP1_DTW_POS)
#define DMAX_CP1_DTW                                    DMAX_CP1_DTW_MASK
#define DMAX_CP1_DTW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP1_DTW_POS )
#define DMAX_CP1_DTW_T_8                                ( 0x01 << DMAX_CP1_DTW_POS )
#define DMAX_CP1_DTW_T_16                               ( 0x02 << DMAX_CP1_DTW_POS )
#define DMAX_CP1_DTW_T_32                               ( 0x03 << DMAX_CP1_DTW_POS )
#define DMAX_CP1_DTW_T_64                               ( 0x04 << DMAX_CP1_DTW_POS )
#define DMAX_CP1_DTW_T_128                              ( 0x05 << DMAX_CP1_DTW_POS )
#define DMAX_CP1_DTW_T_256                              ( 0x06 << DMAX_CP1_DTW_POS )

#define DMAX_CP1_STW_POS                                (3U)
#define DMAX_CP1_STW_MASK                               (0x7UL << DMAX_CP1_STW_POS)
#define DMAX_CP1_STW                                    DMAX_CP1_STW_MASK
#define DMAX_CP1_STW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP1_STW_POS )
#define DMAX_CP1_STW_T_8                                ( 0x01 << DMAX_CP1_STW_POS )
#define DMAX_CP1_STW_T_16                               ( 0x02 << DMAX_CP1_STW_POS )
#define DMAX_CP1_STW_T_32                               ( 0x03 << DMAX_CP1_STW_POS )
#define DMAX_CP1_STW_T_64                               ( 0x04 << DMAX_CP1_STW_POS )
#define DMAX_CP1_STW_T_128                              ( 0x05 << DMAX_CP1_STW_POS )
#define DMAX_CP1_STW_T_256                              ( 0x06 << DMAX_CP1_STW_POS )

#define DMAX_CP1_STAT_DST_POS                           (6U)
#define DMAX_CP1_STAT_DST_MASK                          (0x1UL << DMAX_CP1_STAT_DST_POS)
#define DMAX_CP1_STAT_DST                               DMAX_CP1_STAT_DST_MASK
#define DMAX_CP1_STAT_SRC_POS                           (7U)
#define DMAX_CP1_STAT_SRC_MASK                          (0x1UL << DMAX_CP1_STAT_SRC_POS)
#define DMAX_CP1_STAT_SRC                               DMAX_CP1_STAT_SRC_MASK
#define DMAX_CP1_DST_SCA_EN_POS                         (8U)
#define DMAX_CP1_DST_SCA_EN_MASK                        (0x1UL << DMAX_CP1_DST_SCA_EN_POS)
#define DMAX_CP1_DST_SCA_EN                             DMAX_CP1_DST_SCA_EN_MASK
#define DMAX_CP1_SRC_GAT_EN_POS                         (9U)
#define DMAX_CP1_SRC_GAT_EN_MASK                        (0x1UL << DMAX_CP1_SRC_GAT_EN_POS)
#define DMAX_CP1_SRC_GAT_EN                             DMAX_CP1_SRC_GAT_EN_MASK
#define DMAX_CP1_LOCK_EN_POS                            (10U)
#define DMAX_CP1_LOCK_EN_MASK                           (0x1UL << DMAX_CP1_LOCK_EN_POS)
#define DMAX_CP1_LOCK_EN                                DMAX_CP1_LOCK_EN_MASK
#define DMAX_CP1_MULTI_BLK_EN_POS                       (11U)
#define DMAX_CP1_MULTI_BLK_EN_MASK                      (0x1UL << DMAX_CP1_MULTI_BLK_EN_POS)
#define DMAX_CP1_MULTI_BLK_EN                           DMAX_CP1_MULTI_BLK_EN_MASK
#define DMAX_CP1_CTL_WB_EN_POS                          (12U)
#define DMAX_CP1_CTL_WB_EN_MASK                         (0x1UL << DMAX_CP1_CTL_WB_EN_POS)
#define DMAX_CP1_CTL_WB_EN                              DMAX_CP1_CTL_WB_EN_MASK
#define DMAX_CP1_HC_LLP_POS                             (13U)
#define DMAX_CP1_HC_LLP_MASK                            (0x1UL << DMAX_CP1_HC_LLP_POS)
#define DMAX_CP1_HC_LLP                                 DMAX_CP1_HC_LLP_MASK

#define DMAX_CP1_FC_POS                                 (14U)
#define DMAX_CP1_FC_MASK                                (0x3UL << DMAX_CP1_FC_POS)
#define DMAX_CP1_FC                                     DMAX_CP1_FC_MASK
#define DMAX_CP1_FC_T_DMA                               ( 0x00 << DMAX_CP1_FC_POS )
#define DMAX_CP1_FC_T_SRC                               ( 0x01 << DMAX_CP1_FC_POS )
#define DMAX_CP1_FC_T_DST                               ( 0x02 << DMAX_CP1_FC_POS )
#define DMAX_CP1_FC_T_ANY                               ( 0x03 << DMAX_CP1_FC_POS )

#define DMAX_CP1_MAX_MULT_SIZE_POS                      (16U)
#define DMAX_CP1_MAX_MULT_SIZE_MASK                     (0x7UL << DMAX_CP1_MAX_MULT_SIZE_POS)
#define DMAX_CP1_MAX_MULT_SIZE                          DMAX_CP1_MAX_MULT_SIZE_MASK
#define DMAX_CP1_MAX_MULT_SIZE_T_4                      ( 0x00 << DMAX_CP1_MAX_MULT_SIZE_POS )
#define DMAX_CP1_MAX_MULT_SIZE_T_8                      ( 0x01 << DMAX_CP1_MAX_MULT_SIZE_POS )
#define DMAX_CP1_MAX_MULT_SIZE_T_16                     ( 0x02 << DMAX_CP1_MAX_MULT_SIZE_POS )
#define DMAX_CP1_MAX_MULT_SIZE_T_32                     ( 0x03 << DMAX_CP1_MAX_MULT_SIZE_POS )
#define DMAX_CP1_MAX_MULT_SIZE_T_64                     ( 0x04 << DMAX_CP1_MAX_MULT_SIZE_POS )
#define DMAX_CP1_MAX_MULT_SIZE_T_128                    ( 0x05 << DMAX_CP1_MAX_MULT_SIZE_POS )
#define DMAX_CP1_MAX_MULT_SIZE_T_256                    ( 0x06 << DMAX_CP1_MAX_MULT_SIZE_POS )

#define DMAX_CP1_DMS_POS                                (19U)
#define DMAX_CP1_DMS_MASK                               (0x7UL << DMAX_CP1_DMS_POS)
#define DMAX_CP1_DMS                                    DMAX_CP1_DMS_MASK
#define DMAX_CP1_DMS_T_MASTER1                          ( 0x00 << DMAX_CP1_DMS_POS )
#define DMAX_CP1_DMS_T_MASTER2                          ( 0x01 << DMAX_CP1_DMS_POS )
#define DMAX_CP1_DMS_T_MASTER3                          ( 0x02 << DMAX_CP1_DMS_POS )
#define DMAX_CP1_DMS_T_MASTER4                          ( 0x03 << DMAX_CP1_DMS_POS )
#define DMAX_CP1_DMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP1_DMS_POS )

#define DMAX_CP1_LMS_POS                                (22U)
#define DMAX_CP1_LMS_MASK                               (0x7UL << DMAX_CP1_LMS_POS)
#define DMAX_CP1_LMS                                    DMAX_CP1_LMS_MASK
#define DMAX_CP1_LMS_T_MASTER1                          ( 0x00 << DMAX_CP1_LMS_POS )
#define DMAX_CP1_LMS_T_MASTER2                          ( 0x01 << DMAX_CP1_LMS_POS )
#define DMAX_CP1_LMS_T_MASTER3                          ( 0x02 << DMAX_CP1_LMS_POS )
#define DMAX_CP1_LMS_T_MASTER4                          ( 0x03 << DMAX_CP1_LMS_POS )
#define DMAX_CP1_LMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP1_LMS_POS )

#define DMAX_CP1_SMS_POS                                (22U)
#define DMAX_CP1_SMS_MASK                               (0x7UL << DMAX_CP1_SMS_POS)
#define DMAX_CP1_SMS                                    DMAX_CP1_SMS_MASK
#define DMAX_CP1_SMS_T_MASTER1                          ( 0x00 << DMAX_CP1_SMS_POS )
#define DMAX_CP1_SMS_T_MASTER2                          ( 0x01 << DMAX_CP1_SMS_POS )
#define DMAX_CP1_SMS_T_MASTER3                          ( 0x02 << DMAX_CP1_SMS_POS )
#define DMAX_CP1_SMS_T_MASTER4                          ( 0x03 << DMAX_CP1_SMS_POS )
#define DMAX_CP1_SMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP1_SMS_POS )

#define DMAX_CP1_FIFO_DEPTH_POS                         (28U)
#define DMAX_CP1_FIFO_DEPTH_MASK                        (0x7UL << DMAX_CP1_FIFO_DEPTH_POS)
#define DMAX_CP1_FIFO_DEPTH                             DMAX_CP1_FIFO_DEPTH_MASK
#define DMAX_CP1_FIFO_DEPTH_T_8                         ( 0x00 << DMAX_CP1_FIFO_DEPTH_POS )
#define DMAX_CP1_FIFO_DEPTH_T_16                        ( 0x01 << DMAX_CP1_FIFO_DEPTH_POS )
#define DMAX_CP1_FIFO_DEPTH_T_32                        ( 0x02 << DMAX_CP1_FIFO_DEPTH_POS )
#define DMAX_CP1_FIFO_DEPTH_T_64                        ( 0x03 << DMAX_CP1_FIFO_DEPTH_POS )
#define DMAX_CP1_FIFO_DEPTH_T_128                       ( 0x04 << DMAX_CP1_FIFO_DEPTH_POS )

/*****************  Bit definition for DMAX_CP0 register  ********************/
#define DMAX_CP0_DTW_POS                                (0U)
#define DMAX_CP0_DTW_MASK                               (0x7UL << DMAX_CP0_DTW_POS)
#define DMAX_CP0_DTW                                    DMAX_CP0_DTW_MASK
#define DMAX_CP0_DTW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP0_DTW_POS )
#define DMAX_CP0_DTW_T_8                                ( 0x01 << DMAX_CP0_DTW_POS )
#define DMAX_CP0_DTW_T_16                               ( 0x02 << DMAX_CP0_DTW_POS )
#define DMAX_CP0_DTW_T_32                               ( 0x03 << DMAX_CP0_DTW_POS )
#define DMAX_CP0_DTW_T_64                               ( 0x04 << DMAX_CP0_DTW_POS )
#define DMAX_CP0_DTW_T_128                              ( 0x05 << DMAX_CP0_DTW_POS )
#define DMAX_CP0_DTW_T_256                              ( 0x06 << DMAX_CP0_DTW_POS )

#define DMAX_CP0_STW_POS                                (3U)
#define DMAX_CP0_STW_MASK                               (0x7UL << DMAX_CP0_STW_POS)
#define DMAX_CP0_STW                                    DMAX_CP0_STW_MASK
#define DMAX_CP0_STW_T_NO_HARDCODE                      ( 0x00 << DMAX_CP0_STW_POS )
#define DMAX_CP0_STW_T_8                                ( 0x01 << DMAX_CP0_STW_POS )
#define DMAX_CP0_STW_T_16                               ( 0x02 << DMAX_CP0_STW_POS )
#define DMAX_CP0_STW_T_32                               ( 0x03 << DMAX_CP0_STW_POS )
#define DMAX_CP0_STW_T_64                               ( 0x04 << DMAX_CP0_STW_POS )
#define DMAX_CP0_STW_T_128                              ( 0x05 << DMAX_CP0_STW_POS )
#define DMAX_CP0_STW_T_256                              ( 0x06 << DMAX_CP0_STW_POS )

#define DMAX_CP0_STAT_DST_POS                           (6U)
#define DMAX_CP0_STAT_DST_MASK                          (0x1UL << DMAX_CP0_STAT_DST_POS)
#define DMAX_CP0_STAT_DST                               DMAX_CP0_STAT_DST_MASK
#define DMAX_CP0_STAT_SRC_POS                           (7U)
#define DMAX_CP0_STAT_SRC_MASK                          (0x1UL << DMAX_CP0_STAT_SRC_POS)
#define DMAX_CP0_STAT_SRC                               DMAX_CP0_STAT_SRC_MASK
#define DMAX_CP0_DST_SCA_EN_POS                         (8U)
#define DMAX_CP0_DST_SCA_EN_MASK                        (0x1UL << DMAX_CP0_DST_SCA_EN_POS)
#define DMAX_CP0_DST_SCA_EN                             DMAX_CP0_DST_SCA_EN_MASK
#define DMAX_CP0_SRC_GAT_EN_POS                         (9U)
#define DMAX_CP0_SRC_GAT_EN_MASK                        (0x1UL << DMAX_CP0_SRC_GAT_EN_POS)
#define DMAX_CP0_SRC_GAT_EN                             DMAX_CP0_SRC_GAT_EN_MASK
#define DMAX_CP0_LOCK_EN_POS                            (10U)
#define DMAX_CP0_LOCK_EN_MASK                           (0x1UL << DMAX_CP0_LOCK_EN_POS)
#define DMAX_CP0_LOCK_EN                                DMAX_CP0_LOCK_EN_MASK
#define DMAX_CP0_MULTI_BLK_EN_POS                       (11U)
#define DMAX_CP0_MULTI_BLK_EN_MASK                      (0x1UL << DMAX_CP0_MULTI_BLK_EN_POS)
#define DMAX_CP0_MULTI_BLK_EN                           DMAX_CP0_MULTI_BLK_EN_MASK
#define DMAX_CP0_CTL_WB_EN_POS                          (12U)
#define DMAX_CP0_CTL_WB_EN_MASK                         (0x1UL << DMAX_CP0_CTL_WB_EN_POS)
#define DMAX_CP0_CTL_WB_EN                              DMAX_CP0_CTL_WB_EN_MASK
#define DMAX_CP0_HC_LLP_POS                             (13U)
#define DMAX_CP0_HC_LLP_MASK                            (0x1UL << DMAX_CP0_HC_LLP_POS)
#define DMAX_CP0_HC_LLP                                 DMAX_CP0_HC_LLP_MASK

#define DMAX_CP0_FC_POS                                 (14U)
#define DMAX_CP0_FC_MASK                                (0x3UL << DMAX_CP0_FC_POS)
#define DMAX_CP0_FC                                     DMAX_CP0_FC_MASK
#define DMAX_CP0_FC_T_DMA                               ( 0x00 << DMAX_CP0_FC_POS )
#define DMAX_CP0_FC_T_SRC                               ( 0x01 << DMAX_CP0_FC_POS )
#define DMAX_CP0_FC_T_DST                               ( 0x02 << DMAX_CP0_FC_POS )
#define DMAX_CP0_FC_T_ANY                               ( 0x03 << DMAX_CP0_FC_POS )

#define DMAX_CP0_MAX_MULT_SIZE_POS                      (16U)
#define DMAX_CP0_MAX_MULT_SIZE_MASK                     (0x7UL << DMAX_CP0_MAX_MULT_SIZE_POS)
#define DMAX_CP0_MAX_MULT_SIZE                          DMAX_CP0_MAX_MULT_SIZE_MASK
#define DMAX_CP0_MAX_MULT_SIZE_T_4                      ( 0x00 << DMAX_CP0_MAX_MULT_SIZE_POS )
#define DMAX_CP0_MAX_MULT_SIZE_T_8                      ( 0x01 << DMAX_CP0_MAX_MULT_SIZE_POS )
#define DMAX_CP0_MAX_MULT_SIZE_T_16                     ( 0x02 << DMAX_CP0_MAX_MULT_SIZE_POS )
#define DMAX_CP0_MAX_MULT_SIZE_T_32                     ( 0x03 << DMAX_CP0_MAX_MULT_SIZE_POS )
#define DMAX_CP0_MAX_MULT_SIZE_T_64                     ( 0x04 << DMAX_CP0_MAX_MULT_SIZE_POS )
#define DMAX_CP0_MAX_MULT_SIZE_T_128                    ( 0x05 << DMAX_CP0_MAX_MULT_SIZE_POS )
#define DMAX_CP0_MAX_MULT_SIZE_T_256                    ( 0x06 << DMAX_CP0_MAX_MULT_SIZE_POS )

#define DMAX_CP0_DMS_POS                                (19U)
#define DMAX_CP0_DMS_MASK                               (0x7UL << DMAX_CP0_DMS_POS)
#define DMAX_CP0_DMS                                    DMAX_CP0_DMS_MASK
#define DMAX_CP0_DMS_T_MASTER1                          ( 0x00 << DMAX_CP0_DMS_POS )
#define DMAX_CP0_DMS_T_MASTER2                          ( 0x01 << DMAX_CP0_DMS_POS )
#define DMAX_CP0_DMS_T_MASTER3                          ( 0x02 << DMAX_CP0_DMS_POS )
#define DMAX_CP0_DMS_T_MASTER4                          ( 0x03 << DMAX_CP0_DMS_POS )
#define DMAX_CP0_DMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP0_DMS_POS )

#define DMAX_CP0_LMS_POS                                (22U)
#define DMAX_CP0_LMS_MASK                               (0x7UL << DMAX_CP0_LMS_POS)
#define DMAX_CP0_LMS                                    DMAX_CP0_LMS_MASK
#define DMAX_CP0_LMS_T_MASTER1                          ( 0x00 << DMAX_CP0_LMS_POS )
#define DMAX_CP0_LMS_T_MASTER2                          ( 0x01 << DMAX_CP0_LMS_POS )
#define DMAX_CP0_LMS_T_MASTER3                          ( 0x02 << DMAX_CP0_LMS_POS )
#define DMAX_CP0_LMS_T_MASTER4                          ( 0x03 << DMAX_CP0_LMS_POS )
#define DMAX_CP0_LMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP0_LMS_POS )

#define DMAX_CP0_SMS_POS                                (22U)
#define DMAX_CP0_SMS_MASK                               (0x7UL << DMAX_CP0_SMS_POS)
#define DMAX_CP0_SMS                                    DMAX_CP0_SMS_MASK
#define DMAX_CP0_SMS_T_MASTER1                          ( 0x00 << DMAX_CP0_SMS_POS )
#define DMAX_CP0_SMS_T_MASTER2                          ( 0x01 << DMAX_CP0_SMS_POS )
#define DMAX_CP0_SMS_T_MASTER3                          ( 0x02 << DMAX_CP0_SMS_POS )
#define DMAX_CP0_SMS_T_MASTER4                          ( 0x03 << DMAX_CP0_SMS_POS )
#define DMAX_CP0_SMS_T_NO_HARDCODE                      ( 0x04 << DMAX_CP0_SMS_POS )

#define DMAX_CP0_FIFO_DEPTH_POS                         (28U)
#define DMAX_CP0_FIFO_DEPTH_MASK                        (0x7UL << DMAX_CP0_FIFO_DEPTH_POS)
#define DMAX_CP0_FIFO_DEPTH                             DMAX_CP0_FIFO_DEPTH_MASK
#define DMAX_CP0_FIFO_DEPTH_T_8                         ( 0x00 << DMAX_CP0_FIFO_DEPTH_POS )
#define DMAX_CP0_FIFO_DEPTH_T_16                        ( 0x01 << DMAX_CP0_FIFO_DEPTH_POS )
#define DMAX_CP0_FIFO_DEPTH_T_32                        ( 0x02 << DMAX_CP0_FIFO_DEPTH_POS )
#define DMAX_CP0_FIFO_DEPTH_T_64                        ( 0x03 << DMAX_CP0_FIFO_DEPTH_POS )
#define DMAX_CP0_FIFO_DEPTH_T_128                       ( 0x04 << DMAX_CP0_FIFO_DEPTH_POS )

/*****************  Bit definition for DMAX_MBTP register  ********************/
#define DMAX_MBTP_CH0_POS                               (0U)
#define DMAX_MBTP_CH0_MASK                              (0xFUL << DMAX_MBTP_CH0_POS)
#define DMAX_MBTP_CH0                                   DMAX_MBTP_CH0_MASK
#define DMAX_MBTP_CH1_POS                               (4U)
#define DMAX_MBTP_CH1_MASK                              (0xFUL << DMAX_MBTP_CH1_POS)
#define DMAX_MBTP_CH1                                   DMAX_MBTP_CH1_MASK
#define DMAX_MBTP_CH2_POS                               (8U)
#define DMAX_MBTP_CH2_MASK                              (0xFUL << DMAX_MBTP_CH2_POS)
#define DMAX_MBTP_CH2                                   DMAX_MBTP_CH2_MASK
#define DMAX_MBTP_CH3_POS                               (12U)
#define DMAX_MBTP_CH3_MASK                              (0xFUL << DMAX_MBTP_CH3_POS)
#define DMAX_MBTP_CH3                                   DMAX_MBTP_CH3_MASK
#define DMAX_MBTP_CH4_POS                               (16U)
#define DMAX_MBTP_CH4_MASK                              (0xFUL << DMAX_MBTP_CH4_POS)
#define DMAX_MBTP_CH4                                   DMAX_MBTP_CH4_MASK
#define DMAX_MBTP_CH5_POS                               (20U)
#define DMAX_MBTP_CH5_MASK                              (0xFUL << DMAX_MBTP_CH5_POS)
#define DMAX_MBTP_CH5                                   DMAX_MBTP_CH5_MASK
#define DMAX_MBTP_CH6_POS                               (24U)
#define DMAX_MBTP_CH6_MASK                              (0xFUL << DMAX_MBTP_CH6_POS)
#define DMAX_MBTP_CH6                                   DMAX_MBTP_CH6_MASK
#define DMAX_MBTP_CH7_POS                               (28U)
#define DMAX_MBTP_CH7_MASK                              (0xFUL << DMAX_MBTP_CH7_POS)
#define DMAX_MBTP_CH7                                   DMAX_MBTP_CH7_MASK

#define DMAX_MBTP_T_NO_HARDCODE                         ( 0x00 )
#define DMAX_MBTP_T_CONT_RELOAD                         ( 0x01 )
#define DMAX_MBTP_T_RELOAD_CONT                         ( 0x02 )
#define DMAX_MBTP_T_RELOAD_RELOAD                       ( 0x03 )
#define DMAX_MBTP_T_COUNT_LLP                           ( 0x04 )
#define DMAX_MBTP_T_RELOAD_LLP                          ( 0x05 )
#define DMAX_MBTP_T_LLP_CONT                            ( 0x06 )
#define DMAX_MBTP_T_LLP_RELOAD                          ( 0x07 )
#define DMAX_MBTP_T_LLP_LLP                             ( 0x08 )

#define DMAX_MBTP_CH0_T_NO_HARDCODE                     ( 0x00 << DMAX_MBTP_CH0_POS )
#define DMAX_MBTP_CH0_T_CONT_RELOAD                     ( 0x01 << DMAX_MBTP_CH0_POS )
#define DMAX_MBTP_CH0_T_RELOAD_CONT                     ( 0x02 << DMAX_MBTP_CH0_POS )
#define DMAX_MBTP_CH0_T_RELOAD_RELOAD                   ( 0x03 << DMAX_MBTP_CH0_POS )
#define DMAX_MBTP_CH0_T_COUNT_LLP                       ( 0x04 << DMAX_MBTP_CH0_POS )
#define DMAX_MBTP_CH0_T_RELOAD_LLP                      ( 0x05 << DMAX_MBTP_CH0_POS )
#define DMAX_MBTP_CH0_T_LLP_CONT                        ( 0x06 << DMAX_MBTP_CH0_POS )
#define DMAX_MBTP_CH0_T_LLP_RELOAD                      ( 0x07 << DMAX_MBTP_CH0_POS )
#define DMAX_MBTP_CH0_T_LLP_LLP                         ( 0x08 << DMAX_MBTP_CH0_POS )

#define DMAX_MBTP_CH1_T_NO_HARDCODE                     ( 0x00 << DMAX_MBTP_CH1_POS )
#define DMAX_MBTP_CH1_T_CONT_RELOAD                     ( 0x01 << DMAX_MBTP_CH1_POS )
#define DMAX_MBTP_CH1_T_RELOAD_CONT                     ( 0x02 << DMAX_MBTP_CH1_POS )
#define DMAX_MBTP_CH1_T_RELOAD_RELOAD                   ( 0x03 << DMAX_MBTP_CH1_POS )
#define DMAX_MBTP_CH1_T_COUNT_LLP                       ( 0x04 << DMAX_MBTP_CH1_POS )
#define DMAX_MBTP_CH1_T_RELOAD_LLP                      ( 0x05 << DMAX_MBTP_CH1_POS )
#define DMAX_MBTP_CH1_T_LLP_CONT                        ( 0x06 << DMAX_MBTP_CH1_POS )
#define DMAX_MBTP_CH1_T_LLP_RELOAD                      ( 0x07 << DMAX_MBTP_CH1_POS )
#define DMAX_MBTP_CH1_T_LLP_LLP                         ( 0x08 << DMAX_MBTP_CH1_POS )

#define DMAX_MBTP_CH2_T_NO_HARDCODE                     ( 0x00 << DMAX_MBTP_CH2_POS )
#define DMAX_MBTP_CH2_T_CONT_RELOAD                     ( 0x01 << DMAX_MBTP_CH2_POS )
#define DMAX_MBTP_CH2_T_RELOAD_CONT                     ( 0x02 << DMAX_MBTP_CH2_POS )
#define DMAX_MBTP_CH2_T_RELOAD_RELOAD                   ( 0x03 << DMAX_MBTP_CH2_POS )
#define DMAX_MBTP_CH2_T_COUNT_LLP                       ( 0x04 << DMAX_MBTP_CH2_POS )
#define DMAX_MBTP_CH2_T_RELOAD_LLP                      ( 0x05 << DMAX_MBTP_CH2_POS )
#define DMAX_MBTP_CH2_T_LLP_CONT                        ( 0x06 << DMAX_MBTP_CH2_POS )
#define DMAX_MBTP_CH2_T_LLP_RELOAD                      ( 0x07 << DMAX_MBTP_CH2_POS )
#define DMAX_MBTP_CH2_T_LLP_LLP                         ( 0x08 << DMAX_MBTP_CH2_POS )

#define DMAX_MBTP_CH3_T_NO_HARDCODE                     ( 0x00 << DMAX_MBTP_CH3_POS )
#define DMAX_MBTP_CH3_T_CONT_RELOAD                     ( 0x01 << DMAX_MBTP_CH3_POS )
#define DMAX_MBTP_CH3_T_RELOAD_CONT                     ( 0x02 << DMAX_MBTP_CH3_POS )
#define DMAX_MBTP_CH3_T_RELOAD_RELOAD                   ( 0x03 << DMAX_MBTP_CH3_POS )
#define DMAX_MBTP_CH3_T_COUNT_LLP                       ( 0x04 << DMAX_MBTP_CH3_POS )
#define DMAX_MBTP_CH3_T_RELOAD_LLP                      ( 0x05 << DMAX_MBTP_CH3_POS )
#define DMAX_MBTP_CH3_T_LLP_CONT                        ( 0x06 << DMAX_MBTP_CH3_POS )
#define DMAX_MBTP_CH3_T_LLP_RELOAD                      ( 0x07 << DMAX_MBTP_CH3_POS )
#define DMAX_MBTP_CH3_T_LLP_LLP                         ( 0x08 << DMAX_MBTP_CH3_POS )

#define DMAX_MBTP_CH4_T_NO_HARDCODE                     ( 0x00 << DMAX_MBTP_CH4_POS )
#define DMAX_MBTP_CH4_T_CONT_RELOAD                     ( 0x01 << DMAX_MBTP_CH4_POS )
#define DMAX_MBTP_CH4_T_RELOAD_CONT                     ( 0x02 << DMAX_MBTP_CH4_POS )
#define DMAX_MBTP_CH4_T_RELOAD_RELOAD                   ( 0x03 << DMAX_MBTP_CH4_POS )
#define DMAX_MBTP_CH4_T_COUNT_LLP                       ( 0x04 << DMAX_MBTP_CH4_POS )
#define DMAX_MBTP_CH4_T_RELOAD_LLP                      ( 0x05 << DMAX_MBTP_CH4_POS )
#define DMAX_MBTP_CH4_T_LLP_CONT                        ( 0x06 << DMAX_MBTP_CH4_POS )
#define DMAX_MBTP_CH4_T_LLP_RELOAD                      ( 0x07 << DMAX_MBTP_CH4_POS )
#define DMAX_MBTP_CH4_T_LLP_LLP                         ( 0x08 << DMAX_MBTP_CH4_POS )

#define DMAX_MBTP_CH5_T_NO_HARDCODE                     ( 0x00 << DMAX_MBTP_CH5_POS )
#define DMAX_MBTP_CH5_T_CONT_RELOAD                     ( 0x01 << DMAX_MBTP_CH5_POS )
#define DMAX_MBTP_CH5_T_RELOAD_CONT                     ( 0x02 << DMAX_MBTP_CH5_POS )
#define DMAX_MBTP_CH5_T_RELOAD_RELOAD                   ( 0x03 << DMAX_MBTP_CH5_POS )
#define DMAX_MBTP_CH5_T_COUNT_LLP                       ( 0x04 << DMAX_MBTP_CH5_POS )
#define DMAX_MBTP_CH5_T_RELOAD_LLP                      ( 0x05 << DMAX_MBTP_CH5_POS )
#define DMAX_MBTP_CH5_T_LLP_CONT                        ( 0x06 << DMAX_MBTP_CH5_POS )
#define DMAX_MBTP_CH5_T_LLP_RELOAD                      ( 0x07 << DMAX_MBTP_CH5_POS )
#define DMAX_MBTP_CH5_T_LLP_LLP                         ( 0x08 << DMAX_MBTP_CH5_POS )

#define DMAX_MBTP_CH6_T_NO_HARDCODE                     ( 0x00 << DMAX_MBTP_CH6_POS )
#define DMAX_MBTP_CH6_T_CONT_RELOAD                     ( 0x01 << DMAX_MBTP_CH6_POS )
#define DMAX_MBTP_CH6_T_RELOAD_CONT                     ( 0x02 << DMAX_MBTP_CH6_POS )
#define DMAX_MBTP_CH6_T_RELOAD_RELOAD                   ( 0x03 << DMAX_MBTP_CH6_POS )
#define DMAX_MBTP_CH6_T_COUNT_LLP                       ( 0x04 << DMAX_MBTP_CH6_POS )
#define DMAX_MBTP_CH6_T_RELOAD_LLP                      ( 0x05 << DMAX_MBTP_CH6_POS )
#define DMAX_MBTP_CH6_T_LLP_CONT                        ( 0x06 << DMAX_MBTP_CH6_POS )
#define DMAX_MBTP_CH6_T_LLP_RELOAD                      ( 0x07 << DMAX_MBTP_CH6_POS )
#define DMAX_MBTP_CH6_T_LLP_LLP                         ( 0x08 << DMAX_MBTP_CH6_POS )

#define DMAX_MBTP_CH7_T_NO_HARDCODE                     ( 0x00 << DMAX_MBTP_CH7_POS )
#define DMAX_MBTP_CH7_T_CONT_RELOAD                     ( 0x01 << DMAX_MBTP_CH7_POS )
#define DMAX_MBTP_CH7_T_RELOAD_CONT                     ( 0x02 << DMAX_MBTP_CH7_POS )
#define DMAX_MBTP_CH7_T_RELOAD_RELOAD                   ( 0x03 << DMAX_MBTP_CH7_POS )
#define DMAX_MBTP_CH7_T_COUNT_LLP                       ( 0x04 << DMAX_MBTP_CH7_POS )
#define DMAX_MBTP_CH7_T_RELOAD_LLP                      ( 0x05 << DMAX_MBTP_CH7_POS )
#define DMAX_MBTP_CH7_T_LLP_CONT                        ( 0x06 << DMAX_MBTP_CH7_POS )
#define DMAX_MBTP_CH7_T_LLP_RELOAD                      ( 0x07 << DMAX_MBTP_CH7_POS )
#define DMAX_MBTP_CH7_T_LLP_LLP                         ( 0x08 << DMAX_MBTP_CH7_POS )

/*****************  Bit definition for DMAX_MBSP register  ********************/
#define DMAX_MBSP_CH0_POS                               (0U)
#define DMAX_MBSP_CH0_MASK                              (0xFUL << DMAX_MBSP_CH0_POS)
#define DMAX_MBSP_CH0                                   DMAX_MBSP_CH0_MASK
#define DMAX_MBSP_CH1_POS                               (4U)
#define DMAX_MBSP_CH1_MASK                              (0xFUL << DMAX_MBSP_CH1_POS)
#define DMAX_MBSP_CH1                                   DMAX_MBSP_CH1_MASK
#define DMAX_MBSP_CH2_POS                               (8U)
#define DMAX_MBSP_CH2_MASK                              (0xFUL << DMAX_MBSP_CH2_POS)
#define DMAX_MBSP_CH2                                   DMAX_MBSP_CH2_MASK
#define DMAX_MBSP_CH3_POS                               (12U)
#define DMAX_MBSP_CH3_MASK                              (0xFUL << DMAX_MBSP_CH3_POS)
#define DMAX_MBSP_CH3                                   DMAX_MBSP_CH3_MASK
#define DMAX_MBSP_CH4_POS                               (16U)
#define DMAX_MBSP_CH4_MASK                              (0xFUL << DMAX_MBSP_CH4_POS)
#define DMAX_MBSP_CH4                                   DMAX_MBSP_CH4_MASK
#define DMAX_MBSP_CH5_POS                               (20U)
#define DMAX_MBSP_CH5_MASK                              (0xFUL << DMAX_MBSP_CH5_POS)
#define DMAX_MBSP_CH5                                   DMAX_MBSP_CH5_MASK
#define DMAX_MBSP_CH6_POS                               (24U)
#define DMAX_MBSP_CH6_MASK                              (0xFUL << DMAX_MBSP_CH6_POS)
#define DMAX_MBSP_CH6                                   DMAX_MBSP_CH6_MASK
#define DMAX_MBSP_CH7_POS                               (28U)
#define DMAX_MBSP_CH7_MASK                              (0xFUL << DMAX_MBSP_CH7_POS)
#define DMAX_MBSP_CH7                                   DMAX_MBSP_CH7_MASK

#define DMAX_MBSP_T_3                                   ( 0x00 )
#define DMAX_MBSP_T_7                                   ( 0x01 )
#define DMAX_MBSP_T_15                                  ( 0x02 )
#define DMAX_MBSP_T_31                                  ( 0x03 )
#define DMAX_MBSP_T_63                                  ( 0x04 )
#define DMAX_MBSP_T_127                                 ( 0x05 )
#define DMAX_MBSP_T_255                                 ( 0x06 )
#define DMAX_MBSP_T_511                                 ( 0x07 )
#define DMAX_MBSP_T_1023                                ( 0x08 )
#define DMAX_MBSP_T_2047                                ( 0x09 )
#define DMAX_MBSP_T_4095                                ( 0x0A )

#define DMAX_MBSP_CH0_T_3                               ( 0x00<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_7                               ( 0x01<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_15                              ( 0x02<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_31                              ( 0x03<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_63                              ( 0x04<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_127                             ( 0x05<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_255                             ( 0x06<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_511                             ( 0x07<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_1023                            ( 0x08<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_2047                            ( 0x09<< DMAX_MBSP_CH0_POS )
#define DMAX_MBSP_CH0_T_4095                            ( 0x0A<< DMAX_MBSP_CH0_POS )

#define DMAX_MBSP_CH1_T_3                               ( 0x00<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_7                               ( 0x01<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_15                              ( 0x02<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_31                              ( 0x03<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_63                              ( 0x04<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_127                             ( 0x05<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_255                             ( 0x06<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_511                             ( 0x07<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_1023                            ( 0x08<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_2047                            ( 0x09<< DMAX_MBSP_CH1_POS )
#define DMAX_MBSP_CH1_T_4095                            ( 0x0A<< DMAX_MBSP_CH1_POS )

#define DMAX_MBSP_CH2_T_3                               ( 0x00<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_7                               ( 0x01<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_15                              ( 0x02<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_31                              ( 0x03<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_63                              ( 0x04<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_127                             ( 0x05<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_255                             ( 0x06<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_511                             ( 0x07<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_1023                            ( 0x08<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_2047                            ( 0x09<< DMAX_MBSP_CH2_POS )
#define DMAX_MBSP_CH2_T_4095                            ( 0x0A<< DMAX_MBSP_CH2_POS )

#define DMAX_MBSP_CH3_T_3                               ( 0x00<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_7                               ( 0x01<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_15                              ( 0x02<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_31                              ( 0x03<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_63                              ( 0x04<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_127                             ( 0x05<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_255                             ( 0x06<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_511                             ( 0x07<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_1023                            ( 0x08<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_2047                            ( 0x09<< DMAX_MBSP_CH3_POS )
#define DMAX_MBSP_CH3_T_4095                            ( 0x0A<< DMAX_MBSP_CH3_POS )

#define DMAX_MBSP_CH4_T_3                               ( 0x00<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_7                               ( 0x01<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_15                              ( 0x02<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_31                              ( 0x03<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_63                              ( 0x04<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_127                             ( 0x05<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_255                             ( 0x06<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_511                             ( 0x07<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_1023                            ( 0x08<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_2047                            ( 0x09<< DMAX_MBSP_CH4_POS )
#define DMAX_MBSP_CH4_T_4095                            ( 0x0A<< DMAX_MBSP_CH4_POS )

#define DMAX_MBSP_CH5_T_3                               ( 0x00<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_7                               ( 0x01<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_15                              ( 0x02<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_31                              ( 0x03<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_63                              ( 0x04<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_127                             ( 0x05<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_255                             ( 0x06<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_511                             ( 0x07<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_1023                            ( 0x08<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_2047                            ( 0x09<< DMAX_MBSP_CH5_POS )
#define DMAX_MBSP_CH5_T_4095                            ( 0x0A<< DMAX_MBSP_CH5_POS )

#define DMAX_MBSP_CH6_T_3                               ( 0x00<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_7                               ( 0x01<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_15                              ( 0x02<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_31                              ( 0x03<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_63                              ( 0x04<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_127                             ( 0x05<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_255                             ( 0x06<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_511                             ( 0x07<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_1023                            ( 0x08<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_2047                            ( 0x09<< DMAX_MBSP_CH6_POS )
#define DMAX_MBSP_CH6_T_4095                            ( 0x0A<< DMAX_MBSP_CH6_POS )

#define DMAX_MBSP_CH7_T_3                               ( 0x00<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_7                               ( 0x01<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_15                              ( 0x02<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_31                              ( 0x03<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_63                              ( 0x04<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_127                             ( 0x05<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_255                             ( 0x06<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_511                             ( 0x07<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_1023                            ( 0x08<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_2047                            ( 0x09<< DMAX_MBSP_CH7_POS )
#define DMAX_MBSP_CH7_T_4095                            ( 0x0A<< DMAX_MBSP_CH7_POS )


/*****************  Bit definition for DMAX_TLP register  ********************/
#define DMAX_TLP_BIG_ENDIAN_POS                         (0U)
#define DMAX_TLP_BIG_ENDIAN_MASK                        (0x1UL << DMAX_TLP_BIG_ENDIAN_POS)
#define DMAX_TLP_BIG_ENDIAN                             DMAX_TLP_BIG_ENDIAN_MASK
#define DMAX_TLP_INTR_IO_POS                            (1U)
#define DMAX_TLP_INTR_IO_MASK                           (0x3UL << DMAX_TLP_INTR_IO_POS)
#define DMAX_TLP_INTR_IO                                DMAX_TLP_INTR_IO_MASK
#define DMAX_TLP_INTR_IO_T_ALL                          ( 0x00 << DMAX_TLP_INTR_IO_POS )
#define DMAX_TLP_INTR_IO_T_TYPE                         ( 0x01 << DMAX_TLP_INTR_IO_POS )
#define DMAX_TLP_INTR_IO_T_COMBINED                     ( 0x02 << DMAX_TLP_INTR_IO_POS )

#define DMAX_TLP_MAB_RST_POS                            (3U)
#define DMAX_TLP_MAB_RST_MASK                           (0x1UL << DMAX_TLP_MAB_RST_POS)
#define DMAX_TLP_MAB_RST                                DMAX_TLP_MAB_RST_MASK
#define DMAX_TLP_CH_NUM_POS                             (8U)
#define DMAX_TLP_CH_NUM_MASK                            (0x7UL << DMAX_TLP_CH_NUM_POS)
#define DMAX_TLP_CH_NUM                                 DMAX_TLP_CH_NUM_MASK
#define DMAX_TLP_MST_INT_NUM_POS                        (11U)
#define DMAX_TLP_MST_INT_NUM_MASK                       (0x3UL << DMAX_TLP_MST_INT_NUM_POS)
#define DMAX_TLP_MST_INT_NUM                            DMAX_TLP_MST_INT_NUM_MASK
#define DMAX_TLP_SHDW_POS                               (13U)
#define DMAX_TLP_SHDW_MASK                              (0x2UL << DMAX_TLP_SHDW_POS)
#define DMAX_TLP_SHDW                                   DMAX_TLP_SHDW_MASK
#define DMAX_TLP_SHDW_T_32                              ( 0x00 << DMAX_TLP_SHDW_POS )
#define DMAX_TLP_SHDW_T_64                              ( 0x01 << DMAX_TLP_SHDW_POS )
#define DMAX_TLP_SHDW_T_128                             ( 0x02 << DMAX_TLP_SHDW_POS )
#define DMAX_TLP_SHDW_T_256                             ( 0x03 << DMAX_TLP_SHDW_POS )

#define DMAX_TLP_M4HDW_POS                              (15U)
#define DMAX_TLP_M4HDW_MASK                             (0x2UL << DMAX_TLP_M4HDW_POS)
#define DMAX_TLP_M4HDW                                  DMAX_TLP_M4HDW_MASK
#define DMAX_TLP_M4HDW_T_32                             ( 0x00 << DMAX_TLP_M4HDW_POS )
#define DMAX_TLP_M4HDW_T_64                             ( 0x01 << DMAX_TLP_M4HDW_POS )
#define DMAX_TLP_M4HDW_T_128                            ( 0x02 << DMAX_TLP_M4HDW_POS )
#define DMAX_TLP_M4HDW_T_256                            ( 0x03 << DMAX_TLP_M4HDW_POS )

#define DMAX_TLP_M3HDW_POS                              (17U)
#define DMAX_TLP_M3HDW_MASK                             (0x2UL << DMAX_TLP_M3HDW_POS)
#define DMAX_TLP_M3HDW                                  DMAX_TLP_M3HDW_MASK
#define DMAX_TLP_M3HDW_T_32                             ( 0x00 << DMAX_TLP_M3HDW_POS )
#define DMAX_TLP_M3HDW_T_64                             ( 0x01 << DMAX_TLP_M3HDW_POS )
#define DMAX_TLP_M3HDW_T_128                            ( 0x02 << DMAX_TLP_M3HDW_POS )
#define DMAX_TLP_M3HDW_T_256                            ( 0x03 << DMAX_TLP_M3HDW_POS )

#define DMAX_TLP_M2HDW_POS                              (19U)
#define DMAX_TLP_M2HDW_MASK                             (0x2UL << DMAX_TLP_M2HDW_POS)
#define DMAX_TLP_M2HDW                                  DMAX_TLP_M2HDW_MASK
#define DMAX_TLP_M2HDW_T_32                             ( 0x00 << DMAX_TLP_M2HDW_POS )
#define DMAX_TLP_M2HDW_T_64                             ( 0x01 << DMAX_TLP_M2HDW_POS )
#define DMAX_TLP_M2HDW_T_128                            ( 0x02 << DMAX_TLP_M2HDW_POS )
#define DMAX_TLP_M2HDW_T_256                            ( 0x03 << DMAX_TLP_M2HDW_POS )

#define DMAX_TLP_M1HDW_POS                              (21U)
#define DMAX_TLP_M1HDW_MASK                             (0x2UL << DMAX_TLP_M1HDW_POS)
#define DMAX_TLP_M1HDW                                  DMAX_TLP_M1HDW_MASK
#define DMAX_TLP_M1HDW_T_32                             ( 0x00 << DMAX_TLP_M1HDW_POS )
#define DMAX_TLP_M1HDW_T_64                             ( 0x01 << DMAX_TLP_M1HDW_POS )
#define DMAX_TLP_M1HDW_T_128                            ( 0x02 << DMAX_TLP_M1HDW_POS )
#define DMAX_TLP_M1HDW_T_256                            ( 0x03 << DMAX_TLP_M1HDW_POS )

#define DMAX_HS_INT_NUM_POS                             (23U)
#define DMAX_HS_INT_NUM_MASK                            (0x1FUL << DMAX_HS_INT_NUM_POS)
#define DMAX_HS_INT_NUM                                 DMAX_HS_INT_NUM_MASK
#define DMAX_AEP_POS                                    (28U)           /* !< add_encoded_params */
#define DMAX_AEP_MASK                                   (0x1UL << DMAX_AEP_POS)
#define DMAX_AEP                                        DMAX_AEP_MASK
#define DMAX_SES_POS                                    (29U)           /* !< static_endian_select */
#define DMAX_SES_MASK                                   (0x1UL << DMAX_SES_POS)
#define DMAX_SES                                        DMAX_SES_MASK


/* value type ----------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_DMA_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

