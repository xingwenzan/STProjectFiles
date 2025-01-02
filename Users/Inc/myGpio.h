//
// Created by 86159 on 2024-03-24.
//

#ifndef STPROJECTFILES_GPIO_H
#define STPROJECTFILES_GPIO_H

#include "main.h"

#define MY_LED_PIN GPIO_PIN_0
#define MY_LED_GPIO_PORT GPIOC
#define MY_LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

void MY_GPIO_INIT(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void MY_GPIO_EXAMPLE_LED_ByDelay(uint32_t delay_num);
void MY_GPIO_EXAMPLE_LED_ByTimer(uint32_t sysTickNum);

#endif //STPROJECTFILES_GPIO_H