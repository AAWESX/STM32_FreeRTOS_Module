#ifndef __DELAY_H
#define __DELAY_H 			   
#include "main.h"  
#include "stm32f1xx_hal_cortex.h"
	 
void XK_delay_init(void);
void XK_delay_ms(uint32_t nms);
void XK_delay_us(uint32_t nus);
void XK_delay_xms(uint32_t nms);

#endif



