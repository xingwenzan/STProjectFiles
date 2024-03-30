//
// Created by 86159 on 2024-03-31.
//

#include "myTIM.h"

TIM_HandleTypeDef TIM_TimeBaseStructure;

/**
  * @brief  基本定时器 TIMx,x[6,7]中断优先级配置
  * @param  无
  * @retval 无
  */
static void TIMx_NVIC_Configuration(void)
{
    //设置抢占优先级，子优先级
    HAL_NVIC_SetPriority(BASIC_TIM_IRQn, 0, 3);
    // 设置中断来源
    HAL_NVIC_EnableIRQ(BASIC_TIM_IRQn);
}

/*
 * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
 * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
 * 另外三个成员是通用定时器和高级定时器才有.
 *-----------------------------------------------------------------------------
 * TIM_Prescaler         都有
 * TIM_CounterMode			 TIMx,x[6,7]没有，其他都有（基本定时器）
 * TIM_Period            都有
 * TIM_ClockDivision     TIMx,x[6,7]没有，其他都有(基本定时器)
 * TIM_RepetitionCounter TIMx,x[1,8]才有(高级定时器)
 *-----------------------------------------------------------------------------
 */
static void TIM_Mode_Config(void)
{
    // 开启TIMx_CLK,x[6,7]
    BASIC_TIM_CLK_ENABLE();

    TIM_TimeBaseStructure.Instance = BASIC_TIM;
    /* 累计 TIM_Period 个脉冲后产生一个更新或者中断*/
    //当定时器从 0 计数到 9999，即为 10000 次，为一个定时周期
    TIM_TimeBaseStructure.Init.Period = 10000-1;

    //定时器时钟源TIMxCLK = 2 * PCLK1
    //				PCLK1 = HCLK / 4
    //				=> TIMxCLK=HCLK/2=SystemCoreClock/2=8MHz
    // 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=10000Hz
    TIM_TimeBaseStructure.Init.Prescaler = 800-1;

    // 初始化定时器TIMx, x[6,7]
    HAL_TIM_Base_Init(&TIM_TimeBaseStructure);

    // 开启定时器更新中断
    HAL_TIM_Base_Start_IT(&TIM_TimeBaseStructure);
}

/**
  * @brief  初始化基本定时器定时，1ms产生一次中断
  * @param  无
  * @retval 无
  */
void TIMx_Configuration(void)
{
    TIMx_NVIC_Configuration();

    TIM_Mode_Config();
}