led port A	portA.0, portA.1

beep port A portA.2

´®¿Ú·ÂÕæ ÃüÁî
	MODE COM1 115200,0,8,1
	ASSIGN COM1 <S1IN>S1OUT
usart1 
		Tx	portA.9
		Rx	portA.10
		
usart2
		Tx	portA.2
		Rx	portA.3

usart3
		Tx	portB.10
		Rx	portB.11
		
uart4
		Tx	portC.10
		Rx	portC.11
		
uart5	
		Tx	portC.12
		Rx	portD.2
		
APB2	
	Gpio
	USART1
	
APB1
	USART2
	USART3
	UART4
	UART5
	