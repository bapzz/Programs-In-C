#ifndef Ds1338_H
#define Ds1338_H

#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07

void init_ds1338(void);
void write_ds1338(unsigned char address1,  unsigned char data);
unsigned char read_ds1338(unsigned char address1);

#endif
