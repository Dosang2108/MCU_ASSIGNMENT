//#include "scheduler.h"
//
//sTask SCH_tasks_G[SCH_MAX_TASK];
//
//int numTask = 0;
//
//void SCH_Init(void) {
//	unsigned char i;
//	for (i = 0; i < SCH_MAX_TASK; i++) {
//		SCH_Delete_Task(i);
//	}
//}
//
//
//void SCH_Add_Task(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD) {
//    if (numTask < SCH_MAX_TASK) {
//        uint8_t index;
//        for (index = 0; index < SCH_MAX_TASK; index++) {
//            if (SCH_tasks_G[index].pTask != 0) continue;
//
//            SCH_tasks_G[index].pTask = pFunction;
//            SCH_tasks_G[index].Delay = DELAY / TIME_CYCLE;
//            SCH_tasks_G[index].Period = PERIOD / TIME_CYCLE;
//            SCH_tasks_G[index].RunMe = 0;
//            SCH_tasks_G[index].TaskID = index;
//            numTask++;
//            break;
//        }
//    }
//}
//
//void SCH_Update(void) {
//	unsigned char index;
//	for (index = 0; index < SCH_MAX_TASK; index++) {
//		if (SCH_tasks_G[index].pTask) {
//			if (SCH_tasks_G[index].Delay == 0) {
//				SCH_tasks_G[index].RunMe += 1;
//				if (SCH_tasks_G[index].Period) {
//					SCH_tasks_G[index].Delay = SCH_tasks_G[index].Period;
//				}
//			}
//			else {
//				SCH_tasks_G[index].Delay -= 1;
//			}
//		}
//	}
//}
//
//void SCH_Dispatch_Tasks(void) {
//	unsigned char index;
//	for (index = 0; index < SCH_MAX_TASK; index++) {
//		if (SCH_tasks_G[index].RunMe > 0) {
//			(*SCH_tasks_G[index].pTask)();
//			SCH_tasks_G[index].RunMe -= 1;
//			if (SCH_tasks_G[index].Period == 0) SCH_Delete_Task(index);
//		}
//	}
//}
//
//void SCH_Delete_Task(uint32_t taskID) {
//	if (taskID >= SCH_MAX_TASK || SCH_tasks_G[taskID].pTask == 0) return;
//	SCH_tasks_G[taskID].pTask = 0x0000;
//	SCH_tasks_G[taskID].Delay = 0;
//	SCH_tasks_G[taskID].Period = 0;
//	SCH_tasks_G[taskID].RunMe = 0;
//}

#include "scheduler.h"

sTask SCH_tasks_G[SCH_MAX_TASK];
uint32_t current_time = 0;
uint8_t task_count = 0;

uint8_t ready_queue[SCH_MAX_TASK];
uint8_t queue_head = 0, queue_tail = 0;

void SCH_Init(void) {
    current_time = 0;
    task_count = 0;
    queue_head = queue_tail = 0;

    for (int i = 0; i < SCH_MAX_TASK; i++) {
        SCH_tasks_G[i].Active = 0;
    }
}

void SCH_Add_Task(void (*pFunction)(void), uint32_t DELAY, uint32_t PERIOD) {
    if (task_count >= SCH_MAX_TASK) return;

    uint8_t index;
    for (index = 0; index < SCH_MAX_TASK; index++) {
        if (!SCH_tasks_G[index].Active) break;
    }

    if (index >= SCH_MAX_TASK) return;

    SCH_tasks_G[index].pTask = pFunction;
    SCH_tasks_G[index].ExecuteTime = current_time + (DELAY / TIME_CYCLE);
    SCH_tasks_G[index].Period = PERIOD / TIME_CYCLE;
    SCH_tasks_G[index].Active = 1;
    task_count++;
}

void SCH_Update(void) {
    current_time++;
}

void SCH_Dispatch_Tasks(void) {
    for (uint8_t i = 0; i < SCH_MAX_TASK; i++) {
        if (SCH_tasks_G[i].Active && SCH_tasks_G[i].ExecuteTime <= current_time) {
            ready_queue[queue_tail] = i;
            queue_tail = (queue_tail + 1) % SCH_MAX_TASK;
        }
    }
    while (queue_head != queue_tail) {
        uint8_t task_index = ready_queue[queue_head];
        queue_head = (queue_head + 1) % SCH_MAX_TASK;
        sTask* task = &SCH_tasks_G[task_index];
        if (task->Active) {
            (*(task->pTask))();

            if (task->Period > 0) {
                task->ExecuteTime += task->Period;
            } else {
                task->Active = 0;
                task_count--;
            }
        }
    }
}

void SCH_Delete_Task(uint32_t taskID) {
    if (taskID < SCH_MAX_TASK && SCH_tasks_G[taskID].Active) {
        SCH_tasks_G[taskID].Active = 0;
        task_count--;
    }
}
