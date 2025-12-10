/*
 * fsm_handle.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#ifndef INC_FSM_HANDLE_H_
#define INC_FSM_HANDLE_H_

#include "global.h"
#include "traffic_light.h"
#include "button.h"
#include "lcd_i2c.h"
#include "software_timer.h"
#include "fsm_manual.h"

void fsm_handle_run(void);

#endif /* INC_FSM_HANDLE_H_ */
