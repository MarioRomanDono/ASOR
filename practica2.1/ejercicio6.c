#include <unistd.h>
#include <stdio.h>

int main() {
	int value;
	
	// Longitud máxima de los argumentos
	if ((value = sysconf(_SC_ARG_MAX)) != -1) {
		printf("Maximum argument length: %d\n", value);
	}
	else {
		perror("Error while executing sysconf");
		return -1;
	}
	// Número máximo de los argumentos
	if ((value = sysconf(_SC_CHILD_MAX)) != -1) {
		printf("Maximum number of childs: %d\n", value);
	}
	else {
		perror("Error while executing sysconf");
		return -1;
	}
	// Número máximo de ficheros abiertos 
	if ((value = sysconf(_SC_OPEN_MAX)) != -1) {
		printf("Maximum number of opened files: %d\n", value);
	}
	else {
		perror("Error while executing sysconf");
		return -1;
	}
	return 0;
}
