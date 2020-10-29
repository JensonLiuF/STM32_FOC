#include "config.h"
#include "main.h"

int main(void)
{
	SysInit();
	while(1)
	{
		dev_beep_on();
		dev_led_on();
		SysTickDelayMs(1000);
		dev_beep_off();
		dev_led_off();
		SysTickDelayMs(1000);
	}

}
