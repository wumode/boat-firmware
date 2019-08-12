#include "exti.h"
#include "stdio.h"

void NVIC_Configuration(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI_PB14_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	NVIC_Configuration();
}

void EXTI15_10_IRQHandler(void){
	if(EXTI_GetFlagStatus(EXTI_Line14) != RESET) 
	{
		//LED_TOGGLE;
		
	}
	EXTI_ClearITPendingBit(EXTI_Line14);
}

void EXTIT_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXIT_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	

	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU; 
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXIT_InitStruct.EXTI_Line = EXTI_Line0;
	EXIT_InitStruct.EXTI_LineCmd=ENABLE;
	EXIT_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXIT_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXIT_InitStruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
}


#define target1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define target2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)
#define target3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)


char temp1=0;
char temp2=0;
char temp3=0;

	void judge1(void)
{
		if(target1==1){
		temp1=0;
		}
		else if(target1==0){
		temp1=1;}
		
 }
	
void judge2(void)
{
		if(target2==1){
		temp2=2;
		}
		else if(target2==0){
		temp2=3;}
}


	void judge3(void)
{
		if(target3==1){
		temp3=4;
		}
		else if(target3==0){
		temp3=5;}
}
		
		
 void EXTI0_IRQHandler(void)
{
	//temp1=temp1+48;
	//printf("a");
	if(EXTI_GetFlagStatus(EXTI_Line0) != RESET) 
	{
		//LED_TOGGLE;
		//printf("a");
	}
	//USART_SendData(USART1,0xFF);
	EXTI_ClearITPendingBit(EXTI_Line0);
}
 
 void EXTI1_IRQHandler(void)
{
	temp2=temp2+48;
	//USART_SendData(USART1,temp1);
	EXTI_ClearITPendingBit(EXTI_Line1);
}

 void EXTI2_IRQHandler(void)
{
	temp3=temp3+48;
	//USART_SendData(USART1,temp1);
	EXTI_ClearITPendingBit(EXTI_Line2);
}



