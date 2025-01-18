//
// Created by 86159 on 2025/1/2.
//

#include "myRobot.h"

/**
 * 机器狗腿部舵机选择
 * @param idx 编号，范围 0-7，对应三八译码器 Y0-Y7 输出端口
 */
void Robot_Leg_Choose(uint8_t idx) {
//    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_A, (idx & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_B, (idx & 0x02)?GPIO_PIN_SET:GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_C, (idx & 0x04)?GPIO_PIN_SET:GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_A, (idx & 0x01));
    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_B, (idx & 0x02));
    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_C, (idx & 0x04));
}

/**
 * 机器狗腿部舵机角度调整
 * @param pwm pwm 值，其占据 pwm 设定值的比例（即占空比）决定当前舵机的角度
 */
void Robot_Leg_PWM(uint16_t pwm) {
    if (pwm >= MY_PWM_Period)return;  // 保证不会爆掉
            __HAL_TIM_SetCompare(&htim_advance, MY_PWM_CHANNEL, pwm);
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
    HAL_TIM_PWM_Start(&htim_advance, MY_PWM_CHANNEL);    /* 开启 PWM 通道 1 */
}

/**
 * 单条腿部状态选择，只有两种状态，出腿、收腿
 * @param leg 腿部选择，范围 0-3，对应 4 条腿，每条腿上两个舵机
 * @param isDoLeg 是否出腿：0 - 否，即收腿；other - 是，即出腿。出腿即为正常站立时机器狗的腿部状态
 */
void Robot_Leg_State(uint8_t leg, uint8_t isDoLeg) {
    // 收腿与出腿状态下 8 个舵机的 PWM 值，0-7 号为收腿时的值，8-15 为出腿的值
    uint16_t pwms[16] = {
            33000, 22000, 17000, 25000, 36000, 25000, 14000, 25000,
            30000, 10000, 20000, 37000, 32000, 13000, 18000, 37000
    };

    // 偏移值：如果要求出腿，舵机 pwm 值映射上方数组的后 8 个值，否则映射前 8 个
    isDoLeg = isDoLeg ? 8 : 0;
    // 选择腿部对应的大腿舵机并动作
    uint8_t bigLeg = leg * 2;
    Robot_Leg_Choose(bigLeg);
    Robot_Leg_PWM(pwms[bigLeg + isDoLeg]);
    // 选择腿部对应的小腿舵机并动作
    uint8_t smallLeg = leg * 2 + 1;
    Robot_Leg_Choose(smallLeg);
    Robot_Leg_PWM(pwms[smallLeg + isDoLeg]);
}

/**
 * 机器狗腿部动作
 * @param state 机器狗当前状态，范围：受当前机器狗可以进行的动作影响\n
 * 0 - 站立\n
 * 1 - 下蹲\n
 * 2 - 行走 1 - 左前腿、右后腿前迈\n
 * 3 - 行走 2 - 右前腿、左后腿前迈
 */
void Robot_Leg_Do(uint8_t state) {
    uint8_t legState[4][4] = {
            {1, 1, 1, 1},  // 状态 0 - 站立
            {0, 0, 0, 0},  // 状态 1 - 下蹲
            {1, 0, 1, 0},  // 状态 2 - 行走 1 - 左前腿、右后腿前迈
            {0, 1, 0, 1}  // 状态 3 - 行走 2 - 右前腿、左后腿前迈
    };

    for (uint8_t i = 0; i < 4; ++i) {
        Robot_Leg_State(i, legState[state][i]);
    }
}