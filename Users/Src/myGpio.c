//
// Created by 86159 on 2024-03-24.
//

#include "myGpio.h"

/**
 * @brief GPIO 初始化
 */
void MY_GPIO_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    LED_GPIO_CLK_ENABLE();   // LED（C 端口）时钟使能，使用外设时都要先开启它的时钟

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN | PWM_POWER_PIN, GPIO_PIN_RESET);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = LED_PIN | PWM_POWER_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * @brief GPIO 使用例子 - LED 闪烁 - 通过 delay
 * @param delay_num 闪烁间隔（半周期），每隔 delay_num ms LED 电平翻转一次
 */
void MY_GPIO_EXAMPLE_LED_ByDelay(uint32_t delay_num) {
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);
    HAL_Delay(delay_num);
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
    HAL_Delay(delay_num);
}

/**
 * @brief GPIO 使用例子 - LED 闪烁 - 通过定时器
 * @param sysTickNum 每隔 sysTickNum 次中断 LED 电平翻转一次
 */
void MY_GPIO_EXAMPLE_LED_ByTimer(uint32_t sysTickNum){
    static uint32_t n_us_num = 0;   // 已中断次数记录
//    static uint8_t state = 0;

    n_us_num = (n_us_num+1)%sysTickNum;
    if (n_us_num%sysTickNum==0){
//        state = ~state;
//        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, state ? GPIO_PIN_RESET : GPIO_PIN_SET);
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);   // GPIO 电平翻转
    }
}