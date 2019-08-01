#ifndef LASER_H
#define LASER_H
#include "stm32f10x.h"
#include "sys_config.h"
#include "stdio.h"

#define LASER_PWM_TIM_Period	  7199
#define LASER_PWM_TIM_Prescaler	  0
#define LASER_INIT 				  7199

extern u8 laser_set;
void Laser_Init(void);
void Laser_control(void);

#endif
