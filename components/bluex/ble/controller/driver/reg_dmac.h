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
#ifndef __REG_DMAC_H__
#define __REG_DMAC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

typedef struct dw_dmac_portmap {

  /* Channel registers                                    */
  /* The offset address for each of the channel registers */
  /*  is shown for channel 0. For other channel numbers   */
  /*  use the following equation.                         */
  /*                                                      */
  /*    offset = (channel_num * 0x058) + channel_0 offset */
  /*                                                      */
  struct {
      volatile uint32_t sar_l;     /* Source Address Reg      (0x000) */
      volatile uint32_t sar_h;
      volatile uint32_t dar_l;     /* Destination Address Reg (0x008) */
      volatile uint32_t dar_h;
      volatile uint32_t llp_l;     /* Linked List Pointer Reg (0x010) */
      volatile uint32_t llp_h;
      volatile uint32_t ctl_l;     /* Control Reg             (0x018) */
      volatile uint32_t ctl_h;
      volatile uint32_t sstat_l;   /* Source Status Reg       (0x020) */
      volatile uint32_t sstat_h;
      volatile uint32_t dstat_l;   /* Destination Status Reg  (0x028) */
      volatile uint32_t dstat_h;
      volatile uint32_t sstatar_l; /* Source Status Addr Reg  (0x030) */
      volatile uint32_t sstatar_h;
      volatile uint32_t dstatar_l; /* Dest Status Addr Reg    (0x038) */
      volatile uint32_t dstatar_h;
      volatile uint32_t cfg_l;     /* Configuration Reg       (0x040) */
      volatile uint32_t cfg_h;
      volatile uint32_t sgr_l;     /* Source Gather Reg       (0x048) */
      volatile uint32_t sgr_h;
      volatile uint32_t dsr_l;     /* Destination Scatter Reg (0x050) */
      volatile uint32_t dsr_h;
  } ch[8];

  /* Interrupt Raw Status Registers */
  volatile uint32_t raw_tfr_l;     /* Raw Status for IntTfr   (0x2c0) */
  volatile uint32_t raw_tfr_h;
  volatile uint32_t raw_block_l;   /* Raw Status for IntBlock (0x2c8) */
  volatile uint32_t raw_block_h;
  volatile uint32_t raw_srctran_l; /* Raw Status IntSrcTran   (0x2d0) */
  volatile uint32_t raw_srctran_h;
  volatile uint32_t raw_dsttran_l; /* Raw Status IntDstTran   (0x2d8) */
  volatile uint32_t raw_dsttran_h;
  volatile uint32_t raw_err_l;     /* Raw Status for IntErr   (0x2e0) */
  volatile uint32_t raw_err_h;

  /* Interrupt Status Registers */
  volatile uint32_t status_tfr_l;    /* Status for IntTfr     (0x2e8) */
  volatile uint32_t status_tfr_h;
  volatile uint32_t status_block_l;  /* Status for IntBlock   (0x2f0) */
  volatile uint32_t status_block_h;
  volatile uint32_t status_srctran_l;/* Status for IntSrcTran (0x2f8) */
  volatile uint32_t status_srctran_h;
  volatile uint32_t status_dsttran_l;/* Status for IntDstTran (0x300) */
  volatile uint32_t status_dsttran_h;
  volatile uint32_t status_err_l;    /* Status for IntErr     (0x308) */
  volatile uint32_t status_err_h;

  /* Interrupt Mask Registers */
  volatile uint32_t mask_tfr_l;      /* Mask for IntTfr       (0x310) */
  volatile uint32_t mask_tfr_h;
  volatile uint32_t mask_block_l;    /* Mask for IntBlock     (0x318) */
  volatile uint32_t mask_block_h;
  volatile uint32_t mask_srctran_l;  /* Mask for IntSrcTran   (0x320) */
  volatile uint32_t mask_srctran_h;
  volatile uint32_t mask_dsttran_l;  /* Mask for IntDstTran   (0x328) */
  volatile uint32_t mask_dsttran_h;
  volatile uint32_t mask_err_l;      /* Mask for IntErr       (0x330) */
  volatile uint32_t mask_err_h;

  /* Interrupt Clear Registers */
  volatile uint32_t clear_tfr_l;     /* Clear for IntTfr      (0x338) */
  volatile uint32_t clear_tfr_h;
  volatile uint32_t clear_block_l;   /* Clear for IntBlock    (0x340) */
  volatile uint32_t clear_block_h;
  volatile uint32_t clear_srctran_l; /* Clear for IntSrcTran  (0x348) */
  volatile uint32_t clear_srctran_h;
  volatile uint32_t clear_dsttran_l; /* Clear for IntDstTran  (0x350) */
  volatile uint32_t clear_dsttran_h;
  volatile uint32_t clear_err_l;     /* Clear for IntErr      (0x358) */
  volatile uint32_t clear_err_h;
  volatile uint32_t status_int_l;    /* Combined Intr Status  (0x360) */
  volatile uint32_t status_int_h;

  /* Software Handshaking Registers */
  volatile uint32_t req_src_reg_l; /* Src Sw Transaction Req  (0x368) */
  volatile uint32_t req_src_reg_h;
  volatile uint32_t req_dst_reg_l; /* Dest Sw Transaction Req (0x370) */
  volatile uint32_t req_dst_reg_h;
  volatile uint32_t sgl_rq_src_reg_l; /* Sgl Src Transac Req  (0x378) */
  volatile uint32_t sgl_rq_src_reg_h;
  volatile uint32_t sgl_rq_dst_reg_l; /* Sgl Dest Transac Req (0x380) */
  volatile uint32_t sgl_rq_dst_reg_h;
  volatile uint32_t lst_src_reg_l;   /* Last Src Transac Req  (0x388) */
  volatile uint32_t lst_src_reg_h;
  volatile uint32_t lst_dst_reg_l;   /* Last Dest Transac Req (0x390) */
  volatile uint32_t lst_dst_reg_h;

  /* Misc Registers */
  volatile uint32_t dma_cfg_reg_l; /* Configuration Register  (0x398) */
  volatile uint32_t dma_cfg_reg_h;
  volatile uint32_t ch_en_reg_l;   /* Channel Enable Register (0x3a0) */
  volatile uint32_t ch_en_reg_h;
  volatile uint32_t dma_id_reg_l;    /* ID Register           (0x3a8) */
  volatile uint32_t dma_id_reg_h;
  volatile uint32_t dma_test_reg_l;  /* Test Register         (0x3b0) */
  volatile uint32_t dma_test_reg_h;
  volatile uint32_t old_version_id_l;/* legacy support        (0x3b8) */
  volatile uint32_t old_version_id_h;
  volatile uint32_t reserved_low;    /* reserved              (0x3c0) */
  volatile uint32_t reserved_high;
  volatile uint32_t dma_comp_params_6_l;/* hardware params    (0x3c8) */
  volatile uint32_t dma_comp_params_6_h;
  volatile uint32_t dma_comp_params_5_l;/* hardware params    (0x3d0) */
  volatile uint32_t dma_comp_params_5_h;
  volatile uint32_t dma_comp_params_4_l;/* hardware params    (0x3d8) */
  volatile uint32_t dma_comp_params_4_h;
  volatile uint32_t dma_comp_params_3_l;/* hardware params    (0x3e0) */
  volatile uint32_t dma_comp_params_3_h;
  volatile uint32_t dma_comp_params_2_l;/* hardware params    (0x3e8) */
  volatile uint32_t dma_comp_params_2_h;
  volatile uint32_t dma_comp_params_1_l;/* hardware params    (0x3f0) */
  volatile uint32_t dma_comp_params_1_h;
  volatile uint32_t dma_version_id_l;/* Version ID Register   (0x3f8) */
  volatile uint32_t dma_version_id_h;
}ble_reg_dmac_t;

