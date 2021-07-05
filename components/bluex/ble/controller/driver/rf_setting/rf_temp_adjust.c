#include "rf_temp_adjust.h"
#include "plf.h"
#include "log.h"
#include "rf_reg_typedef.h"
#include "sys_sleep.h"
#include "reg_ble_mdm.h"
#include "ll.h"
#include "rtc.h"
#include "rf_reg_settings.h"
#include "app_adc_utils.h"
#include "modem.h"
#include "rf_power_set.h"
#include "log.h"

/*
 *  schmitt TYPEDEF
 ****************************************************************************************	
 */
#define SMT_TAB_SIZE    2
//goal 0 threshold
#define GOAL1_L   -5
#define GOAL1_H   5
//goal 1 threshold
#define GOAL2_L   45
#define GOAL2_H   55
/*
 *  RF TYPEDEF
 ****************************************************************************************			
 */

//#define TEMP_TEST		MODE_BELOW0//MODE_BELOW0/MODE_NORMAL/MODE_OVER50
typedef int16_t smt_t;	//schmitt value
extern int32_t adc_cp_RO;
static temp_mode_t mode_last;
typedef enum
{
    SCHMITT_IN_LOW,
    SCHMITT_IN_HIGH,
}smt_stat_t;	

typedef struct			
{			
    smt_t       goal_l;
    smt_t       goal_h;
    smt_stat_t  current;
}schmitt_t;

#define DISPLAY_PERIOD  1000
#define portMAX_32_BIT_NUMBER       (0xffffffff)

#define REG4_10_9   hwp_rf_reg->rf_reg_4.VDD_AWO_Sleep
#define REG9_22_20  hwp_rf_reg->rf_reg_9.RX_Mixer_LO_Bias_Voltage
#define REGA_6_4    hwp_rf_reg->rf_reg_a.LNA_I_Control_1
#define REGA_2_0    hwp_rf_reg->rf_reg_a.LNA_V_Contro
#define REGD_31_29  hwp_rf_reg->rf_reg_d.ICTL_PA1
#define REGD_28_26  hwp_rf_reg->rf_reg_d.ICTL_PA2
#define REGD_24_22  hwp_rf_reg->rf_reg_d.VCTL_0PA
#define REGE_5_3    hwp_rf_reg->rf_reg_e.VCO_Current_for_RX
#define REGE_11_9   hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_RX
#define REGE_2_0    hwp_rf_reg->rf_reg_e.VCO_Current_for_TX
#define REGE_8_6    hwp_rf_reg->rf_reg_e.VCO_Buffer_Current_for_TX
#define REG0_29_28  hwp_rf_reg->rf_reg_0.xtal_current
#define REGB_15_14  hwp_rf_reg->rf_reg_b.VDD_PLL_Regulator_Voltage
#define REG6_6_3    hwp_rf_reg->rf_reg_6.Slow_Clock_Current
#define REG4_31_31  hwp_rf_reg->rf_reg_4.Sleep_Regulator

#define REGE_25_25  hwp_rf_reg->rf_reg_e.DM_Sync_LP
#define REGD_2_0    hwp_rf_reg->rf_reg_d.R1_TX_1Mbps
#define REGE_14_12  hwp_rf_reg->rf_reg_e.Divide_by_2_current_for_TX
#define REGB_13_12  hwp_rf_reg->rf_reg_b.VDD_Div2_Regulator_Voltage
#define REGB_11_10  hwp_rf_reg->rf_reg_b.VDD_VCO_Regulator_Voltage
#define REG0_31_30  hwp_rf_reg->rf_reg_0.iboost_current
#define REGF_2_0    hwp_rf_reg->rf_reg_f.R1_RX_1Mbps
#define REG4_25_22  hwp_rf_reg->rf_reg_4.VSLP
#define REG6_9      hwp_rf_reg->rf_reg_6.LV_32K
#define REG0_19_21  hwp_rf_reg->rf_reg_0.freq_pulling

