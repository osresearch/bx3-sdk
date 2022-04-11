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
 
 #include "mpu9250_iic.h"
 #include "bxd_iic.h"
 #include "plf.h"
 #include "bx_pm.h"
 
 uint8_t AK8963_data[1] = {0x11};
 uint8_t iic_test_buf[6];
 short gx,gy,gz;
 short ax,ay,az;
 short mx,my,mz;
 float temp;
 float pitch,roll,yaw;
 
//初始化iic
void IIC_Init()
{
  bx_pm_lock( BX_PM_IIC );
  bxd_iic_open( BX_IIC0 );
  bxd_iic_set_scl( BX_IIC0, 2 );
  bxd_iic_set_sda( BX_IIC0, 3 );
  bxd_iic_set_speed( BX_IIC0, BX_IIC_SPEED_STANDARD );
  bxd_iic_set_addr_bit( BX_IIC0, BX_IIC_ADDR_BIT_7B );
  bxd_iic_set_mode( BX_IIC0, BX_IIC_MODE_MASTER );
}

//u8 MPU9250_Init(void)
//{
//  return 0;
//}
 
uint8_t iic_read_mpu9250(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
//	bx_set( bxs_iic0_id(), BXP_SUB_ADDR, reg, 0 );
//	bx_call( bxs_iic0_id(), BXM_READ, (uint32_t)data_buf, len);
	
	bxd_iic_read(BX_IIC0,addr,reg,(u8 *)(uint32_t)buf,(u32)len);
  
  return 0;

}
 
uint8_t iic_write_mpu9250(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
//	bx_set( bxs_iic0_id(), BXP_SUB_ADDR, reg, 0 );
//	bx_call( bxs_iic0_id(), BXM_WRITE, (uint32_t)data_buf, len);

	bxd_iic_write(BX_IIC0,addr,reg,buf,(u32)len);
  
  return 0;
}

////得到陀螺仪值（原始值）
////gx,gy,gz:陀螺仪x,y,z轴的原始读数（带符号）
////返回值：0,成功
////  其他，错误代码
//u8 MPU_Get_Gyroscope( short * gx, short * gy, short * gz )
//{
//    u8 buf[6], res;
//    res = iic_read_mpu9250( 0xd1, 0x43, 6, buf );
//    if( res == 0 ) {
//        *gx = ( ( u16 )buf[0] << 8 ) | buf[1];
//        *gy = ( ( u16 )buf[2] << 8 ) | buf[3];
//        *gz = ( ( u16 )buf[4] << 8 ) | buf[5];
//    }
//    return res;;
//}

////得到加速度的值（原始值）
////ax,ay,az:加速度x,y,z轴的原始读数（带符号）
////返回值：0，成功
////  其他，错误代码
//u8 MPU_Get_Accelerometer( short * ax, short * ay, short * az )
//{
//    u8 buf[6], res;
//    res = iic_read_mpu9250( 0xd1, 0x3B, 6, buf );
//    if( res == 0 ) {
//        *ax = ( ( u16 )buf[0] << 8 ) | buf[1];
//        *ay = ( ( u16 )buf[2] << 8 ) | buf[3];
//        *az = ( ( u16 )buf[4] << 8 ) | buf[5];
//    }
//    return res;;
//}

////得到磁力计值（原始值）
////mx,my,mz:磁力计x,y,z轴的原始读数（带符号）
////返回值：0，成功
////  其他，错误代码
//u8 MPU_Get_Magnetometer( short * mx, short * my, short * mz )
//{
//  u8 buf[6],res;
//  res = iic_read_mpu9250(0x19,0x03,6,buf);
//  if( res == 0 ) {
//        *mx = ( ( u16 )buf[1] << 8 ) | buf[0];
//        *my = ( ( u16 )buf[3] << 8 ) | buf[2];
//        *mz = ( ( u16 )buf[5] << 8 ) | buf[4];
//    }
//    iic_write_mpu9250(0x19,0x0A,1,AK8963_data);//AK8963每次读完以后都需要重新设置为单次测量模式，否则数据不会更新
//    return res;
//}

////得到温度值
////返回值：温度值（扩大了100倍）
//short MPU_Get_Temperature( void )
//{
//  u8 buf[2];
//  short raw;
//  float temp;
//  iic_read_mpu9250(0xd1,0x41,2,buf);
//  raw = ( ( u16 )buf[0] << 8 ) | buf[1];
//  temp = 21 + ( ( double )raw ) / 333.87;
//  return temp* 100;;  
//}

void mpu9250_delay_ms(uint32_t num_ms)
{
   BX_DELAY_US(num_ms*1000);
//   u32 i;
//	 for(i=0;i<num_ms;i++) BX_DELAY_US(1000);
}


/// @} GLPS