enum DMAC_CH0_SAR_L_FIELD
{
    DMAC_SAR_MASK = (int)0xffffffffL,
    DMAC_SAR_POS = 0,
};


enum DMAC_CH0_DAR_L_FIELD
{
    DMAC_DAR_MASK = (int)0xffffffffL,
    DMAC_DAR_POS = 0,
};


enum DMAC_CH0_CTRL_L_FIELD
{
    DMAC_LLP_SRC_EN_MASK = 0x10000000,
    DMAC_LLP_SRC_EN_POS = 28,
    DMAC_LLP_DST_EN_MASK = 0x8000000,
    DMAC_LLP_DST_EN_POS = 27,
    DMAC_SMS_MASK = 0x6000000,
    DMAC_SMS_POS = 25,
    DMAC_DMS_MASK = 0x1c00000,
    DMAC_DMS_POS = 22,
    DMAC_TT_FC_MASK = 0x300000,
    DMAC_TT_FC_POS = 20,
    DMAC_DST_SCATTER_EN_MASK = 0x40000,
    DMAC_DST_SCATTER_EN_POS = 18,
    DMAC_SRC_GATHER_EN_MASK = 0x20000,
    DMAC_SRC_GATHER_EN_POS = 17,
    DMAC_SRC_MSIZE_MASK = 0x1c000,
    DMAC_SRC_MSIZE_POS = 14,
    DMAC_DEST_MSIZE_MASK = 0x3800,
    DMAC_DEST_MSIZE_POS = 11,
    DMAC_SINC_MASK = 0x600,
    DMAC_SINC_POS = 9,
    DMAC_DINC_MASK = 0x180,
    DMAC_DINC_POS = 7,
    DMAC_SRC_TR_WIDTH_MASK = 0x70,
    DMAC_SRC_TR_WIDTH_POS = 4,
    DMAC_DST_TR_WIDTH_MASK = 0xe,
    DMAC_DST_TR_WIDTH_POS = 1,
    DMAC_INT_EN_MASK = 0x1,
    DMAC_INT_EN_POS = 0,
};

