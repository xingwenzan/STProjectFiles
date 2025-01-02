//
// Created by 86159 on 2024/4/30.
//

#ifndef STPROJECTFILES_MYUSART_H
#define STPROJECTFILES_MYUSART_H

#include "main.h"

extern UART_HandleTypeDef huart;


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
#define MY_UART_TX_PORT GPIOC
#define MY_UART_TX_PIN GPIO_PIN_10
#define MY_UART_RX_PORT GPIOC
#define MY_UART_RX_PIN GPIO_PIN_11
#define MY_UART_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
#define MY_UART_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()

#define MY_UART_ALTERNATE GPIO_AF8_UART4
#define MY_UART_CLK_ENABLE() __HAL_RCC_UART4_CLK_ENABLE()
#define MY_UART_CLK_DISABLE() __HAL_RCC_UART4_CLK_DISABLE()
#define MY_UART UART4


void MX_UART_Init(void);

#endif //STPROJECTFILES_MYUSART_H
