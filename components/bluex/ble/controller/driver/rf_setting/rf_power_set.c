#include "rf_power_set.h"
#include "rf_reg_typedef.h"
#include "bx_sys_config.h"
#include "rf_temp_adjust.h"
#include "reg_sysc_awo_apollo_00.h"
#include "rf_reg_settings.h"

extern temp_mode_t temp_mode;
extern int32_t adc_cp_RO;
extern void refresh_rf_param_with_ro_dcoff( uint32_t ro );
extern void refresh_rf_param_with_ro_dcon(uint32_t ro);

//4V2
void rf_18_8_4v2_dcoff_rf3v3_8dbm(void)
{
    RF_REG_1 = 0x0001E825;
    RF_REG_2 = 0x00000000;
    RF_REG_3 = 0x00000000;
    RF_REG_4 = 0x85C00775;
    RF_REG_5 = 0x00000000;
    RF_REG_6 = 0x00000020;
    RF_REG_7 = 0x00003980;	//adc
    RF_REG_8 = 0x0301F8C4;
    RF_REG_9 = 0x3F231400;
    RF_REG_a = 0xDB100DAC;
    RF_REG_b = 0xDB1CF000;
    RF_REG_c = 0x610003C6;
    RF_REG_d = 0xFDC00DB0;
    RF_REG_e = 0x46FF6492;
    RF_REG_f = 0x10000005;
    refresh_rf_param_with_ro_dcoff(adc_cp_RO);
}

void rf_18_8_4v2_dcoff_rf3v3_4dbm(void)
{
    RF_REG_1 = 0x0001E825;
    RF_REG_2 = 0x00000000;
    RF_REG_3 = 0x00000000;
    RF_REG_4 = 0x85C00775;
    RF_REG_5 = 0x00000000;
    RF_REG_6 = 0x00000020;
    RF_REG_7 = 0x00003980;	//adc
    RF_REG_8 = 0x0301F8C4;
    RF_REG_9 = 0x3F231400;
    RF_REG_a = 0xDB100DAC;
    RF_REG_b = 0xDB18D000;
    RF_REG_c = 0x61000206;
    RF_REG_d = 0x4C800DB0;
    RF_REG_e = 0x46FF6492;
    RF_REG_f = 0x10000005;
    refresh_rf_param_with_ro_dcoff(adc_cp_RO);
}

void rf_18_8_4v2_dcoff_rf3v3_2dbm(void)
{
    RF_REG_1 = 0x0001E825;
    RF_REG_2 = 0x00000000;
    RF_REG_3 = 0x00000000;
    RF_REG_4 = 0x85C00775;
    RF_REG_5 = 0x00000000;
    RF_REG_6 = 0x00000020;
    RF_REG_7 = 0x00003980;	//adc
    RF_REG_8 = 0x0301F8C4;
    RF_REG_9 = 0x3F231400;
    RF_REG_a = 0xDB100DAC;
    RF_REG_b = 0xDB1CF000;
    RF_REG_c = 0x610003C6;
    RF_REG_d = 0x01C00DB0;
    RF_REG_e = 0x46FF6492;
    RF_REG_f = 0x10000005;
    refresh_rf_param_with_ro_dcoff(adc_cp_RO);
}

void rf_18_8_4v2_dcoff_rf1v8_2dbm(void)
{
    RF_REG_1 = 0x0001E825;
    RF_REG_2 = 0x00000000;
    RF_REG_3 = 0x00000000;
    RF_REG_4 = 0x85C00775;
    RF_REG_5 = 0x00000000;
    RF_REG_6 = 0x00000020;
    RF_REG_7 = 0x00003980;	//adc
    RF_REG_8 = 0x0301F8C4;
    RF_REG_9 = 0x3F231400;
    RF_REG_a = 0xDB100DAC;
    RF_REG_b = 0xDB1CF000;
    RF_REG_c = 0x61000206;
    RF_REG_d = 0xFDC00DB0;
    RF_REG_e = 0x46FF6492;
    RF_REG_f = 0x10000005;
    refresh_rf_param_with_ro_dcoff(adc_cp_RO);
}

