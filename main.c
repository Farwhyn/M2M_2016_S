#include <stdio.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "PeripheralSetup.h"


int main(void)
{
	SysTick_Init();

	double Reading;
	while (1){
		int state=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

		if (!state){
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14);
			delay_1ms(500);
		}
		else{
			GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14);
		}

		Reading=adc_convert();

		printf("%d\r\n", Reading);

	}
}

void SysTick_Handler(void) {
	TimeTick_Decrement();
}
