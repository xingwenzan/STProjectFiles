//
// Created by 86159 on 2025/1/2.
//

#ifndef STPROJECTFILES_MYPWMPARAMETER_H
#define STPROJECTFILES_MYPWMPARAMETER_H

#include "main.h"

// PWM 相关端口引脚及其使能
#define MY_PWM_GPIO_PORT GPIOC
#define MY_PWM_POWER_PIN GPIO_PIN_14   // 5v 引脚
#define MY_PWM_POWER_PIN_38 GPIO_PIN_5   // 三八译码器高电平引脚
/**TIM8 GPIO Configuration
 * PC6     ------> TIM8_CH1
 * PC7     ------> TIM8_CH2
 * PC8     ------> TIM8_CH3
 * PC9     ------> TIM8_CH4
 */
#define MY_PWM_CONTROL_PIN_ALL (GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9)   // 三八译码器输出选择引脚
#define MY_PWM_CONTROL_PIN GPIO_PIN_6   // PWM 输出引脚
#define MY_PWM_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()   // 端口时钟使能

// PWM 控制状态相关
#define MY_PWM_Period 9999  // 当定时器从 0 计数到 MY_PWM_Period，即为 MY_PWM_Period 次，为一个定时周期，是 pwm 的初始设定值

#endif //STPROJECTFILES_MYPWMPARAMETER_H
