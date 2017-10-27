
#ifndef i2c_h
#define i2c_h

void i2c_fail(unsigned char status);
void write_external_eeprom(unsigned char, unsigned char);
unsigned char read_external_eeprom(unsigned char);

#endif
