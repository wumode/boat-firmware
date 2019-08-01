#ifndef DATA_TRANSMISSION_H
#include <string.h>
#include "stm32f10x.h"
#include "stdio.h"
#include "sys_config.h"
#define DATA_TRANSMISSION_H

extern void Usart5_SendData(uint8_t *data, u16 length);

void DT_Send_Data(u8 *dataToSend, u8 length);

void DT_Send_Imu(const ImuDataTrans* imu_data_trans);

void DT_Send_Gps(const GpsDataTrans* gps_data_trans);

void DT_Send_RemoteChannel(const RemoteChannelTrans* remote_channel_data_trans);

void DT_Send_Velocity(const VelocityDataTrans* velocity_data_trans);

void DT_Send_ControlPower(const ControlPowerTrans* control_power_data_trans);

void DT_Imu_Parse(u8* buffer, ImuDataTrans* imu_data_trans);

void DT_Gps_Parse(u8* buffer, GpsDataTrans* gps_data_trans);

void DT_Velocity_Parse(u8* buffer, VelocityDataTrans* velocity_data_trans);

void DT_ControlPower_Parse(u8* buffer, ControlPowerTrans* control_power_data_trans);

void DT_Data_Receive_Anl(u8 *data_buf, u8 num);

void DT_Data_Receive_Prepare(u8 data);

#endif
