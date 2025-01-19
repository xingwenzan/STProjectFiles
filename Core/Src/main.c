/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "myGpio.h"
#include "myTIM.h"
#include "myUsart.h"
#include "myRobot.h"
#include "BMI088driver.h"
#include "myIMU.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t walk = 0;   // ?? myRobot ?? walk 赋???，该参数是 extern 型变量，可以在同??个项目中跨文件使用，只要在使用前正确赋???了
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
void SystemClock_Config(void);   // 文件创建自带函数
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
fp32 gyro[3], accel[3], temp;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */
    HAL_Init();
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
    SystemClock_Config();
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_DMA_Init();
    MX_SPI2_Init();
    MX_TIM3_Init();
    MX_USB_DEVICE_Init();
    /* USER CODE BEGIN 2 */
    // 初始?? LED
    MY_LED_GPIO_CLK_ENABLE();   // LED（C 端口）时钟使能，使用外设时都要先??启它的时钟，且端口时钟使能后才能进行初始??
    MY_GPIO_INIT(MY_LED_GPIO_PORT, MY_LED_PIN);   // 初始?? LED 引脚
    HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_LED_PIN, GPIO_PIN_SET);
    // 机器人初始化
    Robot_Init();   // 机器人初始化函数
    // 其他功能
    TIMx_Configuration();   // 初始化基本定时器定时??1s 产生??次中断，控制机器人运动的每一步的核心
    MX_UART_Init();   // 初始化串??
    HAL_UART_Transmit(&huart, "my Uart Hello!\n", 15, 100);   // 串口发???内容（用于测试，可有可无）
    // 初始?? IMU
    IMU_Init();
    HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_LED_PIN, GPIO_PIN_RESET);
    // 舵机角度测试??
//    uint16_t tmp = 0;
    // 机器狗位移测试用
//    walk = 0;
//    HAL_Delay(10000);
//    walk = 1;
//    HAL_Delay(10000);
//    walk = 2;
    // IMU 测试用，用于将获取的内容发???出??
    union Data_Uart_Float tmp_out = {0};
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE BEGIN 3 */
        // 主要信号接收部分，???过接收串口信号实现启停接收
//        int ch;
//        HAL_UART_Receive(&huart, (uint8_t *) &ch, 1, 0xFFFF);   // 串口接收
//        HAL_GPIO_TogglePin(MY_LED_GPIO_PORT, MY_LED_PIN);
//        // 舵机角度测试
//        if (ch == '=') {
//            Robot_Leg_PWM(tmp);
//            tmp = 0;
//        } else {
//            tmp *= 10;
//            tmp += ch-'0';
//        }

        // 腿部舵机选择测试
//        Robot_Leg_Choose(ch-'0');

        // IMU 测试
        BMI088_read(gyro, accel, &temp);
        HAL_Delay(10);
        HAL_UART_Transmit(&huart, "\nTemp:", 6, 100);
        tmp_out.fx = temp;
        Float_Uart_Out(&huart, tmp_out);
        HAL_UART_Transmit(&huart, "\nAccelX:", 8, 100);
        tmp_out.fx = accel[0];
        Float_Uart_Out(&huart, tmp_out);
        HAL_UART_Transmit(&huart, "\nAccelY:", 8, 100);
        tmp_out.fx = accel[1];
        Float_Uart_Out(&huart, tmp_out);
        HAL_UART_Transmit(&huart, "\nAccelZ:", 8, 100);
        tmp_out.fx = accel[2];
        Float_Uart_Out(&huart, tmp_out);
        HAL_UART_Transmit(&huart, "\nGyroX:", 7, 100);
        tmp_out.fx = gyro[0];
        Float_Uart_Out(&huart, tmp_out);
        HAL_UART_Transmit(&huart, "\nGyroY:", 7, 100);
        tmp_out.fx = gyro[1];
        Float_Uart_Out(&huart, tmp_out);
        HAL_UART_Transmit(&huart, "\nGyroZ:", 7, 100);
        tmp_out.fx = gyro[2];
        Float_Uart_Out(&huart, tmp_out);
        HAL_Delay(10000);

        /* USER CODE END 3 */
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // 主要信号接收部分，???过接收串口信号实现启停接收
//        int ch;
//        HAL_UART_Receive(&huart, (uint8_t *) &ch, 1, 0xFFFF);   // 串口接收
//        HAL_GPIO_TogglePin(MY_LED_GPIO_PORT, MY_LED_PIN);
//        // 舵机角度测试
//        if (ch == '=') {
//            Robot_Leg_PWM(tmp);
//            tmp = 0;
//        } else {
//            tmp *= 10;
//            tmp += ch-'0';
//        }

    // 腿部舵机选择测试
//        Robot_Leg_Choose(ch-'0');

    // IMU 测试
    BMI088_read(gyro, accel, &temp);
    HAL_Delay(10);
    HAL_UART_Transmit(&huart, "\nTemp:", 6, 100);
    tmp_out.fx = temp;
    Float_Uart_Out(&huart, tmp_out);
    HAL_UART_Transmit(&huart, "\nAccelX:", 8, 100);
    tmp_out.fx = accel[0];
    Float_Uart_Out(&huart, tmp_out);
    HAL_UART_Transmit(&huart, "\nAccelY:", 8, 100);
    tmp_out.fx = accel[1];
    Float_Uart_Out(&huart, tmp_out);
    HAL_UART_Transmit(&huart, "\nAccelZ:", 8, 100);
    tmp_out.fx = accel[2];
    Float_Uart_Out(&huart, tmp_out);
    HAL_UART_Transmit(&huart, "\nGyroX:", 7, 100);
    tmp_out.fx = gyro[0];
    Float_Uart_Out(&huart, tmp_out);
    HAL_UART_Transmit(&huart, "\nGyroY:", 7, 100);
    tmp_out.fx = gyro[1];
    Float_Uart_Out(&huart, tmp_out);
    HAL_UART_Transmit(&huart, "\nGyroZ:", 7, 100);
    tmp_out.fx = gyro[2];
    Float_Uart_Out(&huart, tmp_out);

    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 6;
    RCC_OscInitStruct.PLL.PLLN = 168;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    RCC_OscInitStruct.PLL.PLLR = 2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
