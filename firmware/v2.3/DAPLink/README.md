### 文件说明
#### flash_image_128k_bl_if_hid.bin = (stm32f103xb_bl.bin + stm32f103xb_stm32f103rb_if_hid.hex)  
    完整的128KB镜像，包括bootloader(48KB)和interface(80KB)，为v2.3硬件版本出厂烧录固件
#### stm32f103xb_bl.bin  
    bootloader，大小为48KB
#### stm32f103xb_stm32f103rb_if_bulk.hex  
    interface, 大小为80KB, 支持usb bulk传输的固件(烧录速度是usb hid固件的一倍以上)，keil需要5.29版本及以上才支持，IAR支持，openocd不支持。
#### stm32f103xb_stm32f103rb_if_hid.hex  
    interface, 大小为80KB, 支持usb hid传输的固件，所有IDE包括keil，iar，openocd均支持。