enum DMAC_CH0_CTRL_H_FIELD
{
    DMAC_DONE_MASK = 0x1000,
    DMAC_DONE_POS = 12,
    DMAC_BLOCK_TS_MASK = 0xfff,
    DMAC_BLOCK_TS_POS = 0,
};

enum DMAC_CH0_CFG_L_FIELD
{
    DMAC_RELOAD_DST_MASK = (int)0x80000000L,
    DMAC_RELOAD_DST_POS = 31,
    DMAC_RELOAD_SRC_MASK = (int)0x40000000L,
    DMAC_RELOAD_SRC_POS = 30,
    DMAC_MAX_ABRST_MASK = 0x3ff00000,
    DMAC_MAX_ABRST_POS = 20,
    DMAC_SRC_HS_POL_MASK = 0x80000,
    DMAC_SRC_HS_POL_POS = 19,
    DMAC_DST_HS_POL_MASK = 0x40000,
    DMAC_DST_HS_POL_POS = 18,
    DMAC_LOCK_B_MASK = 0x20000,
    DMAC_LOCK_B_POS = 17,
    DMAC_LOCK_CH_MASK = 0x10000,
    DMAC_LOCK_CH_POS = 16,
    DMAC_LOCK_B_L_MASK = 0xc000,
    DMAC_LOCK_B_L_POS = 14,
    DMAC_LOCK_CH_L_MASK = 0x3000,
    DMAC_LOCK_CH_L_POS = 12,
    DMAC_HS_SEL_SRC_MASK = 0x800,
    DMAC_HS_SEL_SRC_POS = 11,
    DMAC_HS_SEL_DST_MASK = 0x400,
    DMAC_HS_SEL_DST_POS = 10,
    DMAC_FIFO_EMPTY_MASK = 0x200,
    DMAC_FIFO_EMPTY_POS = 9,
    DMAC_CH_SUSP_MASK = 0x100,
    DMAC_CH_SUSP_POS = 8,
    DMAC_CH_PRIOR_MASK = 0xe0,
    DMAC_CH_PRIOR_POS = 5,
};

enum DMAC_CH0_CFG_H_FIELD
{
    DMAC_DEST_PER_MASK = 0x7800,
    DMAC_DEST_PER_POS = 11,
    DMAC_SRC_PER_MASK = 0x780,
    DMAC_SRC_PER_POS = 7,
    DMAC_SS_UPD_EN_MASK = 0x40,
    DMAC_SS_UPD_EN_POS = 6,
    DMAC_DS_UPD_EN_MASK = 0x20,
    DMAC_DS_UPD_EN_POS = 5,
    DMAC_PROTCTL_MASK = 0x1c,
    DMAC_PROTCTL_POS = 2,
    DMAC_FIFO_MODE_MASK = 0x2,
    DMAC_FIFO_MODE_POS = 1,
    DMAC_FC_MODE_MASK = 0x1,
    DMAC_FC_MODE_POS = 0,
};


enum DMAC_RAW_FIELD
{
    DMAC_RAW_MASK = 0x3f,
    DMAC_RAW_POS = 0,
};


enum DMAC_STATUS_FIELD
{
    DMAC_STATUS_MASK = 0x3f,
    DMAC_STATUS_POS = 0,
};


