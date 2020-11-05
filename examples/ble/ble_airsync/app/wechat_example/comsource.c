/*
*	WeChat mpbledemo2 common source
*
*	modified  by anqiren  2014/12/02  V1.0bat
*
**/

#include <stdio.h>
#include <string.h>
#include "comsource.h"


// Length of bd addr as a string
#define B_ADDR_STR_LEN                        15

/*********************************************************************
 * @fn      Read_Mac
 *
 * @brief   ������MAC  
 *
 * @param   mac��Ҫ���浽��λ�ã���Ҫ6���ֽڴ�С
 *
 * @return  none
 */

void Read_Mac(uint8 *ownAddress)   
{   
  ownAddress[0] = *(unsigned char *)(0x7813);                 
  ownAddress[1] = *(unsigned char *)(0x7812); 
  ownAddress[2] = *(unsigned char *)(0x7811);             
  ownAddress[3] = *(unsigned char *)(0x7810); // ֱ��ָ��ָ������     
  ownAddress[4] = *(unsigned char *)(0x780F);    
  ownAddress[5] = *(unsigned char *)(0x780E);
} 

#if (defined HAL_LCD) && (HAL_LCD == TRUE)

/*********************************************************************
 * @fn      bdAddr2Str
 *
 * @brief   Convert Bluetooth address to string. Only needed when
 *          LCD display is used.
 *
 * @return  none
 */

char *bdAddr2Str( uint8 *pAddr )
{
  uint8       i;
  char        hex[] = "0123456789ABCDEF";
  static char str[B_ADDR_STR_LEN];
  char        *pStr = str;

  *pStr++ = '0';
  *pStr++ = 'x';

  // Start from end of addr
  pAddr += 6;

  for ( i = 6; i > 0; i-- )
  {
    *pStr++ = hex[*--pAddr >> 4];
    *pStr++ = hex[*pAddr & 0x0F];
  }

  *pStr = 0;

  return str;
}

#endif // (defined HAL_LCD) && (HAL_LCD == TRUE)