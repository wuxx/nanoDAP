# 说明 #
这个固件是为了解决DAPLink 目前不支持jtag功能的问题，实际上就是cmsis-dap的固件，  
只不过编译的时候重定向到了0x0800c000，因为0x08000000 - 0x0800c000是DAPLink的bootloader。
只需进入DAPLInk bootloader，然后拖拽此镜像到bootloader的U盘中，即可升级。