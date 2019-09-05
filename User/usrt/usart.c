#include "usart.h"
#include "laser.h"
#include "control.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

char gps_line[80];
u8 line_length = 0;



static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //NVIC_Init(&NVIC_InitStructure);
}

void USART1_Config(u32 bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	NVIC_Configuration();
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	USART_Cmd(DEBUG_USARTx, ENABLE);	   
}

void USART2_Config(u32 bound)
{  	 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	  //使能映射IO模块（开启时钟）
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);  //开启I/O口重映射模块
	
	//USART_TX  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
   
	//USART_RX	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE); 
}



void USART3_Config(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_USART3,ENABLE);  //开启I/O口重映射模块
	//TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	
	USART_Cmd(USART3, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//USART_ClearFlag(USART1, USART_FLAG_TC);     
}

void USART4_Config(u32 bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	
	/* config USART1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	//UART-RX-PC11
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
		      
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure); 
	
	NVIC_InitTypeDef NVIC_InitStructure;
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	USART_Cmd(UART4, ENABLE);	
}


void USART5_Config(u32 bound){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;        

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE );
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE );
  //TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
  //RX  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART5, &USART_InitStructure);

	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	USART_Cmd(UART5, ENABLE);
}

void Usart1_SendData(uint8_t *data, u16 length)
{
	unsigned int k=0;
	do
	{
		USART_SendData(USART1,*(data + k));
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		k++;
	} while(k<length);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET){}
}

void Usart1_SendString(char *str)
{
	unsigned int k=0;
	do
	{
		USART_SendData(USART1,*(str + k));
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		k++;
	} while(*(str + k)!='\0');
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET){}
}

void Usart2_SendByte(uint8_t ch)
{
	USART_SendData(USART2,ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

void Usart2_SendString(char *str)
{
	unsigned int k=0;
	do
	{
		USART_SendData(USART2,*(str + k));
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		k++;
	} while(*(str + k)!='\0');
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET){}
}

void Usart3_SendByte(uint8_t ch)
{
	USART_SendData(USART3,ch);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	
}

void Usart3_SendString(char *str)
{
	unsigned int k=0;
	do
	{
		USART_SendData(USART3,*(str + k));
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		k++;
	} while(*(str + k)!='\0');
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET){}
}

void Usart4_SendByte(uint8_t ch)
{
	USART_SendData(UART4,ch);
	while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);	
}

void Usart4_SendString(char *str)
{
	unsigned int k=0;
	do
	{
		USART_SendData(UART4,*(str + k));
		while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
		k++;
	} while(*(str + k)!='\0');
	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET){}
}

void Usart4_SendData(uint8_t *data, u16 length)
{
	unsigned int k=0;
	do
	{
		USART_SendData(UART4,*(data + k));
		while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
		k++;
	} while(k<length);
	while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET){}
}

void Usart5_SendByte(uint8_t ch)
{
	USART_SendData(UART5,ch);
	while (USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);	
}

void Usart5_SendString(char *str)
{
	unsigned int k=0;
	do
	{
		USART_SendData(UART5,*(str + k));
		while (USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
		k++;
	} while(*(str + k)!='\0');
	while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET){}
}

void Usart5_SendData(uint8_t *data, u16 length)
{
	unsigned int k=0;
	do
	{
		USART_SendData(UART5,*(data + k));
		while (USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
		k++;
	} while(k<length);
	while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET){}
}

//串口1接收中断
void USART1_IRQHandler(void)
{	
	char Usart1_Receive;
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)!=RESET){
		USART_ClearFlag(USART1, USART_IT_RXNE);
		Usart1_Receive = USART_ReceiveData(USART1);
	}
	else{
		USART_ClearFlag(USART1, USART_IT_RXNE);
	}
} 

//串口2接收中断		IMU
void USART2_IRQHandler(void)
{
	char Usart2_Receive;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		USART_ClearFlag(USART2, USART_IT_RXNE);
		//USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		Usart2_Receive = USART_ReceiveData(USART2);
		CopeSerial2Data_1(Usart2_Receive);
	}
	else{
		Usart2_Receive = USART_ReceiveData(USART2);
		USART_ClearFlag(USART2, USART_IT_RXNE);
	}
}

//串口3接收中断
void USART3_IRQHandler(void)
{
	char Usart3_Receive;
	
	if(USART_GetFlagStatus(USART3,USART_IT_RXNE)!=RESET)
	{
		Usart3_Receive = USART_ReceiveData(USART3);
		USART_ClearFlag(USART3, USART_IT_RXNE);
		//printf("%c", Usart3_Receive);
		if(Usart3_Receive == '$'){
			gps_line[line_length] = '\0';
			AnalysisGPS(gps_line);
			line_length = 0;
		}
		gps_line[line_length] = Usart3_Receive;
		line_length++;
		if(line_length>=80){
			line_length = 0;
		}
	}
	else{
		Usart3_Receive = USART_ReceiveData(USART3);
		USART_ClearFlag(USART3, USART_IT_RXNE);
	}
}


u8 Pos = 0;
u8 openmv_rx[4];
u8 trace_rx[3];
void UART4_IRQHandler(void)
{
	u8 Res;
	if(USART_GetFlagStatus(UART4,USART_IT_RXNE)!=RESET)
	{
		Res =USART_ReceiveData(UART4);		
		USART_ClearFlag(UART4, USART_IT_RXNE);
		if(Res == 0x0a)
		{
			openmv_rx[Pos] = Res;
			Pos = 0;
			laser_set = openmv_rx[0];
			trace_pot_x = trace_rx[1];
			trace_stop_flag = trace_rx[2];
		}
		else
		{
			openmv_rx[Pos] = Res;
			Pos++;
		} 
	}
	else{
		Res =USART_ReceiveData(UART4);		
		USART_ClearFlag(UART4, USART_IT_RXNE);
	}
}


void UART5_IRQHandler(void)
{
	char Usart5_Receive;
	
	if(USART_GetFlagStatus(UART5,USART_IT_RXNE)!=RESET)
	{
		//printf("%c", Usart5_Receive);
		Usart5_Receive = USART_ReceiveData(UART5);
		USART_ClearFlag(UART5, USART_IT_RXNE);
		DT_Data_Receive_Prepare(Usart5_Receive);
	}
	else{
		Usart5_Receive = USART_ReceiveData(UART5);
		USART_ClearFlag(UART5, USART_IT_RXNE);
		//printf("%c", Usart4_Receive);
	}
}

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	return (ch);
}

int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){}
	return (int)USART_ReceiveData(USART1);
}


