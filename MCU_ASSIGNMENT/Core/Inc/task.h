/*
 * task.h
 *
 *  Created on: Nov 12, 2025
 *      Author: Sang
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

#include "button.h"
#include "software_timer.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"
#include "fsm_handle.h"
#include "main.h"

void TASK_LED_BLINK(void);
void TASK_ScanButtons(void);
void TASK_SoftwareTimer(void);

void TASK_FSM(void);

#endif /* INC_TASK_H_ */
