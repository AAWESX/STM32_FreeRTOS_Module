/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention 
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* TASK1 任务配置
 * 包括：任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK1_PRIO       1
#define TASK1_STACK_SZIE 128
TaskHandle_t      xTaskHandle_LED1;
StackType_t       g_pucStackOfLedTask_1[TASK1_STACK_SZIE];
StaticTask_t      g_Task_TCP_LED1;


/* TASK2 任务配置
 * 包括：任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK2_PRIO       2
#define TASK2_STACK_SZIE 128
TaskHandle_t      xTaskHandle_LED2;
StackType_t       g_pucStackOfLedTask_2[TASK2_STACK_SZIE];
StaticTask_t      g_Task_TCP_LED2;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	BaseType_t ret;

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_T HREADS */
  	taskENTER_CRITICAL();    /*进入临界区*/
	
  xTaskHandle_LED1 = xTaskCreateStatic( (TaskFunction_t )LED_test1,
																			  (char *         )"LEDtask1",
																			  (uint16_t       )TASK1_STACK_SZIE,
																			  (void *         )NULL,
																	    	(UBaseType_t    )TASK1_PRIO,
																			  (StackType_t *  )g_pucStackOfLedTask_1,
                                        (StaticTask_t * )&g_Task_TCP_LED1);

  xTaskHandle_LED2 = xTaskCreateStatic( (TaskFunction_t )LED_test2,
																			  (char *         )"LEDtask2",
																			  (uint16_t       )TASK2_STACK_SZIE,
																			  (void *         )NULL,
																	    	(UBaseType_t    )TASK2_PRIO,
																			  (StackType_t *  )g_pucStackOfLedTask_2,
                                        (StaticTask_t * )&g_Task_TCP_LED2 );



	// ret = xTaskCreate(	(TaskFunction_t )LED_test1,
	// 										(char *         )"LEDtask1",
	// 										(uint16_t       )TASK1_STACK_SZIE,
  //                     (void *         )NULL,
	// 										(UBaseType_t    )TASK1_PRIO,
	// 										(TaskHandle_t * )&xTaskHandle_LED1);
	
  // ret = xTaskCreate( (TaskFunction_t )LED_test2,
	// 					   			  (char *         )"LEDtask1",
	// 								  	(uint16_t       )TASK2_STACK_SZIE,
	// 								    (void *         )NULL,
	// 							    	(UBaseType_t    )TASK2_PRIO,
	// 							    	(TaskHandle_t * )&xTaskHandle_LED2);

  // osDelay(10000);
  vTaskDelete(xTaskHandle_LED1);
	
  vTaskDelay(NULL);   /*退出临界*/

  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

