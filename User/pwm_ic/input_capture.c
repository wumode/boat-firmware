
#include <stdio.h>
#include "input_capture.h"
extern u16 TIM2_CH1_STATUS,TIM2_CH2_STATUS,TIM2_CH3_STATUS,TIM2_CH4_STATUS;
extern u16 TIM2_CH2_START_VALUE,TIM2_CH2_END_VALUE,TIM2_CH1_START_VALUE,TIM2_CH1_END_VALUE;
extern u16 TIM2_CH3_START_VALUE,TIM2_CH3_END_VALUE,TIM2_CH4_START_VALUE,TIM2_CH4_END_VALUE;
/*
˵����TIM2��ʱ�����ĸ�ͨ����Ӧ���ŷֱ��PA0\PA1\PA2\PA3.
Warning�� arr����ֵԽС��ͨ����������Խ�ߣ�������ͨ���ĸߵ�ƽʱ�����ֵ��С��
					ʵ�⣺arr��ֵΪ10ʱ���������ֵΪ180ms���ҡ�
					psc����Ϊ72-1����arr+1������ʱ�������ж�һ�ε�ʱ�䡣��λΪus.
*/
void TIM2_Capture_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	/*ʱ��ʹ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	/*����TIM*/
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	/*����GPIO*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	//����ߵ�ƽ�������˿�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);

	/*���ò���*/
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0;  //���˲�
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ش���
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ITConfig(TIM2,TIM_IT_CC1,ENABLE);
	/*���ò���*/
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0;  //���˲�
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ش���
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ITConfig(TIM2,TIM_IT_CC2,ENABLE);
	/*���ò���*/
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ITConfig(TIM2,TIM_IT_CC3,ENABLE);
	/*���ò���*/
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ITConfig(TIM2,TIM_IT_CC4,ENABLE);
	/*����NVIC*/
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		/*ʹ��ָ���ն�����*/
		TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);
		
		TIM_Cmd(TIM2,ENABLE);
}


u8 TIM2_4channel_process(u16 arr,u16 psc)
{
	u8 processed=0;
	u32 STATUS_CH;
	/*��ͨ��1������Чʱ*/
	TIM_Cmd(TIM2,DISABLE);
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,DISABLE);
	if(TIM2_CH1_STATUS&0x8000)
	{
		STATUS_CH = TIM2_CH1_STATUS&0x3FFF;
		processed=1;						/*���STATUS>0*/
		if(STATUS_CH>0) 
		{
			remote_channel_data.channel_1 = (STATUS_CH-1)*(arr+1) + (arr+1-TIM2_CH1_START_VALUE)+TIM2_CH1_END_VALUE;
		}
		else 
		{
			if(TIM2_CH1_END_VALUE>=TIM2_CH1_START_VALUE){ 
				remote_channel_data.channel_1 = TIM2_CH1_END_VALUE-TIM2_CH1_START_VALUE;
			}
			else {
				remote_channel_data.channel_1 = TIM2_CH1_START_VALUE - TIM2_CH1_END_VALUE;
			}
		}
	}
	
	if(TIM2_CH2_STATUS&0x8000)
	{
		STATUS_CH = TIM2_CH2_STATUS&0x3FFF;
		processed=1;
		if(STATUS_CH>0) 
		{
			remote_channel_data.channel_2 = (STATUS_CH-1)*(arr+1) + (arr+1-TIM2_CH2_START_VALUE)+TIM2_CH2_END_VALUE;
		}
		else 
		{
			if(TIM2_CH2_END_VALUE>=TIM2_CH2_START_VALUE) {
				remote_channel_data.channel_2  = TIM2_CH2_END_VALUE-TIM2_CH2_START_VALUE;
			}
			else {
				remote_channel_data.channel_2  = TIM2_CH2_START_VALUE - TIM2_CH2_END_VALUE;
			}
		}
	}

	if(TIM2_CH3_STATUS&0x8000)
	{
		STATUS_CH = TIM2_CH3_STATUS&0x3FFF;
		processed=1;
		if(STATUS_CH>0) 
		{
			remote_channel_data.channel_3  = (STATUS_CH-1)*(arr+1) + (arr+1-TIM2_CH3_START_VALUE)+TIM2_CH3_END_VALUE;
		}
		else 
		{
			if(TIM2_CH3_END_VALUE>=TIM2_CH3_START_VALUE) 
			{
				remote_channel_data.channel_3  = TIM2_CH3_END_VALUE-TIM2_CH3_START_VALUE;
			}
			else {
				remote_channel_data.channel_3 = TIM2_CH3_START_VALUE - TIM2_CH3_END_VALUE;
			}
		}
	}

	if(TIM2_CH4_STATUS&0x8000)
	{
		STATUS_CH = TIM2_CH4_STATUS&0x3FFF;
		processed=1;
		if(STATUS_CH>0) 
		{
			remote_channel_data.channel_4 = (STATUS_CH-1)*(arr+1) + (arr+1-TIM2_CH4_START_VALUE)+TIM2_CH4_END_VALUE;
		}
		else 
		{
			if(TIM2_CH4_END_VALUE>=TIM2_CH4_START_VALUE) {
				remote_channel_data.channel_4 = TIM2_CH4_END_VALUE-TIM2_CH4_START_VALUE;
			}
			else{
				remote_channel_data.channel_4 = TIM2_CH4_START_VALUE - TIM2_CH4_END_VALUE;
			}
		}
	}	

	/*
	���������ݺ���������־λ�����¿�ʼ��һ�ζ�ȡ
	*/
	TIM2_CH1_STATUS = 0;
	TIM2_CH2_STATUS = 0;
	TIM2_CH3_STATUS = 0;
	TIM2_CH4_STATUS = 0;
	TIM_Cmd(TIM2,ENABLE);
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);	
	return processed;
}


