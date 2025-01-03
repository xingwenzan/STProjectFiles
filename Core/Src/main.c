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
uint8_t walk = 1;   // 为 myRobot 的 walk 赋值，该参数是 extern 型变量，可以在同一个项目中跨文件使用，只要在使用前正确赋值了
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void SystemClock_Config(void);   // 文件创建自带函数
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
    /* USER CODE BEGIN Init */
    HAL_Init();
    /* USER CODE END Init */

    /* Configure the system clock *************************************************/
    /* USER CODE BEGIN SysInit */
    SystemClock_Config();
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals *************************************/
    /* USER CODE BEGIN 2 */

    // 初始化 LED
    MY_LED_GPIO_CLK_ENABLE();   // LED（C 端口）时钟使能，使用外设时都要先开启它的时钟，且端口时钟使能后才能进行初始化
    MY_GPIO_INIT(MY_LED_GPIO_PORT,MY_LED_PIN);   // 初始化 LED & 5v 引脚

    // 初始化 5v 引脚、pwm 控制引脚
    MY_PWM_GPIO_CLK_ENABLE();  // 5v（C 端口）时钟使能
    MY_GPIO_INIT(MY_PWM_GPIO_PORT,MY_PWM_POWER_PIN|MY_PWM_CONTROL_PIN);   // 初始化 5v 引脚、pwm 控制引脚

    // PWM - 供电
    HAL_GPIO_WritePin(MY_PWM_GPIO_PORT, MY_PWM_POWER_PIN, GPIO_PIN_SET);   // 开启 PWM 正极
    HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_LED_PIN, GPIO_PIN_RESET);    // 开启小灯指示

    // 机器人初始化
    Robot_Init();   // 机器人初始化函数
    // 机器狗测试
    Robot_Leg_PWM(6554);
    Robot_Leg_Choose(1);

    // 其他功能
    TIMx_Configuration();   // 初始化基本定时器定时，1s 产生一次中断，控制机器人运动的每一步的核心
    MX_UART_Init();   // 初始化串口
    HAL_UART_Transmit(&huart, "my Uart Hello!\n", 15, 100);   // 串口发送内容（用于测试，可有可无）
    /* USER CODE END 2 */

    /* Infinite loop *************************************************************/
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE BEGIN 3 */
        // 主要信号接收部分，通过接收串口信号实现启停接收
        int ch;
        HAL_UART_Receive(&huart, (uint8_t *) &ch, 1, 0xFFFF);   // 串口接收
//        HAL_UART_Transmit(&huart, (uint8_t *) &ch, 1, 0xFFFF);   // 串口发送
//        if (ch == '1') {
//            walk = 1;
//            HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_LED_PIN, GPIO_PIN_RESET);
//        } else {
//            walk = 0;
//            HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_LED_PIN, GPIO_PIN_SET);
//        }

        // 腿部舵机选择测试
//        Robot_Leg_Choose(ch-'0');



        /* USER CODE END 3 */
    }
    /* USER CODE END WHILE */
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
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
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
