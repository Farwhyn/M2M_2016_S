void PeripheralsInit(void); //Tap = PC0 -- Squeeze = PC1 -- Spin = PC2

void SqueezeLEDInit(void); //Connect LED to PA0
void PushButtonInit(void); //Turns on the blue push button on the stm board

int SensorRead(int sensor); //Reads the voltage value input of the different peripheral devices.
							 //For the function input (sensor), type "squeeze","tap","spin".

