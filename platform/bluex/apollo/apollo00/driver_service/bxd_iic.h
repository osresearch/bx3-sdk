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
#ifndef __BXD_IIC_H__
#define __BXD_IIC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "bx_iic_type_def.h"
#include "apollo_00_reg.h"

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t    bxd_iic_set_sda( void * hdl, u8 pin_num );
bx_err_t    bxd_iic_set_scl( void * hdl, u8 pin_num );

bx_err_t    bxd_iic_set_mode( void * hdl, u8 mode );
bx_err_t    bxd_iic_set_speed( void * hdl, u8 speed );
bx_err_t    bxd_iic_set_addr_bit( void * hdl, u8 addr_bit );


bx_err_t    bxd_iic_open( void * hdl );
bx_err_t    bxd_iic_close( void * hdl );

bx_err_t    bxd_iic_read( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len );
bx_err_t    bxd_iic_read_ex( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len,s32 timeout_ms );
bx_err_t    bxd_iic_write( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len );
bx_err_t    bxd_iic_read_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len );
bx_err_t    bxd_iic_write_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len );


#ifdef __cplusplus
}
#endif

#endif /* __BXD_IIC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
