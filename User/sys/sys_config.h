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

//GPS??
typedef struct GpsDataTrans {
	volatile float latitude;
	volatile float longitude;
	volatile float speed;
}GpsDataTrans;
//GPS???

typedef struct VelocityDataTrans {
	volatile float velocity_x;
	volatile float velocity_angle;
}VelocityDataTrans;

typedef struct ControlPowerTrans {
	u8 host;
}ControlPowerTrans;

typedef struct RemoteChannelTrans{
    volatile uint16_t channel_1;
    volatile uint16_t channel_2;
    volatile uint16_t channel_3;
    volatile uint16_t channel_4;
}RemoteChannelTrans;

typedef struct EmpowerTrans{
    volatile uint8_t empower;
}EmpowerTrans;

typedef struct LockingTrans{
    uint8_t locking;
}LockingTrans;

typedef struct StopTrans{
    volatile uint8_t stop;
}StopTrans;

typedef struct ModeTrans{
        uint8_t mode;
    }ModeTrans;

    typedef struct BehaviorTrans{
        uint8_t behavior;
    }BehaviorTrans;
typedef struct BehaviorParamsTrans{
        uint8_t laser_intensity;
    }BehaviorParamsTrans;
typedef enum SerialDataType{
        kIMU_FLAG = 0xf1,
        kGPS_FLAG = 0xf2,
        kVELOCITY_FLAG = 0xf3,
        kCONTROL_POWER_FLAG = 0xf4,
        kREMOTE_CHANNEL_FLAG = 0xf5,
        kEMPOWER_FLAG = 0xf6,
        kLOCKING_FLAG = 0xf7,
        kINITIALIZED_FLAG = 0xf8,
        kSTOP_FLAG = 0xf9,
        kMODE_FLAG = 0xfa,
        kBEHAVIOR_FLAG = 0xfb,
		KBEHAVIOR_PARAMS_FLAG = 0xfc
    }SerialDataType;

typedef enum BoatMode{
        remote_mode = 1,
        navigation_mode,
        track_mode,
        attack_mode,
        kDynamicPositioningMode
    }BoatMode;

	typedef enum Behavior{
        kNoBehavior = 0,
        kAttack = 1
    }Behavior;

typedef struct CradlePwm{
	volatile uint8_t servo_up;   
	volatile uint8_t servo_down; 
}CradlePwm;

extern CradlePwm cradle_pwm;
extern ImuDataTrans imu_data;
extern GpsDataTrans gps_data;
extern VelocityDataTrans velocity_data;
//extern ControlPowerTrans control_power_data;
extern RemoteChannelTrans remote_channel_data;
extern EmpowerTrans empower_data;
extern LockingTrans locking_data;
extern StopTrans stop_data;
extern ModeTrans mode_data;
extern BehaviorTrans behavior_data;
extern BehaviorParamsTrans behavior_params_data;

extern volatile uint8_t gps_updated;
extern volatile uint8_t imu_updated;
extern volatile uint8_t velocity_updated;
extern uint8_t servo_pwm_updated;

extern uint8_t laser_set;
extern uint8_t last_laser_set;
extern uint8_t stop_motor;
extern uint8_t stop_laser;
//extern u32 CHANNEL_HIGHOUTPUT[4];
#endif
