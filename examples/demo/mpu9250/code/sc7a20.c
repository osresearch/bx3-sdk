//#include "gsensor.h"

//#include "boards.h"

#include "i2c_bus.h"
#include "io_ctrl.h"
#include "sc7a20.h"
#include "plf.h"
#include "bx_dbg.h"

#define SC7A20_IIC_ADDR             0x18//0x19
#define SC7A20_CHIP_ID_ADDRESS    (unsigned char)0x0F

//gsensor_wakeup_handler_t wakeup_handler = NULL;

char gsensor_chip_sc_id =0;

static bool __inline gsensor_reg_read(uint8_t reg, uint8_t* p_data)
{	
	i2c_bus_read(SC7A20_IIC_ADDR<<1, reg, p_data, 1);
	
	return true;
}

void sc7a20_readid(void)
{
	uint8_t whoami = 0;
	gsensor_reg_read(SC7A20_CHIP_ID_ADDRESS, &whoami);
	gsensor_chip_sc_id = whoami;
  bx_logln("sc7a20_id=%d\r\n",gsensor_chip_sc_id);

}
static bool __inline gsensor_reg_write(uint8_t reg, uint8_t data)
{
	i2c_bus_write(SC7A20_IIC_ADDR<<1, reg, data);
	
	return true;
}

static __inline bool gsensor_reg_read_ex(uint8_t reg, uint8_t* p_data, uint16_t len)
{
	i2c_bus_read(SC7A20_IIC_ADDR<<1, reg, p_data, len);
	
	return true;
}

void gsensor_comm_delay_ms(uint32_t ms)
{
	for(int i=0; i<ms; i++)
	{
		for(int j=0; j<10000; j++)
		{
		
		}
	}
}

void gsensor_powerdown(void)
{
		gsensor_reg_write(0x20, 0x00);
}

void gsensor_set_iic_mode(void)
{
	uint8_t sl_val=0;
	gsensor_reg_write(0x1E,0x05); //??????,0x1E ????0x05
	gsensor_reg_read(0x57, &sl_val); //??0x57 ???????
	sl_val=sl_val|0x08; //SDO_PU ?1
	gsensor_reg_write(0x57,sl_val); //??SDO_PU ?,0x57 ???????
	gsensor_reg_write(0x1E,0x00); //??????,0x1E ????0x00
}

bool gsensor_init(void)
{
//	//VDD PIN INIT
//	#if(GSENSOR_VDD_PIN != 0xFF)
//	io_cfg_output(GSENSOR_VDD_PIN);
//	io_pin_pull_write(GSENSOR_VDD_PIN, IO_PULL_UP);
//	io_pin_clear(GSENSOR_VDD_PIN);
//	#endif
//	
//	//VIO PIN INIT
//	#if(GSENSOR_VIO_PIN != 0xFF)
//	io_cfg_output(GSENSOR_VIO_PIN);
//	io_pin_pull_write(GSENSOR_VIO_PIN, IO_PULL_UP);
//	io_pin_clear(GSENSOR_VIO_PIN);
//	#endif
//	
//	// CS = 1 : IIC Mode
//	#if(GSENSOR_CS_PIN != 0xFF)
//	io_cfg_output(GSENSOR_CS_PIN);
//	io_pin_set(GSENSOR_CS_PIN);
//	#endif
//	
//	// MISO = 1 : IIC ADDR (7 bit、LSB)
//	#if(GSENSOR_MISO_PIN != 0xFF)
//	io_cfg_output(GSENSOR_MISO_PIN);
//	io_pin_set(GSENSOR_MISO_PIN);
//	#endif
//	
//	//INT PIN INIT
//	#if(GSENSOR_INT_PIN != 0xFF)
//	io_cfg_input(GSENSOR_INT_PIN);
//	#endif
//	
//	#if(GSENSOR_VDD_PIN != 0xFF)
//	io_pin_set(GSENSOR_VDD_PIN);
//	#endif
//	
//	#if(GSENSOR_VIO_PIN != 0xFF)
//	io_pin_set(GSENSOR_VIO_PIN);
//	#endif
	
//	GSENSOR_DELAY_MS(100);
  i2c_bus_init();
  BX_DELAY_US(100000);
	
	// 读取ID
	bool ret = true;
	uint8_t retry ;
	uint8_t whoami = 0;
	
	for(retry=0; retry<3; retry++)
	{
		ret = true;
		
		gsensor_reg_read(SC7A20_CHIP_ID_ADDRESS, &whoami);
		
		if(whoami != SC7A20_CHIP_ID_VALUE)
		{	
			ret = false;
		}
		
		if(ret)
			break;
		
//		GSENSOR_DELAY_MS(100);
     BX_DELAY_US(100000);
	}

	bx_logln("G-SENSOR Init......%s (id=0x%.2X, retry=%d)", ret?"OK":"ERROR", whoami, retry);
	
	
	//if(ret)
	//{
	//	gsensor_switch_normal();
	//}

	
	gsensor_chip_sc_id = whoami;

	
    extern signed char SL_SC7A20_PEDO_KCAL_WRIST_SLEEP_INIT(void);
	SL_SC7A20_PEDO_KCAL_WRIST_SLEEP_INIT();
	
	return ret;
}

