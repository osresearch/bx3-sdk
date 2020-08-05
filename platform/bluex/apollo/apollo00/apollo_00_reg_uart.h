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
#ifndef __APOLLO_00_REG_UART_H__
#define __APOLLO_00_REG_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/
typedef struct {
    __IO uint32_t RTD;                  /* !< union type. Receive buffer,Transmit holding,Divisor latch low 0x0000 */
    __IO uint32_t DI;                   /* !< union type. Divisor latch high,Interrupt enable               0x0004 */
    __IO uint32_t IF;                   /* !< union type. Interrupt Identity,FIFO Control                   0x0008 */
    __IO uint32_t LC;                   /* !< Line Control                                                  0x000C */
    __IO uint32_t MC;                   /* !< Modem Control                                                 0x0010 */
    __I  uint32_t LS;                   /* !< Line Status                                                   0x0014 */
    __IO uint32_t MS;                   /* !< Modem Status                                                  0x0018 */
    __IO uint32_t SCRA;                 /* !< Scratchpad. use as a temporary storage space.                 0x001C */
    __IO uint32_t LPDLL;                /* !< Low Power Divisor Latch (Low)                                 0x0020 */
    __IO uint32_t LPDLH;                /* !< Low Power Divisor Latch (High)                                0x0024 */
         uint32_t reserved0[2];         /* !< wait description                                              0x0028 */
    __IO uint32_t SRT0;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0030 */
    __IO uint32_t SRT1;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0034 */
    __IO uint32_t SRT2;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0038 */
    __IO uint32_t SRT3;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x003C */
    __IO uint32_t SRT4;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0040 */
    __IO uint32_t SRT5;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0044 */
    __IO uint32_t SRT6;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0048 */
    __IO uint32_t SRT7;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x004C */
    __IO uint32_t SRT8;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0050 */
    __IO uint32_t SRT9;                 /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0054 */
    __IO uint32_t SRT10;                /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0058 */
    __IO uint32_t SRT11;                /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x005C */
    __IO uint32_t SRT12;                /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0060 */
    __IO uint32_t SRT13;                /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0064 */
    __IO uint32_t SRT14;                /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x0068 */
    __IO uint32_t SRT15;                /* !< union type. Shadow Receive Buffer,Shadow Transmit Holding     0x006C */
    __I  uint32_t FA;                   /* !< FIFO Access                                                   0x0070 */
    __I  uint32_t TFR;                  /* !< Transmit FIFO Read                                            0x0074 */
    __O  uint32_t RFW;                  /* !< Receive FIFO Write                                            0x0078 */
    __I  uint32_t US;                   /* !< UART Status                                                   0x007C */
    __I  uint32_t TFL;                  /* !< Transmit FIFO Level                                           0x0080 */
    __I  uint32_t RFL;                  /* !< Receive FIFO Level                                            0x0084 */
    __O  uint32_t SR;                   /* !< Software Reset                                                0x0088 */
         uint32_t reserved1[6];         /* !< wait description                                              0x008C */
    __IO uint32_t HTX;                  /* !< Halt TX                                                       0x00A4 */
    __O  uint32_t DMASA;                /* !< DMA Software Acknowledge                                      0x00A8 */
         uint32_t reserved2[18];        /* !< wait description                                              0x00AC */
    __I  uint32_t CP;                   /* !< Component Parameter                                           0x00F4 */
    __I  uint32_t VER;                  /* !< UART Component Version                                        0x00F8 */
    __I  uint32_t CT;                   /* !< Component Type                                                0x00FC */
} reg_uart_t;

/* bit definition ------------------------------------------------------------*/

/*****************  Bit definition for UART_RB register  ********************/
#define UART_RTD_RB_VAL_POS                             (0U)
#define UART_RTD_RB_VAL_MASK                            (0x1FFUL << UART_RTD_RB_VAL_POS)
#define UART_RTD_RB_VAL                                 UART_RTD_RB_VAL_MASK

/*****************  Bit definition for UART_TD register  ********************/
#define UART_RTD_TH_VAL_POS                             (0U)
#define UART_RTD_TH_VAL_MASK                            (0x1FFUL << UART_RTD_TH_VAL_POS)
#define UART_RTD_TH_VAL                                 UART_RTD_TH_VAL_MASK

