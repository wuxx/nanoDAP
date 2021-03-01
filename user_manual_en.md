# CMSIS-DAP/DAPLink User Manual
* [Introduction](#introduction) 
* [Feature](#feature)
* [MDK Config](#mdk-config)
    * [Debugger Select](#debugger-select)
    * [Target Detect](#target-detect)
    * [Flash Algorithm](#flash-algorithm)
    * [Reset Setting](#reset-setting)
* [DAPLink Usage](#DAPLink-Usage)
    * [Drag-and-Drop](#drag-and-drop)
    * [Firmware Upgrade](#firmware-upgrade)
	
# Introduction
CMSIS-DAP/DAPLink is a cmsis-dap debugger made by MuseLab which support SWD/JTAG and a USB CDC serial port.
![screenshot](https://github.com/wuxx/nanoDAP/blob/master/doc/nanoDAP2.jpg)

# Feature
- open source hardware/software
- 5V/3.3V power supply to target board
- SWD interface
- JTAG interface
- USB CDC serial port
- DAPLink is a upgrade of CMSIS-DAP, which support drag-n-drop program
- DAPLink support drag-n-drop upgrade the firmware

# MDK config
plug the debugger into PC USB, if everything is ok, there will appear a CDC port and a USB HID device  
![usb_device](https://github.com/wuxx/nanoDAP/blob/master/doc/usb_device.png)
## Debugger Select
select CMSIS-DAP Debugger in Option -> Debug  
![debug_select](https://github.com/wuxx/nanoDAP/blob/master/doc/debug_select.jpg)  
## Target Detect
click Settings in Option -> Debug, recommend to select the swd port, and config the frequence to 10MHz
![target_id1](https://github.com/wuxx/nanoDAP/blob/master/doc/target_id1.png)

## Flash Algorithm
you need to config the flash algorithm for your target mcu, here is a example with stm32f1x  
Note: select the Reset and Run  for target auto reset after program done.
![flash_algorithm](https://github.com/wuxx/nanoDAP/blob/master/doc/flash_algorithm.jpg)

## Reset Setting
Generally, you may need to start the mcu when program done, config the Reset type to `SYSRESETREQ` here and select `Reset and Run` in the Flash Download Page above.
![reset_select](https://github.com/wuxx/nanoDAP/blob/master/doc/reset_select.jpg)

# DAPLink Usage
## Drag and Drop
plug the DAPLink into PC USB, there will be a USB DISK appear called DAPLink, 
![daplink_msd](https://github.com/wuxx/nanoDAP/blob/master/doc/DAPLink_MSD.png)  
DAPLink support drag and drop program, just drag the binary with suffix `hex` or `bin` into the DAPLink, the DAPLink will do all the program work.  
Tips: one firmware can only support one type of MCU drag-n-drop program, for different type of MCU, you may need to compile the source yourself. please check [here](https://github.com/ARMmbed/DAPLink/blob/master/docs/DEVELOPERS-GUIDE.md)

## Firmware Upgrade
DAPLink implement a bootloader with USB MSD, which made it very easy for the firmware upgrade.
1. short the nRST and GND.  
2. plug the DAPLink into PC USB, a USB DISK named `MAINTAINENCE` will appear.  
3. disconnect the nRST and GND.  
4. drag the new firmware into the `MAINTAINENCE`, wait for a few moment, then upgrade done, a new USB DISK `DAPLINK` will appear with replace of `MAINTAINENCE`  

