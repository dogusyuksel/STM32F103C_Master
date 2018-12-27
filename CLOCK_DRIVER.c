
#include "CLOCK_DRIVER.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include <assert.h>


void InitClock(OscillatorSelection oscillatorType, ClockFrequency oscillatorFrequency)
{	
	//control parameters here
	assert(((oscillatorType == INTERNAL) || (oscillatorType == EXTERNAL)));
	assert(oscillatorFrequency <= MHz_72);
	
	//note that, if oscillator type is internal, then clock cannot exceed 8MHz, control it
	assert(!((oscillatorType == INTERNAL) && (oscillatorFrequency > MHz_8)));
	
	/* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	if(oscillatorType == INTERNAL)
		RCC_HSICmd(ENABLE); /* Enable HSI */
	else
		RCC_HSEConfig( RCC_HSE_ON); /* Enable HSE */

	if(oscillatorType == INTERNAL)
		while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET); /* Wait till HSI is ready */
	else
		while(RCC_WaitForHSEStartUp() != SUCCESS); /* Wait till HSE is ready */


	/* Enable Prefetch Buffer */
	FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable);

	/* Flash 2 wait state */
	FLASH_SetLatency( FLASH_Latency_2);

	/* HCLK = SYSCLK */
	RCC_HCLKConfig( RCC_SYSCLK_Div1); //set SYSCLK to HCLK, It means set it to max value, we guaranteed that HCLK cannot exceed 72MHz

	/* PCLK2 = HCLK */
	RCC_PCLK2Config( RCC_HCLK_Div1); //Set PCLK2 to HCLK, we set it to max. PCLK cannot exceed 72MHz because we guaranteed it.

	/* PCLK1 = HCLK/2 */
	RCC_PCLK1Config( RCC_HCLK_Div2); //Set PCLK1 to HCLK/2, since HCLK cannot exceed 72MHz it means PCLK1 cannot exceed 36MHz

	uint32_t pllSourceDivision = RCC_PLLSource_HSE_Div2;
	if(oscillatorType == INTERNAL)
		pllSourceDivision = RCC_PLLSource_HSI_Div2;		
	
	//note that since we divide clock to 2 anyway, we get a 4 MHz not. In order to input, we can configure RCC_PLLMul_9 now.
	switch(oscillatorFrequency) 
	{
		 case MHz_8  :
				RCC_PLLConfig(pllSourceDivision, RCC_PLLMul_2); //2 * 4 = 8 MHz
				break;
		
		 case MHz_12  :
				RCC_PLLConfig(pllSourceDivision, RCC_PLLMul_3); //3 * 4 = 12 MHz
				break;
		
		 case MHz_16  :
				RCC_PLLConfig(pllSourceDivision, RCC_PLLMul_4); //4 * 4 = 16 MHz
				break;
		
		 case MHz_24  :
				RCC_PLLConfig(pllSourceDivision, RCC_PLLMul_6); //6 * 4 = 24 MHz
				break;
		
		 case MHz_32  :
				RCC_PLLConfig(pllSourceDivision, RCC_PLLMul_8); //8 * 4 = 32 MHz
				break;
		
		 case MHz_48  :
				RCC_PLLConfig(pllSourceDivision, RCC_PLLMul_12); //12 * 4 = 48 MHz
				break;
		
		 case MHz_64  :
				RCC_PLLConfig(pllSourceDivision, RCC_PLLMul_16); //16 * 4 = 64 MHz
				break;
		
		 case MHz_72  :
				//this is special condition so reconfigure pll source division
				pllSourceDivision = RCC_PLLSource_HSE_Div1;
		 
				assert(oscillatorType != INTERNAL); //this is error condition, you cannot set 72MHz with HSI, only HSE
		 
				RCC_PLLConfig(pllSourceDivision, RCC_PLLMul_9); //9 * 8 = 72 MHz
				break;
		
		 default :
			RCC_PLLConfig(pllSourceDivision, RCC_PLLMul_2); // set clock to 8 in default
	}

  
	// Enable PLL
  RCC_PLLCmd(ENABLE);
  
	// Wait till PLL is ready
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  
	// Select PLL as system clock source
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
	// Wait till PLL is used as system clock source
  while(RCC_GetSYSCLKSource() != 0x08);
  
}

