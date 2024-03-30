//
// Created by 86159 on 2024-03-31.
//

#ifndef STPROJECTFILES_MYTIM_H
#define STPROJECTFILES_MYTIM_H

#include "main.h"

#define BASIC_TIM           		TIM6
#define BASIC_TIM_CLK_ENABLE()     	__TIM6_CLK_ENABLE()

#define BASIC_TIM_IRQn				TIM6_DAC_IRQn
#define BASIC_TIM_IRQHandler    	TIM6_DAC_IRQHandler

extern TIM_HandleTypeDef TIM_TimeBaseStructure;
void TIMx_Configuration(void);

#endif //STPROJECTFILES_MYTIM_H
