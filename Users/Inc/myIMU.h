//
// Created by 86159 on 2025/1/18.
//

#ifndef STPROJECTFILES_MYIMU_H
#define STPROJECTFILES_MYIMU_H

#include "main.h"
#include "myGpio.h"
#include "myDma.h"
#include "mySpi.h"
#include "usb_device.h"
#include "myTIM.h"
#include "BMI088driver.h"

// 加速度计和陀螺仪定义
#define Accel_INT_Pin GPIO_PIN_2
#define Gryo_INT_Pin GPIO_PIN_3
#define AccelAndGryo_INT_GPIO_Port GPIOC
#define AccelAndGryo_INT_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

void IMU_Init(void);

#endif //STPROJECTFILES_MYIMU_H
