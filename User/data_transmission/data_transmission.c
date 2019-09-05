#include "data_transmission.h"
u8 wait_for_translate = 1;
uint8_t tx_buffer_[128];
//uint8_t rx_buffer_[128];


void DT_Send_Data(u8 *dataToSend, u8 length)
{
	Usart5_SendData(dataToSend, length);
}

/*----------------------------------------------------------
+ 实现功能：发送速度信息
+ 调用参数：IMU_DATA
----------------------------------------------------------*/
void DT_Send_Imu(const ImuDataTrans* imu_data_trans)
{
    uint8_t data_length = sizeof(ImuDataTrans);
    tx_buffer_[0] = send_head_high_;
    tx_buffer_[1] = send_head_low_;
    tx_buffer_[2] = kIMU_FLAG;
    tx_buffer_[3] = sizeof(ImuDataTrans);
    memcpy(tx_buffer_+4, (void*)imu_data_trans, data_length);
    uint8_t sum = 0;
    for (int i = 0; i < data_length+4; i++) {
        sum += tx_buffer_[i];
    }
    tx_buffer_[data_length+4] = sum;
	DT_Send_Data(tx_buffer_, (uint8_t)(data_length+5));
}


void DT_Send_RemoteChannel(const RemoteChannelTrans* remote_channel_data_trans){
	uint8_t data_length = sizeof(RemoteChannelTrans);
    tx_buffer_[0] = send_head_high_;
    tx_buffer_[1] = send_head_low_;
    tx_buffer_[2] = kREMOTE_CHANNEL_FLAG;
    tx_buffer_[3] = sizeof(RemoteChannelTrans);
    memcpy(tx_buffer_+4, (void*)remote_channel_data_trans, data_length);
    uint8_t sum = 0;
    for (int i = 0; i < data_length+4; i++) {
        sum += tx_buffer_[i];
    }
    tx_buffer_[data_length+4] = sum;
	DT_Send_Data(tx_buffer_, (uint8_t)(data_length+5));
}

void DT_Send_Gps(const GpsDataTrans* gps_data_trans)
{
    uint8_t data_length = sizeof(GpsDataTrans);
    tx_buffer_[0] = send_head_high_;
    tx_buffer_[1] = send_head_low_;
    tx_buffer_[2] = kGPS_FLAG;
    tx_buffer_[3] = sizeof(GpsDataTrans);
    memcpy(tx_buffer_+4, (void*)gps_data_trans, data_length);
    uint8_t sum = 0;
    for (int i = 0; i < data_length+4; i++) {
        sum += tx_buffer_[i];
    }
    tx_buffer_[data_length+4] = sum;
    DT_Send_Data(tx_buffer_, (uint8_t)(data_length+5));
}
void DT_Send_Velocity(const VelocityDataTrans* velocity_data_trans)
{
    uint8_t data_length = sizeof(VelocityDataTrans);
    tx_buffer_[0] = send_head_high_;
    tx_buffer_[1] = send_head_low_;
    tx_buffer_[2] = kVELOCITY_FLAG;
    tx_buffer_[3] = sizeof(VelocityDataTrans);
    memcpy(tx_buffer_+4, (void*)velocity_data_trans, data_length);
    uint8_t sum = 0;
    for (int i = 0; i < data_length+4; i++) {
        sum += tx_buffer_[i];
    }
    tx_buffer_[data_length+4] = sum;
    DT_Send_Data(tx_buffer_, (uint8_t)(data_length+5));
}

void DT_Send_ControlPower(const ControlPowerTrans* control_power_data_trans) {
    uint8_t data_length = sizeof(ControlPowerTrans);
    tx_buffer_[0] = send_head_high_;
    tx_buffer_[1] = send_head_low_;
    tx_buffer_[2] = kCONTROL_POWER_FLAG;
    tx_buffer_[3] = sizeof(ControlPowerTrans);
    memcpy(tx_buffer_+4, (void*)control_power_data_trans, data_length);
    uint8_t sum = 0;
    for (int i = 0; i < data_length+4; i++) {
        sum += tx_buffer_[i];
    }
    tx_buffer_[data_length+4] = sum;
    DT_Send_Data(tx_buffer_, (uint8_t)(data_length+5));
}

void DT_Send_Locking(const LockingTrans* locking_data_trans){
	uint8_t data_length = sizeof(LockingTrans);
    tx_buffer_[0] = send_head_high_;
    tx_buffer_[1] = send_head_low_;
    tx_buffer_[2] = kLOCKING_FLAG;
    tx_buffer_[3] = sizeof(LockingTrans);
    memcpy(tx_buffer_+4, (void*)locking_data_trans, data_length);
    uint8_t sum = 0;
    for (int i = 0; i < data_length+4; i++) {
        sum += tx_buffer_[i];
    }
    tx_buffer_[data_length+4] = sum;
    DT_Send_Data(tx_buffer_, (uint8_t)(data_length+5));
}

void DT_Gps_Parse(u8* buffer, GpsDataTrans* gps_data_trans) {
    memcpy(gps_data_trans, buffer, sizeof(GpsDataTrans));
}

void DT_Imu_Parse(u8* buffer, ImuDataTrans* imu_data_trans) {
    memcpy(imu_data_trans, buffer, sizeof(ImuDataTrans));
    //std::cout<<imu_data_trans->roll<<std::endl;
}
void DT_Velocity_Parse(u8* buffer, VelocityDataTrans* velocity_data_trans) {
    memcpy(velocity_data_trans, buffer, sizeof(VelocityDataTrans));
	velocity_updated = 1;
}

