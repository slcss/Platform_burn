环境：任意

先更新busybox：将新的 busybox 程序烧写到 /bin 目录下，chmod
在 /bin 目录下执行  ln -s busybox arp
之后即可直接运行arp

网络层：ip_interface  netlayer  netconfig.sh  routingp     生成方法：make clean，make

烧写步骤：烧写 ip_interface  netlayer  netconfig.sh  routingp

运行步骤：./ip_interface     ./netconfig.sh     ./netlayer     ./routingp	或者通过init.sh运行
