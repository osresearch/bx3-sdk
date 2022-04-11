#ifndef SC7A20_H
#define SC7A20_H

#include <stdbool.h>
#include <stdint.h>


#define SC7A20_IIC_ADDR				0x18//0x19

#define SC7A20_CHIP_ID_ADDRESS    (unsigned char)0x0F
#define SC7A20_CHIP_ID_VALUE      (unsigned char)0x11

#define  SL_SC7A20_CTRL_REG1      (unsigned char)0x20
#define  SL_SC7A20_CTRL_REG2      (unsigned char)0x21
#define  SL_SC7A20_CTRL_REG3      (unsigned char)0x22
#define  SL_SC7A20_CTRL_REG4      (unsigned char)0x23 
#define  SL_SC7A20_CTRL_REG5      (unsigned char)0x24
#define  SL_SC7A20_CTRL_REG6      (unsigned char)0x25

#define  SL_SC7A20_STATUS_REG     (unsigned char)0x27

#define  SL_SC7A20_OUT_X_L        (unsigned char)0x28
#define  SL_SC7A20_OUT_X_H        (unsigned char)0x29
#define  SL_SC7A20_OUT_Y_L        (unsigned char)0x2A
#define  SL_SC7A20_OUT_Y_H        (unsigned char)0x2B
#define  SL_SC7A20_OUT_Z_L        (unsigned char)0x2C
#define  SL_SC7A20_OUT_Z_H        (unsigned char)0x2D

#define  SL_SC7A20_FIFO_CTRL_REG  (unsigned char)0x2E
#define  SL_SC7A20_FIFO_SRC_REG   (unsigned char)0x2F

#define  SL_SC7A20_INT1_CFG    	  (unsigned char)0x30
#define  SL_SC7A20_INT1_SRC       (unsigned char)0x31
#define  SL_SC7A20_INT1_THS    	  (unsigned char)0x32
#define  SL_SC7A20_INT1_DURATION  (unsigned char)0x33

#define  SL_SC7A20_INT2_CFG    	  (unsigned char)0x34
#define  SL_SC7A20_INT2_SRC       (unsigned char)0x35
#define  SL_SC7A20_INT2_THS    	  (unsigned char)0x36
#define  SL_SC7A20_INT2_DURATION  (unsigned char)0x37
#define  SL_SC7A20_CLICK_CFG   	  (unsigned char)0x38
#define  SL_SC7A20_CLICK_SRC   	  (unsigned char)0x39
#define  SL_SC7A20_CLICK_THS   	  (unsigned char)0x3A
#define  SL_SC7A20_TIME_LIMIT     (unsigned char)0x3B
#define  SL_SC7A20_TIME_LATENCY   (unsigned char)0x3C
#define  SL_SC7A20_TIME_WINDOW    (unsigned char)0x3D
#define  SL_SC7A20_ACT_THS        (unsigned char)0x3E
#define  SL_SC7A20_ACT_DURATION   (unsigned char)0x3F
	
/*连续读取数据时的数据寄存器地址*/
#define  SL_SC7A20_DATA_OUT       (unsigned char)(SL_SC7A20_OUT_X_L|0X80)

/**********特殊功能寄存器**********/
/*非原厂技术人员请勿修改*/
#define  SL_SC7A20_MTP_ENABLE    	             0X00
#define  SL_SC7A20_MTP_CFG    	  (unsigned char)0x1E
#define  SL_SC7A20_MTP_VALUE   	  (unsigned char)0x05
#define  SL_SC7A20_SDOI2C_PU_CFG  (unsigned char)0x57
#define  SL_SC7A20_SDO_PU_MSK     (unsigned char)0x08
#define  SL_SC7A20_I2C_PU_MSK     (unsigned char)0x04
#define  SL_SC7A20_HR_ENABLE      (unsigned char)0X08
/*非原厂技术人员请勿修改*/


