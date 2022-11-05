/*
 * lt1.h
 *
 *  Created on: Sep 24, 2022
 *      Author: trong
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "global.h"

extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;

void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);
void timerRun();


#endif /* INC_TIMER_H_ */
