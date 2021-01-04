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
#ifndef __APOLLO_00_LL_CLK_H__
#define __APOLLO_00_LL_CLK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "apollo_00_reg.h"


/* exported types ------------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

#define BX_CLK_GPIO_ON()        ( BX_SET_BIT(BX_PER->CLKG1,PER_CLKG1_SET_GPIO) )
#define BX_CLK_GPIO_OFF()       ( BX_SET_BIT(BX_PER->CLKG1,PER_CLKG1_CLR_GPIO) )

#define BX_CLK_TIM0_ON()        ( BX_SET_BIT(BX_CPU->CLKG1,CPU_CLKG1_SET_TIM0) )
#define BX_CLK_TIM0_OFF()       ( BX_SET_BIT(BX_CPU->CLKG1,CPU_CLKG1_CLR_TIM0) )


/* exported functions --------------------------------------------------------*/

/* exported include ----------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* __APOLLO_00_LL_CLK_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

