/*
 * fsm_handle.c
 *
 * Created on: Dec 6, 2025
 * Author: Sang
 */

#include "fsm_handle.h"
#include <string.h>
#include <stdio.h>

static int is_transitioning = 0;

static int last_time_display = -1;
static int last_handle_pattern = -1;
static int last_transitioning = -1;


void displayHandleInfo() {
    if (is_transitioning) {
        int current_timer = timerCounter[2];
        int time_display = 0;
        if(current_timer > 0) {
             time_display = (current_timer - 1) / 100 + 1;
        }

        if (time_display != last_time_display || is_transitioning != last_transitioning) {
            char str[16];

            lcd_center_text1(0, "   WARNING!   ");
            snprintf(str, sizeof(str), "YELLOW TIME: %d", time_display);
            lcd_center_text1(1, str);

            last_time_display = time_display;
            last_transitioning = is_transitioning;
        }
    }
    else {

        if (handle_pattern != last_handle_pattern || is_transitioning != last_transitioning) {
            if (handle_pattern == 0) {
                lcd_gotoxy(0, 0);
                lcd_write_string("L0:RED     MODE");
                lcd_gotoxy(0, 1);
                lcd_write_string("L1:GREEN HANDLE");
            }
            else {
                lcd_gotoxy(0, 0);
                lcd_write_string("L0:GREEN   MODE");
                lcd_gotoxy(0, 1);
                lcd_write_string("L1:RED   HANDLE");
            }


            last_handle_pattern = handle_pattern;
            last_transitioning = is_transitioning;
            last_time_display = -1;
        }
    }
}

void handle_apply_final_state(void) {
    if (handle_pattern == 0) {
        TrafficLight1Control(RED);
        TrafficLight2Control(GREEN);
    }
    else {
        TrafficLight1Control(GREEN);
        TrafficLight2Control(RED);
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
            is_transitioning = 0;
            last_time_display = -1;
            last_handle_pattern = -1;
            last_transitioning = -1;

            changeMode(MODE_1);
            return;
        }

        if (isButtonPressed(1) == 1) {
            if (handle_pattern == 1 && is_transitioning == 0) {
                TrafficLight1Control(YELLOW);
                TrafficLight2Control(RED);
                setTimer(2, 3000);
                handle_pattern = 0;
                lcd_clear();
                is_transitioning = 1;
                last_time_display = -1;
            }
            else if (handle_pattern == 0 && is_transitioning == 0) {
                 handle_apply_final_state();
            }
        }

        if (isButtonPressed(2) == 1) {
            if (handle_pattern == 0 && is_transitioning == 0) {
                TrafficLight1Control(RED);
                TrafficLight2Control(YELLOW);
                setTimer(2, 3000);
                handle_pattern = 1;
                is_transitioning = 1;
                lcd_clear();
                last_time_display = -1;
            }
            else if (handle_pattern == 1 && is_transitioning == 0) {
                 handle_apply_final_state();
            }
        }

        if (is_transitioning == 1) {
            if (timer_flag[2] == 1) {
                handle_apply_final_state();
                is_transitioning = 0;
            }
        }
    }
}
