#include "system.h"

void CpuInit(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // selected the secend interrupt priority
}
void SysInit(void)
{
	CpuInit();	// config system information
	SysTickInit();
	hal_uart_init(HAL_UART_1, 115200);
	dev_led_open();
	dev_beep_open();
	
}
