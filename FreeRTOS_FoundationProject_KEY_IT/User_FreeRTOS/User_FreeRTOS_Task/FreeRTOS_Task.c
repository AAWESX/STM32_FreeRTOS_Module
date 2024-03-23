#include "User_FreeRTOS_Task\FreeRTOS_Task.h"
#include "usart.h"
void LED_test1(void * pvDynamics);
void LED_test2(void * pvDynamics);
void KEY_test3(void * pvDynamics);
void LCD_tesk4(void * pvDynamics);

/* TASK1 任务配置
 * 包括：任务句柄 堆栈大小 创建任务
 */
	TaskHandle_t      xTaskHandle_Static_LED_1;
	StackType_t       g_pucStackOfLedTask_Static_1[TASK_STACK_128_SIZE];
	StaticTask_t      g_Task_TCP_Static_LED_1;




/* TASK2 任务配置
 * 包括：任务句柄 任务优先级 堆栈大小 创建任务
 */
TaskHandle_t      xTaskHandle_Static_LED_2;
StackType_t       g_pucStackOfLedTask_Static_2[TASK_STACK_128_SIZE];
StaticTask_t      g_Task_TCP_Static_LED_2;

void FreeRTOS_Static_Demo(void * pvDynamics)
{
	taskENTER_CRITICAL();    /*进入临界区*/
	
  	xTaskHandle_Static_LED_1 = xTaskCreateStatic(	(TaskFunction_t)LED_test1,
																(char *         )"LEDtask1",
																(uint16_t       )TASK_STACK_128_SIZE,
																(void *         )NULL,
																(UBaseType_t    )TASK_PRECEDENCE_PRIO_2,
																(StackType_t *  )g_pucStackOfLedTask_Static_1,
																(StaticTask_t * )&g_Task_TCP_Static_LED_1);
																
	xTaskHandle_Static_LED_2 = xTaskCreateStatic((TaskFunction_t)LED_test2,
												(char *         )"LEDtask2",
												(uint16_t       )TASK_STACK_128_SIZE,
												(void *         )NULL,
												(UBaseType_t    )TASK_PRECEDENCE_PRIO_3,
												(StackType_t *  )g_pucStackOfLedTask_Static_2,
												(StaticTask_t * )&g_Task_TCP_Static_LED_2 );

//  vTaskDelete(xTaskHandle_LED1);
	
  vTaskDelay(NULL);   /*退出临界*/
}

/* TASK1 任务配置
 * 包括：任务句柄 任务优先级 堆栈大小 创建任务
 */
BaseType_t        xTaskBase_Dynamic_LED_1;
TaskHandle_t      xTaskHandle_Dynamic_LED_1;

/* TASK2 任务配置
 * 包括：任务句柄 任务优先级 堆栈大小 创建任务
 */

BaseType_t        xTaskBase_Dynamic_LED_2;
TaskHandle_t      xTaskHandle_Dynamic_LED_2;

/* TASK2 任务配置
 * 包括：任务句柄 任务优先级 堆栈大小 创建任务
 */

BaseType_t        xTaskBase_Dynamic_KEY_3;
TaskHandle_t      xTaskHandle_Dynamic_KEY_3;

/* TASK4 LCD 任务配置
 * 包括：任务句柄 任务优先级 堆栈大小 创建任务
 */

BaseType_t        xTaskBase_Dynamic_LCD_4;
TaskHandle_t      xTaskHandle_Dynamic_LCD_4;

void FreeRTOS_Dynamic_Demo(void * pvDynamics)
{
	
	taskENTER_CRITICAL();    /*进入临界区*/
	
	
		xTaskBase_Dynamic_LED_1 = xTaskCreate((TaskFunction_t )LED_test1,
												(char *         )"LEDtask1",
												(uint16_t       )TASK_STACK_16_SIZE,
												(void *         )NULL,
												(UBaseType_t    )TASK_PRECEDENCE_PRIO_1,
												(TaskHandle_t * )&xTaskHandle_Dynamic_LED_1);
	
												
    xTaskBase_Dynamic_LED_2 = xTaskCreate((TaskFunction_t )LED_test2,
												(char *         )"LEDtask2",
												(uint16_t       )TASK_STACK_16_SIZE,
												(void *         )NULL,
												(UBaseType_t    )TASK_PRECEDENCE_PRIO_2,
												(TaskHandle_t * )&xTaskHandle_Dynamic_LED_2);
		
    xTaskBase_Dynamic_KEY_3 = xTaskCreate((TaskFunction_t )KEY_test3,
												(char *         )"KEYtask3",
												(uint16_t       )TASK_STACK_64_SIZE,
												(void *         )NULL,
												(UBaseType_t    )TASK_PRECEDENCE_PRIO_3,
												(TaskHandle_t * )&xTaskHandle_Dynamic_KEY_3);												
		xTaskBase_Dynamic_LCD_4 = xTaskCreate((TaskFunction_t )LCD_tesk4,
												(char *         )"LCDtask4",
												(uint16_t       )TASK_STACK_128_SIZE,
												(void *         )NULL,
												(UBaseType_t    )TASK_PRECEDENCE_PRIO_4,
												(TaskHandle_t * )&xTaskHandle_Dynamic_LCD_4);							
			
 vTaskDelay(NULL);   /*退出临界*/
}

/*系统运行指示灯任务*/
void LED_test1(void * pvDynamics)
{


	while (1)
	{
		printf("Task\r\n");
		//HAL_UART_Transmit_IT(&huart1,"Task\r\n",sizeof("Task\r\n"));
		LED_Control(GPIOB,Pin_5,Pin_LOW);
		osDelay(100);
		LED_Control(GPIOB,Pin_5,Pin_HIGH);
		osDelay(100);
	}
}

/*系统指示灯任务*/
void LED_test2(void * pvDynamics)
{
	//printf("LED_Task1 Run!!!");
	while (1)
	{
		osDelay(10);
		LED_Control(GPIOE,Pin_5,Pin_LOW);
		osDelay(1000);
		LED_Control(GPIOE,Pin_5,Pin_HIGH);
		osDelay(1000);
	}
}

/*输入式按键任务*/
void KEY_test3(void * pvDynamics)
{
	
uint8_t KEY_Value = 0;
	
	while(1)
	{
		KEY_Value = Key_scanf(1);
		
		if(KEY_Value == 1)
		{
			LCD_printf(30,150,16,"LED2 Task Suspend!");
			vTaskSuspend(xTaskHandle_Dynamic_LED_2);
		}
		else if(KEY_Value == 2)
		{
			LCD_printf(30,150,16,"LED2 Task Resume!");
			vTaskResume(xTaskHandle_Dynamic_LED_2);
		}
		osDelay(10);
	}
}

void LCD_tesk4(void* pvDynamics)
{	
	int sum = 0;
	LCD_Init();							//初始化LCD
//	LCD_Clear(BLACK);
	POINT_COLOR = BLACK;

	LCD_printf(30,10 ,16,"ATK STM32F103/F407");
	LCD_printf(30,30 ,16,"FreeRTOS Examp 6-1");
	LCD_printf(30,50 ,16,"Task Creat and Del");
	LCD_printf(30,70 ,16,"ATOM@ALIENTEK");
	LCD_printf(30,90 ,16,"2016/11/25");
	LCD_printf(30,110,16,"LCD_Printf read!!!!");
	LCD_printf(30,130,16,"LCD_Printf sum:");
	while(1)
	{
		LCD_printf(152,130,16,"%d",sum++);
		osDelay(100);
	}
		
}


