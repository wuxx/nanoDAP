* [自己动手做仿真器 之 nanoDAP 前言](#自己动手做仿真器-之-nanodap-前言) 
* [自己动手做仿真器 之 nanoDAP 原理分析0-硬件](#自己动手做仿真器-之-nanodap-原理分析0-硬件)
* [自己动手做仿真器 之 nanoDAP 原理分析1-软件](#自己动手做仿真器-之-nanodap-原理分析1-软件)
* [自己动手做仿真器 之 nanoDAP 原理分析2-协议](#自己动手做仿真器-之-nanodap-原理分析2-协议)
* [自己动手做仿真器 之 nanoDAP PCB及元器件](#自己动手做仿真器-之-nanodap-pcb及元器件)
* [自己动手做仿真器 之 nanoDAP 焊接](#自己动手做仿真器-之-nanodap-焊接)
* [自己动手做仿真器 之 nanoDAP 测试](#自己动手做仿真器-之-nanodap-测试)
* [自己动手做仿真器 之 nanoDAP 后记](#自己动手做cpu-之-nanodap-后记)
 
#### 自己动手做仿真器 之 nanoDAP 前言 ####
- 仿真器原理
- 当前流行的几种仿真器 (jlink stlink ulink cmsis-dap)
- nanoDAP
![nanoDAP1](https://github.com/wuxx/nanoDAP/blob/master/doc/nanoDAP1.jpg)
![nanoDAP1](https://github.com/wuxx/nanoDAP/blob/master/doc/nanoDAP2.jpg)

#### 自己动手做仿真器 之 nanoDAP 原理分析0-硬件 ####
- cpu
- osc
- power
- reset
- led
- header
#### 自己动手做仿真器 之 nanoDAP 原理分析1-软件 ####
- cmsis-dap
#### 自己动手做仿真器 之 nanoDAP 原理分析2-协议 ####
- jtag  
https://www.fpga4fun.com/JTAG.html
- swd  
Programming Internal Flash Over the Serial Wire Debug Interface
http://markdingst.blogspot.com/2014/03/programming-internal-sram-over-swd.html
https://github.com/MarkDing/swd_programing_sram
- uart  
https://www.fpga4fun.com/SerialInterface1.html
https://blog.csdn.net/zjy900507/article/details/79789671
#### 自己动手做仿真器 之 nanoDAP PCB及元器件 ####
#### 自己动手做仿真器 之 nanoDAP 焊接 ####
* 先焊接贴片元件，再焊接直插元件
* 贴片元件先焊接 CPU，使用拖焊，若引脚连锡，则烙铁沾上少许松香或者助焊剂接触连锡引脚使之分离。
* 焊接USB和2.54插针时，注意尽量摆放平整，和PCB平面对齐，避免歪斜。
#### 自己动手做仿真器 之 nanoDAP 测试 ####

#### 自己动手做仿真器 之 nanoDAP 后记 ####

reference:  
[bilibili视频教程合集](https://www.bilibili.com/video/av33323302/?p=1)  
[nanoDAP套件](https://item.taobao.com/item.htm?spm=a1z10.1-c-s.w4004-12590273744.22.507d20f8u9W5KD&id=583995116271)  
https://github.com/ARMmbed/DAPLink  
https://github.com/blacksphere/blackmagic  
https://github.com/ntfreak/openocd

