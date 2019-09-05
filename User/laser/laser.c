#include "laser.h"

void Laser_Init(void) 
{
	  /*GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE ,&GPIO_InitStructure);*/
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	
	TIM_TimeBaseStructure.TIM_Period = LASER_PWM_TIM_Period;
	TIM_TimeBaseStructure.TIM_Prescaler = LASER_PWM_TIM_Prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	//TIM_ClearITPendingBit(TIM1,  TIM_IT_Update); 
	//TIM_ITConfig(TIM1,  TIM_IT_Update, ENABLE);
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = LASER_INIT;     
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	//TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	//TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	//TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	//TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
 
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}


void LaserControl(uint8_t status, uint16_t intensity){
	if(status){
		TIM1->CCR1 = LASER_PWM_TIM_Period - (int)(LASER_PWM_TIM_Period*intensity/100.0);
	}
	else{
		TIM1->CCR1 = LASER_PWM_TIM_Period;
	}
}

void Laser_control()
{
	if(laser_set==1 && empower_data.empower==1 && stop_laser == 0)
	{
		TIM1->CCR1 = 0;
		// laser_set = 0;
	    //GPIO_SetBits(GPIOE,GPIO_Pin_9);
	}
	else
	{
		TIM1->CCR1 = LASER_PWM_TIM_Period;
		// GPIO_ResetBits(GPIOE,GPIO_Pin_9);
	}
}
