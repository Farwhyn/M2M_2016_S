/**************************************************************************//*****
 * @file     PeripheralSetup.c
 * @brief    Implementation of pin initialization functions to setup each
 * 			 individual peripheral devices.
 ********************************************************************************/
#include <stdio.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"

//void TapInit(void){
//	GPIO_InitTypeDef GPIO_InitStruct;
//	ADC_InitTypeDef ADC_InitStruct;
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);
//
//	//Analog Pin Config
//	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_0;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOC, &GPIO_InitStruct);
//
//	ADC_DeInit();
//
//	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
//	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
//	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
//	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
//	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
//	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
//	ADC_InitStruct.ADC_NbrOfConversion = 1;
//	ADC_Init(ADC1, &ADC_InitStruct);
//
//	ADC_Cmd(ADC1, ENABLE);
//
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_15Cycles);
//}
//
//
//void SqueezeInit(void){
//	GPIO_InitTypeDef GPIO_InitStruct;
//	ADC_InitTypeDef ADC_InitStruct;
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);
//
//	//Analog Pin Config
//	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_1;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOC, &GPIO_InitStruct);
//
//	ADC_DeInit();
//
//	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
//	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
//	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
//	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
//	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC2;
//	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
//	ADC_InitStruct.ADC_NbrOfConversion = 1;
//	ADC_Init(ADC2, &ADC_InitStruct);
//
//	ADC_Cmd(ADC2, ENABLE);
//
//	ADC_RegularChannelConfig(ADC2,ADC_Channel_11,1,ADC_SampleTime_15Cycles);
//}
//
//
//void SpinInit(void){
//	GPIO_InitTypeDef GPIO_InitStruct;
//	ADC_InitTypeDef ADC_InitStruct;
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);
//
//	//Analog Pin Config
//	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_2;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOC, &GPIO_InitStruct);
//
//	ADC_DeInit();
//
//	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
//	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
//	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
//	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
//	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
//	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
//	ADC_InitStruct.ADC_NbrOfConversion = 1;
//	ADC_Init(ADC3, &ADC_InitStruct);
//
//	ADC_Cmd(ADC3, ENABLE);
//
//	ADC_RegularChannelConfig(ADC3,ADC_Channel_12,1,ADC_SampleTime_15Cycles);
//}

volatile uint16_t ADCConvertedValues[2];

void PeripheralsInit(void){ //2 Peripheral devices for now

	  GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	  /* Configure ADC1 Channel3 & 5 pins as analog input ******************************/
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);


	//****************************************************************************
	  ADC_InitTypeDef       ADC_InitStructure;
	  ADC_CommonInitTypeDef ADC_CommonInitStructure;
	  DMA_InitTypeDef       DMA_InitStructure;

	  /* Enable peripheral clocks *************************************************/
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	  /* DMA2_Stream0 channel0 configuration **************************************/
	  DMA_DeInit(DMA2_Stream0);
	  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADCConvertedValues[0];
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	  DMA_InitStructure.DMA_BufferSize = 2;
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	  /* DMA2_Stream0 enable */
	  DMA_Cmd(DMA2_Stream0, ENABLE);

	  /* ADC Common Init **********************************************************/
	  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	  ADC_CommonInit(&ADC_CommonInitStructure);

	  /* ADC1 Init ****************************************************************/
	  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfConversion = 2;
	  ADC_Init(ADC1, &ADC_InitStructure);

	  /* ADC1 regular channel configuration ******************************/
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_480Cycles); // PA3
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_480Cycles); // PA5

	   /* Enable DMA request after last transfer (Single-ADC mode) */
	  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

	  /* Enable ADC1 DMA */
	  ADC_DMACmd(ADC1, ENABLE);

	    /* Enable ADC1 **************************************************************/
	  ADC_Cmd(ADC1, ENABLE);

	    /* Start ADC1 Software Conversion */
	  ADC_SoftwareStartConv(ADC1);
}

void BoardLEDInit (void){
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
			| GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void PushButtonInit(void) {
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int SensorRead(int sensor){

	if (sensor == 1){
		ADC_SoftwareStartConv(ADC1);
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){

		}
			return ADC_GetConversionValue(ADC1);
				}
	else if (sensor == 2){
		ADC_SoftwareStartConv(ADC2);
		while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC)){

		}
			return ADC_GetConversionValue(ADC2);
		}

	else if (sensor == 3){
		ADC_SoftwareStartConv(ADC3);
		while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC)){

		}
			return ADC_GetConversionValue(ADC3);
		}

	else
		return 1;


}

void TapLedInit(void) {
	GPIO_InitTypeDef GPIO_InitStruct;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		GPIO_InitStruct.GPIO_Pin= GPIO_Pin_2;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_InitStruct);

}
