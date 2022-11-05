/*
 * fsm_normal.c
 *
 *  Created on: Nov 5, 2022
 *      Author: trong
 */

#include "fsm_normal.h"

//if any button signal is regconized, timer1 will be set to 10s
//after 10s without any buttons pushed, the mode will be changed to AUTO
void fsm_simple_buttons_run() {
	switch (mode) {
	//In INIT state, it will initialize value of counter and change mode into AUTO mode

	case INIT:
		counter = 9;
		update7SEG(counter);
		setTimer3(1000);
		mode = AUTO;
		break;
	case RESET_MODE:
		//if push RESET button, counter will be reset to 0
		if (isButtonPressed(0) == 1) {
			setTimer1(10000);
			mode = RESET_MODE;
			counter = 0;
			update7SEG(counter);
		}
		//if push INC button, counter will be plus 1
		else if (isButtonPressed(1) == 1) {
			setTimer1(10000);
			mode = INC;
			if (counter == 9) {
				counter = 0;
				update7SEG(counter);
			} else {
				counter = counter + 1;
				update7SEG(counter);
			}
		}
		//if push DEC button, counter will be minus 1
		else if (isButtonPressed(2) == 1) {
			setTimer1(10000);
			mode = DEC;
			if (counter == 0) {
				counter = 9;
				update7SEG(counter);
			} else {
				counter = counter - 1;
				update7SEG(counter);
			}

		} else if (timer1_flag == 1) {
			setTimer2(1000);
			mode = AUTO;
		}
		break;
	case INC:
		if (isButtonPressed(0) == 1) {
			setTimer1(10000);
			mode = RESET_MODE;
			counter = 0;
			update7SEG(counter);
		} else if (isButtonPressed(1) == 1) {
			setTimer1(10000);
			mode = INC;
			if (counter == 9) {
				counter = 0;
				update7SEG(counter);
			} else {
				counter = counter + 1;
				update7SEG(counter);
			}
		} else if (isButtonPressed(2) == 1) {
			setTimer1(10000);
			mode = DEC;
			if (counter == 0) {
				counter = 9;
				update7SEG(counter);
			} else {
				counter = counter - 1;
				update7SEG(counter);
			}
		}

		else if (timer1_flag == 1) {
			setTimer2(1000);
			mode = AUTO;
		}
		break;
	case DEC:
		if (isButtonPressed(0) == 1) {
			setTimer1(10000);
			mode = RESET_MODE;
			counter = 0;
			update7SEG(counter);
		} else if (isButtonPressed(1) == 1) {
			setTimer1(10000);
			mode = INC;
			if (counter == 9) {
				counter = 0;
				update7SEG(counter);
			} else {
				counter = counter + 1;
				update7SEG(counter);
			}
		} else if (isButtonPressed(2) == 1) {
			setTimer1(10000);
			mode = DEC;
			if (counter == 0) {
				counter = 9;
				update7SEG(counter);
			} else {
				counter = counter - 1;
				update7SEG(counter);
			}
		}

		else if (timer1_flag == 1) {
			setTimer2(1000);
			mode = AUTO;
		}
		break;
	case AUTO:
		if (timer2_flag == 1) {
			setTimer2(1000);
			display7SEG(counter);
			if (counter == 0) {
				counter = 0;
			} else {
				counter--;
			}
		}
		if (isButtonPressed(0) == 1) {
			setTimer1(10000);
			mode = RESET_MODE;
			counter = 0;
			update7SEG(counter);
		} else if (isButtonPressed(1) == 1) {
			setTimer1(10000);
			mode = INC;
			if (counter == 9) {
				counter = 0;
				update7SEG(counter);
			} else {
				counter = counter + 1;
				update7SEG(counter);
			}
		} else if (isButtonPressed(2) == 1) {
			setTimer1(10000);
			mode = DEC;
			if (counter == 0) {
				counter = 9;
				update7SEG(counter);
			} else {
				counter = counter - 1;
				update7SEG(counter);
			}
		}
		break;
	default:
		break;
	}
}
