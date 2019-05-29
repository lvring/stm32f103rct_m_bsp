#include "Board_Uart.h"

const Board_Uart_HardWareConfig_t UartDefaultConfig = 
{
	.BaudRate = 115200,
	.WordLength = UART_WORDLENGTH_8B,
	.StopBits = UART_STOPBITS_1,
	.Parity = UART_PARITY_NONE,
};

Board_Uart_Control_t UartHandle[USART_N] = 
{
	{
		.UsartName = USART_DEBUG,
		.Instance = USART1,
		.HardConfig = (Board_Uart_HardWareConfig_t *)&UartDefaultConfig,
	}
};


UART_HandleTypeDef huart1;




/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void UART_Init(Board_Uart_Name_e usartname)
{

	UartHandle[usartname].UartHalHandle.Instance = UartHandle[usartname].Instance;
	UartHandle[usartname].UartHalHandle.Init.BaudRate = UartHandle[usartname].HardConfig->BaudRate;
	UartHandle[usartname].UartHalHandle.Init.WordLength = UartHandle[usartname].HardConfig->WordLength;
	UartHandle[usartname].UartHalHandle.Init.StopBits = UartHandle[usartname].HardConfig->StopBits;
	UartHandle[usartname].UartHalHandle.Init.Parity = UartHandle[usartname].HardConfig->Parity;
	UartHandle[usartname].UartHalHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle[usartname].UartHalHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle[usartname].UartHalHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if(HAL_UART_Init(&UartHandle[usartname].UartHalHandle) != HAL_OK)
	{
			Error_Handler();
	}
	

}