/*****************  Bit definition for UART_DLL register  *******************/
#define UART_RTD_DLL_VAL_POS                            (0U)
#define UART_RTD_DLL_VAL_MASK                           (0xFFUL << UART_RTD_DLL_VAL_POS)
#define UART_RTD_DLL_VAL                                UART_RTD_DLL_VAL_MASK

/*****************  Bit definition for UART_DLH register  *******************/
#define UART_DI_DLH_VAL_POS                             (0U)
#define UART_DI_DLH_VAL_MASK                            (0xFFUL << UART_DI_DLH_VAL_POS)
#define UART_DI_DLH_VAL                                 UART_DI_DLH_VAL_MASK

/*****************  Bit definition for UART_IE register  ********************/
#define UART_DI_IE_RDA_AND_IDLE_POS                     (0U)
#define UART_DI_IE_RDA_AND_IDLE_MASK                    (0x1UL << UART_DI_IE_RDA_AND_IDLE_POS)
#define UART_DI_IE_RDA_AND_IDLE                         UART_DI_IE_RDA_AND_IDLE_MASK
#define UART_DI_IE_TX_EMPTY_POS                         (1U)
#define UART_DI_IE_TX_EMPTY_MASK                        (0x1UL << UART_DI_IE_TX_EMPTY_POS)
#define UART_DI_IE_TX_EMPTY                             UART_DI_IE_TX_EMPTY_MASK
#define UART_DI_IE_RX_LINE_STA_POS                      (2U)
#define UART_DI_IE_RX_LINE_STA_MASK                     (0x1UL << UART_DI_IE_RX_LINE_STA_POS)
#define UART_DI_IE_RX_LINE_STA                          UART_DI_IE_RX_LINE_STA_MASK
#define UART_DI_IE_MDM_STA_POS                          (3U)
#define UART_DI_IE_MDM_STA_MASK                         (0x1UL << UART_DI_IE_MDM_STA_POS)
#define UART_DI_IE_MDM_STA                              UART_DI_IE_MDM_STA_MASK
#define UART_DI_IE_THRE_POS                             (7U)
#define UART_DI_IE_THRE_MASK                            (0x1UL << UART_DI_IE_THRE_POS)
#define UART_DI_IE_THRE                                 UART_DI_IE_THRE_MASK

/*****************  Bit definition for UART_II register  ********************/
#define UART_IF_II_VAL_POS                              (0U)
#define UART_IF_II_VAL_MASK                             (0xFUL << UART_IF_II_VAL_POS)
#define UART_IF_II_VAL                                  UART_IF_II_VAL_MASK
#define UART_IF_II_FIFOS_EN_POS                         (6U)
#define UART_IF_II_FIFOS_EN_MASK                        (0x3UL << UART_IF_II_FIFOS_EN_POS)
#define UART_IF_II_FIFOS_EN                             UART_IF_II_FIFOS_EN_MASK


/*****************  Bit definition for UART_FIFO register  ********************/
#define UART_IF_FIFO_EN_POS                             (0U)
#define UART_IF_FIFO_EN_MASK                            (0x1UL << UART_IF_FIFO_EN_POS)
#define UART_IF_FIFO_EN                                 UART_IF_FIFO_EN_MASK

#define UART_IF_FIFO_RST_POS                            (1U)
#define UART_IF_FIFO_RST_MASK                           (0x1UL << UART_IF_FIFO_RST_POS)
#define UART_IF_FIFO_RST                                UART_IF_FIFO_RST_MASK

#define UART_IF_FIFO_TX_RST_POS                         (2U)
#define UART_IF_FIFO_TX_RST_MASK                        (0x1UL << UART_IF_FIFO_TX_RST_POS)
#define UART_IF_FIFO_TX_RST                             UART_IF_FIFO_TX_RST_MASK
#define UART_IF_FIFO_DMA_MODE_POS                       (3U)
#define UART_IF_FIFO_DMA_MODE_MASK                      (0x1UL << UART_IF_FIFO_DMA_MODE_POS)
#define UART_IF_FIFO_DMA_MODE                           UART_IF_FIFO_DMA_MODE_MASK
#define UART_IF_FIFO_TXET_POS                           (4U)
#define UART_IF_FIFO_TXET_MASK                          (0x3UL << UART_IF_FIFO_TXET_POS)
#define UART_IF_FIFO_TXET                               UART_IF_FIFO_TXET_MASK
#define UART_IF_FIFO_RXT_POS                            (6U)
#define UART_IF_FIFO_RXT_MASK                           (0x3UL << UART_IF_FIFO_RXT_POS)
#define UART_IF_FIFO_RXT                                UART_IF_FIFO_RXT_MASK

