#include "sys.h"

void WatchDog_Init()
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//ȥ��д����
	IWDG_SetPrescaler(IWDG_Prescaler_32);	//��Ƶ��32
	IWDG_SetReload(64);  //u16�����Ĵ���ֻ�е�11λ��Ч��Ϊ��װ��ֵ�����¼���
	//Tout=((4*2^prer)*rlr)/40 (ms).
	IWDG_Enable();//�������Ź�
	IWDG_ReloadCounter();		//ι��
}
