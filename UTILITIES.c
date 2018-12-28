
#include "UTILITIES.h.h"
#include "stm32f10x.h"


extern "C"
{
	static __IO uint32_t msTicks;

	// SysTick_Handler function will be called every 1 us
	void SysTick_Handler()
	{
		if (msTicks != 0)
			msTicks--;
	}
};

void Delay(uint32_t ms)
{
	msTicks = 0;
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	SysTick_Config(SystemCoreClock / 1000000);
	
	msTicks = (ms * 1000);
	
	//wait here
	while(msTicks != 0){}
}


void EnterSleep(void)
{
	// ENABLE sleep function
	  NVIC_SystemLPConfig(NVIC_LP_SLEEPONEXIT, ENABLE);

	/* sleep*/
	__WFI();

	/*System states are same, for example, pin statuses are not changed in sleep mode.*/
}


void EnterStanBy(void)
{
	// ENABLE Wake Up Pin, used for configuration
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	PWR_WakeUpPinCmd(ENABLE);

	/* Enters STANDBY mode, used for go into standby mode */
	PWR_EnterSTANDBYMode();

	/*After this, when wake up pin triged to HIGH, system wakes up.*/

}
