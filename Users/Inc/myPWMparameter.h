//
// Created by 86159 on 2025/1/2.
//

#ifndef STPROJECTFILES_MYPWMPARAMETER_H
#define STPROJECTFILES_MYPWMPARAMETER_H

#include "main.h"

#define MY_PWM_GPIO_PORT GPIOC
#define MY_PWM_POWER_PIN GPIO_PIN_14
/**TIM8 GPIO Configuration
 * PC6     ------> TIM8_CH1
 * PC7     ------> TIM8_CH2
 * PC8     ------> TIM8_CH3
 * PC9     ------> TIM8_CH4
 */
#define MY_PWM_CONTROL_PIN (GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9)
#define MY_PWM_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
/** PWM 状态
 * PWM 使用的有效数字在 0x2000~0xa000 之间
 * 实际实验有三种状态：0-中间、+1(01)-正向、-1(11)-反向
 * 同时有三种不同编号：nan(无编号)-任何时候通用、S-站立时使用、M-运动时使用
 * 且实际使用极端情况并不合适，经过实验选择以下数据
 */
#define MY_PWM_STATE_0 0x6000
#define MY_PWM_STATE_S01 0x5800
#define MY_PWM_STATE_S11 0x6800
#define MY_PWM_STATE_M01 0x3800
#define MY_PWM_STATE_M11 0x8800

#endif //STPROJECTFILES_MYPWMPARAMETER_H
