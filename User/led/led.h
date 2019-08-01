#ifndef LED_H
#define LED_H
#define ON 1
#define OFF 0

#define LED_ON GPIO_ResetBits(GPIOE, GPIO_Pin_6)
#define LED_OFF GPIO_SetBits(GPIOE, GPIO_Pin_6)
#define digitalToggle(p,i) {p->ODR ^=i;}
#define LED_TOGGLE digitalToggle(GPIOE,GPIO_Pin_6)
#define LED(a) if(a) \
	GPIO_ResetBits(GPIOE, GPIO_Pin_6);\
else	\
	GPIO_SetBits(GPIOE, GPIO_Pin_6)

#define LED_1_ON GPIO_ResetBits(GPIOE, GPIO_Pin_5)
#define LED_1_OFF GPIO_SetBits(GPIOE, GPIO_Pin_5)
#define LED_1_TOGGLE digitalToggle(GPIOE,GPIO_Pin_5)
#define LED_1(a) if(a) \
	GPIO_ResetBits(GPIOE, GPIO_Pin_5);\
else	\
	GPIO_SetBits(GPIOE, GPIO_Pin_5)
void LED_GPIO_Config(void);
#endif
