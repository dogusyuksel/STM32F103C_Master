
#include "UART_DRIVER.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include <string.h>
#include "OPT_VTIMER.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


extern "C"
{	
	uint8_t volatile USART1Buffer[SERIALPORT_RECV_BUFFER_LEN];
	uint32_t volatile USART1BufferLen = 0;
	
	uint8_t volatile USART2Buffer[SERIALPORT_RECV_BUFFER_LEN]; 
	uint32_t volatile USART2BufferLen = 0;
	
	uint8_t volatile USART3Buffer[SERIALPORT_RECV_BUFFER_LEN];
	uint32_t volatile USART3BufferLen = 0;
	
	void USART1_IRQHandler(void)
	{
			if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
		{
					unsigned char RXc = USART_ReceiveData(USART1);
					USART1Buffer[(USART1BufferLen++)%SERIALPORT_RECV_BUFFER_LEN] = (uint8_t)RXc;
		}
	}

	void USART2_IRQHandler(void)
	{
			if ((USART2->SR & USART_FLAG_RXNE) != (u16)RESET)
		{
					unsigned char RXc = USART_ReceiveData(USART2);
					USART2Buffer[(USART2BufferLen++)%SERIALPORT_RECV_BUFFER_LEN] = (uint8_t)RXc;
		}
	}

	void USART3_IRQHandler(void)
	{
			if ((USART3->SR & USART_FLAG_RXNE) != (u16)RESET)
		{
					unsigned char RXc = USART_ReceiveData(USART3);
					USART3Buffer[(USART3BufferLen++)%SERIALPORT_RECV_BUFFER_LEN] = (uint8_t)RXc;
		}
	}

};


void void ConfigureUART(USART_TypeDef *uart, uint32_t baudRate, uint16_t dataLen)
{
	
	//control parameters
	assert((uart == USART1) || (uart == USART2) || (uart == USART3));
	
	//we assume that data bits: 8, stop bit: 1, parity: none for this configuration
	//there are 3 different uart on stm32f103c8 mcu and we will follow these.
	//UART1 --> PA10 - RX ,  PA9  - TX
	//UART2 --> PA3  - RX ,  PA2  - TX
	//UART3 --> PB11 - RX ,  PB10 - TX
	uint16_t rcvPin = GPIO_Pin_10; //initial configuration is for UART1
	uint16_t trnPin = GPIO_Pin_9;
	GPIO_TypeDef* gpioPort = GPIOA;
	uint8_t uart_irqn = USART1_IRQn;
	
	if(uart == USART2)
	{
		rcvPin = GPIO_Pin_3;
		trnPin = GPIO_Pin_2;
		gpioPort = GPIOA;
		uart_irqn = USART2_IRQn;
		/* Enable USART1 and GPIOA clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	}
	else if(uart == USART3)
	{
		rcvPin = GPIO_Pin_11;
		trnPin = GPIO_Pin_10;
		gpioPort = GPIOB;
		uart_irqn = USART3_IRQn;
		/* Enable USART1 and GPIOA clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	}
	else
	{
		//this is for USART1
		/* Enable USART1 and GPIOA clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	}
	
	/* NVIC Configuration */
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = uart_irqn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = priority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = subPreority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* Configure the GPIOs */
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = trnPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gpioPort, &GPIO_InitStructure);

	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = rcvPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(gpioPort, &GPIO_InitStructure);
	
	/* Configure the USART1 */
	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = UART_DATA_LEN;
	USART_InitStructure.USART_StopBits = UART_STOP_BIT;
	USART_InitStructure.USART_Parity = UART_PARITY;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(uart, &USART_InitStructure);

	/* Enable USART1 */
	USART_Cmd(uart, ENABLE);
	
	/* Enable the USART1 Receive interrupt: this interrupt is generated when the
	USART1 receive data register is not empty */
	USART_ITConfig(uart, USART_IT_RXNE, ENABLE);
}

