#include "dev_led.h"
#include "config.h"

static int g_dev_led_active = false;

int dev_led_open(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = LED_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(LED_PORT, &GPIO_InitStruct);

	g_dev_led_active = true;

	return DEV_OK;
}
int dev_led_on(void)
{
	if (g_dev_led_active == false)
	{
		return DEV_ERROR;
	}

	GPIO_SetBits(LED_PORT, LED_PIN);
	return DEV_OK;

}
int dev_led_close(void)
{
	g_dev_led_active = false;
	return DEV_OK;
}
int dev_led_off(void)
{
	if (g_dev_led_active == false)
	{
		return DEV_ERROR;
	}

	GPIO_ResetBits(LED_PORT, LED_PIN);
	return DEV_OK;
}


