#date:2014.4.16
#autor:lvv
#decription: run adhoc net system

#!/bin/bash

#set -e#!/bin/bash
#set -e
echo "insmod fpga_driver"
insmod nic_driver.ko
mknod /dev/fpga c 250 0
#echo "please input inode ID"
#read inode_ID
inode_ID=2
./ap_net $inode_ID &

ap_net_pid=`ps aux | grep ap_net | awk '$4!="grep" {print $1}'`
if [ ! $ap_net_pid ];then
  echo "ap_net failed to run"
  exit -1
else
  echo $ap_net_pid
  ./routes $ap_net_pid $inode_ID &
 # ./maodv $ap_net_pid $inode_ID &
#  ./maodv-al $ap_net_pid $ inode_ID &
fi

amixer set Master 50
amixer cset numid=6,iface=MIXER,name='Mic Volume' 10

route_pid=`ps aux | grep routes | awk '$4!="grep" {print $1}'`
./armIF -qws $inode_ID $route_pid&
