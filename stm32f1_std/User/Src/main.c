#include "main.h"
#include "board_uart.h"
#include "board_init.h"
#include "m_scheduler.h"
#include "m_alloc.h"
#include "m_timer.h"
#include "m_port.h"
#include "easyflash.h"

void printf_1(void* UserParameters)
{
	printf("%d\r\n",1);
}
void printf_2(void* UserParametersoid)
{
	printf("task_2\r\n");
}
/**
 * Env demo.
 */
static void test_env(void) {
    uint32_t i_boot_times = NULL;
    char *c_old_boot_times, c_new_boot_times[11] = {0};

    /* get the boot count number from Env */
    c_old_boot_times = ef_get_env("boot_times");
    assert_param(c_old_boot_times);
    i_boot_times = atol(c_old_boot_times);
    /* boot count +1 */
    i_boot_times ++;
    printf("The system now boot %d times\r\n", i_boot_times);
    /* interger to string */
    sprintf(c_new_boot_times,"%ld", i_boot_times);
    /* set and store the boot count number to Env */
    ef_set_env("boot_times", c_new_boot_times);
    ef_save_env();
}


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	Com_Init(COM_1,115200);
	M_Timer_Init();//初始化系统DWT定时器实现微秒级定时
	m_init();
	SchedulerInit(1000);
	Scheduler_Create("Printf1",1000,1,printf_1,(void *)0);
	Scheduler_Create("Printf2",1000,1,printf_2,(void *)0);
	if (easyflash_init() == EF_NO_ERR) {
        /* test Env demo */
        test_env();
  } 
	else{printf("error\r\n");}
	while(1)
	{
		SchedulerRun();
		
	}

}

