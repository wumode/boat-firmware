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
#define CLI() __set_PRIMASK(1) //总中断关闭
#define SEI() __set_PRIMASK(0) //总中断开启

//Ex_NVIC_Config专用定义
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 
#define FTIR   1  //下降沿触发
#define RTIR   2  //上升沿触发

#define WHEEL_RADIOUS 					0.0325			//半径
#define HALF_SHAFT_LENGTH 				0.85			//半轴长
#define CPR 							1560			//每圈脉冲数
#define FREQUENCY						200				//主程序执行频率
#define INTERRUPTION_FREQUENCY			10000			//中断频率
#define MIN_DISTANCE					10.0			//最小距离
#define INITIAL_ATTITUDE				0.0				//初始姿态
#define TURNING_TIME					0.02			//转向时间
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
