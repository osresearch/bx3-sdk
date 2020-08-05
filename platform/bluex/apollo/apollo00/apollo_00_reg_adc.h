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
#ifndef __APOLLO_00_REG_ADC_H__
#define __APOLLO_00_REG_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

typedef struct {
    __IO uint32_t CTRL;                 /* <! control register.         0x0000 */
    __IO uint32_t DMA;                  /* <! DMA                       0x0004 */
    __IO uint32_t DLY;                  /* <! delay .                   0x0008 */
    __O  uint32_t SSM;                  /* <! single sample mode .      0x000C */
    __I  uint32_t FRAP;                 /* <! fifo read access point    0x0010 */
    __IO uint32_t MSM;                  /* <! multiply sample mode .    0x0014 */
} reg_adc_t;

typedef struct {
    uint32_t   ADC_COMP_Current: 3,
               ADC_CLK_DIV: 2,
               ADC_REFP: 2,
               ADC_REF_BUF_Current: 2,
               Reserved0: 1,
               LV_VCM: 1,
               Force_ADC_CH_VDD_to_INT: 1,
               ADC_SINGLE_DR: 1,
               Sinlge_ended_Mode: 1,
               External_Input_Buffer: 1,
               Temperature_Sensor_Type: 1,
               Temperature_Sensor: 1,
               Battery_Monitor: 1,
               Reserved2: 14;
} adc_cfg_reg_t;


/* bit definition ------------------------------------------------------------*/

/******************  Bit definition for ADC_CTRL register  ********************/
#define ADC_CTRL_LDO_FORCE_ON_POS                       (0U)
#define ADC_CTRL_LDO_FORCE_ON_MASK                      (0x1UL << ADC_CTRL_LDO_FORCE_ON_POS)
#define ADC_CTRL_LDO_FORCE_ON                           ADC_CTRL_LDO_FORCE_ON_MASK
#define ADC_CTRL_LDO_FORCE_OFF_POS                      (1U)
#define ADC_CTRL_LDO_FORCE_OFF_MASK                     (0x1UL << ADC_CTRL_LDO_FORCE_OFF_POS)
#define ADC_CTRL_LDO_FORCE_OFF                          ADC_CTRL_LDO_FORCE_OFF_MASK
#define ADC_CTRL_LDO_SD_MULT_POS                        (2U)
#define ADC_CTRL_LDO_SD_MULT_MASK                       (0x1UL << ADC_CTRL_LDO_SD_MULT_POS)
#define ADC_CTRL_LDO_SD_MULT                            ADC_CTRL_LDO_SD_MULT_MASK
#define ADC_CTRL_LDO_SD_SNGL_POS                        (3U)
#define ADC_CTRL_LDO_SD_SNGL_MASK                       (0x1UL << ADC_CTRL_LDO_SD_SNGL_POS)
#define ADC_CTRL_LDO_SD_SNGL                            ADC_CTRL_LDO_SD_SNGL_MASK
#define ADC_CTRL_CLK_POL_POS                            (4U)
#define ADC_CTRL_CLK_POL_MASK                           (0x1UL << ADC_CTRL_CLK_POL_POS)
#define ADC_CTRL_CLK_POL                                ADC_CTRL_CLK_POL_MASK
#define ADC_CTRL_DMA_EN_POS                             (5U)
#define ADC_CTRL_DMA_EN_MASK                            (0x1UL << ADC_CTRL_DMA_EN_POS)
#define ADC_CTRL_DMA_EN                                 ADC_CTRL_DMA_EN_MASK

/******************  Bit definition for ADC_MSMC register  ********************/
#define ADC_MSMC_NUM_POS                                (0U)
#define ADC_MSMC_NUM_MASK                               (0xFFFFUL << ADC_MSMC_NUM_POS)
#define ADC_MSMC_NUM                                    ADC_MSMC_NUM_MASK
#define ADC_MSMC_DLY_POS                                (0U)
#define ADC_MSMC_DLY_MASK                               (0xFFFFUL << ADC_MSMC_DLY_POS)
#define ADC_MSMC_DLY                                    ADC_MSMC_DLY_MASK

/******************  Bit definition for ADC_DLY register  ********************/
#define ADC_DLY_LDO_POS                                 (0U)
#define ADC_DLY_LDO_MASK                                (0x3FFUL << ADC_DLY_LDO_POS)
#define ADC_DLY_LDO                                     ADC_DLY_LDO_MASK
#define ADC_DLY_CHANNEL_POS                             (16U)
#define ADC_DLY_CHANNEL_MASK                            (0x3FFUL << ADC_DLY_CHANNEL_POS)
#define ADC_DLY_CHANNEL                                 ADC_DLY_CHANNEL_MASK

/******************  Bit definition for ADC_SSM register  ********************/
#define ADC_SSM_START_POS                               (1U)
#define ADC_SSM_START_MASK                              (0x1UL << ADC_SSM_START_POS)
#define ADC_SSM_START                                   ADC_SSM_START_MASK
#define ADC_SSM_FIFO_EMPTY_POS                          (2U)
#define ADC_SSM_FIFO_EMPTY_MASK                         (0x1UL << ADC_SSM_FIFO_EMPTY_POS)
#define ADC_SSM_FIFO_EMPTY                              ADC_SSM_FIFO_EMPTY_MASK
#define ADC_SSM_FIFO_FULL_POS                           (3U)
#define ADC_SSM_FIFO_FULL_MASK                          (0x1UL << ADC_SSM_FIFO_FULL_POS)
#define ADC_SSM_FIFO_FULL                               ADC_SSM_FIFO_FULL_MASK
#define ADC_SSM_CH_NUM_POS                              (12U)
#define ADC_SSM_CH_NUM_MASK                             (0x7UL << ADC_SSM_CH_NUM_POS)
#define ADC_SSM_CH_NUM                                  ADC_SSM_CH_NUM_MASK
#define ADC_SSM_DATA_POS                                (16U)
#define ADC_SSM_DATA_MASK                               (0x3FFUL << ADC_SSM_DATA_POS)
#define ADC_SSM_DATA                                    ADC_SSM_DATA_MASK

/******************  Bit definition for ADC_FRAP register  ********************/
#define ADC_FRAP_DATA_POS                               (0U)
#define ADC_FRAP_DATA_MASK                              (0x3FFUL << ADC_FRAP_DATA_POS)
#define ADC_FRAP_DATA                                   ADC_FRAP_DATA_MASK

/******************  Bit definition for ADC_MSM register  ********************/
#define ADC_MSM_START_POS                               (0U)
#define ADC_MSM_START_MASK                              (0x1UL << ADC_MSM_START_POS)
#define ADC_MSM_START                                   ADC_MSM_START_MASK
#define ADC_MSM_CH_NUM_POS                              (8U)
#define ADC_MSM_CH_NUM_MASK                             (0x7UL << ADC_MSM_CH_NUM_POS)
#define ADC_MSM_CH_NUM                                  ADC_MSM_CH_NUM_MASK

/* value type ----------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_REG_ADC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

