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

#define IIC_TX_FIFO_LEN         (16)
#define IIC_RX_FIFO_LEN         (16)
/* exported types ------------------------------------------------------------*/
enum IIC_IRQ_ID_FIELD
{
    IIC_INTR_RX_UNDER = 0,
    IIC_INTR_RX_OVER,     // 1
    IIC_INTR_RX_FULL,
    IIC_INTR_TX_OVER,
    IIC_INTR_TX_EMPTY,
    IIC_INTR_RD_REQ,      // 5
    IIC_INTR_TX_ABORT,
    IIC_INTR_RX_DONE,
    IIC_INTR_ACTIVITY,
    IIC_INTR_STOP_DET,
    IIC_INTR_START_DET,   // 10
    IIC_INTR_GEN_CALL,
    IIC_INTR_RESTART_DET, // 12
    IIC_INTR_MAX
};

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

bx_err_t    bxd_iic_set_sda( void * hdl, u8 pin_num );
bx_err_t    bxd_iic_set_scl( void * hdl, u8 pin_num );

bx_err_t    bxd_iic_set_mode( void * hdl, u8 mode );
bx_err_t    bxd_iic_set_speed( void * hdl, u8 speed );
bx_err_t    bxd_iic_set_addr_bit( void * hdl, u8 addr_bit );
bx_err_t    bxd_iic_set_slave_addr( void * hdl, u16 slave_addr );


bx_err_t    bxd_iic_open( void * hdl );
bx_err_t    bxd_iic_close( void * hdl );

bx_err_t    bxd_iic_read( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len );
bx_err_t    bxd_iic_read_ex( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len,s32 timeout_ms );
bx_err_t    bxd_iic_write( void * hdl, u8 addr, u8 reg, u8 * buff, u32 len );
bx_err_t    bxd_iic_read_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len );
bx_err_t    bxd_iic_write_16( void * hdl, u8 addr, u16 reg, u8 * buff, u32 len );
bx_err_t    bxd_iic_slave_intr_read( void * hdl, u8 * buff, u32 len, void (*callback) (void*) );


#ifdef __cplusplus
}
#endif

#endif /* __BXD_IIC_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

