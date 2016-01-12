#include "stm32f0xx.h"                  // Device header
#include "dma_usart_stm32f0.h"
#include "serial_stdio.h"
#include "usart_stm32f0.h"

void	setToMaxSpeed(void);
int main(void)
{
	char inputBuffer[40]; 
	setToMaxSpeed();
	dma_and_usart2_init(9600);
	dma_usart2_puts("Hello, World\n");
	dma_usart2_waitUntilComplete();
	while(1){
		UART2_sync_gets(inputBuffer);
		serial_putc_to_printf(UART2_sendChar,">>%s\n",inputBuffer);
	}
}

void setToMaxSpeed(void){
		int internalClockCounter;
		RCC_PLLCmd(DISABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
		RCC_HSEConfig(RCC_HSE_OFF);
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_12);
		RCC_PREDIV1Config(RCC_PREDIV1_Div1);
		RCC_PLLCmd(ENABLE);
		while(!RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		for(internalClockCounter=0;internalClockCounter<1024;internalClockCounter++){
			if(RCC_GetSYSCLKSource()==RCC_SYSCLKSource_PLLCLK){
				SystemCoreClockUpdate();
				break;
			}
		}
}
