//
// Created by 86159 on 2024/5/13.
//

#include "myRobot.h"

// 机器人初始化
void Robot_Init() {
    MX_TIM_Advance_Init();   // 初始化高级定时器 - 用于PWM
    HAL_TIM_PWM_Start(&htim_advance, LEG_LARGE_RIGHT);    /* 开启 PWM 通道 1 */
    HAL_TIM_PWM_Start(&htim_advance, LEG_LARGE_LEFT);    /* 开启 PWM 通道 2 */
    HAL_TIM_PWM_Start(&htim_advance, LEF_SMALL_RIGHT);    /* 开启 PWM 通道 3 */
    HAL_TIM_PWM_Start(&htim_advance, LEF_SMALL_LEFT);    /* 开启 PWM 通道 4 */
}

// 机器人站立
void Robot_Stand() {
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_RIGHT, MY_PWM_STATE_S01);
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_LEFT, MY_PWM_STATE_S11);
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_RIGHT, MY_PWM_STATE_S01);
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_LEFT, MY_PWM_STATE_S11);
}

// 运动前的准备
// 另：为了方便记忆与书写，机器人的左前+右后两条腿简写为`左腿`（记为 L），右前+左后两条腿简写为`右腿`（记为 R）
// 右腿状态 0
void Leg_R_State0() {
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_RIGHT, MY_PWM_STATE_S01);
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_RIGHT, MY_PWM_STATE_S01);
}

// 左腿状态 0
void Leg_L_State0() {
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_LEFT, MY_PWM_STATE_S11);
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_LEFT, MY_PWM_STATE_S11);
}

// 右腿状态 1
void Leg_R_State1() {
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_RIGHT, MY_PWM_STATE_S11);
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_RIGHT, MY_PWM_STATE_S11);
}

// 左腿状态 1
void Leg_L_State1() {
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_LEFT, MY_PWM_STATE_S01);
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_LEFT, MY_PWM_STATE_S01);
}

// 机器人运动
void Robot_Move() {
    Leg_L_State0();Leg_R_State1();
    HAL_Delay(300);
    Leg_R_State0();Leg_L_State1();
    HAL_Delay(300);
    Leg_L_State0();Leg_R_State1();
    HAL_Delay(300);

    Leg_R_State0();Leg_L_State1();
    HAL_Delay(300);
    Leg_L_State0();Leg_R_State1();
    HAL_Delay(300);

    Leg_R_State0();Leg_L_State1();
    HAL_Delay(300);
    Leg_L_State0();Leg_R_State1();
    HAL_Delay(300);
}