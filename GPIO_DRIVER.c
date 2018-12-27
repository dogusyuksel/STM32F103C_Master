
#include "GPIO_DRIVER.h"

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "stm32f10x.h"
#include <stdlib.h>
#include <assert.h>


//these variables are hold function pointers that called by user
void (*extiLine0)()  = NULL;
void (*extiLine1)()  = NULL;
void (*extiLine2)()  = NULL;
void (*extiLine3)()  = NULL;
void (*extiLine4)()  = NULL;
void (*extiLine5)()  = NULL;
void (*extiLine6)()  = NULL;
void (*extiLine7)()  = NULL;
void (*extiLine8)()  = NULL;
void (*extiLine9)()  = NULL;
void (*extiLine10)() = NULL;
void (*extiLine11)() = NULL;
void (*extiLine12)() = NULL;
void (*extiLine13)() = NULL;
void (*extiLine14)() = NULL;
void (*extiLine15)() = NULL;


//INTERRUPT PARTS
extern "C" void EXTI0_IRQHandler(void)
{
 
    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        //execute user defined function
				if(extiLine0 != NULL)
					(*extiLine0)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line0);
}

extern "C" void EXTI1_IRQHandler(void)
{
 
    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        //execute user defined function
				if(extiLine1 != NULL)
					(*extiLine1)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line1);
}
extern "C" void EXTI2_IRQHandler(void)
{
 
    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        //execute user defined function
				if(extiLine2 != NULL)
					(*extiLine2)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line2);
}
extern "C" void EXTI3_IRQHandler(void)
{
 
    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        //execute user defined function
				if(extiLine3 != NULL)
					(*extiLine3)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line3);
}
extern "C" void EXTI4_IRQHandler(void)
{
 
    //Check if EXTI_Line0 is asserted
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
        //execute user defined function
				if(extiLine4 != NULL)
					(*extiLine4)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line4);
}
extern "C" void EXTI9_5_IRQHandler(void)
{
    //Check if EXTI_Line5 is asserted
    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        //execute user defined function
				if(extiLine5 != NULL)
					(*extiLine5)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line5);
		
    //Check if EXTI_Line6 is asserted
    if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        //execute user defined function
				if(extiLine6 != NULL)
					(*extiLine6)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line6);
		
    //Check if EXTI_Line7 is asserted
    if(EXTI_GetITStatus(EXTI_Line7) != RESET)
    {
        //execute user defined function
				if(extiLine7 != NULL)
					(*extiLine7)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line7);
		
    //Check if EXTI_Line8 is asserted
    if(EXTI_GetITStatus(EXTI_Line8) != RESET)
    {
        //execute user defined function
				if(extiLine8 != NULL)
					(*extiLine8)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line8);
		
    //Check if EXTI_Line9 is asserted
    if(EXTI_GetITStatus(EXTI_Line9) != RESET)
    {
        //execute user defined function
				if(extiLine9 != NULL)
					(*extiLine9)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line9);
}

extern "C" void EXTI15_10_IRQHandler(void)
{
    //Check if EXTI_Line10 is asserted
    if(EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        //execute user defined function
				if(extiLine10 != NULL)
					(*extiLine10)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line10);
		
    //Check if EXTI_Line11 is asserted
    if(EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
        //execute user defined function
				if(extiLine11 != NULL)
					(*extiLine11)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line11);
		
    //Check if EXTI_Line12 is asserted
    if(EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        //execute user defined function
				if(extiLine12 != NULL)
					(*extiLine12)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line12);
		
    //Check if EXTI_Line13 is asserted
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        //execute user defined function
				if(extiLine13 != NULL)
					(*extiLine13)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line13);
		
    //Check if EXTI_Line14 is asserted
    if(EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        //execute user defined function
				if(extiLine14 != NULL)
					(*extiLine14)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line14);
		
    //Check if EXTI_Line15 is asserted
    if(EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
        //execute user defined function
				if(extiLine15 != NULL)
					(*extiLine15)();
    }
    //we need to clear line pending bit manually
    EXTI_ClearITPendingBit(EXTI_Line15);
}
//END OF INTERRUPT PARTS


