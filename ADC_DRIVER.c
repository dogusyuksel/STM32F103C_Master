#include "ADC_DRIVER.h"

//include libraries here
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


volatile ADC_PINS *actualPinList = NULL;
volatile uint16_t *actualPinData = NULL;
volatile uint32_t listLen = 0;


ADC_ERRORS ReadADCValue(ADC_PINS pinNumber, uint16_t *data)
{
		
	if((!actualPinList) || (!actualPinData))
		return ADC_ERR_MEMORY;
	
	int i = 0;
	for(i = 0; i < listLen; i++)
	{
		if(actualPinList[i] > IN7)
		{
			//it means error
			return ADC_ERR_UNDEFINED_PIN;
		}
		if(actualPinList[i] == pinNumber)
		{
			//return data here
			*data = actualPinData[i];
			return ADC_ERR_OK;
		}
	}
	return ADC_ERR_UNDEFINED_PIN;
}


void ConfigureADCChannels(ADC_PINS *pinList, uint32_t len)
{
	
	if(actualPinList)
		free(actualPinList);
	
	if(actualPinData)
		free(actualPinData);
	
	actualPinList = (ADC_PINS *)malloc(len * sizeof (ADC_PINS));
	actualPinData = (uint16_t *)malloc(len * sizeof(uint16_t));
	
	if((!actualPinList) || (!actualPinData))
		return;
	
	listLen = len;
	
	//make an copy pin list
	int i = 0;
	for(i=0; i < len; i++)
		actualPinList[i] = pinList[i];
	
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //since max freq is 72MHz, divider 6 is fine for ADC because it does not exceed max value
	/* Enable ADC1 and GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE); //we use ADC1 as default
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE ); //we use DMA1 as default

	DMA_InitStructure.DMA_BufferSize = len;	// howmany analog channel will be read
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)actualPinData;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1 , ENABLE ) ;

	uint16_t gpioPins = 0; //make OR operation to select all pins
	int i = 0;
	for(i = 0; i < len; i++)
	{
		assert(pinList[i] <= IN7);
		
		if(pinList[i] == IN0) //it means, PA0
			gpioPins = gpioPins | GPIO_Pin_0;
		if(pinList[i] == IN1) //it means, PA1
			gpioPins = gpioPins | GPIO_Pin_1;
		if(pinList[i] == IN2) //it means, PA2
			gpioPins = gpioPins | GPIO_Pin_2;
		if(pinList[i] == IN3) //it means, PA3
			gpioPins = gpioPins | GPIO_Pin_3;
		if(pinList[i] == IN4) //it means, PA4
			gpioPins = gpioPins | GPIO_Pin_4;
		if(pinList[i] == IN5) //it means, PA5
			gpioPins = gpioPins | GPIO_Pin_5;
		if(pinList[i] == IN6) //it means, PA6
			gpioPins = gpioPins | GPIO_Pin_6;
		if(pinList[i] == IN7) //it means, PA7
			gpioPins = gpioPins | GPIO_Pin_7;
	}
	GPIO_InitStructure.GPIO_Pin = gpioPins; //GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6; //select pins here
		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = len;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	for(i=0; i < len; i++)
	{
		uint8_t channel = ADC_Channel_0; //select defaultly 
		
		if(pinList[i] == IN0) //it means, PA0
			channel = ADC_Channel_0;
		else if(pinList[i] == IN1) //it means, PA1
			channel = ADC_Channel_1;
		else if(pinList[i] == IN2) //it means, PA2
			channel = ADC_Channel_2;
		else if(pinList[i] == IN3) //it means, PA3
			channel = ADC_Channel_3;
		else if(pinList[i] == IN4) //it means, PA4
			channel = ADC_Channel_4;
		else if(pinList[i] == IN5) //it means, PA5
			channel = ADC_Channel_5;
		else if(pinList[i] == IN6) //it means, PA6
			channel = ADC_Channel_6;
		else if(pinList[i] == IN7) //it means, PA7
			channel = ADC_Channel_7;
		
		// configure order in the memory and pin here
		ADC_RegularChannelConfig(ADC1, channel, (i + 1), ADC_SampleTime_7Cycles5);
	}
	
	ADC_Cmd(ADC1 , ENABLE ) ;
	ADC_DMACmd(ADC1 , ENABLE ) ;
	ADC_ResetCalibration(ADC1);

	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);

	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd ( ADC1 , ENABLE ) ;

}