/*****************  Bit definition for UART_LC register  ********************/
#define UART_LC_DATA_WIDTH_POS                          (0U)
#define UART_LC_DATA_WIDTH_MASK                         (0x3UL << UART_LC_DATA_WIDTH_POS)
#define UART_LC_DATA_WIDTH                              UART_LC_DATA_WIDTH_MASK
#define UART_LC_STOP_BIT_POS                            (2U)
#define UART_LC_STOP_BIT_MASK                           (0x1UL << UART_LC_STOP_BIT_POS)
#define UART_LC_STOP_BIT                                UART_LC_STOP_BIT_MASK
#define UART_LC_PARITY_EN_POS                           (3U)
#define UART_LC_PARITY_EN_MASK                          (0x1UL << UART_LC_PARITY_EN_POS)
#define UART_LC_PARITY_EN                               UART_LC_PARITY_EN_MASK
#define UART_LC_EVEN_PARITY_EN_POS                      (4U)
#define UART_LC_EVEN_PARITY_EN_MASK                     (0x1UL << UART_LC_EVEN_PARITY_EN_POS)
#define UART_LC_EVEN_PARITY_EN                          UART_LC_EVEN_PARITY_EN_MASK
#define UART_LC_STICK_PARITY_EN_POS                     (5U)
#define UART_LC_STICK_PARITY_EN_MASK                    (0x1UL << UART_LC_STICK_PARITY_EN_POS)
#define UART_LC_STICK_PARITY_EN                         UART_LC_STICK_PARITY_EN_MASK
#define UART_LC_BREAK_POS                               (6U)
#define UART_LC_BREAK_MASK                              (0x1UL << UART_LC_BREAK_POS)
#define UART_LC_BREAK                                   UART_LC_BREAK_MASK
#define UART_LC_DLAB_POS                                (7U)
#define UART_LC_DLAB_MASK                               (0x1UL << UART_LC_DLAB_POS)
#define UART_LC_DLAB                                    UART_LC_DLAB_MASK

/*****************  Bit definition for UART_MC register  ********************/
#define UART_MC_DTR_POS                                 (0U)
#define UART_MC_DTR_MASK                                (0x1UL << UART_MC_DTR_POS)
#define UART_MC_DTR                                     UART_MC_DTR_MASK
#define UART_MC_RTS_POS                                 (1U)
#define UART_MC_RTS_MASK                                (0x1UL << UART_MC_RTS_POS)
#define UART_MC_RTS                                     UART_MC_RTS_MASK
#define UART_MC_OUT1_POS                                (2U)
#define UART_MC_OUT1_MASK                               (0x1UL << UART_MC_OUT1_POS)
#define UART_MC_OUT1                                    UART_MC_OUT1_MASK
#define UART_MC_OUT2_POS                                (3U)
#define UART_MC_OUT2_MASK                               (0x1UL << UART_MC_OUT2_POS)
#define UART_MC_OUT2                                    UART_MC_OUT2_MASK
#define UART_MC_LOOPBACK_POS                            (4U)
#define UART_MC_LOOPBACK_MASK                           (0x1UL << UART_MC_LOOPBACK_POS)
#define UART_MC_LOOPBACK                                UART_MC_LOOPBACK_MASK
#define UART_MC_AUTO_FLOW_CTRL_EN_POS                   (5U)
#define UART_MC_AUTO_FLOW_CTRL_EN_MASK                  (0x1UL << UART_MC_AUTO_FLOW_CTRL_EN_POS)
#define UART_MC_AUTO_FLOW_CTRL_EN                       UART_MC_AUTO_FLOW_CTRL_EN_MASK
#define UART_MC_SIR_MODE_EN_POS                         (6U)
#define UART_MC_SIR_MODE_EN_MASK                        (0x1UL << UART_MC_SIR_MODE_EN_POS)
#define UART_MC_SIR_MODE_EN                             UART_MC_SIR_MODE_EN_MASK

