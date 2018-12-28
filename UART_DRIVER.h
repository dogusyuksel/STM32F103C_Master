#ifndef _UART_DRIVER
#define _UART_DRIVER

#include "stdint.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"

#define UART_STOP_BIT USART_StopBits_1
#define UART_PARITY USART_Parity_No
#define UART_DATA_LEN USART_WordLength_8b
#define UART_INTERRUPT_PRIORITY 0
#define UART_INTERRUPT_SUBPRIORITY 0

	typedef enum
	{
		UART_ERR_OK,
		UART_ERR_UNKNOWN,
		UART_ERR_NOT_ENOUGH,
		UART_ERR_MUCH_MORE,
		UART_ERR_MEMORY
	}UART_ERRORS;
	
	static const uint16_t SERIALPORT_SEND_BUFFER_LEN          		= 128;
	static const uint16_t SERIALPORT_RECV_BUFFER_LEN          		= 128;
	

	void ConfigureUART(USART_TypeDef *uart, uint32_t baudRate, uint16_t dataLen);
	void SendData(USART_TypeDef *uart, uint8_t *buffer, uint32_t len);
	UART_ERRORS GetData(USART_TypeDef *uart, uint8_t *buffer, uint32_t len);
	void ClearBuffer(USART_TypeDef *uart);
	uint32_t GetDataLen(USART_TypeDef *uart);
	uint32_t SendChar (USART_TypeDef *uart, uint8_t ch);
	
#endif
