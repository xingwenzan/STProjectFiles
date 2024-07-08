//
// Created by 86159 on 2024/4/30.
//

#include "myUart.h"

// `串口结构体`，用于控制串口的状态
// 该参数是个 extern 参数，第一次出现在 `myUart.h`，可在项目的其他文件使用
UART_HandleTypeDef huart;

/* UART init function */
void MX_UART_Init(void) {

    huart.Instance = MY_UART;   // 设置串口为 MY_UART，MY_UART 在 main.h 中被定义为 UART4（串口4），方便代码重写
    huart.Init.BaudRate = 115200;   // 波特率，一般用 115200 或 9600，具体可选范围受主频、分频影响，但一定得保证通信双方波特率相同
    huart.Init.WordLength = UART_WORDLENGTH_8B;   // 字长，一般用 8b，也可选 9b（一般多一个奇偶校检位），但一定要保证通信双方字长相同
    huart.Init.StopBits = UART_STOPBITS_1;   // 停止位，一般用 1b，也可选 2b，但一定要保证通信双方相同
    huart.Init.Parity = UART_PARITY_NONE;   // 校检位，可选 UART_Parity_No(无校验)、UART_Parity_Even(偶校验) 以及 UART_Parity_Odd(奇校验)
    huart.Init.Mode = UART_MODE_TX_RX;   // uart（串口）模式，可控制 UART_MODE_TX_RX（收发）、UART_MODE_RX（仅接收）、UART_MODE_TX（仅发送）
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;   // 硬件流设置，为是否支持硬件流控制，我们设置为无硬件流控制
    huart.Init.OverSampling = UART_OVERSAMPLING_16;   // 过采样为 16 倍还是 8 倍，我们选择 16 倍
    // 设置好参数后调用 HAL_UART_Init 函数，会自动初始化串口，如果不成功会报错
    if (HAL_UART_Init(&huart) != HAL_OK) {
        Error_Handler();
    }

}

// UART MSP Init - 代码重写 - 开启对应的引脚和时钟 - 它会在 HAL_UART_Init 函数（HAL 库的串口初始化函数）中被调用
void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (uartHandle->Instance == MY_UART) {
        /* USER CODE BEGIN UART5_MspInit 0 */

        /* USER CODE END UART5_MspInit 0 */
        /* UART5 clock enable */
        MY_UART_CLK_ENABLE();

        MY_UART_TX_GPIO_CLK_ENABLE();
        MY_UART_RX_GPIO_CLK_ENABLE();
        /**
         * UART SET
         *
         * UART5 GPIO Configuration
         * PC12     ------> UART5_TX
         * PD2     ------> UART5_RX
         *
         * UART4 GPIO Configuration
         * PC10     ------> UART4_TX
         * PC11     ------> UART4_RX
        */
        GPIO_InitStruct.Pin = MY_UART_TX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = MY_UART_ALTERNATE;
        HAL_GPIO_Init(MY_UART_TX_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = MY_UART_RX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = MY_UART_ALTERNATE;
        HAL_GPIO_Init(MY_UART_RX_PORT, &GPIO_InitStruct);

        /* USER CODE BEGIN UART5_MspInit 1 */

        /* USER CODE END UART5_MspInit 1 */
    }
}

// UART MSP DeInit - 代码重写 - 关闭对应的引脚和时钟 - 它会在 HAL_UART_DeInit 函数（HAL 库的串口关闭函数）中被调用
void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle) {

    if (uartHandle->Instance == MY_UART) {
        /* USER CODE BEGIN UART5_MspDeInit 0 */

        /* USER CODE END UART5_MspDeInit 0 */
        /* Peripheral clock disable */
        MY_UART_CLK_DISABLE();

        /**
         * UART SET
         *
         * UART5 GPIO Configuration
         * PC12     ------> UART5_TX
         * PD2     ------> UART5_RX
         *
         * UART4 GPIO Configuration
         * PC10     ------> UART4_TX
         * PC11     ------> UART4_RX
        */
        HAL_GPIO_DeInit(MY_UART_TX_PORT, MY_UART_TX_PIN);

        HAL_GPIO_DeInit(MY_UART_RX_PORT, MY_UART_RX_PIN);

        /* USER CODE BEGIN UART5_MspDeInit 1 */

        /* USER CODE END UART5_MspDeInit 1 */
    }
}