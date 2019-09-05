/**
  ******************************************************************************
  * @file    main.c
  * @author  wumo <wumo1999@gmail.com>
  * @version V1.0
  * @date    2019-3-3
  * @brief   智能船比赛
  ******************************************************************************
  * @attention
  *
  * 平台:STM32F103
  *
  ******************************************************************************
  */
  

#include "sys.h"
#include "control.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */

float Velocity_KP=PID_P,Velocity_KI=PID_I, Velocity_KD=PID_D;
int Encoder[2];   
int Target[2];

uint8_t stop_laser;
uint8_t stop_motor;

ImuDataTrans imu_data;
GpsDataTrans gps_data;
VelocityDataTrans velocity_data;
//ControlPowerTrans control_power_data;
RemoteChannelTrans remote_channel_data;
EmpowerTrans empower_data;
LockingTrans locking_data;
StopTrans stop_data;
ModeTrans mode_data;
BehaviorTrans behavior_data;
BehaviorParamsTrans behavior_params_data;
CradlePwm cradle_pwm;

u16 TIM2_CH1_STATUS,TIM2_CH2_STATUS,TIM2_CH3_STATUS,TIM2_CH4_STATUS;
u16 TIM2_CH2_START_VALUE,TIM2_CH2_END_VALUE,TIM2_CH1_START_VALUE,TIM2_CH1_END_VALUE;
u16 TIM2_CH3_START_VALUE,TIM2_CH3_END_VALUE,TIM2_CH4_START_VALUE,TIM2_CH4_END_VALUE;


volatile uint8_t gps_updated;
volatile uint8_t imu_updated;
volatile uint8_t velocity_updated;
uint8_t servo_pwm_updated;

int gps_initialized;

//const float (*now_point)[2];
uint8_t laser_set;
uint8_t last_laser_set;

int main(void){
	//CLI();
	SEI();
	Init();
	control(); 
	return 0;
}
