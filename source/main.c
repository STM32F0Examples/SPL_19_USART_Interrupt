#include "stm32f0xx.h"                  // Device header
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "dma_usart_stm32f0.h"
#include "serial_stdio.h"
#include "usart_stm32f0.h"
#include "os_serial_stdio.h"
#include "os_usart_stm32f0.h"

char inputBuffer[40];
void	setToMaxSpeed(void);
int main(void)
{
	//Set procesor speed
	setToMaxSpeed();
	//Initialize kernel
	osKernelInitialize();
	//Hardware initialize
	os_serial_init();
	os_usart2_init(9600);
	//Start Thread switching
	osKernelStart();
	//User Application
	os_usart2_puts("Hello, World\n");
	while(1){
		os_usart2_gets(inputBuffer);
		os_serial_printf(os_usart2_puts,">>%s\n",inputBuffer);
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
