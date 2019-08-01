#ifndef CONTROL_H
#define CONTROL_H

#include "sys.h"
#include "oled.h"
#include "sys_config.h"
#include "stdio.h"
#include "led.h"
#include "motor.h"
#include "data_transmission.h"
#include "laser.h"
#include "input_capture.h"
#include "usart.h"

extern struct SAngle stcAngle;
extern u8 trace_pot_x;
extern u8 trace_pot_y;
extern float trace_error_ori; 
extern float trace_error_last;
extern float trace_error; 
extern u8 trace_stop_flag;

void control(void);
void SysTick_Init(void);
void Delay_us(__IO uint32_t nTime);
#endif  
