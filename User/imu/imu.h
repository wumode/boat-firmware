#ifndef IMU_H_
#define IMU_H_
#include <string.h>
#include <stdio.h>
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
//#include "delay.h"
//#include "IOI2C.h"
//#include "hw_config.h"
#include "JY901.h"
#include "sys.h"
//#include "DIO.h"

void CopeSerial2Data(uint8_t ucData);
void CopeSerial2Data_1(uint8_t ucData_1);
#endif

