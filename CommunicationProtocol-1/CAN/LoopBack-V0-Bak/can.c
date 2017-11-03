#include "pic_specific.h"
#include "can.h"
#include "main.h"

/* Global Variables */
unsigned char can_payload[13];

typedef enum _CanOpMode
{
	e_can_op_mode_bits    = 0xE0,			/* Use this to access opmode bits */
	e_can_op_mode_normal  = 0x00,
	e_can_op_mode_sleep   = 0x20,
	e_can_op_mode_loop    = 0x40,
	e_can_op_mode_listen  = 0x60,
	e_can_op_mode_config  = 0x80
} CanOpMode;

/* Configure the CAN Module */
void init_can(void)
{
	/* CAN_TX = RB2, CAN_RX = RB3 */
	TRISB2 = 0;								/* CAN TX */
	TRISB3 = 1;								/* CAN RX */

	/* Enter CAN module into config mode */
	CANSTAT &= 0x1F;						/* clear previous mode */
	CANSTAT |= 0x80;                       	/* set new mode */

	/* Wait untill desired mode is set */
	while (CANSTAT != 0x80);

	/* Enter CAN module into Mode 2 */
	ECANCON = 0x80;

	/* Initialize CAN Timing 8MHz */
	BRGCON1 = 0xE1;							/* 1110 0001, SJW=4, TQ, BRP 4 */
	BRGCON2 = 0x1B;							/* 0001 1011, SEG2PHTS 1 sampled once PS1=4TQ PropagationT 4TQ */
	BRGCON3 = 0x03;							/* 0000 0011, PS2, 4TQ */

	/*
	 * Setup Programmable buffers
	 * B0 is a receive buffer AND B2,B3,B4,B5 are Transmit buffers
	 */
	BSEL0 = 0xF8;							/* 1111 10-- */

	/* Initialize Receive Masks */
	RXM0EIDH = 0x00;						/* 0's for EID and SID */
	RXM0EIDL = 0x00;
	RXM0SIDH = 0xFF;						/* Standard ID FILTER */
	RXM0SIDL = 0x80;

	RXM1EIDH = 0x00;    
	RXM1EIDL = 0x00;
	RXM1SIDH = 0xFF;
	RXM1SIDL = 0x80;

	/*
	 * Enable Filters
	 * Filter 0
	 */
	RXFCON0 = 0x01;     
	RXFCON1 = 0x00;							/* Disable all from Filter 1-15 */

	/* Assign Filters to Masks */
	MSEL0 = 0xFF;							/* Assign Filters 0-3 to No mask */
	MSEL1 = 0xFF;							/* Assign Filters 4-7 to No mask */
	MSEL2 = 0xFF;							/* Assign Filters 8-11 to No mask */
	MSEL3 = 0xFF;							/* Assign Filters 12-15 to No mask */

	/*
	 * Initialize Receive Filters
	 * Filter 0 = 0xFFC
	 */
	RXF0EIDH = 0x00;
	RXF0EIDL = 0x00;
	RXF0SIDH = 0x6B;
	RXF0SIDL = 0xC0;

	/* Filter 1 = 0xFFC */
	RXF1EIDH = 0x00;
	RXF1EIDL = 0x00;
	RXF1SIDH = 0xFF;
	RXF1SIDL = 0xC0;

	/* Enter CAN module into Loop back mode */
	CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_loop);

	/* Set Receive Mode for buffers */
	RXB0CON = 0x00;
	RXB1CON = 0x00;
}

/* Check the buffers, if it have message */
unsigned char can_receive(void)
{
	unsigned char rx_msg_flag = 0;

	if (RXB0FUL) /* CheckRXB0 */
	{
		can_payload[EIDH] = RXB0EIDH;
		can_payload[EIDL] = RXB0EIDL;
		can_payload[SIDH] = RXB0SIDH;
		can_payload[SIDL] = RXB0SIDL;
		can_payload[DLC] = RXB0DLC;
		can_payload[D0] = RXB0D0;
		can_payload[D1] = RXB0D1;
		can_payload[D2] = RXB0D2;
		can_payload[D3] = RXB0D3;
		can_payload[D4] = RXB0D4;
		can_payload[D5] = RXB0D5;
		can_payload[D6] = RXB0D6;
		can_payload[D7] = RXB0D7;

		RXB0FUL = 0;
		rx_msg_flag = 0x01;
	}
	else if (RXB1FUL) /* CheckRXB1 */
	{
		can_payload[EIDH] = RXB1EIDH;
		can_payload[EIDL] = RXB1EIDL;
		can_payload[SIDH] = RXB1SIDH;
		can_payload[SIDL] = RXB1SIDL;
		can_payload[DLC] = RXB1DLC;
		can_payload[D0] = RXB1D0;
		can_payload[D1] = RXB1D1;
		can_payload[D2] = RXB1D2;
		can_payload[D3] = RXB1D3;
		can_payload[D4] = RXB1D4;
		can_payload[D5] = RXB1D5;
		can_payload[D6] = RXB1D6;
		can_payload[D7] = RXB1D7;

		RXB1FUL = 0;
		rx_msg_flag = 0x01;
	}
	else if (B0RXFUL) /* CheckB0 */
	{
		can_payload[EIDH] = B0EIDH;
		can_payload[EIDL] = B0EIDL;
		can_payload[SIDH] = B0SIDH;
		can_payload[SIDL] = B0SIDL;
		can_payload[DLC] = B0DLC;
		can_payload[D0] = B0D0;
		can_payload[D1] = B0D1;
		can_payload[D2] = B0D2;
		can_payload[D3] = B0D3;
		can_payload[D4] = B0D4;
		can_payload[D5] = B0D5;
		can_payload[D6] = B0D6;
		can_payload[D7] = B0D7;

		B0RXFUL = 0;
		rx_msg_flag = 0x01;
	}

	if (rx_msg_flag == 0x01)
	{
		rx_msg_flag = 0x00;
		RXB1IF = 0;			/* A CAN Receive Buffer has received a new message */

		return TRUE;
	}
	else
	{
		return FALSE;
	}    
}

/* Transmit Sample Mesaage */
void can_transmit(void)
{
	TXB0EIDH = 0x00;		/* Extended Identifier */
	TXB0EIDL = 0x00;		/* Extended Identifier */

	/* 0x35E  0110 1011 110 */
	TXB0SIDH = 0x6B;		/* Standard Identifier */
	TXB0SIDL = 0xC0;		/* Standard Identifier */

	TXB0DLC = 0x04;			/* Data Length Count */
	TXB0D0 = 'A';			/* DataByte 0 */
	TXB0D1 = 'B';			/* DataByte 1 */
	TXB0D2 = 'C';			/* DataByte 2 */
	TXB0D3 = 'D';			/* DataByte 3 */
	TXB0D4 = 'E';			/* DataByte 4 */
	TXB0D5 = 'F';			/* DataByte 5 */
	TXB0D6 = 'G';			/* DataByte 6 */
	TXB0D7 = 'H';			/* DataByte 7 */

	TXB0REQ = 1;			/* Set the buffer to transmit */
}
