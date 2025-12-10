/*
 * traffic_light.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_
#include "main.h"
#include "software_timer.h"


#define RED 0
#define YELLOW 1
#define GREEN 2
#define OFF_STATE 3
#define BLINK_TIME 250

void TrafficLight1Control(int state);
void TrafficLight2Control(int state);


void TwoWayControl(int state_1, int state_2);

void TrafficBlink(int state);

#endif /* INC_TRAFFIC_LIGHT_H_ */
