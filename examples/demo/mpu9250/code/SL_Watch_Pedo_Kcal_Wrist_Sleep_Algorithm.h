/* 
Copyright (c) 2017 Silan MEMS. All Rights Reserved.
*/

#ifndef SL_Watch_PEDO_KCAL_WRIST_SLEEP_ALGO_DRV__H__
#define SL_Watch_PEDO_KCAL_WRIST_SLEEP_ALGO_DRV__H__

#define SL_Sensor_Algo_Release_Enable 0x01
//0x00: for debug
//0x01: release version

/***使用驱动前请根据实际接线情况配置******/
/**SC7A20的SDO 脚接地：  0****************/
/**SC7A20的SDO 脚接电源：1****************/
#define SL_SC7A20_SDO_VDD_GND            1
/*****************************************/

/***使用驱动前请根据实际IIC情况进行配置***/
/**SC7A20的IIC 接口地址类型 7bits：  0****/
/**SC7A20的IIC 接口地址类型 8bits：  1****/
#define SL_SC7A20_IIC_7BITS_8BITS        1
/*****************************************/

#if SL_SC7A20_SDO_VDD_GND==0
#define SL_SC7A20_IIC_7BITS_ADDR        0x18
#define SL_SC7A20_IIC_8BITS_WRITE_ADDR  0x30
#define SL_SC7A20_IIC_8BITS_READ_ADDR   0x31
#else
#define SL_SC7A20_IIC_7BITS_ADDR        0x19
#define SL_SC7A20_IIC_8BITS_WRITE_ADDR  0x32
#define SL_SC7A20_IIC_8BITS_READ_ADDR   0x33
#endif

#if SL_SC7A20_IIC_7BITS_8BITS==0
#define SL_SC7A20_IIC_ADDRESS        SL_SC7A20_IIC_7BITS_ADDR
#else
#define SL_SC7A20_IIC_WRITE_ADDRESS  SL_SC7A20_IIC_8BITS_WRITE_ADDR
#define SL_SC7A20_IIC_READ_ADDRESS   SL_SC7A20_IIC_8BITS_READ_ADDR
#endif

#define SL_SC7A20_CHIP_ID_ADDR       (unsigned char)0x0F
#define SL_SC7A20_CHIP_ID_VALUE      (unsigned char)0x11

/********客户需要进行的IIC接口封包函数****************/
extern unsigned char SL_SC7A20_I2c_Spi_Write(unsigned char sl_spi_iic,unsigned char reg, unsigned char dat);
extern unsigned char SL_SC7A20_I2c_Spi_Read(unsigned char sl_spi_iic,unsigned char reg, unsigned char len, unsigned char *buf);
/**SL_SC7A20_I2c_Spi_Write 函数中， sl_spi_iic:0=spi  1=i2c  Reg：寄存器地址   dat：寄存器的配置值*******************/
/**SL_SC7A20_I2c_Spi_Write 函数 是一个单次写的函数*******************************************************************/
/***SL_SC7A20_I2c_Spi_Read 函数中， sl_spi_iic:0=spi  1=i2c Reg 同上，len:读取数据长度，buf:存储数据首地址（指针）***/
/***SL_SC7A20_I2c_Spi_Read 函数 是可以进行单次读或多次连续读取的函数*************************************************/

/*************驱动初始化函数**************/
signed char SL_SC7A20_Driver_Init(unsigned char Sl_spi_iic_init,unsigned char Sl_pull_up_mode);
/***输入参数:1,Sl_spi_iic_init:0-1***2,PULL_UP_MODE:0x00 0x08 0x04 0x0c********/
/****Sl_spi_iic_init=0：SPI MODE, Sl_pull_up_mode config failed****************/
/****Sl_spi_iic_init=1：IIC MODE***********************************************/
/****Sl_pull_up_mode=0x00: SDO  I2C  pull up***********************************/
/****Sl_pull_up_mode=0x08: I2C  pull up and  SDO  open drain*******************/
/****Sl_pull_up_mode=0x04: SDO  pull up and  I2C  open drain*******************/
/****Sl_pull_up_mode=0x0C: SDO  I2C  open drain********************************/
/****SDO脚接地，推荐关闭SDO内部上拉电阻****************************************/
/****SPI通讯，推荐关闭SDA，SCL内部上拉电阻，SDO内部上拉电阻会自动关闭**********/

