void SqueezeInit(); //Connect Sensor to PC0
void TapInit(); //Connect Sensor to PC1
void SpinInit(); //Connect Sensor to PC2

void SqueezeLEDInit(); //Connect LED to PA0
void PushButtonInit (); //Turns on the blue push button on the stm board

int SensorRead(char sensor); //Reads the voltage value input of the different peripheral devices.
							 //For the function input (sensor), type "squeeze","tap","spin".

