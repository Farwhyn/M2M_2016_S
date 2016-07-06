#include <stdio.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "PeripheralSetup.h"
#include "delay.h"


int main(void)
{
	printf("Hello\r\n");
	SqueezeInit(); //Connect Sensor to PC0
	TapInit(); //Connect Sensor to PC1
	SpinInit(); //Connect Sensor to PC2

//	SqueezeLEDInit(); //Connect LED to PA0
	PushButtonInit (); //Turns on the blue push button on the stm board

	//Initialize the delay timer
	SysTick_Init();

	//Initialize values for each sensor reading
	int SqueezeReading=0;
	int TapReading=0;
	int SpinReading=0;

	//Initialize state of the blue button to OFF
	int ButtonState=0;

	//Initialize Sensor Thresholds
	int SqueezeThreshold=0;
	int TapThreshold=0;
	int SpinThreshold=0;
	//Begin main loop

	GPIO_SetBits(GPIOD, GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12);
	while (1){
		//Read the state of the blue button
		ButtonState=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);



		//If blue button is off, initialize the Free Play mode
		if (!ButtonState){
			//Turn on the LEDs to indicate it's in Free Play Mode
			GPIO_SetBits(GPIOD, GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12);

			//Read the voltage values for each of the three peripherals
			SqueezeReading=SensorRead("Squeeze");
			TapReading=SensorRead("Tap");
			printf("%d\r\n", TapReading);
			SqueezeReading=SensorRead("Spin");

			if (SqueezeReading>SqueezeThreshold){
				//Turn on Squeeze LED
				//Play Squeeze music note
			}

			if (SpinReading>SqueezeThreshold){
				//Turn on Spin LED
				//Play Spin music note
			}

			if (TapReading>SqueezeThreshold){
				//Turn on Tap LED
				//Play Tap music note

			}
			delay_nms(1000);
		}

		//If blue button is on, initialize Simon Says Mode
		else{
			//Flash the LEDs ON and OFF to indicate Simon Says Mode
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12);

		}



//		printf("%d\r\n", Reading);

	}
}

void SysTick_Handler(void) {
	TimeTick_Decrement();
}
