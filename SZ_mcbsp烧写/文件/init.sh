#!/bin/sh
insmod driver.ko
mknod /dev/McBSP1 c 500 0
./timll-3730
