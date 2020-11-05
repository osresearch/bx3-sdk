
#include "ble_wechat_util.h"





#define BigLittleSwap16(A)  ((((uint16_t)(A) & 0xff00) >> 8) | \
                            (((uint16_t)(A) & 0x00ff) << 8))

 
#define BigLittleSwap32(A)  ((((uint32_t)(A) & 0xff000000) >> 24) | \
                            (((uint32_t)(A) & 0x00ff0000) >> 8) | \
                            (((uint32_t)(A) & 0x0000ff00) << 8) | \
                            (((uint32_t)(A) & 0x000000ff) << 24))

int checkCPUendian()
{
       union{
              unsigned long i;
              uint8_t s[4];
       }c;
 
       c.i = 0x12345678;
       return (0x12 == c.s[0]);
}

unsigned long t_htonl(unsigned long h)
{
       return checkCPUendian() ? h : BigLittleSwap32(h);
}
 
unsigned long t_ntohl(unsigned long n)
{

       return checkCPUendian() ? n : BigLittleSwap32(n);
}

unsigned short htons(unsigned short h)
{
       return checkCPUendian() ? h : BigLittleSwap16(h);
}
 
unsigned short ntohs(unsigned short n)
{
       return checkCPUendian() ? n : BigLittleSwap16(n);
}

/*turn an unsigned short value to big-endian value					*/
/*for example 0x1234 in the memory of X86 is 0x34 and 0x12	*/
/*then turn it to Network Byte Order is 0x12 and 0x34				*/

