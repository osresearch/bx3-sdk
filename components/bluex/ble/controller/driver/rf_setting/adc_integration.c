/*
 * adc_integration.c
 *
 *  Created on: 2018Äê6ÔÂ26ÈÕ
 *      Author: jiachuang
 */


#include "periph_common.h"
#include "app_adc.h"
#include "periph_recovery.h"
#include "bx_config.h"
#include "bx_dbg.h"
#include "rst_gen.h"
#include "clk_gate.h"
#include "reg_sysc_per.h"
#include "pshare.h"
#include "log.h"
#include "sysctrl.h"


static void adc_intr_op(app_adc_inst_t * inst,intr_operation_t op)
{
    //NOTHING TO DO
    return;
}
static void adc_sw_rst(app_adc_inst_t * inst)
{
    //NOTHING TO DO
    return;
}
static void adc_clk_src_cfg(app_adc_inst_t * inst,uint32_t clk_cfg)
{
    //NOTHING TO DO
    return;
}
static void adc_clk_gate(app_adc_inst_t * inst,clk_gate_operation_t op)
{
    //NOTHING TO DO
    return;
}
static void adc_pin_cfg(app_adc_inst_t * inst,uint8_t pin_num,uint32_t pin_role,bool enable)
{
    //NOTHING TO DO
    return;
}

static void adc_sys_stat(app_adc_inst_t *inst,uint32_t sys_stat)
{
    switch(sys_stat)
    {
    case ADC_INIT:
        recovery_list_add(cpu_domain_recovery_buf,CPU_DOMAIN_ADC_CTRL,&inst->inst);
        break;
    case ADC_UNINIT:
        recovery_list_remove(cpu_domain_recovery_buf,CPU_DOMAIN_ADC_CTRL);
        break;
    case ADC_READ_START:
        cpu_domain_stat.adc_ctrl = 1;
        break;
    case ADC_READ_DONE:
        cpu_domain_stat.adc_ctrl = 0;
        break;
    default:
        LOG(LOG_LVL_WARN,"unexpected sys stat: %d\n",sys_stat);
        break;
    }
}

const periph_universal_func_set_t adc_universal_func =
{
    .intr_op_func     = (intr_op_func_t    )adc_intr_op,
    .sw_rst_func      = (sw_rst_func_t     )adc_sw_rst,
    .clk_src_cfg_func = (clk_src_cfg_func_t)adc_clk_src_cfg,
    .clk_gate_func    = (clk_gate_func_t   )adc_clk_gate,
    .pin_cfg_func     = (pin_cfg_func_t    )adc_pin_cfg,
    .sys_stat_func    = (sys_stat_func_t   )adc_sys_stat,
};



