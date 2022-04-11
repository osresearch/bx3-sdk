/**
 ****************************************************************************************
 *
 * @file diss.h
 *
 * @brief Header file - Device Information Service Server.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef MPU9250_IIC_H_
#define MPU9250_IIC_H_


#include "bxs_iic.h"
#include "bx_kernel.h"


extern uint32_t m_len_sent;
extern uint32_t m_cnt_10ms;
extern uint8_t m_data_array[250];
extern uint16_t   m_conn_handle;

extern uint8_t AK8963_data[1];
extern uint8_t iic_test_buf[6];
extern short gx,gz,gy;
extern short ax,ay,az;
extern short mx,my,mz;
extern float temp;
extern float pitch,roll,yaw;

void IIC_Init(void);
uint8_t iic_read_mpu9250( uint8_t addr, uint8_t reg, uint8_t len, uint8_t * buf );
uint8_t iic_write_mpu9250( uint8_t addr, uint8_t reg, uint8_t len, uint8_t * buf );
u8 MPU_Get_Gyroscope( short * gx, short * gy, short * gz );
u8 MPU_Get_Accelerometer( short * ax, short * ay, short * az );
u8 MPU_Get_Magnetometer( short * mx, short * my, short * mz );
short MPU_Get_Temperature( void );
void mpu9250_delay_ms( uint32_t num_ms );


#endif //BLE_USER_PROFILE_SERVER

