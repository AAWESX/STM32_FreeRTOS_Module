#include "KEY\KEY_User.h"

uint8_t Key_scanf(uint8_t mode)           
{
  static uint8_t KLL = 1;
	
	if(mode == 1)
		KLL = 1;
	if( KLL == 1 &&(KEY_1 == 0 ||KEY_2 == 0 /*||KEY_3 == 0||KEY_4 == 0*/))
	{
		osDelay(5);
		KLL = 0;
		if(KEY_1 == 0)
			return KEY_PRESS_1;
		else if(KEY_2 == 0)
			return KEY_PRESS_2;
//		else if(KEY_3 == 0)
//			return KEY_PRESS_3;
//		else if(KEY_4 == 0)
//			return KEY_PRESS_4;
	}
	
	else if(KEY_1 == 1 && KEY_2 == 1 /*&& KEY_3 == 1 && KEY_4 == 1*/)
	{
		KLL = 1;
	}
	return KEY_UNPRESS;
}