/*****************  Bit definition for UART_LS register  ********************/
#define UART_LS_DATA_READY_POS                          (0U)
#define UART_LS_DATA_READY_MASK                         (0x1UL << UART_LS_DATA_READY_POS)
#define UART_LS_DATA_READY                              UART_LS_DATA_READY_MASK
#define UART_LS_OVERRUN_ERR_POS                         (1U)
#define UART_LS_OVERRUN_ERR_MASK                        (0x1UL << UART_LS_OVERRUN_ERR_POS)
#define UART_LS_OVERRUN_ERR                             UART_LS_OVERRUN_ERR_MASK
#define UART_LS_PARITY_ERR_POS                          (2U)
#define UART_LS_PARITY_ERR_MASK                         (0x1UL << UART_LS_PARITY_ERR_POS)
#define UART_LS_PARITY_ERR                              UART_LS_PARITY_ERR_MASK
#define UART_LS_FRAME_ERR_POS                           (3U)
#define UART_LS_FRAME_ERR_MASK                          (0x1UL << UART_LS_FRAME_ERR_POS)
#define UART_LS_FRAME_ERR                               UART_LS_FRAME_ERR_MASK
#define UART_LS_BREAD_INT_POS                           (4U)
#define UART_LS_BREAD_INT_MASK                          (0x1UL << UART_LS_BREAD_INT_POS)
#define UART_LS_BREAD_INT                               UART_LS_BREAD_INT_MASK
#define UART_LS_TH_EMPTY_POS                            (5U)
#define UART_LS_TH_EMPTY_MASK                           (0x1UL << UART_LS_TH_EMPTY_POS)
#define UART_LS_TH_EMPTY                                UART_LS_TH_EMPTY_MASK
#define UART_LS_TX_EMPTY_POS                            (6U)
#define UART_LS_TX_EMPTY_MASK                           (0x1UL << UART_LS_TX_EMPTY_POS)
#define UART_LS_TX_EMPTY                                UART_LS_TX_EMPTY_MASK
#define UART_LS_RX_FIFO_ERR_POS                         (7U)
#define UART_LS_RX_FIFO_ERR_MASK                        (0x1UL << UART_LS_RX_FIFO_ERR_POS)
#define UART_LS_RX_FIFO_ERR                             UART_LS_RX_FIFO_ERR_MASK
#define UART_LS_RX_IS_ADDR_POS                          (8U)
#define UART_LS_RX_IS_ADDR_MASK                         (0x1UL << UART_LS_RX_IS_ADDR_POS)
#define UART_LS_RX_IS_ADDR                              UART_LS_RX_IS_ADDR_MASK

/*****************  Bit definition for UART_MS register  ********************/
#define UART_MS_DCTS_POS                                (0U)
#define UART_MS_DCTS_MASK                               (0x1UL << UART_MS_DCTS_POS)
#define UART_MS_DCTS                                    UART_MS_DCTS_MASK
#define UART_MS_DDSR_POS                                (1U)
#define UART_MS_DDSR_MASK                               (0x1UL << UART_MS_DDSR_POS)
#define UART_MS_DDSR                                    UART_MS_DDSR_MASK
#define UART_MS_TERI_POS                                (2U)
#define UART_MS_TERI_MASK                               (0x1UL << UART_MS_TERI_POS)
#define UART_MS_TERI                                    UART_MS_TERI_MASK
#define UART_MS_DDCD_POS                                (3U)
#define UART_MS_DDCD_MASK                               (0x1UL << UART_MS_DDCD_POS)
#define UART_MS_DDCD                                    UART_MS_DDCD_MASK
#define UART_MS_CTS_POS                                 (4U)
#define UART_MS_CTS_MASK                                (0x1UL << UART_MS_CTS_POS)
#define UART_MS_CTS                                     UART_MS_CTS_MASK
#define UART_MS_DSR_POS                                 (5U)
#define UART_MS_DSR_MASK                                (0x1UL << UART_MS_DSR_POS)
#define UART_MS_DSR                                     UART_MS_DSR_MASK
#define UART_MS_RI_POS                                  (6U)
#define UART_MS_RI_MASK                                 (0x1UL << UART_MS_RI_POS)
#define UART_MS_RI                                      UART_MS_RI_MASK
#define UART_MS_DCD_POS                                 (7U)
#define UART_MS_DCD_MASK                                (0x1UL << UART_MS_DCD_POS)
#define UART_MS_DCD                                     UART_MS_DCD_MASK

