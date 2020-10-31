#ifndef __HAL_UART_H__
#define __HAL_UART_H__

#include "config.h"

typedef enum
{
	HAL_UART_1 = 0,
	HAL_UART_2,
	HAL_UART_3,
	HAL_UART_4,
	HAL_UART_5,
	HAL_UART_MAX,
}HAL_UART_TYPE;

static void receive_char(char ch);
static int read_buf(char* buf, int len);
void hal_uart_init(int uart_id, uint32_t baud);
int hal_uart_sendbyte(int uart_id, uint8_t tx_data);
int hal_uart_sendbuf(int uart_id, uint8_t *buf, uint16_t len);
int hal_uart_recvbyte(int uart_id, uint8_t *rx_data);
uint32_t get_uart_baudrate(int uart_id);
#endif
