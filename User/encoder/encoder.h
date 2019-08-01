#ifndef ENCODE_H
#define ENCODE_H

#include "sys.h"

#define ENCODER_TIM_PERIOD (u16)(65535)   

void Encoder_Init(void);
int  Read_Encoder(u8 wheel);


#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08


#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


// Encoder 通道0
#define            ENCODER_CH0_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ENCODER_CH0_PORT          GPIOA
#define            ENCODER_CH0_A_PIN         GPIO_Pin_1
#define            ENCODER_CH0_B_PIN         GPIO_Pin_0

// Encoder 通道1
#define            ENCODER_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ENCODER_CH1_PORT          GPIOA
#define            ENCODER_CH1_A_PIN         GPIO_Pin_7
#define            ENCODER_CH1_B_PIN         GPIO_Pin_6

// Encoder 通道2
#define            ENCODER_CH2_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            ENCODER_CH2_PORT          GPIOC
#define            ENCODER_CH2_A_PIN         GPIO_Pin_8
#define            ENCODER_CH2_B_PIN         GPIO_Pin_8

// Encoder 通道3
#define            ENCODER_CH3_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            ENCODER_CH3_PORT          GPIOC
#define            ENCODER_CH3_A_PIN         GPIO_Pin_9
#define            ENCODER_CH3_B_PIN         GPIO_Pin_9

#endif