void rf_18_8_4v2_dcon_rf3v3_8dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0xFDC00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB1CD008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0xFDC00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB1C9008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0xFDC00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB1C9008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0xFDC00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_rf3v3_4dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x0DC00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB1CF080;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x0DC00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;  //adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB1CB000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x0DC00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB1CB000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x0DC00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_rf3v3_n2dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_dcoutput_2dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0xFC000DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0xFC000DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0xFC000DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0xFC000DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_dcoutput_0dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18F000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB18B000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB18B000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_dcoutput_n2dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_dcoutput_n5dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x25000DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x25000DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x25000DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x25000DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_dcoutput_n10dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_dcoutput_n15dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x61000286;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D080;
            RF_REG_c = 0x61000286;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000286;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000286;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_dcoutput_n20dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DE080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18C080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB188000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB188000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_4v2_dcon_dcoutput_n30dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DE080;
            RF_REG_c = 0x61000306;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x05C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000010;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18C080;
            RF_REG_c = 0x61000306;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB188000;
            RF_REG_c = 0x61000306;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x85C00775;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000020;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB188000;
            RF_REG_c = 0x61000306;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

//3V3
void rf_18_8_3v3_dcoff_rf3v3_8dbm(void)
{
    RF_REG_1 = 0x0001E825;
    RF_REG_2 = 0x00000000;
    RF_REG_3 = 0x00000000;
    RF_REG_4 = 0x87C00F70;
    RF_REG_5 = 0x00000000;
    RF_REG_6 = 0x00000120;
    RF_REG_7 = 0x00003980;	//adc
    RF_REG_8 = 0x0301F8C4;
    RF_REG_9 = 0x3F231400;
    RF_REG_a = 0xDB100DAC;
    RF_REG_b = 0xDB1CF000;
    RF_REG_c = 0x610003C6;
    RF_REG_d = 0xFDC00DB0;
    RF_REG_e = 0x46FF6492;
    RF_REG_f = 0x10000005;
	refresh_rf_param_with_ro_dcoff(adc_cp_RO);
}

void rf_18_8_3v3_dcoff_rf3v3_4dbm(void)
{
    RF_REG_1 = 0x0001E825;
    RF_REG_2 = 0x00000000;
    RF_REG_3 = 0x00000000;
    RF_REG_4 = 0x87C00F70;
    RF_REG_5 = 0x00000000;
    RF_REG_6 = 0x00000120;
    RF_REG_7 = 0x00003980;	//adc
    RF_REG_8 = 0x0301F8C4;
    RF_REG_9 = 0x3F231400;
    RF_REG_a = 0xDB100DAC;
    RF_REG_b = 0xDB18D000;
    RF_REG_c = 0x61000206;
    RF_REG_d = 0x4C800DB0;
    RF_REG_e = 0x46FF6492;
    RF_REG_f = 0x10000005;
    refresh_rf_param_with_ro_dcoff(adc_cp_RO);
}

void rf_18_8_3v3_dcoff_rf3v3_2dbm(void)
{
    RF_REG_1 = 0x0001E825;
    RF_REG_2 = 0x00000000;
    RF_REG_3 = 0x00000000;
    RF_REG_4 = 0x87C00F70;
    RF_REG_5 = 0x00000000;
    RF_REG_6 = 0x00000120;
    RF_REG_7 = 0x00003980;	//adc
    RF_REG_8 = 0x0301F8C4;
    RF_REG_9 = 0x3F231400;
    RF_REG_a = 0xDB100DAC;
    RF_REG_b = 0xDB1CF000;
    RF_REG_c = 0x610003C6;
    RF_REG_d = 0x01C00DB0;
    RF_REG_e = 0x46FF6492;
    RF_REG_f = 0x10000005;
    refresh_rf_param_with_ro_dcoff(adc_cp_RO);
}


void rf_18_8_3v3_dcoff_rf1v8_2dbm(void)
{
    RF_REG_1 = 0x0001E825;
    RF_REG_2 = 0x00000000;
    RF_REG_3 = 0x00000000;
    RF_REG_4 = 0x87C00F70;
    RF_REG_5 = 0x00000000;
    RF_REG_6 = 0x00000120;
    RF_REG_7 = 0x00003980;	//adc
    RF_REG_8 = 0x0301F8C4;
    RF_REG_9 = 0x3F231400;
    RF_REG_a = 0xDB100DAC;
    RF_REG_b = 0xDB1CF000;
    RF_REG_c = 0x61000206;
    RF_REG_d = 0xFDC00DB0;
    RF_REG_e = 0x46FF6492;
    RF_REG_f = 0x10000005;
    refresh_rf_param_with_ro_dcoff(adc_cp_RO);
}


