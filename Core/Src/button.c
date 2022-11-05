/*
 * button.c
 *
 *  Created on: Sep 30, 2022
 *      Author: trong
 */

#include "button.h"

//signal of buttons
static int buttonBuffer[NUM_OF_BUTTONS] = { NORMAL_STATE };
//debouncing buffers help to stabilize signal from input
static int debounceButtonBuffer1[NUM_OF_BUTTONS] = { NORMAL_STATE };
static int debounceButtonBuffer2[NUM_OF_BUTTONS] = { NORMAL_STATE };
//signal that indicates whether we push the button for long time
static int longPressButtonBuffer[NUM_OF_BUTTONS] = { NORMAL_STATE };

//bool signals indicate state of button
int button_flag[NUM_OF_BUTTONS] = { 0 };
int longButton_flag[NUM_OF_BUTTONS] = { 0 };
int isLongButtonPressed[NUM_OF_BUTTONS] = { 0 };
int TimeOutForKeyPress[NUM_OF_BUTTONS];

void init_button() {
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, NORMAL_STATE);
	HAL_GPIO_WritePin(INC_GPIO_Port, INC_Pin, NORMAL_STATE);
	HAL_GPIO_WritePin(DEC_GPIO_Port, DEC_Pin, NORMAL_STATE);
}

int isButtonPressed(int index) {
	if (button_flag[index] == 1) {
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(int index) {
	if (longButton_flag[index] == 1) {
		longButton_flag[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index) {
	button_flag[index] = 1;
}

void longKeyProcess(int index) {
	longButton_flag[index] = 1;
}

void getKeyInput() {
	init_button();
	//we use same method for reading input from the buttons
	for (int i = 0; i < NUM_OF_BUTTONS; i++) {
		debounceButtonBuffer1[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = buttonBuffer[i];

		//read input corresponding to the [i] button
		if (i == 0) {
			buttonBuffer[i] = HAL_GPIO_ReadPin(RESET_GPIO_Port,
			RESET_Pin);
		} else if (i == 1) {
			buttonBuffer[i] = HAL_GPIO_ReadPin(INC_GPIO_Port,
			INC_Pin);
		} else if (i == 2) {
			buttonBuffer[i] = HAL_GPIO_ReadPin(DEC_GPIO_Port,
			DEC_Pin);
		}
		//debouncing the interference signal
		if ((debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
				&& (debounceButtonBuffer2[i] == buttonBuffer[i])) {
			//this below condition helps us to indicate whether we push the button or not
			if (buttonBuffer[i] != longPressButtonBuffer[i]) {
				longPressButtonBuffer[i] = buttonBuffer[i];

				//if we first time push the button for long time,
				//it will store with the signal isLongButtonPressed and set wait time to 3s
				if (buttonBuffer[i] == PRESSED_STATE
						&& isLongButtonPressed[i] == 0) {
					TimeOutForKeyPress[i] = TIME_OUT_FOR_KEY_PRESS;
					subKeyProcess(i);
				}
				//if we still push the button for long time,
				//it will regconize and change the wait time to 1s
				else if (buttonBuffer[i] == PRESSED_STATE
						&& isLongButtonPressed[i] == 1) {
					TimeOutForKeyPress[i] = TIME_OUT_FOR_LONG_KEY_PRESS;
					subKeyProcess(i);
				}

				else {
					isLongButtonPressed[i] = 0;
				}
			}

			else {
				//counter reference counts down until 0, then it will activate the button again
				TimeOutForKeyPress[i]--;
				if (TimeOutForKeyPress[i] == 0) {
					isLongButtonPressed[i] = 1;
					longKeyProcess(i);
					longPressButtonBuffer[i] = NORMAL_STATE;
				}

				else if (isLongButtonPressed[i] == 1) {
					isLongButtonPressed[i] = 0;
				}
			}
		}
	}
}

