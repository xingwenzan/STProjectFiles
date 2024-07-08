# 机器狗整体控制

> 写在前面：
> 未特殊说明，一切树莓派操作皆在 `小黑框（终端）` 中进行
> STM32单片机的操作皆在创建的 Keil 项目中进行
>
> 项目创建：[Keil创建STM32项目并烧录使用](RelevantInformation/AboutSTM32/STM32InitByKeil.md)

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

- [初始化开启串口](/RelevantInformation/AboutRaspberryPi/RaspberryPiUartUse.docx)
- 使用 python 代码控制串口发送
    - [python 环境配置](/RelevantInformation/AboutRaspberryPi/PythonVirtualEnvironment.docx)并激活虚拟环境
    - 创建 `.py` 文件并在文件中添加如下代码（详情查看下方 `代码 4.1.1`、`代码 4.1.2`）
    - 运行刚才的文件（详情查看下方 `代码 4.1.3`）
    - 接收查看：树莓派与电脑正确连接后打开任意串口助手软件开启串口后皆可看见结果

```shell
# 代码 4.1.1
# 创建名为 python 文件；xxx 是文件名，可更改；`.py` 不允许更改
nano xxx.py
# 有些文件夹创建文件会要求根权限，则这么写，当然，最好不要在这种文件夹下操作
# sudo nano xxx.py

# 运行后会自动进入创建的文件
```

```python
# 代码 4.1.2
# 以下代码添加到刚刚创建的文件（创建后会自动进入）
import serial  # 添加串口包

ser = serial.Serial("/dev/ttyAMA0", 115200)  # 设置串口端口和波特率，前者自行查看，一般用本部分的串口初始化者和我的是一样的
ser.flushInput()  # 清除缓存
ser.write("Hello World\r\n".encode())  # 发送数据  \r\n可以实现换行  encode()默认是'utf-8'
# ctrl + o，回车：保存
# ctrl + x：退出该文件
```

```shell
# 代码 4.1.3
# 运行刚刚的文件
python3 xxx.py   # python3 文件名
```

> 参考资料

- [串口使用](https://blog.csdn.net/ZhuanShangNiDeXin/article/details/113791267)

### 4.2、单片机的串口接收

> 使用步骤

1. 正确接线
    - 一般串口接线都用四根线，本单片机也是选择四线制，下面是两个设备（设备A - 设备B）的串口连线，A 和 B 分别是什么无所谓
    - 5v - 5v
    - GND - GND
    - RX/RXD - TX/TXD
    - TX/TXD - RX/RXD
    - 本单片机和转接模块（USB 转 TTL）接线如下
      ![如图](/RelevantInformation/Photos/AboutControl/USBToUart.png)
2. 开启对应配置并检查文件完整性
    - 找到 [stm32f4xx_hal_conf.h](/Core/Inc/stm32f4xx_hal_conf.h) 中对应定义的定义并解除注释
      ![如图](/RelevantInformation/Photos/AboutControl/OpenUartSet.png)
    - 查看 [驱动文件夹](/Drivers/STM32F4xx_HAL_Driver) 下是否存在
      串口驱动文件 [stm32f4xx_hal_uart.c](/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c)
      和 [stm32f4xx_hal_uart.h](/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h)
      ![如图](/RelevantInformation/Photos/AboutControl/CheckHALUart.png)
    - 如果没有，请自行在 [官网](https://www.st.com/zh/embedded-software/stm32cubef4.html) 下载整个 HAL
      库，并分别复制这两个文件到正确的文件夹下
3. 串口初始化（详见 [myUart.c](/Users/Src/myUart.c) 注释）
    - 关于代码重写：库文件的函数不能修改，故为了实现初始化，必须重写；同时，这种不允许修改的函数是个 `__weak`
      （即弱定义）函数，在自写同名函数时将不会使用带 `__weak` 的函数
      ![如图](/RelevantInformation/Photos/AboutControl/CodeRewrite.png)
4. 两个函数解决串口常规使用问题
    - 串口发送函数：`HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)`
        - `UART_HandleTypeDef *huart`：已经初始化的串口结构体
        - `const uint8_t *pData`：将要发送的字符串
        - `uint16_t Size`：将要发送的字符串的大小
        - `uint32_t Timeout`：超时响应，超过设置的时间无论是否发送完成将会跳出串口发送
    - 串口接收函数：`HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)`
        - `UART_HandleTypeDef *huart`：已经初始化的串口结构体
        - `const uint8_t *pData`：将要接收的字符所存放的指针
        - `uint16_t Size`：将要接收的字符的大小
        - `uint32_t Timeout`：超时响应，超过设置的时间无论是否接收完成将会跳出串口接收
5. 另外：串口同样可以使用中断来控制，不过由于暂时无该需求，就未研究

> 参考资料

- [野火——STM32F4XX——串口](https://doc.embedfire.com/mcu/stm32/f429tiaozhanzhe/hal/zh/latest/doc/chapter20/chapter20.html)

## 5、单片机的 PWM 运动控制

-----------还没写------------