enum DMAC_MASK_FIELD
{
    DMAC_INT_MASK_WE_MASK = 0x3f00,
    DMAC_INT_MASK_WE_POS = 8,
    DMAC_INT_MASK_MASK = 0x3f,
    DMAC_INT_MASK_POS = 0,
};

enum DMAC_CLEAR_FIELD
{
    DMAC_CLEAR_MASK = 0x3f,
    DMAC_CLEAR_POS = 0,
};


enum DMAC_STATUSINT_L_FIELD
{
    DMAC_ERR_MASK = 0x10,
    DMAC_ERR_POS = 4,
    DMAC_DSTT_MASK = 0x8,
    DMAC_DSTT_POS = 3,
    DMAC_SRCT_MASK = 0x4,
    DMAC_SRCT_POS = 2,
    DMAC_BLOCK_MASK = 0x2,
    DMAC_BLOCK_POS = 1,
    DMAC_TFR_MASK = 0x1,
    DMAC_TFR_POS = 0,
};


enum DMAC_REQSRCREG_L_FIELD
{
    DMAC_SRC_REQ_WE_MASK = 0x3f00,
    DMAC_SRC_REQ_WE_POS = 8,
    DMAC_SRC_REQ_MASK = 0x3f,
    DMAC_SRC_REQ_POS = 0,
};


enum DMAC_REQDSTREG_L_FIELD
{
    DMAC_DST_REQ_WE_MASK = 0x3f00,
    DMAC_DST_REQ_WE_POS = 8,
    DMAC_DST_REQ_MASK = 0x3f,
    DMAC_DST_REQ_POS = 0,
};


enum DMAC_SGLREQSRCREG_L_FIELD
{
    DMAC_SRC_SGLREQ_WE_MASK = 0x3f00,
    DMAC_SRC_SGLREQ_WE_POS = 8,
    DMAC_SRC_SGLREQ_MASK = 0x3f,
    DMAC_SRC_SGLREQ_POS = 0,
};


enum DMAC_SGLREQDSTREG_L_FIELD
{
    DMAC_DST_SGLREQ_WE_MASK = 0x3f00,
    DMAC_DST_SGLREQ_WE_POS = 8,
    DMAC_DST_SGLREQ_MASK = 0x3f,
    DMAC_DST_SGLREQ_POS = 0,
};


enum DMAC_LSTSRCREG_L_FIELD
{
    DMAC_LSTSRC_WE_MASK = 0x3f00,
    DMAC_LSTSRC_WE_POS = 8,
    DMAC_LSTSRC_MASK = 0x3f,
    DMAC_LSTSRC_POS = 0,
};


enum DMAC_LSTDSTREG_L_FIELD
{
    DMAC_LSTDST_WE_MASK = 0x3f00,
    DMAC_LSTDST_WE_POS = 8,
    DMAC_LSTDST_MASK = 0x3f,
    DMAC_LSTDST_POS = 0,
};


enum DMAC_DMACFGREG_L_FIELD
{
    DMAC_DMA_EN_MASK = 0x1,
    DMAC_DMA_EN_POS = 0,
};


enum DMAC_CHENREG_L_FIELD
{
    DMAC_CH_EN_WE_MASK = 0x3f00,
    DMAC_CH_EN_WE_POS = 8,
    DMAC_CH_EN_MASK = 0x3f,
    DMAC_CH_EN_POS = 0,
};


enum DMAC_DMAIDREG_L_FIELD
{
    DMAC_DMAH_ID_NUM_MASK = (int)0xffffffffL,
    DMAC_DMAH_ID_NUM_POS = 0,
};


enum DMAC_DMATESTREG_L_FIELD
{
    DMAC_TEST_SLV_IF_MASK = 0x1,
    DMAC_TEST_SLV_IF_POS = 0,
};





