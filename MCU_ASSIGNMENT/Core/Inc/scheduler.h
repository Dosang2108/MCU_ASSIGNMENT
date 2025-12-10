/*
 * scheduler.h
 *
 *  Created on: Oct 27, 2025

 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#define NUM_TASK 20
#define TIME_CYCLE 10
#include <stdint.h>
typedef struct {
	void (*pFunction) (void);
	uint32_t DELAY;
	uint32_t PERIOD;
	uint32_t TASK_ID;
	uint32_t NEXT_RUN;

} Task;

void SCH_Init();
uint32_t SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t taskID);
#endif /* INC_SCHEDULER_H_ */