void SendData(USART_TypeDef *uart, uint8_t *buffer, uint32_t len)
{
	assert(len <= (int)SERIALPORT_SEND_BUFFER_LEN);
	int i = 0;
	for(i=0; i < len; i++)
		SendChar (uart, (int)(buffer[i]));
}


UART_ERRORS GetData(USART_TypeDef *uart, uint8_t *buffer, uint32_t len)
{
	memset(&buffer[0], 0, len);
	
	assert((uart == USART1) || (uart == USART2) || (uart == USART3));

	if(uart == USART1)
	{
		int newLen = len;
		if(len > USART1BufferLen)
			newLen = USART1BufferLen;
		int i = 0;
		for(i = 0; i < newLen; i++)
			buffer[i] = USART1Buffer[i];
		
		if(len < USART1BufferLen)
		{
			//get first len byte so shift the buffer left in len count
			USART1BufferLen = USART1BufferLen - len;
			unsigned char *dummyBuffer = (unsigned char *)malloc(USART1BufferLen * sizeof(unsigned char));
			memcpy(dummyBuffer, &USART1Buffer[len], USART1BufferLen);
			memcpy(USART1Buffer, dummyBuffer, USART1BufferLen);
			free(dummyBuffer);
			return UART_ERR_OK;
		} else
		{
			USART1BufferLen = 0;
			return UART_ERR_MEMORY;
		}
		
	}
	else if(uart == USART2)
	{
		int newLen = len;
		if(len > USART2BufferLen)
			newLen = USART2BufferLen;
		int i = 0;
		for(i = 0; i < newLen; i++)
			buffer[i] = USART2Buffer[i];
		
		if(len < USART2BufferLen)
		{
			//get first len byte so shift the buffer left in len count
			USART2BufferLen = USART2BufferLen - len;
			unsigned char *dummyBuffer = (unsigned char *)malloc(USART2BufferLen * sizeof(unsigned char));
			memcpy(dummyBuffer, &USART2Buffer[len], USART2BufferLen);
			memcpy(USART2Buffer, dummyBuffer, USART2BufferLen);
			free(dummyBuffer);
			return UART_ERR_OK;
		} else
		{
			USART2BufferLen = 0;
			return UART_ERR_MEMORY;
		}
	}
	else if(uart == USART3)
	{
		int newLen = len;
		if(len > USART3BufferLen)
			newLen = USART3BufferLen;
		int i = 0;
		for(i = 0; i < newLen; i++)
			buffer[i] = USART3Buffer[i];
		
		if(len < USART3BufferLen)
		{
			//get first len byte so shift the buffer left in len count
			USART3BufferLen = USART3BufferLen - len;
			unsigned char *dummyBuffer = (unsigned char *)malloc(USART3BufferLen * sizeof(unsigned char));
			memcpy(dummyBuffer, &USART3Buffer[len], USART3BufferLen);
			memcpy(USART3Buffer, dummyBuffer, USART3BufferLen);
			free(dummyBuffer);
			return UART_ERR_OK;
		} else
		{
			USART3BufferLen = 0;
			return UART_ERR_MEMORY;
		}
	}
	else
		return UART_ERR_UNKNOWN;
}


void ClearBuffer(USART_TypeDef *uart)
{
	assert((uart == USART1) || (uart == USART2) || (uart == USART3));
	if(uart == USART1)
		USART1BufferLen = 0;
	else if(uart == USART2)
		USART2BufferLen = 0;
	else if(uart == USART3)
		USART3BufferLen = 0;
}
			
uint32_t GetDataLen(USART_TypeDef *uart)
{
	assert((uart == USART1) || (uart == USART2) || (uart == USART3));
	if(uart == USART1)
		return USART1BufferLen;
	else if(uart == USART2)
		return USART2BufferLen;
	else
		return USART3BufferLen;
}

uint32_t SendChar (USART_TypeDef *uart, uint8_t ch)
{
	while (!(uart->SR & USART_FLAG_TXE)){}
	uart->DR = (ch & 0x1FF); //We send 8 data + 1 stop bit = 9 bits, normally register is 16 bits

  return (ch);
}


