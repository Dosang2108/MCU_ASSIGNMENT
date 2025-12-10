/*
 * traffic_light.c
 *
 *  Created on: Dec 6, 2025
 *      Author: Lolle
 */
#include "traffic_light.h"
#include "software_timer.h"

void TrafficLight1Control(int state){
	switch (state) {
		case RED:
			HAL_GPIO_WritePin(TRAFFIC_A0_GPIO_Port,TRAFFIC_A0_Pin,SET);
			HAL_GPIO_WritePin(TRAFFIC_A1_GPIO_Port,TRAFFIC_A1_Pin,SET);
			break;
		case YELLOW:
			HAL_GPIO_WritePin(TRAFFIC_A0_GPIO_Port,TRAFFIC_A0_Pin,RESET);
		    HAL_GPIO_WritePin(TRAFFIC_A1_GPIO_Port,TRAFFIC_A1_Pin,SET);
			break;
		case GREEN:
			HAL_GPIO_WritePin(TRAFFIC_A0_GPIO_Port,TRAFFIC_A0_Pin,SET);
		    HAL_GPIO_WritePin(TRAFFIC_A1_GPIO_Port,TRAFFIC_A1_Pin,RESET);
			break;
		default:
			HAL_GPIO_WritePin(TRAFFIC_A0_GPIO_Port,TRAFFIC_A0_Pin,RESET);
		    HAL_GPIO_WritePin(TRAFFIC_A1_GPIO_Port,TRAFFIC_A1_Pin,RESET);
			break;
	}
}

void TrafficLight2Control(int state){
	switch (state) {
		case RED:
			HAL_GPIO_WritePin(TRAFFIC_B0_GPIO_Port,TRAFFIC_B0_Pin,SET);
			HAL_GPIO_WritePin(TRAFFIC_B1_GPIO_Port,TRAFFIC_B1_Pin,SET);
			break;
		case YELLOW:
			HAL_GPIO_WritePin(TRAFFIC_B0_GPIO_Port,TRAFFIC_B0_Pin,RESET);
		    HAL_GPIO_WritePin(TRAFFIC_B1_GPIO_Port,TRAFFIC_B1_Pin,SET);
			break;
		case GREEN:
			HAL_GPIO_WritePin(TRAFFIC_B0_GPIO_Port,TRAFFIC_B0_Pin,SET);
		    HAL_GPIO_WritePin(TRAFFIC_B1_GPIO_Port,TRAFFIC_B1_Pin,RESET);
			break;
		default:
			HAL_GPIO_WritePin(TRAFFIC_B0_GPIO_Port,TRAFFIC_B0_Pin,RESET);
		    HAL_GPIO_WritePin(TRAFFIC_B1_GPIO_Port,TRAFFIC_B1_Pin,RESET);
			break;
	}
}

void TwoWayControl(int state_1, int state_2){
	TrafficLight1Control(state_1);
	TrafficLight2Control(state_2);
}


int sw=0;
void TrafficBlink(int state){
	switch(state){
		case RED:
			if(timer_flag[0]) sw=1- sw;
			if(sw){
				TrafficLight1Control(RED);
				TrafficLight2Control(RED);
				setTimer(0, BLINK_TIME);
			} else {
				TrafficLight1Control(OFF_STATE);
				TrafficLight2Control(OFF_STATE);
				setTimer(0, BLINK_TIME);
			}
			break;
		case YELLOW:
			if(timer_flag[0]) sw=1- sw;
			if(sw){
				TrafficLight1Control(YELLOW);
				TrafficLight2Control(YELLOW);
				setTimer(0, BLINK_TIME);
			} else {
				TrafficLight1Control(OFF_STATE);
				TrafficLight2Control(OFF_STATE);
				setTimer(0, BLINK_TIME);
			}
			break;
		case GREEN:
			if(timer_flag[0]) sw=1- sw;
			if(sw){
				TrafficLight1Control(GREEN);
				TrafficLight2Control(GREEN);
				setTimer(0, BLINK_TIME);
			} else {
				TrafficLight1Control(OFF_STATE);
				TrafficLight2Control(OFF_STATE);
				setTimer(0, BLINK_TIME);
			}
			break;
		default : break;

	}
}
