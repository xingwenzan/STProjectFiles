# 两栖机器人开发项目

## 项目背景

> [背景调研](RelevantInformation/Research/背景调研.docx)

## 使用工具

- 代码编译 - CLion
    - 自行搜索：clion 开发 stm32
- 开发板 - STM32F446RC
    - 链接：【淘宝】https://m.tb.cn/h.5CJXeVUz83zlGUm?tk=SRL0WoMApgi CZ0012 「神器工具开发板比赛STM32F446达妙科技DM_MC01小米电机电赛机器人」
      点击链接直接打开 或者 淘宝搜索直接打开
- 树莓派4B
    - 链接：【淘宝】https://m.tb.cn/h.gbH1X1HDpsrB7PX?tk=vHVsWsDZ7jL CZ0012 「树莓派4代B型 RaspberryPi4 4B 8GB 开发板编程AI入门套件
      Python」
      点击链接直接打开 或者 淘宝搜索直接打开
- 仿真器 - JLink

## 进度

- 电控
    - STM32
        - [x] HelloWorld! & PWM By Delay
        - [x] Example By SysTick
        - [x] PWM 初步应用
        - [x] 串口使用
        - [ ] IMU 应用
    - 树莓派
        - [x] 外壳组装
        - [x] 系统下载
            - 下载地址：[官方软件](https://downloads.raspberrypi.org/imager/imager_latest.exe)
            - 一般挂 vpn 速度会快些，不挂有时候好使，有时候不好使
            - 我选择的系统：Raspberry Pi OS(64-bit)
        - [x] 开机、WiFi 连接与 ssh连接（详见 [初始化文档](RelevantInformation/AboutRaspberryPi/RaspberryPiInit.md)）
        - [x] 串口使用
        - [x] 摄像头使用
    - 混合
        - [x] 树莓派与 STM32 的串口通信（正确接线即可正常使用）
        - [x] 树莓派定时拍摄并获取信息发送到 STM32
            - [x] 定时拍摄
            - [x] 信息获取
            - [x] 定时发送与接收
            - [x] 完整启停控制流程（即上面三个内容的拼接）
            - 参考文档
                - [树莓派定时发送图片到服务器](https://www.cnblogs.com/nnnv/p/17722550.html)
        - [x] 完整流程控制：树莓派控制启停、开发板控制运动
- 原理
    - [机器人足数调研](RelevantInformation/Research/机械人足数调研.docx)
    - [机器人足部运动方式调研](RelevantInformation/Research/足部运动.docx)
    - [灯哥开源](https://space.bilibili.com/493192058/lists/895912?type=series)
        - [运动学逆解](https://www.bilibili.com/video/BV13T4y1G7qy?spm_id_from=333.788.recommend_more_video.1&vd_source=1ccb8ff2c60b49bbfff6dfe8c1bb0eab)
        - [摆线坐标](https://www.bilibili.com/video/BV1KQ4y1K7aV/?spm_id_from=333.1387.collection.video_card.click&vd_source=1ccb8ff2c60b49bbfff6dfe8c1bb0eab)
        - [程序参考](https://github.com/ToanTech/py-apple-quadruped-robot/tree/master/Py%20Apple%20Dynamics%20V6.8/Py%20Apple%20Dynamics%20V6.8%20%E5%9B%BA%E4%BB%B6%E5%8F%8A%E7%A8%8B%E5%BA%8F/V6.8%20%E6%BA%90%E4%BB%A3%E7%A0%81)
    - 仿真（皆为 matlab 脚本）
        - [足部运动摆线](RelevantInformation/LegSport/Cyclone.m)
        - [腿部沿摆线运动整体形状](RelevantInformation/LegSport/LegCyclone.m)![如图](RelevantInformation/Photos/AboutOverall/FootMovementCycloid.png)
- 结构
    - [x] 最初版结构
    - [x] 3D 打印外壳，结构更新（[菠萝狗](http://padog.com.cn/#/index.md)）
    - [x] 
      结构重做（[菠萝狗-灯哥开源](https://github.com/ToanTech/py-apple-quadruped-robot/tree/master/%E4%BA%8C%E4%BB%A3%E8%8F%A0%E8%90%9D%EF%BC%88Py-Apple%20Structure%20V10.0%20%E4%B8%B2%E8%81%94%EF%BC%89)
      ），打印新的扩展板

## 实验进程

> 2024

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
- [x] 第四次实验 - 8 舵机 - 坐立 & 行走推演
    - 结果：成功坐立
    - 问题：顺拐 -> 重构身躯，问题解决
- [x] 第五次实验 - 8 舵机 - 坐立 & 行走
    - 结果：坐立、跪走
    - 问题：腿力量不够 -> 换舵机
- [x] 第六次实验 - 8 舵机 & 加脚掌 - 坐立 & 行走
    - 结果：很难坐立，但是行走正常（虽然脚步怪怪的）
    - 优化：调整代码，与树莓派结合

> 2025

- [x] 第一次实验 - 重新设计扩展板 & 重整步态方程
    - 结果：体态结构恢复正常，坐立运动皆可实现（运动时左偏，可能与初始零点设置有关）
    - 优化：重整零点，添加 IMU 模块调整
    - 实验效果：[效果视频](RelevantInformation/Photos/AboutOverall/RobotDogSport.mp4)
- [ ] 极限实验
    - [x] 图像获取与处理
    - [ ] 通讯速度：受波特率影响，速度绝对够，有时间再算
    - [ ] 单片机反应速度
    - [ ] 功耗测定

# 相关资料

- [总体设计](RelevantInformation/Research/课程设计_机器狗.docx)
    - [机器人整体控制](RelevantInformation/Research/TotalControl.md)
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
    - 相关文档
        - [Keil创建STM32项目并烧录使用](RelevantInformation/AboutSTM32/STM32InitByKeil.md)
- 树莓派
    - [官网](https://www.raspberrypi.com/)
    - [资料全集](https://pan.baidu.com/s/1SkvnrBC5YwOKgMn1FnPlzw?pwd=mylo)
    - [初始化文档](RelevantInformation/AboutRaspberryPi/RaspberryPiInit.md)
        - 我喜欢的 Linux 配置 - 来自 [AcWing Linux 基础课](https://www.acwing.com/activity/content/57/)
            - 配置方法：将 [该文件](RelevantInformation/AboutRaspberryPi/LinuxConfig.zip) 解压缩后里面的内容上传到树莓派中
            - 上传方法：百度搜索 - Linux scp 使用
            - 这里的 .bashrc 文件就不要用了，但是可以参考其中的 tmux 设置
    - 串口使用
        - [资料全集](https://pan.baidu.com/s/1SkvnrBC5YwOKgMn1FnPlzw?pwd=mylo)/
          `入门版——树莓派4B型初学者使用及设置指南`/`8.串口连接外部设备通信`
        - [原资料改编版](RelevantInformation/AboutRaspberryPi/RaspberryPiUartUse.docx)
        - [python 调用](https://blog.csdn.net/ZhuanShangNiDeXin/article/details/113791267)
    - 摄像头使用
        - 寻常拍照及录像：
            - [libcamera 命令](https://shumeipai.nxez.com/2023/05/14/camera-module-v3-configuration-and-libcamera-usage.html)
              及其 [官方使用文档](https://www.raspberrypi.com/documentation/computers/camera_software.html#libcamera-and-libcamera-apps)
        - python 库调用 - [创建虚拟环境时、环境创建后进行配置](https://docs.python.org/3/library/venv.html)
            - [picamera 库](https://blog.csdn.net/yong1585855343/article/details/121762202)
            - OpenCV(cv2 库)
            - [YOLO v11](https://github.com/ultralytics/ultralytics)：
                - [模型训练](https://www.heywhale.com/mw/project/677f7f94bf47195ee71aaf17)
                - [模型参数](RelevantInformation/AboutRaspberryPi/best.pt)
        - 视频截取帧：`ffmpeg` 命令
    - [定时使用脚本](https://www.labno3.com/2021/08/05/raspberry-pi-time-lapse-in-four-easy-steps/#i-8)
        - 最低使用间隔：1min -> 可通过循环命令和 `sleep` 命令解决
        - [cron 服务启、停、状态查看](https://www.jianshu.com/p/7cc20d441bda?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)
        - 注意：
            - 调用的脚本中一定要使用绝对路径，或在内部自行定义路径，一定不要直接使用全局的环境变量，否则既不会报错，也不会正常运行
            - cron 命令调用生成的内容有时候会自带写保护，影响不大
    - [开机启动使用](https://shumeipai.nxez.com/2020/06/30/linux-usage-systemd.html)
        - 自启动服务应在 `/etc/systemd/system/`
          文件夹下，但为了方便，服务文件在被自启动的文件所在文件夹也有一份备份，请在该备份中更改，并在更改后将其复制到应在的文件夹，如
          `sudo cp distance_measurement.service /etc/systemd/system/distance_measurement.service`
    - [jupyter lab 使用](https://lingshunlab.com/book/raspberry-pi/raspberry-pi-install-jupyter-lab)
        - [官网下载](https://jupyter.org/)
        - [汉化](https://blog.csdn.net/weixin_52444045/article/details/124558541)
    - python 使用
        - 虚拟环境使用
            - [网络参考文档](https://blog.csdn.net/qq_59449692/article/details/136397131)
            - [自写文档](RelevantInformation/AboutRaspberryPi/PythonVirtualEnvironment.docx)
            - [创建虚拟环境时、环境创建后进行配置](https://docs.python.org/3/library/venv.html)
            - 我的环境路径：`$HOME/.env`
        - [更换国内源](https://blog.csdn.net/qq_44214671/article/details/111008427)
        - [串口使用](https://blog.csdn.net/ZhuanShangNiDeXin/article/details/113791267)
        - [特定图形（颜色块）测距](https://blog.csdn.net/qq_42444944/article/details/97415276)
        - [CV2 读取图片文件](https://blog.csdn.net/weixin_43196262/article/details/82807698)
        - [查看包版本](https://blog.csdn.net/weixin_42578378/article/details/89293537)
    - 其他使用
        - [B站视频](https://www.bilibili.com/video/BV1QB4y1M7EJ/?buvid=XU8906089F0C5E86A9676712E0A07656645F7&from_spmid=search.search-result.0.0&is_story_h5=false&mid=n%2FX0f%2F%2FzAX2mMZP5OK9PEg%3D%3D&p=1&plat_id=122&share_from=ugc&share_medium=android&share_plat=android&share_session_id=6aa7a45c-79b4-434e-a531-84a6a2bed73f&share_source=WEIXIN&share_tag=s_i&spmid=united.player-video-detail.0.0&timestamp=1713808563&unique_k=U51iiDN&up_id=330866298&vd_source=1ccb8ff2c60b49bbfff6dfe8c1bb0eab)
        - [使用 python](https://blog.csdn.net/Eden2088/article/details/122118962)
        - [树莓派定时发送图片到服务器](https://www.cnblogs.com/nnnv/p/17722550.html)
- 其他相关
    - 扩展板
        - [扩展板结构](RelevantInformation/ExpansionBoard)
            - [二代](RelevantInformation/ExpansionBoard/exBoard_2.eprj)&#x2002;误将高电平直接接 5v
            - [三代](RelevantInformation/ExpansionBoard/exBoard_3.eprj)&#x2002;PWM 输出有时 GND 悬空（高阻态），波形无法使用
            - [四代](RelevantInformation/ExpansionBoard/exBoard_4.eprj)
        - 芯片使用
            - [三八译码器](https://atta.szlcsc.com/upload/public/pdf/source/20200619/C513527_D04113946337FFA11528F3555AE2E14A.pdf)
            - [三态门](https://atta.szlcsc.com/upload/public/pdf/source/20200402/C507191_D85B46125E3A0A7EFEB90895E388FB75.pdf)
            - [反相器1](https://atta.szlcsc.com/upload/public/pdf/source/20231109/6055D1B61DE2E899F5391931885BEAFC.pdf)
            - [反相器2](https://atta.szlcsc.com/upload/public/pdf/source/20170918/C131317_1505726905601976309.pdf)
            - [与门](https://atta.szlcsc.com/upload/public/pdf/source/20200624/C5593_29BD22E613BAE221D22F61679620A23D.pdf)
    - 舵机占空比参考：参考淘宝（注意：时基是 20ms，因此，约 5 次 PWM 周期才能凑出一次）
    - 调试（通过 win11 串口接收内容调试，主要用于调试 IMU）
        - [基础/通用/原始版](RelevantInformation/DebugByWinUart/WinUartBase.c)
        - [IMU 特化版](RelevantInformation/DebugByWinUart/WinUartForIMU.c)

## 问题解决

- [Clion开发STM32添加文件后报错“No such file or directory“](https://blog.csdn.net/weixin_45636061/article/details/121623826)
- [解决IDEA配置.gitignore不生效的问题](https://blog.csdn.net/qq_43705131/article/details/107989768)
- [STM32F4xx_HAL_Driver](Drivers/STM32F4xx_HAL_Driver) 结构未定义(标红)/函数无法使用(淡黄字色)问题
    - 解除 [stm32f4xx_hal_conf.h](Core/Inc/stm32f4xx_hal_conf.h) 中对应定义的注释
    - 缺少驱动文件
        - [官网下载](https://www.st.com/zh/embedded-software/stm32cubef4.html)
          自行添加到 [STM32F4xx_HAL_Driver](Drivers/STM32F4xx_HAL_Driver) 文件夹中
- [系统时钟问题](https://blog.csdn.net/u014670574/article/details/70162036)
- [树莓派为 py 安装依赖的包时 error: externally-managed-environment](https://www.yaolong.net/article/pip-externally-managed-environment/#%E6%96%B9%E6%A1%88%E4%B8%89%E9%AB%98%E9%98%B6-%E4%BD%BF%E7%94%A8venv)
- [树莓派使用 pip 安装太慢解决](https://blog.csdn.net/qq_43556844/article/details/113616214)
- [树莓派 py 使用串口不好使](https://blog.csdn.net/ChenWenHaoHaoHao/article/details/130328922)
- [无法进入图形界面](https://www.cnblogs.com/ssjxx98/p/16172291.html)：设置默认进入命令行，然后命令行运行 `startx` 命令
    - 如果同时开启 `systemctl` 开机自启动内容和 `cron` 定时功能，会出现该问题（因为 CPU 满了）
    - 解决 1：停止使用这两个功能，永久性解决问题
    - 解决 2：设置命令行进入，临时解决问题
        - ssh 登录，单次关闭两个中的任意一个，
        - 使用 `sudo raspi-config` 设置 `System Options`-
          `S5 Boot Auto Login Select boot into desktop or to command line` 为
          `B2 Console Autologin Text console,automatically logged in as 'your_name'user`
        - 重启，树莓派重启后屏幕默认将会变为命令行，在命令行里面再次任意关闭其中任意一个功能，输入 `startx` 即可进入正常界面
- [树莓派 git 问题](https://blog.csdn.net/qq_40296909/article/details/134285451)
- [树莓派使用 python 虚拟环境无法调用 `libcamera`](https://github.com/raspberrypi/picamera2/issues/341)
    - [创建虚拟环境时、环境创建后进行配置](https://docs.python.org/3/library/venv.html)

## 备注

- 代码规则
    - 自写代码添加到 [Users](Users) 文件夹中使用
    - `main.h` 里仅保留完全和 `main.c`、项目全局有关的定义，且被所有自写头文件调用
    - 所有自写头文件仅被 `main.c`、同名 `.c` 文件、相关头文件调用，内部仅包含自己相关的定义
    - `main.c` 仅在使用对应功能时引用相关头文件