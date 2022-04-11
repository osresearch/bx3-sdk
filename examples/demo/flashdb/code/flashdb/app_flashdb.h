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
#ifndef __APP_FLASHDB_H__
#define __APP_FLASHDB_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"

/* config --------------------------------------------------------------------*/

/* exported paras ------------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void  app_fdb_init( void );

bx_err_t app_fdb_save( char * key, u8 * value, u32 value_size );
bx_err_t app_fdb_get( char * key, u8 * value, u32 value_size );


/* exported macros -----------------------------------------------------------*/
#define app_fdb_make_key(var)   (#var)
#define app_fdb_save_easy(var)  app_fdb_save( #var, (u8 *)&var, sizeof( var ) )
#define app_fdb_get_easy(var)   app_fdb_get( #var, (u8 *)&var, sizeof( var ) )

#ifdef __cplusplus
}
#endif

#endif /* __APP_FLASHDB_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
