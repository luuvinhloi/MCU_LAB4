/*
 * scheduler.c
 *
 *  Created on: Nov 30, 2022
 *      Author: LUUVINHLOI
 */
#include "Led_Blinky.h"
#include "main.h"
#include "scheduler.h"

typedef struct
{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;

	uint32_t TaskID;
} sTask;

#define SCH_MAX_TASKS 4

sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void)
{
	for (int i=0; i < SCH_MAX_TASKS; i++)
	{
		SCH_Delete_Task(i);
	}
}

void SCH_Update(void)
{
	for (int Index_Tasks = 0; Index_Tasks < SCH_MAX_TASKS; Index_Tasks++)
	{
		if (SCH_tasks_G[Index_Tasks].pTask)
		{
			if (SCH_tasks_G[Index_Tasks].Delay <= 0)
			{
				SCH_tasks_G[Index_Tasks].RunMe += 1;
				if (SCH_tasks_G[Index_Tasks].Period)
				{
					SCH_tasks_G[Index_Tasks].Delay = SCH_tasks_G[Index_Tasks].Period;
				}
			}
			else
			{
				SCH_tasks_G[Index_Tasks].Delay -= 1;
			}
		}
	}
}

unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD)
{
	unsigned char Index_Tasks = 0;

	while ((SCH_tasks_G[Index_Tasks].pTask != 0) && (Index_Tasks < SCH_MAX_TASKS))
	{
		Index_Tasks++;
	}
	if (Index_Tasks == SCH_MAX_TASKS)
	{
		return SCH_MAX_TASKS;
	}
	SCH_tasks_G[Index_Tasks].pTask = pFunction;
	SCH_tasks_G[Index_Tasks].Delay = DELAY;
	SCH_tasks_G[Index_Tasks].Period = PERIOD;
	SCH_tasks_G[Index_Tasks].RunMe = 0;

	return Index_Tasks;
}

void SCH_Dispatch_Tasks(void)
{
	unsigned char Index_Tasks;

	for (Index_Tasks = 0; Index_Tasks < SCH_MAX_TASKS; Index_Tasks++)
	{
		if (SCH_tasks_G[Index_Tasks].RunMe > 0)
		{
			(*SCH_tasks_G[Index_Tasks].pTask)();
			SCH_tasks_G[Index_Tasks].RunMe -= 1;
			if (SCH_tasks_G[Index_Tasks].Period == 0)
			{
				SCH_Delete_Task(Index_Tasks);
			}
		}
	}
	SCH_Sleep();
}

unsigned char SCH_Delete_Task(uint32_t current_index_task)
{
	unsigned char Return_Code = 0;

	SCH_tasks_G[current_index_task].pTask = 0x000;
	SCH_tasks_G[current_index_task].Delay = 0;
	SCH_tasks_G[current_index_task].Period = 0;
	SCH_tasks_G[current_index_task].RunMe = 0;

	return Return_Code;
}

void SCH_Sleep(void)
{
	HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	HAL_ResumeTick();
}
