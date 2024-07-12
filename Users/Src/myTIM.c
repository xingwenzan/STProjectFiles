//
// Created by 86159 on 2024-03-31.
//

#include "myTIM.h"

// 定时器结构体（无论哪种定时器，控制其的结构体都是一样的）
// 它们都在 `.h` 文件里添加了 extern，可以跨文件使用
TIM_HandleTypeDef htim_base;
TIM_HandleTypeDef htim_advance;


/* 基本定时器使用 **************************************************/
/**
  * @brief  基本定时器 TIMx,x[6,7]中断优先级配置
  * @param  无
  * @retval 无
  */
static void TIMx_NVIC_Configuration(void) {
    //设置抢占优先级，子优先级
    HAL_NVIC_SetPriority(BASIC_TIM_IRQn, 0, 3);
    // 设置中断来源 - 启用指定中断通道，使能后，NVIC 能够处理该中断请求
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
static void TIM_Mode_Config(void) {
    // 开启TIMx_CLK,x[6,7]，定义在 `main.h` 可自行更改
    BASIC_TIM_CLK_ENABLE();

    htim_base.Instance = BASIC_TIM;
    /* 累计 TIM_Period 个脉冲后产生一个更新或者中断*/
    //当定时器从 0 计数到 9999，即为 10000 次，为一个定时周期
    htim_base.Init.Period = 10000 - 1;

    // 高级控制定时器时钟源 TIMxCLK = HCLK = 16MHz
    // 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=10000Hz
    htim_base.Init.Prescaler = 1600 - 1;

    // 初始化基本定时器 TIMx, x[6,7]
    HAL_TIM_Base_Init(&htim_base);

    // 开启定时器更新中断 - 启动定时器并使能定时器更新中断，这样当定时器达到指定的计数值时，会触发/产生一个中断
    HAL_TIM_Base_Start_IT(&htim_base);
}

/**
  * @brief  初始化基本定时器定时，1s 产生一次中断
  * @param  无
  * @retval 无
  */
void TIMx_Configuration(void) {
    TIMx_NVIC_Configuration();

    TIM_Mode_Config();
}


/* 高级定时器使用 **************************************************/
/* TIM_ADVANCE init function */
void MX_TIM_Advance_Init(void) {
    // 目前我也不清楚这玩意有啥用，过后去掉试试
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    // 用于输出比较模式，与 TIM_OCx_SetConfig 函数配合使用完成指定定时器输出通道初始化配置
    // 高级控制定时器有四个定时器通道，使用时都必须单独设置
    TIM_OC_InitTypeDef sConfigOC = {0};
    // 用于断路和死区参数的设置，属于高级定时器专用，用于配置断路时通道输出状态，以及死区时间
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    /* 定义定时器的句柄即确定定时器寄存器的基地址*/
    htim_advance.Instance = ADVANCE_TIM;   // ADVANCE_TIM 定义在 `main.h`，定为了定时器 8
    // 高级控制定时器时钟源 TIMxCLK = HCLK = 16MHz
    // 设定定时器频率为 = TIMxCLK/(TIM_Prescaler+1) = 16MHz
    htim_advance.Init.Prescaler = 0;
    // 计数方式 - 上升沿计数
    htim_advance.Init.CounterMode = TIM_COUNTERMODE_UP;
    /* 累计 TIM_Period 个后产生一个更新或者中断*/
    //当定时器从 0 计数到 65535，即为 65536 次，为一个定时周期
    htim_advance.Init.Period = 65535;
    // 采样时钟分频 - 不分频
    htim_advance.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    // 重复计数器 - 不重复计数
    htim_advance.Init.RepetitionCounter = 0;
    // 自动输出使能 - 不自动输出
    htim_advance.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    // 初始化定时器TIMx, x[1,8] - 它会调用下面重写的 HAL_TIM_PWM_MspInit
    if (HAL_TIM_PWM_Init(&htim_advance) != HAL_OK) {
        Error_Handler();
    }

    /* 自动输出使能，断路、死区时间和锁定配置 */
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim_advance, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }

    /*PWM模式配置*/
    sConfigOC.OCMode = TIM_OCMODE_PWM1;   // 比较输出模式选择，总共有八种，常用的为 PWM1/PWM2，这里用 PWM1
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;   // 比较输出极性，可选为高电平有效或低电平有效。它决定着定时器通道有效电平，这里选为高电平有效
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;   // 比较互补输出极性，可选OCxN为高电平有效或低电平有效
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;   // 比较输出模式快速使能，这里不使能
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;   // 空闲状态时通道输出电平设置，可选输出 1 或 0，即在空闲状态时，经过死区时间后定时器通道输出高电平或低电平，当前为低电平
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_SET;   // 空闲状态时互补通道输出电平设置，可选输出1或输出0，即在空闲状态时，经过死区时间 定时器互补通道输出高电平或低电平，设定值必须与OCIdleState相反
    // 初始化通道 1 输出 PWM（各通道在使用不同定时器时对应不同引脚，这部分数据手册上已经标明）
    sConfigOC.Pulse = MY_PWM_STATE_0;   // 比较输出脉冲宽度，max = 2^16，正占空比 = Pulse/max
    if (HAL_TIM_PWM_ConfigChannel(&htim_advance, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
    // 初始化通道 2 输出 PWM
    sConfigOC.Pulse = MY_PWM_STATE_0;
    if (HAL_TIM_PWM_ConfigChannel(&htim_advance, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) {
        Error_Handler();
    }
    // 初始化通道 3 输出 PWM
    sConfigOC.Pulse = MY_PWM_STATE_0;
    if (HAL_TIM_PWM_ConfigChannel(&htim_advance, &sConfigOC, TIM_CHANNEL_3) != HAL_OK) {
        Error_Handler();
    }
    // 初始化通道 4 输出 PWM
    sConfigOC.Pulse = MY_PWM_STATE_0;
    if (HAL_TIM_PWM_ConfigChannel(&htim_advance, &sConfigOC, TIM_CHANNEL_4) != HAL_OK) {
        Error_Handler();
    }
//    __HAL_TIM_SetCompare(&htim_advance,TIM_CHANNEL_1,0);   // 外部控制占空比代码

    /* 自动输出使能，断路、死区时间和锁定配置 */
    // 这里为了省事全关了，不设置死区
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim_advance, &sBreakDeadTimeConfig) != HAL_OK) {
        Error_Handler();
    }
    // 开启引脚
    HAL_TIM_MspPostInit(&htim_advance);

}

// Initializes the TIM PWM MSP - 代码重写 - 开启对应的时钟（引脚在最后配置完成后使用下面的 `HAL_TIM_MspPostInit` 统一开启）
// 它会在 HAL_TIM_PWM_Init 函数（HAL 库的定时器 PWM 功能初始化函数）中被调用 - MX_TIM_Advance_Init 在上面的 MX_TIM_Advance_Init 被调用
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *tim_pwmHandle) {

    if (tim_pwmHandle->Instance == ADVANCE_TIM) {
        /* USER CODE BEGIN TIM8_MspInit 0 */

        /* USER CODE END TIM8_MspInit 0 */
        /* TIM8 clock enable */
        ADVANCE_TIM_CLK_ENABLE();
        /* USER CODE BEGIN TIM8_MspInit 1 */

        /* USER CODE END TIM8_MspInit 1 */
    }
}