#if 0
static void gensor_gpiote_interrupt(void)
{
	//uint8_t tmp;
	
	//GSENSOR_LOG("gensor_gpiote_interrupt......！");
	
	//gsensor_reg_read(0x32, &tmp);
	
	//if(wakeup_handler != NULL)
	//	wakeup_handler();
}
#endif

void gsensor_switch_normal(void)
{
	// Interrupt Init
//	wakeup_handler = NULL;
	
//	io_cfg_input(GSENSOR_INT_PIN);
//	io_pin_pull_write(GSENSOR_INT_PIN, IO_PULL_UP);
//	io_ext_int_cfg(GSENSOR_INT_PIN, EXT_INT_TRIGGER_LOW_LEVEL, gensor_gpiote_interrupt);
//	
//	io_ext_int_en(GSENSOR_INT_PIN, false);
	
	
	// 写配置
	/*
	gsensor_reg_write(SL_SC7A20_FIFO_CTRL_REG, 0x00);
	gsensor_reg_write(SL_SC7A20_CLICK_CFG, 0x00);
	gsensor_reg_write(SL_SC7A20_CTRL_REG1, SL_SC7A20_ODR_25HZ);
	gsensor_reg_write(SL_SC7A20_CTRL_REG2, 0x00);
	gsensor_reg_write(SL_SC7A20_CTRL_REG3, 0x00);
	gsensor_reg_write(SL_SC7A20_CTRL_REG4, 0x98);	// BDU=1	BLE=0	+-4G	HR=1（高精度输出）
	gsensor_reg_write(SL_SC7A20_CTRL_REG5, 0x40);	// FIFO_EN = 1
	gsensor_reg_write(SL_SC7A20_INT1_CFG, 0x00); 
	gsensor_reg_write(SL_SC7A20_INT2_CFG, 0x00); 
	gsensor_reg_write(SL_SC7A20_FIFO_CTRL_REG, 0x40);
	*/
}

void gsensor_switch_motion(gsensor_wakeup_handler_t wakeup_hld)
{
	// 写配置
//	gsensor_reg_write(SL_SC7A20_FIFO_CTRL_REG, 0x00);
//	gsensor_reg_write(SL_SC7A20_CLICK_CFG, 0x00);
//	gsensor_reg_write(SL_SC7A20_CTRL_REG1, SL_SC7A20_ODR_25HZ);
//	gsensor_reg_write(SL_SC7A20_CTRL_REG2, 0x00);
//	gsensor_reg_write(SL_SC7A20_CTRL_REG3, 0x00);
//	gsensor_reg_write(SL_SC7A20_CTRL_REG4, 0x98);	// BDU=1	BLE=0	+-4G	HR=1（高精度输出）
//	gsensor_reg_write(SL_SC7A20_CTRL_REG5, 0x41);	// FIFO_EN=1	D4D_INT2=1（4D检测中断在INT2上）
//	gsensor_reg_write(SL_SC7A20_INT1_CFG, 0x00); 	
//	gsensor_reg_write(SL_SC7A20_INT2_CFG, 0x7F); 	// 6个方向位置检测
//	gsensor_reg_write(SL_SC7A20_FIFO_CTRL_REG, 32);
//	gsensor_reg_write(SL_SC7A20_CTRL_REG6, 0x02);	// H_LACTIVE=1(低电平触发中断)
//	
//	gsensor_reg_write(SL_SC7A20_INT2_THS, 0x01);		// 触发阈值
//	gsensor_reg_write(SL_SC7A20_INT2_DURATION, 0x00);	// 中断持续时间
	
	/*
	gsensor_reg_write(0x20, 0x47);
	gsensor_reg_write(0x21, 0x11);
	gsensor_reg_write(0x25, 0x42);
	gsensor_reg_write(0x23, 0xc8);
	gsensor_reg_write(0x30, 0x7f);
	gsensor_reg_write(0x36, 0xFF);
	
	uint8_t tmp;
	gsensor_reg_read(0x32, &tmp);

	// Interrupt Init
	wakeup_handler = wakeup_hld;
	
	io_cfg_input(GSENSOR_INT_PIN);
	io_pin_pull_write(GSENSOR_INT_PIN, IO_PULL_UP);
	io_ext_int_cfg(GSENSOR_INT_PIN, EXT_INT_TRIGGER_LOW_LEVEL, gensor_gpiote_interrupt);
	
	io_ext_int_en(GSENSOR_INT_PIN, true);
	*/
}