void ConfigureInputWithInterruptCallback(GPIO_TypeDef *port, uint16_t pin, INTERRUPT_EDGE edge, void (*f)())
{
	uint8_t portSource = GPIO_PortSourceGPIOA;
	uint8_t pinSource = GPIO_PinSource0;
	uint32_t extiLineNumber = EXTI_Line0;
	uint8_t channelNumber = EXTI0_IRQn;
	
	//error setup
	assert(portSource <= GPIO_PortSourceGPIOG);
	
	if(port == GPIOA)
		portSource = GPIO_PortSourceGPIOA;
	else if(port == GPIOB)
		portSource = GPIO_PortSourceGPIOB;
	else if(port == GPIOC)
		portSource = GPIO_PortSourceGPIOC;
	else if(port == GPIOD)
		portSource = GPIO_PortSourceGPIOD;
	else if(port == GPIOE)
		portSource = GPIO_PortSourceGPIOE;
	else if(port == GPIOF)
		portSource = GPIO_PortSourceGPIOF;
	else if(port == GPIOG)
		portSource = GPIO_PortSourceGPIOG;
	
	//error setup
	assert(pin <= GPIO_Pin_15);
	
	if(pin == GPIO_Pin_0)
	{
		pinSource = GPIO_PinSource0;
		extiLineNumber = EXTI_Line0;
		channelNumber = EXTI0_IRQn;
		
		extiLine0 = f;
	}
	else if(pin == GPIO_Pin_1)
	{
		pinSource = GPIO_PinSource1;
		extiLineNumber = EXTI_Line1;
		channelNumber = EXTI1_IRQn;
		
		extiLine1 = f;
	}
	else if(pin == GPIO_Pin_2)
	{
		pinSource = GPIO_PinSource2;
		extiLineNumber = EXTI_Line2;
		channelNumber = EXTI2_IRQn;
		
		extiLine2 = f;
	}
	else if(pin == GPIO_Pin_3)
	{
		pinSource = GPIO_PinSource3;
		extiLineNumber = EXTI_Line3;
		channelNumber = EXTI3_IRQn;
		
		extiLine3 = f;
	}
	else if(pin == GPIO_Pin_4)
	{
		pinSource = GPIO_PinSource4;
		extiLineNumber = EXTI_Line4;
		channelNumber = EXTI4_IRQn;
		
		extiLine4 = f;
	}
	else if(pin == GPIO_Pin_5)
	{
		pinSource = GPIO_PinSource5;
		extiLineNumber = EXTI_Line5;
		channelNumber = EXTI9_5_IRQn;
		
		extiLine5 = f;
	}
	else if(pin == GPIO_Pin_6)
	{
		pinSource = GPIO_PinSource6;
		extiLineNumber = EXTI_Line6;
		channelNumber = EXTI9_5_IRQn;
		
		extiLine6 = f;
	}
	else if(pin == GPIO_Pin_7)
	{
		pinSource = GPIO_PinSource7;
		extiLineNumber = EXTI_Line7;
		channelNumber = EXTI9_5_IRQn;
		
		extiLine7 = f;
	}
	else if(pin == GPIO_Pin_8)
	{
		pinSource = GPIO_PinSource8;
		extiLineNumber = EXTI_Line8;
		channelNumber = EXTI9_5_IRQn;
		
		extiLine8 = f;
	}
	else if(pin == GPIO_Pin_9)
	{
		pinSource = GPIO_PinSource9;
		extiLineNumber = EXTI_Line9;
		channelNumber = EXTI9_5_IRQn;
		
		extiLine9 = f;
	}
	else if(pin == GPIO_Pin_10)
	{
		pinSource = GPIO_PinSource10;
		extiLineNumber = EXTI_Line10;
		channelNumber = EXTI15_10_IRQn;
		
		extiLine10 = f;
	}
	else if(pin == GPIO_Pin_11)
	{
		pinSource = GPIO_PinSource11;
		extiLineNumber = EXTI_Line11;
		channelNumber = EXTI15_10_IRQn;
		
		extiLine11 = f;
	}
	else if(pin == GPIO_Pin_12)
	{
		pinSource = GPIO_PinSource12;
		extiLineNumber = EXTI_Line12;
		channelNumber = EXTI15_10_IRQn;
		
		extiLine12 = f;
	}
	else if(pin == GPIO_Pin_13)
	{
		pinSource = GPIO_PinSource13;
		extiLineNumber = EXTI_Line13;
		channelNumber = EXTI15_10_IRQn;
		
		extiLine13 = f;
	}
	else if(pin == GPIO_Pin_14)
	{
		pinSource = GPIO_PinSource14;
		extiLineNumber = EXTI_Line14;
		channelNumber = EXTI15_10_IRQn;
		
		extiLine14 = f;
	}
	else if(pin == GPIO_Pin_15)
	{
		pinSource = GPIO_PinSource15;
		extiLineNumber = EXTI_Line15;
		channelNumber = EXTI15_10_IRQn;
		
		extiLine15 = f;
	}
	
	
	//enable AFIO clock
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);
	EXTI_InitTypeDef EXTI_InitStructure;
	//NVIC structure to set up NVIC controller
	NVIC_InitTypeDef NVIC_InitStructure;
	//GPIO structure used to initialize Button pins

	//Connect EXTI Lines to Button Pins
	GPIO_EXTILineConfig(portSource, pinSource);

	//select EXTI line12 because of pin 12
	EXTI_InitStructure.EXTI_Line = extiLineNumber;
	//select interrupt mode
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	
	//error condition
	assert(edge <= BOTH);
	
	//generate interrupt on rising edge
	if(edge == FALLING)
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	else if(edge == RISING)
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	else if(edge == BOTH)
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	
	//enable EXTI line
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	//send values to registers
	EXTI_Init(&EXTI_InitStructure);
	
	//disable AFIO clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  DISABLE);
	
	//configure NVIC
	//select NVIC channel to configure
	NVIC_InitStructure.NVIC_IRQChannel = channelNumber; //EXTI0_IRQn; because of pin number is 12, if it is 0, then select other for example
	//set priority to lowest
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = GPIO_INTERRUPT_PRIORITY;
	//set subpriority to lowest
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = GPIO_INTERRUPT_SUB_PRIORITY;
	//enable IRQ channel
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//update NVIC registers
	NVIC_Init(&NVIC_InitStructure);
	
}

