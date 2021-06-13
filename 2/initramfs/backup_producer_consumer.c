#include "semaphore.h"
#include <stdio.h>

int main()
{
	unsigned int initial_value = 0;
	int sem = init_semaphore(initial_value);
	printf("🚀 ~ file: producer_consumer.c ~ line 7 ~ sem %d\n", sem);
	up(0);

	char a = getchar();
	down(0);

	a = getchar();
	down(0);

	a = getchar();

	up(0);
}