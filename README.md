# 两栖机器人开发项目

## 项目背景

> [背景调研](RelevantInformation/AboutSTM32/Research/背景调研.docx)

## 使用工具

- 代码编译 - CLion
    - 自行搜索：clion 开发 stm32
- 开发板 - STM32F446RC
    - 链接：【淘宝】https://m.tb.cn/h.5CJXeVUz83zlGUm?tk=SRL0WoMApgi CZ0012 「神器工具开发板比赛STM32F446达妙科技DM_MC01小米电机电赛机器人」
      点击链接直接打开 或者 淘宝搜索直接打开
- 仿真器 - JLink

## 各自进度

> 为了学到新东西 & 利用上空闲时间 & 努力有方向，电控方面进行扩展，尝试添加使用树莓派，进行功能扩展的同时深入理解计算机

- 电控
    - STM32
        - [x] HelloWorld! & PWM By Delay
        - [x] Example By SysTick
        - [x] PWM 初步应用
        - [x] 串口使用
        - [ ] CAN 及其他学习（方便控制额外电机）
    - 树莓派
        - [x] 外壳组装
        - [x] 系统下载
            - 下载地址：[官方软件](https://downloads.raspberrypi.org/imager/imager_latest.exe)
            - 一般挂 vpn 速度会快些，不挂有时候好使，有时候不好使
            - 我选择的系统：Raspberry Pi OS(64-bit)
        - [x] 开机、WiFi 连接与 ssh 连接
        - [x] 串口使用
- 原理
    - [机器人足数调研](RelevantInformation/AboutSTM32/Research/机械人足数调研.docx)
- 结构
    - [x] 最初版结构
    - [x] 3D 打印外壳，结构更新

## 实验进程

- [x] 第一次实验 - PWM 控制 4 电机 - 仅前移
    - 结果：无法行动
    - 问题：
        - 电机仅顺时针转动，导致左右腿反向 -> 电机调向
        - 太沉，电机力量不够，带不动 -> 换 12v 电源尝试
        - 电线发热 -> 需要更好的线以及焊接转接板
- [x] 第二次实验 - 4 电机直接供电 - 仅前移
    - 结果：未前移，机器人起来了，腿飞了
    - 问题：
        - 飞腿：新的固定方法
        - 电机疯转未前移：改舵机
        - 舵机带不动
            - [ ] 大型化：大舵机
            - [X] 小型化：小电池（重点在12v）、小电机（无需太大力，水下推动即可）
- [x] 第三次实验 - 8 舵机 - 仅站立/手持
    - 结果：腿未改变状态/舵机未转动，舵机颤抖 -> 舵机想动没转动
    - 问题：舵机力量不够 -> 电池驱动不够 -> 换电池

# 相关资料

- STM32F446RC
    - 数据手册
        - [官网](https://www.st.com/zh/microcontrollers-microprocessors/stm32f446/documentation.html)
        - 本地 &#x2002; 方便使用而下载到本地，基本都来自官网
            - [数据手册](RelevantInformation/AboutSTM32/DataSheet/stm32f446mc.pdf)
            - [参考手册](RelevantInformation/AboutSTM32/DataSheet/rm0390-stm32f446xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
            - [编程手册](RelevantInformation/AboutSTM32/DataSheet/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)
            - [Cortex-M3权威指南](RelevantInformation/AboutSTM32/DataSheet/Cortex_M3_Definitive_Guide(CN).pdf)
        - 其他资源
            - [野火 - STM32 HAL库开发实战指南](https://doc.embedfire.com/mcu/stm32/f429tiaozhanzhe/hal/zh/latest/index.html)
            - [Doxygen 注释规范](https://www.cnblogs.com/silencehuan/p/11169084.html)
- 树莓派
    - [官网](https://www.raspberrypi.com/)
    - [初始化文档](/RelevantInformation/AboutRaspberryPi/RaspberryPiInit.md)
        - 我喜欢的 Linux 配置 - 来自 [AcWing Linux 基础课](https://www.acwing.com/activity/content/57/)
            - 配置方法：将 [该文件](RelevantInformation/AboutRaspberryPi/LinuxConfig.zip) 解压缩后里面的内容上传到树莓派中
            - 上传方法：百度搜索 - Linux scp 使用
    - 使用
        - [B站视频](https://www.bilibili.com/video/BV1QB4y1M7EJ/?buvid=XU8906089F0C5E86A9676712E0A07656645F7&from_spmid=search.search-result.0.0&is_story_h5=false&mid=n%2FX0f%2F%2FzAX2mMZP5OK9PEg%3D%3D&p=1&plat_id=122&share_from=ugc&share_medium=android&share_plat=android&share_session_id=6aa7a45c-79b4-434e-a531-84a6a2bed73f&share_source=WEIXIN&share_tag=s_i&spmid=united.player-video-detail.0.0&timestamp=1713808563&unique_k=U51iiDN&up_id=330866298&vd_source=1ccb8ff2c60b49bbfff6dfe8c1bb0eab)

## 问题解决

- [Clion开发STM32添加文件后报错“No such file or directory“](https://blog.csdn.net/weixin_45636061/article/details/121623826)
- [解决IDEA配置.gitignore不生效的问题](https://blog.csdn.net/qq_43705131/article/details/107989768)
- [STM32F4xx_HAL_Driver](Drivers/STM32F4xx_HAL_Driver) 结构未定义(标红)/函数无法使用(淡黄字色)问题
    - 解除 [stm32f4xx_hal_conf.h](Core/Inc/stm32f4xx_hal_conf.h) 中对应定义的注释
    - 缺少驱动文件
        - [官网下载](https://www.st.com/zh/embedded-software/stm32cubef4.html)
          自行添加到 [STM32F4xx_HAL_Driver](Drivers/STM32F4xx_HAL_Driver) 文件夹中
- [系统时钟问题](https://blog.csdn.net/u014670574/article/details/70162036)

## 备注

- 自写代码添加到 [Users](Users) 文件夹中使用