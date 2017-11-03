#ifndef __I2C_H
#define __I2C_H

// Define i2c pins
#define SDA					RC4				// Data pin for i2c
#define SCK					RC3				// Clock pin for i2c
#define SDA_DIR				TRISC4			// Data pin direction
#define SCK_DIR				TRISC3			// Clock pin direction

// Define i2c speed
#define I2C_SPEED			100				// kbps 
#define HALF_BIT_DELAY		500 / I2C_SPEED	// usec

// Define macros
#define SET_SDA_LOW			SDA_DIR = 0
#define SET_SDA_HIGH		SDA_DIR = 1
#define SET_SCK_LOW			SCK_DIR = 0
#define SET_SCK_HIGH		SCK_DIR = 1

//Function Declarations
void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_send_ack(void);
void i2c_send_nack(void);
bit  i2c_write(unsigned char);
unsigned char i2c_read(unsigned char);

#endif
