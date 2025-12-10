/*
 * fsm_manual.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#ifndef INC_FSM_MANUAL_H_
#define INC_FSM_MANUAL_H_

#include "global.h"
#include "traffic_light.h"
#include "software_timer.h"
#include "button.h"
#include "lcd_i2c.h"
#include <stdio.h>

void handle_apply_initial(void);
void start_edit_session(void);
void changeMode(int mode);
void end_edit_session_and_maybe_commit(void);
void displayDuration(int mode, int duration);
void blink_traffic_light(int color);
void fsm_manual_run(void);

#endif /* INC_FSM_MANUAL_H_ */
