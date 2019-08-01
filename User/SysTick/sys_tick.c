#include "sys_tick.h"

static __IO uint32_t TimingDelay;

void SysTick_Init(void){
	if(SysTick_Config(SystemCoreClock / 200)) //���ٸ�ʱ�����ڲ���һ���ж�
	{
		while(1);
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


void Delay_us(__IO uint32_t nTime){
	TimingDelay = nTime;
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	while(TimingDelay!=0);
}

void TimingDelay_Decrement(void){
	if(TimingDelay != 0x00){
		TimingDelay--;
	}
}
