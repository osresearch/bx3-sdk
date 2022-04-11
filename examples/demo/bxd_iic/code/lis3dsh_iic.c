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
 uint8_t addr=0x3d;
 
void iic_read_lis3dsh(int reg,uint8_t *data_buf,uint8_t len)
{

	bxd_iic_read(BX_IIC0,addr,reg,data_buf,len);

}
 
void iic_write_lis3dsh(int reg,uint8_t *data_buf,uint8_t len)
{

	bxd_iic_write(BX_IIC0,addr,reg,data_buf,len);

}
 



/// @} GLPS
