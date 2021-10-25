#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int main() {
	struct timeval * tv = malloc(sizeof(struct timeval));
	suseconds_t inicio, fin;
	int i;

	if (gettimeofday(tv, NULL) != 0) {
		perror("Error while executing gettimeofday");
		return -1;
	}

	inicio = tv->tv_usec;
	
	for (i = 0; i <= 1000000; i++);
	
	if (gettimeofday(tv, NULL) != 0) {
		perror("Error while executing gettimeofday");
		return -1;
	}
	
	fin = tv->tv_usec;

	printf("Microseconds: %ld\n", fin - inicio);	

	free(tv);	
	return 0;
}
