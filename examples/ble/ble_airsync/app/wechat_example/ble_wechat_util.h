
#ifndef BLE_WECHAT_UTIL
#define BLE_WECHAT_UTIL

//#include <hal_types.h>
#include <string.h>
#include <stdint.h>


#define PRODUCT_TYPE_UNKNOWN 0
#define PRODUCT_TYPE_MPBLEDEMO2 1


#define ARGS_ITEM_SET(ARGS_TYPE, ARGS_POINTER, ITEM_NAME, ITEM_VALUE)	\
		do {	\
				ARGS_TYPE *tmp = (ARGS_TYPE *)ARGS_POINTER;	\
				tmp->ITEM_NAME = ITEM_VALUE;	\
		} while(0)


typedef struct
{
		unsigned char bMagicNumber;
		unsigned char bVer;
		unsigned short nLength;
		unsigned short nCmdId;
		unsigned short nSeq;
} BpFixHead;


unsigned short htons(unsigned short val);
unsigned short ntohs(unsigned short val);
unsigned long t_htonl(unsigned long h);
unsigned long t_ntohl(unsigned long n);

#endif