enum DMAC_DMA_COMP_PARAMS_5_H_FIELD
{
    DMAC_CH5_FIFO_DEPTH_MASK = (int)0x70000000L,
    DMAC_CH5_FIFO_DEPTH_POS = 28,
    DMAC_CH5_SMS_MASK = 0xe000000,
    DMAC_CH5_SMS_POS = 25,
    DMAC_CH5_LMS_MASK = 0x1c00000,
    DMAC_CH5_LMS_POS = 22,
    DMAC_CH5_DMS_MASK = 0x380000,
    DMAC_CH5_DMS_POS = 19,
    DMAC_CH5_MAX_MULT_SIZE_MASK = 0x70000,
    DMAC_CH5_MAX_MULT_SIZE_POS = 16,
    DMAC_CH5_FC_MASK = 0xc000,
    DMAC_CH5_FC_POS = 14,
    DMAC_CH5_HC_LLP_MASK = 0x2000,
    DMAC_CH5_HC_LLP_POS = 13,
    DMAC_CH5_CTL_WB_EN_MASK = 0x1000,
    DMAC_CH5_CTL_WB_EN_POS = 12,
    DMAC_CH5_MULTI_BLK_EN_MASK = 0x800,
    DMAC_CH5_MULTI_BLK_EN_POS = 11,
    DMAC_CH5_LOCK_EN_MASK = 0x400,
    DMAC_CH5_LOCK_EN_POS = 10,
    DMAC_CH5_SRC_GAT_EN_MASK = 0x200,
    DMAC_CH5_SRC_GAT_EN_POS = 9,
    DMAC_CH5_DST_SCA_EN_MASK = 0x100,
    DMAC_CH5_DST_SCA_EN_POS = 8,
    DMAC_CH5_STAT_SRC_MASK = 0x80,
    DMAC_CH5_STAT_SRC_POS = 7,
    DMAC_CH5_STAT_DST_MASK = 0x40,
    DMAC_CH5_STAT_DST_POS = 6,
    DMAC_CH5_STW_MASK = 0x38,
    DMAC_CH5_STW_POS = 3,
    DMAC_CH5_DTW_MASK = 0x7,
    DMAC_CH5_DTW_POS = 0,
};

enum DMAC_DMA_COMP_PARAMS_4_L_FIELD
{
    DMAC_CH4_FIFO_DEPTH_MASK = (int)0x70000000L,
    DMAC_CH4_FIFO_DEPTH_POS = 28,
    DMAC_CH4_SMS_MASK = 0xe000000,
    DMAC_CH4_SMS_POS = 25,
    DMAC_CH4_LMS_MASK = 0x1c00000,
    DMAC_CH4_LMS_POS = 22,
    DMAC_CH4_DMS_MASK = 0x380000,
    DMAC_CH4_DMS_POS = 19,
    DMAC_CH4_MAX_MULT_SIZE_MASK = 0x70000,
    DMAC_CH4_MAX_MULT_SIZE_POS = 16,
    DMAC_CH4_FC_MASK = 0xc000,
    DMAC_CH4_FC_POS = 14,
    DMAC_CH4_HC_LLP_MASK = 0x2000,
    DMAC_CH4_HC_LLP_POS = 13,
    DMAC_CH4_CTL_WB_EN_MASK = 0x1000,
    DMAC_CH4_CTL_WB_EN_POS = 12,
    DMAC_CH4_MULTI_BLK_EN_MASK = 0x800,
    DMAC_CH4_MULTI_BLK_EN_POS = 11,
    DMAC_CH4_LOCK_EN_MASK = 0x400,
    DMAC_CH4_LOCK_EN_POS = 10,
    DMAC_CH4_SRC_GAT_EN_MASK = 0x200,
    DMAC_CH4_SRC_GAT_EN_POS = 9,
    DMAC_CH4_DST_SCA_EN_MASK = 0x100,
    DMAC_CH4_DST_SCA_EN_POS = 8,
    DMAC_CH4_STAT_SRC_MASK = 0x80,
    DMAC_CH4_STAT_SRC_POS = 7,
    DMAC_CH4_STAT_DST_MASK = 0x40,
    DMAC_CH4_STAT_DST_POS = 6,
    DMAC_CH4_STW_MASK = 0x38,
    DMAC_CH4_STW_POS = 3,
    DMAC_CH4_DTW_MASK = 0x7,
    DMAC_CH4_DTW_POS = 0,
};

