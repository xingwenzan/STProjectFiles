//
// Created by 86159 on 2024/5/13.
//

#include "myRobot.h"

void Robot_Init() {
    MX_TIM_Advance_Init();   // 初始化高级定时器 - 用于PWM
    HAL_TIM_PWM_Start(&htim_advance, TIM_CHANNEL_1);    /* 开启 PWM 通道 1 */
    HAL_TIM_PWM_Start(&htim_advance, TIM_CHANNEL_2);    /* 开启 PWM 通道 2 */
    HAL_TIM_PWM_Start(&htim_advance, TIM_CHANNEL_3);    /* 开启 PWM 通道 3 */
    HAL_TIM_PWM_Start(&htim_advance, TIM_CHANNEL_4);    /* 开启 PWM 通道 4 */
}

void Robot_Stand() {
            __HAL_TIM_SetCompare(&htim_advance, TIM_CHANNEL_1, MY_PWM_STATE_S01);
            __HAL_TIM_SetCompare(&htim_advance, TIM_CHANNEL_2, MY_PWM_STATE_S11);
            __HAL_TIM_SetCompare(&htim_advance, TIM_CHANNEL_3, MY_PWM_STATE_S01);
            __HAL_TIM_SetCompare(&htim_advance, TIM_CHANNEL_4, MY_PWM_STATE_S11);
}