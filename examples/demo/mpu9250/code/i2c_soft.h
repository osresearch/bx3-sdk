#ifndef _I2C_SOFT_H
#define _I2C_SOFT_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct {
	unsigned int GPIO_Pin;
}struct_gpio;

typedef struct {
	struct_gpio i2c_sda;
	struct_gpio i2c_sck;
	unsigned char i2c_addr;
	void (*i2c_nop)(void);
	void (*i2c_delay)(void);
}i2c_dev_str;

//these could change accordingly with the architecture
void i2c_init(i2c_dev_str *i2c_dev);
void i2c_deinit(i2c_dev_str *i2c_dev);
void i2c_sda_io_config(i2c_dev_str *i2c_dev, int flag);
int soft_i2c_read(i2c_dev_str *i2c_dev, unsigned char Reg, unsigned char *Data, unsigned int len);
int soft_i2c_write(i2c_dev_str *i2c_dev, unsigned char Reg, unsigned char *Data, unsigned int len);


#endif
