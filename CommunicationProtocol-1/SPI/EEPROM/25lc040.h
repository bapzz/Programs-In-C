#ifndef EEPROM_25LC040_H
#define EEPROM_25LC040_H

#define WRITE_ENABLE	0x06
#define READ_INSTR		0x03
#define WRITE_INSTR		0x02

void eeprom_25lc040_byte_write(unsigned char memory_loc, unsigned char data);
void eeprom_25lc040_page_write(unsigned char memory_loc, unsigned char *data, unsigned char count);
unsigned char eeprom_25lc040_read(unsigned char memory_loc);

#endif
