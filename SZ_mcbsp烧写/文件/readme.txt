uImage包含tun/tap

环境：Ubuntu 10.04 LTS

驱动：driver.ko     位置：'/home/shimw/桌面/mcbsp_drive'     生成方法：在 '/home/shimw/桌面/mcbsp_drive' 目录下执行命令 make clean 再执行 make   
相关源码：'/home/shimw/桌面/mcbsp_drive/fpga_drive.c'     '/home/shimw/桌面/mcbsp_drive/reg.c'

烧写步骤：
先通过SD卡烧写内核uImage，run updatesys
再烧写驱动 driver.ko，timll-3730，init.sh

运行步骤：
./init.sh