enum DMAC_DMA_COMP_PARAMS_4_H_FIELD
{
    DMAC_CH3_FIFO_DEPTH_MASK = (int)0x70000000L,
    DMAC_CH3_FIFO_DEPTH_POS = 28,
    DMAC_CH3_SMS_MASK = 0xe000000,
    DMAC_CH3_SMS_POS = 25,
    DMAC_CH3_LMS_MASK = 0x1c00000,
    DMAC_CH3_LMS_POS = 22,
    DMAC_CH3_DMS_MASK = 0x380000,
    DMAC_CH3_DMS_POS = 19,
    DMAC_CH3_MAX_MULT_SIZE_MASK = 0x70000,
    DMAC_CH3_MAX_MULT_SIZE_POS = 16,
    DMAC_CH3_FC_MASK = 0xc000,
    DMAC_CH3_FC_POS = 14,
    DMAC_CH3_HC_LLP_MASK = 0x2000,
    DMAC_CH3_HC_LLP_POS = 13,
    DMAC_CH3_CTL_WB_EN_MASK = 0x1000,
    DMAC_CH3_CTL_WB_EN_POS = 12,
    DMAC_CH3_MULTI_BLK_EN_MASK = 0x800,
    DMAC_CH3_MULTI_BLK_EN_POS = 11,
    DMAC_CH3_LOCK_EN_MASK = 0x400,
    DMAC_CH3_LOCK_EN_POS = 10,
    DMAC_CH3_SRC_GAT_EN_MASK = 0x200,
    DMAC_CH3_SRC_GAT_EN_POS = 9,
    DMAC_CH3_DST_SCA_EN_MASK = 0x100,
    DMAC_CH3_DST_SCA_EN_POS = 8,
    DMAC_CH3_STAT_SRC_MASK = 0x80,
    DMAC_CH3_STAT_SRC_POS = 7,
    DMAC_CH3_STAT_DST_MASK = 0x40,
    DMAC_CH3_STAT_DST_POS = 6,
    DMAC_CH3_STW_MASK = 0x38,
    DMAC_CH3_STW_POS = 3,
    DMAC_CH3_DTW_MASK = 0x7,
    DMAC_CH3_DTW_POS = 0,
};

enum DMAC_DMA_COMP_PARAMS_3_L_FIELD
{
    DMAC_CH2_FIFO_DEPTH_MASK = (int)0x70000000L,
    DMAC_CH2_FIFO_DEPTH_POS = 28,
    DMAC_CH2_SMS_MASK = 0xe000000,
    DMAC_CH2_SMS_POS = 25,
    DMAC_CH2_LMS_MASK = 0x1c00000,
    DMAC_CH2_LMS_POS = 22,
    DMAC_CH2_DMS_MASK = 0x380000,
    DMAC_CH2_DMS_POS = 19,
    DMAC_CH2_MAX_MULT_SIZE_MASK = 0x70000,
    DMAC_CH2_MAX_MULT_SIZE_POS = 16,
    DMAC_CH2_FC_MASK = 0xc000,
    DMAC_CH2_FC_POS = 14,
    DMAC_CH2_HC_LLP_MASK = 0x2000,
    DMAC_CH2_HC_LLP_POS = 13,
    DMAC_CH2_CTL_WB_EN_MASK = 0x1000,
    DMAC_CH2_CTL_WB_EN_POS = 12,
    DMAC_CH2_MULTI_BLK_EN_MASK = 0x800,
    DMAC_CH2_MULTI_BLK_EN_POS = 11,
    DMAC_CH2_LOCK_EN_MASK = 0x400,
    DMAC_CH2_LOCK_EN_POS = 10,
    DMAC_CH2_SRC_GAT_EN_MASK = 0x200,
    DMAC_CH2_SRC_GAT_EN_POS = 9,
    DMAC_CH2_DST_SCA_EN_MASK = 0x100,
    DMAC_CH2_DST_SCA_EN_POS = 8,
    DMAC_CH2_STAT_SRC_MASK = 0x80,
    DMAC_CH2_STAT_SRC_POS = 7,
    DMAC_CH2_STAT_DST_MASK = 0x40,
    DMAC_CH2_STAT_DST_POS = 6,
    DMAC_CH2_STW_MASK = 0x38,
    DMAC_CH2_STW_POS = 3,
    DMAC_CH2_DTW_MASK = 0x7,
    DMAC_CH2_DTW_POS = 0,
};