/*************返回数据情况如下*****************/
/**return : 0x11    表示CHIP ID 正常***********/
/**return : 0       表示读取异常***************/
/**return :-1;      SPI 通信问题***************/
/**return :-2;      IIC 通信问题***************/
/**return :-3;      连续读取 通信问题**********/

/***************执行算法前需要读取FIFO数据*****/
/***************FIFO数据读取后，FIFO会清空*****/
/***************所以FIFO只能定时读取一次*******/
unsigned char SL_SC7A20_Read_FIFO(void);
/**return : FIFO_LEN    表示数组长度***********/


/****说明:该函数需要定时执行,从而保证算法执行到位**/
unsigned int SL_Watch_Pedo_Kcal_Algo(void);
/***************获取当天的当前计步值***************/
/**************输出数据为：计步值(步)**************/


/***************获取三轴原始数据***************/
unsigned char SL_SC7A20_GET_FIFO_Buf(signed short *sl_x_buf,signed short *sl_y_buf,signed short *sl_z_buf);
/****************执行算法后执行该命令**********/
/**x_buf  y_buf  z_buf : 长度32的数组首地址****/
/****************返回数据情况如下**************/
/**return : FIFO_LEN    表示数组长度***********/


/******************复位计步值************************/
void SL_Pedo_Kcal_ResetStepCount(void);
/**********输入数据为：无******输出数据为：无********/
/*使用方法: 系统时间到第二天时，调用该函数清除计步值*/

/******************升级后，设置计步值,距离,热量************************/
/******************升级后，请在初始化函数后，增加该函数****************/
void SL_Pedo_StepCount_Set(unsigned int sl_pedo_value,unsigned int sl_dis_value,unsigned int sl_kcal_value);
/**********输入数据为：sl_pedo_value  计步值*****/
/**********输入数据为：sl_dis_value   距离值*****/
/**********输入数据为：sl_kcal_value  热量值*****/

/******************计步灵敏度设置********************/
void SL_PEDO_TH_SET(unsigned char sl_pedo_amp,unsigned char sl_pedo_th,unsigned char sl_pedo_weak,unsigned char sl_zcr_lel);
/******sl_pedo_amp>4&&sl_pedo_amp<201**************************/
/******sl_pedo_amp:越小灵敏度越高，越容易计步******************/
/******sl_pedo_amp:越大灵敏度越高，越难计步********************/
/******sl_pedo_amp:默认值26，不设置就是26**********************/

/******sl_pedo_th>5&&sl_pedo_th<50*****************************/
/******sl_pedo_th:越小灵敏度越高，越容易计步*******************/
/******sl_pedo_th:越大灵敏度越高，越难计步*********************/
/******sl_pedo_th:默认值10，不设置就是10***********************/

/******sl_pedo_weak>=0&&sl_pedo_weak<6*************************/
/******sl_pedo_th:0,不打开轻微走路计步功能*********************/
/******sl_pedo_th:1,打开轻微走路计步功能***********************/
/******sl_pedo_th:2,打开轻微走路计步功能***********************/
/******sl_pedo_th:3,打开轻微走路计步功能***********************/
/******sl_pedo_th:4,打开轻微走路计步功能***********************/
/******sl_pedo_th:5,打开轻微走路计步功能***********************/
/******sl_pedo_th:默认值0,设置的值越大，检测计步的越灵敏*******/

/*****sl_zcr_lel>=0&&sl_zcr_lel<=255***************************/
/*****sl_zcr_lel:默认值=20,设置的值越小，越容易屏蔽喇叭震动****/
/*****一定时间内的过零率计算***********************************/


