#ifndef __DEV_SYSTICK_H__
#define __DEV_SYSTICK_H__

#include "config.h"
#include "stm32f10x.h"

#define MAX_TIMER 5	// create MAX_TIMER software timer with system tick timer 
extern uint32 sysTimer[MAX_TIMER];

#define DelayTimer sysTimer[0]	// delay timer
#define ATaskTimer sysTimer[1]	// A Task timer
#define BTaskTimer sysTimer[2]	// B Task timer

void SysTickInit(void);	// System tick timer initialize
void SysTickDelayMs(uint32 nms); // delay n ms
uint32 GetRunTime(void);	// get system run time

#endif
