#include "GeneralTim.h"


static void TIM4_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	

/* -----------------------------------------------------------------------
    TIM4 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM3CLK = 36 MHz, Prescaler = 0x0, TIM4 counter clock = 36 MHz
    TIM4 ARR Register = 999 => TIM4 Frequency = TIM4 counter clock/(ARR + 1)
    TIM4 Frequency = 36 KHz.
    TIM4 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
    TIM4 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
    TIM4 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
    TIM4 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period;       //当定时器从0计数到999，即为1000次，为一个定时周期
	TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM_Prescaler;	    //设置预分频：不预分频，即为36MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//设置时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
//  TIM_OCInitStructure.TIM_Pulse = 0;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平

//  TIM_OC1Init(TIM4, &TIM_OCInitStructure);	 //使能通道1

//  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM

	TIM_OC2Init(TIM4, &TIM_OCInitStructure);	  //使能通道2

	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = 0;	//设置通道3的电平跳变值，输出另外一个占空比的PWM

//  TIM_OC3Init(TIM4, &TIM_OCInitStructure);	 //使能通道3

//  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;	//设置通道4的电平跳变值，输出另外一个占空比的PWM

	TIM_OC4Init(TIM4, &TIM_OCInitStructure);	//使能通道4

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);			 // 使能TIM4重载寄存器ARR

	/* TIM4 enable counter */
	TIM_Cmd(TIM4, ENABLE);                   //使能定时器4
}



///*
// * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
// * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
// * 另外三个成员是通用定时器和高级定时器才有.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            都有
// *	TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
// *  TIM_Period               都有
// *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)

void PWMSet(uint8_t Wheel,int32_t TIM_CCR)
{
	if(Wheel){
		if(TIM_CCR>0){
			TIM4->CCR2 = TIM_CCR;
			GPIO_ResetBits(CH1_1_PORT,CH1_1_PIN); 
		}
		else{
			TIM4->CCR2 = 7200 + TIM_CCR;
			GPIO_SetBits(CH1_1_PORT,CH1_1_PIN);
		}
	}
	else{
		if(TIM_CCR>0){
			TIM4->CCR4 = TIM_CCR;
			GPIO_ResetBits(CH0_1_PORT,CH0_1_PIN); 
		}
		else{
			TIM4->CCR4 = 7200 + TIM_CCR;
			GPIO_SetBits(CH0_1_PORT,CH0_1_PIN);
		}
	}
}


void GENERAL_TIM_Init(void)
{
	
	TIM4_Mode_Config();
}

/*********************************************END OF FILE**********************/
