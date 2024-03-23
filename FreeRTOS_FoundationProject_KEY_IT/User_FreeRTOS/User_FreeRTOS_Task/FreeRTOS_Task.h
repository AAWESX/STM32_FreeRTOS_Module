#ifndef __FREERTOS_TESK_H_
#define __FREERTOS_TESK_H_

#include "main.h"

/*任务优先级 枚举*/
const typedef enum
{
	TASK_PRECEDENCE_PRIO_1 = 1,
	TASK_PRECEDENCE_PRIO_2,
	TASK_PRECEDENCE_PRIO_3,
	TASK_PRECEDENCE_PRIO_4,
	TASK_PRECEDENCE_PRIO_5,
	TASK_PRECEDENCE_PRIO_6,
	TASK_PRECEDENCE_PRIO_7,
	TASK_PRECEDENCE_PRIO_8,
	TASK_PRECEDENCE_PRIO_9,
	TASK_PRECEDENCE_PRIO_10,
	TASK_PRECEDENCE_PRIO_11,
	TASK_PRECEDENCE_PRIO_12,
	TASK_PRECEDENCE_PRIO_13,
	TASK_PRECEDENCE_PRIO_14,
	TASK_PRECEDENCE_PRIO_15
}TASK_PRECEDENCE_PRIO;

const typedef enum
{
	TASK_STACK_16_SIZE  = 16,
	TASK_STACK_32_SIZE  = 32,
	TASK_STACK_64_SIZE  = 64,
	TASK_STACK_128_SIZE = 128,
	TASK_STACK_256_SIZE = 256,
	TASK_STACK_512_SIZE = 512,
}FreeRTOS_Demo_Stack_Size;


void FreeRTOS_Dynamic_Demo(void * pvDynamics);
void FreeRTOS_Static_Demo(void * pvDynamics);

#endif 

