#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_init_semaphore 404
#define __NR_up_2 405

long init_semaphore(unsigned int initial_value)
{
	return syscall(__NR_init_semaphore, initial_value);
}

long up(unsigned int sem)
{
	return syscall(__NR_up_2, sem);
}