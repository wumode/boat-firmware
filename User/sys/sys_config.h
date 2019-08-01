#ifndef CONFIG_H
#define CONFIG_H
#include "stm32f10x.h"

typedef struct MotorPwm{
	int right;
	int left;
	int lateral_push_right;
	int lateral_push_left;
}MotorPwm;
typedef char Flag;


/* ???? ????*/
#define send_head_high_ 0xAA
#define send_head_low_ 0xAF
#define title1_received 0xAA
#define title2_received 0xAF

void DT_Data_Receive_Prepare(u8 data);

//IMU??
typedef struct ImuDataTrans{
	volatile float roll;
	volatile float pitch;
	volatile float yaw;
	volatile float linear_acceleration_x;
	volatile float linear_acceleration_y;
	volatile float angular_velocity_z;
}ImuDataTrans;
//IMU???
#define IMU_FLAG 0xf1

//GPS??
typedef struct GpsDataTrans {
	volatile float latitude;
	volatile float longitude;
	volatile float speed;
}GpsDataTrans;
//GPS???
#define GPS_FLAG 0xf2

typedef struct VelocityDataTrans {
	volatile float velocity_x;
	volatile float velocity_angle;
}VelocityDataTrans;
#define VELOCITY_FLAG 0xf3

//?????
typedef struct ControlPowerTrans {
	u8 host;
}ControlPowerTrans;
//??????
#define CONTROL_POWER_FLAG 0xf4

typedef struct RemoteChannelTrans{
    volatile uint16_t channel_1;
    volatile uint16_t channel_2;
    volatile uint16_t channel_3;
    volatile uint16_t channel_4;
}RemoteChannelTrans;
#define REMOTE_CHANNEL_FLAG 0xf5

typedef struct EmpowerTrans{
    uint8_t empower;
}EmpowerTrans;
#define EMPOWER_FLAG 0xf6

typedef struct CradlePwm{
	volatile uint8_t servo_up;   
	volatile uint8_t servo_down; 
}CradlePwm;

extern CradlePwm cradle_pwm;
extern ImuDataTrans imu_data;
extern GpsDataTrans gps_data;
extern VelocityDataTrans velocity_data;
extern ControlPowerTrans control_power_data;
extern RemoteChannelTrans remote_channel_data;
extern EmpowerTrans empower_data;

extern volatile uint8_t gps_updated;
extern volatile uint8_t imu_updated;
extern volatile uint8_t velocity_updated;
extern uint8_t servo_pwm_updated;
//extern u32 CHANNEL_HIGHOUTPUT[4];
#endif
