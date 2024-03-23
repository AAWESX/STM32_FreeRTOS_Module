#ifndef _LED_UESR_H_
#define _LED_UESR_H_

#include "main.h"

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 


typedef enum
{
	Pin_LOW = 0U,
	Pin_HIGH
}LED_GPIO_STAT;

typedef enum
{
	Pin_0 = 0,
	Pin_1,
	Pin_2,
	Pin_3,
	Pin_4,
	Pin_5,
	Pin_6,
	Pin_7,
	Pin_8,
	Pin_9,
	Pin_10,
	Pin_11,
	Pin_12,
	Pin_13,
	Pin_14,
	Pin_15
}LED_Pin_Switch;

void LED_Control(GPIO_TypeDef *GPIOx,LED_Pin_Switch LED_Pin, LED_GPIO_STAT  GpioStat);


#endif


