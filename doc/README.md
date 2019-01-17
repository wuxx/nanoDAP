# CMSIS-DAP/DAPLink 用户手册
* [产品介绍](#产品介绍) 
* [产品特点](#产品特点)
* [MDK配置说明](#mdk配置说明)
    * [仿真器选择](#仿真器选择)
    * [目标检测](#目标检测)
    * [烧写算法](#烧写算法)
    * [复位设置](#复位设置)
* [DAPLink使用](#DAPLink使用)
    * [拖拽烧录](#拖拽烧录)
    * [固件升级](#固件升级)
* [FAQ](#faq)
    * [在win7系统下会提示无串口驱动，应该如何安装？](#q-在win7系统下会提示无串口驱动应该如何安装)
# 产品介绍
CMSIS-DAP/DAPLink 仿真器是MuseLab推出硬件软件均开源的仿真器，相比当前市面上流行的jlink/st-link，烧录速度快，不丢固件，无版权风险，功能丰富，价格低廉，外观简洁精致，能较好的满足电子工程师进行日常的开发调试下载需求。
![screenshot](https://github.com/wuxx/nanoDAP/blob/master/doc/nanoDAP2.jpg)

# 产品特点
- 硬件原理图PCB完全开源，软件开源，无版权风险。当前市面上的jlink/stlink均为盗版，使用上存在一些法律问题，部分jlink和IDE如MDK配合使用时，会提示盗版而无法正常使用，且部分jlink版本存在使用一段时间后丢固件的问题，一旦固件丢失，需要手动操作软件恢复固件，操作极其繁琐。同时 jlink售价亦较为昂贵。
- 引出5V、3.3V电源，不需要外接额外的电源到您的单板上，使用上更方便。
- 引出SWD接口，支持主流上位机调试软件，包括keil、IAR、openocd，均支持使用SWD进行下载、单步调试。
- 引出JTAG接口，配合openocd可支持全球范围内几乎所有SoC芯片的调试，如ARM Cortex-A系列、DSP、FPGA、MIPS等，因为SWD协议只是ARM自己定义的私有协议，而JTAG则是国际IEEE 1149标准。通常的仿真器目标芯片一般为ARM Cortex-M系列，均未引出JTAG接口，而本产品引出JTAG接口，适合您在其他平台下进行开发调试工作。
- 支持虚拟串口（也就是既可以用来当仿真器，又可以作为串口工具使用，替代ch340、cp2102，pl2303）。
- DAPLink是CMSIS-DAP仿真器的升级版，也是ARM官方在开源社区力推的仿真器，最大的特点是支持U盘拖拽烧录。插入DAPLink之后，PC上会出来一个U盘，只需将hex或者bin文件拖入到U盘中，即可完成烧录。
- DAPLink支持U盘固件升级，只需将nRST接地，插入DAPLink，PC上即会出来一个U盘，只需将新的固件（hex或者bin文件）拖入到U盘中，即可完成固件升级。因为DAPLink实现了一个带U盘功能的bootloader，可以方便的完成固件升级。若您有基于STM32的产品正在量产，而且产品后续可能需要升级，则DAPLink中的bootloader代码非常值得您参考，客户端不需要安装复杂的IDE或者烧写工具才能完成升级，只需拖动到U盘即可方便的完成您的产品升级。
- 具有一定深度的原理性的教程讲解视频，包括通信协议、硬件原理图PCB、和CMSIS-DAP软件系统，适合对嵌入式开发感兴趣的朋友观看学习。


# MDK配置说明
将CMSIS-DAP/DAPLink 插入到PC的USB口中，若一切正常，则在设备管理器中会出现一个虚拟串口和USB-HID设备，如图所示  
![usb_device](https://github.com/wuxx/nanoDAP/blob/master/doc/usb_device.png)
## 仿真器选择
在 Option -> Debug 一栏中选择CMSIS-DAP Debugger  
![debug_select](https://github.com/wuxx/nanoDAP/blob/master/doc/debug_select.jpg)
## 目标检测
在 Option -> Debug 菜单中点击Settings 进入配置菜单，如图所示，假若仿真器已经正常连接，则在左侧窗口会识别出仿真器的相关信息，假若使用SWD接口进行调试烧录，则请将接口配置成和左侧红框处一致。假若此时目标单板已经正常连接，则在右侧红框出会识别出目标单板的相关信息。  
![target_id1](https://github.com/wuxx/nanoDAP/blob/master/doc/target_id1.png)

## 烧写算法
对于特定的目标芯片，您需要为其配置特定的烧写算法，以stm32f10x系列为例，如图所示：  
![flash_algorithm](https://github.com/wuxx/nanoDAP/blob/master/doc/flash_algorithm.jpg)


## 复位设置
一般情况下，您或许希望烧写完芯片之后立即开始运行，我们的CMSIS-DAP经过软件定制，支持复位后立即开始运行，您需要在Debug 选项中进行配置，如图所示：  
![reset_select](https://github.com/wuxx/nanoDAP/blob/master/doc/reset_select.jpg)

# DAPLink使用
DAPLink 包含CMSIS-DAP的所有功能，使用的具体配置同上，这里是针对DAPLink的额外说明。
## 拖拽烧录
将DAPLink插入到PC中，正常情况下，会出现一个新的U盘，如图所示。
DAPLink支持U盘拖拽烧录，只需将hex或者bin文件拖拽到U盘中，即可完成芯片的烧录。  
注意：每一种固件只支持一种芯片的拖拽烧录，具体支持拖拽烧录的芯片请查看firmware目录，您可根据自己的需求选择升级不同的固件。

## 固件升级
DAPLink 实现了一个bootloader并且提供了U盘功能，这使得固件升级极为方便。具体固件升级的操作过程如下：
1. 使用杜邦线将nRST和GND短接。  
2. 将DAP插入到PC中，预期应该会出现一个名为MAINTAIN的U盘。  
3. 此时可以将nRST和GND断开。  
4. 将新的固件拖动到MAINTAIN U盘中，即可自动完成固件升级。

# FAQ
##### Q: 在win7系统下会提示无串口驱动，应该如何安装？  
##### A: 在仓库的software/windows7_serial_driver/ 目录下有CMSIS-DAP.inf，请尝试安装此驱动，大部分情况下可以正常安装使用，若仍然无法安装，请尝试目录下的另一驱动windows7_serial_driver.rar，根据压缩包里的指导进行操作即可。   
有任何问题或者建议，请在本仓库的[Issues](https://github.com/wuxx/nanoDAP/issues)页面中提出，我们会持续跟进解决。