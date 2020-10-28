#include "config.h"

static int g_dev_beep_active = false;

int dev_beep_open(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = BEEP_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(BEEP_PORT, &GPIO_InitStruct);

	g_dev_beep_active = true;

	return DEV_OK;
}
int dev_beep_on(void)
{

	if (g_dev_beep_active == false)
	{
		return DEV_ERROR;
	}

	GPIO_SetBits(BEEP_PORT, BEEP_PIN);
	return DEV_OK;
}
int dev_beep_close(void)
{
	g_dev_beep_active = false;
	return DEV_OK;


}
int dev_beep_off(void)
{
	if (g_dev_beep_active == false)
	{
		return DEV_ERROR;
	}

	GPIO_ResetBits(BEEP_PORT, BEEP_PIN);
	return DEV_OK;

}