/*******计步主轴设置****************/
void SL_PEDO_SET_AXIS(unsigned char sl_xyz);
/***sl_xyz:0  x轴*******************/
/***sl_xyz:1  y轴*******************/
/***sl_xyz:2  z轴*******************/
/***sl_xyz:3  算法决定**************/

/*设置运动检测幅度阈值和时间阈值****/
void SL_PEDO_INT_SET(unsigned char V_TH,unsigned char T_TH,unsigned char INT_EN);
/***V_TH:0  0-127************************************/
/***T_TH:1  0-127************************************/
/***INT_EN:0 关闭中断功能，1，打开中断状态监测功能***/
/***USE AOI1 INT*************************************/

/*设置运动状态读取******************/
unsigned char SL_INT_STATUS_READ(void);
/*0：  没有运动*********************/
/*1：  有运动***********************/
/*关闭中断功能情况下，一直输出1*****/

/***********关闭IIC设备**************/
/***********Power down 函数**********/
/********不使用该设备情况下**********/
/****如需重启，使用驱动初始化函数****/
signed char  SL_SC7A20_Power_Down(void);
/*************输入参数:无************/
/**********返回参数情况说明**********/
/**return  1: Power Down Success*****/
/**return -1: Power Down Fail********/




/*************初始化个人参数*************/
/**参数初始化，用于热量，距离计算********/
void SL_Pedo_Person_Inf_Init(unsigned char *Person_Inf_Init);
/*********输入指针参数分别是:身高 体重 年龄 性别***举例:178,60,26 1*********/
/**身高范围:  30cm ~ 250cm  ***********/
/**体重范围:  10Kg ~ 200Kg  ***********/
/**年龄范围:  3岁  ~ 150岁  ***********/
/**性别范围:  0 ~ 1    0:女 1:男   ****/

/*********************获取运动状态值**********************/
unsigned char SL_Pedo_GetMotion_Status(void);
/**********输入数据为：无*********************************/
/**********输出数据为：0 ~ 3 *****************************/
/**输出数据为：0   *静止或静坐**********/
/**输出数据为：1   *慢走或散步**********/
/**输出数据为：2   *正常走路************/
/**输出数据为：3   *跑步或剧烈运动******/

/**************获取截止当前当天的行走距离*****************/
unsigned int SL_Pedo_Step_Get_Distance(void);
/*******************输入数据为：无************************/
/*******************输出数据为：当天行走距离 *************/
/*******************单位:       分米(dm)******************/

/**************获取截止当前当天的热量消耗*****************/
unsigned int SL_Pedo_Step_Get_KCal(void);
/*******************输入数据为：无************************/
/*******************输出数据为：当天热量消耗值 ***********/
/*********单位: 大卡     1个单位=0.1大卡******************/

/**************获取最近一段时间的走路平均幅度*************/
unsigned short SL_Pedo_Step_Get_Avg_Amp(void);
/********************输入数据为：无***********************/
/***********************1LSB≈XXXmg************************/

/***********************获取当前走路平均步频**************/
unsigned char SL_Pedo_Step_Get_Step_Per_Min(void);
/********************输入数据为：无***********************/
/********************输出数据为：XXX步/分钟 **************/

/***********************获取当前的运动等级****************/
unsigned char SL_Pedo_Step_Get_Motion_Degree(void);
/********************输入数据为：无***********************/
/********************输出数据为：0-25 ********************/


/**********抬手亮屏算法**********/

/*****************抬手亮屏算法初始化函数****************/
void SL_Turn_Wrist_Init(unsigned char *SL_Turn_Wrist_Para);
/************输入参数：*************/
/******SL_Turn_Wrist_Para[0]:加速度计贴片位置设置  0--7********/
/******SL_Turn_Wrist_Para[1]:抬手亮屏灵敏度设置    1--5********/

