#include "semaphore.h"

int main () {
	unsigned int initial_value = 10;	
	int sem = init_semaphore(initial_value); 
	up(0);
}