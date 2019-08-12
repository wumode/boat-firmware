#include "control.h"
#include "math.h"

static __IO uint32_t TimingDelay;

void SysTick_Init(void){
	if(SysTick_Config(SystemCoreClock / INTERRUPTION_FREQUENCY))
	{
		while(1);
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


void Delay_us(__IO uint32_t nTime){
	TimingDelay = nTime / (10000000/INTERRUPTION_FREQUENCY);
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	while(TimingDelay!=0);
}

void TimingDelay_Decrement(void){
	if(TimingDelay != 0x00){
		TimingDelay--;
	}
}

void SpeedAnalyze(const VelocityDataTrans* velocity_data ,MotorPwm* motor_pwm){
	motor_pwm->right = PWM_TIM_Pause + (int)(velocity_data->velocity_x * PROPULSION_COFFICENT);
	motor_pwm->left = PWM_TIM_Pause + (int)(velocity_data->velocity_x * PROPULSION_COFFICENT);
	//motor_pwm->left = PWM_TIM_Pause;
	int v_a = velocity_data->velocity_angle * TURNING_PROPULSION_COFFICENT;
	if(v_a>0){
		motor_pwm->lateral_push_right = LATERAL_TIM_PAUSE + v_a;
		motor_pwm->lateral_push_left = LATERAL_TIM_PAUSE;
		
	}
	else {
		motor_pwm->lateral_push_right = LATERAL_TIM_PAUSE ;
		motor_pwm->lateral_push_left = LATERAL_TIM_PAUSE - v_a;
		
	}
}

void PwmApplicate(const MotorPwm* motor_pwm){
	if(stop_motor){
		PwmSet(PWM_TIM_Pause, 1);
		PwmSet(PWM_TIM_Pause, 2);
		PwmSet(LATERAL_TIM_PAUSE, 3);
		PwmSet(LATERAL_TIM_PAUSE, 4);
	}
	else{
		PwmSet(motor_pwm->right, 1);
		PwmSet(motor_pwm->left, 2);
		PwmSet(motor_pwm->lateral_push_right, 3);
		PwmSet(motor_pwm->lateral_push_left, 4);
	}
}

void LimitPwm(MotorPwm* motor_pwm){
	if(motor_pwm->right>UPPER_LIMIT){
		motor_pwm->right = UPPER_LIMIT;
	}
	else if(motor_pwm->right< LOWER_LIMIT){
		motor_pwm->right = LOWER_LIMIT;
	}
	if(motor_pwm->left>UPPER_LIMIT){
		motor_pwm->left = UPPER_LIMIT;
	}
	else if(motor_pwm->left< LOWER_LIMIT){
		motor_pwm->left = LOWER_LIMIT;
	}
	if(motor_pwm->lateral_push_left>UPPER_LIMIT){
		motor_pwm->lateral_push_left = UPPER_LIMIT;
	}
	else if(motor_pwm->lateral_push_left< LOWER_LIMIT){
		motor_pwm->lateral_push_left = LOWER_LIMIT;
	}
	if(motor_pwm->lateral_push_right>UPPER_LIMIT){
		motor_pwm->lateral_push_right = UPPER_LIMIT;
	}
	else if(motor_pwm->lateral_push_right< LOWER_LIMIT){
		motor_pwm->lateral_push_right = LOWER_LIMIT;
	}
}

int Incremental_PI_0 (int Encoder,int Target)
{ 	
	static int Bias,Pwm, Last_bias, Last_last_bias;
	Bias = Target - Encoder;      
	Pwm += Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias + Velocity_KD*(Bias - 2*Last_bias + Last_last_bias); 
	Last_last_bias = Last_bias;
	Last_bias = Bias;	                   
	return Pwm;                        
}

int Incremental_PI_1 (int Encoder,int Target)
{ 	
	static int Bias,Pwm, Last_bias, Last_last_bias;

	Bias = Target - Encoder;      
	Pwm += Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias + Velocity_KD*(Bias - 2*Last_bias + Last_last_bias); 
	Last_last_bias = Last_bias;
	Last_bias = Bias;	                   
	return Pwm;                        
}


void Remote(const RemoteChannelTrans* rm_trans, MotorPwm* m_p ){
	int v_x = rm_trans->channel_1 - 1500;
	int v_a = rm_trans->channel_2 - 1500;
	m_p->right = PWM_TIM_Pause + (v_x);
	m_p->left = PWM_TIM_Pause + (v_x);
	if(v_a>0){
		m_p->lateral_push_right = LATERAL_TIM_PAUSE + v_a;
		m_p->lateral_push_left = LATERAL_TIM_PAUSE;
		
	}
	else {
		m_p->lateral_push_right = LATERAL_TIM_PAUSE ;
		m_p->lateral_push_left = LATERAL_TIM_PAUSE - v_a;
		
	}
}

u8 trace_pot_x = 80;
u8 trace_pot_y = 60;
float trace_error_ori; 
float trace_error_last;
float trace_error; 
u8 trace_stop_flag = 1;

void trace_control(void)
{
	MotorPwm motor_trace_pwm;
	trace_error_ori = 80 - trace_pot_x; 
	trace_error = 0.015*trace_error_ori + 0*(trace_error_ori-trace_error_last);
	if(trace_error>1.5){
		trace_error = 1.5;
	}
	else if(trace_error<-1.5){
		trace_error = -1.5;
	}
	trace_error_last = trace_error_ori;
	velocity_data.velocity_angle = trace_error;
	if(trace_stop_flag == 0)
	{
		velocity_data.velocity_x = 0.6;
	}
	else
	{
		//velocity_data.velocity_angle = 0;
		velocity_data.velocity_x=0;
	}
	SpeedAnalyze(&velocity_data, &motor_trace_pwm);
	LimitPwm(&motor_trace_pwm);
	//printf("pw_tracem: %;d-%d\n", motor_pwm.right, motor_pwm.left);
	PwmApplicate(&motor_trace_pwm);

}
void mode_choose_openmv(void)
{

  if(control_power_data.host ==2)
	{
		Usart4_SendByte(3);
	}
  else if(control_power_data.host ==3)
	{
		Usart4_SendByte(2);
	}
	else if(control_power_data.host ==1)
	{
	  Usart4_SendByte(1);
	}
}

void MotorInit(){
	//int num = 0;
	int num1 = 0;
	MotorPwm motor_pwm;
	motor_pwm.lateral_push_left = 1000;
	motor_pwm.lateral_push_right = 1000;
	PwmSet(motor_pwm.lateral_push_right, 3);
	PwmSet(motor_pwm.lateral_push_left, 4);
	while(num1 <= 500){
		IWDG_ReloadCounter();
		TimingDelay = INTERRUPTION_FREQUENCY/FREQUENCY;
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
		num1++;
		while(TimingDelay!=0x00);
	}
//	motor_pwm.lateral_push_left = 2000;
//	motor_pwm.lateral_push_right = 2000;
//	PwmSet(motor_pwm.lateral_push_right, 3);
//	PwmSet(motor_pwm.lateral_push_left, 4);
//	num1 = 0;
//	while(num1 <= 50){
//		IWDG_ReloadCounter();
//		TimingDelay = INTERRUPTION_FREQUENCY/FREQUENCY;
//		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
//		num1++;
//		while(TimingDelay!=0x00);
//	}

}


void LaserInit(void){
	int num = 0;
	uint8_t s = 0;
	while(num <= 150){
		IWDG_ReloadCounter();
		TimingDelay = INTERRUPTION_FREQUENCY/FREQUENCY;
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
		num++;
		if(num%3 == 0){
			if(s){
				s = 0;
			}
			else{
				s = 1;
			}
			LaserControl(s, num*12);
		}
		while(TimingDelay!=0x00);
	}
	LaserControl(0, num*10);
}

void control(void){
	uint16_t location_time = 0;
	uint16_t read_remote_channel_time = 0;
//u8 A;
	MotorPwm motor_pwm;
	motor_pwm.left = PWM_TIM_Pause;
	motor_pwm.right = PWM_TIM_Pause;
	motor_pwm.lateral_push_left = LATERAL_TIM_PAUSE;
	motor_pwm.lateral_push_right = LATERAL_TIM_PAUSE;
	MotorInit();
	int j = 0;
	for(j=0;j<3;j++){
			LaserInit();
	}
	while(1){
		IWDG_ReloadCounter();		//Î¹¹·
		TimingDelay = INTERRUPTION_FREQUENCY/FREQUENCY;
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
		if(location_time == FREQUENCY/LOCATION_FREQUENCY){
			location_time = 0;
			LED_1_TOGGLE;
			LED_TOGGLE;
		}
		if(read_remote_channel_time == FREQUENCY/READ_REMOTE_CHANNEL_FREQUENCY){
			read_remote_channel_time = 0;
			TIM2_4channel_process(CAPTURE_PERIOD, CAPTURE_PRESCALER);
			DT_Send_RemoteChannel(&remote_channel_data);
		}
		if(imu_updated){
			imu_updated = 0;
			//printf("f: %f\n", imu_data.angular_velocity_z);
			DT_Send_Imu(&imu_data);
		}
		if(gps_updated){
			gps_updated = 0;
			DT_Send_Gps(&gps_data);
		}
		//printf("aa\n");
//		if(servo_pwm_updated){
//			servo_pwm_updated = 0;
//			ServoPwmSet(cradle_pwm.servo_up, 1);
//			ServoPwmSet(cradle_pwm.servo_down, 2);
//		}
		if(control_power_data.host == 1)
		{
			laser_set=0;
			if(velocity_updated){
				velocity_updated = 0;
				SpeedAnalyze(&velocity_data, &motor_pwm);
				LimitPwm(&motor_pwm);
				PwmApplicate(&motor_pwm);
			}
		}
		if(control_power_data.host == 2)
		{
			trace_control();
			laser_set=0;
		}
		if(control_power_data.host == 3)
		{
//			velocity_data.velocity_angle=0;
//			velocity_data.velocity_x=0;
			SpeedAnalyze(&velocity_data, &motor_pwm);
			LimitPwm(&motor_pwm);
			//printf("pw_tracem: %;d-%d\n", motor_pwm.right, motor_pwm.left);
			PwmApplicate(&motor_pwm);
		}
		 
		if(laser_set!=last_laser_set){
			if(laser_set){
				locking_data.locking = 1;
			}
			else{
				locking_data.locking = 0;
			}
			last_laser_set = laser_set;
			DT_Send_Locking(&locking_data);
		 }
		if(stop_data.stop){
			stop_laser = 1;
			stop_motor = 1;
		}
		else{
			stop_laser = 0;
			stop_motor = 0;
		}
		//ServoPwmSet(1500, 1);
		//printf("channel: %d-%d\n", remote_channel_data.channel_1, remote_channel_data.channel_2);
		//printf("%f-%f\n", velocity_data.velocity_x, velocity_data.velocity_angle);
			
		//PwmSet(&motor_pwm);
		//Remote(&remote_channel_data, &motor_pwm);
		//LimitPwm(&motor_pwm);
		//motor_pwm.lateral_push_left = 1100;
		//motor_pwm.lateral_push_right = 1100;
		//printf("lateral: %d-%d\n", motor_pwm.lateral_push_right, motor_pwm.lateral_push_left);
		//printf("motor: %d-%d\n", motor_pwm.right, motor_pwm.left);
		//PwmApplicate(&motor_pwm);
		//LaserSetPwm(6000);
		Laser_control();
		mode_choose_openmv();
		//TIM1->CCR1 = 6000;
		//A=GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_9);
		printf("main control host: %d\n",control_power_data.host);
		//printf("empower: %d\n", empower_data.empower);
		//printf("trace_pot_x: %d ",trace_pot_x);
		//printf("trace_stop_flag: %d\n",trace_stop_flag);
		location_time++;
		read_remote_channel_time++;
		while(TimingDelay!=0x00);
	}
}

