#ifndef INIT_LED_CONFIG_H
#define INIT_LED_CONFIG_H

#define LEDS PORTB
#define ON 0xFF
#define OFF 0x00

#define LED1 PORTBbits.RB0
#define LED2 PORTBbits.RB1
#define LED3 PORTBbits.RB2
#define LED4 PORTBbits.RB3
#define LED5 PORTBbits.RB4
#define LED6 PORTBbits.RB5

void init_LED_config(void);

#endif
