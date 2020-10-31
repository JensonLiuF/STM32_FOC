#include "config.h"
#include "main.h"
#include "log.h"

/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
 /* 创建任务句柄 */
static TaskHandle_t AppTask_Handle = NULL;
static void AppTaskCreate(void);/* AppTask任务 */

static void AppTask(void* parameter)
{	
    while (1)
    {
        dev_led_on();
        vTaskDelay(500);   /* 延时500个tick */
				PRINTFLOG("running~~~~~~~~~~\r\n");
        dev_led_off();     
        vTaskDelay(500);   /* 延时500个tick */	
				PRINTFLOG("running~~~~~~~~~~\r\n");	 		
    }
}

int main(void)
{	
  BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */

  SysInit();

   /* 创建AppTaskCreate任务 */
  xReturn = xTaskCreate((TaskFunction_t )AppTask,  /* 任务入口函数 */
                        (const char*    )"AppTask",/* 任务名字 */
                        (uint16_t       )512,  /* 任务栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )1, /* 任务的优先级 */
                        (TaskHandle_t*  )&AppTask_Handle);/* 任务控制块指针 */ 
  /* 启动任务调度 */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* 启动任务，开启调度 */
  else
    return -1;  
  
  while(1);   /* 正常不会执行到这里 */    
}

