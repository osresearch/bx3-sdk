#ifndef RF_POWER_SET_H_
#define RF_POWER_SET_H_
#include <stdint.h>

//------------------------------------------------------
//4.2V
//#define RF_18_8_4V2_DCOFF_RF3V3_8dBm
//#define RF_18_8_4V2_DCOFF_RF3V3_4dBm
//#define RF_18_8_4V2_DCOFF_RF3V3_2dBm
//#define RF_18_8_4V2_DCOFF_RF1V8_2dBm
//#define RF_18_8_4V2_DCON_RF3V3_8dBm
//#define RF_18_8_4V2_DCON_RF3V3_4dBm
//#define RF_18_8_4V2_DCON_RF3V3_N2dBm
//#define RF_18_8_4V2_DCOUTPUT_2dBm
//#define RF_18_8_4V2_DCOUTPUT_0dBm
//#define RF_18_8_4V2_DCOUTPUT_N2dBm
//#define RF_18_8_4V2_DCOUTPUT_N5dBm
//#define RF_18_8_4V2_DCOUTPUT_N10dBm
//#define RF_18_8_4V2_DCOUTPUT_N15dBm
//#define RF_18_8_4V2_DCOUTPUT_N20dBm
//#define RF_18_8_4V2_DCOUTPUT_N30dBm

//3.3V
//#define RF_18_8_3V3_DCOFF_RF3V3_8dBm
//#define RF_18_8_3V3_DCOFF_RF3V3_4dBm
//#define RF_18_8_3V3_DCOFF_RF3V3_2dBm
//#define RF_18_8_3V3_DCOFF_RF1V8_2dBm
//#define RF_18_8_3V3_DCON_RF3V3_8dBm
//#define RF_18_8_3V3_DCON_RF3V3_4dBm
//#define RF_18_8_3V3_DCON_RF3V3_N2dBm
//#define RF_18_8_3V3_DCOUTPUT_2dBm
//#define RF_18_8_3V3_DCOUTPUT_0dBm
#define RF_18_8_3V3_DCOUTPUT_N2dBm
//#define RF_18_8_3V3_DCOUTPUT_N5dBm
//#define RF_18_8_3V3_DCOUTPUT_N10dBm
//#define RF_18_8_3V3_DCOUTPUT_N15dBm
//#define RF_18_8_3V3_DCOUTPUT_N20dBm
//#define RF_18_8_3V3_DCOUTPUT_N30dBm

//custom
//2416
//#define BX2416_IDLE_MODE
//#define RF_18_8_3V3_32M_DCOFF_RF3V3_SINGLE_3dBm
//------------------------------------------------------



#define RF_REG_0        *(volatile uint32_t*)0x20201070
#define RF_REG_1        *(volatile uint32_t*)0x20201074
#define RF_REG_2        *(volatile uint32_t*)0x20201078
#define RF_REG_3        *(volatile uint32_t*)0x2020107C
#define RF_REG_4        *(volatile uint32_t*)0x20201080
#define RF_REG_5        *(volatile uint32_t*)0x20201084
#define RF_REG_6        *(volatile uint32_t*)0x20201088
#define RF_REG_7        *(volatile uint32_t*)0x2020108C
#define RF_REG_8        *(volatile uint32_t*)0x20201090
#define RF_REG_9        *(volatile uint32_t*)0x20201094
#define RF_REG_a        *(volatile uint32_t*)0x20201098
#define RF_REG_b        *(volatile uint32_t*)0x2020109C
#define RF_REG_c        *(volatile uint32_t*)0x202010A0
#define RF_REG_d        *(volatile uint32_t*)0x202010A4
#define RF_REG_e        *(volatile uint32_t*)0x202010A8
#define RF_REG_f        *(volatile uint32_t*)0x202010AC


void rf_18_8_4v2_dcoff_rf3v3_8dbm(void);
void rf_18_8_4v2_dcoff_rf3v3_4dbm(void);
void rf_18_8_4v2_dcoff_rf3v3_2dbm(void);
void rf_18_8_4v2_dcoff_rf1v8_2dbm(void);
void rf_18_8_4v2_dcon_rf3v3_8dbm(void);
void rf_18_8_4v2_dcon_rf3v3_4dbm(void);
void rf_18_8_4v2_dcon_rf3v3_n2dbm(void);
void rf_18_8_4v2_dcon_dcoutput_2dbm(void);
void rf_18_8_4v2_dcon_dcoutput_0dbm(void);
void rf_18_8_4v2_dcon_dcoutput_n2dbm(void);
void rf_18_8_4v2_dcon_dcoutput_n5dbm(void);
void rf_18_8_4v2_dcon_dcoutput_n10dbm(void);
void rf_18_8_4v2_dcon_dcoutput_n15dbm(void);
void rf_18_8_4v2_dcon_dcoutput_n20dbm(void);
void rf_18_8_4v2_dcon_dcoutput_n30dbm(void);

void rf_18_8_3v3_dcoff_rf3v3_8dbm(void);
void rf_18_8_3v3_dcoff_rf3v3_4dbm(void);
void rf_18_8_3v3_dcoff_rf3v3_2dbm(void);
void rf_18_8_3v3_dcoff_rf1v8_2dbm(void);
void rf_18_8_3v3_dcon_rf3v3_8dbm(void);
void rf_18_8_3v3_dcon_rf3v3_4dbm(void);
void rf_18_8_3v3_dcon_rf3v3_n2dbm(void);
void rf_18_8_3v3_dcon_dcoutput_2dbm(void);
void rf_18_8_3v3_dcon_dcoutput_0dbm(void);
void rf_18_8_3v3_dcon_dcoutput_n2dbm(void);
void rf_18_8_3v3_dcon_dcoutput_n5dbm(void);
void rf_18_8_3v3_dcon_dcoutput_n10dbm(void);
void rf_18_8_3v3_dcon_dcoutput_n15dbm(void);
void rf_18_8_3v3_dcon_dcoutput_n20dbm(void);
void rf_18_8_3v3_dcon_dcoutput_n30dbm(void);

void rf_18_8_3v3_32m_dcoff_rf3v3_single_3dbm(void);
void test_rf(void);

void rf_power_setting(void);
void refresh_rf_param_with_ro( uint32_t ro );


#endif


