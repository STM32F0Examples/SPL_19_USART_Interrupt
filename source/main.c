#include "stm32f0xx.h"                  // Device header
#include "retarget_STM32F0.h"
#include "serial_stdio.h"

void setToMaxSpeed(void);
Serial_t UART2_serial = {UART2_getChar, UART2_sendChar};

int main(void)
{
	setToMaxSpeed();
	UART2_init(9600);
	serial_printf(UART2_serial,"\nSystem ready\n");
	printf("$ ");
	while(1){

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
