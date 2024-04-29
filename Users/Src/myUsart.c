//
// Created by 86159 on 2024/4/30.
//

#include "myUsart.h"

UART_HandleTypeDef huart;

/* UART init function */
void MX_UART_Init(void) {

    huart.Instance = UART5;
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart) != HAL_OK) {
        Error_Handler();
    }

}

// UART MSP Init - 代码重写
void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (uartHandle->Instance == UART5) {
        /* USER CODE BEGIN UART5_MspInit 0 */

        /* USER CODE END UART5_MspInit 0 */
        /* UART5 clock enable */
        __HAL_RCC_UART5_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /**UART5 GPIO Configuration
        PC12     ------> UART5_TX
        PD2     ------> UART5_RX
        */
        GPIO_InitStruct.Pin = UART_TX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
        HAL_GPIO_Init(UART_TX_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = UART_RX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
        HAL_GPIO_Init(UART_RX_PORT, &GPIO_InitStruct);

        /* USER CODE BEGIN UART5_MspInit 1 */

        /* USER CODE END UART5_MspInit 1 */
    }
}
// UART MSP DeInit - 代码重写
void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle) {

    if (uartHandle->Instance == UART5) {
        /* USER CODE BEGIN UART5_MspDeInit 0 */

        /* USER CODE END UART5_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_UART5_CLK_DISABLE();

        /**UART5 GPIO Configuration
        PC12     ------> UART5_TX
        PD2     ------> UART5_RX
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

        /* USER CODE BEGIN UART5_MspDeInit 1 */

        /* USER CODE END UART5_MspDeInit 1 */
    }
}