#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include "sys.h"
#include <stdio.h>
#include "data_transmission.h"

#define USART1_DR_BASE 0x40013804 	//0x40013800 + 0x04
#define SENDBUFF_SIZE 5000

// ´®¿Ú1-USART1
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

#define  DEBUG_USART_GPIO_CLK           RCC_APB2Periph_GPIOA
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler


void USART1_Config(u32 bound);
void USART2_Config(u32 bound);
void USART3_Config(u32 bound);
void USART4_Config(u32 bound);
void USART5_Config(u32 bound);

void Usart1_SendString(char *str);
void Usart2_SendString(char *str);
void Usart3_SendString(char *str);
void Usart4_SendString(char *str);
void Usart5_SendString(char *str);

void Usart1_SendData(uint8_t *data, u16 length);
void Usart4_SendData(uint8_t *data, u16 length);
void Usart5_SendData(uint8_t *data, u16 length);

void Usart4_SendByte(uint8_t ch);

extern void AnalysisGPS(char* line);
extern void CopeSerial2Data(uint8_t ucData);
extern void CopeSerial2Data_1(uint8_t ucData_1);
extern void CopeSerialVelocaityData(char ucData);
#endif
