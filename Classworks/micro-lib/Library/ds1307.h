#ifndef DS1307_H
#define DS1307_H

#include "config.h"
#include "i2c.h"

#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07

void init_ds1307(void);
void write_ds1307(unsigned char address,  unsigned char data);
unsigned char read_ds1307(unsigned char address);

#endif
