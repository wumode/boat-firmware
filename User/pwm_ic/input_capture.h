#ifndef INPUT_CAPTURE_H
#define INPUT_CAPTURE_H
#include "stm32f10x.h"
#include "sys_config.h"

#define CAPTURE_PERIOD 149
#define CAPTURE_PRESCALER 71

void TIM2_Capture_Init(u16 arr,u16 psc);
u8 TIM2_4channel_process(u16 arr,u16 psc);

#endif
