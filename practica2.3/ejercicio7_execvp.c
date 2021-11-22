#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: ./myexecvp <command>\n");
		return -1;
	}
	
	if (execvp(argv[1], argv + 1) == -1) {
		perror("Error while executing execvp");
		return -1;
	}
	printf("El comando terminó de ejecutarse\n");
	return 0;
}