/***************数据更新速率**加速度计使能**********/
#define  SL_SC7A20_ODR_POWER_DOWN (unsigned char)0x00
#define  SL_SC7A20_ODR_1HZ        (unsigned char)0x17
#define  SL_SC7A20_ODR_10HZ       (unsigned char)0x27
#define  SL_SC7A20_ODR_25HZ       (unsigned char)0x37
#define  SL_SC7A20_ODR_50HZ       (unsigned char)0x47
#define  SL_SC7A20_ODR_100HZ      (unsigned char)0x57
#define  SL_SC7A20_ODR_200HZ      (unsigned char)0x67
#define  SL_SC7A20_ODR_400HZ      (unsigned char)0x77
#define  SL_SC7A20_ODR_1600HZ     (unsigned char)0x87
#define  SL_SC7A20_ODR_1250HZ     (unsigned char)0x97
#define  SL_SC7A20_ODR_5000HZ     (unsigned char)0x9F
    
#define  SL_SC7A20_LOWER_POWER_ODR_1HZ        (unsigned char)0x1F
#define  SL_SC7A20_LOWER_POWER_ODR_10HZ       (unsigned char)0x2F
#define  SL_SC7A20_LOWER_POWER_ODR_25HZ       (unsigned char)0x3F
#define  SL_SC7A20_LOWER_POWER_ODR_50HZ       (unsigned char)0x4F
#define  SL_SC7A20_LOWER_POWER_ODR_100HZ      (unsigned char)0x5F
#define  SL_SC7A20_LOWER_POWER_ODR_200HZ      (unsigned char)0x6F
#define  SL_SC7A20_LOWER_POWER_ODR_400HZ      (unsigned char)0x7F
/***************数据更新速率**加速度计使能**********/


/***************传感器量程设置**********************/
#define  SL_SC7A20_FS_2G          (unsigned char)0x00		
#define  SL_SC7A20_FS_4G          (unsigned char)0x10
#define  SL_SC7A20_FS_8G          (unsigned char)0x20	
#define  SL_SC7A20_FS_16G         (unsigned char)0x30
/***************传感器量程设置**********************/


/***取值在0-127之间，此处仅举例****/
#define SL_SC7A20_INT1_THS_5PERCENT   (unsigned char)0x06
#define SL_SC7A20_INT1_THS_10PERCENT  (unsigned char)0x0C
#define SL_SC7A20_INT1_THS_20PERCENT  (unsigned char)0x18
#define SL_SC7A20_INT1_THS_40PERCENT  (unsigned char)0x30
#define SL_SC7A20_INT1_THS_80PERCENT  (unsigned char)0x60


/***取值在0-127之间，此处仅举例 乘以ODR单位时间****/
#define SL_SC7A20_INT1_DURATION_2CLK  (unsigned char)0x02
#define SL_SC7A20_INT1_DURATION_5CLK  (unsigned char)0x05
#define SL_SC7A20_INT1_DURATION_10CLK (unsigned char)0x0A

/***中断有效时的电平设置，高电平相当于上升沿，低电平相当于下降沿****/
#define SL_SC7A20_INT_ACTIVE_LOWER_LEVEL 0x02 //0x02:中断时INT1脚输出 低电平
#define SL_SC7A20_INT_ACTIVE_HIGH_LEVEL  0x00 //0x00:中断时INT1脚输出 高电平 

/***中断有效时的电平设置，高电平相当于上升沿，低电平相当于下降沿****/
#define SL_SC7A20_INT_AOI1_INT1          0x40 //AOI1 TO INT1
#define SL_SC7A20_INT_AOI2_INT1          0x20 //AOI2 TO INT1


typedef struct
{
    int16_t AXIS_X;
    int16_t AXIS_Y;
    int16_t AXIS_Z;
}
AxesRaw_t;


typedef void (*gsensor_wakeup_handler_t)(void);

//bool gsensor_init(void);
void sc7a20_readid(void);
void gsensor_switch_normal(void);
void gsensor_switch_motion(gsensor_wakeup_handler_t wakeup_hld);
bool gsensor_init(void);
bool gsensor_uninit(void);
bool gsensor_fifo_get(AxesRaw_t *data_buf, uint8_t *data_len);
bool gsensor_xyz_get(int16_t *x, int16_t *y, int16_t *z);
bool gsensor_z_get(int16_t *z);

#endif
