/*
 * software_timer.c
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#include "software_timer.h"

volatile int timerCounter[4] = {0,0,0,0};
volatile int timer_flag[4]   = {0,0,0,0};

void setTimer(int num, int duration){
	timerCounter[num] = duration/TIMER_CYCLE;
	timer_flag[num] = 0;
}

void timerRun(){
	if(timerCounter[0] > 0){
		timerCounter[0]--;
		if(timerCounter[0] <= 0){
			timer_flag[0] = 1;
		}
	}
	if(timerCounter[1] > 0){
		timerCounter[1]--;
		if(timerCounter[1] <= 0){
			timer_flag[1] = 1;
		}
	}
	if(timerCounter[2] > 0){
		timerCounter[2]--;
		if(timerCounter[2] <= 0){
			timer_flag[2] = 1;
		}
	}
	if(timerCounter[3] > 0){
		timerCounter[3]--;
		if(timerCounter[3] <= 0){
			timer_flag[3] = 1;
		}
	}
}
