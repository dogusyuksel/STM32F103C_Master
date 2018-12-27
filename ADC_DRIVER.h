#ifndef _ADC_DRIVER
#define _ADC_DRIVER

//these are ADC pins' numbers
typedef enum
{
	IN0,
	IN1,
	IN2,
	IN3,
	IN4,
	IN5,
	IN6,
	IN7
}ADC_PINS;

//these are ADC functions error flags
typedef enum
{
	ADC_ERR_OK,
	ADC_ERR_UNDEFINED_PIN,
	ADC_ERR_MEMORY
}ADC_ERRORS;

void ConfigureADCChannels(ADC_PINS *pinList, uint32_t len); //used to init a series of ADC channels, feed the function with a pin list with specified list len
ADC_ERRORS ReadADCValue(ADC_PINS pinNumber, uint16_t *data); //read specified channel's ADC value

#endif
