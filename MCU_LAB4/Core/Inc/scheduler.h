/*
 * scheduler.h
 *
 *  Created on: Nov 30, 2022
 *      Author: LUUVINHLOI
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>


typedef struct{
 void (*pTask)(void);
 uint32_t  Delay;
 uint32_t  Period;
 uint8_t  RunMe;

 uint32_t  TaskID;
}sTasks;

#define SCH_MAX_TASKS 4

void SCH_Init(void);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

unsigned char SCH_Add_Task(void(*pFunction)(), unsigned int DELAY, unsigned int PERIOD);

unsigned char SCH_Delete_Task(uint32_t TASK_INDEX);

void SCH_Sleep(void);

#endif /* INC_SCHEDULER_H_ */
