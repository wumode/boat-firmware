#ifndef MOTOR_H
#define MOTOR_H
#include "sys.h"
#include "stm32f10x.h"
#include "system_stm32f10x.h"
 
#define PWM_TIM_Period            19999
#define PWM_TIM_Prescaler         71
#define PWM_TIM_Pause			  1500
#define LATERAL_TIM_PAUSE		  1000

#define SERVO_PWM_TIM_Period	  19999
#define SERVO_PWM_TIM_Prescaler	  71
#define SERVO_INIT 				  1500
#define K						  318.309f

#define MOTOR(a) if(a) \
	GPIO_SetBits(GPIOC, GPIO_Pin_9);\
else	\
	GPIO_ResetBits(GPIOC, GPIO_Pin_9)

#define AIN2   PAout(15)
#define AIN1   PBout(5)
#define BIN1   PBout(4)
#define BIN2   PAout(12)

void PwmSet(int pwm, uint8_t number);
void PwmInit(void);
void Servo_Pwm_Init(void) ;
void ServoPwmSet(int pwm, uint8_t number);
#endif
