#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
	if (setuid(0) != 0) {
		fprintf(stderr, "Error number: %d\n", errno);
		perror("Error string");	
	}
	return 1;
}
