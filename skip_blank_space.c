#include <ctype.h>

#define BT_WCM_SKIP_CHAR(str)        			((*str)++)												/* Macro to skip a character of string*/

#define BT_WCM_SKIP_WHITESPACES(str) 			while (isspace(**str)) { BT_WCM_SKIP_CHAR(str); }  		/* Macro to skip the blank spaces*/
