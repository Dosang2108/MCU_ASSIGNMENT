/*
 * fsm_automatic.c
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#include "fsm_automatic.h"
#include "fsm_manual.h"

/* */
void fsm_automatic(int lane) {
    switch(LED_STATE[lane]) {
        case INIT_STATE:
            if (lane == 0) {
                LED_STATE[lane] = RED_STATE;
                setTrafficLight(lane, RED);
                setTimer(lane, RED_DURATION * 1000);
            }
            else {
                LED_STATE[lane] = GREEN_STATE;
                setTrafficLight(lane, GREEN);
                setTimer(lane, GREEN_DURATION * 1000);
            }
            break;
        case RED_STATE:
            setTrafficLight(lane, RED);
            if (timer_flag[lane] == 1) {
                LED_STATE[lane] = GREEN_STATE;
                setTimer(lane, GREEN_DURATION * 1000);
            }
            break;
        case GREEN_STATE:
            setTrafficLight(lane, GREEN);
            if (timer_flag[lane] == 1) {
                LED_STATE[lane] = YELLOW_STATE;
                setTimer(lane, YELLOW_DURATION * 1000);
            }
            break;
        case YELLOW_STATE:
            setTrafficLight(lane, YELLOW);
            if (timer_flag[lane] == 1) {
                LED_STATE[lane] = RED_STATE;
                setTimer(lane, RED_DURATION * 1000);
            }
            break;
        default:
            break;
    }

    if (timerCounter[lane] % 100 == 0 || timerCounter[lane] > (timerCounter[lane]/100)*100 + 95) {
        int time_display = timerCounter[lane] / 100 + 1;

        char str[16];
        lcd_gotoxy(0, lane);
        if(lane==0)
        	snprintf(str, sizeof(str), "L%d:%02d      MODE", lane + 1, time_display);
        else
        	snprintf(str, sizeof(str), "L%d:%02d      AUTO", lane + 1, time_display);
        lcd_write_string(str);
    }
}

void fsm_automatic_run() {
	if (MODE == MODE_1) {
		fsm_automatic(0);
		fsm_automatic(1);

		if (isButtonPressed(0) == 1) {
			start_edit_session();
			tempDuration = RED_DURATION;
			MODE = MODE_2;
			lcd_clear();
			setTimer(3, BLINK_TIME);
		}

		if (isButtonPressed(3) == 1) {
			MODE = MODE_HANDLE;
			lcd_clear();
			setTimer(2, 3000);
		}
	}
}