void rf_18_8_3v3_dcon_rf3v3_8dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0xFDC00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB1CD008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0xFDC00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB1C9008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0xFDC00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB1C9008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0xFDC00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_rf3v3_4dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x0DC00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB1CF080;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x0DC00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB1CB000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x0DC00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB1CB000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x0DC00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_rf3v3_n2dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF008;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x610003C6;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_dcoutput_2dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0xFC000DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0xFC000DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0xFC000DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0xFC000DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_dcoutput_0dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF008;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18F000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB18B000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E820;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB18B000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_dcoutput_n2dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x4C800DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_dcoutput_n5dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x25000DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x25000DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x25000DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x25000DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_dcoutput_n10dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_dcoutput_n15dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DF080;
            RF_REG_c = 0x61000286;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18D080;
            RF_REG_c = 0x61000286;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000286;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB189000;
            RF_REG_c = 0x61000286;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_dcoutput_n20dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DE080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18C080;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB188000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB188000;
            RF_REG_c = 0x61000206;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}


void rf_18_8_3v3_dcon_dcoutput_n30dbm(void)
{
    switch (temp_mode)
    {
        case MODE_BELOWN25:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F7F9000;
            RF_REG_a = 0xDB100FFC;
            RF_REG_b = 0xDB0DE080;
            RF_REG_c = 0x61000306;
            RF_REG_d = 0x01C00DB2;
            RF_REG_e = 0x46FFFFE7;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_BELOW0:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x07C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000110;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F4A9300;
            RF_REG_a = 0xDB100EDC;
            RF_REG_b = 0xDB18C080;
            RF_REG_c = 0x61000306;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF77C9;
            RF_REG_f = 0x10000006;
            sysc_awo_o_ldo_setup_time_setf( 0xD0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 7, 0 );
        break;
        case MODE_NORMAL:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x3F231400;
            RF_REG_a = 0xDB100DAC;
            RF_REG_b = 0xDB188000;
            RF_REG_c = 0x61000306;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000005;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        case MODE_OVER50:
            RF_REG_1 = 0x0001E825;
            RF_REG_2 = 0x00000000;
            RF_REG_3 = 0x00000000;
            RF_REG_4 = 0x87C00F70;
            RF_REG_5 = 0x00000000;
            RF_REG_6 = 0x00000120;
            RF_REG_7 = 0x00003980;	//adc
            RF_REG_8 = 0x0301F8C4;
            RF_REG_9 = 0x5F131380;
            RF_REG_a = 0xDB100DDE;
            RF_REG_b = 0xDB188000;
            RF_REG_c = 0x61000306;
            RF_REG_d = 0x01C00DB0;
            RF_REG_e = 0x46FF6489;
            RF_REG_f = 0x10000003;
            sysc_awo_o_ldo_setup_time_setf( 0xc0 );
            sysc_awo_reg_pmu_timer_pack( 8, 5, 1, 2, 3 );
        break;
        default: break;
    }
    refresh_rf_param_with_ro_dcon(adc_cp_RO);
}

void rf_18_8_3v3_32m_dcoff_rf3v3_single_3dbm(void)
{
    RF_REG_1 = 0x0001E825;
    RF_REG_2 = 0x00000000;
    RF_REG_3 = 0x00000000;
    RF_REG_4 = 0x85C00F70;
    RF_REG_5 = 0x00000000;
    RF_REG_6 = 0x00000120;
    RF_REG_7 = 0x00003980;	//adc
    RF_REG_8 = 0x0301F8C4;
    RF_REG_9 = 0x3F231400;
    RF_REG_a = 0xDB100DAC;
    RF_REG_b = 0xDB1CF000;
    RF_REG_c = 0x610003C6;
    RF_REG_d = 0xFDC00DB0;
    RF_REG_e = 0x46FF6492;
    RF_REG_f = 0x10000005;
    refresh_rf_param_with_ro_dcoff(adc_cp_RO);
}

