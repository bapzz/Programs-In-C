#ifndef SPI_H
#define SPI_H

//#define BIT_BANGING

#define LO						0
#define HI						1
#define ENABLE					0
#define	DISABLE					1

#define SPI_MOSI				RC4
#define SPI_MISO				RC5
#define SPI_SCK					RC3
#define SPI_SS					RC2

#define ENABLE_CHIP_SELECT		RC2 = 0
#define DISABLE_CHIP_SELECT		RC2 = 1

void init_spi(void);
unsigned char spi_rw(char byte);

#endif