/*****************  Bit definition for UART_SCRA register  ********************/
#define UART_SCRA_VAL_POS                               (0U)
#define UART_SCRA_VAL_MASK                              (0xFFUL << UART_SCRA_VAL_POS)
#define UART_SCRA_VAL                                   UART_SCRA_VAL_MASK

/*****************  Bit definition for UART_LPDLL register  ********************/
#define UART_LPDLL_VAL_POS                              (0U)
#define UART_LPDLL_VAL_MASK                             (0xFFUL << UART_LPDLL_VAL_POS)
#define UART_LPDLL_VAL                                  UART_LPDLL_VAL_MASK

/*****************  Bit definition for UART_LPDLH register  ********************/
#define UART_LPDLH_VAL_POS                              (0U)
#define UART_LPDLH_VAL_MASK                             (0xFFUL << UART_LPDLH_VAL_POS)
#define UART_LPDLH_VAL                                  UART_LPDLH_VAL_MASK

/*****************  Bit definition for UART_FA register  ********************/
#define UART_FA_EN_POS                                  (0U)
#define UART_FA_EN_MASK                                 (0x1UL << UART_FA_EN_POS)
#define UART_FA_EN                                      UART_FA_EN_MASK

/*****************  Bit definition for UART_TFR register  ********************/
#define UART_TFR_VAL_POS                                (0U)
#define UART_TFR_VAL_MASK                               (0xFFUL << UART_TFR_VAL_POS)
#define UART_TFR_VAL                                    UART_TFR_VAL_MASK

/*****************  Bit definition for UART_RFW register  ********************/
#define UART_RFW_DATA_POS                               (0U)
#define UART_RFW_DATA_MASK                              (0xFFUL << UART_RFW_DATA_POS)
#define UART_RFW_DATA                                   UART_RFW_DATA_MASK
#define UART_RFW_PARITY_ERR_POS                         (8U)
#define UART_RFW_PARITY_ERR_MASK                        (0x1UL << UART_RFW_PARITY_ERR_POS)
#define UART_RFW_PARITY_ERR                             UART_RFW_PARITY_ERR_MASK
#define UART_RFW_FRAME_ERR_POS                          (8U)
#define UART_RFW_FRAME_ERR_MASK                         (0x1UL << UART_RFW_FRAME_ERR_POS)
#define UART_RFW_FRAME_ERR                              UART_RFW_FRAME_ERR_MASK

/*****************  Bit definition for UART_RFW register  ********************/
#define UART_US_BUSY_POS                                (0U)
#define UART_US_BUSY_MASK                               (0x1UL << UART_US_BUSY_POS)
#define UART_US_BUSY                                    UART_US_BUSY_MASK
#define UART_US_TX_FIFO_NOT_FULL_POS                    (1U)
#define UART_US_TX_FIFO_NOT_FULL_MASK                   (0x1UL << UART_US_TX_FIFO_NOT_FULL_POS)
#define UART_US_TX_FIFO_NOT_FULL                        UART_US_TX_FIFO_NOT_FULL_MASK
#define UART_US_TX_FIFO_EMPTY_POS                       (2U)
#define UART_US_TX_FIFO_EMPTY_MASK                      (0x1UL << UART_US_TX_FIFO_EMPTY_POS)
#define UART_US_TX_FIFO_EMPTY                           UART_US_TX_FIFO_EMPTY_MASK
#define UART_US_RX_FIFO_NOT_EMPTY_POS                   (3U)
#define UART_US_RX_FIFO_NOT_EMPTY_MASK                  (0x1UL << UART_US_RX_FIFO_NOT_EMPTY_POS)
#define UART_US_RX_FIFO_NOT_EMPTY                       UART_US_RX_FIFO_NOT_EMPTY_MASK
#define UART_US_RX_FIFO_FULL_POS                        (4U)
#define UART_US_RX_FIFO_FULL_MASK                       (0x1UL << UART_US_RX_FIFO_FULL_POS)
#define UART_US_RX_FIFO_FULL                            UART_US_RX_FIFO_FULL_MASK

