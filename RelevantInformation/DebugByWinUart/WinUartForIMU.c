//
// Created by 86159 on 2025/2/24.
// 通过 win11 串口接收内容调试，主要用于调试 IMU
// 注意：
// 1、该程序不要在本项目（STM32 项目）直接运行，请放到单纯的 C 语言项目里运行
// 2、运行该程序时，记得提前将串口连接好
//
#include <windows.h>
#include <stdio.h>

// 用于辅助 float、double 变量测试的共用体
// 共用体：https://www.runoob.com/cprogramming/c-unions.html
union Data_Uart_Float {
    float fx;
    unsigned char byte[4];
};

union Data_Uart_Float tmp_out = {0};

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    char buffer[256];
    DWORD bytesRead;

    // 打开串口（根据你的实际情况修改COM端口）
    // 端口名参考：https://blog.csdn.net/martinkeith/article/details/102734376
    hSerial = CreateFile("\\\\.\\COM10", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "无法打开串口\n");
//        system("pause");
        return 1;
    }

    // 配置串口参数
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "获取串口状态失败\n");
        CloseHandle(hSerial);
//        system("pause");
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_115200;   // 波特率 9600
    dcbSerialParams.ByteSize = 8;          // 数据位 8
    dcbSerialParams.StopBits = ONESTOPBIT; // 停止位 1
    dcbSerialParams.Parity = NOPARITY;     // 无校验

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "设置串口参数失败\n");
        CloseHandle(hSerial);
//        system("pause");
        return 1;
    }

    // 设置超时参数
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "设置超时参数失败\n");
        CloseHandle(hSerial);
//        system("pause");
        return 1;
    }

    printf("正在监听串口数据...\n");

    // 持续读取数据
    while (1) {
        if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
            if (bytesRead > 0) {
                printf("\n0、温度；123、加速度计；456、陀螺仪\n");
                for (int i = 0; i < 7; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        tmp_out.byte[j] = buffer[i * 4 + j];
                    }
                    printf("收到数据 %d: %f\n", i, tmp_out.fx);
                }
            }
        } else {
            fprintf(stderr, "读取数据时发生错误\n");
            break;
        }
    }

    CloseHandle(hSerial);
//    system("pause");
    return 0;
}