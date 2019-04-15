
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "board_uart.h"
#include "board_init.h"
#include "m_scheduler.h"
#include "m_alloc.h"
#include "m_timer.h"
#include "m_port.h"

/* USER CODE END Includes */
void printf_1(void* UserParameters)
{
	printf("task_1\r\n");
}
void printf_2(void* UserParametersoid)
{
	printf("task_2\r\n");
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
	M_Timer_Init();//初始化系统DWT定时器实现微秒级定时
	m_init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  UART_Init(USART_DEBUG);
	SchedulerInit(1000);//间隔10Hz
	//int Scheduler_Create(const char *Create_Name,uint32_t Scheduler_Frenquency,bool Enable,void (*Func_Callback)(void *), void* UserParameters)
	Scheduler_Create("Printf1",1000,1,printf_1,(void *)0);
	Scheduler_Create("Printf2",1000,1,printf_2,(void *)0);
  while (1)
  {
		SchedulerRun();
  }
  /* USER CODE END 3 */
}