void rf_power_setting(void)
{
#if(MAIN_CLOCK == 96000000)
    {
        RF_REG_0 = 0x00C75CB3;
    }
#else
    {
        RF_REG_0 = 0x00C00000;
    }
#endif
    //4.2V
#ifdef RF_18_8_4V2_DCOFF_RF3V3_8dBm
    rf_18_8_4v2_dcoff_rf3v3_8dbm();
#endif
#ifdef RF_18_8_4V2_DCOFF_RF3V3_4dBm
    rf_18_8_4v2_dcoff_rf3v3_4dbm();
#endif
#ifdef RF_18_8_4V2_DCOFF_RF3V3_2dBm
    rf_18_8_4v2_dcoff_rf3v3_2dbm();
#endif
#ifdef RF_18_8_4V2_DCOFF_RF1V8_2dBm
    rf_18_8_4v2_dcoff_rf1v8_2dbm();
#endif
#ifdef RF_18_8_4V2_DCON_RF3V3_8dBm
    rf_18_8_4v2_dcon_rf3v3_8dbm();
#endif
#ifdef RF_18_8_4V2_DCON_RF3V3_4dBm
    rf_18_8_4v2_dcon_rf3v3_4dbm();
#endif
#ifdef RF_18_8_4V2_DCON_RF3V3_N2dBm
    rf_18_8_4v2_dcon_rf3v3_n2dbm();
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_2dBm
    rf_18_8_4v2_dcon_dcoutput_2dbm();
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_0dBm
    rf_18_8_4v2_dcon_dcoutput_0dbm();
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N2dBm
    rf_18_8_4v2_dcon_dcoutput_n2dbm();
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N5dBm
    rf_18_8_4v2_dcon_dcoutput_n5dbm();
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N10dBm
    rf_18_8_4v2_dcon_dcoutput_n10dbm();
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N15dBm
    rf_18_8_4v2_dcon_dcoutput_n15dbm();
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N20dBm
    rf_18_8_4v2_dcon_dcoutput_n20dbm();
#endif
#ifdef RF_18_8_4V2_DCOUTPUT_N30dBm
    rf_18_8_4v2_dcon_dcoutput_n30dbm();
#endif

    //3.3V
#ifdef RF_18_8_3V3_DCOFF_RF3V3_8dBm
    rf_18_8_3v3_dcoff_rf3v3_8dbm();
#endif
#ifdef RF_18_8_3V3_DCOFF_RF3V3_4dBm
    rf_18_8_3v3_dcoff_rf3v3_4dbm();
#endif
#ifdef RF_18_8_3V3_DCOFF_RF3V3_2dBm
    rf_18_8_3v3_dcoff_rf3v3_2dbm();
#endif
#ifdef RF_18_8_3V3_DCOFF_RF1V8_2dBm
    rf_18_8_3v3_dcoff_rf1v8_2dbm();
#endif
#ifdef RF_18_8_3V3_DCON_RF3V3_8dBm
    rf_18_8_3v3_dcon_rf3v3_8dbm();
#endif
#ifdef RF_18_8_3V3_DCON_RF3V3_4dBm
    rf_18_8_3v3_dcon_rf3v3_4dbm();
#endif
#ifdef RF_18_8_3V3_DCON_RF3V3_N2dBm
    rf_18_8_3v3_dcon_rf3v3_n2dbm();
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_2dBm
    rf_18_8_3v3_dcon_dcoutput_2dbm();
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_0dBm
    rf_18_8_3v3_dcon_dcoutput_0dbm();
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N2dBm
    rf_18_8_3v3_dcon_dcoutput_n2dbm();
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N5dBm
    rf_18_8_3v3_dcon_dcoutput_n5dbm();
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N10dBm
    rf_18_8_3v3_dcon_dcoutput_n10dbm();
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N15dBm
    rf_18_8_3v3_dcon_dcoutput_n15dbm();
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N20dBm
    rf_18_8_3v3_dcon_dcoutput_n20dbm();
#endif
#ifdef RF_18_8_3V3_DCOUTPUT_N30dBm
    rf_18_8_3v3_dcon_dcoutput_n30dbm();
#endif

    //custom ------------------------------------------------------
    //2416 - 3.3V 32M
#ifdef RF_18_8_3V3_32M_DCOFF_RF3V3_SINGLE_3dBm
    rf_18_8_3v3_32m_dcoff_rf3v3_single_3dbm();
#endif
    //custom ------------------------------------------------------

    reg_pad_voltage_init();
    
}

