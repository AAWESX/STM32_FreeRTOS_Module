#include "USART\XK_Usart.h"
#include "string.h"
#include <stdarg.h>		  //  ��׼ͷ�ļ�
#include <stdio.h>
#include "usart.h"


#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{  
//		HAL_UART_Transmit_IT(&huart1,(char *)ch,sizeof(ch));
	while((USART1->SR&0X40) == 0); //ѭ������,ֱ���������   
    USART1->DR = (uint8_t) ch;
	return ch;
}
#endif 


//   ��ʽ���ɱ�����ַ�������
char  formatBuf[256];
//   ��ʽ���ɱ�����ַ���
char *XK_Format(char *p,...)
{
    va_list ap;
		va_start(ap,p);
		vsprintf(formatBuf,p,ap);
		va_end(ap);
	  return formatBuf;
}


//   ��ʽ���ɱ�����ַ�������
#define   DEBUG_LOOP_LEN 10
char      debugBuf[DEBUG_LOOP_LEN][128];
uint16_t  loopCount   = 0 ;
uint16_t  loopTxCount = 0 ;
//   ��ʽ������ĵ��Ժ���
void XK_printf(char *p,...)   // �� printf  һ��һ���Ĺ��� 
{
	  /*  ��ʽ������  */
    va_list ap;
		va_start(ap,p);
		vsprintf(debugBuf[loopCount],p,ap);
		va_end(ap);
	  if(++loopCount == DEBUG_LOOP_LEN ) loopCount = 0;	
//  �������	
#ifdef DEBUG_EN    
	  if(huart1.gState == HAL_UART_STATE_READY) 
		{
		  XK_Debug_Loop_Transmit(); 
		}			
#endif	 
}

//   ѭ�����͵�����Ϣ
void XK_Debug_Loop_Transmit(void)
{
    if(loopTxCount != loopCount)
		{
		    HAL_UART_Transmit_IT(&huart1,(uint8_t *)debugBuf[loopTxCount],strlen(debugBuf[loopTxCount])); //  ��Ϣ����ӿ�
		    
			  if(++ loopTxCount == DEBUG_LOOP_LEN)
					loopTxCount = 0;
		}
}


//  �����ַ����ڵ���ָ�������ַ���
//  p_stepString : �������ַ���
//  index        : ��Ҫ���ҵ��ַ����±�,1~XXXX;
//  p_RxBuf      ; ������ҵ����ַ���
char XK_Find_Index_String(char *p_stepString , int index, char *p_RxBuf)
{
	   int n = 0      ;     //  ��¼�����ַ���
	   int strnum = 0 ;     //  ��¼�����ַ�����
	   p_RxBuf[0]  = 0;     //  ���
     while(n < STEP_STRING_MAX_LEN && *p_stepString != 0) 
		 {  
				if((*p_stepString  == STOP_CHAR) ||  n == 0)
				{
				   strnum ++;
					 if(strnum == index) //  �ҵ�ƥ���±�
						{
							 if(n > 0) p_stepString ++;
							 while(*p_stepString != 0 && *p_stepString != STOP_CHAR)
							 {
							   *p_RxBuf = *p_stepString;
								  p_stepString ++        ;
								  p_RxBuf ++;
							 }
							 *p_RxBuf = 0;
							 return XK_Status_True;
						}
				}
			  n ++           ;
				p_stepString ++;
		 }
	 *p_RxBuf = 0; 
	 return XK_Status_False;	 
}





