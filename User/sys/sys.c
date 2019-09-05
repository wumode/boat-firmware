#include "sys.h"
#include "usart.h"
#include "led.h"
#include "motor.h"
#include "laser.h"
#include "exti.h"
#include "input_capture.h"

extern void WatchDog_Init(void);

void Init(void){
	LED_GPIO_Config();
	USART1_Config(460800);
	USART2_Config(921600);
	USART3_Config(115200);
	USART4_Config(921600);
	USART5_Config(460800);
	imu_updated = 0;
	gps_updated = 0;
	velocity_updated = 1;
	servo_pwm_updated = 0;
	
	velocity_data.velocity_x = 0.0;
	velocity_data.velocity_angle = 0.0;
	
	imu_data.angular_velocity_z = 0.0;
	imu_data.linear_acceleration_x = 0.0;
	imu_data.linear_acceleration_y = 0.0;
	imu_data.pitch = 0.0;
	imu_data.roll = 0.0;
	imu_data.pitch = 0.0;
	
	gps_data.latitude = 0.0;
	gps_data.longitude = 0.0;
	gps_data.speed = 0.0;
	
	SysTick_Init(); 
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	PwmInit();
	Servo_Pwm_Init();
	Laser_Init();
	TIM2_Capture_Init(CAPTURE_PERIOD, CAPTURE_PRESCALER);
	
	//Encoder_Init();
	//EXTI_PB14_Config();
	//OLED_Init(); 
	gps_initialized = 0;
	laser_set = 0;
	last_laser_set = laser_set;
	locking_data.locking = 0;
	stop_laser = 0;
	stop_motor = 0;
	stop_data.stop = 0;
	mode_data.mode = remote_mode;
	behavior_params_data.laser_intensity = 10;
	//LED(OFF);
	
	//line_length = 0;
	//gps_info.fix_quality = 0;
	//attitude_angle = 0.0;
	//now_point_num = 0;
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);
	//while(!gps_updated);
	//control_power_data.host = 2;
	WatchDog_Init();
}