//bool gsensor_uninit(void)
//{
//	gsensor_powerdown();

//	#if(GSENSOR_VDD_PIN != 0xFF)
//	io_cfg_input(GSENSOR_VDD_PIN);	// Do not use io_pin_clear()
//	#endif
//	
//	#if(GSENSOR_VIO_PIN != 0xFF)
//	io_cfg_input(GSENSOR_VIO_PIN);	// Do not use io_pin_clear()
//	#endif
//	
//	#if(GSENSOR_CS_PIN != 0xFF)
//	io_cfg_input(GSENSOR_CS_PIN);
//	#endif
//	
//	#if(GSENSOR_MISO_PIN != 0xFF)
//	io_cfg_input(GSENSOR_MISO_PIN);
//	#endif
//	
//	#if(GSENSOR_INT_PIN != 0xFF)
//	io_cfg_input(GSENSOR_INT_PIN);
//	#endif
//	
//	return true;
//	
//}

bool gsensor_fifo_get(AxesRaw_t *data_buf, uint8_t *data_len)
{
	uint8_t len = 0;
	uint8_t rxData[6];
	
	gsensor_reg_read(SL_SC7A20_FIFO_SRC_REG, &len);
	
	//GSENSOR_LOG("g-sensor fifo len = %d", len);
	
	len &= 0x1F;
	
	if(len > 0)
	{
		for(int i=0; i<len; i++)
		{
			gsensor_reg_read_ex(SL_SC7A20_DATA_OUT, rxData, 6);
			
			data_buf[i].AXIS_X = ((uint8_t)rxData[1]<<8)+((uint8_t)rxData[0]);
			data_buf[i].AXIS_Y = ((uint8_t)rxData[3]<<8)+((uint8_t)rxData[2]);
			data_buf[i].AXIS_Z = ((uint8_t)rxData[5]<<8)+((uint8_t)rxData[4]);
			
			//GSENSOR_LOG("g-sensor: x=%d y=%d z=%d", data_buf[i].AXIS_X, data_buf[i].AXIS_Y, data_buf[i].AXIS_Z);
		}
	}
	
	gsensor_reg_write(SL_SC7A20_FIFO_CTRL_REG, 0x00);
	gsensor_reg_write(SL_SC7A20_FIFO_CTRL_REG, 0x40);
	
	*data_len = len ;
	
	return true;
}

bool gsensor_xyz_get(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t data_h, data_l;
	
	gsensor_reg_read(SL_SC7A20_OUT_X_L, &data_l);
	gsensor_reg_read(SL_SC7A20_OUT_X_H, &data_h);
	*x = (data_h<<8)|data_l;
	
	gsensor_reg_read(SL_SC7A20_OUT_Y_L, &data_l);
	gsensor_reg_read(SL_SC7A20_OUT_Y_H, &data_h);
	*y = (data_h<<8)|data_l;
	
	gsensor_reg_read(SL_SC7A20_OUT_Z_L, &data_l);
	gsensor_reg_read(SL_SC7A20_OUT_Z_H, &data_h);
	*z = (data_h<<8)|data_l;
	
	return true;
}

bool gsensor_z_get(int16_t *z)
{
	uint8_t data_h, data_l;
	
	gsensor_reg_read(SL_SC7A20_OUT_Z_L, &data_l);
	gsensor_reg_read(SL_SC7A20_OUT_Z_H, &data_h);
	*z = (data_h<<8)|data_l;
	
	return true;
}

/*add for silan pedometer */
unsigned char SL_SC7A20_I2c_Spi_Write(unsigned char sl_spi_iic,unsigned char reg, unsigned char data)
{
	i2c_bus_write(SC7A20_IIC_ADDR<<1, reg, data);
	return 0;
}

unsigned char SL_SC7A20_I2c_Spi_Read(unsigned char sl_spi_iic,unsigned char reg, unsigned char len, unsigned char *buf)
{
	i2c_bus_read(SC7A20_IIC_ADDR<<1, reg, buf, len);
	return 0;
}
