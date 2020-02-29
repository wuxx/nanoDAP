# CMSIS-DAP 升级说明 #
CMSIS-DAP 使用stm32f103c8t6，由于flash只有64KB，升级需要使用另外一个仿真器配合上位机对其进行升级，
如stlink + st utility，jlink + jflash，或者cmsis-dap + openocd/pyocd，（注意设置烧录起始地址为0x08000000）。

# DAPLink 升级说明 #
DAPLink使用 stm32f103cbt6，flash大小为128KB，DAPLink自带一个带U盘的bootloader，可以方便的
进行拖拽升级，升级步骤如下：  
1. 使用杜邦线将nRST和GND短接。  
2. 将DAP插入到PC中，预期应该会出现一个名为MAINTENANCE的U盘。  
3. 此时可以将nRST和GND断开。  
4. 将新的固件拖动到MAINTENANCE U盘中，即可自动完成固件升级。

PS:  
all-in-one-image目录下为完整的128KB镜像，若需要烧录此目录下的镜像，则和CMSIS-DAP一样，
需要另一个仿真器对其进行升级，其他目录下则可以通过拖拽方式进行升级。


