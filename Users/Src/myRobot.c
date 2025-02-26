//
// Created by 86159 on 2025/1/2.
//

#include "myRobot.h"
#include "myUsart.h"

// 结果参数
// 足部运动摆线的坐标：0 为水平向坐标，即 x 轴；1 为竖直向坐标，即 z 轴（在求单腿运动学逆解时为 y 轴坐标）
static double leg_point[2] = {0, 0};
// 输出到控制足部的舵机的 pwm 值，0 为大腿舵机 pwm，1 为小腿舵机 pwm
static uint16_t pwmGS[2] = {3000, 3000};

// 用于求足部摆线坐标的参数
// 50 为单条腿迈步摆线的总周期，50 次 pwm 输出为 1 步，而单条腿接收的也是 50Hz 的 pwm 信号，即 1s 迈步一次
// 2 为占空比的倒数，单条腿一半时间用作摆动相，一半时间用作支撑相
static const uint8_t Ts_lambda = 50 / 2;
static float x_st = -1, x_ed = 1; // 摆线在起点、终点的 x 轴坐标
static float z_st = -10; // 摆线在起点的 z 轴坐标
static int8_t h = 1; // 摆线的高度

// 用于求运动学逆解的参数
static const double l_G = 8.0, l_S = 6.15; // 大小腿长度

/**
 * 求单腿足部坐标
 */
void get_leg_point(uint8_t leg) {
    static double sigma, x_BaiDong, x_ZhiCheng, z;
    uint8_t t = walk >> 2;
    // 根据所在时段求 sigma，计算当前摆动相、支撑相的应该在的坐标
    if (t <= Ts_lambda) { // 前半段
        sigma = 2 * M_PI * t / Ts_lambda;
    } else { // 后半段
        sigma = 2 * M_PI * (t - Ts_lambda) / Ts_lambda;
    }
    z = h * (1 - cos(sigma)) / 2 + z_st;
    x_BaiDong = (x_ed - x_st) * ((sigma - sin(sigma)) / (2 * M_PI)) + x_st;
    x_ZhiCheng = (x_st - x_ed) * ((sigma - sin(sigma)) / (2 * M_PI)) + x_ed;
    // 0、3 在前半段作摆动相，在后半段作支撑相；1、2 反之
    // A = 是否在前半段，B = 腿是否是 0、3
    // A、B 相同，则作摆动相；反之
    if ((t <= Ts_lambda) == (leg == 0 || leg == 3)) { // 摆动相
        leg_point[0] = x_BaiDong;
        leg_point[1] = z;
    } else { // 支撑相
        leg_point[0] = x_ZhiCheng;
        leg_point[1] = z_st;
    }
}

// 通过已知的足部坐标求运动学逆解
// 参考：https://www.bilibili.com/video/BV13T4y1G7qy?spm_id_from=333.788.recommend_more_video.1&vd_source=1ccb8ff2c60b49bbfff6dfe8c1bb0eab
void get_Kinematics_Inverse_Solution(uint8_t leg) {
    double x = -leg_point[0], y = -leg_point[1]; // 将足部坐标从三、四象限转到一、二象限
    static double thetaS, thetaG; // 小腿和大腿的角度
    static double varphi; // 计算大腿角度时的中间参数
    // 求小腿角度
    thetaS = M_PI - acos((x * x + y * y - l_S * l_S - l_G * l_G) / (-2 * l_G * l_S));
    // 求大腿角度
    varphi = acos((l_G * l_G + x * x + y * y - l_S * l_S) / (2 * l_G * sqrt(x * x + y * y)));
    if (x > 0) {
        thetaG = fabs(atan(y / x)) - varphi;
        HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_LED_PIN, GPIO_PIN_SET);
    } else if (x < 0) {
        thetaG = M_PI - fabs(atan(y / x)) - varphi;
        HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_LED_PIN, GPIO_PIN_SET);
    } else {
        thetaG = M_PI / 2 - varphi;
        HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_LED_PIN, GPIO_PIN_RESET);
    }
    // 左腿（0、2）右腿（1、3）摆动到同一位置所需的 pwm 信号不同
    // 左腿 pwm 值越小越往前；右腿越大越往前
//    thetaS -= M_PI / 4;
    if (leg == 0 || leg == 2) { // 左腿
        pwmGS[0] = (uint16_t) (5000.0 - 4000.0 * thetaG / M_PI); //G
    } else { // 右腿
        pwmGS[0] = (uint16_t) (4000.0 * thetaG / M_PI + 1000.0); //G
        thetaS = M_PI - thetaS;
    }
    pwmGS[1] = (uint16_t) (4000.0 * thetaS / M_PI + 1000.0); //S
}

/**
 * 机器狗腿部舵机选择
 * @param idx 编号，范围 0-7，对应三八译码器 Y0-Y7 输出端口
 */
void Robot_Leg_Choose(uint8_t idx) {
//    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_A, (idx & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_B, (idx & 0x02)?GPIO_PIN_SET:GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_C, (idx & 0x04)?GPIO_PIN_SET:GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_A, (idx & 0x01));
    HAL_GPIO_WritePin(MY_ROBOT_GPIO_Port, MY_ROBOT_CHOOSE_PIN_B, (idx & 0x02) >> 1);

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
 * 6、7 号：选定当前腿，00 - 11 依次为左前、右前、左后、右后\n
 * 5 号：0 静止（站立、下蹲）；1 运动/走路\n
 * 5 号为 0 时，仅 0 号有效（为 0 下蹲，为 1 站立）；5 号为 1 时：0、1 号有效（走路时的 4 种状态）\n
 * 其余位：暂时无用，设置为 0\n
 * \n ***************************************************** \n\n
 * 特别强调：该函数只能在 while 里使用，禁止放到定时器中断里去，会使流水线产生未知偏移
 */
void Robot_Leg_Do() {
    if (walk_state == 0) {
        h = 0;
        x_st = x_ed = 0;
        z_st = -8;
    } else if (walk_state == 1) {
        h = 0;
        x_st = x_ed = 0;
        z_st = -10;
    } else {
        x_st = -2;
        x_ed = 2; // 摆线在起点、终点的 x 轴坐标
        z_st = -10; // 摆线在起点的 z 轴坐标
        h = 2; // 摆线的高度
    }

    uint8_t leg = walk & 0x03;
    // PWM 数值获取
    get_leg_point(leg);
    get_Kinematics_Inverse_Solution(leg);

    // PWM 选择输出
    Robot_Leg_Choose(leg);
    Robot_Leg_PWM(pwmGS[0], pwmGS[1]);
}
