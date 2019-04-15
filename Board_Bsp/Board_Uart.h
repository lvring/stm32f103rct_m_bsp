#ifndef __BOARD_UART_H
#define __BOARD_UART_H
#include "stm32f1xx_hal.h"
#include "printf.h"
#include "board_init.h"
#include "m_port.h"

typedef enum
{
	USART_DEBUG = 0,
  USART_N        // COMNum
}Board_Uart_Name_e;

typedef struct
{
  uint32_t BaudRate;
  uint32_t WordLength;
  uint32_t StopBits;
	uint32_t Parity;
}Board_Uart_HardWareConfig_t;

typedef struct
{
	Board_Uart_Name_e UsartName;
	USART_TypeDef *Instance;
	Board_Uart_HardWareConfig_t *HardConfig;
	UART_HandleTypeDef UartHalHandle;
	
}Board_Uart_Control_t;

extern Board_Uart_Control_t UartHandle[USART_N];

void UART_Init(Board_Uart_Name_e usartname);




#endif
