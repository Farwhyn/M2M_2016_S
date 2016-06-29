#include <stdio.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;

int Reading = 0;

void initialize(){

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
GPIO_InitStruct.GPIO_Pin= GPIO_Pin_13 | GPIO_Pin_14;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOD, &GPIO_InitStruct);

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
GPIO_InitStruct.GPIO_Pin= GPIO_Pin_0;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
GPIO_Init(GPIOA, &GPIO_InitStruct);

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_1;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
//	GPIO_Init(GPIOC, &GPIO_InitStruct);



RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);

//Analog Pin Config
GPIO_InitStruct.GPIO_Pin= GPIO_Pin_0;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOC, &GPIO_InitStruct);

ADC_DeInit();

ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
ADC_InitStruct.ADC_ScanConvMode = DISABLE;
ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
ADC_InitStruct.ADC_NbrOfConversion = 1;
ADC_Init(ADC1, &ADC_InitStruct);

ADC_Cmd(ADC1, ENABLE);

ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_144Cycles);

}

int adc_convert(){
	ADC_SoftwareStartConv(ADC1);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){

	}
		return ADC_GetConversionValue(ADC1);
}
int main(void)
{
	SysTick_Init();

	initialize();

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
