# 机器狗整体控制

## 1、控制关系

> 通过树莓派接收图片信息并测量标志距离，根据所得距离信息与预设 `危险距离`
> 对比，启动串口，根据是否在 `危险距离以内` 发送 `停止` 或 `启动` 信息到单片机，单片机根据接收的启停信号来重新开始运动或停止运动，运动过程中机器狗的步伐完全由单片机控制

![如图](/RelevantInformation/Photos/AboutControl/TotalFlowChar.png)

## 2、系统初始化

详见 [树莓派初始化文档](/RelevantInformation/AboutRaspberryPi/RaspberryPiInit.md)
和 [Keil创建STM32项目并烧录使用](/RelevantInformation/AboutSTM32/STM32InitByKeil.md)

## 3、树莓派摄像头监视与距离获取

![如图](/RelevantInformation/Photos/AboutControl/PhotoDistGet.png)

> 具体步骤如下

-----------还没写---------

> 参考资料如下

1. [开机启动使用](https://shumeipai.nxez.com/2020/06/30/linux-usage-systemd.html)
    - 自启动服务应在 `/etc/systemd/system/`
      文件夹下，但为了方便，服务文件在被自启动的文件所在文件夹也有一份备份，请在该备份中更改，并在更改后将其复制到应在的文件夹，如 `sudo cp distance_measurement.service /etc/systemd/system/distance_measurement.service`
2. [定时使用脚本](https://www.labno3.com/2021/08/05/raspberry-pi-time-lapse-in-four-easy-steps/#i-8)
    - 最低使用间隔：1min -> 可通过循环命令和 `sleep` 命令解决
    - [cron 服务启、停、状态查看](https://www.jianshu.com/p/7cc20d441bda?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)
    - 注意：
    - 调用的脚本中一定要使用绝对路径，或在内部自行定义路径，一定不要直接使用全局的环境变量，否则既不会报错，也不会正常运行
    - cron 命令调用生成的内容有时候会自带写保护，影响不大
3. 摄像头使用
    - [libcamera 命令](https://shumeipai.nxez.com/2023/05/14/camera-module-v3-configuration-and-libcamera-usage.html)
      及其 [官方使用文档](https://www.raspberrypi.com/documentation/computers/camera_software.html#libcamera-and-libcamera-apps)
4. [特定图形（颜色块）测距](https://blog.csdn.net/qq_42444944/article/details/97415276)

## 4、串口信号发送与接收

### 4.1、树莓派的串口发送

> 具体实现

-----------还没写------------

> 参考资料

- [串口使用](https://blog.csdn.net/ZhuanShangNiDeXin/article/details/113791267)

### 4.2、单片机的串口接收

------------还没写-----------

## 5、单片机的 PWM 运动控制

-----------还没写------------