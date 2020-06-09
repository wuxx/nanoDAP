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
    * [WebUSB驱动应该如何安装？](#q-webusb驱动应该如何安装)
    * [烧录失败，提示 RDDI-DAP ERROR，应该如何解决？](#q-烧录失败提示-rddi-dap-error应该如何解决)
    * [无法检测到目标，提示communication failure，应该如何解决？](#q-无法检测到目标提示communication-failure应该如何解决)
    * [CMSIS-DAP/DAPLink目前支持哪些芯片的调试烧录？](#q-cmsis-dapdaplink目前支持哪些芯片的调试烧录)
    * [DAPLink目前支持哪些芯片的U盘拖拽烧录？](#q-daplink目前支持哪些芯片的u盘拖拽烧录)
    * [DAPLink如何升级固件？](#q-daplink如何升级固件)
    * [在Linux下能否使用dap仿真器进行调试？](#q-在linux下可以使用dap仿真器进行调试吗)
	
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
### Q: 在win7系统下会提示无串口驱动，应该如何安装？  
请参考 (https://github.com/wuxx/nanoDAP/tree/master/driver/windows7_serial_driver) 。   
### Q: WebUSB驱动应该如何安装？  
WebUSB可以在web网页上实现拖拽烧录，win10自带驱动支持，win7系统本身不支持，不常用，一般可不用理会。
### Q: 烧录失败，提示 RDDI-DAP ERROR，应该如何解决？
由于仿真器烧录速度较快，杜邦线之间的信号会产生串扰，请尝试换短一些的杜邦线，或者把紧密连在一起的杜邦线拉开，也可以尝试降低烧录速度，一般即可正常解决。
### Q: 无法检测到目标，提示communication failure，应该如何解决？
请首先排查硬件接线是否正确(GND, CLK, IO, 3V3)，然后检查目标板电源是否正常，若目标板由仿真器供电，由于USB最大输出电流只有500mA，请排查是否可能目标板供电不足。
### Q: CMSIS-DAP/DAPLink目前支持哪些芯片的调试烧录？
 典型的使用场景为对单片机进行编程调试，理论上Cortex-M系列的内核均可以使用DAP进行烧录调试，典型的芯片如STM32全系列的芯片，GD32全系列，nRF51/52系列等。
### Q: DAPLink目前支持哪些芯片的U盘拖拽烧录？
 目前DAPLink支持拖拽烧录的芯片并不算特别多，将来随着ARM社区支持力度将会增加更多芯片支持，目前支持U盘拖拽烧录的的芯片列表如下  
- stm32f072rb  
- stm32f103rb  
- stm32f207zg  
- stm32f401re  
- stm32f411re  
- stm32f429zi  
- stm32f746zg  
- stm32l476rg  
您可以自行编译固件，固件编译可参考[DEVELOPERS-GUIDE](https://github.com/ARMmbed/DAPLink/blob/master/docs/DEVELOPERS-GUIDE.md)，假若您有自己的芯片平台需要支持拖拽烧录，可以参考目前的代码作修改。
### Q: DAPLink如何升级固件？
请参考[CMSIS-DAP/DAPLink固件升级](https://github.com/wuxx/nanoDAP/tree/master/firmware/v2.3)
### Q: 在linux下可以使用DAP仿真器进行调试吗？
 linux下可以使用openocd配合DAP仿真器进行调试，openocd是目前全世界最流行，最强大的开源调试器上位机，由于openocd是跨平台的，你也可以在windows下使用openocd，通过编写适当的配置脚本，可以实现对芯片的调试、烧录等操作。由于涉及内容较多，更多说明请读者自行搜索，或者留言咨询。  


有任何问题或者建议，请在本仓库的[Issues](https://github.com/wuxx/nanoDAP/issues)页面中提出，我们会持续跟进解决。
