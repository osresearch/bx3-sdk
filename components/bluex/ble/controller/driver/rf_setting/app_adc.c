/*
 * app_adc.c
 *
 *  Created on: 2018Äê6ÔÂ26ÈÕ
 *      Author: jiachuang
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "reg_adc.h"
#include "field_manipulate.h"
#include "app_adc.h"
#include "bx_dbg.h"
#include "ll.h"
#include "rwip.h"
#include "log.h"
#include "co_utils.h"
#include "app_dmac_wrapper.h"
#include "string.h"
#include "plf.h"
#include "rf_reg_typedef.h"
#include "rf_reg_settings.h"
#include "reg_sysc_cpu.h"
#include "reg_sysc_cpu_apollo_00.h"
#include "app_adc_utils.h"

extern periph_universal_func_set_t adc_universal_func;

void app_adc_set_ldo_delay_us(ble_reg_adc_t *reg , uint16_t us)
{
    uint16_t adc_ldo_val = 0;
    adc_ldo_val = us * APB_CLK / MHZ;
    if(adc_ldo_val > 0x3FF) adc_ldo_val = 0x3FF;
    if(adc_ldo_val < 1)     adc_ldo_val = 1;

    FIELD_WR(reg,CTRL_DELAY,ADC_CH_DLY ,adc_ldo_val);
    FIELD_WR(reg,CTRL_DELAY,ADC_LDO_DLY,adc_ldo_val);
}



periph_err_t app_adc_init(periph_inst_handle_t hdl)
{
    app_adc_inst_t *inst = CONTAINER_OF(hdl, app_adc_inst_t, inst);
    ble_reg_adc_t *reg = inst->reg;

    //NO USE
    adc_universal_func.sw_rst_func(inst);
    adc_universal_func.pin_cfg_func(inst,0,0,true);
    adc_universal_func.intr_op_func(inst,INTR_CLR);
    adc_universal_func.clk_src_cfg_func(inst,0);
    adc_universal_func.clk_gate_func(inst,SET_CLK);
    
    //SET PARAM
    rf_setting_single_mode_adc();
    app_adc_set_ldo_delay_us(reg , inst->param.ldo_delay_us);
    if(inst->param.ldo_force_on)
    {
        FIELD_WR(reg, CTRL0, ADC_LDO_FORCE_ON, 1);
    }
    else
    {
        FIELD_WR(reg, CTRL0, ADC_LDO_FORCE_ON, 0);
    }
    
    //STAT
    adc_universal_func.sys_stat_func(inst,ADC_INIT);
    return PERIPH_NO_ERROR;
}

periph_err_t app_adc_uninit(periph_inst_handle_t hdl)
{
    app_adc_inst_t *inst = CONTAINER_OF(hdl, app_adc_inst_t, inst);
    ble_reg_adc_t *reg = inst->reg;
    
    //NO USE
    adc_universal_func.clk_gate_func(inst,CLR_CLK);
    adc_universal_func.intr_op_func(inst,INTR_DISABLE);
    
    //Close LDO FORCE ON
    FIELD_WR(reg, CTRL0, ADC_LDO_FORCE_ON, 0);

		//SET PARAM
    rf_setting_single_mode_adc();
    //STAT
    adc_universal_func.sys_stat_func(inst,ADC_UNINIT);
    return PERIPH_NO_ERROR;
}

void adc_transfer_sanity_check(uint8_t channel)
{
    // Sanity check
    if(channel > ADC_CHANNEL_SUM_CNT)
    {
        BX_ASSERT(0);
    }
}



periph_err_t app_adc_read_without_dma(periph_inst_handle_t hdl , uint8_t channel , uint16_t *value)
{
    app_adc_inst_t *inst = CONTAINER_OF(hdl, app_adc_inst_t, inst);
    ble_reg_adc_t *reg = inst->reg;
    //thread lock
    if(periph_lock(&inst->env.adc_lock)==false)
    {
        return PERIPH_BUSY;
    }
    //read
    adc_transfer_sanity_check(channel);
    adc_universal_func.sys_stat_func(inst,ADC_READ_START);
    FIELD_WR(reg, CTRL_SNGL, ADC_SNGL_CH   , channel);
    FIELD_WR(reg, CTRL_SNGL, ADC_SNGL_START, 1);
    // wait adc data ready.
    while(FIELD_RD(reg, CTRL_SNGL, ADC_SNGL_START));
    adc_universal_func.sys_stat_func(inst,ADC_READ_DONE);
    
    //thread unlock
    periph_unlock(&inst->env.adc_lock);
    //adc value
    *value  = FIELD_RD(reg, CTRL_SNGL, ADC_ADC_DATA_SNGL);
    //return
    return PERIPH_NO_ERROR;
}


static void adc_read_complete(app_adc_inst_t *inst)
{
    void (*callback) (void*,uint8_t) = NULL;
    void * dummy = NULL;
    // Retrieve callback pointer
    callback = inst->env.callback;
    dummy = inst->env.dummy;
    BX_ASSERT(callback);
    // Clear callback pointer
    inst->env.callback = NULL;
    inst->env.dummy = NULL;
    //set iic idle status
    adc_universal_func.sys_stat_func(inst,ADC_READ_DONE);
    //thread unlock
    periph_unlock(&inst->env.adc_lock);
    // Call handler
    callback(dummy, RWIP_EIF_STATUS_OK);
}

void app_adc_disable_dma(ble_reg_adc_t *reg)
{
    sysc_cpu_adc_has_dma_setf(0);
    FIELD_WR(reg, CTRL0    , ADC_DMA_EN     , 0);
    FIELD_WR(reg, CTRL_MULT, ADC_MULT_START , 0);
}

static void adc_read_dma_callback(app_adc_inst_t *inst)
{
    app_adc_disable_dma(inst->reg);
    adc_read_complete(inst);
}

periph_err_t app_adc_read_with_dma(periph_inst_handle_t hdl , uint8_t channel , void (*callback) (void*,uint8_t),void* dummy)
{
    periph_err_t retval;
    app_adc_inst_t *inst = CONTAINER_OF(hdl, app_adc_inst_t, inst);
    ble_reg_adc_t *reg = inst->reg;
    //thread lock
    if(periph_lock(&inst->env.adc_lock)==false)
    {
        return PERIPH_BUSY;
    }
    //set adc param
    sysc_cpu_adc_has_dma_setf(1);
    FIELD_WR(reg, CTRL0    , ADC_DMA_EN     , 1);
    FIELD_WR(reg, CTRL_DMA , ADC_MULT_DLY   , inst->param.dma_delay);
    FIELD_WR(reg, CTRL_DMA , ADC_MULT_NUM   , inst->param.dma_size - 1);
    FIELD_WR(reg, CTRL_MULT, ADC_MULT_CH    , channel);
    while(FIELD_RD(reg, CTRL_MULT, ADC_MULT_START));//wait last ADC convert complete
    FIELD_WR(reg, CTRL_MULT, ADC_MULT_START , 1);
    //set adc idle status
    inst->env.callback = callback;
    inst->env.dummy    = dummy;
    adc_universal_func.sys_stat_func(inst,ADC_READ_START);

    //set dma para
    app_dmac_transfer_param_t param = 
    {
        .callback = (void (*)(void*))adc_read_dma_callback,
        .callback_param = inst,
        .src = (uint8_t *)&reg->FIFO,
        .dst = (uint8_t *)inst->param.dma_bufptr,
        .length = inst->param.dma_size,
        .src_tr_width = Transfer_Width_16_bits,
        .dst_tr_width = Transfer_Width_16_bits,
        .src_msize = Burst_Transaction_Length_1,
        .dst_msize = Burst_Transaction_Length_1,
        .tt_fc = Peripheral_to_Memory_DMAC_Flow_Controller,
        .src_per = Dmac_Iic1_Rx,
        .dst_per = 0,
        .int_en = 1,
    };
    retval = app_dmac_start_wrapper(&param , NULL);
    return retval;
}



