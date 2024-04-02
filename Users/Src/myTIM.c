//
// Created by 86159 on 2024-03-31.
//

#include "myTIM.h"

TIM_HandleTypeDef htim_base;
TIM_HandleTypeDef htim_advance;


/* 基本定时器使用实验 **************************************************/
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

    htim_base.Instance = BASIC_TIM;
    /* 累计 TIM_Period 个脉冲后产生一个更新或者中断*/
    //当定时器从 0 计数到 9999，即为 10000 次，为一个定时周期
    htim_base.Init.Period = 10000 - 1;

    //定时器时钟源TIMxCLK = 2 * PCLK1
    //				PCLK1 = HCLK / 4
    //				=> TIMxCLK = HCLK/2 = SystemCoreClock/2 = 8MHz
    // 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=10000Hz
    htim_base.Init.Prescaler = 800 - 1;

    // 初始化定时器TIMx, x[6,7]
    HAL_TIM_Base_Init(&htim_base);

    // 开启定时器更新中断
    HAL_TIM_Base_Start_IT(&htim_base);
}

/**
  * @brief  初始化基本定时器定时，1s 产生一次中断
  * @param  无
  * @retval 无
  */
void TIMx_Configuration(void)
{
    TIMx_NVIC_Configuration();

    TIM_Mode_Config();
}


/* 高级定时器使用实验 **************************************************/
/* TIM_ADVANCE init function */
void MX_TIM_Advance_Init(void)
{
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    /* 定义定时器的句柄即确定定时器寄存器的基地址*/
    htim_advance.Instance = ADVANCE_TIM;
    // 高级控制定时器时钟源 TIMxCLK = HCLK = 16MHz
    // 设定定时器频率为 = TIMxCLK/(TIM_Prescaler+1) = 16MHz
    htim_advance.Init.Prescaler = 0;
    // 计数方式
    htim_advance.Init.CounterMode = TIM_COUNTERMODE_UP;
    /* 累计 TIM_Period个后产生一个更新或者中断*/
    //当定时器从 0 计数到 65535，即为 65536 次，为一个定时周期
    htim_advance.Init.Period = 65535;
    // 采样时钟分频
    htim_advance.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    // 重复计数器
    htim_advance.Init.RepetitionCounter = 0;
    // 自动输出使能
    htim_advance.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    // 初始化定时器TIMx, x[1,8]
    if (HAL_TIM_PWM_Init(&htim_advance) != HAL_OK)
    {
        Error_Handler();
    }

    /* 自动输出使能，断路、死区时间和锁定配置 */
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim_advance, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    /*PWM模式配置*/
    //配置为PWM模式1
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    // 初始化通道 1 输出 PWM
    sConfigOC.Pulse = 40000;
    if (HAL_TIM_PWM_ConfigChannel(&htim_advance, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    // 初始化通道 2 输出 PWM
    sConfigOC.Pulse = 30000;
    if (HAL_TIM_PWM_ConfigChannel(&htim_advance, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }
    // 初始化通道 3 输出 PWM
    sConfigOC.Pulse = 20000;
    if (HAL_TIM_PWM_ConfigChannel(&htim_advance, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler();
    }
    // 初始化通道 4 输出 PWM
    sConfigOC.Pulse = 10000;
    if (HAL_TIM_PWM_ConfigChannel(&htim_advance, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
    {
        Error_Handler();
    }

    /* 自动输出使能，断路、死区时间和锁定配置 */
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim_advance, &sBreakDeadTimeConfig) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_TIM_MspPostInit(&htim_advance);

}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
{

    if(tim_pwmHandle->Instance==ADVANCE_TIM)
    {
        /* USER CODE BEGIN TIM8_MspInit 0 */

        /* USER CODE END TIM8_MspInit 0 */
        /* TIM8 clock enable */
        ADVANCE_TIM_CLK_ENABLE();
        /* USER CODE BEGIN TIM8_MspInit 1 */

        /* USER CODE END TIM8_MspInit 1 */
    }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(timHandle->Instance==TIM8)
    {
        /* USER CODE BEGIN TIM8_MspPostInit 0 */

        /* USER CODE END TIM8_MspPostInit 0 */

        PWM_GPIO_CLK_ENABLE();

        GPIO_InitStruct.Pin = PWM_CONTROL_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF_ADVANCE_TIM;
        HAL_GPIO_Init(PWM_GPIO_PORT, &GPIO_InitStruct);

        /* USER CODE BEGIN TIM8_MspPostInit 1 */

        /* USER CODE END TIM8_MspPostInit 1 */
    }

}
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle)
{

    if(tim_pwmHandle->Instance==ADVANCE_TIM)
    {
        /* USER CODE BEGIN TIM8_MspDeInit 0 */

        /* USER CODE END TIM8_MspDeInit 0 */
        /* Peripheral clock disable */
        ADVANCE_TIM_CLK_DISABLE();
        /* USER CODE BEGIN TIM8_MspDeInit 1 */

        /* USER CODE END TIM8_MspDeInit 1 */
    }
}