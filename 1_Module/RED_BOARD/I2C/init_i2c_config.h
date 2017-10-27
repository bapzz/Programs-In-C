
#ifndef init_i2c_config_h
#define init_i2c_config_h

#define control_in 0xA0
#define control_out 0xA1

#define SDA PORTCbits.RC4
#define SCL PORTCbits.RC3

#define WAIT_MSSP               while(!PIR1bits.SSPIF);  \
	                        PIR1bits.SSPIF = 0;

#define ack(data)               if(SSPCON2bits.ACKSTAT)  \
				{			 \
					i2c_fail(data);	 \
				}				
#define send_info(data) 	SSPBUF = data;           \
				WAIT_MSSP
#define start 			SSPCON2bits.SEN = 1;      \
				WAIT_MSSP
#define stop 			SSPCON2bits.PEN = 1;      \
				WAIT_MSSP
#define restart 		SSPCON2bits.RSEN = 1;     \
				WAIT_MSSP
#define nack 			SSPCON2bits.ACKDT = 1;    \
				SSPCON2bits.ACKEN = 1

void init_i2c_config(void);

#endif
