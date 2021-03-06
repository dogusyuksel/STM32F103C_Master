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

USING CLOCK CONFIGURATION
----------------------------------------

	#include "CLOCK_DRIVER.h"

	int main (void)
	{
		//setup the clock configuration
		InitClock(EXTERNAL, MHz_72);

		while(1)
		{
			//
		}

		return 1;
	}


USING GPIO DRIVER
----------------------------

	#include "GPIO_DRIVER.h"

	void dummy(void)
	{
		//use this function just like interrupt callback
		ToggleGPIOPin(GPIOB, GPIO_Pin_13);
	}

	int main (void)
	{
		//set port B pin 13 as output
		ConfigureGPIOPin(GPIOB, GPIO_Pin_13, OUTPUT);
		//write the pin LOW
		SetGPIOPin(GPIOB, GPIO_Pin_13, HIGH);

		//set port A pin 7 as input with rising edge and callback with "dummy" function
		ConfigureInputWithInterruptCallback(GPIOA, GPIO_Pin_7, RISING, &dummy);

		while(1)
		{
			//this project toggles the led when button pressed.
		}

		return 1;
	}
	
USING INTERNAL FLASH DRIVER
-----------------------------------------

	#include "INTERNAL_FLASH_DRIVER.h"

	int main (void)
	{
		uint32_t data = 0x19, readdata = 0;
		uint32_t address = FLASH_DATA_PART_START_ADDRESS;

		//ClearFlash();

		ReadData(address, &readdata, 1);
		if(readdata != data)
			WriteData(address, &data, 1);

		while(1)
		{
			//
		}

		return 1;
	}
	
	
USING TIMER DRIVER
-----------------------------


	#include "TIMER_DRIVER.h"

	void UserTIM3CallBack()
	{
		//do whatever you want successively in 6.5 seconds
	}

	int main (void)
	{
		ConfigureTimerWithInterrupt(TIM3, 6500, &UserTIM3CallBack);

		while(1)
		{
			//
		}

		return 1;
	}
	
	
USING UART DRIVER
------------------------------------

	#include "UART_DRIVER.h"

	int main (void)
	{
		ConfigureUART(USART3, uint32_t baudRate, uint16_t dataLen);

		while(1)
		{
			uint8_t receivedBuff[20];
			memset(receivedBuff, 0, 20);
			UART_ERRORS errCondition = GetData(USART3, receivedBuff, 3, 10000);
			if ((errCondition == UART_ERR_OK) && (strncmp((char *)receivedBuff, "OK\r", 3) == 0)) 
			{
				SendData(USART3, (uint8_t *)"OK REVEIVED\n", 12);
			}
		}

		return 1;
	}
	
