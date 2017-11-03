#ifndef INIT_LED_CONFIG_H
#define INIT_LED_CONFIG_H

#define ON 0
#define OFF 1
#define LEDS PORTD

#define LED1 PORTDbits.RD0
#define LED2 PORTDbits.RD1
#define LED3 PORTDbits.RD2
#define LED4 PORTDbits.RD3
#define LED5 PORTDbits.RD4
#define LED6 PORTDbits.RD5

void init_LED_config(void);

#endif
