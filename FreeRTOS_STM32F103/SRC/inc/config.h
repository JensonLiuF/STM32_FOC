#ifndef __CONFIG_H__
#define __CONFIG_H__

#define uchar 	unsigned char
#define uint 		unsigned int

#define uint8 	unsigned char
#define uint16	unsigned short int
#define uint32	unsigned int

#ifdef MAIN_CONFIG
	#define EXT
#else
	#define EXT extern
#endif

// Global variable definenition


// Global variable definenition

// include common head file 
#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdbool.h"
#include "stdint.h"
	
// include common head file 



// include Peripheral drive head file 

#include "system.h"
#include "dev_sysTick.h"
#include "dev_led.h"
#include "dev_beep.h"
#include "hal_uart.h"
#include "dev_def.h"

// include Peripheral drive head file 

// Gloable macro definition
#define CUP_INT_DISABLE() {__set_PRIMASK(1);}	// disable interrupt
#define CUP_INT_ENABLE()		{__set_PRIMASK(0);}	// enable interrupt
// Gloable macro definition

// Gloable type definition
typedef enum
{
	FALSE = 0,
	TRUE = !FALSE
}BOOL;
// Gloable type definition

#endif

