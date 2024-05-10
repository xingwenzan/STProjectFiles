/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
void Error_Handler(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define MY_LED_PIN GPIO_PIN_0
#define MY_LED_GPIO_PORT GPIOC
#define MY_LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

#define MY_PWM_GPIO_PORT GPIOC
#define MY_PWM_POWER_PIN GPIO_PIN_14
/**TIM8 GPIO Configuration
 * PC6     ------> TIM8_CH1
 * PC7     ------> TIM8_CH2
 * PC8     ------> TIM8_CH3
 * PC9     ------> TIM8_CH4
 */
#define MY_PWM_CONTROL_PIN (GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9)
#define MY_PWM_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

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

#define MY_UART_ALTERNATE GPIO_AF8_UART4
#define MY_UART_CLK_ENABLE() __HAL_RCC_UART4_CLK_ENABLE()
#define MY_UART_CLK_DISABLE() __HAL_RCC_UART4_CLK_DISABLE()
#define MY_UART UART4
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
