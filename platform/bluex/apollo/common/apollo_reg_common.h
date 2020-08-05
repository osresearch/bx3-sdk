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
#ifndef __APOLLO_REG_COMMON_H__
#define __APOLLO_REG_COMMON_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* config ------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/
#define BX_SET_BIT(REG, BIT)                        ((REG) |= (BIT))

#define BX_CLR_BIT(REG, BIT)                        ((REG) &= ~(BIT))

#define BX_READ_BIT(REG, BIT)                       ((REG) & (BIT))

#define BX_CLR_REG(REG)                             ((REG) = (0x0))

#define BX_SET_REG(REG, VAL)                        ((REG) = (VAL))

#define BX_READ_REG(REG)                            ((REG))

#define BX_MODIFY_REG(REG, CLEARMASK, SETMASK)      BX_SET_REG((REG), (((BX_READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


//val cannot be type like "XX_T_XX"
#define BX_FIELD_WR(reg,field,val)                                                          \
    do{                                                                                     \
    uint32_t old_val = (reg);                                                               \
    uint32_t new_val = ((val)<<(field##_POS)&(field##_MASK))|(old_val &~(field##_MASK));    \
    (reg)= new_val;                                                                         \
}while(0)

#define BX_FIELD_RD(reg,field)                      (((reg)&(field##_MASK))>>(field##_POS))
    
/* exported functions --------------------------------------------------------*/



#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_REG_COMMON_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

