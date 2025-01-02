//
// Created by 86159 on 2025/1/2.
// 机器狗控制 - 版本 v2
//

#ifndef STPROJECTFILES_MYROBOT_H
#define STPROJECTFILES_MYROBOT_H

#include "main.h"
#include "myTIM.h"
#include "myPWMparameter.h"
#include "myGpio.h"

#define MY_ROBOT_GPIO_Port GPIOC  // 机器人端口
// 控制三八译码器的引脚，A 为低位，C 为高位，低电平为 0，高电平为 1
// 输出从 Y0 到 Y7，依次变为低电平
#define MY_ROBOT_CHOOSE_PIN_A GPIO_PIN_9
#define MY_ROBOT_CHOOSE_PIN_B GPIO_PIN_8
#define MY_ROBOT_CHOOSE_PIN_C GPIO_PIN_7

//#define MY_ROBOT_CHOOSE_PORT_AB GPIOE
//#define MY_ROBOT_CHOOSE_PIN_A GPIO_PIN_13
//#define MY_ROBOT_CHOOSE_PIN_B GPIO_PIN_9
//#define MY_ROBOT_CHOOSE_PORT_C GPIOA
//#define MY_ROBOT_CHOOSE_PIN_C GPIO_PIN_2
//
//#define MY_ROBOT_CHOOSE_AB_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()
//#define MY_ROBOT_CHOOSE_C_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
// pwm 输出通道
#define MY_PWM_CHANNEL TIM_CHANNEL_1

void Robot_Leg_Choose(uint8_t idx);
void Robot_Leg_PWM(uint16_t pwm);
void Robot_Init();  // 机器人初始化

#endif //STPROJECTFILES_MYROBOT_H
