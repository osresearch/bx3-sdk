#ifndef __MD5_H__
#define __MD5_H__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stdint.h"


#define SINGLE_ONE_BIT 0x80
#define BLOCK_SIZE 512
#define MOD_SIZE 448
#define APP_SIZE 64
#define BITS 8
  // MD5 Chaining Variable
#define A 0x67452301UL
#define B 0xEFCDAB89UL
#define C 0x98BADCFEUL
#define D 0x10325476UL

typedef struct
{
    char *str;
    uint32_t len;
}MD5String;
int32_t md5 ( char *argv, uint8_t *md5_32);
#endif
