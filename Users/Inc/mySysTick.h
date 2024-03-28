//
// Created by 86159 on 2024-03-29.
//

#ifndef STPROJECTFILES_MYSYSTICK_H
#define STPROJECTFILES_MYSYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
extern uint32_t my_sysTick_Countdown;
void MY_SysTick_INIT(uint32_t us);
void MY_SysTick_Delay(uint32_t num);
void MY_SysTick_Countdown();

#ifdef __cplusplus
}
#endif

#endif //STPROJECTFILES_MYSYSTICK_H
