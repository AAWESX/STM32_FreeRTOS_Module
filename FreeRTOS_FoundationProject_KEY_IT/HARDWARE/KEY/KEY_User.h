#ifndef __KEY_User_H_
#define __KEY_User_H_

#include "main.h"

#ifdef INC_FREERTOS_H
	#define delay_ms osDelay
#endif
#ifndef INC_FREERTOS_H
	#define delay_ms HAL_Delay
#endif

#define KEY_1  HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)
#define KEY_2  HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4)

typedef enum 
{
	KEY_UNPRESS = 0,
	KEY_PRESS_1,
	KEY_PRESS_2,
	KEY_PRESS_3,
	KEY_PRESS_4,
	KEY_PRESS_5,
	KEY_PRESS_6,
	KEY_PRESS_7,
	KEY_PRESS_8
}KEY_PRESS_DATA;

uint8_t Key_scanf(uint8_t mode);



#endif



