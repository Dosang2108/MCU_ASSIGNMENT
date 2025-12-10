/*
 * software_timer.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIMER_CYCLE 10

#include"main.h"
extern volatile int timerCounter [5];
extern volatile int timer_flag [5];

void setTimer(int num, int duration);

void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
