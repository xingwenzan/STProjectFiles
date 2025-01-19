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

/**
 * 机器狗腿部舵机与三八译码器输出端口编号对应
 * 输出端口 - 舵机位置（左右 - LR，前后 - FB，大小腿 - GS）
 * Y0 - LFG
 * Y1 - LFS
 * Y2 - RFG
 * Y3 - RFS
 * Y4 - LBG
 * Y5 - LBS
 * Y6 - RBG
 * Y7 - RBS
 */

#define MY_ROBOT_GPIO_Port GPIOC  // 机器人端口
// 控制三八译码器的引脚，A 为低位，C 为高位，低电平为 0，高电平为 1
// 输出从 Y0 到 Y7，依次变为低电平
#define MY_ROBOT_CHOOSE_PIN_A GPIO_PIN_9
#define MY_ROBOT_CHOOSE_PIN_B GPIO_PIN_8
#define MY_ROBOT_CHOOSE_PIN_C GPIO_PIN_7


// pwm 输出通道
#define MY_PWM_CHANNEL TIM_CHANNEL_1

extern uint8_t walk;

void Robot_Leg_Choose(uint8_t idx);
void Robot_Leg_PWM(uint16_t pwm);
void Robot_Init();  // 机器人初始化
void Robot_Leg_Do(uint8_t state);


#endif //STPROJECTFILES_MYROBOT_H
