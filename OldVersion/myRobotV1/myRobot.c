//
// Created by 86159 on 2024/5/13.
//

#include "myRobot.h"

// 要么前面加上 extern，要么就不要在这里定义，因为它在 main 和本文件函数都定义会冲突，且在 main 中更早被使用
//uint8_t walk;

// 运动前的准备
// 另：为了方便记忆与书写，机器人的左前+右后两条腿简写为`左腿`（记为 L），右前+左后两条腿简写为`右腿`（记为 R）
// 右腿状态 0
void Leg_R_State0() {
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_RIGHT, MY_PWM_STATE_M01);
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_RIGHT, MY_PWM_STATE_S01);
}

// 右腿状态 1
void Leg_R_State1() {
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_RIGHT, MY_PWM_STATE_M11);
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_RIGHT, MY_PWM_STATE_S11);
}

// 右腿状态 2
void Leg_R_State2() {
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_RIGHT, MY_PWM_STATE_M11);
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_RIGHT, MY_PWM_STATE_S01);
}

// 右腿状态 3
void Leg_R_State3() {
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_RIGHT, MY_PWM_STATE_M01);
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_RIGHT, MY_PWM_STATE_S11);
}

// 左腿状态 0
void Leg_L_State0() {
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_LEFT, MY_PWM_STATE_M11);
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_LEFT, MY_PWM_STATE_S11);
}

// 左腿状态 1
void Leg_L_State1() {
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_LEFT, MY_PWM_STATE_M01);
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_LEFT, MY_PWM_STATE_S01);
}

// 左腿状态 2
void Leg_L_State2() {
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_LEFT, MY_PWM_STATE_M01);
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_LEFT, MY_PWM_STATE_S11);
}

// 左腿状态 3
void Leg_L_State3() {
            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_LEFT, MY_PWM_STATE_M11);
            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_LEFT, MY_PWM_STATE_S01);
}

// 机器人初始化
void Robot_Init() {
    MX_TIM_Advance_Init();   // 初始化高级定时器 - 用于PWM
    HAL_TIM_PWM_Start(&htim_advance, LEG_LARGE_RIGHT);    /* 开启 PWM 通道 1 */
    HAL_TIM_PWM_Start(&htim_advance, LEG_LARGE_LEFT);    /* 开启 PWM 通道 2 */
    HAL_TIM_PWM_Start(&htim_advance, LEF_SMALL_RIGHT);    /* 开启 PWM 通道 5 */
    HAL_TIM_PWM_Start(&htim_advance, LEF_SMALL_LEFT);    /* 开启 PWM 通道 4 */
}

// 机器人站立
void Robot_Stand() {
    Leg_R_State0();Leg_L_State0();
//            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_RIGHT, MY_PWM_STATE_S01);
//            __HAL_TIM_SetCompare(&htim_advance, LEG_LARGE_LEFT, MY_PWM_STATE_S11);
//            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_RIGHT, MY_PWM_STATE_M01);
//            __HAL_TIM_SetCompare(&htim_advance, LEF_SMALL_LEFT, MY_PWM_STATE_M11);
}

// 机器人运动
void Robot_Move() {
    Leg_R_State0();HAL_Delay(500);
    Leg_L_State1();HAL_Delay(500);
    Leg_L_State2();HAL_Delay(500);
    Leg_R_State1();HAL_Delay(500);
    Leg_R_State2();HAL_Delay(500);
    Leg_L_State3();HAL_Delay(500);
    Leg_L_State0();HAL_Delay(500);
    Leg_R_State3();HAL_Delay(500);
}

// 机器人运动 - 通过输入状态编号改变足部状态实现运动
void Robot_State_Choose(uint8_t state){
    switch (state) {
        case 0:Leg_R_State0();break;
        case 1:Leg_L_State1();break;
        case 2:Leg_L_State2();break;
        case 3:Leg_R_State1();break;
        case 4:Leg_R_State2();break;
        case 5:Leg_L_State3();break;
        case 6:Leg_L_State0();break;
        case 7:Leg_R_State3();break;
        default:
            break;
    }
}

// 机器人启停控制
void Robot_Control(){
    static uint8_t state = 0;
    if(walk){
        Robot_State_Choose(state);
        state = (state+1)%8;
    } else{
        Robot_Stand();
        state = 0;
    }
}