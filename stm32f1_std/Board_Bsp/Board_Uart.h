#ifndef __BOARD_UART_H
#define __BOARD_UART_H
#include "stm32f10x.h"
#include "printf.h"
#include "board_init.h"
#include "m_port.h"

typedef enum
{
  COM_1 = 0,   // COM1 (TX=PA9, RX=PA10)
	COM_2 = 1,   // COM2 (TX=PA9, RX=PA10)
  COM_3 = 2,   // COM3 (TX=PB10, RX=PB11)
  COM_N        // COMNum
}Com_Name_e;
//--------------------------------------------------------------
// 串口数据接收结构体
//--------------------------------------------------------------
typedef struct
{
	//结构体变量
	uint8_t *pu8Databuf;
	uint16_t u16Datalength;
	//RTE_MessageQuene_t ComQuene;  //串口数据环形队列
}Com_Data_t;

//--------------------------------------------------------------
// Struktur einer UARTs
//--------------------------------------------------------------
typedef struct {
	Com_Name_e ComName;    // Name
	USART_TypeDef* USARTx;
	GPIO_TypeDef* ComPort; // Port
	uint16_t ComPintx; // Pin
	uint16_t ComPinrx; // Pin
	uint32_t GpioClk; // Clock
	uint16_t WordLength; 
	uint16_t StopBits;
	uint16_t Parity; 
	uint16_t Mode; 
	uint16_t HardwareFlowControl; 
	DMA_Channel_TypeDef* DMATXChannel;
	DMA_Channel_TypeDef* DMARXChannel;
	uint16_t DataBufferLen;
	uint16_t DataQueneLen;
	Com_Data_t ComData;
}Com_Handle_t;
/* Wait for TX empty */
#define USART_TXEMPTY(USARTx)               ((USARTx->SR & USART_FLAG_TXE))
#define USART_WAIT(USARTx)                  while (!USART_TXEMPTY(USARTx))
#define USART_TX_REG(USARTx)                ((USARTx)->DR)
#define USART_WRITE_DATA(USARTx, data)      ((USARTx)->DR = (data))

void Com_Init(Com_Name_e usart_name,uint32_t baudrate);
Com_Data_t* Com_ReturnQue(Com_Name_e usart_name);
void Com_Putc(Com_Name_e usart_name, volatile char c);
void Com_Puts(Com_Name_e usart_name, char* str);
void Com_Send(Com_Name_e usart_name, uint8_t* DataArray, uint32_t count);


#endif
