# STM32F103C_Master
This repo contains the specified MCU's pheripheral drivers.

USING ADC DRIVER
--------------------------

#include "ADC_DRIVER.h"

	int main (void)
	{
		ADC_PINS adcPins[] = {IN1, IN4, IN6, IN7}; //initialize a pin list
		ConfigureADCChannels(adcPins, 4); //configure pins as analog pins

		while(1)
		{
			//read adc values now
			uint16_t adcValue_Pin1 = 0, adcValue_Pin4 = 0, adcValue_Pin6 = 0, adcValue_Pin7 = 0;
			ReadADCValue(IN1, &adcValue_Pin1);
			ReadADCValue(IN4, &adcValue_Pin4);
			ReadADCValue(IN6, &adcValue_Pin6);
			ReadADCValue(IN7, &adcValue_Pin7);
		}

		return 1;
	}
