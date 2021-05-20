#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define __NR_hello_world_2 447

long hello_world()
{
	return syscall(__NR_hello_world_2);
}
