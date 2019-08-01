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
	PwmSet(motor_pwm->right, 1);
	PwmSet(motor_pwm->left, 2);
	PwmSet(motor_pwm->lateral_push_right, 3);
	PwmSet(motor_pwm->lateral_push_left, 4);
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

u8 trace_pot_x;
u8 trace_pot_y;
float trace_error_ori; 
float trace_error_last;
float trace_error; 
u8 trace_stop_flag = 0;

void trace_control(void)
{
	MotorPwm motor_trace_pwm;
	trace_error_ori = 80 - trace_pot_x; 
  trace_error = 0.01*trace_error_ori + 0*(trace_error_ori-trace_error_last);
  trace_error_last = trace_error_ori;
	if(trace_stop_flag == 0)
  {
		velocity_data.velocity_angle = trace_error;
	  velocity_data.velocity_x = 1-0.2*fabs(trace_error);
			}
	else
	{
		 velocity_data.velocity_angle=0;
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
  if(control_power_data.host ==3)
	{
		Usart4_SendByte(2);
	}
	if(control_power_data.host ==1)
	{
	  Usart4_SendByte(0);
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


void control(void){
	uint16_t location_time = 0;
	uint16_t read_remote_channel_time = 0;
	u8 A;
	MotorPwm motor_pwm;
	motor_pwm.left = PWM_TIM_Pause;
	motor_pwm.right = PWM_TIM_Pause;
	motor_pwm.lateral_push_left = LATERAL_TIM_PAUSE;
	motor_pwm.lateral_push_right = LATERAL_TIM_PAUSE;
	MotorInit();
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
			//printf("c: %f\n", imu_data.angular_velocity_z);
			DT_Send_Imu(&imu_data);
		}
		if(gps_updated){
			gps_updated = 0;
			DT_Send_Gps(&gps_data);
		}
		if(velocity_updated){
			velocity_updated = 0;
			SpeedAnalyze(&velocity_data, &motor_pwm);
			LimitPwm(&motor_pwm);
			//printf("pwm: %d-%d\n", motor_pwm.right, motor_pwm.left);
			PwmApplicate(&motor_pwm);
		}
		
//		if(servo_pwm_updated){
//			servo_pwm_updated = 0;
//			ServoPwmSet(cradle_pwm.servo_up, 1);
//			ServoPwmSet(cradle_pwm.servo_down, 2);
//		}
    if(control_power_data.host ==2)
	  {
		 trace_control();
	  }
   if(control_power_data.host ==3)
	 {
		 velocity_data.velocity_angle=0;
		 velocity_data.velocity_x=0;
		 SpeedAnalyze(&velocity_data, &motor_pwm);
	    LimitPwm(&motor_pwm);
	//printf("pw_tracem: %;d-%d\n", motor_pwm.right, motor_pwm.left);
	    PwmApplicate(&motor_pwm);
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
		//USART_SendData(UART4,2);
		mode_choose_openmv();
		//TIM1->CCR1 = 6000;
		//A=GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_9);
	// printf("control host: %d\n",control_power_data.host);
	//printf("empower: %d\n", empower_data.empower);
	printf("%d",trace_pot_x);
	printf("%d\n",trace_stop_flag);
		location_time++;
		read_remote_channel_time++;
		while(TimingDelay!=0x00);
	}
}