enum DMAC_DMA_COMP_PARAMS_3_H_FIELD
{
    DMAC_CH1_FIFO_DEPTH_MASK = (int)0x70000000L,
    DMAC_CH1_FIFO_DEPTH_POS = 28,
    DMAC_CH1_SMS_MASK = 0xe000000,
    DMAC_CH1_SMS_POS = 25,
    DMAC_CH1_LMS_MASK = 0x1c00000,
    DMAC_CH1_LMS_POS = 22,
    DMAC_CH1_DMS_MASK = 0x380000,
    DMAC_CH1_DMS_POS = 19,
    DMAC_CH1_MAX_MULT_SIZE_MASK = 0x70000,
    DMAC_CH1_MAX_MULT_SIZE_POS = 16,
    DMAC_CH1_FC_MASK = 0xc000,
    DMAC_CH1_FC_POS = 14,
    DMAC_CH1_HC_LLP_MASK = 0x2000,
    DMAC_CH1_HC_LLP_POS = 13,
    DMAC_CH1_CTL_WB_EN_MASK = 0x1000,
    DMAC_CH1_CTL_WB_EN_POS = 12,
    DMAC_CH1_MULTI_BLK_EN_MASK = 0x800,
    DMAC_CH1_MULTI_BLK_EN_POS = 11,
    DMAC_CH1_LOCK_EN_MASK = 0x400,
    DMAC_CH1_LOCK_EN_POS = 10,
    DMAC_CH1_SRC_GAT_EN_MASK = 0x200,
    DMAC_CH1_SRC_GAT_EN_POS = 9,
    DMAC_CH1_DST_SCA_EN_MASK = 0x100,
    DMAC_CH1_DST_SCA_EN_POS = 8,
    DMAC_CH1_STAT_SRC_MASK = 0x80,
    DMAC_CH1_STAT_SRC_POS = 7,
    DMAC_CH1_STAT_DST_MASK = 0x40,
    DMAC_CH1_STAT_DST_POS = 6,
    DMAC_CH1_STW_MASK = 0x38,
    DMAC_CH1_STW_POS = 3,
    DMAC_CH1_DTW_MASK = 0x7,
    DMAC_CH1_DTW_POS = 0,
};

enum DMAC_DMA_COMP_PARAMS_2_L_FIELD
{
    DMAC_CH0_FIFO_DEPTH_MASK = (int)0x70000000L,
    DMAC_CH0_FIFO_DEPTH_POS = 28,
    DMAC_CH0_SMS_MASK = 0xe000000,
    DMAC_CH0_SMS_POS = 25,
    DMAC_CH0_LMS_MASK = 0x1c00000,
    DMAC_CH0_LMS_POS = 22,
    DMAC_CH0_DMS_MASK = 0x380000,
    DMAC_CH0_DMS_POS = 19,
    DMAC_CH0_MAX_MULT_SIZE_MASK = 0x70000,
    DMAC_CH0_MAX_MULT_SIZE_POS = 16,
    DMAC_CH0_FC_MASK = 0xc000,
    DMAC_CH0_FC_POS = 14,
    DMAC_CH0_HC_LLP_MASK = 0x2000,
    DMAC_CH0_HC_LLP_POS = 13,
    DMAC_CH0_CTL_WB_EN_MASK = 0x1000,
    DMAC_CH0_CTL_WB_EN_POS = 12,
    DMAC_CH0_MULTI_BLK_EN_MASK = 0x800,
    DMAC_CH0_MULTI_BLK_EN_POS = 11,
    DMAC_CH0_LOCK_EN_MASK = 0x400,
    DMAC_CH0_LOCK_EN_POS = 10,
    DMAC_CH0_SRC_GAT_EN_MASK = 0x200,
    DMAC_CH0_SRC_GAT_EN_POS = 9,
    DMAC_CH0_DST_SCA_EN_MASK = 0x100,
    DMAC_CH0_DST_SCA_EN_POS = 8,
    DMAC_CH0_STAT_SRC_MASK = 0x80,
    DMAC_CH0_STAT_SRC_POS = 7,
    DMAC_CH0_STAT_DST_MASK = 0x40,
    DMAC_CH0_STAT_DST_POS = 6,
    DMAC_CH0_STW_MASK = 0x38,
    DMAC_CH0_STW_POS = 3,
    DMAC_CH0_DTW_MASK = 0x7,
    DMAC_CH0_DTW_POS = 0,
};

