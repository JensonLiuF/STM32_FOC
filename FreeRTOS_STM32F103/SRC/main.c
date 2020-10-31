#include "config.h"
#include "main.h"
#include "log.h"

/* FreeRTOSͷ�ļ� */
#include "FreeRTOS.h"
#include "task.h"
 /* ���������� */
static TaskHandle_t AppTask_Handle = NULL;
static void AppTaskCreate(void);/* AppTask���� */

static void AppTask(void* parameter)
{	
    while (1)
    {
        dev_led_on();
        vTaskDelay(500);   /* ��ʱ500��tick */
				PRINTFLOG("running~~~~~~~~~~\r\n");
        dev_led_off();     
        vTaskDelay(500);   /* ��ʱ500��tick */	
				PRINTFLOG("running~~~~~~~~~~\r\n");	 		
    }
}

int main(void)
{	
  BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */

  SysInit();

   /* ����AppTaskCreate���� */
  xReturn = xTaskCreate((TaskFunction_t )AppTask,  /* ������ں��� */
                        (const char*    )"AppTask",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* ��������ȼ� */
                        (TaskHandle_t*  )&AppTask_Handle);/* ������ƿ�ָ�� */ 
  /* ����������� */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* �������񣬿������� */
  else
    return -1;  
  
  while(1);   /* ��������ִ�е����� */    
}

