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
uint16_t walk = 0;   // walk ��ֵ���ò����� extern �ͱ�����������ͬһ����Ŀ�п��ļ�ʹ��
uint8_t walk_state = 2;  // walk_state ��ֵ���ò����� extern �ͱ�����������ͬһ����Ŀ�п��ļ�ʹ��
uint8_t walk_sign = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// IMU ��ȡ����
fp32 gyro[3] = {0}, accel[3] = {0}, temp = 0;
fp32 pitch = 0; // ������
fp32 roll = 0; // �����

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
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    /* USER CODE BEGIN 2 */
    // ��ʼ?? LED
    MY_LED_GPIO_CLK_ENABLE();   // LED��C �˿ڣ�ʱ��ʹ�ܣ�ʹ������ʱ��Ҫ�ȿ�������ʱ�ӣ��Ҷ˿�ʱ��ʹ�ܺ���ܽ��г�ʼ��
    MY_GPIO_INIT(MY_LED_GPIO_PORT, MY_LED_PIN);   // ��ʼ�� LED ����
    HAL_GPIO_WritePin(MY_LED_GPIO_PORT, MY_LED_PIN, GPIO_PIN_SET);
    // �����˳�ʼ��
    Robot_Init();   // �����˳�ʼ������
    // ��������
    TIMx_Configuration();   // ��ʼ��������ʱ����ʱ�������ƻ������˶���ÿһ���ĺ���
    MX_UART_Init();   // ��ʼ������
//    HAL_UART_Transmit(&huart, "my Uart Hello!\n", 15, 100);
    // ��ʼ�� IMU
    IMU_Init();

    // IMU �����ã����ڽ���ȡ�����ݷ���������
//    union Data_Uart_Float tmp_out = {0};

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1) {
        /* USER CODE BEGIN 3 */
        if (walk_sign) {
            // IMU ���ݶ�ȡ
            BMI088_read(gyro, accel, &temp);
            GetPitchAndRoll(gyro, accel, &pitch, &roll);
            // ���������˶�
            Robot_Leg_Do(&pitch, &roll);
            walk_sign = 0;

            // �ǶȲ���
//            tmp_out.fx = pitch;
//            Float_Uart_Out(&huart, tmp_out);
//            tmp_out.fx = roll;
//            Float_Uart_Out(&huart, tmp_out);
        }
        /*
        // IMU ���ԣ����ݶ�ȡ��ʾ��
        // temp
        tmp_out.fx = temp;
        Float_Uart_Out(&huart, tmp_out);
        // accel x,y,z
        for (int i = 0; i < 3; ++i) {
            tmp_out.fx = accel[i];
            Float_Uart_Out(&huart, tmp_out);
        }
        // gyro x,y,z
        for (int i = 0; i < 3; ++i) {
            tmp_out.fx = gyro[i];
            Float_Uart_Out(&huart, tmp_out);
        }
        HAL_Delay(100);
         */


        // ��Ҫ�źŽ��ղ��֣�ͨ�����մ����ź�ʵ����ͣ����
        uint8_t ch = 0;
        if (HAL_UART_Receive(&huart,  &ch, 1, 0) == HAL_OK && walk_state!=ch) {// ���ڽ���
            HAL_GPIO_TogglePin(MY_LED_GPIO_PORT, MY_LED_PIN);
            walk_state = ch;
        }

        /*
//        // ����ǶȲ���
//        if (ch == '=') {
//            Robot_Leg_PWM(tmp);
//            tmp = 0;
//        } else {
//            tmp *= 10;
//            tmp += ch-'0';
//        }
         */

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