enum DMAC_DMA_COMP_PARAMS_2_H_FIELD
{
    DMAC_CH7_MULTI_BLK_TYPE_MASK = (int)0xf0000000L,
    DMAC_CH7_MULTI_BLK_TYPE_POS = 28,
    DMAC_CH6_MULTI_BLK_TYPE_MASK = 0xf000000,
    DMAC_CH6_MULTI_BLK_TYPE_POS = 24,
    DMAC_CH5_MULTI_BLK_TYPE_MASK = 0xf00000,
    DMAC_CH5_MULTI_BLK_TYPE_POS = 20,
    DMAC_CH4_MULTI_BLK_TYPE_MASK = 0xf0000,
    DMAC_CH4_MULTI_BLK_TYPE_POS = 16,
    DMAC_CH3_MULTI_BLK_TYPE_MASK = 0xf000,
    DMAC_CH3_MULTI_BLK_TYPE_POS = 12,
    DMAC_CH2_MULTI_BLK_TYPE_MASK = 0xf00,
    DMAC_CH2_MULTI_BLK_TYPE_POS = 8,
    DMAC_CH1_MULTI_BLK_TYPE_MASK = 0xf0,
    DMAC_CH1_MULTI_BLK_TYPE_POS = 4,
    DMAC_CH0_MULTI_BLK_TYPE_MASK = 0xf,
    DMAC_CH0_MULTI_BLK_TYPE_POS = 0,
};

enum DMAC_DMA_COMP_PARAMS_1_L_FIELD
{
    DMAC_CH7_MAX_BLK_SIZE_MASK = (int)0xf0000000L,
    DMAC_CH7_MAX_BLK_SIZE_POS = 28,
    DMAC_CH6_MAX_BLK_SIZE_MASK = 0xf000000,
    DMAC_CH6_MAX_BLK_SIZE_POS = 24,
    DMAC_CH5_MAX_BLK_SIZE_MASK = 0xf00000,
    DMAC_CH5_MAX_BLK_SIZE_POS = 20,
    DMAC_CH4_MAX_BLK_SIZE_MASK = 0xf0000,
    DMAC_CH4_MAX_BLK_SIZE_POS = 16,
    DMAC_CH3_MAX_BLK_SIZE_MASK = 0xf000,
    DMAC_CH3_MAX_BLK_SIZE_POS = 12,
    DMAC_CH2_MAX_BLK_SIZE_MASK = 0xf00,
    DMAC_CH2_MAX_BLK_SIZE_POS = 8,
    DMAC_CH1_MAX_BLK_SIZE_MASK = 0xf0,
    DMAC_CH1_MAX_BLK_SIZE_POS = 4,
    DMAC_CH0_MAX_BLK_SIZE_MASK = 0xf,
    DMAC_CH0_MAX_BLK_SIZE_POS = 0,
};

enum DMAC_DMA_COMP_PARAMS_1_H_FIELD
{
    DMAC_STATIC_ENDIAN_SELECT_MASK = (int)0x20000000,
    DMAC_STATIC_ENDIAN_SELECT_POS = 29,
    DMAC_ADD_ENCODED_PARAMS_MASK = 0x10000000,
    DMAC_ADD_ENCODED_PARAMS_POS = 28,
    DMAC_NUM_HS_INT_MASK = 0xf800000,
    DMAC_NUM_HS_INT_POS = 23,
    DMAC_M1_HDATA_WIDTH_MASK = 0x600000,
    DMAC_M1_HDATA_WIDTH_POS = 21,
    DMAC_M2_HDATA_WIDTH_MASK = 0x180000,
    DMAC_M2_HDATA_WIDTH_POS = 19,
    DMAC_M3_HDATA_WIDTH_MASK = 0x60000,
    DMAC_M3_HDATA_WIDTH_POS = 17,
    DMAC_M4_HDATA_WIDTH_MASK = 0x18000,
    DMAC_M4_HDATA_WIDTH_POS = 15,
    DMAC_S_HDATA_WIDTH_MASK = 0x6000,
    DMAC_S_HDATA_WIDTH_POS = 13,
    DMAC_NUMBER_MASTER_INT_MASK = 0x1800,
    DMAC_NUMBER_MASTER_INT_POS = 11,
    DMAC_NUM_CHANNELS_MASK = 0x700,
    DMAC_NUM_CHANNELS_POS = 8,
    DMAC_MABRST_MASK = 0x8,
    DMAC_MABRST_POS = 3,
    DMAC_INTR_IO_MASK = 0x6,
    DMAC_INTR_IO_POS = 1,
    DMAC_BIG_ENDIAN_MASK = 0x1,
    DMAC_BIG_ENDIAN_POS = 0,
};

enum DMAC_DMACOMPIDREG_L_FIELD
{
    DMAC_DMA_COMP_TYPE_MASK = (int)0xffffffffL,
    DMAC_DMA_COMP_TYPE_POS = 0,
};

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __REG_DMAC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