/*************三轴加速度计贴片位置设置*************************/
/***SL_Turn_Wrist_Para[0]：设定值的范围为: 0 ~ 7 **************/
/***请参考文档:Silan_MEMS_手环算法说明书_V0.3.pdf**************/

/***SL_Turn_Wrist_Para[1]:设定值的范围为: 1 ~ 5 **/
/*********默认值为：3   中等灵敏度****************/
/*********设定值为：1   最低灵敏度****************/
/*********默认值为：5   最高灵敏度****************/
/*********设定值为：1(最迟钝)~5(最灵敏)***********/


/*****************抬手亮屏状态获取函数****************/
signed char SL_Watch_Wrist_Algo(void);
/***********输入参数：无***********/
/***********返回参数情况说明*******/
/**Return:  2     备注说明:屏幕点亮后需要关闭*********/
/**Return:  1     备注说明:屏幕需要点亮***************/
/**Return:  0     备注说明:屏幕不需要点亮*************/
/**Return: -1     备注说明:未初始化或初始化失败*******/

/*****************抬手亮屏状态复位********************/
void SL_Turn_Wrist_Reset(void);
/***********输入参数：无***********/
/***********输出值参数：无*********/


//3-12
//1-10
//0-10
/******************睡眠参数设置********************/
void SL_Sleep_Para(unsigned char adom_time_th,unsigned char sleep_vpp_th,unsigned char sleep_time_th);
/**************************佩戴检测的时长***********************/
/******adom_time_th:0-255 min***********************************/
/******adom_time_th:未活动的时间，大于设置阈值才能认为未佩戴****/
/******adom_time_th:设置值越小，越容易出现未佩戴情况************/

/**************************睡眠中间点阈值***********************/
/******sleep_vpp_th:越小灵敏度越高，越容易睡眠状态切换**********/
/******sleep_vpp_th:越大灵敏度越低，越难睡眠状态切换************/
/******sleep_vpp_th:默认值4，不设置就是4************************/

/**************************状态切换最小时间*********************/
/******sleep_time_th:该值越小，睡眠状态切换的所需时间就越短*****/
/******sleep_time_th:该值越大，睡眠状态切换的所需时间就越长*****/
/******sleep_time_th:默认值2，不设置就是2***********************/


/***************获取当前的睡眠状态*****************/
unsigned char SL_Sleep_GetStatus(unsigned char SL_Sys_Time);
/*******SL_Sys_Time：当前的时间，以小时为单位******/
/*******全天的输入时间范围为：0-23 ****************/
/***************输出数据范围：0-7******************/
/***************0：清醒状态************************/
/***************7：深度睡眠************************/

/***************获取当前的活动等级*****************/
unsigned char SL_Sleep_Active_Degree(unsigned char mode);
/***************mode：0 定时器0.5s中调用***********/
/***************mode：1 定时器1min中调用***********/
/***************输出数据范围：0-255****************/
/***************0：静止****************************/
/*************255：运动****************************/

unsigned char SL_Sleep_Get_Active_Degree(void);
/***************mode：0 定时器0.5s中调用***********/
/***************mode：1 定时器1min中调用***********/
/***************输出数据范围：0-255****************/
/***************0：静止****************************/
/*************255：运动****************************/

/***************获取当前的佩戴的情况***************/
unsigned char SL_Adom_GetStatus(void);
/***************0：未佩戴**************************/
/***************1：已佩戴**************************/

/***************获取当前的佩戴的情况***************/
unsigned char SL_In_Sleep_Status(void);
/***************0：out sleep**********************/
/***************1：in sleep***********************/



/************加测项目客户端测试***********/
/***初始化的时候调用用于判断FIFO是否正常**/
unsigned char SL_SC7A20_FIFO_TEST(void);
/*************输入参数:无*****************/
/*************返回数据情况如下************/
/**return :1  FIFO 异常*******************/
/**return :0  FIFO 正常*******************/
#endif/****SL_Watch_ALGO_DRV__H__*********/



