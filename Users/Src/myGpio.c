//
// Created by 86159 on 2024-03-24.
//

#include "myGpio.h"

void MY_GPIO_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
//    __HAL_RCC_GPIOH_CLK_ENABLE();   // 意义不明，不影响 LED 闪烁
    __HAL_RCC_GPIOC_CLK_ENABLE();   // C端口（LED）时钟使能，没有不亮
//    __HAL_RCC_GPIOA_CLK_ENABLE();   // 意义不明，不影响 LED 闪烁

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
}