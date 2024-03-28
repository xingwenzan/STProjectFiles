//
// Created by 86159 on 2024-03-29.
//

#include "mySysTick.h"



/**
 * @brief 系统定时器初始化，每 us 微秒中断一次
 * @param us
 */
void MY_SysTick_INIT(uint32_t us) {
    /*
     * SystemFrequency / 1000 1ms中断一次
     * SystemFrequency / 100000 10us中断一次
     * SystemFrequency / 1000000 1us中断一次
     *
     * 另：中断行为一律在 stm32f4xx_it.c 内
     * */
    my_sysTick_Countdown = 0;
    if (HAL_SYSTICK_Config(SystemCoreClock / 1000000 * us)) {
        while (1);  // Capture error 错误捕获
    }
}

/**
 * @brief 延时 num 个系统定时器中断
 * @param num
 */
void MY_SysTick_Delay(uint32_t num){
    my_sysTick_Countdown = num;
    while (my_sysTick_Countdown!=0);
}

/**
 * @brief 用于中断中，减少 my_sysTick_Countdown 的值
 */
void MY_SysTick_Countdown(){
    if (my_sysTick_Countdown!=0)my_sysTick_Countdown--;
}
