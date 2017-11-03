#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include "init_LED_config.h"
#include "init_DKP_config.h"
#include "scan_digital_keypad.h"
#include "train.h"

#define DELY 50000

int state_flag = 0;
int flag = 0;

unsigned char key;

#endif
