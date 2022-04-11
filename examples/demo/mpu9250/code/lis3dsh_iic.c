/**
 ****************************************************************************************
 *
 * @file glps.c
 *
 * @brief Glucose Profile Sensor implementation.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @addtogroup GLPS
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
 
 #include "lis3dsh_iic.h"
 #include "bxd_iic.h"
 
 uint8_t iic_test_buf[2];
 
void iic_read_lis3dsh(int reg,uint8_t *data_buf,uint8_t len)
{
//	bx_set( bxs_iic0_id(), BXP_SUB_ADDR, reg, 0 );
//	bx_call( bxs_iic0_id(), BXM_READ, (uint32_t)data_buf, len);
	
	bxd_iic_read(BX_IIC0,0x3d,reg,(u8 *)(uint32_t)data_buf,len);

}
 
void iic_write_lis3dsh(int reg,uint8_t *data_buf,uint8_t len)
{
//	bx_set( bxs_iic0_id(), BXP_SUB_ADDR, reg, 0 );
//	bx_call( bxs_iic0_id(), BXM_WRITE, (uint32_t)data_buf, len);

	bxd_iic_write(BX_IIC0,0x3d,reg,(u8 *)(uint32_t)data_buf,len);
}
 



/// @} GLPS
