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
 
 #include "lis3dsh_bxs_iic.h"
 
 uint8_t iic_test_buf[2];
 
void iic_read_lis3dsh(int reg,uint8_t *data_buf,uint8_t len)
{
	bx_set( bxs_iic0_id(), BXP_SUB_ADDR, reg, 0 );
	bx_call( bxs_iic0_id(), BXM_READ, (uint32_t)data_buf, len);

}
 
void iic_write_lis3dsh(int reg,uint8_t *data_buf,uint8_t len)
{
	bx_set( bxs_iic0_id(), BXP_SUB_ADDR, reg, 0 );
	bx_call( bxs_iic0_id(), BXM_WRITE, (uint32_t)data_buf, len);

}
 



/// @} GLPS
