/*****************************
��д���Ĵ��룬��������������Ӳ��



*****************************/

#ifndef __CORE_H__
#define __CORE_H__

#include "main.h"

#define DEBUG_EN 1


#define STOP_CHAR ','
#define STEP_STRING_MAX_LEN 1024

#define  XK_Status_True		    ( 0 )
#define  XK_Status_False	    ( 1 )




//   ��ʽ���ɱ�����ַ���
char *WS_Format(char *p,...);

//   �������
void XK_printf(char *p,...);
//   ѭ�����͵�����Ϣ
void XK_Debug_Loop_Transmit(void);


char WS_Find_Index_String(char *p_stepString , int index, char *p_RxBuf);



#endif



