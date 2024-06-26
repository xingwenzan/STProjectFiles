//
// Created by 86159 on 2024/5/13.
//

#ifndef STPROJECTFILES_MYROBOT_H
#define STPROJECTFILES_MYROBOT_H

#include "main.h"
#include "myTIM.h"

/**机器人各腿对应通道
 * 1 -> 右前 & 左后大腿 -> 右大腿
 * 2 -> 左前 & 右后大腿 -> 左大腿
 * 3 -> 右前 & 左后小腿 -> 右小腿
 * 4 -> 左前 & 右后小腿 -> 左小腿
 */
#define LEG_LARGE_RIGHT TIM_CHANNEL_1
#define LEG_LARGE_LEFT TIM_CHANNEL_2
#define LEF_SMALL_RIGHT TIM_CHANNEL_3
#define LEF_SMALL_LEFT TIM_CHANNEL_4

// 启停标志，代表是否运动，1 为允许运动，0 为拒绝（注意：作为 extern 变量，它在整个项目第一次使用前必须正确赋值）
extern uint8_t walk;

void Robot_Init();
void Robot_Stand();
void Robot_Move();
void Robot_State_Choose(uint8_t state);
void Robot_Control();

#endif //STPROJECTFILES_MYROBOT_H
