#include <stdio.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "PeripheralSetup.h"
#include "delay.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

volatile uint16_t ADCConvertedValues[2];
volatile uint32_t buffer[18]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int const tap = 1;
int const squeeze = 2;
int const spin =3;

int main(void)
{
	//Initialize LED Strip
	ws2812_initTimer (buffer);
	ws2812_send ( 6 );

	printf("hi");
	//Initialize the delay timer
	SysTick_Init();

	PeripheralsInit();
	TapLedInit();
	BoardLEDInit();
//	SqueezeLEDInit(); //Connect LED to PA0
	PushButtonInit(); //Turns on the blue push button on the stm board
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	//Initialize values for each sensor reading
	int SqueezeReading=0;
	int TapReading=3000;
	int SpinReading=0;

	//Initialize state of the blue button to OFF
	int ButtonState=0;

	//Initialize Sensor Thresholds
	int SqueezeThreshold=0;
	int TapThreshold=0;
	int SpinThreshold=0;

	int LastButtonState = 0;
	int GameMode = 1;

	//Begin main loop
	while (1){
		for (int i = 0; i < 18; i++)
		{
//			buffer[i] = (int)(255.0*(float)i/17.0);
						buffer[i] = 1;
		}
//		printf("%d %d\r\n",buffer[0],buffer[1]);


		//Read the state of the blue button
		ButtonState=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		printf("%d\r\n", ButtonState);

		//Check if the button was pressed. If so, progress to the next game mode
		if (ButtonState != LastButtonState){
			if (ButtonState==1){
				GameMode++;
				if (GameMode>3)
					GameMode=1;
			}
		}
		LastButtonState=ButtonState;

		//If GameMode=1, initialize the Free Play mode
		if (GameMode == 1){
			//Turn on the 1 LED to indicate it's in Free Play Mode
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			GPIO_ResetBits(GPIOD, GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14);

			//Read the voltage values for each of the three peripherals
//			SqueezeReading=SensorRead(squeeze);
//			TapReading=SensorRead(tap);
//			SqueezeReading=SensorRead(spin);

//			if (ADCConvertedValues[1] != 0xFFFF)
//			    {
////			      printf("%d %d\n", ADCConvertedValues[0], ADCConvertedValues[1]);
//			      TapReading=ADCConvertedValues[1];
//			      ADCConvertedValues[1] = 0xFFFF;
//			    }
//
////			printf(TapReading);
////

			if (SqueezeReading>SqueezeThreshold){
				//Turn on Squeeze LED
				//Play Squeeze music note

			}

			if (SpinReading>SpinThreshold){
				//Turn on Spin LED
				//Play Spin music note
			}

			if (TapReading<TapThreshold){
				//Turn on Tap LED
				GPIO_SetBits(GPIOC,GPIO_Pin_2);
				//Play Tap music note
			}
			delay_nms(.01);
		}

		//If GameMode = 2, initialize Simon Says Mode
		else if(GameMode == 2){
			//Turn on 2 LEDS to indicate it's in Simon Says Mode
			GPIO_SetBits(GPIOD, GPIO_Pin_15| GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_12| GPIO_Pin_13);

		}

		//If GameMode = 3, initialize Storyboard mode
		else if(GameMode == 3){
			//Turn on 3 LEDS to indicate it's in Storyboard Mode
			GPIO_SetBits(GPIOD, GPIO_Pin_15| GPIO_Pin_14| GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);

			//Read Sensor values
//			SqueezeReading=SensorRead(squeeze);
//			TapReading=SensorRead(tap);
//			SqueezeReading=SensorRead(spin);




			if (SqueezeReading>SqueezeThreshold){
				//Turn on Squeeze LED
				//Play next part of the song

			}

			if (SpinReading>SpinThreshold){
				//Turn on Spin LED
				//Play next part of the song
			}

			if (TapReading<TapThreshold){
				//Turn on Tap LED
				GPIO_SetBits(GPIOC,GPIO_Pin_2);
				//Play next part of the song
			}
			delay_nms(.01);
		}

}
}

void SysTick_Handler(void) {
	TimeTick_Decrement();
}
