#ifndef SYS_H
#define SYS_H
#include "stm32f10x.h"
#include "system_stm32f10x.h"
#include "core_cm3.h"

#include "sys_tick.h"

#include "stdlib.h"


#include <math.h>
#include <string.h>
#include "sys_config.h"
#define CLI() __set_PRIMASK(1) //���жϹر�
#define SEI() __set_PRIMASK(0) //���жϿ���

//Ex_NVIC_Configר�ö���
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 
#define FTIR   1  //�½��ش���
#define RTIR   2  //�����ش���

#define WHEEL_RADIOUS 					0.0325			//�뾶
#define HALF_SHAFT_LENGTH 				0.85			//���᳤
#define CPR 							1560			//ÿȦ������
#define FREQUENCY						200				//������ִ��Ƶ��
#define INTERRUPTION_FREQUENCY			10000			//�ж�Ƶ��
#define MIN_DISTANCE					10.0			//��С����
#define INITIAL_ATTITUDE				0.0				//��ʼ��̬
#define TURNING_TIME					0.02			//ת��ʱ��
#define LOCATION_FREQUENCY				20			
#define READ_REMOTE_CHANNEL_FREQUENCY	15
#define PI 								3.1415926535

#define PID_P 40.0
#define PID_I 1.0
#define PID_D 0.05

#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	

#define SERIAL_DATA_LENGTH              36
#define SERIAL_DATA_FLAG                0x05
#define VELOCITY_DATA_FLAG              0xf9
#define VELOCITY_DATA_LENGTH            12

#define UPPER_LIMIT				2000
#define LOWER_LIMIT				1000
#define PROPULSION_COFFICENT 	166
#define TURNING_PROPULSION_COFFICENT 	333

extern float Velocity_KP,Velocity_KI, Velocity_KD;	
extern int Encoder[2];
extern int Target[2];
extern char stop_motor;

//extern SerialDataInfo serial_data_info;
extern const float (*now_point)[2];
extern const float KeyPoints [][2];
extern int gps_initialized;

void Init(void);

#endif
