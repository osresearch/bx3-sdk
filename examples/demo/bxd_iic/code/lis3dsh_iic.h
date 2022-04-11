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

#ifndef LIS3DSH_IIC_H_
#define LIS3DSH_IIC_H_



#include "bx_kernel.h"


extern uint32_t m_len_sent;
extern uint32_t m_cnt_10ms;
extern uint8_t m_data_array[250];
extern uint16_t   m_conn_handle;

extern uint8_t iic_test_buf[2];

void iic_read_lis3dsh(int reg,uint8_t *data_buf,uint8_t len);
void iic_write_lis3dsh(int reg,uint8_t *data_buf,uint8_t len);

#endif //BLE_USER_PROFILE_SERVER

