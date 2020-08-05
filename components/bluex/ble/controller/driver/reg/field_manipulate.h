/**
  ******************************************************************************
  * @file   :   .h
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FIELD_MANIPULATE_H__
#define __FIELD_MANIPULATE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include <stdint.h>

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define REG_BIT_RD( reg, bit_idx )                      ( ( ( reg ) >> ( bit_idx ) ) & 0x1 )
#define REG_FIELD_RD( reg, field )                      ( ( ( reg ) & ( field##_MASK ) ) >> ( field##_POS ) )
#define FIELD_BUILD( field, val )                       ( ( val ) << ( field##_POS ) & ( field##_MASK ) )
#define FIELD_RD( base, member, field )                 ( ( ( ( base ) -> member ) & ( field##_MASK ) ) >> ( field##_POS ) )

#define REG_FIELD_WR(reg,field,val)     \
        do{                             \
        uint32_t old_val = (reg);       \
        uint32_t new_val = ((val)<<(field##_POS)&(field##_MASK))|(old_val &~(field##_MASK));\
        (reg)= new_val;                 \
    }while(0)

#define REG_BIT_WR(reg,bit_idx,val)     \
    do{                                 \
        uint32_t old_val = (reg);       \
        uint32_t new_val = (((val)<<(bit_idx))|(old_val &~(1<<(bit_idx))));\
        (reg) = new_val;                \
    }while(0)

#define FIELD_WR(base,member,field,val) \
    do{                                 \
        uint32_t old_val = (base)->member;\
        uint32_t new_val = ((val)<<(field##_POS)&(field##_MASK))|(old_val &~(field##_MASK));\
        (base)->member = new_val;       \
    }while(0)
    
/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __FIELD_MANIPULATE_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
