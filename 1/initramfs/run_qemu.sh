#!/bin/bash

SRC=/home/student/src
BOOT=$SRC/linux/arch/arm/boot
qemu-system-arm -M versatilepb -m 128M -nographic -kernel $BOOT/zImage -dtb $BOOT/dts/versatile-pb.dtb -initrd build/rootfs.gz -append "root=/dev/ram" -s -S
