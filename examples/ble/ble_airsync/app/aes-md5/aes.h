#ifndef __AES_H
#define __AES_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stdint.h"


#ifdef __cplusplus
    extern "C" {
#endif

#define AES_KEY_LENGTH    128

#define AES_MODE_ECB    0
#define AES_MODE_CBC    1
#define AES_MODE        AES_MODE_CBC

void AES_Init(const void *pKey);

void  AES_Encrypt(const unsigned char *pPlainText, unsigned char *pCipherText, 
                 unsigned int nDataLen, const unsigned char *pIV);

void AES_Decrypt(unsigned char *pPlainText, const unsigned char *pCipherText, 
                 unsigned int nDataLen, const unsigned char *pIV);

unsigned char app_data_encode_aes(char *input, char *output, unsigned short *slen);
unsigned char app_data_decode_aes(unsigned char *input, char *output, unsigned short *slen);
unsigned int AES_Encrypt_PKCS7(const unsigned char *pPlainText, unsigned char *pCipherText, 
                 unsigned int nDataLen, const unsigned char *pIV);
unsigned int AES_get_length(unsigned int length);
//void AES_free(unsigned char* p);
#ifdef __cplusplus
    }
#endif


#endif    // __AES_H
