#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv) {
	int len = sysconf(_SC_ARG_MAX);
	char command[len];
	
	if (argc < 2) {
		fprintf(stderr, "Usage: ./mysystem <command>\n");
		return -1;
	}

	for (int i = 1; i < argc; i++) {
		strncat(command, argv[i], len);
		strncat(command, " ", 2);
	}

	if (system(command) == -1) {
		perror("Error while executing system\n");
		return -1;
	}
	printf("El comando terminó de ejecutarse\n");
	return 0;
}
