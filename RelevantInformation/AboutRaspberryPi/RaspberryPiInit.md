# 树莓派初始创建流程

> 本文档解决树莓派初始化问题

## 需求设备

- 树莓派（我用的是 4b 版本）
- 屏幕（可使用 HDMI 接口连接）
- SD 卡
- 鼠标、键盘、电脑

## 步骤

### 格式化 SD 卡

>
使用软件：[SD Card Formatter](https://www.sdcard.org/downloads/formatter/sd-memory-card-formatter-for-windows-download/)

![如图](/RelevantInformation/Photos/AboutRaspberryPi/SD_Card_Formatter.png)

### 烧录

> 使用软件：[Raspberry Pi Imager](https://www.raspberrypi.com/software/)

- 选择树莓派版本、操作系统版本、SD 卡
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/RaspberryPi_Burn_1.jpg)
- 点击 `next`，编辑配置
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/RaspberryPi_Burn_2.png)
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/RaspberryPi_Burn_3.png)
- 保存，`next`，等待烧录完成
    - 若进度始终停在 0%，自行挂 VPN
- 烧录完成后将 SD 卡插入树莓派

### 登录及使用

#### 第一次登录

> 使用设备：屏幕、鼠标、键盘

- 屏幕连接树莓派，连接电源，会自行初始化完成（编辑配置了的话）
- 加载完成进入桌面，右上角会显示设备 IP 地址
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/RaspberryPi_Desktop.png)
- 进入首选项，开启有关的配置（常用 SSH、VNC、串口、GPIO）并重启
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/RaspberryPi_Preferences.jpg)
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/RaspberryPi_Port.jpg)
- 设置语言、时间及键盘
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/RaspberryPi_Locale.jpg)
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/RaspberryPi_Timezone.jpg)
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/RaspberryPi_Keyboard.jpg)
- 设置 root 权限及用户
    - 见 [该文档](https://www.cnblogs.com/lhonghong/p/16170815.html)
- 设置国内源
    - 见 [该文档](https://zhuanlan.zhihu.com/p/98079246)
      最下面的 [文档链接](https://mirrors.tuna.tsinghua.edu.cn/help/raspbian/)

#### 设置 SSH

> 使用设备/软件：电脑、[PuTTY](https://www.putty.org/)

- 打开 PuTTY，并填写之前得到的树莓派 IP 地址
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/Putty_IP.png)
- 设置登录用户（用户名在前面烧录时配置了）
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/Putty_Login.png)
- 接收弹窗后，输入密码，之后即可通过 ssh 使用终端操纵树莓派了
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/Putty_Use.png)

#### 设置 VNC

> 使用设备/软件：电脑、[VNC Viewer](https://www.realvnc.com/en/connect/download/viewer/)

- 打开软件，无须登录，直接输入树莓派 IP 地址，出现弹窗同意/继续即可
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/VNC_Open.png)
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/VNC_Continue.png)
- 输入账号密码（烧录时设置的用户名和密码）即可使用了，以后就再也不需要使用屏幕了，可以用电脑直接通过网络登录树莓派桌面
  ![如图](/RelevantInformation/Photos/AboutRaspberryPi/VNC_Login.png)

## 参考资料

- [树莓派4B上手 - 从初始设置开始](https://cloud.tencent.com/developer/article/2299252)
- [整套相关初始设置](https://www.cnblogs.com/lhonghong/category/2147754.html)
- [更换国内源](https://zhuanlan.zhihu.com/p/98079246)
- [一劳永逸配置树莓派](https://zhuanlan.zhihu.com/p/63275945)