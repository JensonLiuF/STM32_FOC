#include "config.h"

#define MAX_BUF_LEN	1024

static volatile int s_write = 0;
static volatile int s_read = 0;
static char s_uart1buf[MAX_BUF_LEN] = {0};

static USART_TypeDef* uarts[HAL_UART_MAX] = {USART1, USART2, USART3, UART4, UART5};
static int g_hal_uart_active[HAL_UART_MAX] = {0};
static uint32_t g_hal_uart_baud[HAL_UART_MAX] = {0};

static void _uart1_init(uint32_t baud);
static void _uart2_init(uint32_t baud);
static void _uart3_init(uint32_t baud);
static void _uart4_init(uint32_t baud);
static void _uart5_init(uint32_t baud);

//int fputc(int ch,FILE *f)
//{
//	
//	hal_uart_sendbyte(HAL_UART_1, (uint8)ch);
//	
//	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)== RESET);
//	
//	return (ch);

//}

// should be in Application layer
static void receive_char(char ch)
{
	if(((s_write + 1) % MAX_BUF_LEN) != s_read)
	{
		s_uart1buf[s_write++] = ch;
		s_write %= MAX_BUF_LEN;
	}
}

// should be in Application layer
static int read_buf(char* buf, int len)
{
	int ret = 0;
	int rest = 0;
	
	if(s_read < s_write)
	{
		ret = s_write - s_read;
		ret = (ret < len ) ? ret : len;
		memmove(buf, s_uart1buf + s_read, ret);
		s_read += ret;
	}
	else if(s_read > s_write)
	{
		ret = s_write + MAX_BUF_LEN - s_read;
		ret = (ret < len ) ? ret : len;
		if(s_read + ret > MAX_BUF_LEN)
		{
			rest = MAX_BUF_LEN - s_read;
			memmove(buf, s_uart1buf + s_read, rest);
			memmove(buf + rest, s_uart1buf, ret - rest);
			s_read += ret;
			s_read %= MAX_BUF_LEN;
		}
		else
		{
			memmove(buf, s_uart1buf + s_read, ret);
			s_read += ret;
		}
	}
	return ret;
}

// should be in Application layer
void USART1_IRQHandler(void)
{
	uint8_t data = 0;
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
	{
		data = (uint8_t)USART_ReceiveData(USART1);
		receive_char(data);
	}
}

uint32_t get_uart_baudrate(int uart_id)
{
	if(uart_id < 0 || uart_id >= HAL_UART_MAX)
	{
		return DEV_ERROR;
	}
	return g_hal_uart_baud[uart_id];
}
int hal_uart_sendbyte(int uart_id, uint8_t tx_data)
{
	int state = DEV_OK;
	
	if(g_hal_uart_active[uart_id] == false)
	{
		return DEV_ERROR;
	}
	
	if(uart_id < 0 || uart_id >= HAL_UART_MAX)
	{
		return DEV_ERROR;
	}
	
	while((uarts[uart_id]->SR&USART_FLAG_TXE)==0);  
	uarts[uart_id]->DR = (uint8_t) tx_data;    
	return state;
}

int hal_uart_sendbuf(int uart_id, uint8_t *buf, uint16_t len)
{
	int state = DEV_OK;
	int i;
	
	if(g_hal_uart_active[uart_id] == false)
	{
		return DEV_ERROR;
	}
	
	if(uart_id < 0 || uart_id >= HAL_UART_MAX)
	{
		return DEV_ERROR;
	}

	for(i = 0; i < len; i++)
	{
		while((uarts[uart_id]->SR&USART_FLAG_TXE)==0);  
		uarts[uart_id]->DR = (uint8_t) buf[i]; 
	}
	return state;
}	
	
int hal_uart_recvbyte(int uart_id, uint8_t *rx_data)
{
	int state = DEV_OK;

	if (g_hal_uart_active[uart_id] == false)
	{
		return DEV_ERROR;
	}

	return state;

}

void hal_uart_init(int uart_id, uint32_t baud)
{	
	if(uart_id < 0 || uart_id >= HAL_UART_MAX)
	{
		return;
	}
	if(g_hal_uart_active[uart_id] == true)
	{
		return;
	}
	switch(uart_id)
	{
		case HAL_UART_1:
			_uart1_init(baud);
			g_hal_uart_baud[HAL_UART_1] = baud;
			break;
		case HAL_UART_2:
			_uart2_init(baud);
			g_hal_uart_baud[HAL_UART_2] = baud;
			break;
		case HAL_UART_3:
			_uart3_init(baud);
			g_hal_uart_baud[HAL_UART_3] = baud;
			break;
		case HAL_UART_4:
			_uart4_init(baud);
			g_hal_uart_baud[HAL_UART_4] = baud;
			break;
		case HAL_UART_5:
			_uart5_init(baud);
			g_hal_uart_baud[HAL_UART_5] = baud;
			break;
		default:
			return;
	}
	g_hal_uart_active[uart_id] = true;
	return;
}

static void _uart1_init(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// Enable Gpio clock and enable uart clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// init Gpio 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = USART1_TX_PIN;				//TX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = USART1_RX_PIN;				//RX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART1_PORT, &GPIO_InitStruct);
	
	// USART setting config
	USART_InitStruct.USART_BaudRate = baud;  
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS;
	USART_Init(USART1, &USART_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;  
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;	
	NVIC_Init(&NVIC_InitStruct);	// init NVIC
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	//Enable USART1 interrupt
	USART_Cmd(USART1, ENABLE);		//  Enable Usart1
	
	USART_ClearFlag(USART1, USART_FLAG_TC);		// clear transmit flag
}

static void _uart2_init(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// Enable Gpio clock and enable uart clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// init Gpio 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = USART2_TX_PIN;				//TX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART2_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = USART2_RX_PIN;				//RX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART2_PORT, &GPIO_InitStruct);
	
	// USART setting config
	USART_InitStruct.USART_BaudRate = baud;  
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS;
	USART_Init(USART2, &USART_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;  
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;	
	NVIC_Init(&NVIC_InitStruct);	// init NVIC
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);	//Enable USART1 interrupt
	USART_Cmd(USART2, ENABLE);		//  Enable Usart1
	
	USART_ClearFlag(USART2, USART_FLAG_TC);		// clear transmit flag

}

static void _uart3_init(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// Enable Gpio clock and enable uart clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	// init Gpio 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = USART3_TX_PIN;				//TX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART3_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = USART3_RX_PIN;				//RX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART3_PORT, &GPIO_InitStruct);
	
	// USART setting config
	USART_InitStruct.USART_BaudRate = baud;  
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS;
	USART_Init(USART3, &USART_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;  
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;	
	NVIC_Init(&NVIC_InitStruct);	// init NVIC
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);	//Enable USART1 interrupt
	USART_Cmd(USART3, ENABLE);		//  Enable Usart1
	
	USART_ClearFlag(USART3, USART_FLAG_TC);		// clear transmit flag

}

static void _uart4_init(uint32_t baud)
{


}

static void _uart5_init(uint32_t baud)
{


}
