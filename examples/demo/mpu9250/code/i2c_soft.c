#include "bx_kernel.h"
#include "bx_spi_type_def.h"
#include "flash_wrapper.h"
#include "bx_dbg.h"
#include "bxd_io_mux.h"

#include "bxd_gpio.h"
#include "bx_pm.h"
#include "bxs_gpio.h"

#include <stdio.h>
#include <stdbool.h>
//#include "io_ctrl.h"
#include "i2c_soft.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TIMEOUT	6000

#define I2C_ACK   		0
#define I2C_READY 		0
#define I2C_NACK 		1
#define I2C_BUS_BUSY  	2
#define I2C_BUS_ERROR 	3

#define I2C_RETRY_COUNT 3 //重试次数

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


#if 0
static  void I2C_SCL_L(i2c_dev_str *i2c_dev)		{io_cfg_output(i2c_dev->i2c_sck.GPIO_Pin); io_pin_clear(i2c_dev->i2c_sck.GPIO_Pin);}
static  void I2C_SCL_H(i2c_dev_str *i2c_dev) 		{ io_cfg_input(i2c_dev->i2c_sck.GPIO_Pin);}
static  void I2C_SDA_L(i2c_dev_str *i2c_dev) 		{io_cfg_output(i2c_dev->i2c_sda.GPIO_Pin); io_pin_clear(i2c_dev->i2c_sda.GPIO_Pin); }
static  void I2C_SDA_H(i2c_dev_str *i2c_dev) 		{ io_cfg_input(i2c_dev->i2c_sda.GPIO_Pin);}
#else
static  void I2C_SCL_L(i2c_dev_str *i2c_dev)		{bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sck.GPIO_Pin,BX_GPIO_MODE_OUTPUT); bxd_gpio_write(BX_GPIOA, i2c_dev->i2c_sck.GPIO_Pin, 0);}
static  void I2C_SCL_H(i2c_dev_str *i2c_dev) 		{bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sck.GPIO_Pin,BX_GPIO_MODE_INPUT);bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sck.GPIO_Pin,BX_GPIO_PULLUP);}
static  void I2C_SDA_L(i2c_dev_str *i2c_dev) 		{bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sda.GPIO_Pin,BX_GPIO_MODE_OUTPUT); bxd_gpio_write(BX_GPIOA, i2c_dev->i2c_sda.GPIO_Pin, 0);}
static  void I2C_SDA_H(i2c_dev_str *i2c_dev) 		{bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sda.GPIO_Pin,BX_GPIO_MODE_INPUT);bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sda.GPIO_Pin,BX_GPIO_PULLUP);}

#endif

static  unsigned char I2C_SDA_STATE(i2c_dev_str *i2c_dev)
{
	unsigned char res;

	//res = io_pin_read(i2c_dev->i2c_sda.GPIO_Pin);
	res = bxd_gpio_read_pin(BX_GPIOA, i2c_dev->i2c_sda.GPIO_Pin);

	return res;
}

void i2c_sda_io_config(i2c_dev_str *i2c_dev, int flag)
{
	if (flag) {
		//io_cfg_output(i2c_dev->i2c_sda.GPIO_Pin);
		bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sda.GPIO_Pin,BX_GPIO_MODE_OUTPUT);

	} else {
	   //io_cfg_input(i2c_dev->i2c_sda.GPIO_Pin);
	   bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sda.GPIO_Pin,BX_GPIO_MODE_INPUT);
	}
}


void i2c_init(i2c_dev_str *i2c_dev)
{
	bxd_gpio_open(BX_GPIOA);

    //io_cfg_output(i2c_dev->i2c_sck.GPIO_Pin);
  	//io_cfg_output(i2c_dev->i2c_sda.GPIO_Pin);
  	bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sda.GPIO_Pin,BX_GPIO_MODE_OUTPUT);
	bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sck.GPIO_Pin,BX_GPIO_MODE_OUTPUT);

	I2C_SDA_H(i2c_dev);
	I2C_SCL_H(i2c_dev);
}

void i2c_deinit(i2c_dev_str *i2c_dev)
{
    //io_cfg_input(i2c_dev->i2c_sck.GPIO_Pin);
  	//io_cfg_input(i2c_dev->i2c_sda.GPIO_Pin);
  	bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sda.GPIO_Pin,BX_GPIO_MODE_INPUT);
	bxd_gpio_set_mode(BX_GPIOA,i2c_dev->i2c_sck.GPIO_Pin,BX_GPIO_MODE_INPUT);
}

/*******************************************************************************
 * 函数名称:I2C_Delay
 * 描    述:延时函数
 *
 * 输    入:无
 * 输    出:无
 * 返    回:无
 * 作    者:
 * 修改日期:2010年6月8日
 *******************************************************************************/