//this function sets pins as input ot output. with this function, you cannot setup an interrupt.
void ConfigureGPIOPin(GPIO_TypeDef *port, uint16_t pin, GPIO_DIRECTION direction)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//error setup
	assert((port >= GPIOA) && (port <= GPIOG));

	// Enable the Clock
	if(port == GPIOA)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	else if(port == GPIOB)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	else if(port == GPIOC)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	else if(port == GPIOD)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	else if(port == GPIOE)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	else if(port == GPIOF)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	else if(port == GPIOG)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
	
	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = pin;
	if(direction == OUTPUT)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //set as output
	else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //set as input
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(port, &GPIO_InitStructure);
	
}

void SetGPIOPin(GPIO_TypeDef *port, uint16_t pin, GPIO_LEVEL level)
{
	//we dont need to control the pin as input or output because std lib do that already.
	if(level == LOW)
		GPIO_ResetBits(port, pin);
	else
		GPIO_SetBits(port, pin);
	
}


void ToggleGPIOPin(GPIO_TypeDef *port, uint16_t pin)
{
	//we dont need to control the pin as input or output because std lib do that already.
	port->ODR ^= pin; 
	
}

GPIO_LEVEL GetGPIOPin(GPIO_TypeDef *port, uint16_t pin)
{
	//we dont need to control the pin as input or output because std lib do that already.
	if(GPIO_ReadInputDataBit(port, pin) == Bit_SET)
		return HIGH;
	else
		return LOW;
	
}
