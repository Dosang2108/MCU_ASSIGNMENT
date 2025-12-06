/*
 * fsm_automatic.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

#include "global.h"
#include "traffic_light.h"
#include "software_timer.h"
#include "button.h"
#include "lcd_i2c.h"
#include <stdio.h>

void fsm_automatic_run(void);
void fsm_automatic(int lane);

#endif /* INC_FSM_AUTOMATIC_H_ */
