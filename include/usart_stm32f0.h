#ifndef _USART_STM32F0_H
#define _USART_STM32F0_H

	void UART2_init(int baudrate);
	void UART2_sendChar(char c);
	char UART2_getChar(void);

#endif// _USART_STM32F0_H
