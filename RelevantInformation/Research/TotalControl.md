# 机器狗整体控制

## 控制关系

> 通过树莓派接收图片信息并测量标志距离，根据所得距离信息与预设 `危险距离`
> 对比，启动串口，根据是否在 `危险距离以内` 发送 `停止` 或 `启动` 信息到单片机，单片机根据接收的启停信号来重新开始运动或停止运动，运动过程中机器狗的步伐完全由单片机控制

![如图](/RelevantInformation/Photos/AboutControl/TotalFlowChar.png)

## 系统初始化

详见 [树莓派初始化文档](/RelevantInformation/AboutRaspberryPi/RaspberryPiInit.md)
和 [Keil创建STM32项目并烧录使用](/RelevantInformation/AboutSTM32/STM32InitByKeil.md)

## 树莓派摄像头监视与距离获取

## 串口信号发送与接收

## 单片机的 PWM 运动控制
