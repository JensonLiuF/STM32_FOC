
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

//针对不同的编译器调用不同的stdint.h文件
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

//断言
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)
	


#define configUSE_PREEMPTION		1	// 抢占式调度器
#define configUSE_TIME_SLICING	1	//1使能时间片调度(默认式使能的)
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	        1	// 硬件计算前导指令设置为1

// FreeRTOS基础配置
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			0
#define configUSE_MALLOC_FAILED_HOOK			0 		// 内存申请失败钩子函数
#define configCHECK_FOR_STACK_OVERFLOW			0   // 栈溢出检测方法
#define configCPU_CLOCK_HZ			SystemCoreClock //( ( unsigned long ) 72000000 )	// CPU内核时钟频率
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )	// RTOS系统节拍中断频率
#define configMAX_PRIORITIES		( 32 )									// 可用最大优先级
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 128 )	// 空闲任务使用的堆栈大小
#define configMAX_TASK_NAME_LEN		( 16 )
#define configUSE_16_BIT_TICKS		0				// 系统节拍计数器变量类型，1 16bit 0 32bit
#define configIDLE_SHOULD_YIELD		1				// 空闲任务放弃CPU使用权给其他同优先级任务

#define configUSE_QUEUE_SETS			1				//	启用队列
#define configUSE_TASK_NOTIFICATIONS    1 // 开启任务通知功能
#define configUSE_MUTEXES					1				// 使用互斥信号量
#define configUSE_RECURSIVE_MUTEXES			1	// 使用递归互斥信号量
#define configUSE_COUNTING_SEMAPHORES		1	//	使用计数信号量
#define configQUEUE_REGISTRY_SIZE				25 // 可以注册信号量和消息队列个数
#define configUSE_APPLICATION_TASK_TAG		  0 

// FreeRTOS内存申请有关配置
#define configSUPPORT_DYNAMIC_ALLOCATION 	1	// 动态内存申请
#define configSUPPORT_STATIC_ALLOCATION		0	//静态内存
#define configTOTAL_HEAP_SIZE					((size_t)(36*1024))  // 系统所有总的堆大小

// 运行时间和任务状态收集配置
#define configGENERATE_RUN_TIME_STATS	  0 //	运行时间统计功能
#define configUSE_TRACE_FACILITY	0				//	可视化跟踪调试
#define configUSE_STATS_FORMATTING_FUNCTIONS	1 

// 协程相关配置
/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

// 与软件定时器相关的配置
#define configUSE_TIMERS	1 	// 启用软件定时器
#define configTIMER_TASK_PRIORITY		 (2) // 软件定时器优先级
#define configTIMER_QUEUE_LENGTH		 10 	// 软件定时器队列长度
#define configTIMER_TASK_STACK_DEPTH	      (configMINIMAL_STACK_SIZE*2)	// 软件定时器堆栈大小




#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

// 中断有关配置
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4                  
#endif
//中断最低优先级
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15     

//系统可管理的最高中断优先级
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5 

#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )	/* 240 */

#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

// 中断服务函数相关配置
#define xPortPendSVHandler 	PendSV_Handler
#define vPortSVCHandler 	SVC_Handler


/* 以下为使用Percepio Tracealyzer需要的东西，不需要时将 configUSE_TRACE_FACILITY 定义为 0 */
#if ( configUSE_TRACE_FACILITY == 1 )
#include "trcRecorder.h"
#define INCLUDE_xTaskGetCurrentTaskHandle               1   // 启用一个可选函数（该函数被 Trace源码使用，默认该值为0 表示不用）
#endif
#endif /* FREERTOS_CONFIG_H */

