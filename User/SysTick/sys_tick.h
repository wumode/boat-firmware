#include "stm32f10x.h"
#include "system_stm32f10x.h"
#include "core_cm3.h"

#ifndef SYS_TICK_H
#define SYS_TICK_H

void SysTick_Init(void);
void Delay_us(__IO uint32_t nTime);
#endif  
