#include "LED\LED_User.h"

#include "cmsis_os.h"

void LED_Control(GPIO_TypeDef *GPIOx,LED_Pin_Switch LED_Pin, LED_GPIO_STAT  GpioStat)
{
	if(GpioStat == Pin_LOW)
	{
		GPIOx->BSRR = ((uint16_t)0x0001) << LED_Pin;
	}
	else
	{
		GPIOx->BSRR = ((uint16_t)0x0001) << (16 + LED_Pin);
	}
}

