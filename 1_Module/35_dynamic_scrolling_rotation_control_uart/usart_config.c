#include "main.h"

void init_uart_config(void)
{
    // COnfigure the TXSTA register
//    TXSTA = 0X24;

    // Selects 8-bit transmission
    TX9 = 0;

    // Transmit enabled
    TXEN = 1;

    //EUSART Mode Select bit, select Asynchronous mode
    SYNC = 0;

    // Send Break character bit
    SENDB = 1;

    // High Baud rate Select bit
    BRGH = 1;

    // Transmit Shiift Register Status bit, Initially EMPTY
    TRMT = 1;

    // 9th bit of Transmit Data(For data or parity bit)
    TX9D = 0;

    // Configure TXBIT as an output pin
    TXBIT = 0;

    // Set the baud rate, high baud with 9600 bps
    SPBRG = 0x81;

    // Enable the receiver and serial port
    RCSTA = 0x90;

    // Enable the global interrupts
    GIE = 1;

    // Enable the peripheral interrupts
    PEIE = 1;
}
