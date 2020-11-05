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

#define TAG_MMOpen_StepDataItem_Step									0x08
#define TAG_MMOpen_StepDataItem_Timestamp								0x10
#define TAG_MMOpen_StepDataItem_RTCYear									0x18
#define TAG_MMOpen_StepDataItem_RTCMonth								0x20
#define TAG_MMOpen_StepDataItem_RTCDay									0x28
#define TAG_MMOpen_StepDataItem_RTCHour									0x30
#define TAG_MMOpen_StepDataItem_RTCMinute								0x38
#define TAG_MMOpen_StepDataItem_RTCSecond								0x40

const uint8_t data[] = {0x08, 0x0b, 0x10, 0xf4, 0x8f, 0x89, 0x87, 0x05};

MMOpen_StepDataItem *epb_mmopen_unpack_step_data_item(const uint8_t *buf, int buf_len)
{
	Epb epb;
	epb_unpack_init(&epb, buf, buf_len);

	MMOpen_StepDataItem *item = (MMOpen_StepDataItem *)malloc(sizeof(MMOpen_StepDataItem));
	memset(item, 0, sizeof(MMOpen_StepDataItem));

	item->step = epb_get_uint32(&epb, TAG_MMOpen_StepDataItem_Step);

	if (epb_has_tag(&epb, TAG_MMOpen_StepDataItem_Timestamp)) {
		item->timestamp = epb_get_uint32(&epb, TAG_MMOpen_StepDataItem_Timestamp);
		item->has_timestamp = true;
	}

	if (epb_has_tag(&epb, TAG_MMOpen_StepDataItem_RTCYear)) {
		item->rtc_year = epb_get_uint32(&epb, TAG_MMOpen_StepDataItem_RTCYear);
		item->has_rtc_year = true;
	}

	if (epb_has_tag(&epb, TAG_MMOpen_StepDataItem_RTCMonth)) {
		item->rtc_month = epb_get_uint32(&epb, TAG_MMOpen_StepDataItem_RTCMonth);
		item->has_rtc_month = true;
	}

	if (epb_has_tag(&epb, TAG_MMOpen_StepDataItem_RTCDay)) {
		item->rtc_day = epb_get_uint32(&epb, TAG_MMOpen_StepDataItem_RTCDay);
		item->has_rtc_day = true;
	}

	if (epb_has_tag(&epb, TAG_MMOpen_StepDataItem_RTCHour)) {
		item->rtc_hour = epb_get_uint32(&epb, TAG_MMOpen_StepDataItem_RTCHour);
		item->has_rtc_hour = true;
	}

	if (epb_has_tag(&epb, TAG_MMOpen_StepDataItem_RTCMinute)) {
		item->rtc_minute = epb_get_uint32(&epb, TAG_MMOpen_StepDataItem_RTCMinute);
		item->has_rtc_minute = true;
	}

	if (epb_has_tag(&epb, TAG_MMOpen_StepDataItem_RTCSecond)) {
		item->rtc_second = epb_get_uint32(&epb, TAG_MMOpen_StepDataItem_RTCSecond);
		item->has_rtc_second = true;
	}

	return item;
}

/*

int main(int argc, char **argv)
{
	MMOpen_StepDataItem *item = epb_mmopen_unpack_step_data_item(data, sizeof(data));
	printf("steps: %d\n", item->step);
	if (item->has_timestamp) {
		printf("timestamp: %d\n",  item->timestamp);
		printf("time: %s\n", ctime((time_t *)&item->timestamp));
	} 
	if (item->has_rtc_year) {
		printf("time: %d/%d/%d %d:%d:%d\n", item->rtc_year, item->rtc_month, item->rtc_day, item->rtc_hour, item->rtc_minute, item->rtc_second);
	}
	free(item);
	return 0;
}
*/
