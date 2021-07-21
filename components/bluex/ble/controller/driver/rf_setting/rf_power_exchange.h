#ifndef RF_POWER_EXCHANGE_H_
#define RF_POWER_EXCHANGE_H_
#include <stdint.h>

typedef enum{
	DCOFF_RF3V3_8dBm = 0,
	DCOFF_RF3V3_4dBm,
	DCOFF_RF3V3_2dBm,
	DCOFF_RF1V8_2dBm,
	DCON_RF3V3_8dBm,
	DCON_RF3V3_4dBm,
	DCON_RF3V3_N2dBm,
	DCON_DCOUTPUT_2dBm,
	DCON_DCOUTPUT_0dBm,
	DCON_DCOUTPUT_N2dBm,
	DCON_DCOUTPUT_N5dBm,
	DCON_DCOUTPUT_N10dBm,
	DCON_DCOUTPUT_N15dBm,
	DCON_DCOUTPUT_N20dBm,
	DCON_DCOUTPUT_N30dBm,
}RF_POWER_EXCHANGE;

void rf_power_exchange(uint8_t power_set);

#endif
