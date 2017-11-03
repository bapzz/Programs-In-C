#ifndef INIT_LED_CONFIG_H
#define INIT_LED_CONFIG_H

#define ON 1
#define OFF 0

#define LED1 PORTBbits.RB0
#define LED2 PORTBbits.RB1
#define LED3 PORTBbits.RB2
#define LED4 PORTBbits.RB3
#define LED5 PORTBbits.RB4
#define LED6 PORTBbits.RB5
#define LED7 PORTBbits.RB6
#define LED8 PORTBbits.RB7

void init_LED_config(void);

#endif