/*****************  Bit definition for UART_TFL register  ********************/
#define UART_TFL_VAL_POS                                (0U)
#define UART_TFL_VAL_MASK                               (0xFFFFUL << UART_TFL_VAL_POS)
#define UART_TFL_VAL                                    UART_TFL_VAL_MASK

/*****************  Bit definition for UART_RFL register  ********************/
#define UART_RFL_VAL_POS                                (0U)
#define UART_RFL_VAL_MASK                               (0xFFFFUL << UART_RFL_VAL_POS)
#define UART_RFL_VAL                                    UART_RFL_VAL_MASK

/*****************  Bit definition for UART_SR register  ********************/
#define UART_SR_UART_RST_POS                            (0U)
#define UART_SR_UART_RST_MASK                           (0x1UL << UART_SR_UART_RST_POS)
#define UART_SR_UART_RST                                UART_SR_UART_RST_MASK
#define UART_SR_RX_FIFO_RST_SHAD_POS                    (1U)
#define UART_SR_RX_FIFO_RST_SHAD_MASK                   (0x1UL << UART_SR_RX_FIFO_RST_SHAD_POS)
#define UART_SR_RX_FIFO_RST_SHAD                        UART_SR_RX_FIFO_RST_SHAD_MASK
#define UART_SR_TX_FIFO_RST_SHAD_POS                    (2U)
#define UART_SR_TX_FIFO_RST_SHAD_MASK                   (0x1UL << UART_SR_TX_FIFO_RST_SHAD_POS)
#define UART_SR_TX_FIFO_RST_SHAD                        UART_SR_TX_FIFO_RST_SHAD_MASK

/*****************  Bit definition for UART_HTX register  ********************/
#define UART_HTX_EN_POS                                 (0U)
#define UART_HTX_EN_MASK                                (0x1UL << UART_HTX_EN_POS)
#define UART_HTX_EN                                     UART_HTX_EN_MASK

/*****************  Bit definition for UART_DMASA register  ********************/
#define UART_DMASA_BIT_POS                              (0U)
#define UART_DMASA_BIT_MASK                             (0x1UL << UART_DMASA_BIT_POS)
#define UART_DMASA_BIT                                  UART_DMASA_BIT_MASK

