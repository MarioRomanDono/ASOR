#include <stdio.h>
#include <string.h>

int main() {
	int i;
	char * error;

	for (i = 1; i <= 255; i++) {
		error = strerror(i);
		printf("Error number %d: %s\n", i, error);
	}
	return 0;
}
