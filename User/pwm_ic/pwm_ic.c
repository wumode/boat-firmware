#include "pwm_ic.h"
//TIM3???????
TIM_ICS TIM_Ic;    
 
//TIM_IcChannel ????TIM????,?????????????
u16 TIM_IcChannel = 1+(TIM_ICCH1<<1)+(TIM_ICCH2<<2)+(TIM_ICCH3<<3)+(TIM_ICCH4<<4);

void TIM3_PWMICInit(void)
{
	u8 i=0;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef  TIM_ICInitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	/***********************NVIC??*****************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&NVIC_InitStruct);
	
	/**********************TIM3 GPIO??*****************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
 
	/**********************???TIM3*******************************/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = TIM_ICARR;      
	TIM_TimeBaseInitStruct.TIM_Prescaler = TIM_ICPSC;     
 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	/**********************???TIM3 IC*******************************/
	TIM_ICInitStruct.TIM_ICFilter = TIM_ICFIT;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI ;
 
   	if(TIM_ICCH1==1)
	{
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	  GPIO_Init(GPIOA,&GPIO_InitStruct);
	  TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	  TIM_ICInit(TIM3, &TIM_ICInitStruct);
	}
	
	if(TIM_ICCH2==1)
	{
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	  GPIO_Init(GPIOA,&GPIO_InitStruct);
	  TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	  TIM_ICInit(TIM3, &TIM_ICInitStruct);
	}
	
	 if(TIM_ICCH3==1)
       {
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	  GPIO_Init(GPIOB,&GPIO_InitStruct);
	  TIM_ICInitStruct.TIM_Channel = TIM_Channel_3;
	  TIM_ICInit(TIM3, &TIM_ICInitStruct);	
	}
	
	if(TIM_ICCH4==1)
	{
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	  GPIO_Init(GPIOB,&GPIO_InitStruct);
	  TIM_ICInitStruct.TIM_Channel = TIM_Channel_4;
	  TIM_ICInit(TIM3, &TIM_ICInitStruct);
	}
 
	TIM_ITConfig(TIM3, TIM_IcChannel,ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}
void TIM3_IRQHandler(void)
{
	u8  j = 0;
	u16 i = 0, *pTimFre, *pTimCcrT, *pTimOver, *pTimSR, *pTimCCR;
	
        pTimSR  = TIM_ICSR;  //??TIM3 SR?????
	
	for(i=1;i<16;i<<=1)  //?????????
	{
		  //????CH3??????,?????SR?????????????????1
		  //?????,????i??SR????,?????TIM_IcChannel???????????
		  //???? http://blog.csdn.net/a3748622/article/details/79075892
	    if( ((*pTimSR&i)&TIM_IcChannel) > 0 ) break;			
		  j++;
	}
	
	if(j>0)j--; //?j???? 0 1 2 3 4?? 0 0 1 2 3,???????????
	
	pTimCCR  = TIM_ICCCR+2*j; //??????,??TIM3 CCR?????
	pTimFre  = &TIM_Ic.Ic1_Fre+j;      
	pTimCcrT = &TIM_Ic.Ccr1+j;
	pTimOver = &TIM_Ic.Ic1_Over+j;
 
	
	if(i==1)   //??????,??ARR????
	{
		  
		  for(j=0;j<4;j++)
		 {
		        *(pTimOver+j)+=1;
			if(*(pTimOver+j)>TIM_OverF) { *(pTimOver+j) = 0; *(pTimCcrT+j) = 0; *(pTimFre+j) = 0; } 
		 }
		 *pTimSR &= ~i;       //???????	
	}
	else       //??CCR????,????
	{
		         if(*pTimCcrT< 1 )    //?????????
			{			    
			       *pTimCcrT  = *pTimCCR;		
                           if(*pTimCcrT <1) *pTimCcrT += 1; 
			       *pTimOver = 0;   //??????
			}
			else   //?????????
			{
			       *pTimFre= 72000000/( *pTimCCR - *pTimCcrT +  *pTimOver*60000 );	
				printf("%d\n", *pTimFre);
                               *pTimCcrT  = 0;						
			}	
			*pTimSR &= ~i;       //???????
         }
	
}

