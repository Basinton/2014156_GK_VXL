/*
 * button.h
 *
 *  Created on: Sep 30, 2022
 *      Author: trong
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define NORMAL_STATE 				SET
#define PRESSED_STATE 				RESET
//define number of buttons we will use
#define NUM_OF_BUTTONS				3
//define the time when we push the button for long time (3s)
#define TIME_OUT_FOR_KEY_PRESS		300
//define the time when we have already pushed long time before (1s)
#define TIME_OUT_FOR_LONG_KEY_PRESS	100


extern int button_flag[NUM_OF_BUTTONS];

extern int doubleClick_flag[NUM_OF_BUTTONS];

void getKeyInput();
void subKeyProcess(int index);
int isButtonPressed(int index);
int isButtonLongPressed(int index);

#endif /* INC_BUTTON_H_ */
