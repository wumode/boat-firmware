#include "imu.h"

struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus; 
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ       stcQ;

void CopeSerial2Data(uint8_t ucData)
{
	static uint8_t ucRxBuffer[256];
	static uint8_t ucRxCnt;	
	
	//LED_REVERSE();
	//USB_TxWrite(&ucData,1);
	ucRxBuffer[ucRxCnt++]=ucData;
	if (ucRxBuffer[0]!=0x55) 
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}
	else
	{
		switch(ucRxBuffer[1])
		{
			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	{
				memcpy(&stcAngle,&ucRxBuffer[2],8);
				imu_data.yaw = (float)stcAngle.Angle[2]/10430.3785;
				break;	
			}
			case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);break;
			case 0x55:	memcpy(&stcDStatus,&ucRxBuffer[2],8);break;
			case 0x56:	memcpy(&stcPress,&ucRxBuffer[2],8);break;
			case 0x57:	memcpy(&stcLonLat,&ucRxBuffer[2],8);break;
			case 0x58:	memcpy(&stcGPSV,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;
	}
}



void CopeSerial2Data_1(uint8_t ucData_1)
{
	static uint8_t ucRxBuffer_1[250];
	static uint8_t ucRxCnt_1;	
	ucRxBuffer_1[ucRxCnt_1++]=ucData_1;	
	if (ucRxBuffer_1[0]!=0x55) 
	{
		ucRxCnt_1=0;
		
		return;
	}
	if (ucRxCnt_1<11)
	{
		return;
	}
	else
	{
		switch(ucRxBuffer_1[1])
		{
			case 0x51:	{
				memcpy(&stcAcc,&ucRxBuffer_1[2],8);
				imu_data.linear_acceleration_x = (float)stcAcc.a[0]/32768*16;
				imu_data.linear_acceleration_y = (float)stcAcc.a[1]/32768*16;
				break;
			}
			case 0x52:{	
				memcpy(&stcGyro,&ucRxBuffer_1[2],8);
				imu_data.angular_velocity_z = (float)stcGyro.w[2]/32768*2000*PI/180;
				break;
			}
			case 0x53:	{
				memcpy(&stcAngle,&ucRxBuffer_1[2],8);
				imu_data.roll = (float)stcAngle.Angle[0]/32768*PI;
				imu_data.pitch = (float)stcAngle.Angle[1]/32768*PI;
				imu_data.yaw = (float)stcAngle.Angle[2]/32768*PI;
				break;
			}
		}
		imu_updated = 1;
		ucRxCnt_1=0;
	}
}



