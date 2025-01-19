//
// Created by 86159 on 2025/1/18.
//
#include "myIMU.h"
#include "myUsart.h"

void IMU_Init(void) {
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    // GPIO 使能
    // 加速度计和陀螺仪端口时钟使能
    AccelAndGryo_INT_GPIO_CLK_ENABLE();
    MY_GPIO_INIT(AccelAndGryo_INT_GPIO_Port, Accel_INT_Pin | Gryo_INT_Pin);
    // SPI 端口时钟使能
    SPI2_AccelAndGyro_CS_GPIO_CLK_ENABLE();
    MY_GPIO_INIT(SPI2_Accel_CS_GPIO_Port, SPI2_Accel_CS_Pin | SPI2_Gyro_CS_Pin);
    // DMA 初始化
    MX_DMA_Init();
    // SPI 初始化
    MX_SPI2_Init();
    // USB 驱动初始化
    MX_USB_DEVICE_Init();
    // 定时器初始化
    MX_TIM3_Init();
    uint8_t tmp = BMI088_init();
    while (tmp) {
        HAL_GPIO_TogglePin(MY_LED_GPIO_PORT, MY_LED_PIN);
//        HAL_UART_Transmit(&huart, &tmp, 1, 100);
        tmp = BMI088_init();
        HAL_Delay(100);
    }
}