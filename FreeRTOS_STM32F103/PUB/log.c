 
#include <stdio.h>
#include "dev_def.h"
#include "hal_uart.h"

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
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	if (ch == '\n')
    {
		hal_uart_sendbyte(LOG_UART, '\r');
	}
	return (hal_uart_sendbyte(LOG_UART, (uint8_t)ch));
}

