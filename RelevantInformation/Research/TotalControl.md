# 机器狗整体控制

## 0、写在前面：

1. 未特殊说明，一切树莓派操作皆在 `小黑框（终端）` 中进行STM32单片机的操作皆在创建的 Keil 项目中进行
2. 项目创建方法：[Keil创建STM32项目并烧录使用](/RelevantInformation/AboutSTM32/STM32InitByKeil.md)
3. 关于初始化函数的位置
    - （不推荐）直接写在 `main.c` 里
    - （推荐）创建单独的 `XXX.c` 和 `XXX.h` 用于放置相关函数，分别放在 [Core](/Core)
      文件夹下的 [Inc](/Core/Inc) 和 [Src](/Core/Src)里，前一个文件夹用于放 `XXX.h`，后者放 `XXX.c`
    - （较推荐）创建单独的 `XXX.c` 和 `XXX.h`
      用于放置相关函数，单独额外创建文件夹用于放置自写的文件（记得添加到项目的 `include` 中）<br>
      ![如图](/RelevantInformation/Photos/AboutControl/KeilUserPathAdd.png)

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
    - 本单片机和转接模块（USB 转 TTL）接线如下<br>
      ![如图](/RelevantInformation/Photos/AboutControl/USBToUart.png)
2. 开启对应配置并检查文件完整性
    - 找到 [stm32f4xx_hal_conf.h](/Core/Inc/stm32f4xx_hal_conf.h) 中对应定义的定义并解除注释<br>
      ![如图](/RelevantInformation/Photos/AboutControl/OpenUartSet.png)
    - 查看 [驱动文件夹](/Drivers/STM32F4xx_HAL_Driver) 下是否存在
      串口驱动文件 [stm32f4xx_hal_uart.c](/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c)
      和 [stm32f4xx_hal_uart.h](/Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_uart.h)<br>
      ![如图](/RelevantInformation/Photos/AboutControl/CheckHALUart.png)
    - 如果没有，请自行在 [官网](https://www.st.com/zh/embedded-software/stm32cubef4.html) 下载整个 HAL
      库，并分别复制这两个文件到正确的文件夹下
3. 串口初始化（详见 [myUart.c](/Users/Src/myUsart.c) 注释）
    - 关于代码重写：库文件的函数不能修改，故为了实现初始化，必须重写；同时，这种不允许修改的函数是个 `__weak`
      （即弱定义）函数，在自写同名函数时将不会使用带 `__weak` 的函数<br>
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

> 使用步骤

### 5.1、简述

- 引脚输出的 `PWM` 信号控制 180 度舵机的 `输出角度`
- 使用 `高级定时器` 根据当前应该输出的 `脚步状态` 控制引脚输出 `PWM` 信号
- 使用 `基本定时器` 根据 `时间` 控制当前应该输出的 `脚步状态`

### 5.2、`输出角度` 与 `PWM` 信号对应关系

1. 舵机选择
    - MG90S-180 度舵机
    - 【淘宝】限时满70减3 https://m.tb.cn/h.gSzxWhPoudoI3sg?tk=Y7Tf3bsHA3S MF6563 「SG90 9G经典舵机 180/360度
      数字舵机云台遥控飞机马达固定翼航模」
      点击链接直接打开 或者 淘宝搜索直接打开
2. 数据
    - 根据卖家所给数据来看，每次输入的信号不低于 20ms，信号占空比在 25% 到 75% 之间有效<br>
      ![如图](/RelevantInformation/Photos/AboutControl/MG90S_0.jpg)
      ![如图](/RelevantInformation/Photos/AboutControl/MG90S_1.jpg)

### 5.3、`高级定时器` 控制 `PWM` 输出信号

![如图](/RelevantInformation/Photos/AboutControl/STM32F4TIM.png)

1. 初始配置
    - 开启对应配置并检查文件完整性：同串口，不过开启的是 `TIM`
    - 代码配置：详见 [myYIM.c](/Users/Src/myTIM.c) 的 `高级定时器使用` 部分的注释
    - 关于死区：在生成的参考波形 OCxREF 的基础上，可以插入死区时间，用于生成两路互补的输出信号 OCx 和
      OCxN，死区时间的大小必须根据与输出信号相连接的器件及其特性来调整。<br>
      ![如图](/RelevantInformation/Photos/AboutControl/DeadTime.png)
    - 关于通道与引脚对应：这次我们使用的是 TIM8，通道 1、2、3、4 分别对应引脚 PC6、PC7、PC8、PC9（也可自行调整，不过只有这几个在本开发板上引出针脚了，图中的
      CHx 是各个通道）<br>
      ![如图](/RelevantInformation/Photos/AboutControl/STM32CHX.png)
      ![如图](/RelevantInformation/Photos/AboutControl/STM32FunctionalBlockDiagram.png)
2. 使用
    - 先在 `main.c` 使用自写的 `MX_TIM_Advance_Init` 初始化 PWM
    - 后通过 `__HAL_TIM_SetCompare(__HANDLE__, __CHANNEL__, __COMPARE__)` 调节占空比
        - `__HANDLE__`：调节的定时器，这里填 `htim_advance` 即可，已经设置好了 `extern` 关键字
        - `__CHANNEL__`：通道号，调哪个通道写哪个即可，我的代码中使用 `LEF_SMALL_RIGHT` 之类的是因为在 `main.h`
          里 `#define` 了，方便代码和实际物件的对应
        - `__COMPARE__`：调整后的占空比数值，实际占空比为 `__COMPARE__/2^16`

### 5.4、`基本定时器` 控制 `脚步状态`

1. 初始配置
    - 开启对应配置并检查文件完整性：同串口，开启的也是 `TIM`
2. 使用/撰写方法
    - 根据 [启动文件](/Core/Startup/startup_stm32f446rctx.s) 的中断向量表（146
      行）在 [中断处理文件](/Core/Src/stm32f4xx_it.c) 里编写对应的 `中断处理函数` 和 `回调函数`
    - 在合适的文件中（一般单独创建一个文件用于放置定时器相关配置和使用），编写定时器的初始化函数
        - 详见 [myYIM.c](/Users/Src/myTIM.c) 的 `基本定时器使用` 部分的注释
    - 在 `main.c` 中调用定时器初始化函数就完成了
3. 控制脚步
    - 通过前面提到过的 `__HAL_TIM_SetCompare(__HANDLE__, __CHANNEL__, __COMPARE__)` 控制输出的 PWM 占空比控制对应舵机的角度
    - 将机器狗走动时的体态分解，使其成为一个个状态，每个状态中的各个舵机输出的 PWM 信号不同，这样，一个状态就能变成一个函数，一个调节各个舵机到正确
      PWM 值的函数
    - 创建 `Robot_Control` 函数，其核心是内部带有 `static` 关键字的参数 `state`，代表各个状态，`state` 是多少就会调用多少号状态
    - 定时器回调函数内调用 `Robot_Control` 函数，每次调用都会更新 `state`，又由于该参数是 `static`
      ，每次调用 `Robot_Control` 函数时不会清零，而是会在原先的 `state` 值基础上进行更新

> 参考资料

- [野火——STM32F4XX——基本定时器](https://doc.embedfire.com/mcu/stm32/f429tiaozhanzhe/hal/zh/latest/doc/chapter30/chapter30.html)
- [野火——STM32F4XX——高级定时器](https://doc.embedfire.com/mcu/stm32/f429tiaozhanzhe/hal/zh/latest/doc/chapter31/chapter31.html)