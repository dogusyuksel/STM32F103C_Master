
#ifndef _TIMER_DRIVER
#define _TIMER_DRIVER

#include "stdint.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define TIMER_INTERRUPT_PRIORITY 2
#define TIMER_INTERRUPT_SUBPRIORITY 0

void ConfigureTimerWithInterruptCallback(TIM_TypeDef *timer, uint16_t millis, void (*f)());

#endif