void DT_ControlPower_Parse(u8* buffer, ControlPowerTrans* control_power_data_trans) {
    memcpy(control_power_data_trans, buffer, sizeof(ControlPowerTrans));
	//printf("control host: %d\n",control_power_data.host);
}

void DT_Empower_Parse(u8* buffer, EmpowerTrans* empower_trans) {
    memcpy(empower_trans, buffer, sizeof(EmpowerTrans));
}

void DT_Stop_Parse(u8* buffer, StopTrans* stop_trans) {
    memcpy(stop_trans, buffer, sizeof(StopTrans));
}


void DT_Mode_Parse(u8* buffer, ModeTrans* mode_trans) {
    memcpy(mode_trans, buffer, sizeof(ModeTrans));
}

void DT_Behavior_Parse(u8* buffer, BehaviorTrans* behavior_trans) {
    memcpy(behavior_trans, buffer, sizeof(BehaviorTrans));
}

void DT_BehaviorParams_Parse(u8* buffer, BehaviorParamsTrans* behavior_params_trans) {
    memcpy(behavior_params_trans, buffer, sizeof(BehaviorParamsTrans));
}

/*----------------------------------------------------------
+ 实现功能：数据分析
+ 调用参数：传入接受到的一个数据帧和长度
----------------------------------------------------------*/

void DT_Data_Receive_Anl(u8 *data_buf, u8 num)
{
	u8 sum = 0;
	/* 首先计算校验累加和 */
	for (u8 i = 0; i<(num - 1); i++)
		sum += *(data_buf + i);
	/* 判断校验累加和 若不同则舍弃*/
	if (!(sum == *(data_buf + num - 1)))       return;
	/* 判断帧头 */
	if (!(*(data_buf) == title1_received && *(data_buf + 1) == title2_received))       return;
	/* 判断功能字：*/
	//uint8_t flag = *(data_buf + 2);
	//printf("%d\n", flag);
	
	if (*(data_buf + 2) == 0X01)
	{

	}
	/* 判断功能字： */
	else if (*(data_buf + 2) == kIMU_FLAG)
	{
		DT_Imu_Parse(data_buf + 4, &imu_data);
	}
	else if (*(data_buf + 2) == kGPS_FLAG)
	{
		DT_Gps_Parse(data_buf + 4, &gps_data);
	}
	else if (*(data_buf + 2) == kVELOCITY_FLAG) {
		DT_Velocity_Parse(data_buf + 4, &velocity_data);
	}
	
	else if(*(data_buf + 2) == kEMPOWER_FLAG) {
		DT_Empower_Parse(data_buf + 4, &empower_data);
	}
	else if(*(data_buf + 2) == kSTOP_FLAG){
		DT_Stop_Parse(data_buf + 4, &stop_data);
	}
	else if(*(data_buf + 2) == kMODE_FLAG){
		DT_Mode_Parse(data_buf + 4, &mode_data);
	}
	else if(*(data_buf + 2) == kBEHAVIOR_FLAG){
		DT_Behavior_Parse(data_buf + 4, &behavior_data);
	}
	else if(*(data_buf + 2) == KBEHAVIOR_PARAMS_FLAG){
		DT_BehaviorParams_Parse(data_buf + 4, &behavior_params_data);
	}
}

/*----------------------------------------------------------
+ 实现功能：数据接收并保存
+ 调用参数：接收到的单字节数据
----------------------------------------------------------*/
void DT_Data_Receive_Prepare(u8 data)
{
	/* 局部静态变量：接收缓存 */
	static u8 RxBuffer[50];
	/* 数据长度 *//* 数据数组下标 */
	static u8 _data_len = 0, _data_cnt = 0;
	/* 接收状态 */
	static u8 state = 0;
	//printf("state: %d\n", state);
	/* 帧头1  一个数据帧中第一个数据并且判断是否与宏定义帧头1相等*/
	if (state == 0 && data == title1_received)
	{
		state = 1;
		RxBuffer[0] = data;
	}
	/* 帧头2 一个数据帧中第二个数据并且判断是否与宏定义帧头2相等*/
	else if (state == 1 && data == title2_received)
	{
		//printf("data: %d\n", data);
		//&& data == title2_received
		state = 2;
		RxBuffer[1] = data;
	}
	/* 功能字 */
	else if (state == 2 && data>0xf0)
	{
		state = 3;
		RxBuffer[2] = data;
	}
	/* 长度 */
	else if (state == 3 && data<50)
	{
		state = 4;
		RxBuffer[3] = data;
		_data_len = data;
		_data_cnt = 0;
	}
	/* 接收数据组*/
	else if (state == 4 && _data_len>0)
	{
		_data_len--;
		RxBuffer[4 + _data_cnt++] = data;
		if (_data_len == 0)
			state = 5;
	}
	/* 校验累加和 */
	else if (state == 5)
	{
		state = 0;
		RxBuffer[4 + _data_cnt] = data;
		DT_Data_Receive_Anl(RxBuffer, _data_cnt + 5);  //调用数据分析函数,总长比索引+1
	}
	/* 若有错误重新等待接收帧头 */
	else
	state = 0;
}
