/*
 * global.h
 *
 *  Created on: Sep 30, 2022
 *      Author: trong
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "timer.h"
#include "button.h"
#include "led_display.h"

#define TIMER_CYCLE		10

#define INIT 			0
#define RESET_MODE		1
#define INC 			2
#define DEC	 			3
#define AUTO			4

extern int counter;

extern int mode;

#endif /* INC_GLOBAL_H_ */
