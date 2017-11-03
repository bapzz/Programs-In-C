#ifndef I2C_H
#define I2C_H

#include "config.h"

void init_i2c(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_restart(void);
void i2c_wait(void);
void i2c_ack(void);
void i2c_nak(void);
unsigned char i2c_read(void);
void i2c_write(unsigned char data);

#endif
