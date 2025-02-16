//
// Created by 86159 on 2025/1/2.
//

#include "myRobot.h"
#include "myUsart.h"

/**
 * 机器狗腿部舵机选择
 * @param idx 编号，范围 0-7，对应三八译码器 Y0-Y7 输出端口
 */
void Robot_Leg_Choose(uint8_t idx) {
//    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_A, (idx & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_B, (idx & 0x02)?GPIO_PIN_SET:GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_C, (idx & 0x04)?GPIO_PIN_SET:GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_A, (idx & 0x01));
    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_B, (idx & 0x02)>>1);

//    HAL_UART_Transmit(&huart, &idx, 1, 100);
//    uint8_t tmp = (idx & 0x01);
//    HAL_UART_Transmit(&huart, &tmp, 1, 100);
//    tmp = (idx & 0x02);
//    HAL_UART_Transmit(&huart, &tmp, 1, 100);
}

/**
 * 机器狗腿部舵机角度调整
 * @param pwmG 大腿 pwm 值，其占据 pwm 设定值的比例（即占空比）决定当前舵机的角度
 * @param pwmS 小腿 pwm 值，其占据 pwm 设定值的比例（即占空比）决定当前舵机的角度
 */
void Robot_Leg_PWM(uint16_t pwmG, uint16_t pwmS) {
    if (pwmG >= MY_PWM_Period || pwmS >= MY_PWM_Period)return;  // 保证不会爆掉
            __HAL_TIM_SetCompare(&htim_advance, MY_PWM_CHANNEL_G, pwmG);
            __HAL_TIM_SetCompare(&htim_advance, MY_PWM_CHANNEL_S, pwmS);
}

/**
 * 机器狗初始化，主要初始化高级定时器，设定 pwm 等功能
 */
void Robot_Init() {
//    MY_ROBOT_CHOOSE_AB_CLK_ENABLE();
//    MY_GPIO_INIT(MY_ROBOT_CHOOSE_PORT_AB, MY_ROBOT_CHOOSE_PIN_A);
//    MY_GPIO_INIT(MY_ROBOT_CHOOSE_PORT_AB, MY_ROBOT_CHOOSE_PIN_B);
//    MY_ROBOT_CHOOSE_C_CLK_ENABLE();
//    MY_GPIO_INIT(MY_ROBOT_CHOOSE_PORT_C, MY_ROBOT_CHOOSE_PIN_C);

    // 初始化 5v 引脚、pwm 控制、三八译码器高电平引脚
    MY_PWM_GPIO_CLK_ENABLE();  // 5v（C 端口）时钟使能
    MY_GPIO_INIT(MY_PWM_GPIO_PORT,
                 MY_PWM_POWER_PIN | MY_PWM_CONTROL_PIN_ALL | MY_PWM_POWER_PIN_38);   // 初始化 5v 引脚、pwm 控制引脚

    // PWM 5v 供电，三八译码器高电平输出
    HAL_GPIO_WritePin(MY_PWM_GPIO_PORT, MY_PWM_POWER_PIN, GPIO_PIN_SET);   // 开启 PWM 正极
//    HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_PWM_POWER_PIN_38, GPIO_PIN_RESET);    // 开启三八译码器高电平输出

    MX_TIM_Advance_Init();   // 初始化高级定时器 - 用于PWM
    HAL_TIM_PWM_Start(&htim_advance, MY_PWM_CHANNEL_G);    /* 开启 PWM 通道 1 */
    HAL_TIM_PWM_Start(&htim_advance, MY_PWM_CHANNEL_S);    /* 开启 PWM 通道 2 */
}

/**
 * 控制机器狗腿部动作，受 walk 影响\n
 * walk 当前有用位为低四位，功能如下：（低位为 0 号，高位为 7 号）\n
 * 2、3 号：选定当前腿，00 - 11 依次为左前、右前、左后、右后\n
 * 1 号：0 静止（站立、下蹲）；1 运动/走路\n
 * 0 号：（1 号为 0 时）0 下蹲，1 站立；（1 号为 0 时）走路时的两种状态\n
 * 其余位：暂时无用，设置为 0
 */
void Robot_Leg_Do() {
    // 大腿各状态的 pwm 值，同一行为同一状态，同一列为同一条腿
    static uint16_t pwm_G[4][4] = {
            // 右前、左后、右后、左前（流水线未知偏移导致）
            {2000, 4000, 2000, 4000}, // 下蹲
            {2000, 4000, 2000, 4000}, // 站立
            {2000, 4000, 3000, 3000}, // 迈步 0
            {3000, 3000, 2000, 4000}  // 迈步 1
    };
    // 小腿各状态的 pwm 值，同一行为同一状态，同一列为同一条腿
    static uint16_t pwm_S[4][4] = {
            // 右前、左后、右后、左前（流水线未知偏移导致）
            {3000, 3000, 3000, 3000}, // 下蹲
            {4000, 2000, 4000, 2000}, // 站立
            {4000, 2000, 1500, 4500}, // 迈步 0
            {1500, 4500, 4000, 2000}  // 迈步 1
    };
    static uint8_t count = 0;
    static uint8_t state, leg;

    state = walk & 0x03, leg = walk >> 2;
    Robot_Leg_Choose(leg);
    Robot_Leg_PWM(pwm_G[state][leg], pwm_S[state][leg]);

//    HAL_UART_Transmit(&huart, &leg, 1, 100);
//    count = pwm_G[state][leg]/1000;
//    HAL_UART_Transmit(&huart, &count, 1, 100);
//    HAL_UART_Transmit(&huart, " ", 1, 100);


    if (leg == 3 && (state >> 1)) { count++; }
    if (count == 16) {
        count = 0;
        walk = (leg << 2) + 3 - state % 2;
    } // walk = (leg << 2) + 2 + (1 - state % 2);
}