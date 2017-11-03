#ifndef I2C_H
#define I2C_H

void init_i2c(void);
void i2c_wait_for_idle(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
int i2c_read(unsigned char ack);
unsigned char i2c_write(unsigned char i2c_write_data);

#endif
