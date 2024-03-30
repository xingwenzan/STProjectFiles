//
// Created by 86159 on 2024-03-24.
//

#ifndef STPROJECTFILES_GPIO_H
#define STPROJECTFILES_GPIO_H

#include "main.h"

void MY_GPIO_INIT(void);
void MY_GPIO_EXAMPLE_LED_ByDelay(uint32_t delay_num);
void MY_GPIO_EXAMPLE_LED_ByTimer(uint32_t sysTickNum);

#endif //STPROJECTFILES_GPIO_H