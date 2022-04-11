#include "i2c_bus.h"
//#include "boards.h"
#include "plf.h"

#define USE_HW_IIC		0

#define GSENSOR_MOSI_PIN  3
#define GSENSOR_SCK_PIN   2

#if(USE_HW_IIC)
	#include "bxd_iic.h"
	
	app_iic_inst_t iic1 = IIC_INSTANCE(1);
	
	volatile bool iic1_busy_flag = false;

	static void iic_transfer_cb(void *para1, uint8_t para2)
	{
		iic1_busy_flag = false;
	}
#else
	#include "i2c_soft.h"
	
	i2c_dev_str i2c_dev =
	{
		{
			GSENSOR_MOSI_PIN	// SDA
		},
		{
			GSENSOR_SCK_PIN	// SCL
		},
		0,
		0,
		0,
	};


			
#endif

void i2c_bus_init(void)
{
	#if(USE_HW_IIC)
		iic1.param.dev_addr_bit_num = IIC_7BIT_ADDRESS;
		iic1.param.mem_addr_bit_num = IIC_8BIT_MEMORY_ADDRESS;
		iic1.param.work_mode = IIC_MASTER;
		iic1.param.speed_mode = IIC_FAST_MODE;
		iic1.param.sda_pin = GSENSOR_MOSI_PIN;	// SDA
		iic1.param.scl_pin = GSENSOR_SCK_PIN;	// SCL
		iic1.param.enable_pull_up = 0;
		iic1.param.use_dma = 0;
		
		app_iic_init(&iic1.inst);
	#else
		i2c_init(&i2c_dev);
	#endif
}

void i2c_bus_uninit(void)
{
	#if(USE_HW_IIC)
		app_iic_uninit(&iic1.inst);
	#else
		i2c_deinit(&i2c_dev);


	#endif
}
//#define OS_DELAY_MS(ms) vTaskDelay(ms)

void i2c_bus_write(uint8_t dev_addr, int8_t reg, uint8_t data)
{
	#if(USE_HW_IIC)
#if 1	
		iic1_busy_flag = true;
	
		app_iic_write(&iic1.inst,
					   &data,
					   1,
					   dev_addr,
					   reg ,
					   iic_transfer_cb,
					   NULL);
		//while(iic1_busy_flag);
		   uint8_t curseq = 100;
		   wdt_feed();
		   while( iic1_busy_flag && curseq > 0)
		   {
			   //OS_DELAY_MS(2);
			   BX_DELAY_US(100);
			   curseq--;
		   }

#else
		bx_iic_write(&iic1.inst,
					   &data,
					   1,
					   dev_addr,
					   reg, 
					   10);
#endif
	#else
		i2c_dev.i2c_addr = dev_addr;
		
		soft_i2c_write(&i2c_dev, reg, &data, 1);
	#endif
}

void i2c_bus_read(uint8_t dev_addr, int8_t reg, uint8_t *p_data, uint16_t read_size)
{
	#if(USE_HW_IIC)
#if 1	
		iic1_busy_flag = true;

		app_iic_read (&iic1.inst,
					   p_data,
					   read_size,
					   dev_addr,
					   reg ,
					   iic_transfer_cb,
					   NULL);
		//while(iic1_busy_flag);	
		uint16_t curseq = read_size*50;
		wdt_feed();
        while( iic1_busy_flag && curseq > 0)
        {
           // OS_DELAY_MS(2);
            BX_DELAY_US(100);
            curseq--;
        }
        
#else
		bx_iic_read (&iic1.inst,
					   p_data,
					   read_size,
					   dev_addr,
					   reg ,
					   read_size);

#endif

	#else
		i2c_dev.i2c_addr = dev_addr;
		
		soft_i2c_read(&i2c_dev, reg, p_data, read_size);
	#endif
}
