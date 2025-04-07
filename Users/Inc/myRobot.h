//
// Created by 86159 on 2025/1/2.
// 机器狗控制 - 版本 v2
//
/**
 * 机器狗腿部舵机与三八译码器输出端口编号对应
 * 输出端口（X = G 或 S） - 舵机位置（左右 - LR，前后 - FB）
 * X0 - LF
 * X1 - RF
 * X2 - LB
 * X3 - RB
 */

#ifndef STPROJECTFILES_MYROBOT_H
#define STPROJECTFILES_MYROBOT_H

#include "main.h"
#include "myTIM.h"
#include "myPWMparameter.h"
#include "myGpio.h"

#define MY_ROBOT_GPIO_Port GPIOC  // 机器人端口
// 控制三八译码器的引脚，A 为低位，C 为高位，低电平为 0，高电平为 1
// 输出从 Y0 到 Y7，依次变为低电平
// 鉴于已有三八译码器，实际只需二四译码，C 取消不用
#define MY_ROBOT_CHOOSE_PIN_A GPIO_PIN_9
#define MY_ROBOT_CHOOSE_PIN_B GPIO_PIN_8

// pwm 输出通道：G - 大腿；S - 小腿
#define MY_PWM_CHANNEL_G TIM_CHANNEL_1
#define MY_PWM_CHANNEL_S TIM_CHANNEL_2

/**
 * walk 用于控制机器狗腿部动作\n
 * 各位的功能如下：（低位为 0 号，高位为 7 号）\n
 * 0、1 号：腿部选择
 * 2-7 号：控制该腿在摆线的状态（范围：0-49）
 */
extern uint16_t walk;
/**
 * 机器狗运动类型
 * 0 - 下蹲
 * 1 - 站立
 * 2 - 走路
 */
extern uint8_t walk_state;

void Robot_Leg_Choose(uint8_t idx);
void Robot_Leg_PWM(uint16_t pwmG,uint16_t pwmS);
void Robot_Init();  // 机器人初始化
void Robot_Leg_Do(fp32 *pitch, fp32 *roll);
void GetPitchAndRoll(fp32 gyro[3], fp32 accel[3], fp32 *pitch, fp32 *roll);

#endif //STPROJECTFILES_MYROBOT_H
