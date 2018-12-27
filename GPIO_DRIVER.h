
#ifndef GPIO_DRIVER
#define GPIO_DRIVER

#include "stdint.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define GPIO_INTERRUPT_PRIORITY 1
#define GPIO_INTERRUPT_SUB_PRIORITY 0

	typedef enum {
		INPUT,
		OUTPUT
	} GPIO_DIRECTION;

	typedef enum {
		LOW,
		HIGH
	} GPIO_LEVEL;

	typedef enum {
		FALLING,
		RISING,
		BOTH
	} INTERRUPT_EDGE;

	void ConfigureGPIOPin(GPIO_TypeDef *port, uint16_t pin, GPIO_DIRECTION direction);
	void ConfigureInputWithInterruptCallback(GPIO_TypeDef *port, uint16_t pin, INTERRUPT_EDGE edge, void (*f)());
	
	void SetGPIOPin(GPIO_TypeDef *port, uint16_t pin, GPIO_LEVEL level);
	void ToggleGPIOPin(GPIO_TypeDef *port, uint16_t pin);
	GPIO_LEVEL GetGPIOPin(GPIO_TypeDef *port, uint16_t pin);
		
#endif
