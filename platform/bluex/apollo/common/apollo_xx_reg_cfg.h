/**
  ******************************************************************************
  * @file   :   .h
  * @version:    
  * @author :
  * @brief  :   Just for Include Other Head File
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
#ifndef __APOLLO_XX_REG_H__
#define __APOLLO_XX_REG_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* config ------------------------------------------------------------------*/
#define USE_APOLLO_00 

/* includes ------------------------------------------------------------------*/


#if defined(USE_APOLLO_00)
  #include "apollo_00_reg.h"
#elif defined(USE_APOLLO_01)
  #include "apollo_01_reg.h"
#else
 #error "Please select the target device used in your application"
#endif

/* exported types ------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/



#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_XX_REG_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

