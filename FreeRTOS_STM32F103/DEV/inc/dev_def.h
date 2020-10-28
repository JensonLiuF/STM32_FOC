#ifndef __DEV_DEF_H__
#define __DEV_DEF_H__

#ifndef NULL
#define NULL 0
#endif

#ifndef DEV_ERROR
#define DEV_ERROR (-1)
#endif

#ifndef DEV_OK
#define DEV_OK (0)
#endif

#define LED_PORT GPIOA
#define LED_PIN  GPIO_Pin_0|GPIO_Pin_1

#define BEEP_PORT GPIOA
#define BEEP_PIN  GPIO_Pin_2

#define USART1_PORT GPIOA
#define USART1_TX_PIN	GPIO_Pin_9
#define USART1_RX_PIN GPIO_Pin_10

#define USART2_PORT GPIOA
#define USART2_TX_PIN	GPIO_Pin_2
#define USART2_RX_PIN GPIO_Pin_3

#define USART3_PORT GPIOB
#define USART3_TX_PIN	GPIO_Pin_10
#define USART3_RX_PIN GPIO_Pin_11
#endif
