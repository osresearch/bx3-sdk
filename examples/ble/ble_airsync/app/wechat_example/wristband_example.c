//  wristband_example.c
//  WeChat Embedded
//
//  Created by harlliu on 14-04-24.
//  Copyright 2014 Tencent. All rights reserved.
//

//  Version : 0.7.5

#include <stdio.h>
//#include <stdint.h>
#include "hal_types.h"
#include <stdlib.h>
#include <string.h>
#include "epb_WristBand.h"

uint8_t data[] = "Wechat Wristband Proto";

/*

int main(int argc, char **argv)
{
	int count = 5;
	MMOpen_WristbandRequest *request = (MMOpen_WristbandRequest *)malloc(sizeof(MMOpen_WristbandRequest));
	memset(request, 0, sizeof(MMOpen_WristbandRequest));
	request->step_data_count = count;
	request->step_data = (MMOpen_StepDataItem *)malloc(sizeof(MMOpen_StepDataItem) * count);
	memset(request->step_data, 0, sizeof(MMOpen_StepDataItem) * count);

	for (int i=0; i<count; i++) {
		MMOpen_StepDataItem *item = request->step_data + i;

        item->step = 1000*(i+1);

		item->has_rtc_year = true;
		item->has_rtc_month = true;
		item->has_rtc_day = true;
		item->has_rtc_hour = true;
		item->has_rtc_minute = true;
		item->has_rtc_second = true;

		item->rtc_year = 2014;
		item->rtc_month = 6;
		item->rtc_day = 30;
		item->rtc_hour = 17;
		item->rtc_minute = 55;
		item->rtc_second = 0;
	}

	request->has_ext_data = true;
	request->ext_data.data = data;
	request->ext_data.len = sizeof(data);

	int len = epb_mmopen_wristband_request_pack_size(request);
	uint8_t *buf = (uint8_t *)malloc(len);
	int ret = epb_mmopen_pack_wristband_request(request, buf, len);
	printf("ret: %d\n", ret); //67
	printf("wristband request len: %d\n", len); //67
	for(int i=0; i<len; i++) {
		printf("%02x", buf[i]);
	} 
	//0a1008e80718de0f2006281e301138374000
	//0a1008d00f18de0f2006281e301138374000
	//0a1008b81718de0f2006281e301138374000
	//0a1008a01f18de0f2006281e301138374000
	//0a1008882718de0f2006281e301138374000
	//121757656368617420577269737462616e642050726f746f00

	printf("\n");

	free(request->step_data);
	free(request);
	free(buf);
	return 0;
}

*/
