#ifndef _USART_STM32F0_H
#define _USART_STM32F0_H

void UART2_init(int baudrate);
void UART2_sendChar(char c);

void UART2_async_gets(char* pString, void (*rx_complete_callback)(int));
int UART2_sync_gets(char* pString);

char UART2_getChar(void);

#endif// _USART_STM32F0_H
