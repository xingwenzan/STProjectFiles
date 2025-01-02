//
// Created by 86159 on 2024-03-31.
//

#ifndef STPROJECTFILES_MYTIM_H
#define STPROJECTFILES_MYTIM_H

#include "main.h"
#include "myPWMparameter.h"

extern TIM_HandleTypeDef htim_advance;
extern TIM_HandleTypeDef htim_base;

// 可选 TIM6、TIM7
#define BASIC_TIM           		TIM6
#define BASIC_TIM_CLK_ENABLE()     	__TIM6_CLK_ENABLE()

// 可选 TIM1、TIM8
#define ADVANCE_TIM                 TIM8
#define ADVANCE_TIM_CLK_ENABLE()    __HAL_RCC_TIM8_CLK_ENABLE()
#define ADVANCE_TIM_CLK_DISABLE()   __HAL_RCC_TIM8_CLK_DISABLE();
#define GPIO_AF_ADVANCE_TIM         GPIO_AF3_TIM8

#define BASIC_TIM_IRQn				TIM6_DAC_IRQn   // stm32f446xx.h 中可找
#define BASIC_TIM_IRQHandler    	TIM6_DAC_IRQHandler

void TIMx_Configuration(void);

void MX_TIM_Advance_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

#endif //STPROJECTFILES_MYTIM_H
