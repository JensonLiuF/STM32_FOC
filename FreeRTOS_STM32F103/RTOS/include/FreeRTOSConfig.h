
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

//��Բ�ͬ�ı��������ò�ͬ��stdint.h�ļ�
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
    extern uint32_t SystemCoreClock;
#endif

//����
#define vAssertCalled(char,int) printf("Error:%s,%d\r\n",char,int)
#define configASSERT(x) if((x)==0) vAssertCalled(__FILE__,__LINE__)
	


#define configUSE_PREEMPTION		1	// ��ռʽ������
#define configUSE_TIME_SLICING	1	//1ʹ��ʱ��Ƭ����(Ĭ��ʽʹ�ܵ�)
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	        1	// Ӳ������ǰ��ָ������Ϊ1

// FreeRTOS��������
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			0
#define configUSE_MALLOC_FAILED_HOOK			0 		// �ڴ�����ʧ�ܹ��Ӻ���
#define configCHECK_FOR_STACK_OVERFLOW			0   // ջ�����ⷽ��
#define configCPU_CLOCK_HZ			SystemCoreClock //( ( unsigned long ) 72000000 )	// CPU�ں�ʱ��Ƶ��
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )	// RTOSϵͳ�����ж�Ƶ��
#define configMAX_PRIORITIES		( 32 )									// ����������ȼ�
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 128 )	// ��������ʹ�õĶ�ջ��С
#define configMAX_TASK_NAME_LEN		( 16 )
#define configUSE_16_BIT_TICKS		0				// ϵͳ���ļ������������ͣ�1 16bit 0 32bit
#define configIDLE_SHOULD_YIELD		1				// �����������CPUʹ��Ȩ������ͬ���ȼ�����

#define configUSE_QUEUE_SETS			1				//	���ö���
#define configUSE_TASK_NOTIFICATIONS    1 // ��������֪ͨ����
#define configUSE_MUTEXES					1				// ʹ�û����ź���
#define configUSE_RECURSIVE_MUTEXES			1	// ʹ�õݹ黥���ź���
#define configUSE_COUNTING_SEMAPHORES		1	//	ʹ�ü����ź���
#define configQUEUE_REGISTRY_SIZE				25 // ����ע���ź�������Ϣ���и���
#define configUSE_APPLICATION_TASK_TAG		  0 

// FreeRTOS�ڴ������й�����
#define configSUPPORT_DYNAMIC_ALLOCATION 	1	// ��̬�ڴ�����
#define configSUPPORT_STATIC_ALLOCATION		0	//��̬�ڴ�
#define configTOTAL_HEAP_SIZE					((size_t)(36*1024))  // ϵͳ�����ܵĶѴ�С

// ����ʱ�������״̬�ռ�����
#define configGENERATE_RUN_TIME_STATS	  0 //	����ʱ��ͳ�ƹ���
#define configUSE_TRACE_FACILITY	0				//	���ӻ����ٵ���
#define configUSE_STATS_FORMATTING_FUNCTIONS	1 

// Э���������
/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

// �������ʱ����ص�����
#define configUSE_TIMERS	1 	// ���������ʱ��
#define configTIMER_TASK_PRIORITY		 (2) // �����ʱ�����ȼ�
#define configTIMER_QUEUE_LENGTH		 10 	// �����ʱ�����г���
#define configTIMER_TASK_STACK_DEPTH	      (configMINIMAL_STACK_SIZE*2)	// �����ʱ����ջ��С




#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

// �ж��й�����
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       		__NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       		4                  
#endif
//�ж�������ȼ�
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			15     

//ϵͳ�ɹ��������ж����ȼ�
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	5 

#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )	/* 240 */

#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

// �жϷ������������
#define xPortPendSVHandler 	PendSV_Handler
#define vPortSVCHandler 	SVC_Handler


/* ����Ϊʹ��Percepio Tracealyzer��Ҫ�Ķ���������Ҫʱ�� configUSE_TRACE_FACILITY ����Ϊ 0 */
#if ( configUSE_TRACE_FACILITY == 1 )
#include "trcRecorder.h"
#define INCLUDE_xTaskGetCurrentTaskHandle               1   // ����һ����ѡ�������ú����� TraceԴ��ʹ�ã�Ĭ�ϸ�ֵΪ0 ��ʾ���ã�
#endif
#endif /* FREERTOS_CONFIG_H */