/*****************  Bit definition for UART_CP register  ********************/
#define UART_CP_DATA_WIDTH_POS                          (0U)
#define UART_CP_DATA_WIDTH_MASK                         (0x3UL << UART_CP_DATA_WIDTH_POS)
#define UART_CP_DATA_WIDTH                              UART_CP_DATA_WIDTH_MASK
#define UART_CP_AFCE_MODE_POS                           (4U)
#define UART_CP_AFCE_MODE_MASK                          (0x1UL << UART_CP_AFCE_MODE_POS)
#define UART_CP_AFCE_MODE                               UART_CP_AFCE_MODE_MASK
#define UART_CP_THRE_MODE_POS                           (5U)
#define UART_CP_THRE_MODE_MASK                          (0x1UL << UART_CP_THRE_MODE_POS)
#define UART_CP_THRE_MODE                               UART_CP_THRE_MODE_MASK
#define UART_CP_SIR_MODE_POS                            (6U)
#define UART_CP_SIR_MODE_MASK                           (0x1UL << UART_CP_SIR_MODE_POS)
#define UART_CP_SIR_MODE                                UART_CP_SIR_MODE_MASK
#define UART_CP_SIR_LP_MODE_POS                         (7U)
#define UART_CP_SIR_LP_MODE_MASK                        (0x1UL << UART_CP_SIR_LP_MODE_POS)
#define UART_CP_SIR_LP_MODE                             UART_CP_SIR_LP_MODE_MASK
#define UART_CP_NEW_FEAT_POS                            (8U)
#define UART_CP_NEW_FEAT_MASK                           (0x1UL << UART_CP_NEW_FEAT_POS)
#define UART_CP_NEW_FEAT                                UART_CP_NEW_FEAT_MASK
#define UART_CP_FIFO_ACCESS_POS                         (9U)
#define UART_CP_FIFO_ACCESS_MASK                        (0x1UL << UART_CP_FIFO_ACCESS_POS)
#define UART_CP_FIFO_ACCESS                             UART_CP_FIFO_ACCESS_MASK
#define UART_CP_FIFO_STA_POS                            (10U)
#define UART_CP_FIFO_STA_MASK                           (0x1UL << UART_CP_FIFO_STA_POS)
#define UART_CP_FIFO_STA                                UART_CP_FIFO_STA_MASK
#define UART_CP_SHADOW_POS                              (11U)
#define UART_CP_SHADOW_MASK                             (0x1UL << UART_CP_SHADOW_POS)
#define UART_CP_SHADOW                                  UART_CP_SHADOW_MASK
#define UART_CP_UART_ADD_ENCODE_PARA_POS                (12U)
#define UART_CP_UART_ADD_ENCODE_PARA_MASK               (0x1UL << UART_CP_UART_ADD_ENCODE_PARA_POS)
#define UART_CP_UART_ADD_ENCODE_PARA                    UART_CP_UART_ADD_ENCODE_PARA_MASK
#define UART_CP_DMA_EXTRA_POS                           (13U)
#define UART_CP_DMA_EXTRA_MASK                          (0x1UL << UART_CP_DMA_EXTRA_POS)
#define UART_CP_DMA_EXTRA                               UART_CP_DMA_EXTRA_MASK
#define UART_CP_FIFO_MODE_POS                           (16U)
#define UART_CP_FIFO_MODE_MASK                          (0xFFUL << UART_CP_FIFO_MODE_POS)
#define UART_CP_FIFO_MODE                               UART_CP_FIFO_MODE_MASK

/* value type ----------------------------------------------------------------*/
//#define UART_LCR_RESET_VALUE                            (0U)
//#define UART_LCR_DATA_WIDTH_POS                         (0U)
//#define UART_LCR_DATAWIDTH_5B                           ((uint32_t)0X00000001U << UART_LCR_DATA_WIDTH_POS )
//#define UART_LCR_DATAWIDTH_6B                           ((uint32_t)0X00000001U << UART_LCR_DATA_WIDTH_POS )
//#define UART_LCR_DATAWIDTH_7B                           ((uint32_t)0X00000002U << UART_LCR_DATA_WIDTH_POS )
//#define UART_LCR_DATAWIDTH_8B                           ((uint32_t)0X00000003U << UART_LCR_DATA_WIDTH_POS )

//#define UART_LCR_STOP_BIT_POS                           (2U)
//#define UART_LCR_STOPBIT_1                              ((uint32_t)0X00000000U << UART_LCR_STOP_BIT_POS )
//#define UART_LCR_STOPBIT_1_5_or_2                       ((uint32_t)0X00000001U << UART_LCR_STOP_BIT_POS )

//#define UART_LCR_PARITY_EN_POS                          (3U)
//#define UART_LCR_PARITY_EN                              ((uint32_t)0X00000001U << UART_LCR_PARITY_EN_POS )

//#define UART_LCR_PARITY_TYPE_POS                        (4U)
//#define UART_LCR_PARITY_EVEN                            ((uint32_t)0X00000001U << UART_LCR_PARITY_TYPE_POS )

#define UART_LC_DATA_WIDTH_T_5B                         ((uint32_t)0X00000000U << UART_LC_DATA_WIDTH_POS )
#define UART_LC_DATA_WIDTH_T_6B                         ((uint32_t)0X00000001U << UART_LC_DATA_WIDTH_POS )
#define UART_LC_DATA_WIDTH_T_7B                         ((uint32_t)0X00000002U << UART_LC_DATA_WIDTH_POS )
#define UART_LC_DATA_WIDTH_T_8B                         ((uint32_t)0X00000003U << UART_LC_DATA_WIDTH_POS )


/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_UART_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

