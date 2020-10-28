#include "dev_sysTick.h"
#include "config.h"

uint32 sysTimer[MAX_TIMER];
static uint32 g_iRunTime = 0;

void SysTickInit(void)
{
	uchar i = 0;
	for (i = 0; i < MAX_TIMER; ++i)
	{
		sysTimer[i] = 0;		
	}
	SysTick_Config(72000);
}

void SysTick_Handler(void)
{
	uint8 i;
	for (i = 0; i < MAX_TIMER; ++i)
	{
		if (sysTimer[i])
		{
			sysTimer[i]--;
		}
	}

	if(g_iRunTime++ == 0xffffffff)
	{
		g_iRunTime = 0;
	}
}

void SysTickDelayMs(uint32 nms)
{
	CUP_INT_ENABLE();
	DelayTimer = nms;
	while(DelayTimer);
}
uint32 GetRunTime(void)
{
	uint32 RunTime;
	
	CUP_INT_DISABLE();
	RunTime = g_iRunTime;
	CUP_INT_ENABLE();
	return RunTime;
}

