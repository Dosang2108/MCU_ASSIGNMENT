/*
 * fsm_handle.c
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#include "fsm_handle.h"
#include <string.h>

static int handle_toggle_state = 0;

void lcd_center_text1(int row, char *str) {
    int len = strlen(str);
    int padding = 0;
    if (len < 16) {
        padding = (16 - len) / 2;
    }
    lcd_gotoxy(padding, row);
    lcd_write_string(str);
}

void displayHandleInfo() {
	if (handle_pattern == 0) {
		lcd_center_text1(0, "Lane 0: RED");
		lcd_center_text1(1, "Lane 1: GREEN");
	}
	else {
		lcd_center_text1(0, "Lane 0: GREEN");
		lcd_center_text1(1, "Lane 1: RED");
	}
}

void fsm_handle_run(void) {
	if (MODE == MODE_HANDLE) {

		displayHandleInfo();

		if (isButtonPressed(3) == 1) {
			TrafficLight1Control(OFF_STATE);
			TrafficLight2Control(OFF_STATE);
			LED_STATE[0] = INIT_STATE;
			LED_STATE[1] = INIT_STATE;
			changeMode(MODE_1);
			return;
		}

		if (isButtonPressed(1) == 1) {
			handle_pattern = 0;
			handle_apply_initial();
			handle_toggle_state = 1;
			setTimer(2, 25);
		}

		if (isButtonPressed(2) == 1) {
			handle_pattern = 1;
			handle_apply_initial();
			handle_toggle_state = 1;
			setTimer(2, 25);
		}

		if (timer_flag[2] == 1) {
			handle_toggle_state = 1 - handle_toggle_state;

			if (handle_toggle_state == 1) {
				handle_apply_initial();
			}
			else {
				TrafficLight1Control(OFF_STATE);
				TrafficLight2Control(OFF_STATE);
			}

			setTimer(2, 25);
		}
	}
}
