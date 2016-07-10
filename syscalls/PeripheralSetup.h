void PeripheralsInit(void); //Tap = PA5 -- Squeeze = PA3 -- Spin = PC2

void SqueezeLEDInit(void); //Connect LED to PA0
void PushButtonInit(void); //Turns on the blue push button on the stm board

int SensorRead(int sensor); //Reads the voltage value input of the different peripheral devices.
							 //For the function input (sensor), type "squeeze","tap","spin".

void TapLedInit(void);


void ws2812_send (uint16_t len);
void DMA1_Stream4_IRQHandler (void);
void ws2812_initTimer (uint32_t * buffer);
