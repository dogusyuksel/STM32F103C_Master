#include "TIMER_DRIVER.h"

#include "stm32f10x.h"
#include <stdlib.h>
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include <assert.h>


//these are hold user callback function pointers
void (*timer2Funct)()  = NULL;
void (*timer3Funct)()  = NULL;
void (*timer4Funct)()  = NULL;


void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		//DO WHATEWER YOU WANT
		//execute user defined function
			if(timer2Funct != NULL)
				(*timer2Funct)();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		//DO WHATEWER YOU WANT
		//execute user defined function
			if(timer3Funct != NULL)
				(*timer3Funct)();
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		//DO WHATEWER YOU WANT
		//execute user defined function
			if(timer4Funct != NULL)
				(*timer4Funct)();
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}


void ConfigureTimerWithInterruptCallback(TIM_TypeDef *timer, uint16_t millis, void (*f)())
{
	//control timer parameter
	assert((timer == TIM2) || (timer == TIM3) || (timer == TIM4));
	assert(millis <= 6500);
	
	TIM_TimeBaseInitTypeDef TIMER_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	if(timer == TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	else if(timer == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	else if(timer == TIM4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}
	
	TIM_TimeBaseStructInit(&TIMER_InitStructure);
	TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIMER_InitStructure.TIM_Prescaler = (uint16_t)(SystemCoreClock / 10000);  //7.200 * (500 * 10) / Clock Source ? SECOND, mesela 72MHz için YARIM SANIYE
	TIMER_InitStructure.TIM_Period = (millis * 10); //NOTE THAT, since max range of uint16_t is 65535, then we millis MUST E less then 6500, this actually is 6.5 seconds
	TIM_TimeBaseInit(timer, &TIMER_InitStructure);
	TIM_ITConfig(timer, TIM_IT_Update, ENABLE);
	TIM_Cmd(timer, ENABLE);

	/* NVIC Configuration */
	/* Enable the TIM4_IRQn Interrupt */
	if(timer == TIM2)
	{
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		timer2Funct = f;
	}
	else if(timer == TIM3)
	{
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		timer3Funct = f;
	}
	else if(timer == TIM4)
	{
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		timer4Funct = f;
	}
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER_INTERRUPT_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMER_INTERRUPT_SUBPRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


