#ifndef __BSP_GENERALTIME_H
#define __BSP_GENERALTIME_H

#include "sys.h"

//							+   -					A   B
//wheel0 ����  B9  B8    ����A1  A0
//wheel1 ����  B7  B6    ����A7  A6


/********* ***ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM3
//  wheel0 B9  B8
//  wheel1 B7  B6

#define            GENERAL_TIM                   TIM8
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB2Periph_TIM8
#define            GENERAL_TIM_Period            7200-1
#define            GENERAL_TIM_Prescaler         0

// TIM3 ����Ƚ�ͨ��0
#define            GENERAL_TIM_CH0_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            GENERAL_TIM_CH0_PORT          GPIOB
#define            GENERAL_TIM_CH0_PIN           GPIO_Pin_9
#define						 CH0_1_PORT										 GPIOB
#define						 CH0_1_PIN  									 GPIO_Pin_8

// TIM3 ����Ƚ�ͨ��1
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            GENERAL_TIM_CH1_PORT          GPIOB
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_7
#define						 CH1_1_PORT										 GPIOB
#define						 CH1_1_PIN  									 GPIO_Pin_6

//// TIM3 ����Ƚ�ͨ��3
//#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOC
//#define            GENERAL_TIM_CH3_PORT          GPIOC
//#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_8

//// TIM3 ����Ƚ�ͨ��4
//#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOC
//#define            GENERAL_TIM_CH4_PORT          GPIOC
//#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_9

/**************************��������********************************/

//void Mecanum_SteelSpeedApply(int* wheel);
void GENERAL_TIM_Init(void);
//void PWMSet(uint8_t Wheel,int32_t TIM_CCR);
//void PWMInit(void);
#endif	/* __BSP_GENERALTIME_H */