static void I2C_NOP(i2c_dev_str *i2c_dev)
{
	if(i2c_dev->i2c_nop != NULL)
	{
		i2c_dev->i2c_nop();
	}
}

/*******************************************************************************
 * 函数名称:I2C_Delay
 * 描    述:延时函数
 *
 * 输    入:无
 * 输    出:无
 * 返    回:无
 * 作    者:
 * 修改日期:2010年6月8日
 *******************************************************************************/
static void I2C_Delay(i2c_dev_str *i2c_dev)
{
	if(i2c_dev->i2c_delay != NULL)
	{
		i2c_dev->i2c_delay();
	}
}

/*******************************************************************************
 * 函数名称:I2C_START
 * 描    述:发送启动
 *
 * 输    入:无
 * 输    出:无
 * 返    回:无
 * 作    者:
 * 修改日期:
 *******************************************************************************/
static unsigned char I2C_START(i2c_dev_str *i2c_dev)
 {
	I2C_SDA_H(i2c_dev);
	I2C_NOP(i2c_dev);
	I2C_SCL_H(i2c_dev);
	I2C_NOP(i2c_dev);
#if 0
	i2c_sda_io_config(i2c_dev, 0);
	if (!I2C_SDA_STATE(i2c_dev)) {
		return I2C_BUS_BUSY;
	}
	i2c_sda_io_config(i2c_dev, 1);

	I2C_SDA_L(i2c_dev);
	I2C_NOP(i2c_dev);

	if (I2C_SDA_STATE(i2c_dev)) {
		return I2C_BUS_ERROR;
	}

	I2C_SCL_L(i2c_dev);
	//I2C_NOP(i2c_dev);
#else
	I2C_SDA_L(i2c_dev);
	I2C_NOP(i2c_dev);
	I2C_SCL_L(i2c_dev);
	I2C_NOP(i2c_dev);
#endif
	return I2C_READY;
}
#if 0
/* --------------------------------------------------------------------------*/
/**
 * @Brief:  I2C_START_SHT
 *
 * @Returns:
 */
/* --------------------------------------------------------------------------*/
static unsigned char I2C_START_SHT(i2c_dev_str *i2c_dev)
{
    I2C_SDA_H(i2c_dev);
    I2C_SCL_L(i2c_dev);
    I2C_NOP(i2c_dev);

    I2C_SDA_H(i2c_dev);
    I2C_SCL_H(i2c_dev);
    I2C_NOP(i2c_dev);

    i2c_sda_io_config(i2c_dev, 0);
    if(!I2C_SDA_STATE(i2c_dev))
    {
	    return I2C_BUS_BUSY;
    }
    i2c_sda_io_config(i2c_dev, 1);

    I2C_SDA_L(i2c_dev);
    I2C_NOP(i2c_dev);

    I2C_SCL_L(i2c_dev);
    I2C_NOP(i2c_dev);

    I2C_SCL_H(i2c_dev);
    I2C_NOP(i2c_dev);

    I2C_SDA_H(i2c_dev);
    I2C_NOP(i2c_dev);

    I2C_SCL_L(i2c_dev);
    I2C_NOP(i2c_dev);

    return I2C_READY;
}
#endif
/* --------------------------------------------------------------------------*/
/**
 * @Brief:  I2C_STOP
 */
/* --------------------------------------------------------------------------*/
static void I2C_STOP(i2c_dev_str *i2c_dev)
 {
	I2C_SCL_L(i2c_dev);
	I2C_NOP(i2c_dev);

	I2C_SDA_L(i2c_dev);
	I2C_NOP(i2c_dev);

	I2C_SCL_H(i2c_dev);
	I2C_NOP(i2c_dev);

	I2C_SDA_H(i2c_dev);
	I2C_Delay(i2c_dev);
	//I2C_NOP(i2c_dev);
	//I2C_NOP(i2c_dev);
}

/* --------------------------------------------------------------------------*/
/**
 * @Brief:  I2C_SendACK
 */
/* --------------------------------------------------------------------------*/
static void I2C_SendACK(i2c_dev_str *i2c_dev)
{
	I2C_SCL_L(i2c_dev);
	I2C_NOP(i2c_dev);
	I2C_SDA_L(i2c_dev);
	I2C_NOP(i2c_dev);
	I2C_SCL_H(i2c_dev);
	I2C_NOP(i2c_dev);
	I2C_SCL_L(i2c_dev);
	I2C_NOP(i2c_dev);
}

/* --------------------------------------------------------------------------*/
/**
 * @Brief:  I2C_SendNACK
 */
