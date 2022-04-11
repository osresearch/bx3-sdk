#ifndef _I2C_BUS_H
#define _I2C_BUS_H


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


void i2c_bus_init(void);
void i2c_bus_uninit(void);
void i2c_bus_write(uint8_t dev_addr, int8_t reg, uint8_t data);
void i2c_bus_read(uint8_t dev_addr, int8_t reg, uint8_t *p_data, uint16_t read_size);


#endif