// DeInitializes TIM PWM MSP - 代码重写 - 关闭对应的时钟（引脚改变或时钟关闭时功能自然关闭）
// 它会在 HAL_TIM_PWM_Init 函数（HAL 库的定时器 PWM 功能关闭函数）中被调用
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *tim_pwmHandle) {

    if (tim_pwmHandle->Instance == ADVANCE_TIM) {
        /* USER CODE BEGIN TIM8_MspDeInit 0 */

        /* USER CODE END TIM8_MspDeInit 0 */
        /* Peripheral clock disable */
        ADVANCE_TIM_CLK_DISABLE();
        /* USER CODE BEGIN TIM8_MspDeInit 1 */

        /* USER CODE END TIM8_MspDeInit 1 */
    }
}

// 定时器使用 PWM 开启端口及引脚
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (timHandle->Instance == TIM8) {
        /* USER CODE BEGIN TIM8_MspPostInit 0 */

        /* USER CODE END TIM8_MspPostInit 0 */

        MY_PWM_GPIO_CLK_ENABLE();

        GPIO_InitStruct.Pin = MY_PWM_CONTROL_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF_ADVANCE_TIM;
        HAL_GPIO_Init(MY_PWM_GPIO_PORT, &GPIO_InitStruct);

        /* USER CODE BEGIN TIM8_MspPostInit 1 */

        /* USER CODE END TIM8_MspPostInit 1 */
    }

}