typedef struct
{
	uint8_t reg4_10_9   [MODE_MAX];
	uint8_t reg9_22_20  [MODE_MAX];
	uint8_t rega_6_4    [MODE_MAX];
	uint8_t rega_2_0    [MODE_MAX];
	uint8_t regd_31_29  [MODE_MAX];
	uint8_t regd_28_26  [MODE_MAX];
	uint8_t regd_24_22  [MODE_MAX];
	uint8_t rege_5_3    [MODE_MAX];
	uint8_t rege_11_9   [MODE_MAX];
	uint8_t rege_2_0    [MODE_MAX];
	uint8_t rege_8_6    [MODE_MAX];
	uint8_t reg0_29_28  [MODE_MAX];
	uint8_t regb_15_14  [MODE_MAX];
	uint8_t reg6_6_3    [MODE_MAX];
	uint8_t reg4_31_31  [MODE_MAX];
	uint8_t rege_25_25  [MODE_MAX];
	uint8_t regd_2_0  	[MODE_MAX];
	uint8_t rege_14_12  [MODE_MAX];
	uint8_t regb_13_12  [MODE_MAX];
	uint8_t regb_11_10  [MODE_MAX];
	uint8_t reg0_31_30  [MODE_MAX];
	uint8_t regf_2_0    [MODE_MAX];
	uint8_t reg4_25_22  [MODE_MAX];
	uint8_t reg6_9      [MODE_MAX];
	uint8_t reg0_19_21  [MODE_MAX];
}rf_adj_t;
/*
 * VARIABLE
 ****************************************************************************************
 */

schmitt_t smt_tab[SMT_TAB_SIZE]=
{
    {GOAL1_L , GOAL1_H , SCHMITT_IN_LOW},
    {GOAL2_L , GOAL2_H , SCHMITT_IN_HIGH},
};
rf_adj_t rf_adj;
int16_t current_temp=25;
#ifdef TEMP_TEST
temp_mode_t temp_mode=TEMP_TEST;
#else
temp_mode_t temp_mode=MODE_NORMAL;
#endif
uint16_t cur_deriv_calib[4];

/*
 * Schmitt tools
 ****************************************************************************************
 */
static uint8_t smt_get_range(smt_t val)
{
    smt_t current_goal;
    uint8_t result = 0;
    uint8_t i;
    //calc every channel output
    for(i=0;i<SMT_TAB_SIZE;i++)
    {
        current_goal = (smt_tab[i].current == SCHMITT_IN_LOW) ? smt_tab[i].goal_l : smt_tab[i].goal_h;
        if(val > current_goal)
        {
            smt_tab[i].current = SCHMITT_IN_LOW;
            result++;
        }
        else
        {
            smt_tab[i].current = SCHMITT_IN_HIGH;
        }
    }
    return result;
}
/*
 * RF tools
 ****************************************************************************************
 */
