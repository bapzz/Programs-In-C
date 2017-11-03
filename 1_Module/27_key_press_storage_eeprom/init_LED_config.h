#ifndef INIT_LED_CONFIG_H
#define INIT_LED_CONFIG_H

#define ON 1
#define OFF 0

#define LED1 PORTBbits.RB0
#define LED2 PORTBbits.RB1
#define LED3 PORTBbits.RB2
#define LED4 PORTBbits.RB3

void init_LED_config(void);

#endif
