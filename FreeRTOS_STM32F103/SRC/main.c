#include "config.h"
#include "main.h"
#include "hal_uart.h"

int main(void)
{
	uint8_t data = 0x12;

	SysInit();
	hal_uart_init(HAL_UART_1, 15200);
	while(1)
	{
		UsartSendString(USART1,"CTask is Running.\n--------------------------------\n");
		dev_beep_on();
		dev_led_on();
		SysTickDelayMs(1000);
		dev_beep_off();
		dev_led_off();
		SysTickDelayMs(1000);
	}

}
