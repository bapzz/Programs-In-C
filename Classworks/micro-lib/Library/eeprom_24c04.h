#ifndef EEPROM_24C04_H
#define EEPROM_24C04_H

#include "config.h"
#include "i2c.h"

#define WRITE_MODE		0xA0
#define READ_MODE		0xA1

void init_eeprom(void);
void write_eeprom(unsigned char address,  unsigned char data);
unsigned char read_eeprom(unsigned char address);

#endif