void init_rf_temp_adjust(void)
{
    uint8_t* b;
    b = rf_adj.reg4_10_9 ; b[0]=b[1]=b[2] = REG4_10_9 ;   b[MODE_BELOW0] =  0; //VDD_AWO_Sleep
    b = rf_adj.reg9_22_20; b[0]=b[1]=b[2] = REG9_22_20;   b[MODE_OVER50] -= 1; //RX_Mixer_LO_Bias_Voltage
    b = rf_adj.rega_6_4  ; b[0]=b[1]=b[2] = REGA_6_4  ;   b[MODE_OVER50] =  6; //LNA_I_Control_1
    b = rf_adj.rega_2_0  ; b[0]=b[1]=b[2] = REGA_2_0  ;   b[MODE_OVER50] =  6; //LNA_V_Contro
    b = rf_adj.regd_31_29; b[0]=b[1]=b[2] = REGD_31_29;   b[MODE_OVER50] += 1; //ICTL_PA1
    b = rf_adj.regd_28_26; b[0]=b[1]=b[2] = REGD_28_26;   b[MODE_OVER50] =  7; //ICTL_PA2
    b = rf_adj.regd_24_22; b[0]=b[1]=b[2] = REGD_24_22;   b[MODE_OVER50] -= 1; //VCTL_0PA
			
    b = rf_adj.rege_5_3  ; b[0]=b[1]=b[2] = REGE_5_3  ;   b[MODE_BELOW0] = 2;  // VCO_Current_for_RX
    b = rf_adj.rege_11_9 ; b[0]=b[1]=b[2] = REGE_11_9 ;   b[MODE_BELOW0] += 1; //VCO_Buffer_Current_for_RX
    b = rf_adj.rege_2_0  ; b[0]=b[1]=b[2] = REGE_2_0  ;   b[MODE_BELOW0] += 1;//b[MODE_BELOW0] += 3; VCO_Current_for_TX
    b = rf_adj.rege_8_6  ; b[0]=b[1]=b[2] = REGE_8_6  ;   b[MODE_BELOW0] += 1; //VCO_Buffer_Current_for_TX
	b = rf_adj.regb_15_14; b[0]=b[1]=b[2] = REGB_15_14;   b[MODE_BELOW0] = 1; //VDD_PLL_Regulator_Voltage
	b = rf_adj.reg6_6_3;   b[0]=b[1]=b[2] = REG6_6_3;     b[MODE_BELOW0] = 0x2; //Slow_Clock_Current
	//b = rf_adj.reg6_6_3;   b[0]=b[1]=b[2] = REG6_6_3;     b[MODE_BELOW0] = 0x0;
	b = rf_adj.reg0_29_28; b[0]=b[1]=b[2] = REG0_29_28;   b[MODE_BELOW0] = 1; //xtal_current 20200423 org:2
	b = rf_adj.reg4_31_31; b[0]=b[1]=b[2] = REG4_31_31;   b[MODE_BELOW0] = 0; //Sleep_Regulator
	b = rf_adj.rege_25_25; b[0]=b[1]=b[2] = REGE_25_25;   b[MODE_BELOW0] = 1; //DM_Sync_LP jian 20200522 org:0
	b = rf_adj.regd_2_0;   b[0]=b[1]=b[2] = REGD_2_0;     b[MODE_BELOW0] = 0; //R1_TX_1Mbps
	b = rf_adj.rege_14_12; b[0]=b[1]=b[2] = REGE_14_12;   b[MODE_BELOW0] = 7; //Divide_by_2_current_for_TX
	b = rf_adj.regb_13_12; b[0]=b[1]=b[2] = REGB_13_12;   b[MODE_BELOW0] = 1; //VDD_Div2_Regulator_Voltage
    b = rf_adj.reg0_31_30; b[0]=b[1]=b[2] = REG0_31_30;   b[MODE_BELOW0] = 0; //iboost_current
	b = rf_adj.regb_11_10; b[0]=b[1]=b[2] = REGB_11_10;   b[MODE_BELOW0] = 1; //VDD_VCO_Regulator_Voltage
	b = rf_adj.regf_2_0;   b[0]=b[1]=b[2] = REGF_2_0;     b[MODE_BELOW0] = 1;	//	R1_RX_1Mbps
	b = rf_adj.reg4_25_22; b[0]=b[1]=b[2] = REG4_25_22;   b[MODE_BELOW0] = 15; //VSLP for ZLG
	b = rf_adj.reg6_9;     b[0]=b[1]=b[2] = REG6_9;       b[MODE_BELOW0] = 0; //LV_32K for ZLG
	b = rf_adj.reg0_19_21; b[0]=b[1]=b[2] = REG0_19_21;   b[MODE_OVER50] = 0; //freq_pulling for ZLG
    //print
    current_temp = app_adc_tempSensor();

	#ifdef TEMP_TEST
	temp_mode = mode_last = TEMP_TEST;
	#else
	temp_mode = mode_last = (temp_mode_t)smt_get_range(current_temp);
//	LOG_V("temp_mode = %d", temp_mode);
	#endif
	if(temp_mode == 0)		
	{
			reg_set_xtal_current_below_temp0();
	}
	else		
	{
			reg_set_xtal_current_normal();
	}
	refresh_rf_regs_in_lp();
}			

void init_rf_temp_adjust_in_power_exchange(void)
{
	uint8_t* b;
	b = rf_adj.regd_31_29; b[0]=b[1]=b[2] = REGD_31_29;   b[MODE_OVER50] += 1; //ICTL_PA1
	b = rf_adj.regd_28_26; b[0]=b[1]=b[2] = REGD_28_26;   b[MODE_OVER50] =	7; //ICTL_PA2
	b = rf_adj.regd_24_22; b[0]=b[1]=b[2] = REGD_24_22;   b[MODE_OVER50] -= 1; //VCTL_0PA
	b = rf_adj.rege_5_3  ; b[0]=b[1]=b[2] = REGE_5_3  ;   b[MODE_BELOW0] = 2;  // VCO_Current_for_RX
	b = rf_adj.rege_11_9 ; b[0]=b[1]=b[2] = REGE_11_9 ;   b[MODE_BELOW0] += 1; //VCO_Buffer_Current_for_RX
	b = rf_adj.rege_2_0  ; b[0]=b[1]=b[2] = REGE_2_0  ;   b[MODE_BELOW0] += 1;//b[MODE_BELOW0] += 3; VCO_Current_for_TX
	b = rf_adj.rege_8_6  ; b[0]=b[1]=b[2] = REGE_8_6  ;   b[MODE_BELOW0] += 1; //VCO_Buffer_Current_for_TX
	b = rf_adj.regb_15_14; b[0]=b[1]=b[2] = REGB_15_14;   b[MODE_BELOW0] = 1; //VDD_PLL_Regulator_Voltage
	b = rf_adj.rege_25_25; b[0]=b[1]=b[2] = REGE_25_25;   b[MODE_BELOW0] = 1; //DM_Sync_LP jian 20200522 org:0
	b = rf_adj.regd_2_0;   b[0]=b[1]=b[2] = REGD_2_0;	  b[MODE_BELOW0] = 0; //R1_TX_1Mbps
	b = rf_adj.rege_14_12; b[0]=b[1]=b[2] = REGE_14_12;   b[MODE_BELOW0] = 7; //Divide_by_2_current_for_TX
	b = rf_adj.regb_13_12; b[0]=b[1]=b[2] = REGB_13_12;   b[MODE_BELOW0] = 1; //VDD_Div2_Regulator_Voltage
	b = rf_adj.regb_11_10; b[0]=b[1]=b[2] = REGB_11_10;   b[MODE_BELOW0] = 1; //VDD_VCO_Regulator_Voltage
}

