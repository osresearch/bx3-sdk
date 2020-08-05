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
#ifndef __HW_ECC_TYPEDEF_H__
#define __HW_ECC_TYPEDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported define -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/
typedef enum
{
	ECC_Idle = 0,
	ECC_Busy
}HW_ECC_START_BUSY_FIELD;

typedef enum
{
	With_Inversion = 0,
	Without_Inversion
}HW_ECC_WO_INV_FIELD;

typedef enum
{
	Full_ECC_Calc = 0,
	Multiply_Calc,
	ECC_Smpl_Calc,
	Jcb_Add_Calc,
	Jcb_Dble_Calc,
	Gf_Inv_Calc
}HW_ECC_START_SEL_FIELD;

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __HW_ECC_TYPEDEF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
