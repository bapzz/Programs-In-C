#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

#include "config.h"

#define MATRIX_KEYPAD_PORT		PORTB
#define NO_OF_ROWS			3
#define NO_OF_COLS			4

#define MK_SWITCH1			0	/* SW1 */
#define MK_SWITCH2			1	/* SW4 */
#define MK_SWITCH3			2	/* SW7 */
#define MK_SWITCH4			3	/* SW10 */
#define MK_SWITCH5			4	/* SW2 */
#define MK_SWITCH6			5	/* SW5 */
#define MK_SWITCH7			6	/* SW8 */
#define MK_SWITCH8			7	/* SW11 */
#define MK_SWITCH9			8	/* SW3 */
#define MK_SWITCH10			9	/* SW6 */
#define MK_SWITCH11			10	/* SW9 */
#define MK_SWITCH12			11	/* SW12 */

void init_matrix_keypad(void);
char scan_keypad(void);

#endif
