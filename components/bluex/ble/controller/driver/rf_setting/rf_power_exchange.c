#include "rf_power_exchange.h"
#include "rf_reg_typedef.h"
#include "rf_temp_adjust.h"
#include "modem.h"
#include "log.h"

static void exchange_dcoff_rf3V3_8dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB1CF000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 610003C4
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;
	//regd - FDC00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 7;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 7;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcoff_rf3V3_4dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB18D000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 61000204
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
	//regd - 4C800DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcoff_rf3V3_2dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB1CF000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 610003C4
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;
	//regd - 01C00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcoff_rf1V8_2dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB1CF000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 61000204
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
	//regd - FDC00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 7;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 7;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcon_rf3V3_8dBm(void)
{
	//reg1 - 0001E820
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 0;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 0;
	//regb - DB1C5008
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 1;
	//regc - 610003C4
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;
	//regd - FDC00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 7;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 7;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcon_rf3V3_4dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB1C7000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 610003C4
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;
	//regd - 0DC00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcon_rf3V3_N2dBm(void)
{
	//reg1 - 0001E820
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 0;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 0;
	//regb - DB185000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 610003C4
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 7;
	//regd - 01C00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46E36493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 0;
}

static void exchange_dcon_dcoutput_2dBm(void)
{
	//reg1 - 0001E820
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 0;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 0;
	//regb - DB185008
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 1;
	//regc - 61000204
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
	//regd - FC000DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 7;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 7;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 0;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcon_dcoutput_0dBm(void)
{
	//reg1 - 0001E820
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 0;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 0;
	//regb - DB187000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 3;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 61000204
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
	//regd - 01400DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 5;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcon_dcoutput_N2dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB185000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 61000204
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
	//regd - 4C800DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 2;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 3;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 2;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcon_dcoutput_N5dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB185000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 61000204
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
	//regd - 25000DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 1;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 1;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 4;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcon_dcoutput_N10dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB185000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 61000204
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
	//regd - 01C00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcon_dcoutput_N15dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB185000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 61000284
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 2;
	//regd - 01C00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46FF6493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 7;
}

static void exchange_dcon_dcoutput_N20dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB184000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 0;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 61000204
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 0;
	//regd - 01C00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46E36493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 0;
}

static void exchange_dcon_dcoutput_N30dBm(void)
{
	//reg1 - 0001E825
	hwp_rf_reg->rf_reg_1.DCDC_Output_TX = 1;
	hwp_rf_reg->rf_reg_1.DCDC_Output_RX = 1;
	//regb - DB184000
	hwp_rf_reg->rf_reg_b.VDD_RF_Regulator_Voltage = 2;
	hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage = 1;
	hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage = 0;
	hwp_rf_reg->rf_reg_b.VDD_DIV2_Reg_Bypass = 0;
	//regc - 61000304
	hwp_rf_reg->rf_reg_c.VDD_RF2_Regulator_Voltage_3V = 4;
	//regd - 01C00DB0
	hwp_rf_reg->rf_reg_d.ICTL_PA1 = 0;
	hwp_rf_reg->rf_reg_d.ICTL_PA2 = 0;
	hwp_rf_reg->rf_reg_d.ISEL_0PA = 0;
	hwp_rf_reg->rf_reg_d.VCTL_0PA = 7;
	//rege - 46E36493
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_RX = 7;
	hwp_rf_reg->rf_reg_e.LO_Buffer_current_TX = 0;
}


void rf_power_exchange(uint8_t power_set)
{
	if(power_set == DCOFF_RF3V3_8dBm)
	{
		exchange_dcoff_rf3V3_8dBm();
	}
	else if(power_set == DCOFF_RF3V3_4dBm )
	{
		exchange_dcoff_rf3V3_4dBm();
	}
	else if(power_set == DCOFF_RF3V3_2dBm)
	{
		exchange_dcoff_rf3V3_2dBm();
	}
	else if(power_set == DCOFF_RF1V8_2dBm)
	{
		exchange_dcoff_rf1V8_2dBm();
	}
	else if(power_set == DCON_RF3V3_8dBm)
	{
		exchange_dcon_rf3V3_8dBm();
	}
	else if(power_set == DCON_RF3V3_4dBm)
	{
		exchange_dcon_rf3V3_4dBm();
	}
	else if(power_set == DCON_RF3V3_N2dBm)
	{
		exchange_dcon_rf3V3_N2dBm();
	}
	else if(power_set == DCON_DCOUTPUT_2dBm)
	{
		exchange_dcon_dcoutput_2dBm();
	}
	else if(power_set == DCON_DCOUTPUT_0dBm)
	{
		exchange_dcon_dcoutput_0dBm();
	}
	else if(power_set == DCON_DCOUTPUT_N2dBm)
	{
		exchange_dcon_dcoutput_N2dBm();
	}
	else if(power_set == DCON_DCOUTPUT_N5dBm)
	{
		exchange_dcon_dcoutput_N5dBm();
	}
	else if(power_set == DCON_DCOUTPUT_N10dBm)
	{
		exchange_dcon_dcoutput_N10dBm();
	}
	else if(power_set == DCON_DCOUTPUT_N15dBm)
	{
		exchange_dcon_dcoutput_N15dBm();
	}
	else if(power_set == DCON_DCOUTPUT_N20dBm)
	{
		exchange_dcon_dcoutput_N20dBm();
	}
	else if(power_set == DCON_DCOUTPUT_N30dBm)
	{
		exchange_dcon_dcoutput_N30dBm();
	}
	else
	{
		LOG_RAW("rf_power_exchange param error\r\n");
	}
	#if (defined BX_TEMP_SENSOR) && (BX_TEMP_SENSOR == 1) 
	init_rf_temp_adjust_in_power_exchange();
	refresh_rf_regs_in_lp();
	#endif
	#if (defined BX_BATTERY_MONITOR) && (BX_BATTERY_MONITOR == 1) 
	//由于根据bit修改，所以电压部分不用再调整
	#endif
	modem_vcocali_start();
}

