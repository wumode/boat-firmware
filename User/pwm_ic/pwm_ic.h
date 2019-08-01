#ifndef PWM_IC_H
#define PWM_IC_H
#include "sys.h"
typedef struct
{
	  u16 Ccr1;         //??CCR?????
	  u16 Ccr2;
	  u16 Ccr3;
	  u16 Ccr4;
	  u16 Ic1_Over;     //??ARR????
	  u16 Ic2_Over;
      u16 Ic3_Over;
	  u16 Ic4_Over;
	  u16 Ic1_Fre;      //?????
	  u16 Ic2_Fre;
	  u16 Ic3_Fre;
	  u16 Ic4_Fre;
	
}TIM_ICS;   //TIM3?????
 
//TIM?????????,1:?? 0:??
#define  TIM_ICCH1        1    
#define  TIM_ICCH2        1
#define  TIM_ICCH3        1
#define  TIM_ICCH4        1
 
//??????:72000000/(120*60000)=10Hz
#define  TIM_ICARR        (60000-1)          //?????????
#define  TIM_ICPSC        0                  //????  
#define  TIM_ICFIT        0x0f               //?????????  
#define  TIM_OverF        (120-1)            //??ARR????
 
#define  TIM_ICSR         (u16 *)&TIM3->SR   //??????SR?????
#define  TIM_ICCCR        (u16 *)&TIM3->CCR1 //??????CCR?????
void TIM3_PWMICInit(void);
#endif