void TIM2_IRQHandler()
{
	/*
	============�����жϴ���==============
	65536usƫ������
	��65536:
	SRART_VALUE:300
	END_VALUE:700
	ʵ�ʣ�65536 - 300 + 700 us
	*/
	if(TIM_GetITStatus(TIM2,TIM_IT_Update))
	{
		if((!(TIM2_CH1_STATUS&0x8000))&&(TIM2_CH1_STATUS&0x4000))
		{
			if((TIM2_CH1_STATUS&0x3FFF)==0x3FFF)
			{
				TIM2_CH1_STATUS |= 0x8000;
				TIM2_CH1_END_VALUE=0xffff;
			}else 
			{
				TIM2_CH1_STATUS ++;			
			}
		}
		
		if((!(TIM2_CH2_STATUS&0x8000))&&(TIM2_CH2_STATUS&0x4000))
		{
				if((TIM2_CH2_STATUS&0x3FFF)==0x3FFF)
				{
					TIM2_CH2_STATUS |= 0x8000;
					TIM2_CH2_END_VALUE=0xffff;
				}else 
				{
					TIM2_CH2_STATUS ++;			
				}
		}
		
		if((!(TIM2_CH3_STATUS&0x8000))&&(TIM2_CH3_STATUS&0x4000))
		{
				if((TIM2_CH3_STATUS&0x3FFF)==0x3FFF)
				{
					TIM2_CH3_STATUS |= 0x8000;
					TIM2_CH3_END_VALUE=0xffff;
				}else 
				{
					TIM2_CH3_STATUS ++;			
				}
		}
		
		if((!(TIM2_CH4_STATUS&0x8000))&&(TIM2_CH4_STATUS&0x4000))
		{
				if((TIM2_CH4_STATUS&0x3FFF)==0x3FFF)
				{
					TIM2_CH4_STATUS |= 0x8000;
					TIM2_CH4_END_VALUE=0xffff;
				}else 
				{
					TIM2_CH4_STATUS ++;			
				}
		}
		
		
	}
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
	/*
	==========�����жϴ���============
	*/
	if(TIM_GetITStatus(TIM2,TIM_IT_CC1))	//�����ж�
	{
		if(TIM2_CH1_STATUS&0x4000)
		{	
			TIM2_CH1_END_VALUE = TIM_GetCapture1(TIM2);
			TIM2_CH1_STATUS |= 0x8000;
			TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising);	//�ظ�Ϊ�����ش���
		}
		else
		{
			TIM2_CH1_START_VALUE = TIM_GetCapture1(TIM2);
			TIM2_CH1_STATUS= 0;
			TIM2_CH1_STATUS |= 0x4000;
			TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);
		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
	}
	
	if(TIM_GetITStatus(TIM2,TIM_IT_CC2))	//�����ж�
	{
		if(TIM2_CH2_STATUS&0x4000)
		{
			TIM2_CH2_END_VALUE = TIM_GetCapture2(TIM2);
			TIM2_CH2_STATUS |= 0x8000;
			TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising);	//�ظ�Ϊ�����ش���
		}
		else
		{
			TIM2_CH2_START_VALUE = TIM_GetCapture2(TIM2);
			TIM2_CH2_STATUS= 0;
			TIM2_CH2_STATUS |= 0x4000;
			TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);
		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
	}
	
	if(TIM_GetITStatus(TIM2,TIM_IT_CC3))	//�����ж�
	{
		if(TIM2_CH3_STATUS&0x4000)
		{
			TIM2_CH3_END_VALUE = TIM_GetCapture3(TIM2);
			TIM2_CH3_STATUS |= 0x8000;
			TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising);	//�ظ�Ϊ�����ش���
		}
		else
		{
			TIM2_CH3_START_VALUE = TIM_GetCapture3(TIM2);
			TIM2_CH3_STATUS= 0;
			TIM2_CH3_STATUS |= 0x4000;
			TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);
		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);
	}

	if(TIM_GetITStatus(TIM2,TIM_IT_CC4))	//�����ж�
	{
		if(TIM2_CH4_STATUS&0x4000)
		{
			TIM2_CH4_END_VALUE = TIM_GetCapture4(TIM2);
			TIM2_CH4_STATUS |= 0x8000;
			TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Rising);	//�ظ�Ϊ�����ش���
		}
		else
		{
			TIM2_CH4_START_VALUE = TIM_GetCapture4(TIM2);
			TIM2_CH4_STATUS= 0;
			TIM2_CH4_STATUS |= 0x4000;
			TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Falling);
		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC4);
	}		
}
