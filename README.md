# 两栖机器人开发项目

## 项目背景

> [背景调研](RelevantInformation/Research/背景调研.docx)

## 使用工具

- 代码编译 - CLion
    - 自行搜索：clion 开发 stm32
- 开发板 - STM32F446RC
    - 链接：【淘宝】https://m.tb.cn/h.5CJXeVUz83zlGUm?tk=SRL0WoMApgi CZ0012 「神器工具开发板比赛STM32F446达妙科技DM_MC01小米电机电赛机器人」
      点击链接直接打开 或者 淘宝搜索直接打开
- 仿真器 - JLink

## 各自进度

- 电控
    - [x] HelloWorld! & PWM By Delay
    - [x] Example By SysTick
    - [x] PWM 初步应用
    - [ ] CAN 及其他学习（方便控制额外电机）
- 原理
    - [机器人足数调研](RelevantInformation/Research/机械人足数调研.docx)
- 结构
    - [x] 最初版结构

## 实验进程

- [x] 第一次实验 - PWM 控制 4 电机 - 仅前移
  - 结果：失败
  - 问题：
    - 电机仅顺时针转动，导致左右腿反向 -> 电机调向
    - 太沉，电机力量不够，带不动 -> 换 12v 电源尝试
    - 电线发热 -> 需要更好的线以及焊接转接板

# 相关资料

- STM32F446RC
    - 数据手册
        - [官网](https://www.st.com/zh/microcontrollers-microprocessors/stm32f446/documentation.html)
        - 本地 &#x2002; 方便使用而下载到本地，基本都来自官网
            - [数据手册](RelevantInformation/DataSheet/stm32f446mc.pdf)
            - [参考手册](RelevantInformation/DataSheet/rm0390-stm32f446xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
            - [编程手册](RelevantInformation/DataSheet/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)
            - [Cortex-M3权威指南](RelevantInformation/DataSheet/Cortex_M3_Definitive_Guide(CN).pdf)
        - 其他资源
            - [野火 - STM32 HAL库开发实战指南](https://doc.embedfire.com/mcu/stm32/f429tiaozhanzhe/hal/zh/latest/index.html)
            - [Doxygen 注释规范](https://www.cnblogs.com/silencehuan/p/11169084.html)

## 问题解决

- [Clion开发STM32添加文件后报错“No such file or directory“](https://blog.csdn.net/weixin_45636061/article/details/121623826)
- [解决IDEA配置.gitignore不生效的问题](https://blog.csdn.net/qq_43705131/article/details/107989768)
- [STM32F4xx_HAL_Driver](Drivers/STM32F4xx_HAL_Driver) 结构未定义(标红)/函数无法使用(淡黄字色)问题
    - 解除 [stm32f4xx_hal_conf.h](Core/Inc/stm32f4xx_hal_conf.h) 中对应定义的注释
- [系统时钟问题](https://blog.csdn.net/u014670574/article/details/70162036)

## 备注

- 自写代码添加到 [Users](Users) 文件夹中使用