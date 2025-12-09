/*
 * scheduler.c
 *
 *  Created on: Oct 27, 2025
 *      Author: ADMIN
 */

#include "scheduler.h"

Task pTask[NUM_TASK];

uint8_t curr_task=0;
uint64_t tick=0;

void SCH_Init(){
	for(uint8_t i=0; i<NUM_TASK; i++){
		SCH_Delete_Task(i);
	}
	curr_task=0;
}

uint32_t SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(curr_task< NUM_TASK){
		pTask[curr_task].DELAY= DELAY;
		pTask[curr_task].NEXT_RUN= tick+(DELAY);
		pTask[curr_task].PERIOD= PERIOD;
		pTask[curr_task].TASK_ID= curr_task;
		pTask[curr_task].pFunction= pFunction;
		curr_task++;
		return curr_task-1;
	}
	return curr_task;

}

void SCH_Update(){
		tick++;
}

// scheduler.c

// 1. Sửa kiểu dữ liệu tham số giống với khai báo trong struct Task
// 2. Đổi logic từ == sang >= để tránh trôi task (miss deadline)
int runMe(uint64_t current_tick, uint32_t next_run){
    if(current_tick >= next_run) {
        return 1;
    }
    return 0;
}

// Trong hàm SCH_Dispatch_Tasks, gọi lại cho đúng:
void SCH_Dispatch_Tasks(void){
    for(int i=0; i< curr_task; i++){
        // Truyền đúng biến tick toàn cục
        if(runMe(tick, pTask[i].NEXT_RUN)){
            (*pTask[i].pFunction)();

            if(pTask[i].PERIOD==0){
                SCH_Delete_Task(i);
            }
            else {
                // Cập nhật thời gian chạy tiếp theo
                pTask[i].NEXT_RUN = tick + pTask[i].PERIOD; // Cộng dồn từ tick hiện tại để tránh trôi
            }
        }
    }
}

uint8_t SCH_Delete_Task(uint32_t taskID){
	if(taskID<curr_task){
		for(uint32_t i= taskID; i< curr_task-1; i++){
			pTask[i]= pTask[i+1];
		}
		curr_task--;
	}
	return taskID;
}
