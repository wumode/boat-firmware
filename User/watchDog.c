#include "sys.h"

void WatchDog_Init()
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//去除写保护
	IWDG_SetPrescaler(IWDG_Prescaler_32);	//分频数32
	IWDG_SetReload(64);  //u16数但寄存器只有低11位有效，为重装载值，向下计数
	//Tout=((4*2^prer)*rlr)/40 (ms).
	IWDG_Enable();//启动看门狗
	IWDG_ReloadCounter();		//喂狗
}
