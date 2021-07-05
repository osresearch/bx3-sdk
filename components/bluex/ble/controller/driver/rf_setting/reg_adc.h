#ifndef __REG_ADC_H__
#define __REG_ADC_H__
#include <stdint.h>

typedef struct
{
    volatile uint32_t CTRL0;
    volatile uint32_t CTRL_DMA;
    volatile uint32_t CTRL_DELAY;
    volatile uint32_t CTRL_SNGL;
    volatile uint32_t FIFO;
    volatile uint32_t CTRL_MULT;
}ble_reg_adc_t;

enum ADC_CTRL0_FIELD
{
    ADC_DMA_EN_MASK = 0x20,
    ADC_DMA_EN_POS = 5,
    ADC_ADC_CLK_POL_MASK = 0x10,
    ADC_ADC_CLK_POL_POS = 4,
    ADC_LDO_SD_SNGL_MASK = 0x8,
    ADC_LDO_SD_SNGL_POS = 3,
    ADC_LDO_SD_MULT_MASK = 0x4,
    ADC_LDO_SD_MULT_POS = 2,
    ADC_LDO_FORCE_OFF_MASK = 0x2,
    ADC_LDO_FORCE_OFF_POS = 1,
    ADC_LDO_FORCE_ON_MASK = 0x1,
    ADC_LDO_FORCE_ON_POS = 0,
};

enum ADC_CTRL_DMA_FIELD
{
    ADC_MULT_DLY_MASK = (int)0xffff0000L,
    ADC_MULT_DLY_POS = 16,
    ADC_MULT_NUM_MASK = 0xffff,
    ADC_MULT_NUM_POS = 0,
};

enum ADC_CTRL_DELAY_FIELD
{
    ADC_CH_DLY_MASK = 0x3ff0000,
    ADC_CH_DLY_POS = 16,
    ADC_LDO_DLY_MASK = 0x3ff,
    ADC_LDO_DLY_POS = 0,
};

enum ADC_CTRL_SNGL_FIELD
{
    ADC_ADC_DATA_SNGL_MASK = 0x3ff0000,
    ADC_ADC_DATA_SNGL_POS = 16,
    ADC_SNGL_CH_MASK = 0x7000,
    ADC_SNGL_CH_POS = 12,
    ADC_FIFO_FULL_MASK = 0x8,
    ADC_FIFO_FULL_POS = 3,
    ADC_FIFO_EMPT_MASK = 0x4,
    ADC_FIFO_EMPT_POS = 2,
    ADC_SNGL_START_MASK = 0x2,
    ADC_SNGL_START_POS = 1,
};

enum ADC_FIFO_FIELD
{
    ADC_FIFO_DATA_MASK = 0x3ff,
    ADC_FIFO_DATA_POS = 0,
};

enum ADC_CTRL_MULT_FIELD
{
    ADC_MULT_CH_MASK = 0x700,
    ADC_MULT_CH_POS = 8,
    ADC_MULT_START_MASK = 0x1,
    ADC_MULT_START_POS = 0,
};

#endif