/* --------------------------------------------------------------------------*/
static void I2C_SendNACK(i2c_dev_str *i2c_dev)
{
	I2C_SCL_L(i2c_dev);
	I2C_SDA_H(i2c_dev);
	I2C_NOP(i2c_dev);
	I2C_SCL_H(i2c_dev);
	I2C_NOP(i2c_dev);
	I2C_SCL_L(i2c_dev);
}

int I2C_WaitAck(i2c_dev_str *i2c_dev)
{
	I2C_SCL_L(i2c_dev);
	i2c_sda_io_config(i2c_dev, 0);
	I2C_NOP(i2c_dev);
	//I2C_SDA_H();

	//I2C_NOP(i2c_dev);
	I2C_SCL_H(i2c_dev);
	I2C_NOP(i2c_dev);
	if (I2C_SDA_STATE(i2c_dev)) {
		I2C_SCL_L(i2c_dev);
		i2c_sda_io_config(i2c_dev, 1);
		return I2C_BUS_ERROR;
		//return I2C_READY;
	}

	i2c_sda_io_config(i2c_dev, 1);
	I2C_SCL_L(i2c_dev);
	//I2C_NOP(i2c_dev);

	return I2C_READY;
}

void I2C_SendByte(i2c_dev_str *i2c_dev, unsigned char SendByte)
{
	unsigned char i = 8;

	while (i--) {
		I2C_SCL_L(i2c_dev);
		//I2C_NOP(i2c_dev);
		if (SendByte & 0x80)
			I2C_SDA_H(i2c_dev);
		else
			I2C_SDA_L(i2c_dev);
		SendByte <<= 1;
		I2C_NOP(i2c_dev);
		I2C_SCL_H(i2c_dev);
		I2C_NOP(i2c_dev);
	}
	I2C_SCL_L(i2c_dev);
}

unsigned char I2C_ReceiveByte(i2c_dev_str *i2c_dev)
{
	unsigned char i = 8;
	unsigned char ReceiveByte = 0;

	i2c_sda_io_config(i2c_dev, 0);
	//I2C_SDA_H(i2c_dev);
	while (i--) {
		ReceiveByte <<= 1;
		I2C_SCL_H(i2c_dev);
		I2C_NOP(i2c_dev);
		if (I2C_SDA_STATE(i2c_dev)) {
			ReceiveByte |= 0x01;
		}
		I2C_SCL_L(i2c_dev);
		I2C_NOP(i2c_dev);
	}
	i2c_sda_io_config(i2c_dev, 1);
	//I2C_SDA_L();
	return ReceiveByte;
}

int soft_i2c_read(i2c_dev_str *i2c_dev, unsigned char Reg, unsigned char *Data, unsigned int len)
{
	int i;
	int res = false;
	if(I2C_START(i2c_dev))
		{
		res = false;
		goto OUT;
		}
	I2C_SendByte(i2c_dev, i2c_dev->i2c_addr);
	if(I2C_WaitAck(i2c_dev))
		{
		res = false;
		//goto OUT;
		}
	else
		{
			res = true;
		}
	I2C_SendByte(i2c_dev, Reg & 0xFF);
	if(I2C_WaitAck(i2c_dev))
	{
		res = false;
		goto OUT;
	}
	I2C_START(i2c_dev);
	I2C_SendByte(i2c_dev, i2c_dev->i2c_addr | 0x01);
	if(I2C_WaitAck(i2c_dev))
	{
		res = false;
		goto OUT;
	}
	i = 0;
	while(i < (len - 1))
	{
		*(Data + i) = I2C_ReceiveByte(i2c_dev);
		I2C_SendACK(i2c_dev);
		i++;
	}

	*(Data + i) = I2C_ReceiveByte(i2c_dev);
	I2C_SendNACK(i2c_dev);
	res = true;
OUT:
	I2C_STOP(i2c_dev);
	return res;
}

int soft_i2c_write(i2c_dev_str *i2c_dev, unsigned char Reg, unsigned char *Data, unsigned int len)
 {
	int i;
	int res = false;
	if (I2C_START(i2c_dev))
	{
		res = false;
		goto OUT;
	}
	I2C_SendByte(i2c_dev, i2c_dev->i2c_addr);
	if (I2C_WaitAck(i2c_dev)) {
		res = false;
		goto OUT;
	}
	I2C_SendByte(i2c_dev, Reg & 0xFF);
	if (I2C_WaitAck(i2c_dev)) {
		res = false;
		goto OUT;
	}

	for(i = 0; i < len; i++)
	{
		I2C_SendByte(i2c_dev, *(Data + i));
		if (I2C_WaitAck(i2c_dev)) {
			res = false;
			//goto OUT;
		}
	}
	res = true;
OUT:
	I2C_STOP(i2c_dev);
	return res;
}


