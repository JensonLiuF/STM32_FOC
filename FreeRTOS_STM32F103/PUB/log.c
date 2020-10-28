 
#include <stdio.h>
#include "dev_def.h"
#include "hal_uart.h"

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
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

