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
	usart2_dma_sync_puts("Hello, World\n");
	while(1){
		usart2_sync_gets(inputBuffer);
		serial_printf(usart2_dma_sync_puts,">>%s\n",inputBuffer);
		dma_usart2_waitUntilComplete();
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
