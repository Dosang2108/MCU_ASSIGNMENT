/*
 * button.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Sang
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

#define LONG_PRESS_TIME 30

#define AUTO_REPEAT_TIME 2

void button_init(void);
int isButtonPressed(int button);
void getKeyInput(int button);

#endif /* INC_BUTTON_H_ */
