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
 * 备注：各端口的对应在流水线上实际上存在未知原因的异常偏移（例如我选中 X0 时，实际上是由 X1 输出结果），这是经过调整后的结果
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
//#define MY_ROBOT_CHOOSE_PIN_C GPIO_PIN_7


// pwm 输出通道：G - 大腿；S - 小腿
#define MY_PWM_CHANNEL_G TIM_CHANNEL_1
#define MY_PWM_CHANNEL_S TIM_CHANNEL_2

/**
 * walk 用于控制机器狗腿部动作\n
 * 当前有用位为低四位，功能如下：（低位为 0 号，高位为 7 号）\n
 * 2、3 号：选定当前腿，00 - 11 依次为左前、右前、左后、右后\n
 * 1 号：0 静止（站立、下蹲）；1 运动/走路\n
 * 0 号：（1 号为 0 时）0 下蹲，1 站立；（1 号为 0 时）走路时的两种状态\n
 * 其余位：暂时无用，设置为 0
 */
extern uint8_t walk;

void Robot_Leg_Choose(uint8_t idx);
void Robot_Leg_PWM(uint16_t pwmG,uint16_t pwmS);
void Robot_Init();  // 机器人初始化
void Robot_Leg_Do();


#endif //STPROJECTFILES_MYROBOT_H
