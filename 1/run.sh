#!/bin/bash
docker run --name=pcs -ti --rm -v "$PWD/linux":/home/student/src/linux -v "$PWD/../3/initramfs":/home/student/src/initramfs pcs