void try_to_update_rf_param_with_temp(void)			
{			
    static uint32_t tick_count_last = 0;
    uint32_t tick_count_current = RTC_CURRENTCNT_GET();
    uint32_t tick_temp;
    if(tick_count_current > tick_count_last)
    {
        tick_temp = tick_count_current - tick_count_last;
    }
    else if(tick_count_current < tick_count_last)
    {
        tick_temp = (portMAX_32_BIT_NUMBER - tick_count_last) + tick_count_current;
    }
	if( tick_temp >= 0x8000 )	//0x8000 = 1s
    {
        tick_count_last = tick_count_current;
        handle_read_temp();
    }
}

void handle_read_temp(void)			
{
    current_temp = app_adc_tempSensor();
	#ifdef TEMP_TEST
	  temp_mode = TEMP_TEST;
	#else
	  temp_mode = (temp_mode_t)smt_get_range(current_temp);
	  //LOG_RAW("temp_mode = %d\r\n", temp_mode);
	#endif
    if( temp_mode != mode_last )
    {
        mode_last = temp_mode;
        refresh_rf_regs_in_lp();
    }
}

void refresh_rf_regs_in_lp(void)
{
	//case18.7
    //REG4_10_9  = rf_adj.reg4_10_9  [temp_mode];
    REG9_22_20 = rf_adj.reg9_22_20 [temp_mode];
    REGA_6_4   = rf_adj.rega_6_4   [temp_mode];
    REGA_2_0   = rf_adj.rega_2_0   [temp_mode];
    REGD_31_29 = rf_adj.regd_31_29 [temp_mode];
    REGD_28_26 = rf_adj.regd_28_26 [temp_mode];
    REGD_24_22 = rf_adj.regd_24_22 [temp_mode];
	
    REGE_5_3   = rf_adj.rege_5_3   [temp_mode];
    REGE_11_9  = rf_adj.rege_11_9  [temp_mode];
    REGE_2_0   = rf_adj.rege_2_0   [temp_mode];
    REGE_8_6   = rf_adj.rege_8_6   [temp_mode];
	REGB_15_14 = rf_adj.regb_15_14 [temp_mode];
	REG6_6_3   = rf_adj.reg6_6_3 [temp_mode];
	REG0_29_28 = rf_adj.reg0_29_28[temp_mode];
	
	REG4_31_31 = rf_adj.reg4_31_31[temp_mode];
	REGE_25_25 = rf_adj.rege_25_25[temp_mode];
	REGD_2_0   = rf_adj.regd_2_0[temp_mode];
	REGE_14_12 = rf_adj.rege_14_12[temp_mode];
	//REGB_13_12 = rf_adj.regb_13_12[temp_mode];
	REG0_31_30 = rf_adj.reg0_31_30[temp_mode];
	REGB_11_10 = rf_adj.regb_11_10[temp_mode];
    REGF_2_0   = rf_adj.regf_2_0[temp_mode];

	//当使用ZLG的参数时；需要开启
	#ifdef ZLG_RF
    REG4_25_22 = rf_adj.reg4_25_22[temp_mode];	//ZLG
    REG6_9 = rf_adj.reg6_9[temp_mode];			//ZLG
    REG0_19_21 = rf_adj.reg0_19_21[temp_mode];	//ZLG
    #endif
}

	
			
