# CMSIS-DAP 
## 源码
STM32F103C8T6_CMSIS-DAP_SWO    

# DAPLink 
## 源码
v2.3a  
## 工程说明
进入 v2.3a/DAPLink/projectfiles/uvision, 里面有以下三个工程，各自说明如下
### stm32f103xb_bl  
即bootloader, 大小为48KB,会烧录至 0x08000000 - 0x0800C000, 用于固件升级  
### stm32f103xb_stm32f103rb_if_hid
即interface, 大小为80KB, 会烧录至 0x0800C000 - 0x08020000, 使用USB HID传输, 为出厂烧录的固件, 通用性好  
### stm32f103xb_stm32f103rb_if_bulk  
即interface, 大小为80KB, 会烧录至 0x0800C000 - 0x08020000, 使用USB BULK传输, 速度比USB HID 固件快，然而只有Keil 5.29及以上版本才支持  

## 编译说明
分别编译 bootloader 和 interface 工程并烧录即可, 工程中有编译前后执行的脚本, 若本地没有python环境，可在keil中将执行前后的脚本打钩取消，代码略作修改，即可编译通过
