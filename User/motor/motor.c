#include "motor.h"
#include "sys_config.h"

void PwmInit()
{		 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
	
	TIM_DeInit(TIM4);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	TIM_TimeBaseStructure.TIM_Period = PWM_TIM_Period;
	TIM_TimeBaseStructure.TIM_Prescaler =PWM_TIM_Prescaler; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_Pulse = PWM_TIM_Pause;
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = LATERAL_TIM_PAUSE;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
 
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	//GPIO_SetBits(GPIOA, GPIO_Pin_12);
} 


void Servo_Pwm_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	TIM_TimeBaseStructure.TIM_Period = SERVO_PWM_TIM_Period;
	TIM_TimeBaseStructure.TIM_Prescaler = SERVO_PWM_TIM_Prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	//TIM_ClearITPendingBit(TIM3,  TIM_IT_Update); 
	//TIM_ITConfig(TIM3,  TIM_IT_Update, ENABLE);
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = SERVO_INIT;     
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  
 
	//TIM_CtrlPWMOutputs(TIM3,ENABLE);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

void PwmSet(int pwm, uint8_t number){
	if(number == 1){
		TIM4->CCR1 = pwm;
	}
	else if(number == 2){
		TIM4->CCR2 = pwm;
	}
	else if(number == 3){
		TIM4->CCR3 = pwm;
	}
	else if(number == 4){
		TIM4->CCR4 = pwm;
	}
	
}

void ServoPwmSet(int pwm, uint8_t number){
	if(number == 1){
		TIM3->CCR1 = pwm;
	}
	else if(number == 2){
		TIM3->CCR2 = pwm;
	}
	else if(number == 3){
		TIM3->CCR3 = pwm;
	}
	else if(number == 4){
		TIM3->CCR4 = pwm;
	}
}
